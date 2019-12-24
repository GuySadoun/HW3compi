%{
/* Declarations section */
#include <stdio.h>
#include "parser.tab.hpp"
#include "structs.h"
char *ptr;
YYSTYPE yylex;
%}

%option yylineno
%option noyywrap
whitespace		([\t\n\r ])

%%

void                        return TVOID;
int                         return TINT;
byte                        return TBYTE;
b                           return B;
bool                        return TBOOL;
enum                        return TENUM;
and                         return AND;
or                          return OR;
not                         return NOT;
true                        {
                                yylex.boolean = true;
                                return TRUE;
                            }
false                       {
                                yylex.boolean = false;
                                return FALSE;
                            }
return                      return RETURN;
if                          return IF;
else                        return ELSE;
while                       return WHILE;
break                       return BREAK;
continue                    return CONTINUE;
;                           return SC;
","                         return COMMA;
"("                         return LPAREN;
")"                         return RPAREN;
"{"                         return LBRACE;
"}"                         return RBRACE;
"="                         return ASSIGN;
==|!=                       {
                                if (yytext == "==")
                                    yylex.str = "==";
                                else
                                    yylex.str = "!=";
                                return EQUALITY;
                            }
\<|<=                       {
                                if (yytext == "<=")
                                    yylex.str = "<=";
                                else
                                    yylex.str = "<";
                                return LHSS;
                            }
>=|>                        {
                                if (yytext == ">=")
                                    yylex.str = ">=";
                                else
                                    yylex.str = ">";
                                return RHSS;
                            }
\+|\-                       {
                                if (yytext == "+")
                                    yylex.str = "+";
                                else
                                    yylex.str = "-";
                                return ADDITIVE;
                            }
\*|"/"                      {
                                if (yytext == "*")
                                    yylex.str = "*";
                                else
                                    yylex.str = "/";
                                return MUL;
                            }
[a-zA-Z][a-zA-Z0-9]*	    {
                                yylex.str = yytext;
                                return ID;
                            }
0|[1-9][0-9]*			    {
                                yylex.integer = strtol(yytext, &ptr, 10);
                                return NUM;
                            }
"//"[^{\n|\r|\n\r}]*        ;
\"([^\n\r\"\\]|\\[rnt\"\\])+\" {
                                   yylex.str = yytext;
                                   return TSTRING;
                               }
{whitespace}				;
.                           {
                                errorLex(yylineno);
                                exit(1);
                            }
%%
