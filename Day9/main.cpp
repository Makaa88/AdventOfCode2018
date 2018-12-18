#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>

constexpr long long lastMarbleWorth = 25;
constexpr long long numberOfPlayers = 9;

/*long long FindValue(std::vector<long long> &marbles, std:vector<long long>::iterator &it)
{
	long long idx = -1;
	for(std::vector<long long>::iterator i = marbles.begin(); i != marbles.end(); i++)
	{
		if
	}
}*/

void Print(const std::list<long long> &marbles)
{
	for(const long long &m : marbles)
	{
		std::cout<<m<<" ";
	}

	std::cout<<std::endl;
}


int main()
{
	std::list<long long> marbles;
	marbles.push_front(0);
	long long players[numberOfPlayers] = {0};
	long long currentPlayer = 0;
	long long currentMarble = 0;
	std::list<long long>::iterator it = marbles.begin();

	long long winningPlayerIndex = 0;


	for(long long i = 1; i <= lastMarbleWorth; i++)
	{
		if(marbles.size() == 1)
		{
			marbles.push_back(i);
			currentMarble = 1;
		}
		else
		{
			if(i%23 == 0)
			{	
				for(long long j = 0; j < 7; j++)
				{
					if(it == marbles.begin())
					{
						it= marbles.end();
						//it++;
					}
					it--;
				}
				players[currentPlayer] += *it + i;
				it = marbles.erase(it);
			}
			else
			{
				for(long long j = 0; j < 2; j++)
				{
					it++;
					if(it == marbles.end())
					{
						it = marbles.begin();
					}
				}
				marbles.insert(it,i);
				it--;

			}
		}
		//Print(marbles);
		currentPlayer++;
		if(currentPlayer == numberOfPlayers)
			currentPlayer = 0;
	}
	for(long long i = 0; i < numberOfPlayers; i++)
	{
		if(players[i] > players[winningPlayerIndex])
			winningPlayerIndex = i;
	}
	std::cout<<"The winner is player " << winningPlayerIndex+1 << " with " << players[winningPlayerIndex] << " polong longs!"<<std::endl;



	return 0;
}