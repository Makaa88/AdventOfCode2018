#include "Worker.h"
#include <iostream>

Worker::Worker()
:_secondStart(0),
_secondEnd(0),
_workingLetter('-'),
_isFinish(true)
{

}

//Zaczyna prace 
void Worker::startWork(const char &letter )
{
	_secondStart = 0;
	_workingLetter = letter;
	_secondEnd = letter - 'A' + 61;
	_isFinish = false;
}


bool Worker::isWorking() const
{
	return !_isFinish;
}

void Worker::addSecond()
{
	_secondStart++;
}

bool Worker::isFinish()
{
	if(_secondStart == _secondEnd)
	{
		_isFinish = true;
	}

	return _isFinish;
}

char Worker::getWorkingLetter() const
{
	return _workingLetter;
}