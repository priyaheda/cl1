/* The grammar on which recursive descent parser is implemented
 E->TE'
 E'->+TE'|epsilon
 T->FT'
 T'->*FT'|epsilon
 F->(E) | id		*/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
using namespace std;

int i,error;
char input[20];
void e();
void edash();
void t();
void tdash();
void f();
int match(char , char);
int main()
{
	i=0;
	error=0;
	cout<<"Enter the expression";
	cin>>input;
	e();
	if(strlen(input)==i)
	{
		cout<<"String Accepted";
	}	
	else
	{
		cout<<"NOt accepted";
	}
	return 0;
}

void e()
{
	t();
	edash();
}

void edash()
{
	if(match(input[i],'+'))
	{
		i++;
		t();
		edash();
	}
}

void t()
{
	f();
	tdash();
}

void tdash()
{
	if(match(input[i],'*'))
	{
		i++;
		f();
		tdash();
	}
}

void f()
{
	if(isalnum(input[i]))
	{
		i++;
	}
	else if(match(input[i],'('))
	{
		i++;
		e();
		if(match(input[i],')'))
		{
			i++;
		}
		else
		{
			cout<<"terminating because no close brackets";
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		cout<<"Terminating because no open bracket";
		exit(EXIT_FAILURE);
	}
}

int match(char a, char b)
{
	if(a==b)
		return 1;
	else
		return 0;
}
