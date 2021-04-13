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
// Fonctions
void Game::update()
{
	this->pollevent();
	this->enemy.setPosition(sf::Mouse::getPosition(*this->window).x, sf::Mouse::getPosition(*this->window).y);
	std::cout << "Postion souris :" << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << std::endl;
}

void Game::render()
{
	/* - Efface les frames précedents
	.  - Render les objets
	.  - Affiche la fénetre
	*/
	this->window->clear();
	this->window->draw(this->enemy);
	this->window->display();
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

// Acesseurs
bool Game::running() const
{
	return (this->window)->isOpen();
}