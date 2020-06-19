function deleteFilesFunc {
    echo -e "\nDeleting compilation files..."

    rm -f $(pwd)/lib/player.o
    rm -f $(pwd)/view/texture.o
    rm -f $(pwd)/lib/fonts.o
    rm -f $(pwd)/view/intro.o
    rm -f $(pwd)/view/game.o

    echo -e "Done."
}

clear
echo -e "\nHello, $(whoami). The process of compilation has started!\n"

echo -e "Compiling lib/fonts.c"
gcc -c -o lib/fonts.o lib/fonts.c
if [ $? -ne 0 ]; then
    deleteFilesFunc
    exit 1
fi

echo -e "Compiling lib/player.c"
gcc -c -o lib/player.o -Wall lib/player.c
if [ $? -ne 0 ]; then
    deleteFilesFunc
    exit 1
fi

echo -e "Compiling view/texture.c"
gcc -c -o view/texture.o view/texture.c
if [ $? -ne 0 ]; then
    deleteFilesFunc
    exit 1
fi

echo -e "Compiling view/intro"
gcc -c -o view/intro.o view/intro.c
if [ $? -ne 0 ]; then
    deleteFilesFunc
    exit 1
fi

echo -e "Compiling view/game.c"
gcc -c -o view/game.o view/game.c
if [ $? -ne 0 ]; then
    deleteFilesFunc
    exit 1
fi

echo -e "Compiling main.c"
gcc -o tp1.out main.c lib/player.o view/texture.o view/intro.o view/game.o lib/fonts.o -lGL -lglut -lSOIL -lm
if [ $? -ne 0 ]; then
    deleteFilesFunc
    exit 1
fi

echo -e "\nCompiled and finished!"
deleteFilesFunc

echo -e "\nInitializing game...\n"
./tp1.out

exit 0