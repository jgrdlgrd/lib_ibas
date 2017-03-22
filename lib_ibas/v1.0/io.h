#ifndef LABS_IO_H
#define LABS_IO_H

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

extern const int BUFFER_LENGTH;

char* inputString(char terminator);

char* inputLine();

char* inputText();

int inputToken(char *format, void *ptr, char *prompt, char *errorMessage);

double readDouble(char *prompt, char *errorMessage);

double readDoubleFromInterval(char *prompt, char *errorMessage, double min, double max);

int readInt(char *prompt, char *errorMessage);

int readIntFromInterval(char *prompt, char *errorMessage, int min, int max);

void flush();

char *setRusLocale();

bool prompt(char *question);

#endif
