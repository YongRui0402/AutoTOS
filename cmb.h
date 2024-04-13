#include <iostream>
#include <set>
#include <vector>
#include <windows.h>
using namespace std;
#define ROW_SIZE 5
#define COL_SIZE 6

struct Pearl
{
	int pos_x;
	int pos_y;
	int attr;
	bool visited = false;
};
/*
class Pearl{
public:
	int pos_x;
	int pos_y;
	int attr;
	bool visited = false;
};
*/
//int number_plane[5][6] = {0};
Pearl plane[5][6];
vector<Pearl> temp_combo_set;

void swap(Pearl &A, Pearl &B)
{
	//�u�洫��
	int attr = A.attr;
	A.attr = B.attr;
	B.attr = attr;
}

void BFS_combo(vector<Pearl> &delete_combo_handle)
{
	Pearl temp = delete_combo_handle.at(0);
	delete_combo_handle.erase(delete_combo_handle.begin());
	plane[temp.pos_x][temp.pos_y].visited = true;			 //�N�ӯ]�l�P�w���w�ˬd�L
	temp_combo_set.push_back(plane[temp.pos_x][temp.pos_y]); //�[�J�T�w�|������combo��

	//cout << temp.pos_x << " " << temp.pos_y << endl;

	if (plane[temp.pos_x][temp.pos_y].attr == plane[temp.pos_x - 1][temp.pos_y].attr && plane[temp.pos_x][temp.pos_y].attr == plane[temp.pos_x - 2][temp.pos_y].attr && temp.pos_x - 1 >= 0 && temp.pos_x - 2 >= 0)
	{
		if (!plane[temp.pos_x - 1][temp.pos_y].visited)
			delete_combo_handle.push_back(plane[temp.pos_x - 1][temp.pos_y]);
		if (!plane[temp.pos_x - 2][temp.pos_y].visited)
			delete_combo_handle.push_back(plane[temp.pos_x - 2][temp.pos_y]);
	}
	if (plane[temp.pos_x][temp.pos_y].attr == plane[temp.pos_x + 1][temp.pos_y].attr && plane[temp.pos_x][temp.pos_y].attr == plane[temp.pos_x + 2][temp.pos_y].attr && temp.pos_x + 1 < ROW_SIZE && temp.pos_x + 2 < ROW_SIZE)
	{
		if (!plane[temp.pos_x + 1][temp.pos_y].visited)
			delete_combo_handle.push_back(plane[temp.pos_x + 1][temp.pos_y]);
		if (!plane[temp.pos_x + 2][temp.pos_y].visited)
			delete_combo_handle.push_back(plane[temp.pos_x + 2][temp.pos_y]);
	}
	if (plane[temp.pos_x][temp.pos_y].attr == plane[temp.pos_x][temp.pos_y - 1].attr && plane[temp.pos_x][temp.pos_y].attr == plane[temp.pos_x][temp.pos_y - 2].attr && temp.pos_y - 1 >= 0 && temp.pos_y - 2 >= 0)
	{
		//cout << temp.pos_x << " " << temp.pos_y << endl;
		if (!plane[temp.pos_x][temp.pos_y - 1].visited)
			delete_combo_handle.push_back(plane[temp.pos_x][temp.pos_y - 1]);
		if (!plane[temp.pos_x][temp.pos_y - 2].visited)
			delete_combo_handle.push_back(plane[temp.pos_x][temp.pos_y - 2]);
	}
	if (plane[temp.pos_x][temp.pos_y].attr == plane[temp.pos_x][temp.pos_y + 1].attr && plane[temp.pos_x][temp.pos_y].attr == plane[temp.pos_x][temp.pos_y + 2].attr && temp.pos_y + 1 < COL_SIZE && temp.pos_y + 2 < COL_SIZE)
	{
		if (!plane[temp.pos_x][temp.pos_y + 1].visited)
			delete_combo_handle.push_back(plane[temp.pos_x][temp.pos_y + 1]);
		if (!plane[temp.pos_x][temp.pos_y + 2].visited)
			delete_combo_handle.push_back(plane[temp.pos_x][temp.pos_y + 2]);
	}
	if (plane[temp.pos_x][temp.pos_y].attr == plane[temp.pos_x][temp.pos_y + 1].attr && plane[temp.pos_x][temp.pos_y].attr == plane[temp.pos_x][temp.pos_y - 1].attr && temp.pos_y - 1 >= 0 && temp.pos_y + 1 < COL_SIZE)
	{
		if (!plane[temp.pos_x][temp.pos_y + 1].visited)
			delete_combo_handle.push_back(plane[temp.pos_x][temp.pos_y + 1]);
		if (!plane[temp.pos_x][temp.pos_y - 1].visited)
			delete_combo_handle.push_back(plane[temp.pos_x][temp.pos_y - 1]);
	}
	if (plane[temp.pos_x][temp.pos_y].attr == plane[temp.pos_x + 1][temp.pos_y].attr && plane[temp.pos_x][temp.pos_y].attr == plane[temp.pos_x - 1][temp.pos_y].attr && temp.pos_x - 1 >= 0 && temp.pos_x + 1 < ROW_SIZE)
	{
		if (!plane[temp.pos_x + 1][temp.pos_y].visited)
			delete_combo_handle.push_back(plane[temp.pos_x + 1][temp.pos_y]);
		if (!plane[temp.pos_x - 1][temp.pos_y].visited)
			delete_combo_handle.push_back(plane[temp.pos_x - 1][temp.pos_y]);
	}

	if (!delete_combo_handle.empty())
		BFS_combo(delete_combo_handle);
}
void Pop_combo()
{
	while (!temp_combo_set.empty())
	{
		Pearl temp_pearl = temp_combo_set.at(0);
		temp_combo_set.erase(temp_combo_set.begin());
		plane[temp_pearl.pos_x][temp_pearl.pos_y].attr = 0; //����combo
	}
}

