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
}

%define api.value.type variant
%define parse.assert
%locations
%define api.location.file none

%token <uint32_t> NUMBER
%token            OPEN_LIST
%token            CLOSE_LIST
%token            COMMA
%token            INVALID_INPUT

%type <std::vector<uint32_t>> LIST
%type <std::vector<uint32_t>> NUMS

%start LISTS

%%

LISTS
	: %empty
	| LISTS LIST {
		driver.addList($2);
	}
	;

LIST
	: OPEN_LIST CLOSE_LIST {
		$$ = {};
	}
	| OPEN_LIST NUMS CLOSE_LIST {
		$$ = $2;
	}
	;

NUMS
	: NUMBER {
		$$ = { $1 };
	}
	| NUMBER COMMA NUMS {
		$$ = $3;
		$$.push_back($1);
	}
	;

%%

void Grammar::Parser::error(const location_type& loc, const std::string& err_message)
{
	std::cerr << "Error: \'" << err_message << "\' at " << loc << '\n';
}
