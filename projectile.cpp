#include "projectile.h"
#include "maps.h"

char *PLooksArray[16][3][4];
void initplarray(){
	for(int i = 0; i < 16; i++){
		for(int j = 0; j < 3; j++){
			for(int k = 0; k < 4; k++){
				PLooksArray[i][j][k] = new char[4];
			}
		}
	}
	std::string mystring;
	//////////////////////////////////
	mystring = " ";
	mystring += (char)24;
	mystring += "  ";
	PLooksArray[0][0][0] = "    ";
	strcpy(PLooksArray[0][1][0], mystring.c_str());
	PLooksArray[0][2][0] = "    ";
	//////
	mystring = " -";
	mystring += (char)26;
	mystring += " ";
	PLooksArray[0][0][1] = "    ";
	strcpy(PLooksArray[0][1][1], mystring.c_str());
	PLooksArray[0][2][1] = "    ";
	//////
	mystring = " ";
	mystring += (char)25;
	mystring += "  ";
	PLooksArray[0][0][2] = "    ";
	strcpy(PLooksArray[0][1][2], mystring.c_str());
	PLooksArray[0][2][2] = "    ";
	//////
	mystring = " ";
	mystring += (char)27;
	mystring += "- ";
	PLooksArray[0][0][3] = "    ";
	strcpy(PLooksArray[0][1][3], mystring.c_str());
	PLooksArray[0][2][3] = "    ";
	//////
	mystring = " *  ";
	PLooksArray[1][0][0] = "    ";
	strcpy(PLooksArray[1][1][0], mystring.c_str());
	PLooksArray[1][2][0] = "    ";
	//////
	mystring = " *  ";
	PLooksArray[1][0][1] = "    ";
	strcpy(PLooksArray[1][1][1], mystring.c_str());
	PLooksArray[1][2][1] = "    ";
	//////
	mystring = " *  ";
	PLooksArray[1][0][2] = "    ";
	strcpy(PLooksArray[1][1][2], mystring.c_str());
	PLooksArray[1][2][2] = "    ";
	//////
	mystring = " *  ";
	PLooksArray[1][0][3] = "    ";
	strcpy(PLooksArray[1][1][3], mystring.c_str());
	PLooksArray[1][2][3] = "    ";
	//////
}

projectile::projectile(int prx, int pry, int dir, int prtype)
{
	x = prx;
	y = pry;
	direction=dir;
	type=prtype;
	flied = 0;
	switch(type){
	case 0:
		dmg = 20;
		range = 7;
		break;
	case 1:
		dmg = 10;
		range = 9;
		break;
	}
	initplarray();
}

bool impacted(int x, int y, int px, int py, std::vector <enemy> &enemies, bool &isplayer, int &enid){
	bool isi=false;
	if(px!=x||py!=y){
		for(int i = 0; i < enemies.size(); i++){
			if(enemies[i].x == x && enemies[i].y == y){
				isi=true;
				isplayer = false;
				enid = i;
				break;
			}
		}
	}else{
		isi=true;
		isplayer = true;
	}
	return isi;
}

bool projectile::update(int px, int py, int &php, std::vector <enemy> &enemies, int &arrows, float multiplier){
	bool pl = false;
	int eid = 0;
	if(flied == 0){
		switch(direction){
			case 0:
				y--;
				break;
			case 1:
				x++;
				break;
			case 2:
				y++;
				break;
			case 3:
				x--;
				break;
		}
	}else{
		if(!impacted(x, y, px, py, enemies, pl, eid)){
			switch(direction){
			case 0:
				y--;
				break;
			case 1:
				x++;
				break;
			case 2:
				y++;
				break;
			case 3:
				x--;
				break;
			}
		}
	}
	if(getmap(gmap()).main[y][x]==0||getmap(gmap()).main[y][x]==2){
		if(impacted(x, y, px, py, enemies, pl, eid)){
			if(pl){
				int dmgmult=dmg*((multiplier+1)/2);
				if(dmgmult < 1)
					dmgmult = 1;
				php -= dmgmult;
			}else{
				enemies[eid].hp -= dmg;
				if(rand()%4 == 0){
					enemies[eid].arrowsin+=1;
				}
				if(enemies[eid].hp <= 0){
					arrows += enemies[eid].arrowsin;
					enemies[eid].~enemy();
					enemies.erase(enemies.begin() + eid);
				}
			}
			switch(direction){
			case 0:
				y++;
				break;
			case 1:
				x--;
				break;
			case 2:
				y--;
				break;
			case 3:
				x++;
				break;
			}
			return false;
		}
		flied++;
		if(flied >= range){
			return false;
		}
		return true;
	}else{
			switch(direction){
			case 0:
				y++;
				break;
			case 1:
				x--;
				break;
			case 2:
				y--;
				break;
			case 3:
				x++;
				break;
			}
		return false;
	}
}

void projectile::draw(int k, HANDLE buffer, DWORD &written){
	if(k>=0 && k<=2){
		if(type == 1)
			SetConsoleTextAttribute(buffer, rand() %4 + 1);
		WriteConsole(buffer, PLooksArray[type][k][direction], 4, &written, NULL);
		SetConsoleTextAttribute(buffer, 7);
	}
}

projectile::~projectile(void)
{
}