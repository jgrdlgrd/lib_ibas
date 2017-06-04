//
// Created by Павел on 21.05.2017.
//

#include "record-processor.h"
#include "rp-internal.h"

#include "lib_ibas/v2.0/lib_ibas.h"
#include "lib_ibas/v2.0/collections/linked-list.h"

bool unsavedChanges_;
String_t filePath_, savePath_;
LinkedList_t records_;
RecordHandler_i handler_;
Pointer_t iter_;
int recordNo_;

void start(RecordHandler_i handler) {
  $assert(handler != NULL);

  handler_ = handler;
  records_ = LinkedList.create();
  records_->elemClass = (Class_t) handler;

  mainMenu();
}

void finish() {
  unsavedChanges_ = false;
  iter_ = NULL;
  recordNo_ = 0;

  String.destroy(filePath_);
  filePath_ = NULL;
  String.destroy(savePath_);
  savePath_ = NULL;

  LinkedList.destroy(records_);
  records_ = NULL;
  handler_ = NULL;
}

void mainMenu() {
  static const int count = 5;
  static CString_t labels[] = {
      "Открыть файл данных",
      "Сохранить файл данных",
      "Работать с данными",
      "Запустить обработку данных",
      "Завершить работу с программой"
  };
  static Callable actions[] = {
      openDataFile,
      saveDataFile,
      recordsMenu,
      processRecords,
      NULL
  };

  while (true) {
    Console.clearScreen();
    int option = Console.showMenu(NULL, count, labels, actions);
    if (option == 5 && unsavedChangesMenu()) return;
  }
}

//returns true if it's okay to exit the program
bool unsavedChangesMenu() {
  static const int count = 3;
  static CString_t labels[] = {
      "Продолжить без сохранения",
      "Сохранить данные и продолжить",
      "Отменить текущую операцию"
  };

  if (!unsavedChanges_) return true;

  Console.clearScreen();
  Console.CPrint("Имеются несохранённые изменения исходных данных!\n\n");

  int option = Console.showMenu(NULL, count, labels, NULL);

  switch (option) {
    case 1:
      return true;
    case 2:
      return saveDataFile_();
    default:
      return false;
  }
}

void recordsMenu() {
  static const int count = 9;
  static CString_t labels[] = {
      "Следующая запись",
      "Предыдущая запись",
      "Добавить запись",
      "Редактировать запись",
      "Удалить запись",
      "Очистить список",
      "Отсортировать список",
      "Вывести список на экран",
      "Вернуться в главное меню"
  };
  static Callable actions[] = {
      nextRecord,
      prevRecord,
      addRecord,
      editRecord,
      removeRecord,
      clearRecords,
      sortRecords,
      printRecords,
      NULL
  };

  iter_ = LinkedList.begin(records_);
  recordNo_ = 1;

  while (true) {
    Console.clearScreen();

    if (iter_ == LinkedList.end(records_)) {
      Console.CPrintln("Вы достигли конца списка.\n"
                           "Можете добавить элемент в конец, или вернуться к предыдущему.");
      Console.format("Длина списка: %d\n\n", LinkedList.size(records_));
    } else {
      Console.format("Запись %d/%d:\n\n", recordNo_, LinkedList.size(records_));
      Console.printObj(LinkedList.iterGet(records_, iter_));
      Console.newLine();
      Console.newLine();
    }

    int option = Console.showMenu(NULL, count, labels, actions);
    if (option == 9) return;
  }
}

void processRecords() {
  if (!LinkedList.size(records_)) {
    showMessage("Нет загруженных записей!", 0);
    return;
  }

  //@formatter:off
  $withAuto(LinkedList_t, result) {
    result = handler_->process(records_);
  } $use {
    Console.clearScreen();
    showMessage("В новый список будут помещены данные счетов, количество средств на которых превышает"
                    " среднее количество средств по всем счетам.\n"
                    "Записи будут отсортированы по ФИО владельца счёта.", 0);

    Console.clearScreen();
    Console.colored(Colors.GREEN, "Результаты обработки:\n");
    printRecords_(result);
    Console.newLine();
    Console.newLine();

    if (LinkedList.size(result) > 0) {
      saveResultFile(result);
    } else {
      showMessage(NULL, 0);
    }

  };
  //@formatter:on
}

void showMessage(CString_t msg, int code) {
  Console.newLine();
  Console.format(msg, code);
  Console.newLine();
  Console.pause(NULL);
}

$defineNamespace(RecordProcessor) {
    start,
    finish
};
