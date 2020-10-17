%{
#include <string.h>
#include "parser.h"
%}

%%
\n                              /* ignore end of line */
[ \t]+                          /* ignore whitespace */
"&&"                            return T_AND;
"and"                            return T_AND;
"||"                            return T_OR;
"or"                            return T_OR;
"=="                            return T_EQ;
"eq"                            return T_EQ;
"^^"                            return T_CT;
"in"                            return T_IN;
"("                             return '(';
")"                             return ')';
">="                            return T_GE;
"ge"                            return T_GE;
">"                             return T_GT;
"gt"                             return T_GT;
"<="                            return T_LE;
"le"                            return T_LE;
"<"                             return T_LT;
"lt"                             return T_LT;
"!="                            return T_NE;
"not"                           return T_NOT;
"!"                             return T_NOT;
[a-zA-Z0-9][a-zA-Z0-9]*            yylval.string_literal = strdup(yytext); return T_FIELD;
%%

