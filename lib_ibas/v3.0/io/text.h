//
// Created by Павел on 21.12.2016.
//

#ifndef LABS_TEXT_H
#define LABS_TEXT_H

#include "lib_ibas/v3.0/base.h"
#include "lib_ibas/v3.0/validators.h"

extern const int BUFFER_LENGTH;

String readString(FILE *stream, char terminator);

String readLine(FILE *stream);

String readText(FILE *stream);

#endif //LABS_TEXT_H
