//
// Created by Павел on 17.12.2016.
//

#ifndef LABS_IO_H
#define LABS_IO_H

#include "../base.h"
#include "primitive.h"

void newLine();

void clearScreen();

void flush();

String setRusLocale();

int showMenu(const int count, String labels[count]);

bool prompt(String question);

#endif
