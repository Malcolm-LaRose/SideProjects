#include <string>
#include <vector>
#include <list>
#include <iostream>

class Strategem {
public:

	// Constructor

	Strategem(std::string nm, std::vector<char> keys) : name(nm), keyPresses(keys) {}

	std::string getName() {
		return name;
	}

	std::vector<char> getKeys() {
		return keyPresses;
	}

	void displayStrategem() {
		std::cout << name << ": ";
		for (char& key : keyPresses) {
			std::cout << key << ' ';
		}
		std::cout << std::endl;
	}


private:
	std::string name;
	std::vector<char> keyPresses; // w a s d or arrow keys


};

class Game {
public:

	void displayStrategem(Strategem strat) {
		std::cout << strat.getName() << ": ";
		for (char& key : strat.getKeys()) {
			std::cout << key << ' ';
		}
		std::cout << std::endl;
	}

	void addStrategem(Strategem strat) {
		strategems.push_back(strat);
	}


private:
	std::list<Strategem> strategems;


};




int main() {

	Strategem orbitalStrike("Orbital Strike", { 'd','d','s' });

	Game game;

	orbitalStrike.displayStrategem();
	

	return 0;
}