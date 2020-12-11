#include <SFML/Graphics.hpp>
int main()
{
	sf::RenderWindow generation (sf::VideoMode(1000,500),"generation");
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
		generation.display();
	}
	
	return 0;
}