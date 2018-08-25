#include <iostream>
#include "enemy.h"
#include "maps.h"
#include "projectile.h"

char *LooksArray[16][3];
void initlarray(){
	for(int i = 0; i < 16; i++){
		for(int j = 0; j < 3; j++){
			LooksArray[i][j] = new char[4];
		}
	}
	std::string mystring;
	//////////////////////////////////
	mystring = " ";
	mystring += (char)1;
	mystring += "  ";
	strcpy(LooksArray[0][0], mystring.c_str());
	LooksArray[0][1] = "/|\\ ";
	LooksArray[0][2] = "/ \\ ";
	//////////////////////////////////
	LooksArray[1][0] = "    ";
	LooksArray[1][1] = ">@< ";
	LooksArray[1][2] = "    ";
	//////////////////////////////////
	mystring = " ";
	mystring += (char)31;
	mystring += "  ";
	strcpy(LooksArray[2][0], mystring.c_str());
	mystring = (char)16;
	mystring += (char)206;
	mystring += (char)17;
	mystring += "  ";
	strcpy(LooksArray[2][1], mystring.c_str());
	mystring = " ";
	mystring += (char)30;
	mystring += "  ";
	strcpy(LooksArray[2][2], mystring.c_str());
	////////////////////////////////
	mystring = " ";
	mystring += (char)1;
	mystring += " o";
	strcpy(LooksArray[3][0], mystring.c_str());
	LooksArray[3][1] = "/|\\|";
	LooksArray[3][2] = "/ \\ ";
}

mapa mmapa = getmap(gmap());
int lastmap = 0;

enemy::enemy(int i, int j, int k, float multiplier){
	type = i;
	x = j;
	y = k;
	switch(type){
	case 0:
		hp = 100;
		attack = 15;
		random = 5;
		randminus = 2;
		maxmana = 0;
		mana = 0;
		manauser = false;
		break;
	case 1:
		hp = 50;
		attack = 30;
		random = 10;
		randminus = 5;
		maxmana = 0;
		mana = 0;
		manauser = false;
		break;
	case 2:
		hp = 250;
		attack = 5;
		random = 3;
		randminus = 1;
		maxmana = 0;
		mana = 0;
		manauser = false;
		break;
	case 3:
		hp = 60;
		attack = 2;
		random = 0;
		randminus = 0;
		maxmana = 50;
		mana = 50;
		manauser = true;
		break;
	}
	hp=hp*multiplier;
	if(hp<1)
		hp=1;
	attack=attack*multiplier;
	if(attack<1)
		attack=1;
	lhp = hp;
	arrowsin = 0;
	moveulazymob = false;
	damaged = false;
	mt = false;
	initlarray();
}

bool canmoveto(int x, int y, int px, int py, std::vector <enemy> &enemies){
	bool can = true;
	if(px!=x||py!=y){
		for(int i = 0; i < enemies.size(); i++){
			if(enemies[i].x == x && enemies[i].y == y){
				can=false;
			}
		}
	}else{
		can = false;
	}
	return can;
}

projtoput enemy::update(int px,int py,int &php, std::vector <enemy> &enemies, int armor){//, std::vector <projectile> &projectiles){
	ptp str;
	str.is = false;
	if(lastmap != gmap()){
		mmapa = getmap(gmap());
	}
	if(lhp > hp){
		damaged = true;
	}else{
		damaged = false;
	}
	if(moveulazymob){
		if(mana >= 10 && px==x && abs(py - y) <= 8 && manauser){
			if(y < py){
				mana -= 10;
				str.is = true;
				str.x = x;
				str.y = y;
				str.d = 2;
				str.t = 1;
			}else{
				mana -= 10;
				str.is = true;
				str.x = x;
				str.y = y;
				str.d = 0;
				str.t = 1;
			}
		}else if(mana >= 10 && py==y && abs(px - x) <= 8 && manauser){
			if(x < px){
				mana -= 10;
				str.is = true;
				str.x = x;
				str.y = y;
				str.d = 1;
				str.t = 1;
			}else{
				mana -= 10;
				str.is = true;
				str.x = x;
				str.y = y;
				str.d = 3;
				str.t = 1;
			}
		}else if(px - x == 1 && py - y == 0){
			if(true)
				int iabc = 0; 
				php -= (attack - ((float)attack*((float)armor/550)));
		}else if(px - x == -1 && py - y == 0){
			if(true)
				int iabc = 0;
				php -= (attack - ((float)attack*((float)armor/550)));
		}else if(py - y == 1 && px - x == 0){
			if(true)
				int iabc = 0;
				php -= (attack - ((float)attack*((float)armor/550)));
		}else if(py - y == -1 && px - x == 0){
			if(true)
				int iabc = 0;
				php -= (attack - ((float)attack*((float)armor/550)));
		}else if(px - x < 8 && px - x > -8){
			if(py - y < 8 && py - y > -8){
				if(px - x < 8 && px - x > 0){
					if(mmapa.main[y][x+1] != 1 && canmoveto(x+1, y, px, py, enemies)){
						x+=1;
					}else if(py - y < 8 && py - y >= 0){
						if(mmapa.main[y+1][x] != 1 && canmoveto(x, y+1, px, py, enemies)){
							y+=1;
						}
					}else{
						if(mmapa.main[y-1][x] != 1 && canmoveto(x, y-1, px, py, enemies)){
							y-=1;
						}
					}
				}else if(px - x < 0 && px - x > -8){
					if(mmapa.main[y][x-1] != 1 && canmoveto(x-1, y, px, py, enemies)){
						x-=1;
					}else if(py - y < 8 && py - y >= 0){
						if(mmapa.main[y+1][x] != 1 && canmoveto(x, y+1, px, py, enemies)){
							y+=1;
						}
					}else{
						if(mmapa.main[y-1][x] != 1 && canmoveto(x, y-1, px, py, enemies)){
							y-=1;
						}
					}
				}else if(py - y < 8 && py - y > 0){
					if(mmapa.main[y+1][x] != 1 && canmoveto(x, y+1, px, py, enemies)){
						y+=1;
					}else if(px - x < 8 && px - x >= 0){
						if(mmapa.main[y][x+1] != 1 && canmoveto(x+1, y, px, py, enemies)){
							x+=1;
						}
					}else{
						if(mmapa.main[y][x-1] != 1 && canmoveto(x-1, y, px, py, enemies)){
							x-=1;
						}
					}
				}else if(py - y < 0 && py - y > -8){
					if(mmapa.main[y-1][x] != 1 && canmoveto(x, y-1, px, py, enemies)){
						y-=1;
					}else if(px - x < 8 && px - x >= 0){
						if(mmapa.main[y][x+1] != 1 && canmoveto(x+1, y, px, py, enemies)){
							x+=1;
						}
					}else{
						if(mmapa.main[y][x-1] != 1 && canmoveto(x-1, y, px, py, enemies)){
							x-=1;
						}
					}
				}
			}
		}
		moveulazymob = false;
	}else{
		moveulazymob=true;
	}
	if(manauser && mt && mana < maxmana){
		mana++;
		mt = false;
	}else{
		mt = true;
	}
	lhp = hp;
	lastmap = gmap();
	return str;
}

void enemy::draw(int k, HANDLE buffer, DWORD &written){
	if(damaged){
		SetConsoleTextAttribute(buffer, 4);
	}
	if(k>=0 && k<=2){
		WriteConsole(buffer, LooksArray[type][k], 4, &written, NULL);
	}
	SetConsoleTextAttribute(buffer, 7);
}

enemy::~enemy(void)
{
}