# IMAC1-S2-PROGALGO-SYNTHIMG-Proj-final

## To compile the game
- Build the project 
- Use the executable named game
- And voilà you can play our game in its current state

## How to play
- player mouvement : ZQSD for AZERTY and WASD for QWERTY
- destroy block: U
- pause menu: ESCAPE
- start the game: ENTER
- quit the game: O
  
## How to change the dimension of the map?
- Go into the main_game.cpp file
- Change the numbers (by default 50) in function generate_map in the variable new_map, always make your map a square.
- Also change the windowWidth and windowHeight accordingly (always keep a x10 factor) 
  for example: 
  - by default width_map = 50 -> windowWidth = 500 , height_map = 50 -> windowHeight = 500
   
