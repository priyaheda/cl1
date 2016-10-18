%{

#include<stdio.h>
#include<string.h>
int lineno=1;
int cnt=0;
struct st
{
	char name[100];
	int value;
}symbol[5];

int insert(char str[]);


%}

%option noyywrap

%%

[ \t]+		;

"\n"		{lineno++;}

"#"		{printf("%d	",lineno);
		printf("%s	",yytext);
		printf("Preprocessor Directive \n");}

"<"(.)*+\.h">"		{printf("%d	",lineno);
			printf("%s	",yytext);
			printf("Header file \n");}

include|main|for|while|ret|if|else|printf|scanf			{printf("%d	",lineno);
								printf("%s	",yytext);
								printf("Keyword \n");}


int|float|char|double		{printf("%d	",lineno);
				printf("%s	",yytext);
				printf("Keyword \n");}

\+|\-|\*|\/|\=|\<|\>		{printf("%d	",lineno);
			printf("%s	",yytext);
			printf("Operator \n");}	

[a-zA-Z][a-zA-z0-9]*		{printf("%d	",lineno);
				printf("%s	",yytext);
				printf("Identifier \n");
				insert(yytext); }

\"[a-zA-Z][a-zA-z0-9]*\"	{printf("%d	",lineno);
				printf("%s	",yytext);
				printf("String constant \n");}
	
"("|")"|"}"|"{"|";"|","			{printf("%d	",lineno);
				printf("%s	",yytext);
				printf("Delimiter \n");}

\"\%(d|s|u)\"			{printf("%d	",lineno);
				printf("%s	",yytext);
				printf("Format specifier \n");}

"/*"(.|\n)*"*/" 		{printf("%d	",lineno);
				printf("%s	",yytext);
				printf("Comment \n");}


"//"(.)*			{printf("%d	",lineno);
				printf("%s	",yytext);
				printf("Comment \n");}

%%

int main()
{
	char fname[30];
	printf("Enter the name of file \n");
	scanf("%s",fname);
	FILE *fin;
	fin=fopen(fname,"r");
	yyin=fin;	
	yylex();
	for(int i=0;i<cnt;i++)
	{	
		printf("%s	",symbol[i].name);
		printf("%d	",symbol[i].value);
		printf("\n");
	}
	fclose(fin);

}
	
	
int insert(char str[])
{
	int i=0;
	for(int i=0;i<cnt;i++)
	{
		if(strcmp(str,symbol[i].name)==0)
			return i;
	}

	strcpy(symbol[cnt].name,str);
	symbol[cnt].value=0;
	return cnt++;
}
