#include "LJMUGameBase.h"
#include "GameScreenMain.h"
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

/////////////////////////////////////////
// Entry Point to our Application
// In this case it just needs to start
// our SFML Application.
//
// AUTHOR:  DR CHRIS CARTER
/////////////////////////////////////////
#ifdef _DEBUG

bool fileExists(const std::string& filePath) {
	std::ifstream file(filePath);
	return file.good();
}


int main()
{
	const std::string filePath = "Assets/Ryan-Ward.jpg";

	// Check for the existence of the file
	if (!fileExists(filePath)) {
		std::cerr << "Error: Required file '" << filePath << "' is missing!" << std::endl;
		return EXIT_FAILURE;
}

	// If the file exists, print a success message
	std::cout << "The required file '" << filePath << "' is present." << std::endl;
#else
#include <Windows.h>
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
#endif 
	try
	{
		//Construct our Game Instance as a Shared Pointer
		std::shared_ptr<sf::LJMUGameBase> tgame = std::make_shared<sf::LJMUGameBase>();	
		tgame->setupEngine();

		//Create our Initial Screen for the game.
		std::shared_ptr<sf::ILJMUScreenBase> tscreen(new LJMU::LJMUGameScreenMain());
		tgame->addScreen(tscreen, 0);

		//Call Run on Our Game - when the game exits it will be cleaned up
		tgame->runGameLoop();
	}
	catch (std::runtime_error e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
		system("PAUSE");
	}
}

