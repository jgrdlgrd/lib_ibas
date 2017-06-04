//
// Created by Павел on 21.05.2017.
//

#pragma once

#include "../fwd.h"

$declareNamespace(Files) {
  void (*createFile)(CString_t path, bool rewriteExisting);
  String_t (*readFile)(CString_t path);

  Scanner_t (*openScanner)(CString_t path);
  Writer_t (*openWriter)(CString_t path, bool append);
};
