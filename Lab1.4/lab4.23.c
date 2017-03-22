//
// Created by Павел on 22.12.2016.
//

#include "lib_ibas/v1.5/io/console.h"
#include "lib_ibas/v1.5/util.h"

//const int MAGIC_BYTES_LENGTH = 4;
//const char MAGIC_BYTES[4] = {};

const int INITIAL_RECORD_BUFFER = 2;

const int FIELDS_IN_RECORD = 7;
const int DATE_FIELD = 1;

typedef struct {
    String flightNo,
        flightDate,
        lastName,
        firstName,
        patronymic,
        passportSeries,
        passportNo;
} Record;

int recordCount = 0, allocatedCount = 0;
bool unsavedChanges = false;
String filePath = NULL;
Record *records = NULL;

// ---------------------------------------------------------------

void mainMenu();

void openDataFile();
void saveDataFile();
void recordsMenu();
void processRecords();
void exitProgram();

int unsavedChangesMenu();
void noSuchFileMenu(String path);
void fileLoaded(int count, String path);
void fileNotLoaded(String path);

void addRecord();
void removeRecord();
void editRecord();

bool writeFile(String path, int count, Record *records);
void writeRecord(FILE *out, Record *r);
bool readRecord(FILE *in, Record *r);
void inputRecord(Record *r, bool allowEmpty);
void appendRecord(int *count, int allocatedCount, Record *array[], Record r);
void freeRecord(Record *r);
String inputField(String prompt, bool allowEmpty);
String inputDate(String prompt, bool allowEmpty);

void showMessage(String msg, int code);
void printRecords(int count, Record records[], bool showTotal);

// ---------------------------------------------------------------

int main(int argc, char **argv) {
  setRusLocale();
  mainMenu();
  return 0;
}

void mainMenu() {
  static const int count = 5;
  static String labels[] = {
      "Открыть файл данных",
      "Сохранить файл данных",
      "Работать с данными",
      "Запустить обработку данных",
      "Завершить работу с программой"
  };

  while (true) {
    clearScreen();
    int option = showMenu(count, labels);
    switch (option) {
      case 1:
        openDataFile();
        break;
      case 2:
        saveDataFile();
        break;
      case 3:
        recordsMenu();
        break;
      case 4:
        processRecords();
        break;
      case 5:
        exitProgram();
        break;
      default:
        showMessage("Unknown error (code: %d)!", option);
        exit(option);
    }
  }
}

int unsavedChangesMenu() {
  if (!unsavedChanges) return 0;

  clearScreen();
  printf("Имеются несохранённые изменения исходных данных!\n\n");

  static const int count = 3;
  static String labels[] = {
      "Продолжить без сохранения",
      "Сохранить данные и продолжить",
      "Отменить текущую операцию"
  };

  int option = showMenu(count, labels);

  switch (option) {
    case 2:
      saveDataFile();
    case 1:
      newLine();
      return 0;
    default:
      return 1;
  }
}

void noSuchFileMenu(String path) {
  clearScreen();
  printf("Такого файла не существует, или доступ к нему не разрешён!\n\n");

  static const int count = 3;
  static String labels[] = {
      "Создать пустой файл с таким именем",
      "Открыть другой файл",
      "Отменить текущую операцию"
  };

  int option = showMenu(count, labels);

  switch (option) {
    case 1: {
      FILE *out = fopen(path, "w");
      if (out) {
        fclose(out);
        fileLoaded(0, path);
        return;
      } else {
        showMessage("Не удалось создать файл!", 0);
      }
      break;
    }
    case 2:
      openDataFile();
    default:
      break;
  }
  if (path) free(path);
}

void appendRecord(int *count, int allocatedCount, Record *array[], Record r) {
  int shouldAllocate = *count ? *count + 1 : INITIAL_RECORD_BUFFER;

  if (shouldAllocate > allocatedCount) {
    Record *newArray = realloc(*array, shouldAllocate * sizeof(Record));
    if (!newArray) {
      showMessage("Ошибка! Не удалось выделить память для хранения записей.", 0);
      return;
    }
    (*count)++;
    *array = newArray;
  }

  (*array)[*count - 1] = r;
}

void fileLoaded(int count, String path) {
  recordCount = count;
  free(filePath);
  filePath = path;
  unsavedChanges = false;
  showMessage("Файл успешно загружен. Считано записей: %d.", count);
}

