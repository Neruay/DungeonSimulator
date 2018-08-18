#include <iostream>
#include <time.h>
#include <cstring>

#pragma warning(disable : 4244)
#pragma warning(disable : 4101)

using namespace std;

int life = 100;
int mana = 100;
int stamina = 100;
int defmod = 0;
int dodge = 15;
int hitchance = 85;
int pots = 5;
int dmgmod = 0;
int crit = 5;
char mtype[5][250] = { "Скелет","Призрак","Зомби","Разбойник","Маг" };
int moblvl;

void draw(char map[21][21]) {
	for (int i = 0; i < 21; i++) {
		cout << endl;
		for (int j = 0; j < 21; j++)
			cout << map[i][j] << " ";
	}
	cout << endl;
}

int posx(char map[21][21]) {
	int position;
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++)
			if (map[i][j] == 'A' || map[i][j] == 'z') {
				position = i;
			}
	}
	return position;
}

int posy(char map[21][21]) {
	int position;
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++)
			if (map[i][j] == 'A' || map[i][j] == 'z') {
				position = j;
			}
	}
	return position;
}

int fight(int monster, int moblvl) {
	srand(time(NULL));
	int mlife[5] = { 50, 100, 150, 200, 300 };
	int mdamage[5] = { rand() % 5 + 10, rand() % 7 + 13, rand() % 9 + 15, rand() % 11 + 18, rand() % 15 + 22 };
	int mdefenseaverage[5] = { rand() % 6 + 7, rand() % 6 + 13, rand() % 6 + 19, rand() % 6 + 24, rand() % 6 + 30 };
	int currentmlife = mlife[moblvl];
	int mdmgmod = 0;
	int victory;
	system("cls");
	while (currentmlife > 0 || life > 0) {
		if (life <= 0) {
			victory = 0;
			break;
		}
		if (currentmlife <= 0) {
			victory = 1;
			break;
		}
		int mdamagedealt = 0;
		int mdamagedealttotal = 0;
		int mdefense = 0;
		int damagetaken = 0;
		int damagedealt = 0;
		int defense = 0;
		int action = 0;
		int intention = rand() % 3;
		char maction[3][150] = { "атаковать!","защищиться!","усилить себя!" };
		switch (intention) {
		case 0: mdamagedealt = mdamage[moblvl]; break;
		case 1: mdefense = mdefenseaverage[moblvl]; break;
		case 2: mdmgmod += 10; break;
		}

		cout << " _________   _________   _________" << endl;
		cout << "|    / |  | | _______ | |   __    |" << endl;
		cout << "|   /  /  | |(       )| |   ||    |" << endl;
		cout << "|  /__/   | | (     ) | |   ||    |" << endl;
		cout << "| //      | |  (___)  | |  (__)   |" << endl;
		cout << " ---------   ---------   ---------" << endl;
		cout << "     1           2          3 (" << pots << ")" << endl;
		cout << endl << endl;
		cout << "Вы (" << life << "/100)		" << mtype[monster] << " (" << currentmlife << "/" << mlife[moblvl] << ")" << endl << endl;
		cout << mtype[monster] << " собирается " << maction[intention] << endl;
		cin >> action;
		switch (action) {
		case 1: damagedealt = ((rand() % 11 + 18) + dmgmod - mdefense); break;
		case 2: defense = defmod + rand() % 9 + 10; break;
		case 3: if (pots > 0) {
			pots--;
			life += 30;
		}
				if (life > 100) life = 100; break;
		}
		if (intention == 2) {
			if (currentmlife + 10 <= mlife[moblvl]) currentmlife += 10;
		}
		mdamagedealttotal = mdamagedealt + mdmgmod;
		damagetaken = mdamagedealttotal - defense;
		if (damagetaken < 0 || mdamagedealt == 0) damagetaken = 0;
		life -= damagetaken;
		if (damagedealt > mdefense) currentmlife -= damagedealt;
		system("cls");
	}
	return victory;
}

