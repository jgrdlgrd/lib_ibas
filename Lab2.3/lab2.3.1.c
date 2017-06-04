//
// Created by Павел on 20.05.2017.
//

#include "lib_ibas/v2.0/lib_ibas.h"
#include "lib_ibas/v2.0/collections/linked-list.h"
#include "lib_ibas/v2.0/util/time.h"
#include "record-processor.h"

struct RecordHandler handler;

int main() {
  Ibas.start();

  //@formatter:off
  $try {
    Console.setRusLocale();
    Console.autoDestroyStrings = true;

    RecordProcessor.start(&handler);

  } $finally {
    RecordProcessor.finish();
    Console.newLine();
    Console.colored(Colors.GREEN, "Goodbye :)");
    Console.pause("");
  }
  //@formatter:on

  Ibas.finish();
  return 0;
}

$declareType(Record);
$defineType(Record) {
  Class_t class;
  String_t firstName, lastName, patronymic, number;
  int sum;
  Time_t date;
};

void destroy(Record_t self) {
  String.destroy(self->firstName);
  String.destroy(self->lastName);
  String.destroy(self->patronymic);
  String.destroy(self->number);
  Time.destroy(self->date);

  free(self);
}

String_t toString(Record_t self) {
  String_t date = Time.toString(self->date);

  String_t str = String.format("ФИО: %s %s %s\n"
                           "Номер счёта: %s\n"
                           "Количество средств: %d\n"
                           "Дата открытия: %s",
                       String.CStr(self->lastName),
                       String.CStr(self->firstName),
                       String.CStr(self->patronymic),
                       String.CStr(self->number),
                       self->sum,
                       String.CStr(date));

  String.destroy(date);
  return str;
}

void serialize(Record_t self, Writer_t writer) {
  Writer.CPrint(writer, "{");
  String.serialize(self->firstName, writer);
  Writer.CPrint(writer, ", ");
  String.serialize(self->lastName, writer);
  Writer.CPrint(writer, ", ");
  String.serialize(self->patronymic, writer);
  Writer.CPrint(writer, ", ");
  String.serialize(self->number, writer);
  Writer.CPrint(writer, ", ");
  Int_w.serialize(&self->sum, writer);
  Writer.CPrint(writer, ", ");
  Time.serialize(self->date, writer);
  Writer.CPrint(writer, "}");
}

Record_t deserialize(Record_t self, Scanner_t scanner) {
  if (!self) self = Ibas.alloc(sizeof(Record_s), NULL);
  self->class = (Class_t) &handler;

  Scanner.match(scanner, "{");
  self->firstName = String.deserialize(NULL, scanner);
  Scanner.match(scanner, ",");
  self->lastName = String.deserialize(NULL, scanner);
  Scanner.match(scanner, ",");
  self->patronymic = String.deserialize(NULL, scanner);
  Scanner.match(scanner, ",");
  self->number = String.deserialize(NULL, scanner);
  Scanner.match(scanner, ",");
  Int_w.deserialize(&self->sum, scanner);
  Scanner.match(scanner, ",");
  self->date = Time.deserialize(NULL, scanner);
  self->date->dateOnly = true;
  Scanner.match(scanner, "}");

  return self;
}

static Time_t inputDate(CString_t prompt, CString_t errorMessage) {
  Time_t date = NULL;

  while (true) {
    if (prompt) {
      Console.CPrint(prompt);
    }

    //@formatter:off
    $withAuto(String_t, str) {
      str = Scanner.nextToken(Console.scanner);

      if (!Scanner.endLine(Console.scanner)) {
        date = Time.fromString(String.CStr(str));
      } else {
        $throw(FormatException, "Junk at the end of line!");
      }
    } $catch (FormatException) {
      if (errorMessage) Console.CPrint(errorMessage);
      else $rethrow(NULL);
    }
    //@formatter:on

    if (date) return date;
  }
}

Record_t input() {
  Record_t self = Ibas.alloc(sizeof(Record_s), NULL);
  self->class = (Class_t) &handler;

  self->lastName = Console.prompt("Введите фамилию: ");
  self->firstName = Console.prompt("Введите имя: ");
  self->patronymic = Console.prompt("Введите отчество: ");
  self->number = Console.prompt("Введите номер счёта: ");
  self->sum = Console.inputIntFromInterval(
      "Введите количество средств на счёте: ", "Ошибка! Введите целое неотрицательное число.\n", 0, INT_MAX);

  self->date = inputDate("Введите дату открытия счёта: ", "Неверный формат даты!\n");

  return self;
}

