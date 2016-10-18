%{
#include<string.h>
#include<stdio.h>
#include "y.tab.h"
%}

%%

[ \t\n]+	;
main	{return MAIN;}
int|float|double|char	{strcpy(yylval.string,yytext);return TYPE;}
[a-zA-Z][a-zA-Z_]*	{strcpy(yylval.string,yytext);return ID;}
[0-9]+ |
[0-9]+\.[0-9]+	{yylval.dval=atof(yytext);
			return NUMBER;}
.	{return yytext[0];}

%%
int yywrap()
{
return 1;
}
