//
// Created by Павел on 19.03.2017.
//

#include <lib_ibas/v2.0/lib_ibas.h>
#include "lib_ibas/v2.0/containers/linked-list.h"

int doTask();

int main() {
  Ibas.init();
  int exitCode = 0;

  try {
        Console.setRusLocale();

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
  LinkedList_t list = LinkedList.create(5);
  printf("got it");
  list = LinkedList.create(0);

  return 0;
}