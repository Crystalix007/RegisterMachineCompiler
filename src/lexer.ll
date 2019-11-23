/* Simply lexes arguments */
%{
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <vector>
#include "parser.tab.hh"
#include "scanner.hpp"

#undef YY_DECL
#define YY_DECL int Grammar::Scanner::yylex(Grammar::Parser::semantic_type* const lval, Grammar::Parser::location_type* lloc)
#define YY_USER_ACTION lloc->step(); lloc->columns(yyleng);

using token = Grammar::Parser::token;

#define LOG std::clog
%}

%option debug
%option nodefault
%option yyclass="Grammar::Scanner"
%option noyywrap
%option c++

SPACE [[:space:]]
SYMBOL [^[:space:][:alnum:]]
WORD [[:alnum:]]

%%

%{	/** Code executed at the beginning of yylex **/
	yyval = lval;
%}

"HALT" {
	return token::HALT;
}

R[[:digit:]]+ {
	yyval->build<uint32_t>(std::stoul(yytext + 1));
	return token::REGISTER;
}

L[[:digit:]]+ {
	yyval->build<uint32_t>(std::stoul(yytext + 1));
	return token::LABEL;
}

"+" {
	return token::INCREMENT;
}

"-" {
	return token::DECREMENT;
}

"\," {
	return token::COMMA;
}

"\->" {
	return token::ARROW;
}

{SPACE}+ {
	/* ignore space */
}

{SYMBOL} {
	yymore();
	std::cerr << "Unexpected token found when parsing: " << yytext << std::endl;
	return token::INVALID_INPUT;
}

{WORD} {
	yymore();
	std::cerr << "Unknown name when parsing: '" << yytext << '\'' << std::endl;
	return token::INVALID_INPUT;
}

%%
