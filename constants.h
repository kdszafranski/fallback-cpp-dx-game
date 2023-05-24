// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 4 constants.h v1.1
// Last modification: Mar-9-2015


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

//=============================================================================
//                  Constants
//=============================================================================

// graphic files
const char NEBULA_PATH[] = "pictures\\nebula-bg-game.png";
const char PLANET_PATH[] = "pictures\\planet.png";
const char SHIP_PATH[] = "pictures\\ship.png";


// window
const char CLASS_NAME[] = "Breakout";
const char GAME_TITLE[] = "Breakout";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  800;               // width of game in pixels
const UINT GAME_HEIGHT = 600;               // height of game in pixels
 
// game
const double PI = 3.14159265;
const float FRAME_RATE  = 200.0f;               // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations

// ship art has multiple frames
const UINT SHIP_WIDTH = 32;
const UINT SHIP_HEIGHT = 32;
const UINT SHIP_COLS = 2;
const UINT SHIP_START_FRAME = 0;
const UINT SHIP_END_FRAME = 3;
const float SHIP_ANIM_DELAY = 0.4f;
const float SHIP_ROTATION_RATE = 25.0f;
const float SHIP_SCALE = 1.0f;
const float SHIP_SCALE_RATE = 0.2f;
const float SHIP_SPEED = 150;
const float MAX_VELOCITY = 200;


// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY = VK_MENU;         // Alt key
const UCHAR ENTER_KEY = VK_RETURN;       // Enter key
const UCHAR SHIP_LEFT_KEY = VK_LEFT;     // left arrow
const UCHAR SHIP_RIGHT_KEY = VK_RIGHT;    // right arrow
const UCHAR SHIP_UP_KEY = VK_UP;       // up arrow
const UCHAR SHIP_DOWN_KEY = VK_DOWN;     // down arrow

// weapon types
enum WEAPON { TORPEDO, SHIP, PLANET };

#endif
