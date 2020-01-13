#include "reciever.h"
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>
using namespace std;

int errorDetection(std::vector<int> data,long long int n)
{
	std::reverse(data.begin(),data.end());

	std::vector<int> redundancyBits;

	long long int redundancyBitIndex=n;

	long long int r=ceil(log(2*n+2)/log(2));

	for(long long int app=0;app<r-1;app++)
	{
	    int p=data[(long long int)pow(2,app)-1];

	    for(long long int i=(long long int)pow(2,app)-1;i<n;)
	    {
	        for(long long int j=(long long int)pow(2,app)-1;j>0;j--)
	        {
	            i++;
	            if(i<n)
	            p^=data[i];
	        }
	        i+=(long long int)pow(2,app)+1;
	        if(i<n)
	        p^=data[i];
	    }

	    p^=data[redundancyBitIndex++];

	    redundancyBits.push_back(p);
	}

	int last=data[n];
	for(long long int i=n+1;i<data.size();i++)
		last^=data[i];

	redundancyBits.push_back(last);

	cout<<"\nstatus of parity check...";
	std::reverse(redundancyBits.begin(),redundancyBits.end());
	for(int i=0;i<redundancyBits.size();i++)
		cout<<redundancyBits[i]<<" ";
	cout<<endl;

	std::reverse(redundancyBits.begin(),redundancyBits.end());
	long long int wrongBit=0;

	for(long long int i=0;i<redundancyBits.size();i++)
		wrongBit+=(long long int)pow(2,i)*redundancyBits[i];
	wrongBit-=1;

	

	if(wrongBit>=0)
	{
		cout<<"\nwrong bit is:"<<wrongBit+1<<endl;
		return 1;
	}	
	
	else
		return 0;

}

std::vector<int> errorCorrection(std::vector<int> data,long long int n)
{
	std::reverse(data.begin(),data.end());

	std::vector<int> redundancyBits;

	long long int redundancyBitIndex=n;

	long long int r=ceil(log(2*n+2)/log(2));

	for(long long int app=0;app<r-1;app++)
	{
	    int p=data[(long long int)pow(2,app)-1];

	    for(long long int i=(long long int)pow(2,app)-1;i<n;)
	    {
	        for(long long int j=(long long int)pow(2,app)-1;j>0;j--)
	        {
	            i++;
	            if(i<n)
	            p^=data[i];
	        }
	        i+=(long long int)pow(2,app)+1;
	        if(i<n)
	        p^=data[i];
	    }

	    p^=data[redundancyBitIndex++];

	    redundancyBits.push_back(p);
	}

	int last=data[n];
	for(long long int i=n+1;i<data.size();i++)
		last^=data[i];

	redundancyBits.push_back(last);

	long long int wrongBit=0;

	for(long long int i=0;i<redundancyBits.size();i++)
		wrongBit+=(long long int)pow(2,i)*redundancyBits[i];
	
	wrongBit-=1;

	if(wrongBit>=0)
	{
		if(data[wrongBit]==0)
			data[wrongBit]=1;
		else
			data[wrongBit]=0;
	}

	while(data.size()>n)
		data.pop_back();

	std::reverse(data.begin(),data.end());

	return data;

}
