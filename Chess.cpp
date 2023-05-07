#include "Chess.h"
#include <math.h>
#include<iostream>
#include <conio.h>
#include"tools.h"
#include<mmsystem.h>
#include<Windows.h>
//#pragma comment(lib, "winmm. lib")


//const  char* str[3] = { "\"play res/bjmusic1.wav\"","\"play res/bjmusic2.wav\"","\"play res/bjmusic3.wav\"" };

Chess::Chess(int gradeSize, int margin_x, int margin_y, float chessSize)
{
    this->gradeSize = gradeSize;
    this->margin_x = margin_x;
    this->margin_y = margin_y;
    this->chessSize = chessSize;
    playerFlag = true;
    //��ʼ������
    for (int i = 0; i < gradeSize; i++) {
        std::vector<int>row;
        for (int j = 0; j < gradeSize; j++) {
            row.push_back(0);
        }
        chessMap.push_back(row);
    }
}


void Chess::init()
{
    loadimage(0, "res/����13.png");//��ʾ����ͼƬ

    loadimage(&BlackImg, "res/black.png", chessSize, chessSize,true);//��������ͼƬ(ָ����С��
    loadimage(&WhiteImg, "res/white.png", chessSize, chessSize,true);

    //��������(�Ծֽ�������)
    for (int i = 0; i < gradeSize; i++) {
        for (int j = 0; j < gradeSize; j++) {
            chessMap[i][j] = 0;
        }
    }
    playerFlag = true;

}

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
    //���㵱ǰ���λ�õ����Ͻǵ�����
    int col = (x - margin_x) / chessSize;
    int row = (y - margin_y) / chessSize;
    //�����λ�����Ͻǵ�����
    int leftTopPos_x = margin_x + chessSize * col;
    int leftTopPos_y = margin_y + chessSize * row;
    int offset = chessSize * 0.3;//��ֵ����������ֵ��
    //��������ǵľ���
    int len;
    bool ret = false;
    do {
        //���Ͻǵ��ж�
        len = sqrt((x - leftTopPos_x) * (x - leftTopPos_x) + (y - leftTopPos_y) * (y - leftTopPos_y));
        if (len < offset)
        {
            pos->row = row;
            pos->col = col;
            //�жϵ��λ���Ƿ���Ч��ԭ����û������ռ�����
            if (chessMap[pos->row][pos->col] == 0) {
                ret = true;
            }
            break;//��������Ͻ��Ǹ��ж϶��ˣ��ǾͲ����������������ˣ�ֱ������ȥ
        }
        //���Ͻǵ��ж�
        int x2= leftTopPos_x + chessSize;
        int y2= leftTopPos_y ;
        len = sqrt((x2 - x) * (x2 - x) + (y - y2) * (y - y2));
        if (len < offset)
        {
            pos->row = row;
            pos->col = col+1;
            //�жϵ��λ���Ƿ���Ч��ԭ����û������ռ�����
            if (chessMap[pos->row][pos->col] == 0) {
                ret = true;
            }
            break;
        }
        //���½ǵ��ж�
         x2 = leftTopPos_x;
         y2 = leftTopPos_y + chessSize;
        len = sqrt((x2 - x) * (x2 - x) + (y - y2) * (y - y2));
        if (len < offset)
        {
            pos->row = row+1;
            pos->col = col ;
            //�жϵ��λ���Ƿ���Ч��ԭ����û������ռ�����
            if (chessMap[pos->row][pos->col] == 0) {
                ret = true;
            }
            break;
        }
        //���½ǵ��ж�
        x2 = leftTopPos_x + chessSize;
        y2= leftTopPos_y + chessSize;
        len = sqrt((x2 - x) * (x2 - x) + (y - y2) * (y - y2));
        if (len < offset)
        {
            pos->row = row + 1;
            pos->col = col+1;
            //�жϵ��λ���Ƿ���Ч��ԭ����û������ռ�����
            if (chessMap[pos->row][pos->col] == 0) {
                ret = true;
            }
            break;
        }

    } while (0);
    return ret;//retΪ���ʾ��Ч���
}

