#include "instruction.hpp"

IncrementInstruction::IncrementInstruction(RegisterValue sourceReg, RegisterValue destLabel)
    : sourceReg{ sourceReg }, destLabel{ destLabel } {}

RegisterValue BreakInstruction::getEncoding() const {
	return 0;
}

RegisterValue IncrementInstruction::getEncoding() const {
	return makeTuple(sourceReg * 2, destLabel);
}

DecrementInstruction::DecrementInstruction(RegisterValue sourceReg, RegisterValue trueLabel,
                                           RegisterValue falseLabel)
    : sourceReg{ sourceReg }, trueLabel{ trueLabel }, falseLabel{ falseLabel } {}

RegisterValue DecrementInstruction::getEncoding() const {
	return makeTuple(sourceReg * 2 + 1, combineLabels(trueLabel, falseLabel));
}
