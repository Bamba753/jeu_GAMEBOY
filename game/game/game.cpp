#include "Game.hpp"

// Constructeurs
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemy();
	this->initFonts();
	this->initText();

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
	this->health = 10;
	this->endGame = false;
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

void Game::initFonts()
{
	if (this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
		std::cout << "Error failed load fonts";

}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(36);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("None");
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

		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
		}
	}

	// Delete if click upon
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		bool deleted = false;
		if (this->mousehold == false)
		{
			this->mousehold = true;
			for (int i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
					// Gain points
					this->points += 1;
					std::cout << "points : " << points << std::endl;
				}
			}
		}
	}
	else
		this->mousehold = false;

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

bool Game::endGameState() const
{
	return this->endGame;
}

// Fonctions
void Game::update()
{
	this->pollevent();
	if (!endGame)
	{
		this->updateMousePosition();
		this->updateText();
		this->updateEnemies();
	}

	if (this->health <= 0)
		this->endGame = true;
}



void Game::renderEnemies(sf::RenderTarget& target)
{
	for (auto& i : this->enemies)
	{
		target.draw(i);
	}
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::updateText()
{
	std::stringstream ss;
	ss << "Points : " << this->points << "\n"
		<< "Health : " << this ->health;
	this->uiText.setString(ss.str());
}


void Game::render()
{
	/* - Efface les frames précedents
	.  - Render les objets
	.  - Affiche la fénetre
	*/
	this->window->clear();

	// Draw objects
	this->renderEnemies(*this->window);
	this->renderText(*this->window);
	this->window->display();
}