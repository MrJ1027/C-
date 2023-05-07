#include "Man.h"

void Man::init(Chess* chess)
{
	this->chess = chess;
}

void Man::go()
{
	MOUSEMSG msg;//�����Ϣ����
	ChessPos pos;

	while (1)
	{
		msg = GetMouseMsg();//��ȡ�������Ϣ
		//��chess�������ж������Ƿ���Ч
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos)) {
			break;
		}
	}
	//��������������㣬���λ����Ч����ô����ѭ��ִ�����Ӳ���
	chess->chessDown(&pos, CHESS_BLACK);
}
