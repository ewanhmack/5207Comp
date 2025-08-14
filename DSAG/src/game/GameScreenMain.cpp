#include <GameScreenMain.h>
#include <Bird.h>
#include <Brick.h>
#include<Pig.h>
#include<Foreground.h>
#include <Slingshot.h>
#include <deque> 

///////////////////////////////////////
// Constructor for the Screen
///////////////////////////////////////
LJMU::LJMUGameScreenMain::LJMUGameScreenMain()
	: bird1(1, sf::Texture(), sf::Vector2f(0.0f, 0.0f)),//Initialising bird
	pig1(1, sf::Texture(), sf::Vector2f(0.0, 0.0f)),
	_score(0)
{
	//Nothing Dynamic to initialise
}

////////////////////////////////////////
// Destructor for the Screen
////////////////////////////////////////
LJMU::LJMUGameScreenMain::~LJMUGameScreenMain()
{
	//Nothing Dynamic to Destruct. 
}

//-------------SCREEN IMPLEMENTATION--------------------------------------

/////////////////////////////////////////
//Load the Content of the Level
//And assign two player controls. 
/////////////////////////////////////////
void LJMU::LJMUGameScreenMain::loadContent()
{
	// Get access to the Window via the Weak Pointer
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();
	twndw.setMouseCursorVisible(true);

	// Set FPS limit
	twndw.setFramerateLimit(60); // Set frame rate to 60 FPS

	// Get the size of the window
	sf::Vector2f wndSize(static_cast<float>(twndw.getSize().x), static_cast<float>(twndw.getSize().y));

	// Initialise the game world with the window size
	this->_game_world.create(wndSize);

	// Load bird texture
	sf::Texture birdTexture;
	if (!birdTexture.loadFromFile("bird.png")) {
		//std::cerr << "Failed to load bird texture" << std::endl;
	}
	// Create bird and set position to center of screen
	bird1 = Bird(1, birdTexture, sf::Vector2f(wndSize.x / 2.f, wndSize.y / 2.f));

	// Load pig texture
	sf::Texture pigTexture;
	if (!pigTexture.loadFromFile("pig.png")) {
		//std::cerr << "Failed to load pig texture" << std::endl;
	}
	// Create pig
	pig1 = Pig(1, pigTexture, sf::Vector2f(1080.0f, 435.0f));

	// Load foreground texture
	sf::Texture* foregroundTexture = new sf::Texture();
	if (!foregroundTexture->loadFromFile("Backgrounds/da_foreground.png")) {
		//std::cerr << "Failed to load foreground texture" << std::endl;
	}


	std::vector<std::pair<sf::Vector2f, float>> brickPositionsAndRotations = {
		//Vertical Platforms
		{sf::Vector2f(1275.0f, 615.0f), 0.0f},  // First platform
		{sf::Vector2f(1350.0f, 615.0f), 0.0f},  // Second platform
		{sf::Vector2f(1425.0f, 615.0f), 0.0f},  // Third platform
		{sf::Vector2f(1500.0f, 615.0f), 0.0f},  // Fourth platform

		{sf::Vector2f(1375.0f, 480.0f), 0.0f},  // Fifth platform

		//Horizontal Platforms
		{sf::Vector2f(1335.0f, 550.0f), 90.0f },  // First platform
		{sf::Vector2f(1435.0f, 550.0f), 90.0f},  // Second platform
		{sf::Vector2f(1375.0f, 460.0f), 90.0f},  // Third platform


	};

	// Updated positions for the pigs
	std::vector<std::pair<sf::Vector2f, float>> pigPositionsAndRotations = {
		{sf::Vector2f(1310.0f, 635.0f), 0.0f},  // Between first and second vertical blocks
		{sf::Vector2f(1390.0f, 635.0f), 0.0f},  // Between second and third vertical blocks
		{sf::Vector2f(1470.0f, 635.0f), 0.0f},  // Between third and fourth vertical blocks

		{sf::Vector2f(1335.0f, 430.0f), 0.0f},   // On top of horizontal block (left side)
		{sf::Vector2f(1425.0f, 430.0f), 0.0f}   // On top of horizontal block (Right side)
	};

	// Positions and rotations for the birds remain unchanged
	std::vector<std::pair<sf::Vector2f, float>> birdPositionAndRotation = {
		{sf::Vector2f(35.0f,  615.0f), 0.0f},  // First bird
		{sf::Vector2f(95.0f,  615.0f), 0.0f},  // Second bird
		{sf::Vector2f(155.0f, 615.0f), 0.0f},  // Third bird
		{sf::Vector2f(215.0f, 615.0f), 0.0f},  // Fourth bird
		{sf::Vector2f(275.0f, 615.0f), 0.0f},   // Fifth bird
	};
	std::vector<std::pair<sf::Vector2f, float>> ForegroundPositionsAndRotations = {
		{sf::Vector2f(600.0f, 300.0f), 0.0f},  
	};

	std::vector<std::pair<sf::Vector2f, float>> SlingshotPositionsAndRotations = {
		{sf::Vector2f(290.0f, 570.0f), 0.0f}
	};
	// Call setupBricks with positions and rotations
	this->setupBricks(brickPositionsAndRotations);
	this->setupBirds(birdPositionAndRotation);
	this->setupPigs(pigPositionsAndRotations);
	this->setupForeground(ForegroundPositionsAndRotations);
	this->setupSlingshot(SlingshotPositionsAndRotations);
}
//////////////////////////////////////////
//  Handle any input events that have 
//  arrived on this screen.
//////////////////////////////////////////
void LJMU::LJMUGameScreenMain::handleEvent(const sf::Event& pevent)
{
	sf::Event tevent = pevent;

	switch (tevent.type)
	{
	case sf::Event::MouseButtonPressed:
	{
		if (tevent.mouseButton.button == sf::Mouse::Left)
		{
			// Check if there are any birds left to shoot
			bool hasBirdsLeft = false;
			for (const auto& bird : this->_bird)
			{
				if (!bird.hasBeenFired)
				{
					hasBirdsLeft = true;
					break;
				}
			}

			if (hasBirdsLeft)
			{
				// Start dragging the slingshot
				sf::Vector2i mousePos = sf::Mouse::getPosition(this->getLJMUSFMLManager().lock()->getWindow());
				for (auto& slingshot : this->_slingshot)
				{
					slingshot.startDragging(mousePos);
					// Assign the first inactive bird in the vector to the slingshot
					for (auto& bird : this->_bird)
					{
						if (!bird.isActive())
						{
							slingshot.setProjectile(&bird); // Pass the Bird object
							break;
						}
					}
				}
			}
		}
		break;
	}
	case sf::Event::MouseMoved:
	{
		// Update dragging position of the slingshot
		sf::Vector2i mousePos = sf::Mouse::getPosition(this->getLJMUSFMLManager().lock()->getWindow());
		for (auto& slingshot : this->_slingshot)
		{
			slingshot.updateDragging(mousePos);
		}
		break;
	}
	case sf::Event::MouseButtonReleased:
	{
		if (tevent.mouseButton.button == sf::Mouse::Left)
		{
			// Release the slingshot to launch the bird
			for (auto& slingshot : this->_slingshot)
			{
				slingshot.release();
			}
		}
		break;
	}
	case sf::Event::KeyPressed:
	{
		if (tevent.key.code == sf::Keyboard::Space)
		{
			// Move all birds when spacebar is pressed (Special ability?)
			for (auto& bird : this->_bird)
			{
				bird.setVelocity(sf::Vector2f(50.0f, 0.0f)); // Start moving the bird
			}
		}
		break;
	}
	}
}
//////////////////////////////////////////
//  Secondary update function. 
//////////////////////////////////////////
void LJMU::LJMUGameScreenMain::bgUpdate(sf::Time & ptpf, sf::Time & ptotal, bool pcovered)
{
	//Since we only have one screen, we won't use this, but we might in a multi-screen solution!
}

