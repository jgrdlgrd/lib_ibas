//
// Created by Павел on 19.12.2016.
//

#ifndef LABS_VALIDATORS_H
#define LABS_VALIDATORS_H

#include "base.h"
#include "functions.h"

typedef struct {
    Consumer start;
    BiConsumer process;
    Consumer destroy;
    void *context;
    int* refCount;
} Validator;

Validator createValidator(Consumer start, BiConsumer process, Consumer destroy, size_t contextSize);
void useValidator(Validator v);
void destroyValidator(Validator v);

Validator chainValidators(Validator v1, Validator v2);

Validator PromptErrorValidator(String prompt, String errorMessage);

Validator IntRangeValidator(int min, int max);

#endif //LABS_VALIDATORS_H
