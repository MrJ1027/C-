#pragma once
#include "Man.h"
#include"AI.h"
#include"Chess.h"
class Chessgame
{
public:
	Chessgame(Man* man, AI* ai, Chess* chess);//构造函数初始化
	void play();

private:
	Man* man;
	AI* ai;
	Chess* chess;
};

