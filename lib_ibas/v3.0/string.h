//
// Created by Павел on 07.11.2016.
//

#ifndef LABS_STRING_H
#define LABS_STRING_H

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wctype.h>

wchar_t *stringToWide(char *string);

char *stringToLower(char *str);

wchar_t *wideStringToLower(wchar_t *str);

#endif
