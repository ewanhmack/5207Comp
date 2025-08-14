#ifndef __GAME_ASSETS_H_
#define __GAME_ASSETS_H_

//---------ENUMERATIONS AND ENUMERATED LISTS------------------------------

namespace LJMU
{
	//////////////////////////////////
	// Enumeration to represent the 
	// Different Font Assets available.
	// AUTHOR:  DR CHRIS CARTER
	// DATE:    18/05/2017
	//////////////////////////////////
	enum class LJMUSIFont
	{
		SANSATION = 0,
		RETRO
	};

	//////////////////////////////////
	// Enumeration to represent the 
	// Different Sprite Assets available.
	// AUTHOR:  DR CHRIS CARTER
	// DATE:    18/05/2017
	//////////////////////////////////
	enum class LJMUSIAssets
	{
		BG_ONE,
		BG_TWO,
		BRICK_ONE,
		BIRD_ANIM,
		PIG_ANIM,
		SLING_ANIM,
	};
}
#endif