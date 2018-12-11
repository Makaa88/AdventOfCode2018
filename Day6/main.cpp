#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <map>
using namespace std;

int setClosestPoint(int x, int y, multimap<int,int> &points, int **&table, map<int,int> &pav, int &sX, int &sY, int &region)
{
	//Odkomentowac dla czesci 1
	/*for(multimap<int,int>::iterator it = points.begin(); it != points.end(); it++)
	{
		if(it->first == x && it->second == y)
			return 0;
	}*/
	multimap<int,int>::iterator it = points.begin();
	int min = abs(it->first - x) + abs(it->second - y);
	int sum = min;
	int idx = 1;
	int n = 2;
	it++;
	for(; it != points.end(); it++)
	{
		int distance = abs(it->first - x) + abs(it->second - y);
		sum += distance;
		if(distance < min)
		{
			min = distance;
			idx = n;
		}
		else if( distance == min)
		{
			idx = 0;
		}
		n++;
	}
	if(sum < 10000)
	 region++;

	table[x][y] = idx;
	if(x == 0 || x == sX || y == 0 || y == sY)
	{
		pav[idx] = -1;
	}
	else if(pav[idx] != -1)
		pav[idx]++;

	return 1;
}


int main()
{
	string delim = ", ";
	ifstream file;
	file.open("data.dat", ios::in);
	int sizeX = numeric_limits<int>::min();
	int sizeY = numeric_limits<int>::min();
	multimap<int,int> points;
	while(!file.eof())
	{
		string record;
		getline(file,record);
		int i =record.find(delim);
		int x = stoi(record.substr(0,i));
		int y = stoi(record.substr(i+1));

		points.insert(make_pair(x,y));
		if(sizeX < x)
			sizeX = x;
		if(sizeY < y)
			sizeY = y;
	}

	cout<<sizeX << " " << sizeY << endl;
	int **table = new int *[sizeX+1];
	for(int i = 0; i < sizeX+1; i++)
	{
		table[i] = new int [sizeY+1];
		for(int j = 0; j <= sizeY; j++)
			table[i][j] = 0;
	}

	int number = 1;
	map<int,int> pointsAndValues;

	for(multimap<int,int>::iterator it = points.begin(); it != points.end(); it++)
	{
		table[it->first][it->second] = number;
		pointsAndValues.insert(make_pair(number,0));
		number++;
	}
	pointsAndValues.insert(make_pair(0,0));

	int region = 0;
	for(int i = 0; i <= sizeX; i++)
	{

		for(int j = 0; j <= sizeY; j++)
			{
				setClosestPoint(i,j, points, table, pointsAndValues, sizeX, sizeY, region);
			}
	}


	int max = 0;
	int p = 0;
	for(map<int,int>::iterator it = pointsAndValues.begin(); it != pointsAndValues.end(); it++)
	{
		if(it->second + 1 > max)
		{
			p = it->first;
			max = it->second+1;
		}
	}

	cout<<p << ": " << max << endl << "RegionSize: "<<region << endl;

	/*for(multimap<int,int>::iterator it = pointsAndValues.begin(); it != pointsAndValues.end(); it++)
	{
		cout<<it->first << " :" << it->second << endl;
	}*/

	for(int i = 0; i <= sizeX; i++)
		delete[] table[i];
	delete[] table;
	return 0;
}