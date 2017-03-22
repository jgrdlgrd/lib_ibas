//
// Created by Павел on 17.12.2016.
//

#ifndef LABS_IO_H
#define LABS_IO_H

#include "lib_ibas/v3.0/base.h"
#include "primitive.h"

void newLine();

int showMenu(String prompt, const int count, String labels[count], BoundRunnable actions[count]);

void clearScreen();

void flush();

String setRusLocale();

bool prompt(String question);

#endif
