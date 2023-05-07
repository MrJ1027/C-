#pragma once
#include<graphics.h>
#include <vector>

//���ӵ�λ��
struct ChessPos 
{
	ChessPos(int r, int c) : row(r), col(c) {} //�������Ĺ��캯��
	ChessPos()
	{
		row = 0;
		col = 0;
	}//Ĭ�Ϲ��캯��(�������Ҫд����Ȼ�Ļ��������Ӵ�����Ϊ�Ҳ�����������Ķ��������
	int row;
	int col;
};
//�������Ͱ�ɫ-1����ɫ1
enum chessType 
{
	CHESS_WHITE = -1,
	CHESS_BLACK = 1
};

class Chess
{
public:
	Chess(int gradeSize, int margin_x, int margin_y, float chessSize);

	//����Ĺ��ܣ��ӿڣ�
	void init();
	bool clickBoard(int x, int y, ChessPos* pos);
	void chessDown(ChessPos* pos, chessType type);//��������
	int getGradeSize();//��ȡ���̴�С
	bool checkOver();//�����Ϸ�Ƿ����
	int getChessData(int row, int col);
	bool startUI();

	//void gameBGM();(δʵ�֣�������˵)

private:
	//��ʼ����ͼƬ
	IMAGE startpg;
	//�ڰ�����
	IMAGE BlackImg;
	IMAGE WhiteImg;
	//����ͼƬ
	IMAGE Winpg;
	IMAGE Losepg;

	int gradeSize;//���̴�С
	int margin_x;//������ϲ�߽����
	int margin_y;
	float chessSize;//���Ӵ�С

	//��ŵ�ǰ��ֵ����ӷֲ��������һ����ά������������ϵ�ÿһ����
	//0Ϊ�հף�1Ϊ����
	std::vector<std::vector<int>>chessMap;

	bool playerFlag;//true ������,false ������
	//˽�з������޸���������
	void updateGameMap(ChessPos* pos);

	bool checkWin();
	ChessPos lastPos;//�������λ��
	//void closeWindow();���ȷ���رմ���(δʵ�֣�������˵)
	
};