void fileNotLoaded(String path) {
  free(path);
  showMessage("Не удалось загрузить данные! Файл не соответствует формату программы.", 0);
}

void openDataFile() {
  if (unsavedChangesMenu()) return;

  printf("Введите путь к файлу, который требуется загрузить: ");
  String path = readLine(stdin);
  FILE *in = fopen(path, "r");

  if (in) {
    /*for (int i = 0; i < MAGIC_BYTES_LENGTH; i++) {
      if (feof(in) || fgetc(in) != MAGIC_BYTES[i]) {
        fclose(in);
        fileNotLoaded(path);
        return;
      }
    }*/

    int count = 0, allocated = 0;
    while (!feof(in)) {
      Record r;
      if (readRecord(in, &r)) {
        appendRecord(&count, allocated, &records, r);
      } else {
        fclose(in);
        fileNotLoaded(path);
        return;
      }
    }
    fclose(in);
    fileLoaded(count, path);
  } else {
    noSuchFileMenu(path);
  }
}

void saveDataFile() {
  static const int count = 3;
  static String labels[] = {
      "Сохранить данные в файл, откуда они были загружены",
      "Сохранить в другой файл",
      "Отменить текущую операцию"
  };

  if (!recordCount) {
    showMessage("Нет загруженных записей!", 0);
    return;
  }

  String path = NULL;
  if (filePath) {
    clearScreen();
    printf("Данные загружены из файла: %s\n\n", filePath);
    int option = showMenu(count, labels);
    if (option == 3) return;
    if (option == 1) path = filePath;
  }

  if (writeFile(path, recordCount, records)) {
    unsavedChanges = false;
  }
}

bool writeFile(String path, int count, Record *records) {
  static const int menuCount = 2;
  static String labels[] = {
      "Сохранить в другой файл",
      "Отменить текущую операцию"
  };

  while (true) {
    if (!path) {
      printf("Введите путь к файлу, куда требуется сохранить данные: ");
      path = readLine(stdin);
    }

    FILE *out = fopen(path, "w");
    free(path);
    path = NULL;

    if (!out) {
      clearScreen();
      printf("Возникла ошибка при записи в файл!\n");
      int option = showMenu(menuCount, labels);
      if (option == 1) continue;
      if (option == 2) return false;
    }

    for (int i = 0; i < count; i++) {
      writeRecord(out, &records[i]);
      if (i != count - 1) fputc('\n', out);
    }

    fclose(out);
    showMessage("Файл успешно записан!", 0);
    return true;
  }
}

bool readRecord(FILE *in, Record *r) {
  String *ptr = (String *) r;

  for (int i = 0; i < FIELDS_IN_RECORD; i++) {
    String field = readString(in, '\t');
    if (!field || !*field || (i == DATE_FIELD && !isValidDate(field))) {
      free(field);
      return false;
    }

    *ptr++ = field;
  }

  return fgetc(in) == '\n' || feof(in);
}

void writeRecord(FILE *out, Record *r) {
  String *ptr = (String *) r;

  for (int i = 0; i < FIELDS_IN_RECORD; i++) {
    fprintf(out, "%s\t", *ptr++);
  }
}

void recordsMenu() {
  static const int count = 4;
  static String labels[] = {
      "Добавить запись",
      "Удалить запись",
      "Редактировать запись",
      "Вернуться в главное меню"
  };

  while (true) {
    clearScreen();
    printRecords(recordCount, records, true);
    newLine();

    int option = showMenu(count, labels);

    switch (option) {
      case 1:
        addRecord();
        break;
      case 2:
        removeRecord();
        break;
      case 3:
        editRecord();
        break;
      default:
        return;
    }
  }
}

void showMessage(String msg, int code) {
  newLine();
  printf(msg, code);
  puts("\nНажмите Enter, чтобы вернуться в главное меню.");
  flush();
}

