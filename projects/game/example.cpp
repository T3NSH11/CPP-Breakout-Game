#include "example.h"

Example::Example() : App()
{
	int offset = 50;

	for (size_t count = 0; count < 11; count++)
	{
		lines.push_back(sf::RectangleShape(sf::Vector2f(500.0f, 5.0f)));
		int i = lines.size() - 1;
		lines[i].setPosition(sf::Vector2f(600, count * offset));
		lines[i].setFillColor(sf::Color::Transparent);
	}

	for (size_t counta = 0; counta < 11; counta++)
	{
		lines.push_back(sf::RectangleShape(sf::Vector2f(5.0f, 500.0f)));
		int i = lines.size() - 1;
		lines[i].setPosition(sf::Vector2f(counta * offset + 600, 0));
		lines[i].setFillColor(sf::Color::Transparent);
	}

	for (size_t y = 0; y < 10; y++)
	{
		for (size_t x = 0; x < 10; x++)
		{
			sprites[x + y * 10].sprite.setPosition(sf::Vector2f((x * 50) + 600, y * 50));
			//sprites[x + y * 10].setTexture(*kage::TextureManager::getTexture("bot.png"));
		}
	}
	if (!font.loadFromFile("bluehigh.ttf"))
	{
		std::cout << "can't load font" << std::endl;
	}

	playerblock.setPosition(sf::Vector2f(960.0f, 960.0f));
	playerblock.setFillColor(sf::Color::Red);
	playerblock.setSize(sf::Vector2f(100.0f, 10.0f));

	borderleft.setSize(sf::Vector2f(30.f, 1080.f));
	borderleft.setPosition(sf::Vector2f(540.f, 0.f));
	borderleft.setFillColor(sf::Color::Blue);

	bordertop.setSize(sf::Vector2f(600.f, 10.f));
	bordertop.setPosition(sf::Vector2f(550.f, 0.f));
	bordertop.setFillColor(sf::Color::Blue);

	borderbottom.setSize(sf::Vector2f(600.f, 10.f));
	borderbottom.setPosition(sf::Vector2f(550.f, 1070.f));
	borderbottom.setFillColor(sf::Color::Transparent);

	borderright.setSize(sf::Vector2f(30.f, 1080.f));
	borderright.setPosition(sf::Vector2f(1130.f, 0.f));
	borderright.setFillColor(sf::Color::Blue);

	ball.setRadius(5.f);
	ball.setFillColor(sf::Color::Yellow);
	ball.setPosition(850, 500);

    restarttext.setFont(font);
	restarttext.setString("level restarted");
	restarttext.setPosition(1300.0f, 400.0f);
	restarttext.setCharacterSize(50);
	restarttext.setFillColor(sf::Color::Transparent);
	

    gameovertext.setFont(font);
	gameovertext.setString("GAME OVER");
	gameovertext.setColor(sf::Color::Transparent);
	gameovertext.setPosition(1300.0f, 600.0f);
	gameovertext.setCharacterSize(50);
	

    restartinfo.setFont(font);
	restartinfo.setString("press 'SPACE' to restart");
	restartinfo.setPosition(1300.0f, 700.0f);
	restartinfo.setCharacterSize(50);
	
}

Example::~Example()
{
}

Example& Example::inst()
{
	static Example s_instance;
	return s_instance;
}

bool Example::start()
{
	m_backgroundSprite = kage::TextureManager::getSprite("data/sky.jpg");
	sf::Vector2u resolution = m_backgroundSprite->getTexture()->getSize();
	m_backgroundSprite->setScale(float(m_window.getSize().x) / resolution.x, float(m_window.getSize().y) / resolution.y);
	return true;
}

void Example::update(float deltaT)
{
	ball.move(ballsx, ballsy);

	for (size_t i = 0; i < 99; i++)
	{
		if (ball.getGlobalBounds().intersects(sprites[i].sprite.getGlobalBounds()) && sprites[i].destroyed == 0)
		{
			ballsy = -ballsy;
			sprites[i].sprite.setColor(sf::Color::Transparent);
			sprites[i].destroyed == 1;
		}
	}

	if (ball.getGlobalBounds().intersects(bordertop.getGlobalBounds()) | ball.getGlobalBounds().intersects(playerblock.getGlobalBounds()))
	{
		ballsy = -ballsy;
	}

	if (ball.getGlobalBounds().intersects(borderleft.getGlobalBounds()) | ball.getGlobalBounds().intersects(borderright.getGlobalBounds()))
	{
		ballsx = -ballsx;
	}

	if (ball.getGlobalBounds().intersects(borderbottom.getGlobalBounds()))
	{
		ballsx = 0;
		ballsy = 0;
		ball.setFillColor(sf::Color::Transparent);
		gameovertext.setFillColor(sf::Color::Red);
		restarttext.setFillColor(sf::Color::Transparent);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_window.hasFocus())
	{
		m_running = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && m_window.hasFocus() && !playerblock.getGlobalBounds().intersects(borderright.getGlobalBounds()))
	{
		playerblock.move(sf::Vector2f(+5.0f, 0.0f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && m_window.hasFocus() && !playerblock.getGlobalBounds().intersects(borderleft.getGlobalBounds()))
	{
		playerblock.move(sf::Vector2f(-5.0f, 0.0f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_window.hasFocus())
	{
		ball.setFillColor(sf::Color::Yellow);
		ball.setPosition(850, 500);
		ballsx = 8.0f;
		ballsy = 8.0f;
		gameovertext.setFillColor(sf::Color::Transparent);
		restarttext.setFillColor(sf::Color::Blue);
	}

	ImGui::Begin("Kage2D");
	if (ImGui::Button("Exit"))
	{
		m_running = false;
	}


	if (ImGui::Button("load"))
	{
		std::ifstream  levelfile;
		std::string line;
		std::string newString;
		levelfile.open("level.txt");

		if (levelfile.is_open())
		{
			while (getline(levelfile, line))
			{
				for (size_t i = 0; i < line.size(); i++)
				{
					newString = line.substr(i, 1);
					std::cout << newString << std::endl;

					if (newString == "1")
					{
						sprites[i].sprite.setTexture(*kage::TextureManager::getTexture("bot.png"));
						sprites[i].id = 1;
						
					}
				}

			}
			levelfile.close();
		}
		else
		{
			std::cout << "Unable to open file";
		}
	}

	ImGui::End();
}

void Example::render()
{
	for (size_t o = 0; o < 100; o++)
	{
		m_window.draw(sprites[o].sprite);
	}

	for (size_t E = 0; E < 22; E++)
	{
		m_window.draw(lines[E]);
	}
	//m_window.draw(*m_backgroundSprite);

	m_window.draw(playerblock);
	m_window.draw(borderright);
	m_window.draw(borderleft);
	m_window.draw(ball);
	m_window.draw(borderbottom);
	m_window.draw(bordertop);
	m_window.draw(restarttext);
	m_window.draw(restartinfo);
	m_window.draw(gameovertext);

}

void Example::cleanup()
{
	delete m_backgroundSprite;
}