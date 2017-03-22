//
// Created by Павел on 19.12.2016.
//

#ifndef LABS_BASE_H
#define LABS_BASE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <ctype.h>
#include <locale.h>

typedef char* String;
typedef void* Object;

typedef struct {
    int first, second;
} IntPair;

typedef struct {
    void *first, *second;
} Pair;

#endif //LABS_BASE_H
