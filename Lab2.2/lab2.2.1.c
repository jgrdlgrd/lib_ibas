//
// Created by Павел on 19.03.2017.
//

#include "lib_ibas/v2.0/lib_ibas.h"
#include "lib_ibas/v2.0/collections/typed/double-linked-list.h"

int doTask();

int main() {
  Ibas.init();
  int exitCode = 0;

  try {
        Console.setRusLocale();
        Console.autoDestroyStrings = true;

        printf("Вас приветствует программа для поиска седловых точек в матрице\n"
                   "(седловой точкой называется элемент, являющийся минимумом в своём столбце и максимумом в своей строке).\n"
                   "Автор: Павел Андреев\n\n");
        Console.repeat(doTask, "Вы желаете найти седловые точки для другой матрицы? (Y/N): ");
        Console.newLine();
      } catch(RuntimeException) {
        exitCode = 1;
        e4c_print_exception(e4c_get_exception());
      } finally {
        Console.colored(Colors.GREEN, "Goodbye :)");
        Console.pause();
      }

  Ibas.finish();
  return exitCode;
}

int doTask() {
  printf("got it\n");

  DoubleLinkedList_t dv = DoubleLinkedList.create();
  DoubleLinkedList.add(dv, 16);
  DoubleLinkedList.add(dv, 154.25);

  DoubleLinkedList_t dv2 = DoubleLinkedList.create();
  DoubleLinkedList.add(dv2, 8888);
  DoubleLinkedList.add(dv2, 9999);
  DoubleLinkedList.insertAll(dv2, 1, dv);
  DoubleLinkedList.remove(dv2, 3);

  Console.print(DoubleLinkedList.toString(dv));
  Console.newLine();
  Console.print(DoubleLinkedList.toString(dv2));
  Console.newLine();

  DoubleLinkedList.clear(dv);
  DoubleLinkedList.addAll(dv2, dv);

  dv2->toStringFn = NULL;
  Console.print(DoubleLinkedList.toString(dv2));
  Console.newLine();

  printf("%d", DoubleLinkedList.indexOf(dv2, 16));
  Console.newLine();

  return 0;
}