//
// Created by Павел on 21.12.2016.
//

#ifndef LABS_PRIMITIVE_H
#define LABS_PRIMITIVE_H

#include "../base.h"
#include "text.h"

double readDouble(String prompt, String errorMessage);

double readDoubleFromInterval(String prompt, String errorMessage, double min, double max);

int readInt(String prompt, String errorMessage);

int readIntFromInterval(String prompt, String errorMessage, int min, int max);

#endif //LABS_PRIMITIVE_H
