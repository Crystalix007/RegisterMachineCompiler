#pragma once

#include "instruction.hpp"
#include "parser.tab.hh"
#include "scanner.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace Grammar {
	class Driver {
	public:
		Driver();
		virtual ~Driver();

		void parse(const char* const filename);
		void parse(std::istream& iss);

		/*
		 * functions to store data retrieved by grammar / parser
		 */

		void addList(std::vector<uint32_t> list);
		static RegisterValue getListEncoding(std::vector<uint32_t> list);

		std::vector<std::vector<uint32_t>> getLists() const;

	private:
		void parse_helper(std::istream& iss);

		Grammar::Parser* parser = nullptr;
		Grammar::Scanner* scanner = nullptr;

		/*
		 * specialised data store
		 */

		std::vector<std::vector<uint32_t>> lists;
	};
} // namespace Grammar
