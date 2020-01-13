#include <iostream>
#include <vector>
#include <time.h>
#include "sender.h"
#include "media.h"
#include "reciever.h"
using namespace std;

int main()
{
	//data bits
	std::vector<int> data;

	//to store hamming code
	std::vector<int> hammingCode;

	//number of bits to be transmitted
	long long int n;

	cout<<"\nenter number of bits to be transmitted:"; 
	cin>>n;
	cout<<"\nenter data to be transmitted:";
	for (int i = 0; i < n ; ++i)
	{
		int x; cin>>x;
		data.push_back(x);
	}

	clock_t t1,t2;

	t1=clock();

	cout<<"\nCorresponding Hamming code created...\n";

	//converting data input to hamming code to be sent to reciever
	hammingCode = createHammingCode(data,n);

	for(int i=0;i<hammingCode.size();i++)
		cout<<hammingCode[i]<<" ";
	cout<<endl;

	//recieved code
	std::vector<int> recievedCode;

	cout<<"\nRecieved Data...";

	//sending...
	recievedCode = send(hammingCode,n);

	for(int i=recievedCode.size()-n;i<recievedCode.size();i++)
		cout<<recievedCode[i]<<" ";
	cout<<endl;


	if(errorDetection(recievedCode,n))
	{
		cout<<"\nData was distorted during tranmission\n";
		std::vector<int> correctedCode;

		cout<<"\nCorrected recieved data...\n";
		correctedCode = errorCorrection(recievedCode,n);

		for(int i=0;i<correctedCode.size();i++)
			cout<<correctedCode[i]<<" ";
		cout<<endl;
	}
	else
	{
		cout<<"\nData was not distorted during tranmission\n";

	}
	t2=clock();

	cout << "Time taken: " << (t2 - t1) / (double)CLOCKS_PER_SEC << endl; 
	return 0;
}