void Print_plane()
{
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
		{
			if (plane[i][j].attr != 0)
			{
				cout << plane[i][j].attr << " ";
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
		{ //�q�k�U�����^��
			if (plane[i][j].attr == 0)
			{ //�p�G���Q�d�����]�l
				for (int k = i - 1; k >= 0; k--)
				{ //���W��D�������]�l
					if (plane[k][j].attr != 0)
					{
						swap(plane[k][j], plane[i][j]); //��m�洫
						break;
					}
				}
			}
		}
	}
}

int cmb(int number_plane[ROW_SIZE][COL_SIZE])
{
	for (int i = 0; i < ROW_SIZE; i++)
	{
		for (int j = 0; j < COL_SIZE; j++)
		{
			plane[i][j].attr = number_plane[i][j]+1;
			plane[i][j].pos_x = i;
			plane[i][j].pos_y = j;
		}
	}
	int combo = 0;
	int total_combo = 0;
	//��combo���Y��Jvector �M��i��BFS
	do
	{
		combo = 0;
		for (int i = 0; i < ROW_SIZE; i++)
		{
			for (int j = 0; j < COL_SIZE; j++)
			{
				if (!plane[i][j].visited && plane[i][j].attr != 0 && plane[i][j].attr == plane[i][j + 1].attr && plane[i][j].attr == plane[i][j + 2].attr)
				{
					vector<Pearl> delete_combo_handle;
					delete_combo_handle.push_back(plane[i][j]);
					BFS_combo(delete_combo_handle);
					Pop_combo();
					//Print_plane();
					//Sleep(1000);
					//system("cls");
					combo++;
					total_combo++;
				}
				else if (!plane[i][j].visited && plane[i][j].attr != 0 && plane[i][j].attr == plane[i + 1][j].attr && plane[i][j].attr == plane[i + 2][j].attr)
				{
					vector<Pearl> delete_combo_handle;
					delete_combo_handle.push_back(plane[i][j]);
					BFS_combo(delete_combo_handle);
					Pop_combo();
					//Print_plane();
					//Sleep(1000);
					//system("cls");
					combo++;
					total_combo++;
				}
			}
		}
		Drop();
		//Print_plane();
		//system("pause");
		//system("cls");

		for (int i = 0; i < ROW_SIZE; i++)
		{
			for (int j = 0; j < COL_SIZE; j++)
			{
				plane[i][j].visited = false;
			}
		}

	} while (combo != 0);
	//cout << total_combo << endl;
	//system("pause");
	return total_combo;
}
