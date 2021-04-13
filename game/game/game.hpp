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
	unsigned points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mousehold;

	// Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Fonctions privées
	void initVariables();
	void initWindow();
	void initEnemy();
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
	void renderEnemies();
	// Accesseurs
	bool running() const;
};

#endif