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
	backgroundSprite.setScale(1, 0.698);
	
	/*
	    *****Road******
	*/
	//Placeholder for Road textures in GPU 
	Texture roadTexture;
	//Place Holder for roadTexture Sprite
	Sprite roadSprite;

	//Loading Texture Images from file
	roadTexture.loadFromFile("resources/Sprites/Road/RoadClassicDark.png");
	//Attaching texture to the sprite
	roadSprite.setTexture(roadTexture);
	//Positioning Sprite in window to be scaled full screen(0,0)
	//TODO: Set Position of the Sprite to see the road
	roadSprite.setPosition(0,700);
	
	
	/*
	    *****Cars******
	*/

	//TODO: Polish Player Car Better
	//Placeholder for Car textures in GPU
	Texture playerCarTexture;
	//Place Holder for carTexture Sprite
	Sprite playerCarSprite;

	//Loading Texture Images from file
	playerCarTexture.loadFromFile("resources/Sprites/Cars/Audi.png");
	//Attaching texture to the sprite
	playerCarSprite.setTexture(playerCarTexture);
	//Positioning Sprite in window to be scaled full screen(0,0)
	//TODO: Set Position of the Sprite to see the road
	playerCarSprite.setPosition(40,800);
	//Scaling Sprite to make car little bit smaller
	playerCarSprite.setScale(0.8,0.8);
	



	//TODO:Add More Cars




	/*
	**************************
	  Game Loop
	**************************	
	*/
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
		window.draw(roadSprite);
		window.draw(playerCarSprite);

		//Displaying everithing that have been drawn in buffer
		window.display();


	}

	
	return 0;

}