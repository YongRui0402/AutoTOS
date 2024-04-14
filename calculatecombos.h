#include <iostream>
#include <set>
#include <vector>
#include <windows.h>
using namespace std;
#define ROW_SIZE 5
#define COL_SIZE 6

struct Pearl
{
    int positionX;
    int positionY;
    int attribute;
    bool visited = false;
};

Pearl gamePlane[5][6];
vector<Pearl> temporaryComboSet;

void swapPearls(Pearl &pearlA, Pearl &pearlB)
{
    int tempAttribute = pearlA.attribute;
    pearlA.attribute = pearlB.attribute;
    pearlB.attribute = tempAttribute;
}

void BFS_combo(vector<Pearl> &comboToDelete)
{
	Pearl tempPearl = comboToDelete.at(0);
    comboToDelete.erase(comboToDelete.begin());
    gamePlane[tempPearl.positionX][tempPearl.positionY].visited = true;			 
    temporaryComboSet.push_back(gamePlane[tempPearl.positionX][tempPearl.positionY]); 

	//cout << tempPearl.positionX << " " << tempPearl.positionY << endl;

	if (gamePlane[tempPearl.positionX][tempPearl.positionY].attribute == gamePlane[tempPearl.positionX - 1][tempPearl.positionY].attribute && gamePlane[tempPearl.positionX][tempPearl.positionY].attribute == gamePlane[tempPearl.positionX - 2][tempPearl.positionY].attribute && tempPearl.positionX - 1 >= 0 && tempPearl.positionX - 2 >= 0)
	{
		if (!gamePlane[tempPearl.positionX - 1][tempPearl.positionY].visited)
			comboToDelete.push_back(gamePlane[tempPearl.positionX - 1][tempPearl.positionY]);
		if (!gamePlane[tempPearl.positionX - 2][tempPearl.positionY].visited)
			comboToDelete.push_back(gamePlane[tempPearl.positionX - 2][tempPearl.positionY]);
	}
	if (gamePlane[tempPearl.positionX][tempPearl.positionY].attribute == gamePlane[tempPearl.positionX + 1][tempPearl.positionY].attribute && gamePlane[tempPearl.positionX][tempPearl.positionY].attribute == gamePlane[tempPearl.positionX + 2][tempPearl.positionY].attribute && tempPearl.positionX + 1 < ROW_SIZE && tempPearl.positionX + 2 < ROW_SIZE)
	{
		if (!gamePlane[tempPearl.positionX + 1][tempPearl.positionY].visited)
			comboToDelete.push_back(gamePlane[tempPearl.positionX + 1][tempPearl.positionY]);
		if (!gamePlane[tempPearl.positionX + 2][tempPearl.positionY].visited)
			comboToDelete.push_back(gamePlane[tempPearl.positionX + 2][tempPearl.positionY]);
	}
	if (gamePlane[tempPearl.positionX][tempPearl.positionY].attribute == gamePlane[tempPearl.positionX][tempPearl.positionY - 1].attribute && gamePlane[tempPearl.positionX][tempPearl.positionY].attribute == gamePlane[tempPearl.positionX][tempPearl.positionY - 2].attribute && tempPearl.positionY - 1 >= 0 && tempPearl.positionY - 2 >= 0)
	{
		//cout << tempPearl.positionX << " " << tempPearl.positionY << endl;
		if (!gamePlane[tempPearl.positionX][tempPearl.positionY - 1].visited)
			comboToDelete.push_back(gamePlane[tempPearl.positionX][tempPearl.positionY - 1]);
		if (!gamePlane[tempPearl.positionX][tempPearl.positionY - 2].visited)
			comboToDelete.push_back(gamePlane[tempPearl.positionX][tempPearl.positionY - 2]);
	}
	if (gamePlane[tempPearl.positionX][tempPearl.positionY].attribute == gamePlane[tempPearl.positionX][tempPearl.positionY + 1].attribute && gamePlane[tempPearl.positionX][tempPearl.positionY].attribute == gamePlane[tempPearl.positionX][tempPearl.positionY + 2].attribute && tempPearl.positionY + 1 < COL_SIZE && tempPearl.positionY + 2 < COL_SIZE)
	{
		if (!gamePlane[tempPearl.positionX][tempPearl.positionY + 1].visited)
			comboToDelete.push_back(gamePlane[tempPearl.positionX][tempPearl.positionY + 1]);
		if (!gamePlane[tempPearl.positionX][tempPearl.positionY + 2].visited)
			comboToDelete.push_back(gamePlane[tempPearl.positionX][tempPearl.positionY + 2]);
	}
	if (gamePlane[tempPearl.positionX][tempPearl.positionY].attribute == gamePlane[tempPearl.positionX][tempPearl.positionY + 1].attribute && gamePlane[tempPearl.positionX][tempPearl.positionY].attribute == gamePlane[tempPearl.positionX][tempPearl.positionY - 1].attribute && tempPearl.positionY - 1 >= 0 && tempPearl.positionY + 1 < COL_SIZE)
	{
		if (!gamePlane[tempPearl.positionX][tempPearl.positionY + 1].visited)
			comboToDelete.push_back(gamePlane[tempPearl.positionX][tempPearl.positionY + 1]);
		if (!gamePlane[tempPearl.positionX][tempPearl.positionY - 1].visited)
			comboToDelete.push_back(gamePlane[tempPearl.positionX][tempPearl.positionY - 1]);
	}
	if (gamePlane[tempPearl.positionX][tempPearl.positionY].attribute == gamePlane[tempPearl.positionX + 1][tempPearl.positionY].attribute && gamePlane[tempPearl.positionX][tempPearl.positionY].attribute == gamePlane[tempPearl.positionX - 1][tempPearl.positionY].attribute && tempPearl.positionX - 1 >= 0 && tempPearl.positionX + 1 < ROW_SIZE)
	{
		if (!gamePlane[tempPearl.positionX + 1][tempPearl.positionY].visited)
			comboToDelete.push_back(gamePlane[tempPearl.positionX + 1][tempPearl.positionY]);
		if (!gamePlane[tempPearl.positionX - 1][tempPearl.positionY].visited)
			comboToDelete.push_back(gamePlane[tempPearl.positionX - 1][tempPearl.positionY]);
	}

	if (!comboToDelete.empty())
		BFS_combo(comboToDelete);
}
void Pop_combo()
{
	while (!temporaryComboSet.empty())
	{
		Pearl tempPearl = temporaryComboSet.at(0);
		temporaryComboSet.erase(temporaryComboSet.begin());
		gamePlane[tempPearl.positionX][tempPearl.positionY].attribute = 0; //消除combo
	}
}

