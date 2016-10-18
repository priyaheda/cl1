#include <iostream>
#include <stdlib.h>
using namespace std;

struct bin_tree
{
	/* data */
	int label;
	char data;
	struct bin_tree *right,*left;
};

typedef bin_tree node;

class labelledtree
{
	int R[10];
	int top;
	char *op;
public:

void initializestack(node *root)
{
	top = root->label-1;
	int temp = top;
	for(int i=0;i<=top;i++)
	{
		R[i] = temp;
		temp--;
	}
}

void insertnode(node **tree,char val)
{
	node *temp = NULL;
	if(!(*tree))
	{
		temp = (node *)malloc(sizeof(node));
		temp->left = temp->right = NULL;
		temp->label = -1;
		temp->data = val;
		*tree = temp;
	}
}
 
void insert(node **tree,char val)
{
	char l,r;
	int numofchildren;

	insertnode(tree,val);
	cout<<"Enter the number of children of "<<val<<"\n";
	cin>>numofchildren;

	if(numofchildren==2)
	{
		cout<<"Enter the left child of "<<val<<"\n";
		cin>>l;
		insertnode(&(*tree)->left,l);

		cout<<"Enter the right child of "<<val<<"\n";
		cin>>r;
		insertnode(&(*tree)->right,r);

		insert(&(*tree)->left,l);
		insert(&(*tree)->right,r);


	}
}

void swap()
{
	int temp;
	temp=R[0];
	R[0]=R[1];
	R[1]=temp;
}

int pop()
{
	int temp=R[top];
	top--;
	return temp;
}

void push(int temp)
{
	top++;
	R[top]=temp;
}

void print_inorder(node *tree)
{
	if(tree)
	{
	print_inorder(tree->left);
	cout<<tree->data<<" with labe: "<<tree->label<<"\n";
	print_inorder(tree->right);
	}
}

void nameofoperation(char temp)
{
	switch(temp)
	{
		case '+':	op=(char *)"ADD";
					break;

		case '-':	op=(char *)"SUB";
					break;

		case '*':	op=(char *)"MUL";
					break;

        case '/':	op=(char *)"DIV";
					break;
	}
}

void deltree(node *tree)
{
	if(tree)
	{
	deltree(tree->left);
	deltree(tree->right);
	free(tree);
	}
}

void findleafnodelabel(node *tree,int val)
{
	if(tree->left!=NULL && tree->right!=NULL)
	{
		findleafnodelabel(tree->left,1);
		findleafnodelabel(tree->right,0);
	}

	else
	{
		tree->label = val;
	}
}

void findinteriornodelabel(node *tree)
{
	if(tree->left->label==-1)
	{
		findinteriornodelabel(tree->left);
	}

	else if(tree->right->label == -1)
	{
		findinteriornodelabel(tree->right);
	}

	else
	{
		if(tree->left!=NULL && tree->right!=NULL)
		{
			if(tree->left->label == tree->right->label)
				tree->label=(tree->left->label)+1;

			else
			{
				if(tree->left->label > tree->right->label)
					tree->label=(tree->left->label);

				else
					tree->label=(tree->right->label);


			}
		}
	}
}

void gencode(node *tree)
{

	if(tree->left!=NULL && tree->right!=NULL)
	{
		if(tree->left->label ==1 && tree->right->label == 0)
		{
			cout<<"MOV R["<<R[top]<<"],"<<tree->left->data<<"\n";
			nameofoperation(tree->data);
			cout<<op<<" R["<<R[top]<<"],"<<tree->right->data<<"\n";
		}

		else if(tree->left->label>=1 && tree->right->label == 0)
		{
			gencode(tree->left);
			nameofoperation(tree->data);
			cout<<op<<" R["<<R[top]<<"],"<<tree->right->data<<"\n";

		}

		else if(tree->left->label < tree->right->label)
		{
			int temp;
			swap();
			gencode(tree->right);
			temp=pop();
			gencode(tree->left);
			push(temp);
			swap();
			nameofoperation(tree->data);
			cout<<op<<" R["<<R[top-1]<<"],R["<<R[top]<<"]"<<"\n";
		}

		else if(tree->left->label >= tree->right->label)
		{
			int temp;
			gencode(tree->left);
			temp=pop();
			gencode(tree->right);
			push(temp);
			nameofoperation(tree->data);
			cout<<op<<" R["<<R[top-1]<<"],R["<<R[top]<<"]"<<"\n";
		}
	}

	else if(tree->left==NULL && tree->right==NULL && tree->label==1)
	{
		cout<<"MOV R["<<R[top]<<"],"<<tree->data<<"\n";
	}
}
};

int main()
{
	node *root;
	root=NULL;
	char val;
	labelledtree d;
	cout<<"Enter the value of root node \n";
	cin>>val;

	d.insert(&root,val);
	d.findleafnodelabel(root,1);

	while(root->label == -1)
		d.findinteriornodelabel(root);

	d.initializestack(root);
	cout<<"Inorder Display \n";
	d.print_inorder(root);
	cout<<"\n";
	cout<<"Assembly code: \n";
	d.gencode(root);
	cout<<"\n";
	d.deltree(root);
    
    }