#include <iostream>
#include <omp.h>
using namespace std;

class dynamic{
	int c[5][5];
	int d[24];
	int p[24][6];
	int list[5];
	int n;
	int r;

public:

	dynamic();
	void getdata();
	void display();
	void sol();
	int fact(int);
	int min(int list[]);
	void perm(int list[],int k,int m);
};

dynamic::dynamic()
{
	r=0;

}

void dynamic::getdata()
{
	int i,j;
	cout<<"Enter the number of cities: \n";
	cin>>n;

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			c[i][j]=0;
		}
	}

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(i!=j)
			{
				if(c[i][j]==0)
				{
					cout<<"Enter the distance from "<<i<<" to "<<j<<"\n";
					cin>>c[i][j];
					c[j][i]=c[i][j];
				}
			}
		}
	}

	for (int i=0;i<n-1;i++)
		list[i]=i+1;
}

int dynamic::fact(int num)
{
	int f=1;
	if(num!=0)
		for(int i=1;i<=num;i++)
			f=f*i;

	return f;
}

int dynamic::min(int list[])
{
	int minimum=list[0];
	for(int i=0;i<fact(n-1);i++)
	{
		if(list[i]<minimum)
			minimum=list[i];
	}
	return minimum;
}

void dynamic::sol()
{
	int i,temp;
	#pragma openmp parallel
	perm(list,0,n-2);
	for(i=0;i<fact(n-1);i++)
	{
		p[i][0]=0;
		p[i][n]=0;
	}

	for(int i=0;i<fact(n-1);i++)
	{
		d[i]=0;
		for(int j=0;j<n;j++)
		{
			d[i]=d[i]+c[p[i][j]][p[i][j+1]];
		}
	}
}


void dynamic::perm(int list[],int k,int m)
{
	int i,temp;
	if(k==m)
	{
		for(int i=0;i<=m;i++)
		{
			p[r][i+1]=list[i];
		}
		r++;
	}

	else
	{
		for(int i=k;i<=m;i++)
		{
			temp=list[i];
			list[i]=list[k];
			list[k]=temp;
			perm(list,k+1,m);
			temp=list[i];
			list[i]=list[k];
			list[k]=temp;

		}
	}
}


void dynamic::display()
{
	cout<<"The cost matrix is: \n";
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<c[i][j]<<"\t";
		}

		cout<<"\n";
	}

	cout<<"The possible paths are: \n";
	for(int i=0;i<fact(n-1);i++)
	{
		for(int j=0;j<=n;j++)
		{
			cout<<p[i][j]<<"\t";
		}
		cout<<"--->"<<d[i]<<endl;
	}

	for(i=0;i<fact(n-1);i++)
	{
		if(d[i]==min(d))
			break;
	}

	cout<<"\n The shortest path is: ";

	for(int j=0;j<=n;j++)
		cout<<p[i][j]<<"\t";

	cout<<"\n The minimum cost is:	"<<d[i]<<endl;
}

int main()
{
	dynamic ts;
	ts.getdata();
	ts.sol();
	ts.display();
	return 0;
}
