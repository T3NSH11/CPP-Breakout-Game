#include "example.h"

Example::Example(): App()
{

	int offset = 50;
	for (size_t count = 0; count < 11; count++)
	{
		lines.push_back(sf::RectangleShape(sf::Vector2f(500.0f, 5.0f)));
		int i = lines.size() - 1;
		lines[i].setPosition(sf::Vector2f(0, count * offset));
	}

	for (size_t counta = 0; counta < 11; counta++)
	{
		lines.push_back(sf::RectangleShape(sf::Vector2f(5.0f, 500.0f)));
		int i = lines.size() - 1;
		lines[i].setPosition(sf::Vector2f(counta * offset, 0));
	}
	
	for (size_t y=0; y < 10; y++)
	{
		for (size_t x = 0; x < 10; x++)
		{
			sprites[x + y * 10].sprite.setPosition(sf::Vector2f(x * 50, y * 50));
			//sprites[x + y * 10].setTexture(*kage::TextureManager::getTexture("bot.png"));
		}
	}

}

Example::~Example()
{
}

Example &Example::inst()
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

	

	sf::Vector2i mousepos = sf::Mouse::getPosition(m_window);
	int mouseposx = mousepos.x / 50;
	int mouseposy = mousepos.y / 50;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sprites[mouseposx + mouseposy * 10].sprite.setTexture(*kage::TextureManager::getTexture("bot.png"));
		sprites[mouseposx + mouseposy * 10].id = 1;
	}

	//line.setFillColor(sf::Color(countercolr, countercolg, countercolb));

	//rgb start

	//red loop
	if (countercolr <= 254)
	{
		if (intb == 0)
		{
			countercolr = countercolr + 1;
		}
	}

	if (countercolb == 254)
	{
		intr = 1;
	}

	if (countercolr >= 1)
	{
		if (intg == 0)
		{
			countercolr = countercolr - 1;
		}
	}

	if (countercolr == 0)
	{
		intr = 0;
	}

	//green loop

	if (countercolg <= 254)
	{
		if (intr == 1)
		{
			countercolg = countercolg + 1;
		}
	}

	if (countercolg == 255)
	{
		intg = 1;
	}

	if (countercolg >= 0)
	{
		if (intb == 0)
		{
			countercolr = countercolr - 1;
		}
	}

	if (countercolg == 0)
	{
		intg = 0;
	}

	//blue loop

	if (countercolb <= 254)
	{
		if (intg == 1)
		{
			countercolb = countercolb + 1;
		}
	}

	if (countercolb == 254)
	{
		intb = 1;
	}
	
	if (countercolb >= 0)
	{
		if (intb == 1)
		{
			countercolr = countercolr - 1;
		}
	}

	if (countercolb == 0)
	{
		intb = 0;
	}

	//rgb end
	
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && m_window.hasFocus())
	{
		m_running = false;
	}

	ImGui::Begin("Kage2D");
	if(ImGui::Button("Exit"))
	{ 
		m_running = false;
	}

	if (ImGui::Button("save"))
	{
		std::ofstream  level;
		level.open("level.txt");

		for (size_t l = 0; l < 100; l++)
		{
			level << sprites[l].id;
		}
		level.close();
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

		else std::cout << "Unable to open file";
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
}

void Example::cleanup()
{
	delete m_backgroundSprite;
}

