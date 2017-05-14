//
// Created by Павел on 20.12.2016.
//

#ifndef LABS_FUNCTIONS_H
#define LABS_FUNCTIONS_H

#include "base.h"

typedef int (*Runnable)(void);

typedef int (*Supplier)(Object);

typedef int (*Consumer)(Object);
typedef int (*BiConsumer)(Object, Object);
typedef int (*TerConsumer)(Object, Object, Object);

typedef int (*Function)(Object, Object);
typedef int (*BiFunction)(Object, Object, Object);
typedef int (*TerFunction)(Object, Object, Object, Object);

typedef struct {
    Consumer call;
    Consumer destroy;
    void *context;
} BoundRunnable;

typedef struct {
    Function call;
    Consumer destroy;
    void *context;
} BoundSupplier;

typedef struct {
    BiConsumer call;
    Consumer destroy;
    void *context;
} BoundConsumer;
typedef struct {
    TerConsumer call;
    Consumer destroy;
    void *context;
} BoundBiConsumer;

typedef struct {
    BiFunction call;
    Consumer destroy;
    void *context;
} BoundFunction;
typedef struct {
    TerFunction call;
    Consumer destroy;
    void *context;
} BoundBiFunction;

int noop();
int noopConsumer(Object obj);

#endif //LABS_FUNCTIONS_H
