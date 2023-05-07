#include "Chessgame.h"

Chessgame::Chessgame(Man* man, AI* ai, Chess* chess)
{
	this->man = man;
	this->ai = ai;
	this->chess = chess;
	//��ʼ�����ֺ�ai
	man->init(chess);
	ai->init(chess);
}

void Chessgame::play()
{
	bool is_in = chess-> startUI();//�ж��Ƿ�ʼ
	if (is_in == false) return;
	chess->init();//��ʼ������
	while (1) 
	{
		mciSendString("play res/bjmusic1.wav", 0, 0, 0);
		//�������
		man->go();
		if (chess->checkOver())
		{

			chess->init();
			continue;
		}
		//��������
		ai->go();
		if (chess->checkOver())
		{
			chess->init();
			continue;
		}
	}
}
