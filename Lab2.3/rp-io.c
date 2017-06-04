//
// Created by Павел on 21.05.2017.
//

#include "rp-internal.h"

#include "lib_ibas/v2.0/lib_ibas.h"
#include "lib_ibas/v2.0/io/files.h"
#include "lib_ibas/v2.0/collections/linked-list.h"

void openDataFile() {
  if (!unsavedChangesMenu()) return;

  String_t path = NULL;
  bool opened = false;

  //@formatter:off
  $with(path) {
    path = Console.prompt("Введите путь к файлу, который требуется загрузить: ");
  } $use {
    opened = readFile(String.CStr(path), records_);
  } $catch(FileOpenException) {
    opened = noSuchFileMenu(String.CStr(path));
  };
  //@formatter:on

  if (opened) {
    String.destroy(filePath_);
    filePath_ = path;
    unsavedChanges_ = false;
    showMessage("Файл успешно загружен. Считано записей: %d.", (int) LinkedList.size(records_));
  } else {
    String.destroy(path);
  }
}

bool readFile(CString_t path, LinkedList_t records) {
  bool good = false;

  //@formatter:off
  $withAuto(Scanner_t, scan) {
    scan = Files.openScanner(path);
  } $use {
    LinkedList.clear(records);
    LinkedList.deserialize(records, scan);
    good = true;
  } $catch(FormatException) {
    showMessage("Не удалось загрузить данные! Файл не соответствует формату программы.", 0);
  } $catch(FileOpenException) {
    $rethrow(NULL);
  } $catch(InputOutputException) {
    showMessage("Не удалось загрузить данные! Ошибка ввода/вывода.", 0);
  };
  //@formatter:on

  return good;
}

bool noSuchFileMenu(CString_t path) {
  Console.clearScreen();
  Console.CPrint("Такого файла не существует, или доступ к нему не разрешён!\n\n");

  static const int count = 3;
  static CString_t labels[] = {
      "Создать пустой файл с таким именем",
      "Открыть другой файл",
      "Отменить текущую операцию"
  };

  int option = Console.showMenu(NULL, count, labels, NULL);

  if (option == 3) return false;
  if (option == 2) {
    openDataFile();
    return false;
  }

  bool ret = false;
  //@formatter:off
  $try {
    Files.createFile(path, false);
    ret = true;
  } $catch(InputOutputException) {
    showMessage("Не удалось создать файл!", 0);
  };
  //@formatter:on
  return ret;
}

bool saveDataFile_() {
  static const int count = 4;
  static CString_t labels[] = {
      "Сохранить данные в файл, откуда они были загружены",
      "Сохранить в место последнего успешного сохранения",
      "Сохранить в другой файл",
      "Отменить текущую операцию"
  };

  if (!LinkedList.size(records_)) {
    showMessage("Нет загруженных записей!", 0);
    return false;
  }

  String_t path = NULL;
  if (filePath_ || savePath_) {
    Console.clearScreen();
    if (filePath_) Console.format("Данные загружены из файла: %s\n\n", String.CStr(filePath_));
    if (savePath_) Console.format("Последнее успешное сохранение: %s\n\n", String.CStr(savePath_));

    int option = Console.showMenu(NULL, count, labels, NULL);
    if (option == 4) return false;

    if (option == 1) path = filePath_;
    else if (option == 2) path = savePath_;
  }

  if (saveFile(path, records_)) {
    unsavedChanges_ = false;
    return true;
  }

  return false;
}

void saveDataFile() {
  saveDataFile_();
}

bool saveFile(String_t path, LinkedList_t records) {
  bool saved = false;
  String_t newPath = NULL;

  //@formatter:off
  $with(newPath) {
    if (!path)
      newPath = path = Console.prompt("Введите путь к файлу, куда требуется сохранить данные: ");
  } $use {
    saved = writeFile(String.CStr(path), records);
  };
  //@formatter:on

  if (!saved) {
    String.destroy(newPath);
    return false;
  }

  showMessage("Файл успешно записан!", 0);
  if (savePath_ != path) {
    String.destroy(savePath_);
    savePath_ = path;
  }

  return true;
}

bool writeFile(CString_t path, LinkedList_t records) {
  bool good = false;

  //@formatter:off
  $withAuto(Writer_t, writer) {
    writer = Files.openWriter(path, false);
  } $use {
    LinkedList.serialize(records, writer);
    good = true;
  } $catch(InputOutputException) {
    showMessage("Не удалось сохранить данные! Ошибка ввода/вывода.", 0);
  };
  //@formatter:on

  return good;
}

void saveResultFile(LinkedList_t records) {
  static const int count = 3;
  static CString_t labels[] = {
      "Сохранить в место последнего успешного сохранения",
      "Сохранить в другой файл",
      "Отменить текущую операцию"
  };

  if (!Console.confirm("Сохранить результат? (Y/N)", false)) return;

  String_t path = NULL;
  if (savePath_) {
    Console.clearScreen();
    Console.format("Последнее успешное сохранение: %s\n\n", String.CStr(savePath_));

    int option = Console.showMenu(NULL, count, labels, NULL);
    if (option == 3) return;
    if (option == 1) path = savePath_;
  }

  saveFile(path, records);
}
