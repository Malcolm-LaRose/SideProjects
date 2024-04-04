#include <SDL.h>

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

class StrategemList {
public:

	// Constructor
	StrategemList() : strategems() {
		initStrategems();
	}

	void displayStrategem(Strategem strat) {
		std::cout << strat.getName() << ": ";
		for (char& key : strat.getKeys()) {
			std::cout << key << ' ';
		}
		std::cout << std::endl;
	}

	void displayAllStrats() {
		for (Strategem strat : strategems) {
			std::cout << strat.getName() << ": ";
			for (char& key : strat.getKeys()) {
				std::cout << key << ' ';
			}
			std::cout << std::endl;
		}

	}

	void addStrategem(Strategem strat) {
		strategems.push_back(strat);
	}

	void initStrategems() {
		// Declare and initialize strategems
		Strategem orbitalGatling("Orbital Gatling Barrage", { 'd','s','a','w','w' });
		Strategem orbitalAirburst("Orbital Airburst Strike", { 'd','d','d' });
		Strategem orbital120("Orbital 120MM Barrage", { 'd','d','s','a','d','s' });
		Strategem orbital380("Orbital 380MM Barrage", { 'd','s','w','w','a','s','s' });
		Strategem orbitalWalking("Orbital Walking Barrage", { 'd','s','d','s','d','s' });
		Strategem orbitalLaser("Orbital Laser", { 'd','s','w','d','s' });
		Strategem orbitalRail("Orbital Railcannon Strike", { 'd','w','s','s','d' });
		Strategem orbitalStrike("Orbital Precision Strike", { 'd','d','w' });
		Strategem orbitalGas("Orbital Gas Strike", { 'd','d','s','d' });
		Strategem orbitalEMS("Orbital EMS Strike", { 'd','d','a','s' });
		Strategem orbitalSmoke("Orbital Smoke Strike", { 'd','d','s','w' });

		// Load them into strategems list
		addStrategem(orbitalGatling);
		addStrategem(orbitalAirburst);
		addStrategem(orbital120);
		addStrategem(orbital380);
		addStrategem(orbitalWalking);
		addStrategem(orbitalLaser);
		addStrategem(orbitalRail);
		addStrategem(orbitalStrike);
		addStrategem(orbitalGas);
		addStrategem(orbitalEMS);
		addStrategem(orbitalSmoke);


	}


private:
	std::list<Strategem> strategems;

};

class Menu {}; // Menu for the game, need to include options (for keybindings) and list of all strats (should also include credits) (bonus for saving stats somehow)

class Game {
public:

	Strategem chooseRandomStrategem() {
	
	}

	void handleInput() {
		// Look for keypresses
		// Ignore anything invalid
		// Maybe encapsulate in separate class (later)
	}

	void compareInputToStrategem() {
		// Display random strategem
		// Handle user input
		// Compare input to strategem[0]
		// If correct, continue to loop, otherwise restart
			// Figure out how to show correct input and incorrect input leading to reset
	}

	void stats() {
		// Get average time to complete 
		// Get % correct
	}

	void gameLoop() {
		// Skeleton
		const Strategem chosenStrategem = chooseRandomStrategem();
		while (true) {
			handleInput();
			compareInputToStrategem();
		}
	}


};



int main(int argc, char* argv[]) {

	StrategemList sL;

	sL.displayAllStrats();

	return 0;
}