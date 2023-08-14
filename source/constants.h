// Chapter 6 project by Kris Szafranski
// ====================================
// Builds on engine code provded by
// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly


#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(255,255,0,255)  // transparent color (magenta)

// Structs
struct Vector2 {
	float x;
	float y;
};

//=============================================================================
//                  Constants
//=============================================================================

// graphic files
const char BG_PATH[] = "pictures\\bg-sprites.jpg";
const char TITLE_PATH[] = "pictures\\fallback-title.png";
const char GAME_OVER_PATH[] = "pictures\\game-over-msg.png";
const char ICONS_PATH[] = "pictures\\ui-icons.png";
const char SHIP_PATH[] = "pictures\\ship.png";
const char RACER_PATH[] = "pictures\\racers.png";
const char BLOCK_PATH[] = "pictures\\blocks.png";
const char NG_BUTTON_PATH[] = "pictures\\buttons.png";


// window
const char CLASS_NAME[] = "Breakout";
const char GAME_TITLE[] = "FALLBACK";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  800;               // width of game in pixels
const UINT GAME_HEIGHT = 600;               // height of game in pixels
 
// game
const double PI = 3.14159265;
const float FRAME_RATE  = 200.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const short MAX_BALLS = 3;
const float BALLSHADOW_INTERVAL = 0.07;

// weapon types
enum WEAPON { TORPEDO, SHIP, PLANET, BALL };
// block types
enum BLOCK { WEAK, STRONG, HARD, METAL, INVINCIBLE, NONE };
// screen states
enum SCREEN { TITLE, GAME, EDITOR, CREDITS };


// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[] = "audio\\WaveBank.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\SoundBank.xsb";

// audio cues
const char ZAP[] = "zap";
const char CLICK[] = "click";
const char CLUNK[] = "clunk";
const char POP[] = "pop";
const char HIT[] = "hit";


// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY = VK_MENU;         // Alt key
const UCHAR ENTER_KEY = VK_RETURN;       // Enter key
const UCHAR SHIP_LEFT_KEY = VK_LEFT;     // left arrow
const UCHAR SHIP_RIGHT_KEY = VK_RIGHT;    // right arrow
const UCHAR NEXT_LEVEL_KEY = VK_UP;       // up arrow
const UCHAR SHIP_DOWN_KEY = VK_DOWN;     // down arrow
const UCHAR SPACE_KEY = VK_SPACE;     // down arrow

#endif