void printRecords(int count, Record records[], bool showTotal) {
  for (int i = 0; i < count; i++) {
    printf("Номер строки: %d\n"
               "Номер рейса: %s\n"
               "Дата рейса: %s\n"
               "Фамилия: %s\n"
               "Имя: %s\n"
               "Отчество: %s\n"
               "Серия паспорта: %s\n"
               "Номер паспорта: %s\n\n",
           i + 1,
           records[i].flightNo,
           records[i].flightDate,
           records[i].lastName,
           records[i].firstName,
           records[i].patronymic,
           records[i].passportSeries,
           records[i].passportNo
    );
  }

  if (showTotal) printf("Всего записей: %d\n", count);
}

void processRecords() {
  if (!recordCount) {
    showMessage("Нет загруженных записей!", 0);
    return;
  }

  String flight = inputField("Введите номер рейса, который Вас интересует: ", false);

  //puts(flight);

  String date1 = inputDate("Введите начальную дату: ", false),
      date2 = inputDate("Введите конечную дату: ", false);

  int count = 0, allocated = 0;
  Record *array = NULL;
  for (int i = 0; i < recordCount; i++) {
    //puts(records[i].flightNo);
    if (strcmp(records[i].flightNo, flight) == 0 && isBetween(date1, date2, records[i].flightDate))
      appendRecord(&count, allocated, &array, records[i]);
  }

  if (!count) {
    showMessage("Записей, удовлетворяющих критериям поиска, не найдено.", 0);
    return;
  }

  //printf("%d\n", count);
  for (int i = 0; i < count - 1; i++)
    for (int j = 0; j < count - i - 1; j++) {
      //puts(array[j].lastName);
      //puts(array[j + 1].lastName);
      //int r;
      if (strcmp(array[j].lastName, array[j + 1].lastName) > 0) {
        //printf("swap%d\n", r);
        Record tmp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = tmp;
      }
      //printf("%d\n", r);
    }

  writeFile(NULL, count, array);
  free(array);
}

void addRecord() {
  Record r;
  inputRecord(&r, false);
  appendRecord(&recordCount, allocatedCount, &records, r);
  unsavedChanges = true;
}

void inputRecord(Record *r, bool allowEmpty) {
  static String prompts[] = {
      "Введите номер рейса: ",
      "Введите дату рейса: ",
      "Введите фамилию: ",
      "Введите имя: ",
      "Введите отчество: ",
      "Введите серию паспорта: ",
      "Введите номер паспорта: "
  };

  String *ptr = (String *) r;
  for (int i = 0; i < FIELDS_IN_RECORD; i++) {
    String field;
    if (i == DATE_FIELD) field = inputDate(prompts[i], allowEmpty);
    else field = inputField(prompts[i], allowEmpty);

    if (field) *ptr++ = field;
  }
}

String inputField(String prompt, bool allowEmpty) {
  while (true) {
    printf(prompt);
    String field = readLine(stdin);
    if (!*field && allowEmpty) return NULL;
    if (*field && !strchr(field, '\t')) return field;
    free(field);
    printf("Неверный формат ввода! Поля записей не могут быть пустыми или содержать символа табуляции.\n");
  }
}

String inputDate(String prompt, bool allowEmpty) {
  while (true) {
    String field = inputField(prompt, allowEmpty);
    if (!field || isValidDate(field)) return field;
    free(field);
    printf("Неверный формат даты!\n");
  }
}

void removeRecord() {
  int index = readIntFromInterval("Номер удаляемой записи (введите 0, если хотите вернуться в предыдущее меню): ",
                                  "Такой записи не существует!", 0, recordCount);
  if (!index) return;

  freeRecord(records + index - 1);
  memmove(records + index - 1, records + index, (recordCount - index) * sizeof(Record));
  recordCount--;
  unsavedChanges = true;
}

void freeRecord(Record *r) {
  String *ptr = (String *) r;
  for (int i = 0; i < FIELDS_IN_RECORD; i++) {
    free(*ptr++);
  }
}

void editRecord() {
  int index = readIntFromInterval("Номер редактируемой записи (введите 0, если хотите вернуться в предыдущее меню): ",
                                  "Такой записи не существует!", 0, recordCount);
  if (!index) return;

  clearScreen();
  printf("\nТекущее состояние записи: \n");
  printRecords(1, records + index - 1, false);

  printf("Введите новые значения полей. При вводе пустой строки будет сохранено прежнее значение поля.\n");
  inputRecord(records + index - 1, true);
  unsavedChanges = true;
}

void exitProgram() {
  if (unsavedChangesMenu()) return;
  exit(0);
}
