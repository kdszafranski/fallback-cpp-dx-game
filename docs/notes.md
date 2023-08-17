# IDEAS to take this further

## Fix Bugs
- [x] fix collisions
- [x] block should complete animation before being destroyed


## Architecture
- [ ] Winmain, winproc
- [ ] convert to be like the GCC book
- [ ] move large constructors to init methods
- [ ] Implement an IScreen interface
- [ ] make consistent style
- [ ] choose Vector standard

## Technical Challenges
- [ ] add event manager, implement Observer pattern: https://gameprogrammingpatterns.com/observer.html
- [X] separate direction from speed
- [X] make level editor
- [X] added animation/process manager to handle multi-frame animations
- [ ] consider memory/profiling
- [ ] compile to web assem using Emscripten
- [ ] convert to use SDL2
- [ ] allow blocks of varying sizes

## Graphics
- [ ] custom cursor (resource)
- [ ] screen transitions (start with fading in/out)
- [ ] screen shake on ball loss
- [ ] delay between ball restart
- [ ] ship explosion on game over
- [x] add more animations
- [x] ball trail
- [x] juicier, particles
- [x] clean up score UI
- [x] clean up balls remaining


## Audio
- [ ] better sfx
- [ ] add music


Multiball
- change to vector of Ships
    - need to change every instance to a loop, would have 1 ball 99% of the time