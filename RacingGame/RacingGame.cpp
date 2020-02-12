#include <SFML\Graphics.hpp>

//Temporary namespace to avoid typing sf::
using namespace sf;

int main() {

	//Making video mode object with window size indication
	VideoMode vmScreenSize(1920, 1080);
	//Create window for game
	RenderWindow window(vmScreenSize, "Racing Game!", Style::Default);

	////////////Preparing Images (Textures and Sprites)/////////////////
	
	/*
	    *****Backgound******
	*/
	//Placeholder for textures in GPU
	Texture backgroundTexture;
	//Place Holder for backgroundTexture Sprite
	Sprite backgroundSprite;

	//Loading Texture Images from file
	backgroundTexture.loadFromFile("resources/Sprites/Background/ArtCityBackground.jpg");
	//Attaching texture to the sprite
	backgroundSprite.setTexture(backgroundTexture);
	//Positioning Sprite in window to be scaled full screen(0,0)
	//TODO: Set Position of the Sprite to see the road
	backgroundSprite.setPosition(0, 0);
	


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


		//////////////// Drawing on Screen Section/////////////////

		//Clearing frame buffer
		//And drawing some backgroung color(RED)
		window.clear();

		//Draing Game Assets
		window.draw(backgroundSprite);

		//Displaying everithing that have been drawn in buffer
		window.display();


	}

	
	return 0;

}