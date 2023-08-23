# Fallback

![Fallback Title](source/pictures/title-screenshot.png)

My first game in C++/DirectX! Built with a custom 2D engine (details below). 

[Gameplay Video on YouTube](https://youtu.be/ekXz9nsTwCI)


## Project Details

I went back and updated this significantly beyond what the book covers into a complete little game. I'm very proud of implementing some of the things from other engines into this one. The engine, as conceived in the book, is quite limited, offering the very bare bones of a game loop, update/render cycle, collisions, audio, and input.

I had to refactor the actor hierachy and add a ton of stuff to get to a completed game. Handling collisions and bouncing behavior in conjunction with the animation system was probably the most finicky. 

I learned a ton about C++, managing memory, and using the standard library, including the template container classes.

Overall, it was a blast! 

![Fallback Gameplay](source/pictures/fb-action2.png)

### Final Features

- Full gameplay from start to Game Over, with screen/state management (including a pause feature), all with input controls/navigation to leave the game, start over, etc.
- Animations/Tweening managed through a dynamic `Process Manager` which allows attaching animation processes to any game entity
	- Created a set of reusable Tween classes/API for moving, scaling and alpha blending over time.    
	- The Animation System includes callback support so the entity can gracefully handle post-animation behaviors
- Added a variety of powerups that alter the ball and ship, including changing speeds, scaling, and allowing the ship to warp through the edge wall and appear on the other side!
- Added Block types which have varying health and associated colors with their remaining health. Blocks work down to a basic type but score as their original type which is worth more points
- `Console` class and `log` display, including a common `toString` method which converts relevant object into into a displayable string
- Level progression and loading 
- Audio/SFX using XACT resources
- Hand-rolled UI Buttons and DX Text Buttons with rollover states
- Full Level Editor with intuitive GUI (below)


![Fallback Level Editor](source/pictures/editor-screenshot.png)

---

## About the Original Project

Book: [Programming 2D Games by Charles Kelly](http://www.programming2dgames.com//)

Chapter 6 Challenge: Given the engine so far, make a game, any game. Keep it simple.

I chose to make a simple form of Breakout.

**Features**

* game loop (initialization, input, render, restart)
* collision detection
* game logic: ball resets if missed, blocks disappear when hit


## Learnings

I'll note that the content is quite old (2012) so I had to convert the code in the book and examples a bit to get it working on Windows 10. The biggest challenge was getting all the DirectX9 parts needed set up in the includes and linker settings.

* Learned the basics of Win32 (and WinRT) apps are set up and initialized
* Learned a ton about VS and how to work within it including the debugger
* Win32 apps don't have a built in log like other environments - the debugger is absolutely critical
* I have a very solid understanding of how all the pieces fit together in this engine and the things that need to be accounted for in any game engine
* I can see how the organization of the components so far will be a serious problem on a project that is much larger than this tiny game


## Proud Of

I'm proud of working through 2 blocking type bugs which stopped me in my tracks. But I kept at it and worked passed them. 

