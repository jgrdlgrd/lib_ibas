//
// Created by Павел on 21.05.2017.
//

#pragma once

#include "record-processor.h"

extern bool unsavedChanges_;
extern String_t filePath_, savePath_;
extern LinkedList_t records_;
extern RecordHandler_i handler_;
extern Pointer_t iter_;
extern int recordNo_;

void mainMenu();

void openDataFile();
void saveDataFile();
bool saveDataFile_();
void saveResultFile(LinkedList_t records);
void recordsMenu();
void processRecords();

bool noSuchFileMenu(CString_t path);
bool readFile(CString_t path, LinkedList_t records);
bool saveFile(String_t path, LinkedList_t records);
bool writeFile(CString_t path, LinkedList_t records);

void nextRecord();
void prevRecord();
void addRecord();
void editRecord();
void removeRecord();
void clearRecords();
void sortRecords();
void printRecords();
void printRecords_(LinkedList_t records);

void showMessage(CString_t msg, int code);
bool unsavedChangesMenu();