void edit(Record_t self) {
  static const int count = 7;
  static CString_t labels[] = {
      "Фамилия",
      "Имя",
      "Отчество",
      "Номер счёта",
      "Сумма на счёте",
      "Дата открытия",
      "Вернуться в меню"
  };

  while (true) {
    Console.clearScreen();

    Console.CPrintln("Вы редактируете запись:\n");
    Console.printObj(self);
    Console.newLine();
    Console.newLine();

    int option = Console.showMenu("Выберите редактируемое поле: ", count, labels, NULL);

    switch (option) {
      case 1:
        String.destroy(self->lastName);
        self->lastName = Console.prompt("\nВведите новое значение: ");
        break;
      case 2:
        String.destroy(self->firstName);
        self->firstName = Console.prompt("\nВведите новое значение: ");
        break;
      case 3:
        String.destroy(self->patronymic);
        self->patronymic = Console.prompt("\nВведите новое значение: ");
        break;
      case 4:
        String.destroy(self->number);
        self->number = Console.prompt("\nВведите новое значение: ");
        break;
      case 5:
        self->sum = Console.inputIntFromInterval(
            "Введите количество средств на счёте: ", "Ошибка! Введите целое неотрицательное число.\n", 0, INT_MAX);
        break;
      case 6:
        Time.destroy(self->date);
        self->date = inputDate("Введите дату открытия счёта: ", "Неверный формат даты!\n");
        break;
      default:
        return;
    }
  }
}

static int compareByName(Record_t rec1, Record_t rec2) {
  int ret;

  ret = String.compare(rec1->lastName, rec2->lastName);
  if (ret) return ret;

  ret = String.compare(rec1->firstName, rec2->firstName);
  if (ret) return ret;

  ret = String.compare(rec1->patronymic, rec2->patronymic);

  return ret;
}

static int compareByNumber(Record_t rec1, Record_t rec2) {
  return String.compare(rec1->number, rec2->number);
}

static int compareBySum(Record_t rec1, Record_t rec2) {
  return Int_w.compare(&rec1->sum, &rec2->sum);
}

static int compareByDate(Record_t rec1, Record_t rec2) {
  return Time.compare(rec1->date, rec2->date);
}

bool sort() {
  static const int count = 5;
  static CString_t labels[] = {
      "ФИО",
      "Номер счёта",
      "Сумма на счёте",
      "Дата открытия",
      "Отменить сортировку"
  };

  Console.clearScreen();
  int option = Console.showMenu("Выберите поле для сортировки: ", count, labels, NULL);

  switch (option) {
    case 1:
      handler.compare = (Compare_t) compareByName;
      break;
    case 2:
      handler.compare = (Compare_t) compareByNumber;
      break;
    case 3:
      handler.compare = (Compare_t) compareBySum;
      break;
    case 4:
      handler.compare = (Compare_t) compareByDate;
      break;
    default:
      return false;
  }

  return true;
}

LinkedList_t process(LinkedList_t records) {
  double avg = 0;

  Pointer_t iter = LinkedList.begin(records);
  while (iter != LinkedList.end(records)) {
    Record_t rec = LinkedList.iterGet(records, iter);
    avg += rec->sum;

    iter = LinkedList.iterNext(records, iter);
  }

  avg /= LinkedList.size(records);
  LinkedList_t result = LinkedList.create();

  iter = LinkedList.begin(records);
  while (iter != LinkedList.end(records)) {
    Record_t rec = LinkedList.iterGet(records, iter);
    if (rec->sum > avg)
      LinkedList.add(result, rec);

    iter = LinkedList.iterNext(records, iter);
  }

  handler.compare = (Compare_t) compareByName;
  LinkedList.sort(result, NULL);

  return result;
}

struct RecordHandler handler = {
    (Destroy_t) destroy,
    (ToString_t) toString,
    NULL,
    (Serialize_t) serialize,
    (Deserialize_t) deserialize,
    (Object_t (*)()) input,
    (void (*)(Object_t)) edit,
    process,
    sort
};