//////////////////////////////////////////
//  Update the State of the Screen.
//////////////////////////////////////////
void LJMU::LJMUGameScreenMain::update(sf::Time& ptpf, sf::Time& ptotal)
{
	std::cout << isGameOver() << std::endl; // Debugging line to check if game is over
	if (isGameOver())
	{
		this->triggerGameOver();
		return; // Skip update if game is over
	}

	if (this->_bird.empty())
	{
		this->triggerGameOver();
		return; // Skip update if there are no birds
	}

	// Get the update times
	const float ttpf = ptpf.asSeconds();
	const float ttotal = ptotal.asSeconds();

	// Update all birds
	for (auto it = this->_bird.begin(); it != this->_bird.end();)
	{
		it->update(this->_brick, this->_pig); // Update bird logic

		// Check if the bird has been fired and is no longer active
		if (it->hasBeenFired && !it->isActive())
		{
			it = this->_bird.erase(it); // Use the iterator returned by erase
		}
		else
		{
			if (!this->_bird.empty()) {
				++it; // Move to the next bird
			}
		}
	}

	// Trigger game over if no birds remain
	if (this->_bird.empty())
	{
		this->triggerGameOver();
		return;
	}

	// Update slingshot
	for (auto& slingshot : this->_slingshot)
	{
		slingshot.update();
	}

	// -------------------- Update HUD --------------------
	/*if (!this->_bird.empty())
	{
		// Update the bird's position in the HUD
		// KEPT FOR DEBUGGING
		sf::Vector2f birdPosition = this->_bird.front().getPosition();
		this->_game_world.WorldHUD[LJMUSIHUD::TIME].setString("Bird Position: X=" +
			std::to_string(static_cast<int>(birdPosition.x)) +
			", Y=" +
			std::to_string(static_cast<int>(birdPosition.y)));
		// This can be duplicated for a score system and the pig function, just need variables to count it
	}
	*/

	// Update the score based on the number of pigs and bricks destroyed
	for (auto& brick : this->_brick)
	{
		if (!brick.isActive() && brick.Scored == false) // If the brick is destroyed
		{
			_score += 10; // Add 10 points
			brick.Scored = true; // Mark the brick as scored
		}
	}

	for (auto& pig : this->_pig)
	{
		if (!pig.isActive() && pig.Scored == false) // If the pig is destroyed
		{
			_score += 20; // Add 20 points
			pig.Scored = true; // Mark the pig as scored

		}
	}

	// Count active pigs
	int activePigs = 0;
	for (const auto& pig : this->_pig)
	{
		if (pig.isActive())
		{
			activePigs++;
		}
	}

	// Count active birds
	int activeBirds = 0;
	for (const auto& bird : this->_bird)
	{
		if (!bird.hasBeenFired)
		{
			activeBirds++;
		}
		else if (bird.hasBeenFired)
		{
			activeBirds--;
		}
	}

	// Update the HUD with the number of pigs left and score
	this->_game_world.WorldHUD[LJMUSIHUD::LIVES].setString("Birds Left: " + std::to_string(activeBirds));
	this->_game_world.WorldHUD[LJMUSIHUD::SCORE].setString("Pigs Left: " + std::to_string(activePigs));
	this->_game_world.WorldHUD[LJMUSIHUD::TIME].setString("Score: " + std::to_string(_score));
}
//////////////////////////////////////////
//  Holds the rendering logic to draw 
//  the screen.
//////////////////////////////////////////
void LJMU::LJMUGameScreenMain::render()
{
	// Get access to the window
	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();

	// Render the gameplay layers
	twndw.setView(this->_game_world.CameraGame);

	// Draw the level backgrounds
	for (auto& tbg : this->_game_world.WorldLevel)
		twndw.draw(tbg);

	// Render the birds
	for (auto& bd : this->_bird)
	{
		if (bd.isRolling)
		{
			// Update the bird's sprite to reflect rolling
			bd.BDsprite.setPosition(bd.getPosition());
			bd.BDsprite.setRotation(bd.getRotation());
		}
		twndw.draw(bd.BDsprite);
	}

	// Render active pigs only
	for (auto& pg : this->_pig)
	{
		if (pg.isActive()) // Only draw active pigs
		{
			twndw.draw(pg.sprite);
		}
	}

	// Render other elements (bricks, slingshot, foreground, etc.)
	for (auto& br : this->_brick)
	{
		if (br.isActive()) // Only draw active bricks
		{
			twndw.draw(br.BrickSprite);
		}
	}

	for (auto& fg : this->_foreground)
		twndw.draw(fg.sprite);

	for (auto& ss : this->_slingshot)
	{
		ss.render(twndw);
		ss.drawTrajectory(twndw); // Draw the trajectory line
	}

	// -------------------- Render HUD --------------------
	// Switch to the HUD camera
	twndw.setView(this->_game_world.CameraHUD);

	// Draw HUD elements
	for (auto& hudElement : this->_game_world.WorldHUD)
	{
		twndw.draw(hudElement.second); // Draw each HUD text element
	}

	// -------------------- Render Game Over Screen --------------------
	if (isGameOver())
	{
		this->triggerGameOver();
	}


}
///////////////////////////////////////////
//  Clean up the content of the Level
//////////////////////////////////////////
void LJMU::LJMUGameScreenMain::cleanup()
{
	this->_brick.clear();
	this->_game_world.destroy();
	this->_pig.clear();
	this->_bird.clear();
	this->_foreground.clear();
	this->_slingshot.clear();
}

