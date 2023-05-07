#include<iostream>
#include"Chessgame.h"
int main()
{
	Man man;
	AI ai;
	Chess chess(13,84,80,68.75);
	Chessgame game(&man,&ai,&chess);
	game.play();

	return 0;
}