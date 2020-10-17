%{
#include <stdio.h>
#include <string.h>
#include "expression.h"
#include "lexer.h"

#define YYERROR_VERBOSE 1

void yyerror(const char *str)
{
    fprintf(stderr, "Parse error: %s\n", str);
}
int yywrap()
{
    return 1;
}

extern node_t *zfilter;

%}

%union {
    char *string_literal;
    struct node *expr;
}

%token '(' ')' '!' T_AND T_OR T_NOT
%token <string_literal> T_FIELD
%token T_EQ T_CT T_IN T_LT T_LE T_GT T_GE T_NE

%left T_OR
%left T_AND
%left T_NOT

%type <expr> filter
%type <expr> string_filter
%type <expr> filter_expr

%%

expression: filter_expr
	{
		zfilter = $1;
	}


filter_expr:
	filter_expr T_OR filter_expr
		{
			$$ = make_op_node(OR);
			$$->left_child = $1;
			$$->right_child = $3;
		}
	| filter_expr T_AND filter_expr
		{
			$$ = make_op_node(AND);
			$$->left_child = $1;
			$$->right_child = $3;
		}
	| '(' filter_expr ')'
		{
			$$ = $2;
		}
	| '!' '(' filter_expr ')'
		{
			not_node($3);
			$$ = $3;
		}
	| T_NOT '(' filter_expr ')'
		{
			not_node($3);
			$$ = $3;
		}
	| filter
		{
			$$ = $1;
		}
	| '!' filter
		{
			not_node($2);
			$$ = $2;
		}
	| T_NOT filter
		{
			not_node($2);
			$$ = $2;
		}
	;

filter: string_filter
		{
			$$ = $1;
		}
	;

string_filter:
	T_FIELD T_EQ T_FIELD
		{
			$$ = make_op_node(EQ);
			$$->left_child = make_left_node($1);
			$$->right_child = make_right_node($3);
		}
	|
	T_FIELD T_NE T_FIELD
		{
			$$ = make_op_node(NE);
			$$->left_child = make_left_node($1);
			$$->right_child = make_right_node($3);
		}
	|
	T_FIELD T_CT T_FIELD
		{
			$$ = make_op_node(CT);
			$$->left_child = make_left_node($1);
			$$->right_child = make_right_node($3);
		}
	|
	T_FIELD T_IN T_FIELD
		{
			$$ = make_op_node(IN);
			$$->left_child = make_left_node($1);
			$$->right_child = make_right_node($3);
		}
	|
	T_FIELD T_LT T_FIELD
		{
			$$ = make_op_node(LT);
			$$->left_child = make_left_node($1);
			$$->right_child = make_right_node($3);
		}
	|
	T_FIELD T_LE T_FIELD
		{
			$$ = make_op_node(LE);
			$$->left_child = make_left_node($1);
			$$->right_child = make_right_node($3);
		}
	|
	T_FIELD T_GT T_FIELD
		{
			$$ = make_op_node(GT);
			$$->left_child = make_left_node($1);
			$$->right_child = make_right_node($3);
		}
	|
	T_FIELD T_GE T_FIELD
		{
			$$ = make_op_node(GE);
			$$->left_child = make_left_node($1);
			$$->right_child = make_right_node($3);
		}
	;

%%
