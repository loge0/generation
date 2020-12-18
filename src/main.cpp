#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
int main()
{
	int screen_x = 50; //valeur initial = 1000//
	int screen_y = 500; //valeur initial = 500//
	int min_random = 1;
	int max_random = 100;
	unsigned int good_random = 20;
	float square_size = 10.0f;

	sf::Color brown (91,56,0);
	sf::Color blue (0,243,255);
	sf::Color pink (255,0,255);
	sf::Color green(70,255,0);

	std::random_device random;
	std::mt19937 random_algo (random());
	std::uniform_int_distribution <std::mt19937::result_type> size_random (min_random,max_random);

	sf::RenderWindow generation (sf::VideoMode(screen_x,screen_y),"generation");
	std::vector<std::vector<sf::RectangleShape>> map;

	for (int y=0;y<screen_y/square_size;y++)
	{
		std::vector<sf::RectangleShape> line;
		for (int x=0;x<screen_x/square_size;x++)
		{
			sf::RectangleShape square (sf::Vector2f(square_size,square_size));
			square.setPosition(x*square_size,y*square_size);
			if (size_random(random) > good_random)
			{
				square.setFillColor(blue);
			}
			else 
			{
				square.setFillColor(brown);
			}
			line.push_back(std::move(square));
		}
		map.push_back(std::move(line));
		good_random = good_random +2;
	}
	for (int y=0;y<screen_y/square_size;y++)
	{

		for (int x=0;x<screen_x/square_size;x++)
		{
			
			sf::Color neighboring_squareL;
			if (x > 0)
			{
				neighboring_squareL = map[y][x-1].getFillColor();
			}
			else
			{
				neighboring_squareL = pink;
			}
			std::to_string(neighboring_squareL.r);
			std::cout << std::to_string(neighboring_squareL.r) << std::endl;
			std::cout << std::to_string(neighboring_squareL.g) << std::endl;
			std::cout << std::to_string(neighboring_squareL.b) << std::endl;
			std::cout << "" << std::endl;
			sf::Color neighboring_squareR;
			if (x < screen_x/square_size-1)
			{
				neighboring_squareR = map[y][x+1].getFillColor();
			}
			else
			{
				neighboring_squareR = pink;
			}
			std::cout << std::to_string(neighboring_squareR.r) << std::endl;
			std::cout << std::to_string(neighboring_squareR.g) << std::endl;
			std::cout << std::to_string(neighboring_squareR.b) << std::endl;
			std::cout << "" << std::endl;
			sf::Color neighboring_squareU;
			if (y > 0)
			{
				neighboring_squareU= map[y-1][x].getFillColor();
			}
			else
			{
				neighboring_squareU = pink;
			}
			std::cout << std::to_string(neighboring_squareU.r) << std::endl;
			std::cout << std::to_string(neighboring_squareU.g) << std::endl;
			std::cout << std::to_string(neighboring_squareU.b) << std::endl;
			std::cout << "" << std::endl;
			sf::Color neighboring_squareD;
			if (y < screen_y/square_size-1)
			{
				neighboring_squareD = map[y+1][x].getFillColor();
			}
			else
			{
				neighboring_squareD = pink;
			}
			std::cout << std::to_string(neighboring_squareD.r) << std::endl;
			std::cout << std::to_string(neighboring_squareD.g) << std::endl;
			std::cout << std::to_string(neighboring_squareD.b) << std::endl;
			std::cout << "" << std::endl;
			std::cout << "" << std::endl;
			std::cout << "" << std::endl;
			std::cout << "" << std::endl;
			unsigned int chance_brown = 0;
			if (neighboring_squareL == brown)
			{
				chance_brown = chance_brown + 25;
			}
		//	std::cout << chance_brown << std::endl;//
			if (neighboring_squareR == brown)
			{
				chance_brown = chance_brown + 25;
			}
		//	std::cout << chance_brown << std::endl;//
			if (neighboring_squareU == brown)
			{
				chance_brown = chance_brown + 25;
			}
		//	std::cout << chance_brown << std::endl;//
			if (neighboring_squareD == brown)
			{
				chance_brown = chance_brown + 25;
			}	
			std::cout << chance_brown << std::endl;
			std::cout << "" << std::endl;
			
			if (chance_brown < 60)
			{
				chance_brown = 0;
			}
			std::cout << chance_brown << std::endl;
			std::cout << "" << std::endl;
			
			if (size_random(random) <= chance_brown)
			{
				map[y][x].setFillColor(brown);
			}
			else
			{
				map[y][x].setFillColor(blue);
			}
			
		}
	}
	for (int y=0;y<screen_y/square_size;y++)
	{
		for (int x=0;x<screen_x/square_size;x++)
		{	

			sf::Color neighboring_squareU;
			if (y > 0)
			{
				neighboring_squareU = map[y-1][x].getFillColor();
			}
			else
			{
				neighboring_squareU = pink;
			}
			
			sf::Color square_color = map[y][x].getFillColor();
			if (neighboring_squareU == blue && square_color == brown) 
			{
				map[y][x].setFillColor(green);
			}
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