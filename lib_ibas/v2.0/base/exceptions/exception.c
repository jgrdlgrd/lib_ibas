//
// Created by Павел on 23.12.2016.
//

#include "exception.h"

$defineException(UnsupportedOperationException, "Unsupported operation!", RuntimeException);
$defineException(NotImplementedException, "The feature is not implemented yet!", UnsupportedOperationException);
$defineException(EOFException, "Unexpected end of file!", InputOutputException);
$defineException(FormatException, "Invalid format!", RuntimeException);