//---------------GAME LOGIC FUNCTIONS-------------------------------------------------

///////////////////////////////////////
// Helper function for easy keyboard 
// control.
///////////////////////////////////////
void LJMU::LJMUGameScreenMain::handleInput(sf::Keyboard::Key pkey, bool ppressed)
{
	//Get Access to the Window 
	auto ttotal = this->getLJMUSFMLManager().lock()->getTotalElapsedTime();
}

void LJMU::LJMUGameScreenMain::setupBricks(const std::vector<std::pair<sf::Vector2f, float>>& positionsAndRotations)
{
	// Clear the existing bricks
	this->_brick.clear();

	// Load the texture for the bricks
	sf::Sprite spbrick;
	spbrick.setTexture(this->_game_world.ResourceSprites.get(LJMUSIAssets::BRICK_ONE));
	spbrick.setScale(sf::Vector2f(0.15f, 0.25f)); 
	sf::setOriginCentre(spbrick);

	// Loop through positions and rotations
	for (const std::pair<sf::Vector2f, float>& pair : positionsAndRotations)
	{
		const sf::Vector2f& pos = pair.first;   // Access the position
		float rotation = pair.second;           // Access the rotation

		Brick Tgo(spbrick, pos, rotation);      // Pass position and rotation to the Brick constructor
		this->_brick.push_back(Tgo);            // Add to the vector of bricks
	}
}

