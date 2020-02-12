#include <SFML\Graphics.hpp>

//Temporary namespace to avoid typing sf::
using namespace sf;

int main() {

	//Making video mode object with window size indication
	VideoMode vmScreenSize(1280, 760);
	//Create window for game
	RenderWindow window(vmScreenSize, "Racing Game!", Style::Default);

	//Game Loop
	while (window.isOpen())
	{
		//////////////// Handling  Input Section////////////////////
		
		//Handling Event for Window Closing
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		//////////////// Scence Update Section////////////////////


		//////////////// Drawing on Screen Section////////////////////

	}

	
	return 0;

}