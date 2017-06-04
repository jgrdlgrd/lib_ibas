//
// Created by Павел on 20.05.2017.
//

#pragma once

#ifndef USE_E4C

$declareException(AssertionException);
$declareException(RuntimeException);
$declareException(NotEnoughMemoryException);
$declareException(IllegalArgumentException);
$declareException(InputOutputException);
$declareException(NullPointerException);

#endif

$declareException(NotImplementedException);
$declareException(UnsupportedOperationException);
$declareException(EOFException);
$declareException(FormatException);

$declareException(EmptyTokenException);

$declareException(FileOpenException);
$declareException(FileAlreadyExistsException);
