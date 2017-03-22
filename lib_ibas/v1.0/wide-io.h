//
// Created by Павел on 09.11.2016.
//

#ifndef LABS_WIDE_IO_H
#define LABS_WIDE_IO_H

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <wchar.h>

extern const int WIDE_BUFFER_LENGTH;

wchar_t* inputWideString(wchar_t terminator);

wchar_t* inputWideLine();

#endif //LABS_WIDE_IO_H
