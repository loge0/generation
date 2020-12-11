#include <SFML/Graphics.hpp>
int main()
{
	int screen_x = 1000;
	int screen_y = 500;
	int square_size = 10;
	sf::RenderWindow generation (sf::VideoMode(screen_x,screen_y),"generation");
	std::vector<std::vector<sf::RectangleShape>>;
	for (int y=0;y<screen_y/square_size;y++)
	{
		std::vector<sf::RectangleShape> line;
		for (int x=0;x<screen_x/square_size;x++)
		{
			std::vector<sf::RectangleShape> line;
			sf::RectangleShape square_test (sf::Vector2f(square_size,square_size));
			square_test.setPosition(x*square_size,y*square_size);
			square_test.setFillColor(sf::Color::Magenta);
			line.push_back(square_test);
			line.push_back(std::move(square_test));
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
		generation.draw(square_test);
		generation.display();
	}

	return 0;
}