void LJMU::LJMUGameScreenMain::setupBirds(const std::vector<std::pair<sf::Vector2f, float>>& positionsAndRotations)
{
	this->_bird.clear();

	sf::Sprite spBird;
	spBird.setTexture(this->_game_world.ResourceSprites.get(LJMUSIAssets::BIRD_ANIM));
	spBird.setScale(sf::Vector2f(0.2f, 0.2f));
	sf::setOriginCentre(spBird);

	for (const std::pair<sf::Vector2f, float>& pair : positionsAndRotations)
	{
		const sf::Vector2f& pos = pair.first;
		float rotation = pair.second;

		Bird Tbd(spBird, pos, rotation);
		//Tbd.setVelocity(sf::Vector2f(0.1f, -0.005f)); // Set velocity to move right (remove this code at some point)
		this->_bird.push_back(Tbd);
	}
}
void LJMU::LJMUGameScreenMain::setupPigs(const std::vector<std::pair<sf::Vector2f, float>>& positionsAndRotations)
{
	this->_pig.clear();

	sf::Sprite spPig;
	spPig.setTexture(this->_game_world.ResourceSprites.get(LJMUSIAssets::PIG_ANIM));
	spPig.setScale(sf::Vector2f(0.1f, 0.1f)); 
	sf::setOriginCentre(spPig);

	// Loop through positions and rotations
	for (const std::pair<sf::Vector2f, float>& pair : positionsAndRotations)
	{
		const sf::Vector2f& pos = pair.first;
		float rotation = pair.second;

		// Create pig object and pass position and rotation
		Pig Tpg(spPig, pos, rotation);
		this->_pig.push_back(Tpg);
	}
}