void Chess::chessDown(ChessPos* pos, chessType type)
{
    int x = margin_x + chessSize * pos->col - 0.5* chessSize;
    int y = margin_y + chessSize * pos->row -0.5 * chessSize;
    if (type == CHESS_WHITE) {
        putimagePNG(x, y, &WhiteImg);
    }
    else
    {
        putimagePNG(x, y, &BlackImg);
    }
    updateGameMap(pos);

}

int Chess::getGradeSize()
{
    return gradeSize;
}

bool Chess::checkOver()
{
    int x = 290;
    int y = 357;
    if (checkWin())
    {
        Sleep(1500);
        mciSendString("close res/bjmusic1.wav", 0, 0, 0);
        if (playerFlag == false)
        {
            //��ʤ
            mciSendString("play res/ʤ��music.mp3", 0, 0, 0);
            loadimage(&Winpg, "res/win.jpg");
            putimage(x, y, &Winpg);

          
        }
        else
        {
            //��ʤ
            mciSendString("play res/ʧ��music.mp3", 0, 0, 0);
            loadimage(&Losepg, "res/lose.jpg");
            putimage(x, y, &Losepg);
        }
        //���ȷ���رմ��ڹ���
        //closeWindow();
        system("pause");

        return true;
    }
    return false;
}

int Chess::getChessData(int row, int col)
{
    return chessMap[row][col];
}

bool Chess::startUI()
{
    initgraph(1000, 1000);//���ڴ���
    loadimage(&startpg, "res/startUI.jpg");
    putimage(0, 0, &startpg);
    char a = _getch();
    return a == 32 ? true : false;
}

//void Chess::gameBGM()
// {
//    mciSendString("play res/bjmusic1.wav", 0, 0, 0);
//
//     if (_kbhit())
//    {
//        unsigned char ch = ' ';
//         ch = _getch();
//        if (ch == 32)//�ո�
//        {
//            mciSendString("stop res/bjmusic1.wav", 0, 0, 0);
//            mciSendString(str[2], 0, 0, 0);  
//
//        }
//    }
//
//}


void Chess::updateGameMap(ChessPos* pos)
{
    lastPos = *pos;
    chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
    playerFlag = !playerFlag;//�ڰ׽�������
}

bool Chess::checkWin()
{
    int row = lastPos.row;
    int col = lastPos.col;
    //�ж�ˮƽ����
    for (int i = 0; i < 5; i++)
    {
        if (col - i >= 0 && col - i + 4 < gradeSize && 
            chessMap[row][col - i] == chessMap[row][col - i + 1] &&
            chessMap[row][col - i] == chessMap[row][col - i + 2] &&
            chessMap[row][col - i] == chessMap[row][col - i + 3] && 
            chessMap[row][col - i] == chessMap[row][col - i + 4])
            return true;
    }
    //��ֱ����

    for (int i = 0; i < 5; i++)
    {
        if (row - i >= 0 && row - i + 4 < gradeSize && 
            chessMap[row - i][col] == chessMap[row - i + 1][col] && 
            chessMap[row - i][col] == chessMap[row - i + 2][col] &&
            chessMap[row - i][col] == chessMap[row - i + 3][col] && 
            chessMap[row - i][col] == chessMap[row - i + 4][col])
            return true;
    }
    //б�߷���/
    for (int i = 0;i < 5; i++)
    {
        if (row + i <gradeSize&& row + i - 4 >= 0&& col - i >= 0 && col - i + 4 < gradeSize &&
            chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] && 
            chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2]&& 
            chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
            chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4])
            return true;
    }
    //б�߷���2
    for (int i = 0; i < 5; i++)
    {
        if (row - i >= 0 && row - i + 4 < gradeSize && col - i >= 0 && col - i + 4 < gradeSize &&
            chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] &&
            chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] &&
            chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] && 
            chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4])
            return true;
    }
    
    return false;
}

//void Chess::closeWindow()
//{
//    MOUSEMSG msg;
//    msg = GetMouseMsg();
//    if (msg.uMsg == WM_LBUTTONDOWN && msg.x >= 410 && msg.x <= 585 && msg.y >= 532 && msg.y <= 620)
//    {
//        cleardevice();
//    }
//    
//}
