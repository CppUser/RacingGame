#include <SFML\Graphics.hpp>

int main() {

	sf::Vector2f viewSize(1024, 768);

	sf::VideoMode vm(viewSize.x, viewSize.y);

	sf::RenderWindow window(vm,"Racing Game", sf::Style::Default);
	sf::RectangleShape rect(sf::Vector2f(500.0f, 300.0f));   rect.setFillColor(sf::Color::Yellow);   rect.setPosition(viewSize.x / 2, viewSize.y / 2);   rect.setOrigin(sf::Vector2f(rect.getSize().x / 2, rect.getSize().y / 2));

	while (window.isOpen())
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		window.clear(sf::Color::Red);

		window.draw(rect);
		//Render Game objects
		window.display();
	}
	return 0;

}