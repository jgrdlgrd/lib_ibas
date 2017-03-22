//
// Created by Павел on 17.12.2016.
//

#include "record-processor.h"

int saveDataFileHandler(RP *ctx);

int openDataFileHandler(RP *ctx);

int showUnsavedChangesMenu(RP *ctx) {
  if (!ctx->unsaved) return 0;

  puts("Имеются несохранённые изменения исходных данных!\n");

  static const int count = 3;
  static String labels[] = {
      "Продолжить без сохранения",
      "Сохранить данные и продолжить",
      "Отменить текущую операцию"
  };

  BoundRunnable actions[] = {
      {},
      {(Consumer) saveDataFileHandler, NULL, ctx},
      {}
  };

  return showMenu("Выберите действие: ", count, labels, actions);
}

int showFileNotOpenedMenu(RP *ctx) {
  puts("Такого файла не существует, или доступ к нему не разрешён!\n");

  static const int count = 3;
  static String labels[] = {
      "Создать пустой файл с таким именем",
      "Открыть другой файл",
      "Отменить текущую операцию"
  };

  BoundRunnable actions[] = {
      {},
      {(Consumer) openDataFileHandler, NULL, ctx},
      {}
  };

  return showMenu("Выберите действие: ", count, labels, actions);
}

int openDataFileHandler(RP *ctx) {
  if (showUnsavedChangesMenu(ctx) == 3) return 0;

  puts("Введите путь к файлу: ");
  String path = readLine(stdin);
  FILE *file = fopen(path, "r");

  if (!file) {
    if (showFileNotOpenedMenu(ctx) != 1) return 0;
    file = fopen(path, "w");
    if (!file) {
      puts("Ошибка при создании файла!");
      return 0;
    }
  }
}

int saveDataFileHandler(RP *ctx) {
  if (ctx->sourcePath) {

  }
}

int exitHandler(RP *ctx) {
  return showUnsavedChangesMenu(ctx);
}

int showMainMenu(RP *ctx) {
  static const int count = 5;
  static String labels[] = {
      "Открыть файл данных",
      "Сохранить файл данных",
      "Работать с данными",
      "Запустить обработку данных",
      "Завершить работу с программой"
  };

  BoundRunnable actions[] = {
      {(Consumer) openDataFileHandler, NULL, ctx},
      {(Consumer) openDataFileHandler, NULL, ctx},
      {(Consumer) openDataFileHandler, NULL, ctx},
      {(Consumer) openDataFileHandler, NULL, ctx},
      {(Consumer) exitHandler, NULL, ctx},
  };

  return showMenu("Выберите действие: ", count, labels, actions);
}

RP *RP_new() {
  RP *rp = malloc(sizeof(RP));
  return rp;
}

void RP_start(RP *rp) {
  showMainMenu(rp);
}

void RP_destroy(RP *rp) {
  free(rp);
}
