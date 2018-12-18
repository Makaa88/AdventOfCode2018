#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include "Node.h"



int FindVector(std::vector<Node> &nodeVector,  int &ID)
{
	int idx = -1;
	for(unsigned i = 0; i < nodeVector.size(); i++)
	{
		if(nodeVector[i].GetID() == ID)
		{
			idx = i;
			break;
		}
	}

	return idx;
}

void SetChild(std::vector<Node> &nodeVector,  int &IDParent,  int &IDChild)
{
	int idx = FindVector(nodeVector,IDParent);

	if(idx != -1)
	{
		nodeVector[idx].AddChild(IDChild);
	}
}

void Calculate(std::vector<Node> &nodeVector, int &mainID)
{
	if(nodeVector[mainID].GetNumberOfAllChilds() == 0)
	{

		nodeVector[mainID].SetValue(nodeVector[mainID].GetMetaDataSum());
	}
	else
	{
		int sum = 0;
		std::vector<int> childs = nodeVector[mainID].GetChildsIDs();
		std::vector<int> values = nodeVector[mainID].GetMetaDataValues();
		for(unsigned i = 0; i < values.size(); i++)
		{
			if((values[i]) <= (int)childs.size())
			{
				int idx = FindVector(nodeVector,childs[values[i] - 1]);
				sum += nodeVector[idx].GetValueOfNode();
			}
		}
		nodeVector[mainID].SetValue(sum);
	}
}
	

int main()
{
	std::ifstream file;
	file.open("dane.dat",std::ios::in);

	std::stack<Node> nodeStack;
	std::vector<Node> nodeVector;
	int result = 0;
	int ID = 0;

	while(!file.eof())
	{
	
		if(nodeStack.size() == 0)
		{
			int numberOne;
			int numberTwo;

			file >> numberOne;
			file >> numberTwo;
			
			nodeStack.push(Node(numberOne,numberTwo,ID));
			nodeVector.push_back(Node(numberOne,numberTwo,ID));

			ID++;

			std::cout<<numberOne << " " << numberTwo << std::endl;
		}
		else if(!nodeStack.top().isPresentEveryChild() && nodeStack.top().GetNumberOfAllChilds() != 0)
		{
			int numberOne;
			int numberTwo;

			file >> numberOne;
			file >> numberTwo;
			nodeStack.top().AddChild(ID);
			int parentID = nodeStack.top().GetID();
			SetChild(nodeVector,parentID,ID);
			nodeStack.push(Node(numberOne,numberTwo,ID));
			nodeVector.push_back(Node(numberOne,numberTwo,ID));

			ID++;

		}
		else
		{
			int valueID = nodeStack.top().GetID();
			for(int i = 0; i < nodeStack.top().GetMetadataEntriesNumber(); i++)
			{
				int number;
				file >> number;
				result += number;
				nodeStack.top().AddValue(number);
				nodeVector[valueID].AddValue(number);
			}
			Calculate(nodeVector,valueID);

			nodeStack.pop();
		}
	}


	std::cout<<"\n\nResult: " << result << std::endl;
	std::cout<<"Result2: " << nodeVector[0].GetValueOfNode()<<std::endl;


	return  0;

}