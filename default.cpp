#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <algorithm>
using namespace std;

void extract(int hammingCode[],int n,int r)
{
	std::vector<int> red;
	for(int i=0;i<r;i++)
		red.push_back((int)pow(2,i)-1);

	for(int i=0;i<n;i++)
	{
		int flag=1;
		for(int j=0;j<red.size();j++)
			if(i==red[j])
			{
				flag=0; break;
			}
		if(flag==1)
		{
			cout<<hammingCode[i]<<" ";
		}
	}
}


int main()
{
	//data bits
	std::vector<int> data;

	//number of bits to be transmitted
	long long int n;

	clock_t t1,t2;

	t1=clock();

	cout<<"\nenter number of bits to be transmitted:"; 
	cin>>n;
	cout<<"\nenter data to be transmitted:";
	for (int i = 0; i < n ; ++i)
	{
		int x; cin>>x;
		data.push_back(x);
	}

	long long int r;
	while (n + r + 1 > pow (2, r))
    {
      r++;
    }

	int d=0,d1=0;
	int hammingCode[n+r];

	for (int i = 1; i <= (n+r) ; ++i)
	{
		if(i==pow(2,d))
		{
			hammingCode[i-1]=0;
			d++;
		}
		else
		{
			hammingCode[i-1]=data[d1];
			d1++;
		}
	}


	  for(long long int app=0;app<r-1;app++)
	{
	    int p=hammingCode[(long long int)pow(2,app)-1];

	    //xoring first 2^app bits and then skipping next 2^app bits and continuing...
	    for(long long int i=(long long int)pow(2,app)-1;i<n+r;)
	    {
	        for(long long int j=(long long int)pow(2,app)-1;j>0;j--)
	        {
	            i++;
	            if(i<n+r)
	            p^=hammingCode[i];
	        }
	        i+=(long long int)pow(2,app)+1;
	        if(i<n+r)
	        p^=hammingCode[i];
	    }

	    int index=pow(2,app)-1;
	    hammingCode[index]=p;

	}
	cout <<"\nHamming codeword bits with even parity are : ";
	for (int i = 1; i <= n + r; ++i)
	    cout << hammingCode[i-1] << " ";
	
	srand(time(0));

	int noise=(rand()%2);

	//random distortion of data bits...
	if(noise==1)
	{
		//random data bit distorted
		long long int index=(rand()%n);

		if(ceil(log(index))!=log(index))
		{	if(hammingCode[index]==0)
				hammingCode[index]=1;
			else
				hammingCode[index]=0;
		}
	}

	cout<<"\nRecieved code is: ";
	for (int i = 0; i < n + r; ++i)
	    cout << hammingCode[i] << " ";

	std::vector<int> parity;

	for(long long int app=0;app<r;app++)
	{
	    int p=hammingCode[(long long int)pow(2,app)-1];

	    //xoring first 2^app bits and then skipping next 2^app bits and continuing...
	    for(long long int i=(long long int)pow(2,app)-1;i<n+r;)
	    {
	        for(long long int j=(long long int)pow(2,app)-1;j>0;j--)
	        {
	            i++;
	            if(i<n+r)
	            p^=hammingCode[i];
	        }
	        i+=(long long int)pow(2,app)+1;
	        if(i<n+r)
	        p^=hammingCode[i];
	    }

	    	parity.push_back(p);


	}
	   

	cout<<"\nstatus of parity check...";
	std::reverse(parity.begin(),parity.end());
	for(int i=0;i<parity.size();i++)
		cout<<parity[i]<<" ";
	cout<<endl;

	long long int wrongBit=0;
	
	for(long long int i=0;i<parity.size();i++)
		wrongBit+=(long long int)pow(2,i)*parity[i];
	
	wrongBit-=1;

	if(wrongBit>=0)
	{
		cout<<"\nerror found and wrong bit is:"<<wrongBit+1<<endl;
		if(hammingCode[wrongBit]==0)
			hammingCode[wrongBit]=1;
		else
			hammingCode[wrongBit]=0;
	}
	else
		cout<<"\nno error\n";


	cout<<"\ncorrected recieved code is: ";

	extract(hammingCode,n+r,r);

	t2=clock();

	cout << "Time taken: " << (t2 - t1) / (double)CLOCKS_PER_SEC << endl; 

    return 0;
}