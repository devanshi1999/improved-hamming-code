#include "sender.h"
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>
using namespace std;

vector<int> createHammingCode(std::vector<int> data,long long int n)
{
	long long int r;
	int last;

	//number of redundancy bits
	r=ceil(log(2*n+2)/log(2));

	cout<<"\nnumber of redundancy bits added are: "<<r<<"\n\n";

	//so that lsb gets 0 index
	std::reverse(data.begin(),data.end());

	//bits to be appended at end
	for(long long int app=0;app<r-1;app++)
	{
	    int p=data[(long long int)pow(2,app)-1];

	    //xoring first 2^app bits and then skipping next 2^app bits and continuing...
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

	    //redumdancy bit appended at end
	    data.push_back(p);

	    //calculation of last redundancy bit
	    if(app==0)
	    	last=p;
	    else
	    	last^=p;
	}

	//last redundancy bit which is pr = p1^p2^p3.....^pr-1
	data.push_back(last);

	//to get data and redundancy in original order
	std::reverse(data.begin(),data.end());

	//return hamming code
	return data;
	
}
