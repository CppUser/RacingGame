#include <SFML\Graphics.hpp>
#include <sstream>

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
	//TODO: Set Median Line (Moving on Player Acceleration
	roadSprite.setPosition(0, 700);

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
	playerCarSprite.setPosition(40, 800);
	//Scaling Sprite to make car little bit smaller
	playerCarSprite.setScale(0.8, 0.8);

	//Attributes for Player Car
	//Does the player car moce ?
	bool plCarActive = false;
	//How fast does player car move?
	float plCarSpeed = 0.0f;

	//TODO:Add More Cars for player to choose

	//TODO:Add Multiple Opstical cars to avoid while driving
	//Setting Texture for obsticals
	Texture obsTextures;
	Sprite obsSprite;

	obsTextures.loadFromFile("resources/Sprites/Cars/fer1.png");
	obsSprite.setTexture(obsTextures);
	obsSprite.setPosition(2000, 625);
	//obsSprite.setScale(0.05, 0.05);
	//Obs Attributes
	bool obsActive = false;
	float obsSpeed = 0.0f;

	//*********Frame rate section**********//
	//Variable that controls time
	Clock clock;

	//Tracker for game state
	bool paused = true;


	//**************Declaring and Positioning HUD Section*************//
	int score = 0;
	int distance = 0;

	Text displayMessage;
	Text scoreText,distanceText;

	//Setting up Text and Fonts
	Font font;
	font.loadFromFile("resources/Fonts/KrunchBold.ttf");

	//binding font to text messages variables
	displayMessage.setFont(font);
	scoreText.setFont(font);
	distanceText.setFont(font);

	//Assigning message
	displayMessage.setString("Press Enter to Start");
	scoreText.setString("Score = 0");
	distanceText.setString("Distance = 0");

	//Set Font Size
	displayMessage.setCharacterSize(75);
	scoreText.setCharacterSize(45);
	distanceText.setCharacterSize(45);

	//Filling text with color
	displayMessage.setFillColor(Color::Red);
	scoreText.setFillColor(Color::White);
	distanceText.setFillColor(Color::White);

	//Positioning text on screen
	FloatRect textRect = displayMessage.getLocalBounds();
	displayMessage.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	displayMessage.setPosition(1920 / 2.0f, 670);
	scoreText.setPosition(20, 20);
	distanceText.setPosition(1500, 20);

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
		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			paused = false;
		}

		//////////////// Scence Update Section////////////////////

		if (!paused)
		{
			//Measuring time(clock.restart - restarts the time)
			Time dt = clock.restart();

			//***************** DECORATION ANIMATION SECTION *****************//
			//Setting up obsticals
			if (!obsActive)
			{
				//Randomly generate speed for obsticals
				srand((int)time(0));
				obsSpeed = (rand() % 200) + 600;

				srand((int)time(0));
				//Generate random number between 625 to 724
				float height = (rand() % 100) + 625;
				obsSprite.setPosition(2000, height);
				obsActive = true;
			}
			else
				//Moving obs toward player
			{
				obsSprite.setPosition(obsSprite.getPosition().x - (obsSpeed * dt.asSeconds()), obsSprite.getPosition().y);

				//Check if obsSpite reached left hand edge of the screen
				if (obsSprite.getPosition().x < -600)
				{
					//Reset obstical for next frame
					obsActive = false;
				}
			}
			//TODO: Animate rest of the resources

			//TODO: Temporary location for updating score text
			//Update the score text
			std::stringstream ss,ds;
			ss << "Score = " << score;
			ds << "Distance = " << distance;
			scoreText.setString(ss.str());
			distanceText.setString(ds.str());

			
		}// End of Tracking game state 


		//////////////// Drawing on Screen Section/////////////////

		//Clearing frame buffer
		//And drawing some backgroung color(RED)
		window.clear();

		//Draing Game Assets
		window.draw(backgroundSprite);
		window.draw(roadSprite);
		/* //TODO: Set Condition for obstical sprite and Player Sprite to draw them in order which sprite is higher in pixel dence
		to give them look */
		window.draw(obsSprite);
		window.draw(playerCarSprite);

		//Draw the score
		window.draw(scoreText);
		//Draw Distance
		window.draw(distanceText);
		if (paused)
		{
			//Display start HUD message
			window.draw(displayMessage);
		}

		//Displaying everithing that have been drawn in buffer
		window.display();
	}

	return 0;
}