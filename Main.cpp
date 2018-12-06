#include<string>
#include<iostream>
#include<vector>
#include <stdlib.h>

using namespace std;

class cell
{
public:
	cell(int a, int b): x(a), y(b), type(0), reach(false) {}
	cell() {}
	int x;
	int y;
	int player;
	int type;
	bool reach;
};
class unit : public cell
{
public:
	//unit() {}
	//virtual void make() {}
	int attack;
	int hp;
	int def;
	int od;
	//int player;
};
class archer : public unit
{
public:
	int range = 10;
};
class horseman : public unit
{
public:
	int move = 0;
};
class warrior : public unit
{
public:
	int block = 0;
};

struct hand
{
	unit *u;
	hand *next;
};

int main()
{
	int n, i, j, x, y, k, army, u, stage = 0, turn = 1, xm, ym, xc, yc;
	int *p1, *p2;
	hand *first_player = nullptr;
	hand *second_player = nullptr;
	cin >> n;
	cin >> army;
	p1 = new int[army];
	p2 = new int[army];
	vector<cell> *field = new vector<cell>[n];
	for (i = 0; i < n; i++)
		for (j = 0; j < n * 3; j++)
		{
			cell cl(j, i);
			field[i].push_back(cl);
		}
	string s, ss, command = "";
	s.resize(n * 3 + 2, '_');
	ss.resize(n * 3 + 2, '^');
	/////////////////////////////////
	while (command != "exit")
	{
		/*cout << s << endl;
		for (i = 0; i < n; i++)
		{
			cout << "|";
			for (j = 0; j < n * 3; j++)
			{
				if (field[i][j].empty)
					cout << " ";
				else
					cout << "*";
			}
			cout << "|" << endl;
		}
		cout << ss << endl;
		cout << "Main command:" << endl;
		cin >> command;
		system("cls");*/
		system("cls");
		switch (stage)
		{
		case 0:
			for (j = 0; j < 2; j++)
			{
				system("cls");
				int k = 0;
				string cmd = "", pl;
				if (j == 0)
					pl = "Player One Hand:";
				else
					pl = "Player Two Hand:";
				cout << pl << endl;
				for (i = 0; i < army; i++)
				{
					u = rand() % 3;
					if (j == 0)
						p1[i] = u;
					else
						p2[i] = u;
					if (u == 0)
						cout << "W ";
					else if (u == 1)
						cout << "A ";
					else if (u == 2)
						cout << "H ";
				}
				cout << endl;
				cout << "Pick a Unit You Wanna Change or Print <<ok>>" << endl;
				cin >> cmd;
				while (k < 2 && cmd != "ok")
				{
					system("cls");
					int ch = stoi(cmd) - 1;
					u = rand() % 3;
					cout << pl << endl;
					if (j == 0)
					{
						p1[ch] = u;
						for (i = 0; i < army; i++)
						{
							if (p1[i] == 0)
								cout << "W ";
							else if (p1[i] == 1)
								cout << "A ";
							else
								cout << "H ";
						}
					}
					else
					{
						p2[ch] = u;
						for (i = 0; i < army; i++)
						{
							if (p2[i] == 0)
								cout << "W ";
							else if (p2[i] == 1)
								cout << "A ";
							else
								cout << "H ";
						}
					}
					cout << endl;
					k++;
					if (k < 2)
					{
						cout << "Pick a Unit You Wanna Change or Print <<done>>" << endl;
						cin >> cmd;
					}
				}
			}
			stage++;
			system("cls");
		case 1:
			for (k = 0; k < army; k++)
			{
				string cu;
				if (p1[k] == 0)
					cu = "W";
				else if (p1[k] == 1)
					cu = "A";
				else
					cu = "H";
				cout << "Select Cell for: " << cu << endl;
				cin >> x >> y;
				x--;
				y--;
				field[y][x].player = 1;
				if (cu == "W")
				{
					field[y][x].type = 1;
					hand *hd = new hand;
					hd->u = new warrior;
					//reinterpret_cast<warrior*>(hd.u);
					hd->u->attack = 10;
					hd->u->def = 5;
					hd->u->hp = 100;
					hd->u->od = 3;
					hd->u->x = y;
					hd->u->y = x;
					hd->u->type = 1;
					hd->next = new hand;
					if (first_player != nullptr)
						*(hd->next) = *first_player;
					else
						hd->next = nullptr;
					first_player = hd;
				}
				else if (cu == "A")
				{
					field[y][x].type = 2;
					hand *hd = new hand;
					hd->u = new archer;
					//reinterpret_cast<warrior*>(hd.u);
					hd->u->attack = 10;
					hd->u->def = 1;
					hd->u->hp = 50;
					hd->u->od = 1;
					hd->u->x = y;
					hd->u->y = x;
					hd->u->type = 2;
					hd->next = new hand;
					if (first_player != nullptr)
						*(hd->next) = *first_player;
					else
						hd->next = nullptr;
					first_player = hd;
				}
				else
				{
					field[y][x].type = 3;
					hand *hd = new hand;
					hd->u = new horseman;
					//reinterpret_cast<warrior*>(hd.u);
					hd->u->attack = 15;
					hd->u->def = 3;
					hd->u->hp = 75;
					hd->u->od = 5;
					hd->u->x = y;
					hd->u->y = x;
					hd->u->type = 3;
					hd->next = new hand;
					if (first_player != nullptr)
						*(hd->next) = *first_player;
					else
						hd->next = nullptr;
					first_player = hd;
				}
				//field[x][y] = unt;
				cout << s << endl;
				for (i = 0; i < n; i++)
				{
					cout << "|";
					for (j = 0; j < n * 3; j++)
					{
						if (field[i][j].type == 0)
							cout << " ";
						else if (field[i][j].type == 1)
							cout << "W";
						else if (field[i][j].type == 2)
							cout << "A";
						else if (field[i][j].type == 3)
							cout << "H";
						else
							cout << "*";
					}
					cout << "|" << endl;
				}
				cout << ss << endl;
			}
			stage++;
		case 2:
			for (k = 0; k < army; k++)
			{
				string cu;
				if (p2[k] == 0)
					cu = "W";
				else if (p2[k] == 1)
					cu = "A";
				else
					cu = "H";
				cout << "Select Cell for: " << cu << endl;
				cin >> x >> y;
				x--;
				y--;
				field[y][x].player = 2;
				if (cu == "W")
				{
					field[y][x].type = 1;
					hand *hd = new hand;
					hd->u = new warrior;
					//reinterpret_cast<warrior*>(hd.u);
					hd->u->attack = 10;
					hd->u->def = 5;
					hd->u->hp = 100;
					hd->u->od = 3;
					hd->u->x = y;
					hd->u->y = x;
					hd->u->type = 1;
					hd->next = new hand;
					if (second_player != nullptr)
						*(hd->next) = *second_player;
					else
						hd->next = nullptr;
					second_player = hd;
				}
				else if (cu == "A")
				{
					field[y][x].type = 2;
					hand *hd = new hand;
					hd->u = new archer;
					//reinterpret_cast<warrior*>(hd.u);
					hd->u->attack = 10;
					hd->u->def = 1;
					hd->u->hp = 50;
					hd->u->od = 1;
					hd->u->x = y;
					hd->u->y = x;
					hd->u->type = 2;
					hd->next = new hand;
					if (second_player != nullptr)
						*(hd->next) = *second_player;
					else
						hd->next = nullptr;
					second_player = hd;
				}
				else
				{
					field[y][x].type = 3;
					hand *hd = new hand;
					hd->u = new horseman;
					//reinterpret_cast<warrior*>(hd.u);
					hd->u->attack = 15;
					hd->u->def = 3;
					hd->u->hp = 75;
					hd->u->od = 5;
					hd->u->x = y;
					hd->u->y = x;
					hd->u->type = 3;
					hd->next = new hand;
					if (second_player != nullptr)
						*(hd->next) = *second_player;
					else
						hd->next = nullptr;
					second_player = hd;
				}
				//field[x][y] = unt;
				cout << s << endl;
				for (i = 0; i < n; i++)
				{
					cout << "|";
					for (j = 0; j < n * 3; j++)
					{
						if (field[i][j].type == 0)
							cout << " ";
						else if (field[i][j].type == 1)
							cout << "W";
						else if (field[i][j].type == 2)
							cout << "A";
						else if (field[i][j].type == 3)
							cout << "H";
						else
							cout << "*";
					}
					cout << "|" << endl;
				}
				cout << ss << endl;
			}
			stage++;
			//system("cls");
		case 3:
			system("cls");
			//Field generator
			cout << s << endl;
			for (i = 0; i < n; i++)
			{
				cout << "|";
				for (j = 0; j < n * 3; j++)
				{
					if (field[i][j].type == 0)
						cout << " ";
					else if (field[i][j].type == 1)
						cout << "W";
					else if (field[i][j].type == 2)
						cout << "A";
					else if (field[i][j].type == 3)
						cout << "H";
					else
						cout << "*";
				}
				cout << "|" << endl;
			}
			cout << ss << endl;
			//
			if (turn == 1)
			{
				cout << "Player 1: Chose a unit!" << endl;
				cin >> y >> x;
				y--;
				x--;
				if (field[x][y].type == 0 || field[x][y].player == 2)
				{
					cout << "Wrong Cell" << endl;
				}
				else if (field[x][y].type == 1 || field[x][y].type == 2 || field[x][y].type == 3)
				{
					hand *ptr = first_player;
					while (ptr->u->x != x && ptr->u->y != y)
					{
						ptr = ptr->next;
					}
					//cout << ptr->u->od << endl;///
					for (i = 1; i <= ptr->u->od; i++) 
					{
						if ((x + i < 3 * n) && field[x + i][y].type == 0)
							field[x + i][y].type = 7;
						if ((x - i >= 0) && field[x - i][y].type == 0)
							field[x - i][y].type = 7;
						if ((y + i < n) && field[x][y + i].type == 0)
							field[x][y + i].type = 7;
						if ((y - i >= 0) && field[x][y - i].type == 0)
							field[x][y - i].type = 7;
						///////////////////////////////////////////////////
						if ((x + i < 3 * n) && field[x + i][y].player == 2)
							field[x + i][y].reach == true;
						if ((x - i >= 0) && field[x - i][y].player == 2)
							field[x - i][y].reach == true;
						if ((y + i < n) && field[x][y + i].player == 2)
							field[x][y + i].reach == true;
						if ((y - i >= 0) && field[x][y - i].player == 2)
							field[x][y - i].reach == true;
					}
					system("cls");
					//Field generator
					cout << s << endl;
					for (i = 0; i < n; i++)
					{
						cout << "|";
						for (j = 0; j < n * 3; j++)
						{
							if (field[i][j].type == 0)
								cout << " ";
							else if (field[i][j].type == 1)
								cout << "W";
							else if (field[i][j].type == 2)
								cout << "A";
							else if (field[i][j].type == 3)
								cout << "H";
							else if (field[i][j].type == 7)
								cout << "*";
							else
								cout << "#";
						}
						cout << "|" << endl;
					}
					cout << ss << endl;
					//
					cout << "Player 1: What we gonna do?" << endl;
					cin >> ym >> xm;
					ym--;
					xm--;
					//cout << field[xm][ym].type << endl;///
					if (field[xm][ym].type == 7)
					{
						//cout << "right type" << endl;///
						for (i = 1; i <= ptr->u->od; i++)
						{
							if ((x + i < 3 * n) && field[x + i][y].type == 7)
								field[x + i][y].type = 0;
							if ((x - i >= 0) && field[x - i][y].type == 7)
								field[x - i][y].type = 0;
							if ((y + i < n) && field[x][y + i].type == 7)
								field[x][y + i].type = 0;
							if ((y - i >= 0) && field[x][y - i].type == 7)
								field[x][y - i].type = 0;
							//cout << field[x + i][y].type << ' ' << x + i << ' ' << y << endl;
						}
						ptr->u->x = xm;
						ptr->u->y = ym;
						field[xm][ym].type = ptr->u->type;
						field[x][y].type = 0;
					}
					else if (field[xm][ym].player == 2 && field[xm][ym].reach)
					{
						xc = x;
						yc = y;
						while (xc < xm - 1)
							xc++;
						while (yc < ym - 1)
							yc++;
						//////////////////!!!!!
					}
				}
			}
		}
		

		/*hand *ptr = second_player;
		while (ptr != nullptr) 
		{
			cout << ptr->u->hp << endl;
			ptr = ptr->next;
		}*/
		cout << "Main Command:" << endl;
		cin >> command;
	}
	system("pause");
	return 0;
}