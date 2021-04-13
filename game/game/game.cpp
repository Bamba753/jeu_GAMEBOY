#include "Game.hpp"

// Constructeurs
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemy();
}

// Destructeurs
Game::~Game()
{
	delete this->window;
}

// Fonctions privées
void Game::initVariables()
{
	this->window = nullptr;
	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mousehold = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(144);
}

void Game::initEnemy()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(sf::Color::Cyan);
	this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(1.f);
}


void Game::pollevent()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::Escape)
					this->window->close();
				break;
			default:
				continue;
		}
	}
}

void Game::updateMousePosition()
{
	/*
	. return void
	.
	. update la position de la souris relative à la fénétre
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
	/*
	.	return void
	.	
	.	Update la liste des enemies 
	.	remove the enemy at the edge of the screen
	*/
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemies();
			this->enemySpawnTimer = 0;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	bool deleted;
	for(int i = 0;i < this->enemies.size();i++)
	{
		this->enemies[i].move(0.f, 1.0f);

		// Delete if click upon
		deleted = false;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->mousehold == false)
			{
				this->mousehold = true;
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					deleted = true;

					// Gain points
					this->points += 10;
				}
			}
		}
		else
			this->mousehold = false;


		std::cout << this->points <<std::endl;
		// Delete at the edge of the screen
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			deleted = true;
		}

		if (deleted)
			this->enemies.erase(this->enemies.begin() + i);
	}
}


void Game::spawnEnemies()
{
	/*
	.	return void
	.
	.	spawn enemies, modifie la vouleur et la position
	.	random pos
	.	random color
	*/
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x) - this->enemy.getSize().x),
		0);
	
	this->enemy.setFillColor(sf::Color::Green);

	// Spawn the enemy
	this->enemies.push_back(this->enemy);
}

// Acesseurs
bool Game::running() const
{
	// Renvoie l'etat de ma fenetre
	return (this->window)->isOpen();
}

// Fonctions
void Game::update()
{
	this->pollevent();

	this->updateMousePosition();
	this->updateEnemies();
}



void Game::renderEnemies()
{
	for (auto& i : this->enemies)
	{
		this->window->draw(i);
	}
}


void Game::render()
{
	/* - Efface les frames précedents
	.  - Render les objets
	.  - Affiche la fénetre
	*/
	this->window->clear();

	// Draw objects
	this->renderEnemies();

	this->window->display();
}