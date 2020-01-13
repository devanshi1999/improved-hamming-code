#include "media.h"
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

vector<int> send(std::vector<int> data,long long int n)
{
	
	srand(time(0));

	int noise=(rand()%2);

	//random distortion of data bits...
	if(noise==0)
	{
		//data recieved without any noise

		return data;
	}
	else
	{
		//random data bit distorted
		long long int index=(rand()%n);

		std::reverse(data.begin(),data.end());

		if(data[index]==0)
			data[index]=1;
		else
			data[index]=0;

		std::reverse(data.begin(),data.end());

		//distorted recieved code returned
		return data;
	}

}