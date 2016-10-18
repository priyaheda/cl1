#include <iostream>
#include<pthread.h>
using namespace std;

int k=0;
pthread_t threads[1000];

struct args{
 	int left;
	int right;
	int *arr;
	int tid;
};

int partition(int *arr,int left,int right)
{
	int i=left;
	int j=right;
	int pivot=arr[left];
	while(i<j)
	{
		while(arr[i]<=pivot && i<=right)
			i++;
	
		while(arr[j]>pivot)
			j--;

		if(i<j)	
		{
			int temp=arr[i];
			arr[i]=arr[j];
			arr[j]=temp;
		}
	}

	arr[left]=arr[j];
	arr[j]=pivot;
	return j;
}

void* quicksort(void* arguments)
{
	struct args* arg= (struct args *) arguments;
	int left=arg->left;
	int right=arg->right;
	int *arr=arg->arr;
	int tid=arg->tid;
	int m;

	if(left<right)
	{
		m=partition(arr,left,right);
		cout<<"Placed at position "<<m<<" by thread "<<tid<<"\n";
		k++;
	
		struct args* arg1= new args();
		arg1->left=left;
		arg1->right=m-1;
		arg1->arr=arr;
		arg1->tid=2*arg->tid;


		struct args* arg2= new args();
		arg2->left=m+1;
		arg2->right=right;
		arg2->arr=arr;
		arg2->tid=2*arg->tid+1;

		pthread_create(&threads[arg1->tid],NULL,quicksort,(void *)arg1);
		pthread_create(&threads[arg2->tid],NULL,quicksort,(void *)arg2);
		pthread_join(threads[arg2->tid],NULL);
		pthread_join(threads[arg1->tid],NULL);

	}
}

int main()
{
	int n;
	int arr[100];
	cout<<"Enter the number of elements \n";
	cin>>n;

	cout<<"Enter the elements of the array \n";
	for(int i=0;i<n;i++)
		cin>>arr[i];

	struct args* arg=new args();
	arg->left=0;
	arg->right=n-1;
	arg->arr=arr;
	arg->tid=0;

	pthread_create(&threads[arg->tid],NULL,quicksort,(void *)arg);
	pthread_join(threads[arg->tid],NULL);

	cout<<"The sorted array is: \n";
	for(int i=0;i<n;i++)
		cout<<arr[i]<<"\n";

	cout<<"The total number of threads are: "<<k<<endl;
	return 0;
}

