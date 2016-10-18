%{
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int temp_var=0;
int sym_cnt=0;
int Index=0;

struct Symbol_table{
	char sym_name[10];
	char sym_type[10];
	double value;
	}Sym[10];

struct Quadruple{
	char op[5];
	char op1[10];
	char op2[10];
	char result[10];
	}quad[25];

struct Stack{
	char *items[10];
	int top;
	}Stk;

int search_symbol(char[]);
void make_symtab_entry(char[],char[],double);
void display_symtab();
void add_quadruple(char[],char[],char[],char[]);
void display_quadruple();
void push(char*);
char* pop();


%}

%union{
	int ival;
	double dval;
	char string[10];
	}

%token <string> ID
%token <string> TYPE
%token MAIN
%token <dval> NUMBER
%type <string> varlist
%type <string> expr	
%left '+' '-'
%left '/' '*'

%%

program:MAIN'('')''{' body '}'	
	;

body: varstmt stmtlist
	;

varstmt: vardecl varstmt|;

vardecl: TYPE varlist';' ;

varlist: varlist ',' ID		{
					
					int i=search_symbol($3);
					if(i!= -1)
						printf("No Multiple Declaration");
					
					else
					{
						make_symtab_entry($3,$<string>0,0);
					}

				}

	|ID'='NUMBER		{
					
					int i=search_symbol($1);
					if(i!= -1)
						printf("No Multiple Declaration");
					
					else
					{
						make_symtab_entry($1,$<string>0,$3);
					}

				}

	|varlist ',' ID'='NUMBER	{
					
					int i=search_symbol($3);
					if(i!= -1)
						printf("No Multiple Declaration");
					
					else
					{
						make_symtab_entry($3,$<string>0,$5);
					}

					}

	|ID				{
				
					int i=search_symbol($1);
					if(i!= -1)
						printf("No Multiple Declaration");
					
					else
					{
						make_symtab_entry($1,$<string>0,0);
					}

					}
	;

stmtlist: stmt stmtlist |;


stmt:	ID'='NUMBER ';'	{	int i=search_symbol($1);
				if(i==-1)
					printf("Undefined variable");

				else
				{
					char temp[10];
					if(strcmp(Sym[i].sym_type,"int")==0)
						sprintf(temp,"%d",(int)$3);

					else
						snprintf(temp,10,"%f",$3);

					add_quadruple("=","",temp,$1);
				}
					
			}

	|ID'='ID ';'	{	int i=search_symbol($1);
				int j=search_symbol($3);
				if(i==-1 || j==-1)
					printf("Undefined variable");

				else
					add_quadruple("=","",$3,$1);	
			}
	
	|ID'='expr ';'	{
				int i=search_symbol($1);
				if(i==-1)
					printf("Undefined variable");
				else
					add_quadruple("=","",pop(),$1);	
			}
			;

expr: expr'+'expr 	{	char str[5],str1[5]="t";
				sprintf(str,"%d",temp_var);
				strcat(str1,str);
				add_quadruple("+",pop(),pop(),str1);
				push(str1);
			}

	|expr'-'expr 	{	char str[5],str1[5]="t";
				sprintf(str,"%d",temp_var);
				strcat(str1,str);
				add_quadruple("-",pop(),pop(),str1);
				push(str1);
			}

	|expr'*'expr 	{	char str[5],str1[5]="t";
				sprintf(str,"%d",temp_var);
				strcat(str1,str);
				add_quadruple("*",pop(),pop(),str1);
				push(str1);
			}

	|expr'/'expr	{	char str[5],str1[5]="t";
				sprintf(str,"%d",temp_var);
				strcat(str1,str);
				add_quadruple("/",pop(),pop(),str1);
				push(str1);
			}

	|ID		{
				int i=search_symbol($1);
				if(i==-1)
					printf("Undefined variable");
				else
					push($1);

			}
	
	|NUMBER 	{
				char temp[10];
				snprintf(temp,10,"%f",$1);
				push(temp);

			}
	;


%%

extern FILE *yyin;

int main()
{
	Stk.top=-1;
	yyin=fopen("input.txt","r");
	yyparse();
	display_symtab();
	printf("\n\n");
	display_quadruple();
	printf("\n\n");
	return 0;
}

int search_symbol(char sym[10])
{
	int i,flag=0;
	for(int i=0;i<sym_cnt;i++)
	{	
		if(strcmp(Sym[i].sym_name,sym)==0)
		{
			flag=1;
			break;
		}
	}
	if(flag==0)
		return -1;

	else
		return i;
	
}

void make_symtab_entry(char name[10],char type[10],double value)
{
	strcpy(Sym[sym_cnt].sym_name,name);
	strcpy(Sym[sym_cnt].sym_type,type);
	Sym[sym_cnt].value=value;
	sym_cnt++;

}

void add_quadruple(char op[10],char op2[10],char op1[10],char res[10]){
                                        strcpy(quad[Index].op,op);
                                        strcpy(quad[Index].op2,op2);
                                        strcpy(quad[Index].op1,op1);
                                        strcpy(quad[Index].result,res);
                    Index++;
}

void push(char* str)
{
	Stk.top++;
	Stk.items[Stk.top]=(char*)malloc(strlen(str)+1);
	strcpy(Stk.items[Stk.top],str);
}

char* pop()
{
	if(Stk.top==-1)
		printf("Empty Stack");

	else
	{
	char *str=(char*)malloc(strlen(Stk.items[Stk.top])+1);
	strcpy(str,Stk.items[Stk.top]);
	Stk.top--;
	return str;
	}
}

void display_symtab()
{
  int i;
  printf("\n\n The Symbol Table  \n\n");
  printf(" Name   Type    Value");
  for(i=0;i<sym_cnt;i++)
    printf("\n %s       %s          %f",Sym[i].sym_name,Sym[i].sym_type,Sym[i].value);
}
void display_quadruple()
{
  int i;
  printf("\n\n The INTERMEDIATE CODE Is : \n\n");
  printf("\n\n The Quadruple Table \n\n");
  printf("\n     Result  Operator  Operand1  Operand2  ");
  for(i=0;i<Index;i++)
    printf("\n %d     %s          %s          %s          %s",i,quad[i].result,quad[i].op,quad[i].op1,quad[i].op2);
}
int yyerror()
{
   printf("\nERROR!!\n");
   return(1);
}

