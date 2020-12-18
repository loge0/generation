#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
int main()
{
	int screen_x = 1300;
	int screen_y = 700;
	int min_random = 1;
	int max_random = 100;
	unsigned int good_random = 20;
	float square_size = 10.0f;

	sf::Color brown (91,56,0);
	sf::Color blue (0,243,255);
	sf::Color pink (255,0,255);
	sf::Color green (70,255,0);
	sf::Color grey (109,109,109);
	sf::Color deep_blue (28,45,255);

	std::random_device random;
	std::mt19937 random_algo (random());
	std::uniform_int_distribution <std::mt19937::result_type> size_random (min_random,max_random);

	sf::RenderWindow generation (sf::VideoMode(screen_x,screen_y),"generation");
	std::vector<std::vector<sf::RectangleShape>> map;

	for (int y = 0; y < (screen_y / square_size) / 2; y++)
	{
		std::vector<sf::RectangleShape> line;
		for (int x = 0; x < screen_x / square_size; x++)
		{
			sf::RectangleShape square(sf::Vector2f(square_size, square_size));
			square.setPosition(x * square_size, y * square_size);
			square.setFillColor(blue);
			line.push_back(std::move(square));
		}
		map.push_back(std::move(line));
	}
	for (int y = (screen_y / square_size) / 2; y < screen_y / square_size; y++)
	{
		std::vector<sf::RectangleShape> line;
		for (int x = 0; x < screen_x / square_size; x++)
		{
			sf::RectangleShape square(sf::Vector2f(square_size, square_size));
			square.setPosition(x * square_size, y * square_size);
			if (size_random(random) > good_random)
				square.setFillColor(blue);
			else
				square.setFillColor(brown);
			line.push_back(std::move(square));
		}
		map.push_back(std::move(line));
		good_random = good_random + 5; //default = 5, more it grow, flatter the world is//
	}
	for (int y = 0; y < screen_y / square_size; y++)
	{
		for (int x = 0; x < screen_x / square_size; x++)
		{
			size_t chance_brown = 0;
			sf::Color neighboring_squareL = x > 0 ? map[y][x - 1].getFillColor() : pink;
			sf::Color neighboring_squareR = x < screen_x / square_size - 1 ? map[y][x + 1].getFillColor() : pink;
			sf::Color neighboring_squareU = y > 0 ? map[y - 1][x].getFillColor() : pink;
			sf::Color neighboring_squareD = y < screen_y / square_size - 1 ? map[y + 1][x].getFillColor() : pink;

			if (neighboring_squareL == brown)
				chance_brown += 25;
			if (neighboring_squareR == brown)
				chance_brown += 25;
			if (neighboring_squareU == brown)
				chance_brown += 25;
			if (neighboring_squareD == brown)
				chance_brown += 25;
			
			if (chance_brown >= 75 && size_random(random) <= chance_brown)
				map[y][x].setFillColor(brown);
			else if (chance_brown == 0)
				map[y][x].setFillColor(blue);
		}
	}
	for (int y = 0; y < screen_y / square_size; y++)
	{
		for (int x = 0; x < screen_x / square_size; x++)
		{
			sf::Color square_color = map[y][x].getFillColor();
			if (square_color == brown)
			{
				size_t chance_grey = 3;
				if (chance_grey >= size_random(random))
				{
					map[y][x].setFillColor(grey);
				}
			}
		}
	}
	for (int y = 0; y < screen_y / square_size; y++)
	{
		for (int x = 0; x < screen_x / square_size; x++)
		{
			size_t chance_grey = 0;
			sf::Color square_color = map[y][x].getFillColor();
			sf::Color neighboring_squareL = x > 0 ? map[y][x - 1].getFillColor() : pink;
			sf::Color neighboring_squareR = x < screen_x / square_size - 1 ? map[y][x + 1].getFillColor() : pink;
			sf::Color neighboring_squareU = y > 0 ? map[y - 1][x].getFillColor() : pink;
			sf::Color neighboring_squareD = y < screen_y / square_size - 1 ? map[y + 1][x].getFillColor() : pink;

			if (neighboring_squareL == grey && square_color == brown)
				chance_grey += 25;
			if (neighboring_squareR == grey && square_color == brown)
				chance_grey += 25;
			if (neighboring_squareU == grey && square_color == brown)
				chance_grey += 25;
			if (neighboring_squareD == grey && square_color == brown)
				chance_grey += 25;
			
			if (size_random(random) <= chance_grey)
				map[y][x].setFillColor(grey);
		}
	}
for (int y = 1.3f * (screen_y / square_size) / 2; y < screen_y / square_size; y++)
    {
        for (int x = 0; x < screen_x / square_size; x++)
        {
            sf::Color square_color = map[y][x].getFillColor();
            if (square_color == blue)
            {
                map[y][x].setFillColor(deep_blue);
            }
        }
    }
	for (int y = 0; y < screen_y / square_size; y++)
	{
		for (int x = 0; x < screen_x / square_size; x++)
		{
			sf::Color neighboring_squareU = y > 0 ? map[y - 1][x].getFillColor() : pink;
			sf::Color neighboring_squareD = y < screen_y / square_size - 1 ? map[y + 1][x].getFillColor() : pink;
			
			sf::Color square_color = map[y][x].getFillColor();
			if (square_color == blue && neighboring_squareD == brown && neighboring_squareU != brown)
				map[y][x].setFillColor(green);
		}
	}

	while(generation.isOpen())
	{
		sf::Event event;
		while (generation.pollEvent(event))
		{
			if (event.type==sf::Event::Closed) 
			{
				generation.close();
			}
		}
		for (auto & line : map)
		{
			for (auto & tile : line)
			{
				generation.draw(tile);
			}
		}
		generation.display();
	}

	return 0;
}