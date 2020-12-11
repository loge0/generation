#include <SFML/Graphics.hpp>
int main()
{
	sf::RenderWindow generation (sf::VideoMode(1000,500),"generation");
	sf::RectangleShape square_test (sf::Vector2f(64,64));
	square_test.setPosition(0,0);
	square_test.setFillColor(sf::Color::Magenta);

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