int looting(int moblvl) {
	srand(time(NULL));
	int roll;
	int loot;
	char rarity[4][50] = { "обычный","необычный","редкий","легендарный" };
	char prefixes[10][150] = { "Варварский","Сияющий","Крепкий","Отражающий","Шипастый","Отполированный","Надежный","Зачарованый","Удачливый","Чудесный" };
	char suffixes[10][150] = { "льда","пламени","молнии","регенерации","титана","убежища","мастерства","точности","мудреца","бесконечности" };
	char weppref[10][150] = { "Смертоносный","Безжалостный","Пробивающий","Острый","Зазубренный","Сжигающий","Жалящий","Совершенный","Замораживающий","Молниеносный" };
	char wepsuff[10][150] = { "фехтования","триумфа","ярости","разрушения","гладиатора","убийцы","мастерства","расправы","хитрости","стихий" };
	int dmgbuff[4] = { 5,7,10,15 };
	int defbuff[4] = { 5,7,10,15 };
	for (int i = 0; i < 18; i++) {
		roll = rand() % 6 + 1;
		system("cls");
		cout << "	  ______ " << endl;
		cout << "	 /______/|" << endl;
		cout << "	|       ||" << endl;
		cout << "	|   " << roll << "   ||" << endl;
		cout << "	|_______|/" << endl;
	}
	switch (roll) {
	case 1: loot = 0; break;
	case 2: loot = 0; break;
	case 3: loot = 0; break;
	case 4: loot = 1; break;
	case 5: loot = 1; break;
	case 6: loot = 2; break;
	}
	cout << "Вы нашли " << rarity[loot] << " предмет!" << endl;
	int slot = rand() % 3;
	int pref = rand() % 10;
	int suff = rand() % 10;
	switch (slot) {
	case 0: cout << prefixes[pref] << " шлем " << suffixes[suff] << " (+ " << defbuff[loot] << " брони)." << endl; defmod += defbuff[loot]; break;
	case 1: cout << prefixes[pref] << " доспех " << suffixes[suff] << " (+ " << defbuff[loot] << " брони)." << endl; defmod += defbuff[loot]; break;
	case 2: cout << weppref[pref] << " меч " << wepsuff[suff] << " (+ " << dmgbuff[loot] << " атаки)." << endl; dmgmod += dmgbuff[loot]; break;
	}
	if (int i = rand() % 100 + 1 > 66) {
		cout << "Вы нашли зелье восстановления!" << endl;
		pots += 1;
	}
	system("pause");
	system("cls");

	return 0;
}



