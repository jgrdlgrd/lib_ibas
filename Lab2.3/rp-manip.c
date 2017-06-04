//
// Created by Павел on 21.05.2017.
//

#include "rp-internal.h"

#include "lib_ibas/v2.0/lib_ibas.h"
#include "lib_ibas/v2.0/collections/linked-list.h"

void nextRecord() {
  if (recordNo_ > LinkedList.size(records_)) return;

  iter_ = LinkedList.iterNext(records_, iter_);
  recordNo_++;
}

void prevRecord() {
  if (recordNo_ <= 1) return;

  iter_ = LinkedList.iterPrev(records_, iter_);
  recordNo_--;
}

void addRecord() {
  Object_t record = handler_->input();
  LinkedList.iterInsert(records_, iter_, record);
  iter_ = LinkedList.iterPrev(records_, iter_);
  unsavedChanges_ = true;
}

void editRecord() {
  if (iter_ == LinkedList.end(records_)) {
    showMessage("Не выбрана запись!", 0);
    return;
  }

  handler_->edit(LinkedList.iterGet(records_, iter_));
  Console.clearScreen();
  unsavedChanges_ = true;
}

void removeRecord() {
  if (iter_ == LinkedList.end(records_)) {
    showMessage("Не выбрана запись!", 0);
    return;
  }

  Pointer_t next = LinkedList.iterNext(records_, iter_);
  LinkedList.iterRemove(records_, iter_);
  iter_ = next;
  unsavedChanges_ = true;
}

void clearRecords() {
  if (!LinkedList.size(records_)) return;

  LinkedList.clear(records_);
  iter_ = LinkedList.begin(records_);
  recordNo_ = 1;
  unsavedChanges_ = true;
}

void sortRecords() {
  if (!LinkedList.size(records_)) return;

  if (handler_->sort()) {
    LinkedList.sort(records_, NULL);
    unsavedChanges_ = true;
    recordNo_ = LinkedList.indexOf(records_, LinkedList.iterGet(records_, iter_)) + 1;
    showMessage("\nЗаписи отсортированы!", 0);
  }
}

void printRecords() {
  Console.clearScreen();
  printRecords_(records_);
  showMessage(NULL, 0);
}

void printRecords_(LinkedList_t records) {
  Console.format("Записей в списке: %d.\n", LinkedList.size(records));

  Pointer_t iter = LinkedList.begin(records);
  while (iter != LinkedList.end(records)) {
    Console.newLine();
    Console.newLine();
    Console.printObj(LinkedList.iterGet(records, iter));

    iter = LinkedList.iterNext(records, iter);
  }
}
