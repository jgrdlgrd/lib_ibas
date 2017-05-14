//
// Created by Павел on 19.03.2017.
//

/*
0 0
1 1
-1 -1
5,45 99
0 0
1 0
0 1
5,45 99
 */

#include "lib_ibas/v2.0/lib_ibas.h"
#include "lib_ibas/v2.0/collections/linked-list.h"

void doTask(int count);
LinkedList_t inputList();
LinkedList_t filterList(LinkedList_t list);

int main() {
  Ibas.init();
  int exitCode = 0;

  //@formatter:off
  try {
    Console.setRusLocale();
    Console.autoDestroyStrings = true;

    Console.colored(Colors.GREEN, "Вас приветствует программа обработки списков!\n"
               "Введите список двумерных точек, и я отфильтрую все точки, встречающиеся более 1 раза.\n"
               "Автор: Павел Андреев.\n\n");

    Console.repeat(doTask, "Вы желаете ввести и обработать другой список точек? (Y/N): ");
    Console.newLine();
  } catch(RuntimeException) {
    exitCode = 1;
    e4c_print_exception(e4c_get_exception());
  } finally {
    Console.colored(Colors.GREEN, "Goodbye :)");
    Console.pause();
  }
  //@formatter:on

  Ibas.finish();
  return exitCode;
}

void doTask(int count) {
  if (count > 0) Console.clearScreen();

  Console.CPrintln("Введите координаты точек на плоскости (пары вещественных чисел). Пустая строка завершает ввод списка.\n");
  LinkedList_t list = inputList();
  Console.newLine();

  Console.CPrintln("Вы ввели:");
  Console.println(LinkedList.toPrettyString(list));
  Console.newLine();

  Console.CPrintln("После фильтрации:");
  LinkedList_t filtered = filterList(list);
  Console.println(LinkedList.toPrettyString(filtered));
  Console.newLine();

  LinkedList.destroy(list);
  LinkedList.destroy(filtered);
}

LinkedList_t inputList() {
  LinkedList_t list = LinkedList.createPrimitive(sizeof(DoublePair), DoublePair_w);

  Scanner_t scan = Scanner.fromStream(stdin);
  scan->multiline = false;
  int count = 1;

  while (true) {
    DoublePair dp;
    bool emptyLine = true, error = false;

    //@formatter:off
    try {
      Console.format("Точка № %d: ", count);
      dp.first = Scanner.nextDouble(scan);
      emptyLine = false;
      dp.second = Scanner.nextDouble(scan);
    } catch(EmptyTokenException) {
      error = true;
    } catch(FormatException) {
      error = true;
      emptyLine = false;
    }
    //@formatter:on

    if (Scanner.skip(scan) > 0) error = true; //junk at the end of line
    Scanner.skipLine(scan);

    if (emptyLine) break;
    if (error) {
      Console.CPrintln("Неверные координаты точки! Пожалуйста, повторите: ");
      continue;
    }

    LinkedList.add(list, &dp);
    count++;
  }

  return list;
}

LinkedList_t filterList(LinkedList_t list) {
  LinkedList_t result = LinkedList.createPrimitive(sizeof(DoublePair), DoublePair_w);
  if (list->size == 0) return result;

  LinkedList.sort(list, NULL);

  bool unique = true;
  Object_t iter = LinkedList.begin(list);
  DoublePair *prev = LinkedList.iterGet(list, iter);

  while (true) {
    iter = LinkedList.iterNext(list, iter);

    DoublePair *cur = NULL;
    if (iter != LinkedList.end(list))
      cur = LinkedList.iterGet(list, iter);

    if (cur && DoublePair_w->compare(prev, cur) == 0) {
      unique = false;
    } else {
      if (unique) LinkedList.add(result, prev);
      unique = true;
    }

    if (!cur) break;
    prev = cur;
  }

  return result;
}