int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	int xrand = 0;
	int posix;
	int posiy;
	int yrand = 0;
	int x;
	int y;
	int timer = 0;
	int count = 0;
	int random;
	char buff;
	char map[21][21];

	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++)
			map[i][j] = '#';
	}

	/*for (int i = 0; i < 21; i++) {
	for (int j = 0; j < 21; j++)
	if (i == 0 || i == 20 || j == 0 || j == 20) map[i][j] = '#';
	}*/


	/*for (int i = 0; i < 21; i++) {
	for (int j = 0; j < 21; j++) {
	if (rand() % 100 + 1 < chance)
	map[i][j] = '#';
	}
	}*/

	//map[10][10] = 'A';

	//map[rand() % 21][rand() % 21] = '#';

	do {
		xrand = rand() % 19 + 1;
		yrand = rand() % 19 + 1;
	} while (xrand % 2 != 1 && yrand % 2 != 1);

	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++)
			if (i == 0 || i == 20 || j == 0 || j == 20) map[i][j] = '*';
	}

	map[xrand][yrand] = ' ';

	posix = xrand;
	posiy = yrand;

	do {
		int x = 0, y = 0, x1 = 0, y1 = 0;
		if (map[xrand + 2][yrand] == '#' || map[xrand - 2][yrand] == '#' || map[xrand][yrand + 2] == '#' || map[xrand][yrand - 2] == '#') {
			random = rand() % 4 + 1;
			switch (random) {
			case 1: x = 2, y = 0, x1 = 1, y1 = 0; break;
			case 2: x = 0, y = 2, x1 = 0, y1 = 1; break;
			case 3: x = -2, y = 0, x1 = -1, y1 = 0; break;
			case 4: x = 0, y = -2, x1 = 0, y1 = -1; break;
			}
			if (map[xrand + x][yrand + y] != ' ' && map[xrand + x][yrand + y] != '*') {
				if (map[xrand + x - x1][yrand + y - y1] != '*') {
					map[xrand + x][yrand + y] = ' ';
					map[xrand + x - x1][yrand + y - y1] = ' ';
					xrand = xrand + x;
					yrand = yrand + y;
					cout << "	 ИДЁТ ГЕНЕРАЦИЯ КАРТЫ..." << endl;
					draw(map);
					system("cls");
				}
			}
		}
		else xrand = rand() % 19 + 1, yrand = rand() % 19 + 1;
		//do {
		//	xrand = rand() % 21;
		//	yrand = rand() % 21;
		//} while (xrand % 2 != 1 && yrand % 2 != 1);
		count++;
	} while (count < 200);

	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++)
			if (i == 0 || i == 20 || j == 0 || j == 20) map[i][j] = '#';
	}

	map[posix][posiy] = 'A';

	int mcounter = 0;
	do {
		int mx = rand() % 19 + 1;
		int my = rand() % 19 + 1;
		if (map[mx][my] == ' ') {
			map[mx][my] = 'M';
			mcounter++;
		}
		else continue;
	} while (mcounter < 6);

	cout << "		Здоровье : " << life << endl;
	cout << "		Мана : " << mana << endl;
	cout << "		Энергия : " << stamina << endl;

	draw(map);

	char input;
	do {
		cout << endl;
		input = getchar();

		int x = posx(map);
		int y = posy(map);

		if (input == 'w' && map[posx(map) - 1][posy(map)] != '#' && stamina >= 10) {
			system("cls");
			if (map[x - 1][y] == 'M') {
				int monster = rand() % 5;
				moblvl = rand() % 5;
				cout << "	     Здоровье : " << life << endl;
				cout << "	     Мана : " << mana << endl;
				cout << "	     Энергия : " << stamina << endl;
				cout << "	     Сделано ходов: " << timer << endl;
				draw(map);
				cout << endl << "Впереди " << mtype[monster] << " " << moblvl + 1 << " уровня. [1] Сразиться [2] Сбежать" << endl;
				int choice;
				cin >> choice;
				if (choice == 1) {
					if (fight(monster, moblvl) == 1) {
						cout << "Вы победили!" << endl;
						map[x - 1][y] = 'X';
						system("pause");
						system("cls");
						cout << "	     Здоровье : " << life << endl;
						cout << "	     Мана : " << mana << endl;
						cout << "	     Энергия : " << stamina << endl;
						cout << "	     Сделано ходов: " << timer << endl;
						draw(map);
						continue;
					}
					else {
						cout << "Game Over" << endl;
						system("pause");
						break;
					}
				}
				if (choice == 2) {
					system("cls");
					cout << "	     Здоровье : " << life << endl;
					cout << "	     Мана : " << mana << endl;
					cout << "	     Энергия : " << stamina << endl;
					cout << "	     Сделано ходов: " << timer << endl;
					draw(map);
					continue;
				}
			}
			if (map[x - 1][y] == 'X') {
				system("cls");
				looting(moblvl);
				map[x - 1][y] = ' ';
				cout << "	     Здоровье : " << life << endl;
				cout << "	     Мана : " << mana << endl;
				cout << "	     Энергия : " << stamina << endl;
				cout << "	     Сделано ходов: " << timer << endl;
				draw(map);
				continue;

			}
			map[x - 1][y] = 'A';
			map[x][y] = ' ';
			stamina -= 10;
			if (life < 100) life += 5;
			if (life > 100) life = 100;
			cout << "	     Здоровье : " << life << endl;
			cout << "	     Мана : " << mana << endl;
			cout << "	     Энергия : " << stamina << endl;
			timer++;
			cout << "	     Сделано ходов: " << timer << endl;
			draw(map);
		}
		if (input == 'a' && map[posx(map)][posy(map) - 1] != '#' && stamina >= 10) {
			system("cls");
			if (map[x][y - 1] == 'M') {
				int monster = rand() % 5;
				moblvl = rand() % 5;
				cout << "	     Здоровье : " << life << endl;
				cout << "	     Мана : " << mana << endl;
				cout << "	     Энергия : " << stamina << endl;
				cout << "	     Сделано ходов: " << timer << endl;
				draw(map);
				cout << endl << "Впереди " << mtype[monster] << " " << moblvl + 1 << " уровня. [1] Сразиться [2] Сбежать" << endl;
				int choice;
				cin >> choice;
				if (choice == 1) {
					if (fight(monster, moblvl) == 1) {
						cout << "Вы победили!" << endl;
						map[x][y - 1] = 'X';
						system("pause");
						system("cls");
						cout << "	     Здоровье : " << life << endl;
						cout << "	     Мана : " << mana << endl;
						cout << "	     Энергия : " << stamina << endl;
						cout << "	     Сделано ходов: " << timer << endl;
						draw(map);
						continue;
					}
					else {
						cout << "Game Over" << endl;
						system("pause");
						break;
					}
				}
				if (choice == 2) {
					system("cls");
					cout << "	     Здоровье : " << life << endl;
					cout << "	     Мана : " << mana << endl;
					cout << "	     Энергия : " << stamina << endl;
					cout << "	     Сделано ходов: " << timer << endl;
					draw(map);
					continue;
				}
			}
			if (map[x][y - 1] == 'X') {
				system("cls");
				looting(moblvl);
				map[x][y - 1] = ' ';
				cout << "	     Здоровье : " << life << endl;
				cout << "	     Мана : " << mana << endl;
				cout << "	     Энергия : " << stamina << endl;
				cout << "	     Сделано ходов: " << timer << endl;
				draw(map);
				continue;
			}
			map[x][y - 1] = 'A';
			map[x][y] = ' ';
			stamina -= 10;
			if (life < 100) life += 5;
			if (life > 100) life = 100;
			cout << "	     Здоровье : " << life << endl;
			cout << "	     Мана : " << mana << endl;
			cout << "	     Энергия : " << stamina << endl;
			timer++;
			cout << "	     Сделано ходов: " << timer << endl;
			draw(map);
		}
		if (input == 's' && map[posx(map) + 1][posy(map)] != '#' && stamina >= 10) {
			system("cls");
			if (map[x + 1][y] == 'M') {
				int monster = rand() % 5;
				moblvl = rand() % 5;
				cout << "	     Здоровье : " << life << endl;
				cout << "	     Мана : " << mana << endl;
				cout << "	     Энергия : " << stamina << endl;
				cout << "	     Сделано ходов: " << timer << endl;
				draw(map);
				cout << endl << "Впереди " << mtype[monster] << " " << moblvl + 1 << " уровня. [1] Сразиться [2] Сбежать" << endl;
				int choice;
				cin >> choice;
				if (choice == 1) {
					if (fight(monster, moblvl) == 1) {
						cout << "Вы победили!" << endl;
						map[x + 1][y] = 'X';
						system("pause");
						system("cls");
						cout << "	     Здоровье : " << life << endl;
						cout << "	     Мана : " << mana << endl;
						cout << "	     Энергия : " << stamina << endl;
						cout << "	     Сделано ходов: " << timer << endl;
						draw(map);
						continue;
					}
					else {
						cout << "Game Over" << endl;
						break;
					}
				}
				if (choice == 2) {
					system("cls");
					cout << "	     Здоровье : " << life << endl;
					cout << "	     Мана : " << mana << endl;
					cout << "	     Энергия : " << stamina << endl;
					cout << "	     Сделано ходов: " << timer << endl;
					draw(map);
					continue;
				}
			}
			if (map[x + 1][y] == 'X') {
				system("cls");
				looting(moblvl);
				map[x + 1][y] = ' ';
				cout << "	     Здоровье : " << life << endl;
				cout << "	     Мана : " << mana << endl;
				cout << "	     Энергия : " << stamina << endl;
				cout << "	     Сделано ходов: " << timer << endl;
				draw(map);
				continue;
			}
			map[x + 1][y] = 'A';
			map[x][y] = ' ';
			stamina -= 10;
			if (life < 100) life += 5;
			if (life > 100) life = 100;
			cout << "	     Здоровье : " << life << endl;
			cout << "	     Мана : " << mana << endl;
			cout << "	     Энергия : " << stamina << endl;
			timer++;
			cout << "	     Сделано ходов: " << timer << endl;
			draw(map);
		}
		if (input == 'd' && map[posx(map)][posy(map) + 1] != '#' && stamina >= 10) {
			system("cls");
			if (map[x][y + 1] == 'M') {
				int monster = rand() % 5;
				moblvl = rand() % 5;
				cout << "	     Здоровье : " << life << endl;
				cout << "	     Мана : " << mana << endl;
				cout << "	     Энергия : " << stamina << endl;
				cout << "	     Сделано ходов: " << timer << endl;
				draw(map);
				cout << endl << "Впереди " << mtype[monster] << " " << moblvl + 1 << " уровня. [1] Сразиться [2] Сбежать" << endl;
				int choice;
				cin >> choice;
				if (choice == 1) {
					if (fight(monster, moblvl) == 1) {
						cout << "Вы победили!" << endl;
						map[x][y + 1] = 'X';
						system("pause");
						system("cls");
						cout << "	     Здоровье : " << life << endl;
						cout << "	     Мана : " << mana << endl;
						cout << "	     Энергия : " << stamina << endl;
						cout << "	     Сделано ходов: " << timer << endl;
						draw(map);
						continue;
					}
					else {
						cout << "Game Over" << endl;
						system("pause");
						break;
					}
				}
				if (choice == 2) {
					system("cls");
					cout << "	     Здоровье : " << life << endl;
					cout << "	     Мана : " << mana << endl;
					cout << "	     Энергия : " << stamina << endl;
					cout << "	     Сделано ходов: " << timer << endl;
					draw(map);
					continue;
				}
			}
			if (map[x][y + 1] == 'X') {
				system("cls");
				looting(moblvl);
				map[x][y + 1] = ' ';
				cout << "	     Здоровье : " << life << endl;
				cout << "	     Мана : " << mana << endl;
				cout << "	     Энергия : " << stamina << endl;
				cout << "	     Сделано ходов: " << timer << endl;
				draw(map);
				continue;
			}
			map[x][y + 1] = 'A';
			map[x][y] = ' ';
			stamina -= 10;
			if (life < 100) life += 5;
			if (life > 100) life = 100;
			cout << "	     Здоровье : " << life << endl;
			cout << "	     Мана : " << mana << endl;
			cout << "	     Энергия : " << stamina << endl;
			timer++;
			cout << "	     Сделано ходов: " << timer << endl;
			draw(map);
		}

		if (input == 'z') {
			int swch;
			system("cls");
			map[x][y] = 'z';
			if (stamina == 100 && life == 100) {
				map[x][y] = 'A';
				swch = 0;
			}
			if (stamina < 100) {
				swch = 1;
				stamina += 25;
			}
			if (life < 100) {
				swch = 1;
				life += 15;
			}
			if (stamina > 100) stamina = 100;
			if (life > 100) life = 100;

			cout << "	     Здоровье : " << life << endl;
			cout << "	     Мана : " << mana << endl;
			cout << "	     Энергия : " << stamina << endl;
			timer++;
			cout << "	     Сделано ходов: " << timer << endl;
			draw(map);
			if (int i = rand() % 100 + 1 > 66) {
				cout << "Вам удалось приготовить зелье восстановления!" << endl;
				pots += 1;
			}
			if (swch == 1) cout << "Вы отдохнули, восстановив здоровье и энергию" << endl;
			if (swch == 0) cout << "	    Вы пропустили ход" << endl;
		}

		if (input == 'e' && stamina >= 50) {
			cout << endl;
			char direct;
			direct = getchar();
			switch (direct) {
			case 'w': map[x - 1][y] = ' '; stamina -= 50; if (life < 100) life += 5; if (life > 100) life = 100; timer++; break;
			case 'a': map[x][y - 1] = ' '; stamina -= 50; if (life < 100) life += 5; if (life > 100) life = 100; timer++; break;
			case 's': map[x + 1][y] = ' '; stamina -= 50; if (life < 100) life += 5; if (life > 100) life = 100; timer++; break;
			case 'd': map[x][y + 1] = ' '; stamina -= 50; if (life < 100) life += 5; if (life > 100) life = 100; timer++; break;
			default: break;
			}
			system("cls");
			cout << "	     Здоровье : " << life << endl;
			cout << "	     Мана : " << mana << endl;
			cout << "	     Энергия : " << stamina << endl;
			cout << "	     Сделано ходов: " << timer << endl;
			draw(map);
		}
	} while (input != ' ');

	system("pause");
	return 0;
}