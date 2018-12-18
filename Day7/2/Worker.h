

class Worker
{
public:
	//Ustawia paraetry
	Worker();

	//Zaczyna prace przypisujac _secomdStart = secStart
	//_workingLetter = letter
	//_isFinish = false;
	//_secondEnd = _secondStart  + letter - 'A' + 61;
	void startWork(const char &letter);

	//Czy pracyje
	bool isWorking() const;
	//Dodae sekunde
	void addSecond();
	//SParwa czy skonczyl
	bool isFinish();

	//Zwraca litere nad ktora pracowal
	char getWorkingLetter() const;

private:
	int _secondStart;
	int _secondEnd;
	char _workingLetter;
	bool _isFinish;
};