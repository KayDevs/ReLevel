ConsoleApplication3
===================

Keller's Personal Game/Engine

This is an Game or Game Engine being developed by me, Keller, for personal use.
I am just programming right now to get a handle on SFML and game design in general, 
so this may or may not turn into a complete game.
Either way, it'll be a fun learning experience for me.


This is being developed using SFML 2.0 in Visual Studio 2012 on Windows, and using Vim and standard Makefiles on UNIX-like systems
It should compile and run on both, as it uses no platform-specific code with the exception of #pragma comments for convenience in VS.

It features a game, along with a level editor for editing map files.
To build everything, 'make' should do. To build just the Level Editor, run 'make LevelEditor'.

Mapfiles are syntaxed as follows:  
Obj  
	ClassName  
	X  
	Y  
End  
  
Where:  
Obj is the declaration of a new object  
ClassName is the name of the class of the new object (e.g. Player, BasicEnemy, etc.)  
X and Y are the coordinates of the new object  
and End is the end of the entire Mapfile.  
  
  
  
  
  
Please excuse my profanity in the comments, it helps me remember things as well as it adds additional motivation.
