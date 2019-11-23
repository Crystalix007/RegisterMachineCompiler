#include <cassert>
#include <fstream>
#include <numeric>

#include "driver.hpp"

Grammar::Driver::Driver() {}

Grammar::Driver::~Driver() {
	delete (scanner);
	delete (parser);
}

void Grammar::Driver::parse(const char* const filename) {
	assert(filename != nullptr);
	std::ifstream iss{ filename };

	if (!iss)
		exit(EXIT_FAILURE);

	parse_helper(iss);
}

void Grammar::Driver::parse(std::istream& iss) {
	if (!iss.good() && iss.eof())
		return;

	parse_helper(iss);
}

void Grammar::Driver::parse_helper(std::istream& iss) {
	delete scanner;
	try {
		scanner = new Grammar::Scanner(&iss);
	} catch (const std::bad_alloc& ba) {
		std::cerr << "Failed to allocate scanner: \"" << ba.what() << "\". Exiting!\n";
		exit(EXIT_FAILURE);
	}

	delete parser;
	try {
		parser = new Grammar::Parser(*scanner, *this);
	} catch (const std::bad_alloc& ba) {
		std::cerr << "Failed to allocate parser: \"" << ba.what() << "\". Exiting!\n";
		exit(EXIT_FAILURE);
	}

	if (parser->parse() != 0) {
		std::cerr << "Parsing failure!\n";
	}
	return;
}

void Grammar::Driver::addInstruction(const std::shared_ptr<Instruction> instruction) {
	instructions.push_back(instruction);
}

RegisterValue Grammar::Driver::getEncoding() const {
	RegisterValue encoding = 0;
	auto tempInstructions = instructions;

	while (!tempInstructions.empty()) {
		const auto instruction = tempInstructions.back();
		tempInstructions.pop_back();
		const auto instructionEncoding = instruction->getEncoding();

		encoding = makeTuple(instruction->getEncoding(), encoding);
	}

	return encoding;
}
