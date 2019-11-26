/* Parses an argument specification */
%skeleton "lalr1.cc"
%require "3.2"
%debug
%defines
%define api.namespace {Grammar}
%define api.parser.class {Parser}

%code requires{
#	include <memory>
#include "instruction.hpp"

	namespace Grammar {
		class Driver;
		class Scanner;
	}

#	ifndef YY_NULLPTR
#		if defined __cplusplus && 201103L <= __cplusplus
#			define YY_NULLPTR nullptr
#		else
#			define YY_NULLPTR 0
#		endif
#	endif
}

%parse-param { Scanner& scanner  }
%parse-param { Driver& driver }

%code{
#	include "driver.hpp"
#	include <string>
#	include <vector>
#	include <utility>

#	undef yylex
#	define yylex scanner.yylex

uint32_t labelIndex = 0;
}

%define api.value.type variant
%define parse.assert
%locations
%define api.location.file none

%token <uint32_t> REGISTER
%token <uint32_t> LABEL
%token            INCREMENT
%token            DECREMENT
%token            ARROW
%token            COMMA
%token            HALT
%token            INVALID_INPUT

%type <std::shared_ptr<Instruction>> INSTRUCTION

%start INSTRUCTIONS

%%

INSTRUCTIONS
	: %empty
	| INSTRUCTIONS INSTRUCTION {
		driver.addInstruction($2);
		labelIndex++;
	}
	| INSTRUCTIONS INVALID_INPUT {
		YYABORT;
	}
	;

INSTRUCTION
	: HALT {
		$$ = std::make_shared<BreakInstruction>();
		std::cout << labelIndex << ": " << "BREAK ==> 0" << std::endl;
	}
	| REGISTER INCREMENT ARROW LABEL {
		$$ = std::make_shared<IncrementInstruction>($1, $4);
		std::cout << labelIndex << ": " << "R" << $1 << "\u207a \u21a3 L" << $4 << " ==> " << $$->getEncoding() << std::endl;
	}
	| REGISTER DECREMENT ARROW LABEL COMMA LABEL {
		$$ = std::make_shared<DecrementInstruction>($1, $4, $6);
		std::cout << labelIndex << ": " << "R" << $1 << "\u207b \u21a3 L" << $4 << ", L" << $6 << " ==> " << $$->getEncoding() << std::endl;
	}
	;

%%

void Grammar::Parser::error(const location_type& loc, const std::string& err_message)
{
	std::cerr << "Error: \'" << err_message << "\' at " << loc << '\n';
}
