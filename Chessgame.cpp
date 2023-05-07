#include "Chessgame.h"

Chessgame::Chessgame(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;
	//初始化棋手和ai
	man->init(chess);
	ai->init(chess);
}

void Chessgame::play()
{
	bool is_in = chess-> startUI();//判断是否开始
	if (is_in == false) return;
	chess->init();//初始化棋盘
	while (1) 
	{
		mciSendString("play res/bjmusic1.wav", 0, 0, 0);
		//玩家走棋
		man->go();
		if (chess->checkOver())
		{

			chess->init();
			continue;
		}
		//电脑走棋
		ai->go();
		if (chess->checkOver())
		{
			chess->init();
			continue;
		}
	}
}
