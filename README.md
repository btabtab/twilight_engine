Hello, welcome to twilight engine, this is just
a small project for me to do experiments in.
It's set up so that I can just create a
TwilightNode class and make it do stuff
so that I can throw it into the renderer and see
what happens.

Currently I'm implementing BSP trees.
Later on I might add 3D rendering for
them and do some doom engine stuff.
But for now I'm just messing around
with it...

Eventually I *would* like to make little
games and demos with this, but for now
it's basically just a bunch of boiler
plate code that is going to be used to do stuff.

Massive thanks to **RAYLIB** for existing as I wouldn't
be where I was today without it...

Build instrutions:
->->->->->->->->->->->->->->->->->->->->->->->->->->->
My main build instruction line is:
clang++ */*/*.cpp */*.cpp *.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lncurses -g -o twilightEngineFrameWork.debug.runme

Dependencies:
-> Raylib
-> Ncurses (currently a hangover from a 2nd year project from where I've reused the build line
			so much and never re-used it, but I am going to work on a way to run Twilight-Engine
			in the console using Ncurses.)
<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-<-