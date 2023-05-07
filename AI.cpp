#include "AI.h"
#include "Chess.h"

void AI::init(Chess * chess )
{
	this->chess = chess;
	
	int size = chess->getGradeSize();
	for (int i = 0; i < size; i++) {
		std::vector<int>row;
		for (int j = 0;j < size; j++) {
			row.push_back(0);
		}
		scoreMap.push_back(row);
	}
}

void AI::go()
{
	ChessPos pos=aiThink();
	Sleep(1000);//延时一秒下棋
	chess->chessDown(&pos, CHESS_WHITE);

}

void AI::calculateScore()
{

	int personNum = 0;
	int aiNum = 0;
	int emptyNum = 0;
	//评分数组清零
	for (int i = 0; i < scoreMap.size(); i++) {
		for (int j = 0; j < scoreMap[i].size(); j++) {
			scoreMap[i][j] = 0;
		}
	}

	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++) 
		{

			if (chess->getChessData(row, col)) continue;//如果不等于0（说明这个位置已经有棋子了）那么就跳过这个点
			//各个方向去搜索位置
			for (int y = -1; y <= 0; y++)
			{
				for (int x = -1; x <= 1; x++)
				{
					if (y == 0 && x == 0) continue;//自己要下的点不用理
					if (y == 0 && x != 1) continue;

					personNum = 0;
					aiNum = 0;
					emptyNum = 0;
					//正向计算
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row + i * y; 
						int curCol = col + i * x;
						//看看范围能不能写成宏？
						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
							&& chess->getChessData(curRow, curCol) == 1) 
						{
							personNum++;
						}
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
							&& chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}

					//反向计算
					for (int i = 1;i <= 4; i++) {
						int curRow = row -i * y;
						int curCol = col - i * x;
						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
							&& chess->getChessData(curRow, curCol) == 1) {
							personNum++;
						}
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
							&& chess->getChessData(curRow, curCol) == 0) {
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}
					//各种棋形的计分(对黑棋）
					if (personNum == 1)
					{
						scoreMap[row][col] += 10;
					}
					else if (personNum == 2)
					{
						if (emptyNum == 1)
						{
							scoreMap[row][col] += 30;

						}
						else if (emptyNum == 2)
						{
							scoreMap[row][col] += 40;

						}
					}
					else if (personNum == 3)
					{
						if (emptyNum == 1)
						{
							scoreMap[row][col] += 60;

						}
						else if (emptyNum == 2)
						{
							scoreMap[row][col] += 200;

						}
					}
					else if (personNum == 4)
					{
						scoreMap[row][col] += 20000;

					}

					emptyNum == 0;//清零
					//白棋正向搜索
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row + i * y;
						int curCol = col + i * x;
						//看看范围能不能写成宏？
						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
							&& chess->getChessData(curRow, curCol) == -1)
						{
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
							&& chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}
					//白棋反向搜索
					for (int i = 1;i <= 4; i++) 
					{
						int curRow = row - i * y;
						int curCol = col - i * x;
						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
							&& chess->getChessData(curRow, curCol) == -1) 
						{
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
							&& chess->getChessData(curRow, curCol) == 0) 
						{
							emptyNum++;
							break;
						}
						else
						{
							break;
						}
					}
					//对白棋
					if (aiNum == 0)
					{
						scoreMap[row][col] += 5;

					}
					else if (aiNum == 1)
					{
						scoreMap[row][col] += 10;
					}
					else if (aiNum == 2)
					{
						if (emptyNum == 1)
						{
							scoreMap[row][col] += 25;

						}
						else if (emptyNum == 2)
						{
							scoreMap[row][col] += 50;

						}
					}
					else if (aiNum == 3)
					{
						if (emptyNum == 1)
						{
							scoreMap[row][col] += 55;

						}
						else if (emptyNum == 2)
						{
							scoreMap[row][col] += 10000;

						}
					}
					else if (aiNum == 4)
					{
						scoreMap[row][col] +=30000;

					}
				}
			}
			
		}
	}
}

ChessPos AI::aiThink()
{
	calculateScore();//先计算分数
	std::vector<ChessPos> MaxArrays;
	int MaxScore = 0;
	int size = chess->getGradeSize();
	for (int row = 0;row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			if (scoreMap[row][col] > MaxScore)
			{
				MaxScore = scoreMap[row][col];
				MaxArrays.clear();
				MaxArrays.push_back(ChessPos(row, col));
			}
			else if (scoreMap[row][col] == MaxScore)
			{
				MaxArrays.push_back(ChessPos(row, col));

			}
		}
	}
	int index = rand() % MaxArrays.size();//随机选分数相同的位置来下,随机确定起索引（下标）
	return MaxArrays[index];
}
