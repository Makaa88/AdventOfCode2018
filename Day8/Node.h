#pragma once

#include <vector>
#include <iostream>
class Node
{
public:
	Node(int numberOfChilds, int metadata, int id)
	:_id(id),_maxNumberOfChilds(numberOfChilds), _metadataEntries(metadata)
	{
		_numberOfChilds = 0;
	}

	int GetNumberOfAllChilds() const
	{
		return _maxNumberOfChilds;
	}

	int GetMetadataEntriesNumber() const
	{
		return _metadataEntries;
	}

	void AddChild(const int &ID)
	{
		_numberOfChilds++;
		_childID.push_back(ID);
	}

	int GetID() const
	{
		return _id;
	}

	void AddValue(int value)
	{
		_metadataValues.push_back(value);
	}

	bool isPresentEveryChild() const
	{
		return _numberOfChilds == _maxNumberOfChilds;
	}

	void SetValue(const int &value)
	{
		this->_valueOfNode = value;
	}

	int GetValueOfNode() const
	{
		return _valueOfNode;
	}

	int GetMetaDataSum()
	{
		int sum = 0;
		for(unsigned i = 0; i < _metadataValues.size(); i++)
			sum += _metadataValues[i];
		return sum;
	}

	std::vector<int>& GetChildsIDs()
	{
		return _childID;
	}

	std::vector<int>& GetMetaDataValues()
	{
		return _metadataValues;
	}

	void PrintValues() const
	{
		for(unsigned i = 0; i < _metadataValues.size(); i++)
			std::cout<<_metadataValues[i] << " ";
		std::cout<<std::endl;
	}

private:
	int _id;
	int _numberOfChilds;
	int _maxNumberOfChilds;
	int _metadataEntries;
	std::vector<int> _metadataValues;
	std::vector<int> _childID;
	int _valueOfNode;

};