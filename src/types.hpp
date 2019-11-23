#pragma once

#include <gmpxx.h>

using RegisterValue = mpz_class;

RegisterValue makeTuple(RegisterValue x, const RegisterValue& y);
RegisterValue combineLabels(const RegisterValue& labelX, const RegisterValue& labelY);
