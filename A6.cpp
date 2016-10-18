#include <iostream>
#include<stdlib.h>
#include<iomanip>
#include<cmath>
#include<time.h>

using namespace std;

class point{

	public:
	float x;
	float y;

	point()
	{
		x=0.0;
		y=0.0;
	}

	point(float a,float b)
	{
		this->x=a;
		this->x=b;
	}
};

class kmeans{
	
	int n,k;
	point *points;
	point *centroids;
	point *old_centroids;
	float** table;
	public:
	kmeans(int,int,point*);
	void execute();
	void displaytable();
	void displaycluster();
	void displaypoints(point* , int);
	float distance(point,point);

};

kmeans::kmeans(int n,int k,point* p)
{
	this->n=n;
	this->k=k;
	this->points=p;
	this->centroids = new point[k];
	this->old_centroids = new point[k];
	this->table = new float*[n];
	for(int i=0;i<n;i++)
		table[i] = new float[k+1];
	
}	

float kmeans::distance(point a,point b)
{
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

void kmeans::displaypoints(point *centroid , int size)
{
	for(int i=0;i<size;i++)
	{
		cout<<"\t ("<<centroid[i].x<<","<<centroid[i].y<<")";
		if(i<size-1)
			cout<<" , ";
	}
}

void kmeans::displaytable()
{
	cout<<"Points \t";
	for(int i=0;i<k;i++)
	{
		cout<<"C"<<i+1<<"\t";

	}
	cout<<"MIN"<<endl;
	
	for(int i=0;i<n;i++)
	{
		cout<<"P"<<i+1<<"\t";
		for(int j=0;j<k;j++)
		{	
			cout<<setprecision(2)<<fixed<<table[i][j]<<"\t";
		}
		cout<<"C"<<setprecision(0)<<fixed<<table[i][k]+1<<"\t";
		cout<<"("<<points[i].x<<","<<points[i].y<<")"<<endl;

	}
	
}

void kmeans::displaycluster()
{
	for(int i=0;i<k;i++)
	{
		cout<<"Cluster "<<i+1<<endl;
		cout<<"Centroid: ";
		cout<<"("<<centroids[i].x<<","<<centroids[i].y<<")"<<endl;
		for(int j=0;j<n;j++)
		{
			if(table[j][k]==i)
			{
				cout<<"("<<points[j].x<<","<<points[j].y<<")"<<endl;
			}
		}

	}

}

void kmeans::execute()
{
	int random=0;
	srand(time(NULL));
	for(int i=0;i<k;i++)
	{
		random= (int)((rand()))%n;
		centroids[i].x=points[random].x;
		centroids[i].y=points[random].y;
	}

	bool flag=false;

	while(!flag)
	{
		cout<<"\n\t";
		displaypoints(centroids,k);
		cout<<"\n";

		for(int i=0;i<n;i++)
		{
			table[i][0] = distance(points[i],centroids[0]);
			int min = table[i][0];
			int min_j = 0;
		
			for(int j=1;j<k;j++)
			{
				table[i][j] = distance(points[i],centroids[j]);
				if(table[i][j]<min)
				{
					min = table[i][j];
					min_j = j;
				}
			}
			table[i][k]=min_j;
		
		}

		displaytable();

		for(int i=0; i<k;i++)
		{
			float sumx=0.0;
			float sumy=0.0;
			int count=0;
			for(int j=0;j<n;j++)
			{
				if(table[j][k]==i)
				{
					count++;
					sumx+=points[j].x;
					sumy+=points[j].y;
				}
			}
			old_centroids[i].x = centroids[i].x;
			old_centroids[i].y = centroids[i].y;
			centroids[i].x = (float)sumx/count;
			centroids[i].y = (float)sumy/count;
		}

		int cen_count;

		for(int i=0;i<k;i++)
		{
			if(old_centroids[i].x==centroids[i].x && old_centroids[i].y==centroids[i].y)
			{
				cen_count++;
			}
 
		}

		if(cen_count==k)
			flag=true;
	}
}


int main()
{
	int n,k;
	cout<<"Enter the number of points: "<<endl;
	cin>>n;
	cout<<"Enter the number of clusters: "<<endl;
	cin>>k;
	point p[n];

	for (int i=0;i<n;i++)
	{
		cout<<"Enter the co-ordinates for point"<<i+1<<":";
		cin>>p[i].x;
		cin>>p[i].y;
	}

	kmeans *obj = new kmeans(n,k,p);
	obj->execute();
	obj->displaycluster();
	return 0;
}

