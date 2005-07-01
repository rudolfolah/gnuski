GNUSki README
Copyright (C) 2005  Rudolf Olah

Brief Description
======================
This game is a clone of Skifree which is a Windows game from the early to mid '90s.
It currently uses NCurses for graphics.


Libraries required
======================
ncurses-5.4 (NCurses)
pthread (POSIX Threads)


Compiling
======================
To compile run:
c++ -O2 -o gnuski.o main.cpp -lncurses -lpthread