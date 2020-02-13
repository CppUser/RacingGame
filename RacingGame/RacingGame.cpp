#include <SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include <sstream>

//Temporary namespace to avoid typing sf::
using namespace sf;

//Ongoing traffic function
void updateTraffic(int objects);

const int NUM_CARS = 8;
Sprite trafficSprite[NUM_CARS];

//Enum for player vehicle control
enum class side { TOP, MIDDLE, BOTTOM, NONE };
side trafficPosition[NUM_CARS];

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
	//Indicating on which side player starts
	side playerCarSide = side::BOTTOM;
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
	Text scoreText, distanceText;

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

	//************Traffic Preporation Section***************//
	Texture trafficTexutre;
	trafficTexutre.loadFromFile("resources/Sprites/Cars/fer1.png");

	//TODO: For Multiple obsticalse and HUD for choosing cars use this method
	//Set texture for each traffic Sprite
	for (int i = 0; i < NUM_CARS; i++)
	{
		trafficSprite[i].setTexture(trafficTexutre);
		trafficSprite[i].setPosition(1500, 625);

		//setting sprites origin to center of the texture size
		//To change direction of the traffic without adding additional sprite for different direction
		trafficSprite[i].setOrigin(200, 100);
	}

	//***** Player Input Handling Declaration Section *******//
	bool acceptInput = false;

	//******************SOUND and MUSIC SECTION***********//
	//TODO: Add Sound Effects and Music to game(sound effect for honk car on close calls)
	//TODO: Add Sound Effect for each car
	//TODO: Add Driving car Sound Effect and Turn wheel effect
	//Preparing the sound
	//Player Car Shound
	SoundBuffer drivingCarSound;
	//drivingCarSound.loadFromFile("resources/soundEffects/drivingCarEffect.wav");
	Sound driving;
	driving.setBuffer(drivingCarSound);

	//Player Car Turning Sound
	SoundBuffer turningCarEffect;
	//turningCarEffect.loadFromFile("resources/soundEffects/turningCarEffect.wav");
	Sound turnEffect;
	turnEffect.setBuffer(turningCarEffect);

	//Player Car Crash Sound
	SoundBuffer crashedCarEffect;
	//crashedCarEffect.loadFromFile("resources/soundEffects/crashedCarEffect.wav");
	Sound crashEffect;
	crashEffect.setBuffer(crashedCarEffect);


	/*
	**************************
	  Game Loop
	**************************
	*/
	while (window.isOpen())
	{
		//////////////// Handling  Input Section////////////////////
		//Applying event system
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !paused)
			{
				//Listen for key press again
				acceptInput = true;
			}
		}

		//Handling Event for Window Closing
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			paused = false;
			score = 0;
			distance = 0;

			//Clear screen from traffic and start over again in same position
			for (int i = 1; i < NUM_CARS; i++)
			{
				trafficPosition[i] = side::NONE;
			}

			//Move Player into position
			playerCarSprite.setPosition(40, 800);
			acceptInput = true;
		}
		//Wrapping up player input control 
		//TODO: Fix Issue of handling input (Car is skipping middle line)
		if (acceptInput)
		{
			//Handling pressing to right arrow
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				//Find in which position player is
				if (playerCarSide == side::TOP)
				{
					
					playerCarSide = side::MIDDLE;
					playerCarSprite.setPosition(40, 700);
					//TODO:Add turning sound effect
					turnEffect.play();
				}
				 else if (playerCarSide == side ::MIDDLE)
				{
					playerCarSide = side::BOTTOM;
					playerCarSprite.setPosition(40, 800);
					//TODO:Add turning sound effect
					turnEffect.play();
				}
				 else
				{
					playerCarSide = side::BOTTOM;
					playerCarSprite.setPosition(40, 800);
					turnEffect.play();
					acceptInput = false;
				}
				//updateTraffic(score);
			}
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				//Find in which position player is
				if (playerCarSide == side::BOTTOM)
				{
					playerCarSide = side::MIDDLE;
					playerCarSprite.setPosition(40, 700);
					//TODO:Add turning sound effect
					turnEffect.play();
				}
				else if (playerCarSide == side::MIDDLE)
				{
					playerCarSide = side::TOP;
					playerCarSprite.setPosition(40, 600);
					//acceptInput = false;
					//TODO:Add turning sound effect
					turnEffect.play();
				}
				else
				{
					playerCarSide = side::TOP;
					playerCarSprite.setPosition(40, 600);
					acceptInput = false;
					//TODO:Add turning sound effect
					turnEffect.play();
				}
				//updateTraffic(score);
			}
		}

		//////////////// Scence Update Section////////////////////

		if (!paused)
		{
			//TODO:Add driving sound effect
			driving.play();
			//Measuring time(clock.restart - restarts the time)
			Time dt = clock.restart();

			//***************** DECORATION ANIMATION SECTION *****************//

			////TODO: Compare Random Generating vs Enum specified location
			if (!obsActive)
			{
				//Generatinc Trafic in scence
				for (int i = 0; i < NUM_CARS; i++)
				{
					float lenght = i * 150;
					//Setting up Random Speed For Traffic
					srand((int)time(0));
					obsSpeed = (rand() % 200) + 600;
					if (trafficPosition[i] == side::TOP)
					{
						//Move the traffic sprites to the left side
						trafficSprite[i].setPosition(1500 - lenght, 625);
						//Rotate Sprite 180 degree
						//trafficSprite[i].setRotation(180);
						
					}
					else if (trafficPosition[i] == side::MIDDLE)
					{
						trafficSprite[i].setPosition(1500 - lenght, 725);
					}
					else if (trafficPosition[i] == side::BOTTOM)
					{
						trafficSprite[i].setPosition(1500 - lenght, 825);
					}
					else
					{
						//HIDE THE Traffic
						trafficSprite[i].setPosition(2500, lenght);
					}
				}
				obsActive = true;
			}
			//Move the traffic
			else
			{
				for (int i = 0; i < NUM_CARS; i++) {
					if (trafficPosition[i] == side::TOP)
					{
						trafficSprite[i].setPosition(trafficSprite[i].getPosition().x - (obsSpeed * dt.asSeconds()), trafficSprite[i].getPosition().y);
					}
					else if (trafficPosition[i] == side::MIDDLE)
					{
						trafficSprite[i].setPosition(trafficSprite[i].getPosition().x - (obsSpeed * dt.asSeconds()), trafficSprite[i].getPosition().y);
					}
					else if (trafficPosition[i] == side::BOTTOM)
					{
						trafficSprite[i].setPosition(trafficSprite[i].getPosition().x - (obsSpeed * dt.asSeconds()), trafficSprite[i].getPosition().y);
					}
				}
			}

			////Setting up obsticals
			//if (!obsActive)
			//{
			//	////Randomly generate speed for obsticals
			//	//srand((int)time(0));
			//	//obsSpeed = (rand() % 200) + 600;

			//	//srand((int)time(0));
			//	////Generate random number between 625 to 724
			//	//float height = (rand() % 100) + 625;
			//	//obsSprite.setPosition(2000, height);
			//	obsActive = true;
			//}
			//else
			//	//Moving obs toward player
			//{
			//	obsSprite.setPosition(obsSprite.getPosition().x - (obsSpeed * dt.asSeconds()), obsSprite.getPosition().y);

			//	//Check if obsSpite reached left hand edge of the screen
			//	if (obsSprite.getPosition().x < -600)
			//	{
			//		//Reset obstical for next frame
			//		obsActive = false;
			//	}
			//}
			//TODO: Animate rest of the resources

			//TODO: Temporary location for updating score text
			//Update the score text
			std::stringstream ss, ds;
			ss << "Score = " << score;
			ds << "Distance = " << distance;
			scoreText.setString(ss.str());
			distanceText.setString(ds.str());
			
			//TODO: Polish Collision Detecting and fix minor bugs
			//Handling Collision Detection (Crash)
			if (trafficPosition[5] == playerCarSide)
			{
				//Crash
				paused = true;
				acceptInput = false;
				//TODO: ADD Sprite of  crashed car and display it
				//crashedCarSprite.setPosition(Position of the crash);
				//hide normal car sprite
				// playerCarSprite.setPosition(out of screen)
				
				//Changing text on HUD screen
				displayMessage.setString("Crashed!!!");

				//Positioning text on middle screen
				FloatRect textRect = displayMessage.getLocalBounds();
				displayMessage.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				displayMessage.setPosition(1920 / 2.0f, 670);

				//TODO:Add Crash sound effect
				crashEffect.play();
				
			}

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

		//TODO:Test static obstical vs random
		//Random drawing for obsticals traffic
		//window.draw(obsSprite);
		//Static drawing for obstical Traffic
		for (int i = 0; i < NUM_CARS; i++)
		{
			window.draw(trafficSprite[i]);
		}

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

void updateTraffic(int objects)
{
	//Move traffic sprites down one position
	for (int i = NUM_CARS - 1; i > 0; i--)
	{
		trafficPosition[i] = trafficPosition[i - 1];
	}

	//Spawn New trafficSprites at position 0
	srand((int)time(0) + objects);
	int r = (rand() % 5);
	switch (r)
	{
	case 0:
		trafficPosition[0] = side::TOP;
		break;
	case 1:
		trafficPosition[0] = side::MIDDLE;
		break;
	case 2:
		trafficPosition[0] = side::BOTTOM;
		break;

	default:
		trafficPosition[0] = side::NONE;

		break;
	}
}