%{
#include "y.tab.h"

%}

%%

[ \t\n]+	;
main		{return MAIN;}
if		{return IF;}
else		{return ELSE;}
for		{return FOR;}
while		{return WHILE;}
\*|\+|\-|\/	{return OP;}
\+\+		{return INC;}
\-\-		{return DEC;}
int|float|double|long|short|void		{return DT;}
[0-9]+		{return NUMBER;}
[a-zA-z][a-zA-Z0-9]*	{return ID;}
\<|\>|\<\=|\>\=|\=\=	{return RELATIONAL;}
.		{return yytext[0];}

%%
