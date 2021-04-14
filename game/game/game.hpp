#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <ctime>
#include <sstream>

/*
.   Classe principale du jeu
.
.
*/

class Game
{
	// Variables
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	// Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;
	
	// Game logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mousehold;
	
	//Ressources
	sf::Font font;

	// Text
	sf::Text uiText;

	// Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Fonctions privées
	void initVariables();
	void initWindow();
	void initEnemy();
	void initFonts();
	void initText();
public:
	// Cosntructeurs
	Game();
	// Destructeurs
	~Game();

	// Fonctions
	void update();
	void render();
	void pollevent();
	void updateMousePosition();
	void spawnEnemies();
	void updateEnemies();
	void renderEnemies(sf::RenderTarget& target);
	void renderText(sf::RenderTarget& target);
	void updateText();
	// Accesseurs
	bool running() const;
	bool endGameState() const;
};

#endif