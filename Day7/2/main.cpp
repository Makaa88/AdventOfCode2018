#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Worker.h"
#include "Step.h"

int seconds = 0;

struct FindLetter //funktor
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

std::vector<char> findEmpty(std::set<Step> &set)
{
	std::vector<char> emptyLetter;
	//std::cout<< emptyLetter.size() << std::endl;
	if(checkIfAllEmpty(set))
		{
			for(const Step &s : set)
			{
				emptyLetter.push_back(s.getLetter());
			}
			return emptyLetter;
		}

	for(const Step &s : set)
	{
		if(s.size() == 0)
		{
			//return s.getLetter();
			emptyLetter.push_back(s.getLetter());
		}
	}
	/*for(char &c : emptyLetter)
	{
		std::cout<< c << " ";
	}*/

	//std::cout<<std::endl;
	return emptyLetter;
}

void erase(std::set<Step> &set, const char &sign)
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

void showDependeces(std::set<Step> &step)
{
	for(const Step &s : step)
	{
		std::cout << s;
	}
}


void goToWork(std::vector<Worker> &workers, std::vector<char> &letters,std::set<char> &workedLetters)
{
	unsigned j = 0;
	for(unsigned i = 0; i < workers.size(); i++)
	{
		
		std::set<char>::iterator it = workedLetters.find(letters[j]);

		if(workers[i].isWorking()) continue;
		while(it != workedLetters.end() && j < letters.size())
		{
			j++;
			it = workedLetters.find(letters[j]);
		}
		
		if(j == letters.size()) break;
		workers[i].startWork(letters[j]);
		workedLetters.insert(letters[j]);
	
		j++;
	}
}

void addSecond(std::vector<Worker> &workers)
{
	//std::cout<<"IN addSecond\n";
	for(Worker &w : workers)
	{
		if(w.isWorking())
			w.addSecond();
	}
}

void eraseIfEnd(std::set<Step> &stepSet, std::vector<Worker> &workers, std::vector<char> &result)
{
	/*std::cout<<seconds <<"\t   ";
	if(workers[0].isWorking()) std::cout << workers[0].getWorkingLetter()<<"\t";
	else std::cout<<"-\t";
	if(workers[1].isWorking()) std::cout << workers[1].getWorkingLetter()<<"\t";
	else std::cout<<"-\t";
	if(workers[2].isWorking()) std::cout << workers[2].getWorkingLetter()<<"\t";
	else std::cout<<"-\t";
	if(workers[3].isWorking()) std::cout << workers[3].getWorkingLetter()<<"\t";
	else std::cout<<"-\t";
	if(workers[4].isWorking()) std::cout << workers[4].getWorkingLetter()<<"\t";
	else std::cout<<"-\t";
	std::cout<<std::endl;*/
	
	for(Worker &w : workers)
	{
		std::vector<char>::iterator it = std::find(result.begin(), result.end(), w.getWorkingLetter());
		if(w.isFinish() && w.getWorkingLetter() != '-' && it == result.end())
		{
			erase(stepSet, w.getWorkingLetter());
			result.push_back(w.getWorkingLetter());
			
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
	showDependeces(stepSet);

	std::cout<<std::endl<<std::endl;
	std::vector<char> start;
	std::vector<char> result;
	std::vector<Worker> workers(5, Worker());
	std::set<char> workedLetters;
	while(stepSet.size())
	{

		start = findEmpty(stepSet);

		goToWork(workers, start, workedLetters);
		addSecond(workers);
		eraseIfEnd(stepSet,workers,result);
		seconds++;
	}

	

	for(char c : result)
	{
		std::cout<<c;
	}
	std::cout<<"//"<<std::endl;
	std::cout<< seconds << std::endl;



	return 0;
}