#include "Man.h"

void Man::init(Chess* chess)
{
	this->chess = chess;
}

void Man::go()
{
	MOUSEMSG msg;//鼠标消息类型
	ChessPos pos;

	while (1)
	{
		msg = GetMouseMsg();//获取鼠标点击消息
		//用chess对象来判断落子是否有效
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos)) {
			break;
		}
	}
	//如果上面条件满足，点击位置有效，那么跳出循环执行落子操作
	chess->chessDown(&pos, CHESS_BLACK);
}
