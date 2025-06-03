from os import system

system("gcc src/bst.c src/main.c src/menu.c src/save.c src/utils.c -o main")
system("./main")