void Print_gamePlane()
{
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
		{
			if (gamePlane[i][j].attribute != 0)
			{
				cout << gamePlane[i][j].attribute << " ";
			}
			else
				cout << "  ";
		}
		cout << endl;
	}
}

void Drop()
{
	for (int i = ROW_SIZE - 1; i >= 0; i--)
	{
		for (int j = COL_SIZE - 1; j >= 0; j--)
		{ //從右下角掃回來
			if (gamePlane[i][j].attribute == 0)
			{ //如果有被削除的珠子
				for (int k = i - 1; k >= 0; k--)
				{ //往上找非消除的珠子
					if (gamePlane[k][j].attribute != 0)
					{
						swap(gamePlane[k][j], gamePlane[i][j]); //位置交換
						break;
					}
				}
			}
		}
	}
}

int calculatecombos(int gamePlaneNumbers[ROW_SIZE][COL_SIZE])
{
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
		{
			gamePlane[i][j].attribute = gamePlaneNumbers[i][j]+1;
			gamePlane[i][j].positionX = i;
			gamePlane[i][j].positionY = j;
		}
	}
	int comboCount = 0;
	int totalComboCount = 0;
	//對combo的頭放入vector 然後進行BFS
	do
	{
		comboCount = 0;
		for (int i = 0; i < ROW_SIZE; i++)
		{
			for (int j = 0; j < COL_SIZE; j++)
			{
				if (!gamePlane[i][j].visited && gamePlane[i][j].attribute != 0 && gamePlane[i][j].attribute == gamePlane[i][j + 1].attribute && gamePlane[i][j].attribute == gamePlane[i][j + 2].attribute)
				{
					vector<Pearl> comboToDelete;
					comboToDelete.push_back(gamePlane[i][j]);
					BFS_combo(comboToDelete);
					Pop_combo();

					comboCount++;
					totalComboCount++;
				}
				else if (!gamePlane[i][j].visited && gamePlane[i][j].attribute != 0 && gamePlane[i][j].attribute == gamePlane[i + 1][j].attribute && gamePlane[i][j].attribute == gamePlane[i + 2][j].attribute)
				{
					vector<Pearl> comboToDelete;
					comboToDelete.push_back(gamePlane[i][j]);
					BFS_combo(comboToDelete);
					Pop_combo();

					comboCount++;
					totalComboCount++;
				}
			}
		}
		Drop();


		for (int i = 0; i < ROW_SIZE; i++)
		{
			for (int j = 0; j < COL_SIZE; j++)
			{
				gamePlane[i][j].visited = false;
			}
		}

	} while (comboCount != 0);

	return totalComboCount;
}
