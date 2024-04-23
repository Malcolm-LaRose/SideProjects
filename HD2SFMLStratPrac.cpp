#include <SFML/Graphics.hpp>

#include <stdio.h>
#include <vector>
#include <unordered_map>

using Point = sf::Vector2f;


// Window properties
constexpr int screenWidth = 1920;
constexpr int screenHeight = 1080;

const Point screenCenter((screenWidth / 2), (screenHeight / 2));

class Strategem {
public:
	Strategem(std::string nm, std::vector<char> arr) : name(nm), arrows(arr) {}

	std::string getName() {
		return name;
	}

	std::vector<char> getSequence() {
		return arrows;
	}

	auto getLength() {
		return arrows.size();
	}

private:
	std::string name; // Each strategem has a name
	std::vector<char> arrows; // Represent arrows as a char (wasd or udlr)
	//int length; // Represents size of arrows vector --> Not necessary, just have a function calculate and return it



};


class StrategemList {
public:

	void addStrategem(Strategem strat) {
		strategems.push_back(strat);
	}

	Strategem getStrategem(Strategem strat) {
		return strat;
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
	std::vector<Strategem> strategems; // List of strategems

};





class SFML_Handling {
public:

	SFML_Handling() : window(sf::VideoMode(screenWidth, screenHeight), "SFML works!"), event() {}

	void renderTest() {

		// Rendering

		window.clear();
		// window.draw();
		window.display();
	}

	void handleEvent() {
		while (window.pollEvent(event))
		{
			// Request for closing the window
			if (event.type == sf::Event::Closed)
				window.close();

			// The escape key was pressed
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
				window.close();

		}
	}

	sf::RenderWindow& getWindow() {
		return window;
	}

private:

	sf::RenderWindow window; // Window for displaying graphics
	sf::Event event; // SF event

	enum WASDKeys {
		Key_W = sf::Keyboard::W,
		Key_A = sf::Keyboard::A,
		Key_S = sf::Keyboard::S,
		Key_D = sf::Keyboard::D
	};

	enum ArrowKeys {
		Key_Up = sf::Keyboard::Up,
		Key_Left = sf::Keyboard::Left,
		Key_Down = sf::Keyboard::Down,
		Key_Right = sf::Keyboard::Right
	};

	bool isWASDKey(int key) const {
		return key == Key_W || key == Key_A || key == Key_S || key == Key_D;
	}

	bool isArrowKey(int key) const {
		return key == Key_Up || key == Key_Left || key == Key_Down || key == Key_Right;
	}

	bool isUpKey(int key) const {
		return key == Key_W || key == Key_Up;
	}

	bool isLeftKey(int key) const {
		return key == Key_A || key == Key_Left;
	}

	bool isDownKey(int key) const {
		return key == Key_S || key == Key_Down;
	}

	bool isRightKey(int key) const {
		return key == Key_D || key == Key_Right;
	}



};

class ArrowBox {
public:
	ArrowBox() : boundingBox() {}


private:
	sf::ConvexShape arrowShape;
	sf::ConvexShape boundingBox;



};

class HD2Game {
public:
	HD2Game() : handler(), strategems() { }

	void run() {
	
		while (handler.getWindow().isOpen()) {
			handler.handleEvent();
			handler.renderTest();
		}
	
	}

	Strategem chooseRandomStrategem() {
		// Somehow get a random strategem from strategem list
	}

private:
	SFML_Handling handler;
	StrategemList strategems;


};


int main() {
	// Instantiate classes as needed

	HD2Game game;

	game.run();


}
