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
    //初始化棋盘
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
    loadimage(0, "res/棋盘13.png");//显示棋盘图片

    loadimage(&BlackImg, "res/black.png", chessSize, chessSize,true);//加载棋子图片(指定大小）
    loadimage(&WhiteImg, "res/white.png", chessSize, chessSize,true);

    //棋盘清理(对局结束清理)
    for (int i = 0; i < gradeSize; i++) {
        for (int j = 0; j < gradeSize; j++) {
            chessMap[i][j] = 0;
        }
    }
    playerFlag = true;

}

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
    //计算当前点击位置的左上角的行列
    int col = (x - margin_x) / chessSize;
    int row = (y - margin_y) / chessSize;
    //鼠标点击位置左上角的坐标
    int leftTopPos_x = margin_x + chessSize * col;
    int leftTopPos_y = margin_y + chessSize * row;
    int offset = chessSize * 0.3;//阈值（点击的误差值）
    //距离各个角的距离
    int len;
    bool ret = false;
    do {
        //左上角的判断
        len = sqrt((x - leftTopPos_x) * (x - leftTopPos_x) + (y - leftTopPos_y) * (y - leftTopPos_y));
        if (len < offset)
        {
            pos->row = row;
            pos->col = col;
            //判断点击位置是否有效（原本有没有棋子占在那里）
            if (chessMap[pos->row][pos->col] == 0) {
                ret = true;
            }
            break;//如果是左上角那个判断对了，那就不用算另外三个角了，直接跳出去
        }
        //右上角的判断
        int x2= leftTopPos_x + chessSize;
        int y2= leftTopPos_y ;
        len = sqrt((x2 - x) * (x2 - x) + (y - y2) * (y - y2));
        if (len < offset)
        {
            pos->row = row;
            pos->col = col+1;
            //判断点击位置是否有效（原本有没有棋子占在那里）
            if (chessMap[pos->row][pos->col] == 0) {
                ret = true;
            }
            break;
        }
        //左下角的判断
         x2 = leftTopPos_x;
         y2 = leftTopPos_y + chessSize;
        len = sqrt((x2 - x) * (x2 - x) + (y - y2) * (y - y2));
        if (len < offset)
        {
            pos->row = row+1;
            pos->col = col ;
            //判断点击位置是否有效（原本有没有棋子占在那里）
            if (chessMap[pos->row][pos->col] == 0) {
                ret = true;
            }
            break;
        }
        //右下角的判断
        x2 = leftTopPos_x + chessSize;
        y2= leftTopPos_y + chessSize;
        len = sqrt((x2 - x) * (x2 - x) + (y - y2) * (y - y2));
        if (len < offset)
        {
            pos->row = row + 1;
            pos->col = col+1;
            //判断点击位置是否有效（原本有没有棋子占在那里）
            if (chessMap[pos->row][pos->col] == 0) {
                ret = true;
            }
            break;
        }

    } while (0);
    return ret;//ret为真表示有效点击
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
            //黑胜
            mciSendString("play res/胜利music.mp3", 0, 0, 0);
            loadimage(&Winpg, "res/win.jpg");
            putimage(x, y, &Winpg);

          
        }
        else
        {
            //白胜
            mciSendString("play res/失败music.mp3", 0, 0, 0);
            loadimage(&Losepg, "res/lose.jpg");
            putimage(x, y, &Losepg);
        }
        //点击确定关闭窗口功能
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
    initgraph(1000, 1000);//窗口创建
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
//        if (ch == 32)//空格
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
    playerFlag = !playerFlag;//黑白交换走棋
}

bool Chess::checkWin()
{
    int row = lastPos.row;
    int col = lastPos.col;
    //判断水平方向
    for (int i = 0; i < 5; i++)
    {
        if (col - i >= 0 && col - i + 4 < gradeSize && 
            chessMap[row][col - i] == chessMap[row][col - i + 1] &&
            chessMap[row][col - i] == chessMap[row][col - i + 2] &&
            chessMap[row][col - i] == chessMap[row][col - i + 3] && 
            chessMap[row][col - i] == chessMap[row][col - i + 4])
            return true;
    }
    //垂直方向

    for (int i = 0; i < 5; i++)
    {
        if (row - i >= 0 && row - i + 4 < gradeSize && 
            chessMap[row - i][col] == chessMap[row - i + 1][col] && 
            chessMap[row - i][col] == chessMap[row - i + 2][col] &&
            chessMap[row - i][col] == chessMap[row - i + 3][col] && 
            chessMap[row - i][col] == chessMap[row - i + 4][col])
            return true;
    }
    //斜线方向/
    for (int i = 0;i < 5; i++)
    {
        if (row + i <gradeSize&& row + i - 4 >= 0&& col - i >= 0 && col - i + 4 < gradeSize &&
            chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] && 
            chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2]&& 
            chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
            chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4])
            return true;
    }
    //斜线方向2
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
