//
// Created by Павел on 17.12.2016.
//

#ifndef LABS_RECORD_PROCESSOR_H
#define LABS_RECORD_PROCESSOR_H

#include "lib_ibas/v2.0/io/console.h"

typedef struct {
    bool unsaved;
    String sourcePath;
} RecordProcessor;

typedef RecordProcessor RP;

RP *RP_new();

void RP_start(RP *rp);

void RP_destroy(RP *rp);

#endif //LABS_RECORD_PROCESSOR_H
