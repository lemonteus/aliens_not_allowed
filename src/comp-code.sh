echo Hello, $(whoami). The process of compilation has started!

echo Compiling lib: player
gcc -c -o lib/player.o lib/player.c

echo Compiling lib: texture
gcc -c -o view/texture.o view/texture.c

echo Compiling lib: fonts
gcc -c -o lib/fonts.o lib/fonts.c

echo Compiling lib: intro
gcc -c -o view/intro.o view/intro.c

echo Compiling lib: game
gcc -c -o view/game.o view/game.c

echo Compiling main
gcc main.c lib/player.o view/texture.o view/intro.o view/game.o lib/fonts.o -lGL -lglut -lSOIL

echo Compilation finished.


