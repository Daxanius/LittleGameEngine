# Q*Bert
A game made in my own little game engine, appropriately named LittleGameEngine. 

The repository can be found here: https://github.com/Daxanius/LittleGameEngine

# Running the project
Download the latest release of this project and compile/run in visual studio.

As an alternative, I have also [provided a build on GitHub](https://github.com/Daxanius/LittleGameEngine/releases/tag/v1.0).

# Features
The game features the following:

- Single player mode
- Co-op mode
- Versus mode
- A scoreboard showing the 10 best scores with 3 letter names (which saves)
- Dynamic level loading

## Controls
Generally, the game has pretty standard controls. On keyboard you can use WASD to navigate menus and play the game. Enter to selection options, escape to go to the pause menu, however unpause is bound to tab, since pressing escape again will go back to the main menu.

You can hook up to 2 gamepads to the game, the 1st gamepad is the host player (P1) and can control the menus. A combination of gamepad + keyboard is also possible.

Alternatively, 2nd player can use the arrow keys to move around.

## Modes
The game has 3 "modes" to play: Single player, Co-op and Versus. 

### Single Player
Single player provides a standard Q*Bert game experience: run away from Coily, Ugg and Wrongway, while flipping tiles by stepping on them and chasing / trying to catch Slick and Sam, who undo your progress by stepping on the tiles.

Certain actions like flipping tiles, catching Slick or Sam, winning with discs still there, and fooling Coily into the void reward extra points.

When all tiles are flipped, you move to the next round and have to do it again. After round 4, the player will go to the next level which can have different rules like requiring 2 tile flicks or reverting tiles when stepping on them again.

Coily can be caught by jumping on the spinning discs, which bring Q\*Bert back to the start. Coily will attempt to jump towards Q\*Bert on the disc, causing them to fall off the grid.

## Co-op 
Multi player follows the same rules, except that there are now 2 players with separate scores. Both players start at the bottom edges of the map.

## Versus
Versus allows player 2 to take control of Coily as soon has he hatches from his egg.

# Design Decisions
If you're interested in the design decisions of the project, then you're at the right place. Here I will discuss some design aspects of the engine and my reasoning behind them.

## Z-Ordering
Ahh, dirty flags, my best friend. The engine makes use of dirty flags to avoid recalculating values that have not been changed.

A great use case of this in my engine are for example where I apply Z-ordering. A simply sorting algorithm is ran to sort objects based on Z-values such that they are rendered in the right order. The problem is that recalculating the Z-order every draw call is not very efficient. To solve this, I made it so that objects keep track of when their Z value changed, and if it did, then we recalculate. Z-values don't commonly change, allowing for this neat optimization.

Another usage of the dirty flag is with transforms. My engine allows you to "re-parent" game objects such that their transform becomes a child of the parent. This means that anytime you want the world position of an object, you would have to calculate it based on the parents. However this is clearly uneccesarry as you won't be constantly re-parenting objects. 

## Input System
Input systems can get very complex depending on the requirements. However, in this case the requirements are relatively simple. No need to handle floating point values from joysticks, no need to handle dead zones for stick drift, etc.

For this reason, the Command pattern works incredibly well with my input system. When you press a button, that button is bound to a command based on whether you just pressed it, you just released it, or if you're holding it.

I can bind keys to any action I desire using this system.

## The Audio System
As is the case with many low-level or game-engine related subjects, this can get quite complex, quickly.

For this reason, this engine uses a simple audio system provided as a service, which runs a thread in the background that consumes play commands from a queue sequentially.

The service can be accessed via the ResourceLocator singleton. 

# Scenes
I took a rather unconventional / unusual approach to scenes. Instead of making a scene in some arbitrary builder, and then registering it with the scene system, scenes are built by themselves.

This is done through inheritance. My scenes inherit from Scene, which allows me to avoid global state by having custom scene constructors. I tried my very best to avoid any form of global state in my Q*Bert game as an experimental thing.

The most powerful part of this, is that each scene can have it's own keybindings, scene-specific settings, and even potentially a global update loop that I did not end up making virtual. 

Now, whenever I switch scenes (by providing a string id to the SceneManager), it will automatically load the keybindings and setup the scene.

Scenes are switched in the SceneManager by first registering new scenes using a register function. This uses an unordered map under the hood to map a string (the scene name), to the scene. 

Now you may wonder why I don't use make_sdbm_hash for scene names to have compile-time hashing. The reason is very simple: ease of development. Whenever you try to load a scene that has not been registered (or you made a typo), it will print the scene name you attempted to load in the console, saying it for example did not find the scene. 

While yes, it does require hashing, switching and adding scenes is not in a hot code path, making the trade-of for this handy feature negligible.

Needless to say, while the scene system is incredibly powerful and very nice the way it is, I did end up abusing it due to lack of time, high exhaustion and lots of stress. I.e. I do some questionable stuff regarding scene loading...