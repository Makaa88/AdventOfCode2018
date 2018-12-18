#include <iostream>
#include "Step.h"

Step::Step(const char &letter)
:_letter(letter)
{

}

Step::Step(const char &letter, const char &toAdd)
:_letter(letter)
{
	addDependance(toAdd);
}


bool Step::operator<(const Step &step) const
{
	return _letter < step._letter;
}

char Step::getLetter() const
{
	return _letter;
}


void Step::addDependance(const char &dep) const
{
	_set.insert(dep);
}

bool Step::operator==(const char &letter) const
{
	return (_letter == letter);
}

int Step::size() const
{
	return _set.size();
}

void Step::erase(const char &sign) const
{
	std::set<char>::iterator it;
	it = _set.find(sign);
	if(it != _set.end())
		_set.erase(it);
}


std::ostream& operator<<(std::ostream &out, const Step &step)
{
	out << step._letter << std::endl << "ZALEZNOSCI: ";
	for(char l : step._set)
	{
		out<< l << " ";
	}

	out << std::endl;

	return out;
}