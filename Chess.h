#pragma once
#include<graphics.h>
#include <vector>

//棋子的位置
struct ChessPos 
{
	ChessPos(int r, int c) : row(r), col(c) {} //带参数的构造函数
	ChessPos()
	{
		row = 0;
		col = 0;
	}//默认构造函数(定义必须要写，不然的话出现链接错误，因为找不到这个函数的定义在哪里）
	int row;
	int col;
};
//棋子类型白色-1，黑色1
enum chessType 
{
	CHESS_WHITE = -1,
	CHESS_BLACK = 1
};

class Chess
{
public:
	Chess(int gradeSize, int margin_x, int margin_y, float chessSize);

	//对外的功能（接口）
	void init();
	bool clickBoard(int x, int y, ChessPos* pos);
	void chessDown(ChessPos* pos, chessType type);//棋子下落
	int getGradeSize();//获取棋盘大小
	bool checkOver();//检查游戏是否结束
	int getChessData(int row, int col);
	bool startUI();

	//void gameBGM();(未实现，后面再说)

private:
	//开始界面图片
	IMAGE startpg;
	//黑白棋子
	IMAGE BlackImg;
	IMAGE WhiteImg;
	//结束图片
	IMAGE Winpg;
	IMAGE Losepg;

	int gradeSize;//棋盘大小
	int margin_x;//左侧与上侧边界距离
	int margin_y;
	float chessSize;//棋子大小

	//存放当前棋局的棋子分布情况，用一个二维数组代表棋盘上的每一个点
	//0为空白，1为黑子
	std::vector<std::vector<int>>chessMap;

	bool playerFlag;//true 黑子走,false 白子走
	//私有方法，修改棋盘数据
	void updateGameMap(ChessPos* pos);

	bool checkWin();
	ChessPos lastPos;//最后落子位置
	//void closeWindow();点击确定关闭窗口(未实现，后面再说)
	
};

