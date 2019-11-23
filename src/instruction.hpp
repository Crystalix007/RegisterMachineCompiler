#pragma once

#include "types.hpp"

class Instruction {
public:
	Instruction() = default;
	virtual ~Instruction() = default;

	virtual RegisterValue getEncoding() const = 0;
};

class BreakInstruction : public Instruction {
public:
	BreakInstruction() = default;
	virtual ~BreakInstruction() = default;

	virtual RegisterValue getEncoding() const;
};

class IncrementInstruction : public Instruction {
public:
	IncrementInstruction(RegisterValue sourceReg, RegisterValue destLabel);
	virtual ~IncrementInstruction() = default;

	virtual RegisterValue getEncoding() const override;

private:
	RegisterValue sourceReg, destLabel;
};

class DecrementInstruction : public Instruction {
public:
	DecrementInstruction(RegisterValue sourceReg, RegisterValue trueLabel, RegisterValue falseLabel);
	virtual ~DecrementInstruction() = default;

	virtual RegisterValue getEncoding() const override;

private:
	RegisterValue sourceReg, trueLabel, falseLabel;
};
