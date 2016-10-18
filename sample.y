%{

#include <stdio.h>
extern FILE *yyin;

%}

%start s
%token ID MAIN IF ELSE FOR WHILE OP INC DEC DT NUMBER RELATIONAL
%left '+' '-'
%left '*' '/'

%%
s:	MAIN '('')''{' prog  '}'	{printf("Program is Valid \n");}
	;

prog:	stmtlist prog		
	|	
	;

stmtlist:	stmtlist stmt|;

stmt:	ID'='expr ';'		{printf("Valid statement \n");}
	|ifstmt			{printf("IF statement \n");}	
	|forstmt		{printf("For statement \n");}
	|whilestmt		{printf("While statement \n");}
	|vardeclare ';'		{printf("Variable declaration statement \n");}
	|expr ';'		{printf("Valid statement \n");}
	;

expr:	expr OP expr	{}
	|ID'='expr OP NUMBER 	{}
	|ID			{}
	;

vardeclarelist: vardeclarelist vardeclare|	{}
		;	

vardeclare:	DT ID		{}
		|DT ID'='NUMBER	{}
		|ID'='NUMBER','vardeclarelist	{}
		|ID'='NUMBER		{}
 		|DT ID'='NUMBER','vardeclarelist	{}
		;

ifstmt:	IF'(' condition ')''{' stmtlist '}' ELSE '{' stmtlist '}'	{}
	|IF'(' condition ')''{' stmtlist'}'		{}
	|IF'(' condition ')' stmtlist ELSE stmtlist	{}
	;

forstmt: 	FOR'(' assign ';' condition ';' incdec ')' '{' stmtlist '}'	{}
		|FOR'(' assign ';' condition ';' incdec ')'  stmtlist 	{}
		;

whilestmt:	WHILE'(' condition ')' '{' stmtlist '}'	{}
		;

condition:	expr RELATIONAL expr	{}
		|expr RELATIONAL NUMBER	{}
		;

assign:	DT ID'='NUMBER	{}
	|ID'='NUMBER	{}
	|ID'='expr	{}
	;	

incdec:	ID INC	{}
	|ID DEC	{}
	;

%%

main()
{
	FILE *fin;
	fin=fopen("expressions.txt","r");
	yyin=fin;
	yyparse();
	fclose(fin);

}

int yywrap()
{
return 1;
}

int yyerror()
{
printf("Syntax error \n");
return 1;
}

