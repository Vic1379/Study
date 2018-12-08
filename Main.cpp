#include<string>
#include<iostream>
#include<vector>
#include <stdlib.h>
#include <conio.h>
#include <sstream>

using namespace std;

class cell
{
public:
	cell(int a, int b): x(a), y(b), player(-1), type(0), reach(false) {}
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
	int attack;
	int hp;
	int def;
	int od;
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
	//System Variables:
	int n, i, j, k = 0, army, u, stage = 0, turn = 1, one , two;
	bool win = false;
	//Coordinate Variables:
	int x, y, xm, ym, xc, yc, xt, yt;
	//Hand generation variables:
	int *p1, *p2;
	//Main army lists:
	hand *first_player = nullptr;
	hand *second_player = nullptr;
	//Title
	while (!_kbhit())
	{
		if (k >= 10000)
		{
			k = 0;
			system("cls");
			cout << "=============================================================" << endl;
			cout << "=============================================================" << endl;
			cout << "=============================================================" << endl;
			cout << "===  ===  ==       ==     ======    ====       ====      ====" << endl;
			cout << "===  ===  ==  =======  ==  ====  ==  ===  ========  ====  ===" << endl;
			cout << "===  ===  ==  =======  ==  ===  ====  ==  ========  =========" << endl;
			cout << "===       ==       ==    =====  ====  ==       ====      ====" << endl;
			cout << "===  ===  ==  =======  =  ====  ====  ==  ==============  ===" << endl;
			cout << "===  ===  ==  =======  ==  ====  ==  ===  ========  ====  ===" << endl;
			cout << "===  ===  ==       ==  ===  ====    ====       ====      ====" << endl;
			cout << "=============================================================" << endl;
			cout << "============================================CONSOLE=v.b.0001=" << endl;
			cout << "=============================================================   by Viktor inc." << endl;
		}
		k++;
	}
	//
	cout << "Set the size of the field:" << endl;
	cin >> n;
	cout << endl;
	cout << "Set the nuber of units:" << endl;
	cout << endl;
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
	//Decorative and command variables:
	string s, ss, command = "", ys, xs, st;
	xs.resize(n * 3, ' ');
	ys.resize(n * 3, ' ');
	xs[0] = '!';
	xs[n * 3 / 2] = '!';
	xs[n * 3 - 1] = '!';
	ys[0] = '!';
	ys[n / 2] = '!';
	ys[n - 1] = '!';
	s.resize(n * 3 + 3, '_');
	ss.resize(n * 3 + 3, '^');
	s[0] = ' ';
	ss[0] = ' ';
	/////////////////////////////////
	while (command != "exit")
	{
		system("cls");
		switch (stage)
		{
		case 0:
			for (j = 0; j < 2; j++)
			{
				system("cls");
				k = 0;
				string ok = "", pl;
				if (j == 0) pl = "PLAYER 1: Hand:";
				else pl = "PLAYER 2: Hand:";
				cout << pl << endl;
				cout << endl;
				for (i = 0; i < army; i++)
				{
					u = rand() % 3;
					if (j == 0) p1[i] = u;
					else p2[i] = u;
					if (u == 0) cout << "W ";
					else if (u == 1) cout << "A ";
					else if (u == 2) cout << "H ";
				}
				cout << endl;
				cout << endl;
				cout << "Pick a Unit You Wanna Change or Print <<ok>> if you satisfied with your hand." << endl;
				cin >> ok;
				while (k < 3 && ok != "ok")
				{
					system("cls");
					int ch = stoi(ok) - 1;
					u = rand() % 3;
					cout << pl << endl;
					cout << endl;
					if (j == 0)
					{
						p1[ch] = u;
						for (i = 0; i < army; i++)
						{
							if (p1[i] == 0) cout << "W ";
							else if (p1[i] == 1) cout << "A ";
							else cout << "H ";
						}
					}
					else
					{
						p2[ch] = u;
						for (i = 0; i < army; i++)
						{
							if (p2[i] == 0) cout << "W ";
							else if (p2[i] == 1) cout << "A ";
							else cout << "H ";
						}
					}
					cout << endl;
					k++;
					if (k < 3)
					{
						cout << endl;
						cout << "Pick a Unit You Wanna Change or Print <<ok>> if you satisfied with your hand." << endl;
						cin >> ok;
					}
				}
			}
			stage++;
			system("cls");
		case 1:
			for (k = 0; k < army; k++)
			{
				system("cls");
				//Field generator:
				cout << "> ";
				for (i = 0; i < n * 3; i++)
				{
					if (xs[i] == '!') cout << i + 1;
					else cout << ' ';
				}
				cout << endl;
				cout << s << endl;
				for (i = 0; i < n; i++)
				{
					if (ys[i] == '!') cout << i + 1;
					else cout << ' ';
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
				string cu;
				if (p1[k] == 0) cu = "W";
				else if (p1[k] == 1) cu = "A";
				else cu = "H";
				cout << "PLAYER 1: Select Cell for: " << cu << endl;
				cin >> y >> x;
				while (field[x - 1][y - 1].type != 0) cin >> y >> x;
				x--;
				y--;
				field[x][y].player = 1;
				if (cu == "W")
				{
					field[x][y].type = 1;
					hand *hd = new hand;
					hd->u = new warrior;
					//reinterpret_cast<warrior*>(hd.u);
					hd->u->attack = 10;
					hd->u->def = 5;
					hd->u->hp = 100;
					hd->u->od = 3;
					hd->u->x = x;
					hd->u->y = y;
					hd->u->type = 1;
					hd->next = new hand;
					if (first_player != nullptr) *(hd->next) = *first_player;
					else hd->next = nullptr;
					first_player = hd;
				}
				else if (cu == "A")
				{
					field[x][y].type = 2;
					hand *hd = new hand;
					hd->u = new archer;
					//reinterpret_cast<warrior*>(hd.u);
					hd->u->attack = 10;
					hd->u->def = 1;
					hd->u->hp = 50;
					hd->u->od = 1;
					hd->u->x = x;
					hd->u->y = y;
					hd->u->type = 2;
					hd->next = new hand;
					if (first_player != nullptr) *(hd->next) = *first_player;
					else hd->next = nullptr;
					first_player = hd;
				}
				else
				{
					field[x][y].type = 3;
					hand *hd = new hand;
					hd->u = new horseman;
					//reinterpret_cast<warrior*>(hd.u);
					hd->u->attack = 15;
					hd->u->def = 3;
					hd->u->hp = 75;
					hd->u->od = 5;
					hd->u->x = x;
					hd->u->y = y;
					hd->u->type = 3;
					hd->next = new hand;
					if (first_player != nullptr) *(hd->next) = *first_player;
					else hd->next = nullptr;
					first_player = hd;
				}
			}
			stage++;
		case 2:
			for (k = 0; k < army; k++)
			{
				system("cls");
				//Field generator:
				cout << "> ";
				for (i = 0; i < n * 3; i++)
				{
					if (xs[i] == '!') cout << i + 1;
					else cout << ' ';
				}
				cout << endl;
				cout << s << endl;
				for (i = 0; i < n; i++)
				{
					if (ys[i] == '!') cout << i + 1;
					else cout << ' ';
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
				string cu;
				if (p2[k] == 0) cu = "W";
				else if (p2[k] == 1) cu = "A";
				else cu = "H";
				cout << "PLAYER 2: Select Cell for: " << cu << endl;
				cin >> y >> x;
				while (field[x - 1][y - 1].type != 0) cin >> y >> x;
				x--;
				y--;
				field[x][y].player = 2;
				if (cu == "W")
				{
					field[x][y].type = 1;
					hand *hd = new hand;
					hd->u = new warrior;
					//reinterpret_cast<warrior*>(hd.u);
					hd->u->attack = 10;
					hd->u->def = 5;
					hd->u->hp = 100;
					hd->u->od = 3;
					hd->u->x = x;
					hd->u->y = y;
					hd->u->type = 1;
					hd->next = new hand;
					if (second_player != nullptr) *(hd->next) = *second_player;
					else hd->next = nullptr;
					second_player = hd;
				}
				else if (cu == "A")
				{
					field[x][y].type = 2;
					hand *hd = new hand;
					hd->u = new archer;
					hd->u->attack = 10;
					hd->u->def = 1;
					hd->u->hp = 50;
					hd->u->od = 1;
					hd->u->x = x;
					hd->u->y = y;
					hd->u->type = 2;
					hd->next = new hand;
					if (second_player != nullptr) *(hd->next) = *second_player;
					else hd->next = nullptr;
					second_player = hd;
				}
				else
				{
					field[x][y].type = 3;
					hand *hd = new hand;
					hd->u = new horseman;
					hd->u->attack = 15;
					hd->u->def = 3;
					hd->u->hp = 75;
					hd->u->od = 5;
					hd->u->x = x;
					hd->u->y = y;
					hd->u->type = 3;
					hd->next = new hand;
					if (second_player != nullptr) *(hd->next) = *second_player;
					else hd->next = nullptr;
					second_player = hd;
				}
			}
			stage++;
		case 3:
			one = 0;
			two = 0;
			system("cls");
			//Field generator:
			cout << "> ";
			for (i = 0; i < n * 3; i++)
			{
				if (xs[i] == '!') cout << i + 1;
				else cout << ' ';
			}
			cout << endl;
			cout << s << endl;
			for (i = 0; i < n; i++)
			{
				if (ys[i] == '!') cout << i + 1;
				else cout << ' ';
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
					if (field[i][j].player == 1) one++;
					else if (field[i][j].player == 2) two++;
				}
				cout << "|" << endl;
			}
			cout << ss << endl;
			//
			if (one == 0 || two == 0) stage = 5;
			else if (turn == 1)
			{
				cout << "PLAYER 1: Chose a unit!" << endl;
				cin >> y >> x;
				y--;
				x--;
				xt = -1;
				yt = -1;
				//First Preview Loop:
				while (x != xt || y != yt || field[x][y].player != 1)
				{
					system("cls");
					//Field generator:
					cout << "> ";
					for (i = 0; i < n * 3; i++)
					{
						if (xs[i] == '!') cout << i + 1;
						else cout << ' ';
					}
					cout << endl;
					cout << s << endl;
					for (i = 0; i < n; i++)
					{
						if (ys[i] == '!') cout << i + 1;
						else cout << ' ';
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
					if (field[x][y].type == 0) cout << "Terra" << endl;
					else if (field[x][y].type == 13) cout << "Obstacle" << endl;
					else if (field[x][y].type == 1) cout << "Warrior" << endl;
					else if (field[x][y].type == 2) cout << "Archer" << endl;
					else if (field[x][y].type == 3) cout << "Horseman" << endl;
					if (field[x][y].player == 1) cout << "FRIEND" << endl;
					else if (field[x][y].player == 2) cout << "ENEMY" << endl;
					xt = x;
					yt = y;
					cout << endl;
					cout << "PLAYER 1: Chose a unit!" << endl;
					cin >> y >> x;
					y--;
					x--;
				}
				//
				hand *ptr = first_player;
				while (ptr->u->x != x || ptr->u->y != y) ptr = ptr->next;
				//Make the way
				for (i = 1; i <= ptr->u->od; i++)
				{
					if ((x + i < n) && field[x + i][y].type == 0) field[x + i][y].type = 7;
					if ((x - i >= 0) && field[x - i][y].type == 0) field[x - i][y].type = 7;
					if ((y + i < 3 * n) && field[x][y + i].type == 0) field[x][y + i].type = 7;
					if ((y - i >= 0) && field[x][y - i].type == 0) field[x][y - i].type = 7;
					///////////////////////////////////////////////////
					if ((x + i < n) && field[x + i][y].player == 2) field[x + i][y].reach = true;
					if ((x - i >= 0) && field[x - i][y].player == 2) field[x - i][y].reach = true;
					if ((y + i < 3 * n) && field[x][y + i].player == 2) field[x][y + i].reach = true;
					if ((y - i >= 0) && field[x][y - i].player == 2) field[x][y - i].reach = true;
				}
				//
				system("cls");
				//Field generator:
				cout << "> ";
				for (i = 0; i < n * 3; i++)
				{
					if (xs[i] == '!') cout << i + 1;
					else cout << ' ';
				}
				cout << endl;
				cout << s << endl;
				for (i = 0; i < n; i++)
				{
					if (ys[i] == '!') cout << i + 1;
					else cout << ' ';
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
				cout << "Player 1: What we gonna do?" << endl;
				cin >> ym >> xm;
				ym--;
				xm--;
				xt = -1;
				yt = -1;
				//Second Preview Loop:
				while (xm != xt || ym != yt || (!field[xm][ym].reach && field[xm][ym].type != 7))
				{
					system("cls");
					//Field generator:
					cout << "> ";
					for (i = 0; i < n * 3; i++)
					{
						if (xs[i] == '!') cout << i + 1;
						else cout << ' ';
					}
					cout << endl;
					cout << s << endl;
					for (i = 0; i < n; i++)
					{
						if (ys[i] == '!') cout << i + 1;
						else cout << ' ';
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
					if (field[xm][ym].type == 0) cout << "Terra" << endl;
					else if (field[xm][ym].type == 13) cout << "Obstacle" << endl;
					else if (field[xm][ym].type == 1) cout << "Warrior" << endl;
					else if (field[xm][ym].type == 2) cout << "Archer" << endl;
					else if (field[xm][ym].type == 3) cout << "Horseman" << endl;
					else if (field[xm][ym].type == 7) cout << "Move there?" << endl;
					if (field[xm][ym].player == 1) cout << "FRIEND" << endl;
					else if (field[xm][ym].player == 2) cout << "ENEMY" << endl;
					if (field[xm][ym].player == 2 && field[xm][ym].reach) cout << "Attack him?" << endl;
					xt = xm;
					yt = ym;
					cout << endl;
					cout << "PLAYER 1: What we gonna do?" << endl;
					cin >> ym >> xm;
					ym--;
					xm--;
				}
				//
				if (field[xm][ym].type == 7)
				{
					//Clean the way
					for (i = 1; i <= ptr->u->od; i++)
					{
						if ((x + i < n) && field[x + i][y].type == 7) field[x + i][y].type = 0;
						if ((x - i >= 0) && field[x - i][y].type == 7) field[x - i][y].type = 0;
						if ((y + i < 3 * n) && field[x][y + i].type == 7) field[x][y + i].type = 0;
						if ((y - i >= 0) && field[x][y - i].type == 7) field[x][y - i].type = 0;
						//cout << field[x + i][y].type << ' ' << x + i << ' ' << y << endl;
						if ((x + i < n) && field[x + i][y].player == 2) field[x + i][y].reach = false;
						if ((x - i >= 0) && field[x - i][y].player == 2) field[x - i][y].reach = false;
						if ((y + i < 3 * n) && field[x][y + i].player == 2) field[x][y + i].reach = false;
						if ((y - i >= 0) && field[x][y - i].player == 2) field[x][y - i].reach = false;
					}
					//
					ptr->u->x = xm;
					ptr->u->y = ym;
					field[xm][ym].type = ptr->u->type;
					field[xm][ym].player = 1;
					if (x != xm || y != ym)
					{
						field[x][y].type = 0;
						field[x][y].player = -1;
					}
					turn = 2;
				}
				else if (field[xm][ym].player == 2 && field[xm][ym].reach)
				{
					//Clean the way
					for (i = 1; i <= ptr->u->od; i++)
					{
						if ((x + i < n) && field[x + i][y].type == 7) field[x + i][y].type = 0;
						if ((x - i >= 0) && field[x - i][y].type == 7) field[x - i][y].type = 0;
						if ((y + i < 3 * n) && field[x][y + i].type == 7) field[x][y + i].type = 0;
						if ((y - i >= 0) && field[x][y - i].type == 7) field[x][y - i].type = 0;
						//cout << field[x + i][y].type << ' ' << x + i << ' ' << y << endl;
						if ((x + i < n) && field[x + i][y].player == 2) field[x + i][y].reach = false;
						if ((x - i >= 0) && field[x - i][y].player == 2) field[x - i][y].reach = false;
						if ((y + i < 3 * n) && field[x][y + i].player == 2) field[x][y + i].reach = false;
						if ((y - i >= 0) && field[x][y - i].player == 2) field[x][y - i].reach = false;
					}
					//
					xc = x;
					yc = y;
					if (xc < xm) while (xc < xm - 1) xc++;
					else while (xc > xm + 1) xc--;
					if (yc < ym) while (yc < ym - 1) yc++;
					else while (yc > ym + 1) yc--;
					ptr->u->x = xc;
					ptr->u->y = yc;
					field[xc][yc].type = ptr->u->type;
					field[xc][yc].player = 1;
					if (x != xc || y != yc)
					{
						field[x][y].type = 0;
						field[x][y].player = -1;
					}
					hand *ptr2 = second_player;
					while (ptr2->u->x != xm || ptr2->u->y != ym) ptr2 = ptr2->next;
					cout << ptr->u->type << ' ' << ptr->u->hp << " vs " << ptr2->u->type << ' ' << ptr2->u->hp << endl;
					ptr2->u->hp -= (ptr->u->attack - ptr2->u->def);///!!!
					if (ptr2->u->hp > 0) ptr->u->hp -= (ptr2->u->attack - ptr->u->def) / 2;
					cout << ptr->u->type << ' ' << ptr->u->hp << " result " << ptr2->u->type << ' ' << ptr2->u->hp << endl;
					//If Someone Die:
					hand *th;
					if (ptr2->u->hp <= 0)
					{
						if (second_player == ptr2)
						{
							th = ptr2;
							second_player = ptr2->next;
							delete th;
						}
						else
						{
							th = second_player;
							while (th->next != ptr2)
							{
								th = th->next;
							}
							th->next = ptr2->next;
							delete ptr2;
						}
						field[xm][ym].player = -1;
						field[xm][ym].type = 0;
					}
					else if (ptr->u->hp <= 0)
					{
						if (first_player == ptr)
						{
							th = ptr;
							first_player = ptr->next;
							delete th;
						}
						else
						{
							th = first_player;
							while (th->next != ptr) th = th->next;
							th->next = ptr->next;
							delete ptr;
						}
						field[xc][yc].type = 0;
						field[xc][yc].player = -1;
					}
					//
					turn = 2;
				}
			}
			else if (turn == 2)
			{
				cout << "PLAYER 2: Chose a unit!" << endl;
				cin >> y >> x;
				y--;
				x--;
				xt = -1;
				yt = -1;
				//First Preview Loop:
				while (x != xt || y != yt || field[x][y].player != 2)
				{
					system("cls");
					//Field generator:
					cout << "> ";
					for (i = 0; i < n * 3; i++)
					{
						if (xs[i] == '!') cout << i + 1;
						else cout << ' ';
					}
					cout << endl;
					cout << s << endl;
					for (i = 0; i < n; i++)
					{
						if (ys[i] == '!') cout << i + 1;
						else cout << ' ';
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
					if (field[x][y].type == 0) cout << "Terra" << endl;
					else if (field[x][y].type == 13) cout << "Obstacle" << endl;
					else if (field[x][y].type == 1) cout << "Warrior" << endl;
					else if (field[x][y].type == 2) cout << "Archer" << endl;
					else if (field[x][y].type == 3) cout << "Horseman" << endl;
					if (field[x][y].player == 2) cout << "FRIEND" << endl;
					else if (field[x][y].player == 1) cout << "ENEMY" << endl;
					xt = x;
					yt = y;
					cout << endl;
					cout << "PLAYER 2: Chose a unit!" << endl;
					cin >> y >> x;
					y--;
					x--;
				}
				//
				hand *ptr = second_player;
				while (ptr->u->x != x || ptr->u->y != y) ptr = ptr->next;
				//Make the way
				for (i = 1; i <= ptr->u->od; i++)
				{
					if ((x + i < n) && field[x + i][y].type == 0) field[x + i][y].type = 7;
					if ((x - i >= 0) && field[x - i][y].type == 0) field[x - i][y].type = 7;
					if ((y + i < 3 * n) && field[x][y + i].type == 0) field[x][y + i].type = 7;
					if ((y - i >= 0) && field[x][y - i].type == 0) field[x][y - i].type = 7;
					///////////////////////////////////////////////////
					if ((x + i < n) && field[x + i][y].player == 1) field[x + i][y].reach = true;
					if ((x - i >= 0) && field[x - i][y].player == 1) field[x - i][y].reach = true;
					if ((y + i < 3 * n) && field[x][y + i].player == 1) field[x][y + i].reach = true;
					if ((y - i >= 0) && field[x][y - i].player == 1) field[x][y - i].reach = true;
				}
				//
				system("cls");
				//Field generator:
				cout << "> ";
				for (i = 0; i < n * 3; i++)
				{
					if (xs[i] == '!') cout << i + 1;
					else cout << ' ';
				}
				cout << endl;
				cout << s << endl;
				for (i = 0; i < n; i++)
				{
					if (ys[i] == '!') cout << i + 1;
					else cout << ' ';
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
				cout << "PLAYER 2: What we gonna do?" << endl;
				cin >> ym >> xm;
				ym--;
				xm--;
				xt = -1;
				yt = -1;
				//Second Preview Loop:
				while (xm != xt || ym != yt || (!field[xm][ym].reach && field[xm][ym].type != 7))
				{
					system("cls");
					//Field generator:
					cout << "> ";
					for (i = 0; i < n * 3; i++)
					{
						if (xs[i] == '!') cout << i + 1;
						else cout << ' ';
					}
					cout << endl;
					cout << s << endl;
					for (i = 0; i < n; i++)
					{
						if (ys[i] == '!') cout << i + 1;
						else cout << ' ';
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
					if (field[xm][ym].type == 0) cout << "Terra" << endl;
					else if (field[xm][ym].type == 13) cout << "Obstacle" << endl;
					else if (field[xm][ym].type == 1) cout << "Warrior" << endl;
					else if (field[xm][ym].type == 2) cout << "Archer" << endl;
					else if (field[xm][ym].type == 3) cout << "Horseman" << endl;
					else if (field[xm][ym].type == 7) cout << "Move there?" << endl;
					if (field[xm][ym].player == 2) cout << "FRIEND" << endl;
					else if (field[xm][ym].player == 1) cout << "ENEMY" << endl;
					if (field[xm][ym].player == 1 && field[xm][ym].reach) cout << "Attack him?" << endl;
					xt = xm;
					yt = ym;
					cout << endl;
					cout << "PLAYER 2: What we gonna do?" << endl;
					cin >> ym >> xm;
					ym--;
					xm--;
				}
				//
				if (field[xm][ym].type == 7)
				{
					//Clean the way
					for (i = 1; i <= ptr->u->od; i++)
					{
						if ((x + i < n) && field[x + i][y].type == 7) field[x + i][y].type = 0;
						if ((x - i >= 0) && field[x - i][y].type == 7) field[x - i][y].type = 0;
						if ((y + i < 3 * n) && field[x][y + i].type == 7) field[x][y + i].type = 0;
						if ((y - i >= 0) && field[x][y - i].type == 7) field[x][y - i].type = 0;
						/////////////////////////////////////////////
						if ((x + i < n) && field[x + i][y].player == 1) field[x + i][y].reach = false;
						if ((x - i >= 0) && field[x - i][y].player == 1) field[x - i][y].reach = false;
						if ((y + i < 3 * n) && field[x][y + i].player == 1) field[x][y + i].reach = false;
						if ((y - i >= 0) && field[x][y - i].player == 1) field[x][y - i].reach = false;
					}
					//
					ptr->u->x = xm;
					ptr->u->y = ym;
					field[xm][ym].type = ptr->u->type;
					field[xm][ym].player = 2;
					if (x != xm || y != ym)
					{
						field[x][y].type = 0;
						field[x][y].player = -1;
					}
					turn = 1;
				}
				else if (field[xm][ym].player == 1 && field[xm][ym].reach)
				{
					//Clean the way
					for (i = 1; i <= ptr->u->od; i++)
					{
						if ((x + i < n) && field[x + i][y].type == 7) field[x + i][y].type = 0;
						if ((x - i >= 0) && field[x - i][y].type == 7) field[x - i][y].type = 0;
						if ((y + i < 3 * n) && field[x][y + i].type == 7) field[x][y + i].type = 0;
						if ((y - i >= 0) && field[x][y - i].type == 7) field[x][y - i].type = 0;
						/////////////////////////////////////////////
						if ((x + i < n) && field[x + i][y].player == 1) field[x + i][y].reach = false;
						if ((x - i >= 0) && field[x - i][y].player == 1) field[x - i][y].reach = false;
						if ((y + i < 3 * n) && field[x][y + i].player == 1) field[x][y + i].reach = false;
						if ((y - i >= 0) && field[x][y - i].player == 1) field[x][y - i].reach = false;
					}
					//
					xc = x;
					yc = y;
					if (xc < xm) while (xc < xm - 1) xc++;
					else while (xc > xm + 1) xc--;
					if (yc < ym) while (yc < ym - 1) yc++;
					else while (yc > ym + 1) yc--;
					ptr->u->x = xc;
					ptr->u->y = yc;
					field[xc][yc].type = ptr->u->type;
					field[xc][yc].player = 2;
					if (x != xc || y != yc)
					{
						field[x][y].type = 0;
						field[x][y].player = -1;
					}
					hand *ptr2 = first_player;
					while (ptr2->u->x != xm || ptr2->u->y != ym) ptr2 = ptr2->next;
					cout << ptr->u->type << ' ' << ptr->u->hp << " vs " << ptr2->u->type << ' ' << ptr2->u->hp << endl;
					ptr2->u->hp -= (ptr->u->attack - ptr2->u->def);///!!!
					if (ptr2->u->hp > 0) ptr->u->hp -= (ptr2->u->attack - ptr->u->def) / 2;
					cout << ptr->u->type << ' ' << ptr->u->hp << " result " << ptr2->u->type << ' ' << ptr2->u->hp << endl;
					//Is Someone Die:
					hand *th;
					if (ptr2->u->hp <= 0)
					{
						if (first_player == ptr2)
						{
							th = ptr2;
							first_player = ptr2->next;
							delete th;
						}
						else
						{
							th = first_player;
							while (th->next != ptr2) th = th->next;
							th->next = ptr2->next;
							delete ptr2;
						}
						field[xm][ym].player = -1;
						field[xm][ym].type = 0;
					}
					else if (ptr->u->hp <= 0)
					{
						if (second_player == ptr)
						{
							th = ptr;
							second_player = ptr->next;
							delete th;
						}
						else
						{
							th = second_player;
							while (th->next != ptr) th = th->next;
							th->next = ptr->next;
							delete ptr;
						}
						field[xc][yc].type = 0;
						field[xc][yc].player = -1;
					}
					//
					turn = 1;
				}
			}
			/*case 5:
			cout << stage << endl;
			cout << one << ' ' << two << endl;
			if (one == 0)
				cout << "PLAYER 2 Win!" << endl;
			else
				cout << "PLAYER 1 Win!" << endl;
			win = true;*/
		}
		if (stage == 5)
		{
			system("cls");
			if (one == 0)
				cout << "PLAYER 2 WIN!" << endl;
			else
				cout << "PLAYER 1 WIN!" << endl;
			command = "exit";
		}
		else
		{
			cout << "Main Command:" << endl;
			cin >> command;
		}
	}
	system("pause");
	return 0;
}