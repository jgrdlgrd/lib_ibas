//
// Created by Павел on 21.12.2016.
//

#ifndef LABS_PRIMITIVE_H
#define LABS_PRIMITIVE_H

#include "lib_ibas/v3.0/base.h"
#include "lib_ibas/v3.0/validators.h"
#include "text.h"

int readInt(String prompt, String error);

int readIntV(Validator v);

double readDouble(String prompt, String error);

double readDoubleV(Validator v);

#endif //LABS_PRIMITIVE_H
