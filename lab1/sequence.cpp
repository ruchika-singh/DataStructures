#include <iostream>
#include <vector>

int main(){
	
	int values;
	std::cout<<"Enter # of values and sequence"<<std::endl;
	std::cin>>values;
	std::vector<float> seq;
	for (int i = 0; i < values; i++)
	{
		float in;
		std::cin>>in;
		seq.push_back(in);
	}
	float sum = 0;
	float average;
	for(int i = 0; i < values; i++)
		sum += seq[i];
	average = sum/values;
	std::cout<<"Average of sequence is "<<average<<std::endl;
	std::cout<<"Values less than average:"<<std::endl;
	for(int i = 0; i < values; i++)
		if (seq[i]<average)
			std::cout<<seq[i]<<std::endl;
	return 0;
}