void LJMU::LJMUGameScreenMain::setupForeground(const std::vector<std::pair<sf::Vector2f, float>>& positionsAndRotations)
{
	this->_foreground.clear();

	sf::Sprite spForeground;
	spForeground.setTexture(this->_game_world.ResourceSprites.get(LJMUSIAssets::BG_ONE));
	spForeground.setScale(sf::Vector2f(3.0f, 3.0f)); 
	sf::setOriginCentre(spForeground);

	// Loop through positions and rotations
	for (const std::pair<sf::Vector2f, float>& pair : positionsAndRotations)
	{
		const sf::Vector2f& pos = pair.first;
		float rotation = pair.second;

		// Create Foreground object and pass position and rotation
		Foreground Tfg(spForeground, pos, rotation);
		this->_foreground.push_back(Tfg);
	}
}

void LJMU::LJMUGameScreenMain::setupSlingshot(const std::vector<std::pair<sf::Vector2f, float>>& positionsAndRotations)
{
	this->_slingshot.clear();

	sf::Sprite spSlingshot;
	spSlingshot.setTexture(this->_game_world.ResourceSprites.get(LJMUSIAssets::SLING_ANIM));
	spSlingshot.setScale(sf::Vector2f(0.7f, 0.7f));
	sf::setOriginCentre(spSlingshot);

	// Loop through positions and rotations
	for (const std::pair<sf::Vector2f, float>& pair : positionsAndRotations)
	{
		const sf::Vector2f& pos = pair.first;
		float rotation = pair.second;

		// Create Foreground object and pass position and rotation
		Slingshot Tss(spSlingshot, pos, rotation);
		this->_slingshot.push_back(Tss);
	}
}

bool LJMU::LJMUGameScreenMain::isGameOver()
{
	// Check if there are any active pigs
	// Count active pigs
	int activePigs2 = 0;
	for (const auto& pig : this->_pig)
	{
		if (pig.isActive())
		{
			activePigs2++;
		}
	}

	if (activePigs2 > 0)
	{
		return false; // Game is not over if there are active pigs
	}
	else if (activePigs2 == 0)
		return true;

	// Check if there are any birds left to shoot
	for (const auto& bird : this->_bird)
	{
		if (!bird.hasBeenFired)
		{
			return false; // Game is not over if there are birds left
		}
	}

	return true; // Game is over if no active pigs and no birds left
}

void LJMU::LJMUGameScreenMain::triggerGameOver()
{
	// Display the game over screen
	sf::Text gameOverText;
	gameOverText.setFont(this->_game_world.ResourceFonts.get(LJMUSIFont::RETRO));
	gameOverText.setString("Game Over\nScore: " + std::to_string(_score));
	gameOverText.setCharacterSize(50);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setStyle(sf::Text::Bold);
	gameOverText.setPosition(400.0f, 300.0f); // Center the text

	auto& twndw = this->getLJMUSFMLManager().lock()->getWindow();
	twndw.clear();
	twndw.draw(gameOverText);
	twndw.display();;
}
