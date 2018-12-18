#pragma once
#include <set>

class Step
{
public:
	friend std::ostream& operator<<(std::ostream &out, const Step &step);
	Step(const char &letter);
	Step(const char &letter, const char &toAdd);

	bool operator<(const Step &step) const;

	char getLetter() const;

	void addDependance(const char &dep) const;
	bool operator==(const char &letter) const;
	int size() const;
	void erase(const char &sign) const;
	

private:

	char _letter;
	mutable std::set<char> _set;

};