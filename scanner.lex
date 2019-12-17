%{

/* Declarations section */
#include <stdio.h>
#include "parser.tab.hpp"
#include "structs.h"
char *ptr;
%}

%option yylineno
%option noyywrap
whitespace		([\t\n\r ])

%%

void                        return VOID;
int                         return INT;
byte                        return BYTE;
b                           return B;
bool                        return BOOL;
enum                        return ENUM;
and                         return AND;
or                          return OR;
not                         return NOT;
true                        {
                                yylval boolean = true;
                                return TRUE;
                            }
false                       {
                                yylval boolean = false;
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
                                if (yytext = "==")
                                    yylval.str = "==";
                                else
                                    yylval.str = '!=';
                                return EQUALITY;
                            }
\<|<=                       {
                                if (yytext = "<=")
                                    yylval.str = "<=";
                                else
                                    yylval.str = '<';
                                return LHSS;
                            }
>=|>                        {
                                if (yytext = ">=")
                                    yylval.str = ">=";
                                else
                                    yylval.str = '>';
                                return RHSS;
                            }
\+|\-                       {
                                if (yytext = "+")
                                    yylval.str = "+";
                                else
                                    yylval.str = "-";
                                return ADDITIVE;
                            }
\*|"/"                      {
                                if (yytext = "*")
                                    yylval.singlechar = '*';
                                else
                                    yylval.singlechar = '/';
                                return MUL;
                            }
[a-zA-Z][a-zA-Z0-9]*	    {
                                yylval.str = yytext;
                                return ID;
                            }
0|[1-9][0-9]*			    {
                                yylval.integer = strtol(yytext, &ptr, 10);
                                return NUM;
                            }
"//"[^{\n|\r|\n\r}]*        ;
\"([^\n\r\"\\]|\\[rnt\"\\])+\" {
                                   yylval.str = yytext;
                                   return STRING;
                               }
{whitespace}				;
.                           yylval = 1;
%%
