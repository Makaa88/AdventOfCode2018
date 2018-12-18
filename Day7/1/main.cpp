#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#include "Step.h"

struct FindLetter
{

	FindLetter(const char &letter)
	:_letter(letter)
	{

	}

	bool operator()(const Step &step)
	{
		return (_letter == step.getLetter());
	}

private:
	char _letter;
};

bool checkIfAllEmpty(std::set<Step> &set)
{
	bool isEmpty = true;
	for(Step s : set)
	{
		if(s.size() != 0)
		{
			isEmpty = false;
			break;
		}
	}

	return isEmpty;
}

char findEmpty(std::set<Step> &set)
{
	if(checkIfAllEmpty(set))
		return '-';

	for(Step s : set)
	{
		if(s.size() == 0)
			return s.getLetter();
	}
	return '-';
}

void erase(std::set<Step> &set, char sign)
{
	for(std::set<Step>::iterator it = set.begin(); it != set.end(); it++)
	{
		it->erase(sign);
	}

	for(std::set<Step>::iterator it = set.begin(); it != set.end(); it++)
	{
		if(it->getLetter() == sign)
		{
			set.erase(it);
			break;
		}
	}
}

int main()
{
	std::ifstream file;
	file.open("dane.dat",std::ios::in);
	std::set<Step> stepSet;

	while(!file.eof())
	{
		std::string record;
		getline(file,record);
		std::cout<<record<<std::endl;

		char toInsert = record[5];
		char className = record[36];
		std::set<Step>::iterator result = std::find_if(stepSet.begin(), stepSet.end(), FindLetter(className));

		if(result != stepSet.end())
		{
			result->addDependance(toInsert);
		}
		else
		{
			stepSet.insert(Step(className, toInsert));
			stepSet.insert(Step(toInsert));
		}
	}

	std::cout<<std::endl<<std::endl;


	std::cout<<std::endl<<std::endl;
	char start;
	std::vector<char> result;
	while((start = findEmpty(stepSet)) != '-' )
	{

		result.push_back(start);
		erase(stepSet, start);
	}

	start = stepSet.begin()->getLetter();
	result.push_back(start);
	

	for(char c : result)
	{
		std::cout<<c;
	}
	std::cout<<std::endl;



	return 0;
}