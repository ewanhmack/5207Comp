#ifndef __GAME_SCREEN_MAIN_H_
#define __GAME_SCREEN_MAIN_H_

//Include our Framework Library
#include <LJMUPCH.h>
#include <GameManager.h>
#include <Bird.h>
#include <Brick.h>
#include <Pig.h>
#include <Foreground.h>
#include <Slingshot.h>
//Include our Game Application Classes


namespace LJMU
{
	///////////////////////////////
	// Implementation of the main
	// gameplay screen using our
	// Screen Interface Class. 
	//
	// AUTHOR:  DR CHRIS CARTER
	// DATE:    01/06/2017
	///////////////////////////////
	class LJMUGameScreenMain : public sf::ILJMUScreenBase
	{
		//---------CONSTANTS-------------------------------------------------------
		static const unsigned int   HUD_SCALE = 48;   //Constant to hold the scale of the HUD

		//-----------CONSTRUCTOR/DESTRUCTOR----------------------------------
	public:
		LJMUGameScreenMain();	//Default Constructor
		~LJMUGameScreenMain();	//Default Destructor

	public:
		//-----------FUNCTION OVERRIDES/INTERFACE IMPLEMENTATION-------------
		virtual void    loadContent() override;
		virtual void	handleEvent(const sf::Event& pevent) override;
		virtual void    bgUpdate(sf::Time& ptpf, sf::Time& ptotal, bool pcovered = false) override;
		virtual void	update(sf::Time& ptpf, sf::Time& ptotal) override;
		virtual void	render() override;
		virtual void    cleanup() override;

	public:
		//-----------PUBLIC FUNCTIONS----------------------------------------
		void setupBricks(const std::vector<std::pair<sf::Vector2f, float>>& positionsAndRotations);
		void setupBirds(const std::vector<std::pair<sf::Vector2f, float>>& positionsAndRotations);
		void setupPigs(const std::vector<std::pair<sf::Vector2f, float>>& positionsAndRotations);
		void setupForeground(const std::vector<std::pair<sf::Vector2f, float>>& positionsAndRotations);
		void setupSlingshot(const std::vector<std::pair<sf::Vector2f, float>>& positionsAndRotations);

		bool isGameOver();
		void triggerGameOver();

		//-----------PROTECTED FUNCTIONS-------------------------------------
	protected:
		void handleInput(sf::Keyboard::Key pkey, bool ppressed); //Handle Keyboard Events
		

	public:

		//-----------GETTERS/SETTERS-----------------------------------------

	protected:
		//-----------CLASS MEMBERS-------------------------------------------
		LJMUGameManager _game_world;
		
		Bird bird1; //Adding bird
		Brick brick1; //Adding Brick
		Pig pig1; //Adding pig
		Slingshot slingshot1; //Adding slingshot

		std::vector<Bird> _bird;
		std::vector<Brick> _brick;
		std::vector<Pig> _pig;
		std::vector<Foreground> _foreground;
		std::vector<Slingshot> _slingshot;
		int _score;
	};
}
#endif