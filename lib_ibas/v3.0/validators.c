//
// Created by Павел on 19.12.2016.
//

#include "validators.h"

Validator createValidator(Consumer start, BiConsumer process, Consumer destroy, size_t contextSize) {
  void *ctx = malloc(contextSize + sizeof(int));
  if (ctx) {
    *((int*)(ctx + contextSize)) = 1;
  }
  return (Validator) {start, process, destroy, ctx, ctx + contextSize};
}

void useValidator(Validator v) {
  (*v.refCount)++;
}

void destroyValidator(Validator v) {
  if (*v.refCount > 0) {
    (*v.refCount)--;
  }
  if (*v.refCount == 0) {
    v.destroy(v.context);
  }
}

typedef struct {
    Validator v1, v2;
} VCH_Context;

int VCH_start(VCH_Context *ctx) {
  int ret = ctx->v1.start(ctx->v1.context);
  if (ret) return ret;
  return ctx->v2.start(ctx->v2.context);
}

int VCH_process(VCH_Context *ctx, void *value) {
  int ret = ctx->v2.process(ctx->v2.context, value);
  if (ret) value = NULL;
  return ctx->v1.process(ctx->v1.context, value);
}

int VCH_destroy(VCH_Context *ctx) {
  destroyValidator(ctx->v1);
  destroyValidator(ctx->v2);
  free(ctx);
  return 0;
}

Validator chainValidators(Validator v1, Validator v2) {
  Validator v = createValidator((Consumer) VCH_start, (BiConsumer) VCH_process, (Consumer) VCH_destroy, sizeof(VCH_Context));
  VCH_Context *ctx = v.context;
  useValidator(v1);
  ctx->v1 = v1;
  useValidator(v2);
  ctx->v2 = v2;
  return v;
}

int RWMV_start(Pair *ctx) {
  fputs(ctx->first, stdout);
  return 0;
}

int RWMV_process(Pair *ctx, void *value) {
  if (value) {
    return 0;
  }
  if (ctx->second) {
    fputs(ctx->second, stdout);
    return 1;
  }
  return -1;
}

Validator PromptErrorValidator(String prompt, String errorMessage) {
  Validator v = createValidator((Consumer) RWMV_start, (BiConsumer) RWMV_process, (Consumer) free, sizeof(Pair));
  Pair *ctx = v.context;
  ctx->first = prompt;
  ctx->second = errorMessage;
  return v;
}

int IRV_process(IntPair *ctx, int *value) {
  return !value || *value < ctx->first || *value > ctx->second;
}

Validator IntRangeValidator(int min, int max) {
  Validator v = createValidator(noopConsumer, (BiConsumer) IRV_process, (Consumer) free, sizeof(IntPair));
  IntPair *ctx = v.context;
  ctx->first = min;
  ctx->second = max;
  return v;
}
