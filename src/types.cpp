#include "types.hpp"

RegisterValue makeTuple(RegisterValue x, const RegisterValue& y) {
	RegisterValue tuple = (2 * y + 1);

	while (x > 0) {
		tuple *= 2;
		x--;
	}

	return tuple;
}

RegisterValue combineLabels(const RegisterValue& labelX, const RegisterValue& labelY) {
	return makeTuple(labelX, labelY) - 1;
}
