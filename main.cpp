#include <iostream>
#include <thread>
#include <vector>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <random>
#include <sstream>

#include "maps.h"
#include "enemy.h"
#include "projectile.h"
#include "inventory.h"
//sciana - 177

// 0
//3 1
// 2
int px = 0;
int py = 0;
int php = 100;
int lhp = php;
int panimstate = 0;
int eventtoget = 0;
int activebuffer = 0;
int facing = 0;
int arrows = 0;
int arrowslimit = 48;
int cemap = 0;
int menuselectedposition = 0;
int lootid[128];
int lootnr[128];
float monsterstrenght = 1.0f;
bool isinventory = false;
bool bow = false;
bool pdamaged = false;
bool keysrunning = true;
char armorydamagy[4] = {176, 177, 178, 219};
char* armordmg[4] = {&armorydamagy[0], &armorydamagy[1], &armorydamagy[2], &armorydamagy[3]};
HANDLE buffer = CreateConsoleScreenBuffer( GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
HANDLE buffer2 = CreateConsoleScreenBuffer( GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
HANDLE tbuffer;
DWORD written;
inventory pinventory;
inventory pinventoryempty;
mapa mmmapa = getmap(0);
std::vector <enemy> enemies;
std::vector <projectile> projectiles;


struct menu{
	const char* title;
	int titlel;
	char* names[9];
	int namesl[9];
	int poscount;
};

void drawmearmor(){
	int admg = 0;
	if(pinventory.aworn[0] == 1){
		if(!pdamaged)
			SetConsoleTextAttribute(tbuffer, 6);
		admg = pinventory.adestroy[0];
	}else if(pinventory.aworn[0] == 2){
		if(!pdamaged)
			SetConsoleTextAttribute(tbuffer, 8);
		admg = pinventory.adestroy[4];
	}else if(pinventory.aworn[0] == 3){
		if(!pdamaged)
			SetConsoleTextAttribute(tbuffer, 7);
		admg = pinventory.adestroy[8];
	}else if(pinventory.aworn[0] == 4){
		if(!pdamaged)
			SetConsoleTextAttribute(tbuffer, 3);
		admg = pinventory.adestroy[12];
	}else if(pinventory.aworn[0] == 5){
		if(!pdamaged)
			SetConsoleTextAttribute(tbuffer, 4);
		admg = pinventory.adestroy[16];
	}
	if(pinventory.aworn[0] != 0){
		if(admg >= 0 && admg <= 3){
			WriteConsole(tbuffer, "/", 1, &written, NULL);
			WriteConsole(tbuffer, armordmg[admg], 1, &written, NULL);
			WriteConsole(tbuffer, "\\", 1, &written, NULL);
		}else{
			WriteConsole(tbuffer, "/|\\", 3, &written, NULL);
		}
		if(pdamaged){
			SetConsoleTextAttribute(tbuffer, 4);
		}else{
			SetConsoleTextAttribute(tbuffer, 7);
		}
	}else{
		WriteConsole(tbuffer, "/|\\", 3, &written, NULL);
	}
}

void drawmelegs(){
	if(pinventory.aworn[2] == 1){
		if(!pdamaged)
			SetConsoleTextAttribute(tbuffer, 6);
	}else if(pinventory.aworn[2] == 2){
		if(!pdamaged)
			SetConsoleTextAttribute(tbuffer, 8);
	}else if(pinventory.aworn[2] == 3){
		if(!pdamaged)
			SetConsoleTextAttribute(tbuffer, 7);
	}else if(pinventory.aworn[2] == 4){
		if(!pdamaged)
			SetConsoleTextAttribute(tbuffer, 3);
	}else if(pinventory.aworn[2] == 5){
		if(!pdamaged)
			SetConsoleTextAttribute(tbuffer, 4);
	}
	WriteConsole(tbuffer, "/ \\", 3, &written, NULL);
	if(pdamaged){
		SetConsoleTextAttribute(tbuffer, 4);
	}else{
		SetConsoleTextAttribute(tbuffer, 7);
	}
}

HANDLE drawb(){
	tbuffer = CreateConsoleScreenBuffer( GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	COORD SIZE_COORD = { 85, 26 };
	SetConsoleScreenBufferSize(tbuffer, SIZE_COORD);

	char aaa = 219;
	const char* lol = &aaa;
	bool damaged = false;
	//hp
	WriteConsole(tbuffer, "HP:", 3, &written, NULL);
	SetConsoleTextAttribute(tbuffer, 4);
	for(int i = 0; i < php/5; i++){
		WriteConsole(tbuffer, lol, 1, &written, NULL);
		WriteConsole(tbuffer, lol, 1, &written, NULL);
	}
	for(int i = 0; i < 20 - php/5; i++){
		WriteConsole(tbuffer, "  ", 2, &written, NULL);
	}
	WriteConsole(tbuffer, "|", 1, &written, NULL);
	SetConsoleTextAttribute(tbuffer, 7);

	if(php==100){
		WriteConsole(tbuffer, "1", 1, &written, NULL);
	}else{
		WriteConsole(tbuffer, " ", 1, &written, NULL);
	}
	char hptens = 48 + (((php%100) - (php%10)) / 10);
	char* hptensp = &hptens;
	WriteConsole(tbuffer, hptensp, 1, &written, NULL);
	char hpones = 48 + (php%10);
	char* hponesp = &hpones;
	WriteConsole(tbuffer, hponesp, 1, &written, NULL);
	WriteConsole(tbuffer, "/100", 4, &written, NULL);
	//arrows
	WriteConsole(tbuffer, "             Arrows:", 20, &written, NULL);
	char arrowshunderts = 48 + ((arrows - (arrows%100)) / 100);
	if(arrowshunderts != 48){
		char* arrowshundertsp = &arrowshunderts;
		WriteConsole(tbuffer, arrowshundertsp, 1, &written, NULL);
	}
	char arrowstens = 48 + (((arrows%100) - (arrows%10)) / 10);
	char* arrowstensp = &arrowstens;
	WriteConsole(tbuffer, arrowstensp, 1, &written, NULL);
	char arrowsones = 48 + (arrows%10);
	char* arrowsonesp = &arrowsones;
	WriteConsole(tbuffer, arrowsonesp, 1, &written, NULL);
	WriteConsole(tbuffer, "/", 1, &written, NULL);
	char arrowslimithunderts = 48 + ((arrowslimit - (arrowslimit%100)) / 100);
	if(arrowslimithunderts !=48){
		char* arrowslimithundertsp = &arrowslimithunderts;
		WriteConsole(tbuffer, arrowslimithundertsp, 1, &written, NULL);
	}
	char arrowslimittens = 48 + (((arrowslimit%100) - (arrowslimit%10)) / 10);
	char* arrowslimittensp = &arrowslimittens;
	WriteConsole(tbuffer, arrowslimittensp, 1, &written, NULL);
	char arrowslimitones = 48 + (arrowslimit%10);
	char* arrowslimitonesp = &arrowslimitones;
	WriteConsole(tbuffer, arrowslimitonesp, 1, &written, NULL);
	//
	WriteConsole(tbuffer, "|HOTKEY:\n", 9, &written, NULL);

	//reszta
	for(int i = -4; i < 4; i++){
		for(int k = 0; k < 3; k++){
			for(int j = -9; j < 10; j++){
				if(i != 0 || j != 0){
					if(px + j >= 0 && px + j <= 63){
						if(py + i >= 0 && py + i <= 47){
							bool done = false;
							for(int l = 0; l < enemies.size(); l++){
								if(enemies[l].x == px + j && enemies[l].y == py + i){
									enemies[l].draw(k, tbuffer, written);
									done = true;
								}
							}
							if(!done){
								bool isp = false;
								for(int m = 0; m < projectiles.size(); m++){
									if(projectiles[m].x == px + j && projectiles[m].y == py + i){
										projectiles[m].draw(k, tbuffer, written);
										isp = true;
									}
								}
								if(!isp){
									if(mmmapa.main[py + i][px + j] == 0 || mmmapa.main[py + i][px + j] == 2){
										WriteConsole(tbuffer, "    ", 4, &written, NULL);
									}
									else if(mmmapa.main[py+i][px+j] == 3){
										int aaabb = 0;
										for(int aaabbb = 0; aaabbb < 128; aaabbb++){
											if(lootid[aaabbb]==((py+i)*64)+(px+j)){
												aaabb = lootnr[aaabbb];
												break;
											}
										}
										if(aaabb == 0){
											if(k==0){
												WriteConsole(tbuffer, "    ", 4, &written, NULL);
											}else if(k==1){
												char bbb = 3;
												const char* lawl = &bbb;
												WriteConsole(tbuffer, " (", 2, &written, NULL);
												WriteConsole(tbuffer, lawl, 1, &written, NULL);
												WriteConsole(tbuffer, ")", 1, &written, NULL);
											}else if(k==2){
												WriteConsole(tbuffer, "    ", 4, &written, NULL);
											}
										}else{
											if(k==0){
												WriteConsole(tbuffer, " vv ", 4, &written, NULL);
											}else if(k==1){
												WriteConsole(tbuffer, "{ / ", 4, &written, NULL);
											}else if(k==2){
												WriteConsole(tbuffer, "|/  ", 4, &written, NULL);
											}
										}
									}else if(mmmapa.main[py + i][px + j] == 4){
										if(k==0){
												WriteConsole(tbuffer, " __ ", 4, &written, NULL);
											}else if(k==1){
												WriteConsole(tbuffer, "|<>|", 4, &written, NULL);
											}else if(k==2){
												WriteConsole(tbuffer, "|__|", 4, &written, NULL);
											}
									}else if(mmmapa.main[py + i][px + j] == 5){
										SetConsoleTextAttribute(tbuffer, 2);
										WriteConsole(tbuffer, lol, 1, &written, NULL);
										WriteConsole(tbuffer, lol, 1, &written, NULL);
										WriteConsole(tbuffer, lol, 1, &written, NULL);
										WriteConsole(tbuffer, lol, 1, &written, NULL);
										SetConsoleTextAttribute(tbuffer, 7);
									}else{
										WriteConsole(tbuffer, lol, 1, &written, NULL);
										WriteConsole(tbuffer, lol, 1, &written, NULL);
										WriteConsole(tbuffer, lol, 1, &written, NULL);
										WriteConsole(tbuffer, lol, 1, &written, NULL);
									}
								}
							}
						}else{
							WriteConsole(tbuffer, lol, 1, &written, NULL);
							WriteConsole(tbuffer, lol, 1, &written, NULL);
							WriteConsole(tbuffer, lol, 1, &written, NULL);
							WriteConsole(tbuffer, lol, 1, &written, NULL);
						}
					}else{
						WriteConsole(tbuffer, lol, 1, &written, NULL);
						WriteConsole(tbuffer, lol, 1, &written, NULL);
						WriteConsole(tbuffer, lol, 1, &written, NULL);
						WriteConsole(tbuffer, lol, 1, &written, NULL);
					}
				}else{
					char ccc = 2;
					const char* xd = &ccc;
					if(pdamaged){
						SetConsoleTextAttribute(tbuffer, 4);
					}
					switch(panimstate){
					case 0:
						if(k==0){
							if(!pdamaged){
								switch(pinventory.aworn[1]){
								case 1:
									SetConsoleTextAttribute(tbuffer, 6);
									break;
								case 2:
									SetConsoleTextAttribute(tbuffer, 8);
									break;
								case 3:
									SetConsoleTextAttribute(tbuffer, 7);
									break;
								case 4:
									SetConsoleTextAttribute(tbuffer, 3);
									break;
								case 5:
									SetConsoleTextAttribute(tbuffer, 4);
									break;
								};
							}
							if(pinventory.aworn[1] != 0){
								WriteConsole(tbuffer, "[", 1, &written, NULL);
								WriteConsole(tbuffer, xd, 1, &written, NULL);
								WriteConsole(tbuffer, "]", 1, &written, NULL);
							}else{
								WriteConsole(tbuffer, " ", 1, &written, NULL);
								WriteConsole(tbuffer, xd, 1, &written, NULL);
								WriteConsole(tbuffer, " ", 1, &written, NULL);
							}
							if(pdamaged){
								SetConsoleTextAttribute(tbuffer, 4);
							}else{
								SetConsoleTextAttribute(tbuffer, 7);
							}
							WriteConsole(tbuffer, "|", 1, &written, NULL);
						}else if(k==1){
							drawmearmor();
							WriteConsole(tbuffer, "|", 1, &written, NULL);
						}else if(k==2){
							drawmelegs();
							WriteConsole(tbuffer, " ", 1, &written, NULL);
						}
						break;
					case 1:
						if(k==0){
							WriteConsole(tbuffer, "|", 1, &written, NULL);
							if(!pdamaged){
								switch(pinventory.aworn[1]){
								case 1:
									SetConsoleTextAttribute(tbuffer, 6);
									break;
								case 2:
									SetConsoleTextAttribute(tbuffer, 8);
									break;
								case 3:
									SetConsoleTextAttribute(tbuffer, 7);
									break;
								case 4:
									SetConsoleTextAttribute(tbuffer, 3);
									break;
								case 5:
									SetConsoleTextAttribute(tbuffer, 4);
									break;
								};
							}
							if(pinventory.aworn[1] != 0){
								WriteConsole(tbuffer, "[", 1, &written, NULL);
								WriteConsole(tbuffer, xd, 1, &written, NULL);
								WriteConsole(tbuffer, "]", 1, &written, NULL);
							}else{
								WriteConsole(tbuffer, " ", 1, &written, NULL);
								WriteConsole(tbuffer, xd, 1, &written, NULL);
								WriteConsole(tbuffer, " ", 1, &written, NULL);
							}
							if(pdamaged){
								SetConsoleTextAttribute(tbuffer, 4);
							}else{
								SetConsoleTextAttribute(tbuffer, 7);
							}
						}else if(k==1){
							WriteConsole(tbuffer, "|", 1, &written, NULL);
							drawmearmor();
						}else if(k==2){
							WriteConsole(tbuffer, " ", 1, &written, NULL);
							drawmelegs();
						}
						break;
					case 2:
						if(k==0){
							if(!pdamaged){
								switch(pinventory.aworn[1]){
								case 1:
									SetConsoleTextAttribute(tbuffer, 6);
									break;
								case 2:
									SetConsoleTextAttribute(tbuffer, 8);
									break;
								case 3:
									SetConsoleTextAttribute(tbuffer, 7);
									break;
								case 4:
									SetConsoleTextAttribute(tbuffer, 3);
									break;
								case 5:
									SetConsoleTextAttribute(tbuffer, 4);
									break;
								};
							}
							if(pinventory.aworn[1] != 0){
								WriteConsole(tbuffer, "[", 1, &written, NULL);
								WriteConsole(tbuffer, xd, 1, &written, NULL);
								WriteConsole(tbuffer, "] ", 2, &written, NULL);
							}else{
								WriteConsole(tbuffer, " ", 1, &written, NULL);
								WriteConsole(tbuffer, xd, 1, &written, NULL);
								WriteConsole(tbuffer, "  ", 2, &written, NULL);
							}
							if(pdamaged){
								SetConsoleTextAttribute(tbuffer, 4);
							}else{
								SetConsoleTextAttribute(tbuffer, 7);
							}
						}else if(k==1){
							drawmearmor();
							WriteConsole(tbuffer, "\\", 1, &written, NULL);
						}else if(k==2){
							drawmelegs();
							WriteConsole(tbuffer, " ", 1, &written, NULL);
						}
						break;
					case 3:
						if(k==0){
							if(!pdamaged){
								switch(pinventory.aworn[1]){
								case 1:
									SetConsoleTextAttribute(tbuffer, 6);
									break;
								case 2:
									SetConsoleTextAttribute(tbuffer, 8);
									break;
								case 3:
									SetConsoleTextAttribute(tbuffer, 7);
									break;
								case 4:
									SetConsoleTextAttribute(tbuffer, 3);
									break;
								case 5:
									SetConsoleTextAttribute(tbuffer, 4);
									break;
								};
							}
							if(pinventory.aworn[1] != 0){
								WriteConsole(tbuffer, " [", 2, &written, NULL);
								WriteConsole(tbuffer, xd, 1, &written, NULL);
								WriteConsole(tbuffer, "]", 1, &written, NULL);
							}else{
								WriteConsole(tbuffer, "  ", 2, &written, NULL);
								WriteConsole(tbuffer, xd, 1, &written, NULL);
								WriteConsole(tbuffer, " ", 1, &written, NULL);
							}
							if(pdamaged){
								SetConsoleTextAttribute(tbuffer, 4);
							}else{
								SetConsoleTextAttribute(tbuffer, 7);
							}
						}else if(k==1){
							WriteConsole(tbuffer, "/", 1, &written, NULL);
							drawmearmor();
						}else if(k==2){
							WriteConsole(tbuffer, " ", 1, &written, NULL);
							drawmelegs();
						}
						break;
					case 4:
						if(k==0){
							if(!pdamaged){
								switch(pinventory.aworn[1]){
								case 1:
									SetConsoleTextAttribute(tbuffer, 6);
									break;
								case 2:
									SetConsoleTextAttribute(tbuffer, 8);
									break;
								case 3:
									SetConsoleTextAttribute(tbuffer, 7);
									break;
								case 4:
									SetConsoleTextAttribute(tbuffer, 3);
									break;
								case 5:
									SetConsoleTextAttribute(tbuffer, 4);
									break;
								};
							}
							if(pinventory.aworn[1] != 0){
								WriteConsole(tbuffer, "[", 1, &written, NULL);
								WriteConsole(tbuffer, xd, 1, &written, NULL);
								WriteConsole(tbuffer, "] ", 2, &written, NULL);
							}else{
								WriteConsole(tbuffer, " ", 1, &written, NULL);
								WriteConsole(tbuffer, xd, 1, &written, NULL);
								WriteConsole(tbuffer, "  ", 2, &written, NULL);
							}
							if(pdamaged){
								SetConsoleTextAttribute(tbuffer, 4);
							}else{
								SetConsoleTextAttribute(tbuffer, 7);
							}
						}else if(k==1){
							drawmearmor();
							WriteConsole(tbuffer, "/", 1, &written, NULL);
						}else if(k==2){
							drawmelegs();
							WriteConsole(tbuffer, " ", 1, &written, NULL);
						}
						break;
					case 5:
						if(k==0){
							if(!pdamaged){
								switch(pinventory.aworn[1]){
								case 1:
									SetConsoleTextAttribute(tbuffer, 6);
									break;
								case 2:
									SetConsoleTextAttribute(tbuffer, 8);
									break;
								case 3:
									SetConsoleTextAttribute(tbuffer, 7);
									break;
								case 4:
									SetConsoleTextAttribute(tbuffer, 3);
									break;
								case 5:
									SetConsoleTextAttribute(tbuffer, 4);
									break;
								};
							}
							if(pinventory.aworn[1] != 0){
								WriteConsole(tbuffer, " [", 2, &written, NULL);
								WriteConsole(tbuffer, xd, 1, &written, NULL);
								WriteConsole(tbuffer, "]", 1, &written, NULL);
							}else{
								WriteConsole(tbuffer, "  ", 2, &written, NULL);
								WriteConsole(tbuffer, xd, 1, &written, NULL);
								WriteConsole(tbuffer, " ", 1, &written, NULL);
							}
							if(pdamaged){
								SetConsoleTextAttribute(tbuffer, 4);
							}else{
								SetConsoleTextAttribute(tbuffer, 7);
							}
						}else if(k==1){
							WriteConsole(tbuffer, "\\", 1, &written, NULL);
							drawmearmor();
						}else if(k==2){
							WriteConsole(tbuffer, " ", 1, &written, NULL);
							drawmelegs();
						}
						break;
					case 6:
						if(k==0){
							if(!pdamaged){
								switch(pinventory.aworn[1]){
								case 1:
									SetConsoleTextAttribute(tbuffer, 6);
									break;
								case 2:
									SetConsoleTextAttribute(tbuffer, 8);
									break;
								case 3:
									SetConsoleTextAttribute(tbuffer, 7);
									break;
								case 4:
									SetConsoleTextAttribute(tbuffer, 3);
									break;
								case 5:
									SetConsoleTextAttribute(tbuffer, 4);
									break;
								};
							}
							if(pinventory.aworn[1] != 0){
								WriteConsole(tbuffer, "[", 1, &written, NULL);
								WriteConsole(tbuffer, xd, 1, &written, NULL);
								WriteConsole(tbuffer, "] ", 2, &written, NULL);
							}else{
								WriteConsole(tbuffer, " ", 1, &written, NULL);
								WriteConsole(tbuffer, xd, 1, &written, NULL);
								WriteConsole(tbuffer, "  ", 2, &written, NULL);
							}
							if(pdamaged){
								SetConsoleTextAttribute(tbuffer, 4);
							}else{
								SetConsoleTextAttribute(tbuffer, 7);
							}
						}else if(k==1){
							drawmearmor();
							WriteConsole(tbuffer, "|", 1, &written, NULL);
						}else if(k==2){
							drawmelegs();
							WriteConsole(tbuffer, " ", 1, &written, NULL);
						}
						break;
					case 7:
						if(k==0){
							if(!pdamaged){
								switch(pinventory.aworn[1]){
								case 1:
									SetConsoleTextAttribute(tbuffer, 6);
									break;
								case 2:
									SetConsoleTextAttribute(tbuffer, 8);
									break;
								case 3:
									SetConsoleTextAttribute(tbuffer, 7);
									break;
								case 4:
									SetConsoleTextAttribute(tbuffer, 3);
									break;
								case 5:
									SetConsoleTextAttribute(tbuffer, 4);
									break;
								};
							}
							if(pinventory.aworn[1] != 0){
								WriteConsole(tbuffer, " [", 2, &written, NULL);
								WriteConsole(tbuffer, xd, 1, &written, NULL);
								WriteConsole(tbuffer, "]", 1, &written, NULL);
							}else{
								WriteConsole(tbuffer, "  ", 2, &written, NULL);
								WriteConsole(tbuffer, xd, 1, &written, NULL);
								WriteConsole(tbuffer, " ", 1, &written, NULL);
							}
							if(pdamaged){
								SetConsoleTextAttribute(tbuffer, 4);
							}else{
								SetConsoleTextAttribute(tbuffer, 7);
							}
						}else if(k==1){
							WriteConsole(tbuffer, "|", 1, &written, NULL);
							drawmearmor();
						}else if(k==2){
							WriteConsole(tbuffer, " ", 1, &written, NULL);
							drawmelegs();
						}
						break;
					case 8:
						if(k==0){
							if(!pdamaged){
								switch(pinventory.aworn[1]){
								case 1:
									SetConsoleTextAttribute(tbuffer, 6);
									break;
								case 2:
									SetConsoleTextAttribute(tbuffer, 8);
									break;
								case 3:
									SetConsoleTextAttribute(tbuffer, 7);
									break;
								case 4:
									SetConsoleTextAttribute(tbuffer, 3);
									break;
								case 5:
									SetConsoleTextAttribute(tbuffer, 4);
									break;
								};
							}
							if(pinventory.aworn[1] != 0){
								WriteConsole(tbuffer, "[", 1, &written, NULL);
								WriteConsole(tbuffer, xd, 1, &written, NULL);
								WriteConsole(tbuffer, "]\\", 2, &written, NULL);
							}else{
								WriteConsole(tbuffer, " ", 1, &written, NULL);
								WriteConsole(tbuffer, xd, 1, &written, NULL);
								WriteConsole(tbuffer, " \\", 2, &written, NULL);
							}
							if(pdamaged){
								SetConsoleTextAttribute(tbuffer, 4);
							}else{
								SetConsoleTextAttribute(tbuffer, 7);
							}
						}else if(k==1){
							drawmearmor();
							WriteConsole(tbuffer, "/", 1, &written, NULL);
						}else if(k==2){
							drawmelegs();
							WriteConsole(tbuffer, " ", 1, &written, NULL);
						}
						break;
					case 9:
						if(k==0){
							if(!pdamaged){
								switch(pinventory.aworn[1]){
								case 1:
									SetConsoleTextAttribute(tbuffer, 6);
									break;
								case 2:
									SetConsoleTextAttribute(tbuffer, 8);
									break;
								case 3:
									SetConsoleTextAttribute(tbuffer, 7);
									break;
								case 4:
									SetConsoleTextAttribute(tbuffer, 3);
									break;
								case 5:
									SetConsoleTextAttribute(tbuffer, 4);
									break;
								};
							}
							if(pinventory.aworn[1] != 0){
								WriteConsole(tbuffer, "/[", 2, &written, NULL);
								WriteConsole(tbuffer, xd, 1, &written, NULL);
								WriteConsole(tbuffer, "]", 1, &written, NULL);
							}else{
								WriteConsole(tbuffer, "/ ", 2, &written, NULL);
								WriteConsole(tbuffer, xd, 1, &written, NULL);
								WriteConsole(tbuffer, " ", 1, &written, NULL);
							}
							if(pdamaged){
								SetConsoleTextAttribute(tbuffer, 4);
							}else{
								SetConsoleTextAttribute(tbuffer, 7);
							}
						}else if(k==1){
							WriteConsole(tbuffer, "\\", 1, &written, NULL);
							drawmearmor();
						}else if(k==2){
							WriteConsole(tbuffer, " ", 1, &written, NULL);
							drawmelegs();
						}
						break;
					}
					if(pdamaged){
						SetConsoleTextAttribute(tbuffer, 7);
					}
				}
			}
			//nie dzia³a 3, 7, 11, 15
			WriteConsole(tbuffer, "|", 1, &written, NULL);
			char bbb = 3;
			const char* lawl = &bbb;
			switch(((i+4)*4)+k){
			case 0:
				WriteConsole(tbuffer, "      \n", 7, &written, NULL);
				break;
			case 1:
				WriteConsole(tbuffer, "1.Sword\n", 8, &written, NULL);
				break;
			case 2:
				WriteConsole(tbuffer, "   |  \n", 7, &written, NULL);
				break;
			case 4:
				WriteConsole(tbuffer, "   |  \n", 7, &written, NULL);
				break;
			case 5:
				WriteConsole(tbuffer, "      \n", 7, &written, NULL);
				break;
			case 6:
				WriteConsole(tbuffer, "      \n", 7, &written, NULL);
				break;
			case 8:
				WriteConsole(tbuffer, "2.Bow \n", 7, &written, NULL);
				break;
			case 9:
				WriteConsole(tbuffer, "   \\  \n", 7, &written, NULL);
				break;
			case 10:
				WriteConsole(tbuffer, "   /  \n", 7, &written, NULL);
				break;
			case 12:
				WriteConsole(tbuffer, "      \n", 7, &written, NULL);
				break;
			case 13:
				WriteConsole(tbuffer, "      \n", 7, &written, NULL);
				break;
			case 14:
				WriteConsole(tbuffer, "3.Health\n", 9, &written, NULL);
				break;
			case 16:
				WriteConsole(tbuffer, "Potion\n", 7, &written, NULL);
				break;
			case 17:
				WriteConsole(tbuffer, "      \n", 7, &written, NULL);
				break;
			case 18:
				WriteConsole(tbuffer, "  <", 3, &written, NULL);
				WriteConsole(tbuffer, lawl, 1, &written, NULL);
				WriteConsole(tbuffer, "> \n", 3, &written, NULL);
				break;
			default:
				WriteConsole(tbuffer, "\n", 1, &written, NULL);
				break;
			};
			//std::cout << "\n";
		}
	}
	return tbuffer;
}

void draw(){
	if(isinventory){
		if(activebuffer == 1){
			buffer = pinventory.draw(php, arrows, arrowslimit);
			activebuffer = 0;
			SetConsoleActiveScreenBuffer(buffer);
		}else if(activebuffer == 0){
			buffer2 = pinventory.draw(php, arrows, arrowslimit);
			activebuffer = 1;
			SetConsoleActiveScreenBuffer(buffer2);
		}
	}else{
		if(activebuffer == 1){
			buffer = drawb();
			activebuffer = 0;
			SetConsoleActiveScreenBuffer(buffer);
		}else if(activebuffer == 0){
			buffer2 = drawb();
			activebuffer = 1;
			SetConsoleActiveScreenBuffer(buffer2);
		}
	}
}

void keyusing(){
	int ch = 0;
	while(keysrunning){
		ch = _getch();
		if(eventtoget == 0){
			if(ch==119 || ch==87){
				eventtoget = 1;
			}
			if(ch==97 || ch==65){
				eventtoget = 2;
			}
			if(ch==115 || ch==83){
				eventtoget = 3;
			}
			if(ch==100 || ch==68){
				eventtoget = 4;
			}
			if(ch==0 || ch==224){
				switch(_getch ()){
				case 72:
					eventtoget = 6;
					break;
				case 75:
					eventtoget = 7;
					break;
				case 80:
					eventtoget = 8;
					break;
				case 77:
					eventtoget = 9;
					break;
				}
			}
			if(ch==112 || ch==80){
				eventtoget = 10;
			}
			if(ch==27){
				eventtoget = 5;
			}
			if(ch==99 || ch==67){
				eventtoget = 11;
			}
			if(ch==77 || ch==109){
				eventtoget = 12;
			}
			if(ch==13){
				eventtoget = 13;
			}
			if(ch==73 || ch==105){
				eventtoget = 14;
			}
			if(ch==49){
				eventtoget = 15;
			}
			if(ch==50){
				eventtoget = 16;
			}
			if(ch==51){
				eventtoget = 17;
			}
			if(ch==52){
				eventtoget = 18;
			}
			if(ch==53){
				eventtoget = 19;
			}
		}
	}
	return;
}
std::thread keys (keyusing);
void initenemies(){
	for(int i = 0; i <= 63; i++){
		for(int j = 0; j <= 48; j++){
			if(mmmapa.main[j][i] == 2){
				enemies.push_back(enemy(rand() %4, i, j, monsterstrenght));
			}
		}
	}
}

void initloots(){
	int k = 0;
	for(int i = 0; i<48; i++){
		for(int j = 0; j<64; j++){
			if(mmmapa.main[i][j] == 3){
				lootid[k] = i*64+j;
				lootnr[k] = rand() %2;
				k++;
				if(k==128){
					k=127;
				}
			}
		}
	}
}

void reset(int i){
	mmmapa = getmap(i);
	while(enemies.size() > 0){
		enemies[0].~enemy();
		enemies.erase(enemies.begin());
	}
	while(projectiles.size() > 0){
		projectiles[0].~projectile();
		projectiles.erase(projectiles.begin());
	}
	px=mmmapa.spawnx;
	py=mmmapa.spawny;
	php = 100;
	arrows = arrowslimit/2;
	initenemies();
	initloots();
	pinventory = pinventoryempty;
}

void changemap(int i){
	mmmapa = getmap(i);
	while(enemies.size() > 0){
		enemies[0].~enemy();
		enemies.erase(enemies.begin());
	}
	while(projectiles.size() > 0){
		projectiles[0].~projectile();
		projectiles.erase(projectiles.begin());
	}
	px=mmmapa.spawnx;
	py=mmmapa.spawny;
	initenemies();
	initloots();
}

int game(){
	srand(time(NULL));
	time_t tstart = 0;
	time_t tend = 0;
	/*for(int i = 0; i < 256; i++){
		std::cout << i << "." << (char)i << "\n";
	}*/
	//getch();
	memset(lootid, 0, sizeof(lootid));
	memset(lootnr, 0, sizeof(lootnr));
	reset(cemap);
	draw();
	
	bool cont = true;
	bool temp = true;
	bool temp2 = true;
	bool temp3 = true;
	bool temp4 = true;
	bool temp5 = true;
	bool updenem = false;
	bool ismob = false;
	while(cont){
		if(php < lhp){
			pdamaged = true;
		}else if(pdamaged){
			if(!temp2){
				pdamaged = false;
				temp2 = true;
			}else{
				temp2 = false;
			}
		}
		lhp = php;
		tstart = clock();
		if((tstart - tend)/(CLOCKS_PER_SEC / 1000) <= 125){
			Sleep(125-(tstart - tend)/(CLOCKS_PER_SEC / 1000));
		}
		if(!isinventory){
			switch(eventtoget){
			case 1:
				ismob = false;
				for(int i = 0; i < enemies.size(); i++){
					if(enemies[i].x == px && enemies[i].y == py - 1){
						ismob=true;
					}
				}
				if(!ismob){
					if(mmmapa.main[py-1][px] == 1 || py - 1 <= -1){
						eventtoget=0;
					}else{
						if(temp){
							temp = false;
							draw();
						}else if(!temp){
							py--;
							if(mmmapa.main[py][px] == 3){
								for(int i = 0; i < 128; i++){
									if(lootid[i]==py*64+px){
										if(lootnr[i] == 0){
											pinventory.add(2,1,0,0);
											mmmapa.main[py][px] = 0;
										}else if(lootnr[i] == 1 && arrows<arrowslimit){
											arrows+=rand()%5 +5;
											if(arrows>arrowslimit){
												arrows=arrowslimit;
											}
											mmmapa.main[py][px] = 0;
										}
										break;
									}
								}
							}else if(mmmapa.main[py][px] == 4){
								int r = 0;
								r=rand()%20+5;
								while(true){
									if((r - 5)%4 != 3){
										break;
									}else{
										r=rand()%20+5;
									}
								}
								pinventory.add(r, 1, rand()%4, 0);
								mmmapa.main[py][px] = 0;
							}else if(mmmapa.main[py][px] == 5){
								if(mmmapa.redirectto == -1){
									if(MessageBox(NULL, "Congratulations, You've won the game!\nYes to exit to main menu, no to continue playing", "Congratulations!", MB_YESNO) == IDYES){
										return 0;
									}
								}else{
									changemap(mmmapa.redirectto);
								}
							}
							eventtoget=0;
							temp=true;
							draw();
						}
					}
				}else{
					eventtoget=0;
				}
				break;
			case 2:
				ismob = false;
				for(int i = 0; i < enemies.size(); i++){
					if(enemies[i].x == px - 1 && enemies[i].y == py){
						ismob=true;
					}
				}
				if(!ismob){
					if(mmmapa.main[py][px-1] == 1 || px - 1 <= -1){
						eventtoget=0;
					}else{
						if(temp){
							temp = false;
							draw();
						}else if(!temp){
							px--;
							if(mmmapa.main[py][px] == 3){
								for(int i = 0; i < 128; i++){
									if(lootid[i]==py*64+px){
										if(lootnr[i] == 0){
											pinventory.add(2,1,0,0);
											mmmapa.main[py][px] = 0;
										}else if(lootnr[i] == 1 && arrows<arrowslimit){
											arrows+=rand()%5 +5;
											if(arrows>arrowslimit){
												arrows=arrowslimit;
											}
											mmmapa.main[py][px] = 0;
										}
										break;
									}
								}
							}else if(mmmapa.main[py][px] == 4){
								int r = 0;
								r=rand()%20+5;
								while(true){
									if((r - 5)%4 != 3){
										break;
									}else{
										r=rand()%20+5;
									}
								}
								pinventory.add(r, 1, rand()%4, 0);
								mmmapa.main[py][px] = 0;
							}else if(mmmapa.main[py][px] == 5){
								if(mmmapa.redirectto == -1){
									if(MessageBox(NULL, "Congratulations, You've won the game!\nYes to exit to main menu, no to continue playing", "Congratulations!", MB_YESNO) == IDYES){
										return 0;
									}
								}else{
									changemap(mmmapa.redirectto);
								}
							}
							eventtoget=0;
							if(!bow){
								panimstate=1;
							}else{
								panimstate=9;
							}
							temp=true;
							draw();
						}
					}
				}else{
					eventtoget = 0;
				}
				break;
			case 3:
				ismob = false;
				for(int i = 0; i < enemies.size(); i++){
					if(enemies[i].x == px && enemies[i].y == py + 1){
						ismob=true;
					}
				}
				if(!ismob){
					if(mmmapa.main[py+1][px] == 1 || py + 1 >= 48){
						eventtoget=0;
					}else{
						if(temp){
							temp = false;
							draw();
						}else if(!temp){
							py++;
							if(mmmapa.main[py][px] == 3){
								for(int i = 0; i < 128; i++){
									if(lootid[i]==py*64+px){
										if(lootnr[i] == 0){
											pinventory.add(2,1,0,0);
											mmmapa.main[py][px] = 0;
										}else if(lootnr[i] == 1 && arrows<arrowslimit){
											arrows+=rand()%5 +5;
											if(arrows>arrowslimit){
												arrows=arrowslimit;
											}
											mmmapa.main[py][px] = 0;
										}
										break;
									}
								}
							}else if(mmmapa.main[py][px] == 4){
								int r = 0;
								r=rand()%20+5;
								while(true){
									if((r - 5)%4 != 3){
										break;
									}else{
										r=rand()%20+5;
									}
								}
								pinventory.add(r, 1, rand()%4, 0);
								mmmapa.main[py][px] = 0;
							}else if(mmmapa.main[py][px] == 5){
								if(mmmapa.redirectto == -1){
									if(MessageBox(NULL, "Congratulations, You've won the game!\nYes to exit to main menu, no to continue playing", "Congratulations!", MB_YESNO) == IDYES){
										return 0;
									}
								}else{
									changemap(mmmapa.redirectto);
								}
							}
							eventtoget=0;
							temp=true;
							draw();
						}
					}
				}else{
					eventtoget = 0;
				}
				break;
			case 4:
				ismob = false;
				for(int i = 0; i < enemies.size(); i++){
					if(enemies[i].x == px + 1 && enemies[i].y == py){
						ismob=true;
					}
				}
				if(!ismob){
					if(mmmapa.main[py][px+1] == 1 || px + 1 >= 64){
						eventtoget=0;
					}else{
						if(temp){
							temp = false;
							draw();
						}else if(!temp){
							px++;
							if(mmmapa.main[py][px] == 3){
								for(int i = 0; i < 128; i++){
									if(lootid[i]==py*64+px){
										if(lootnr[i] == 0){
											pinventory.add(2,1,0,0);
											mmmapa.main[py][px] = 0;
										}else if(lootnr[i] == 1 && arrows<arrowslimit){
											arrows+=rand()%5 +5;
											if(arrows>arrowslimit){
												arrows=arrowslimit;
											}
											mmmapa.main[py][px] = 0;
										}
										break;
									}
								}
							}else if(mmmapa.main[py][px] == 4){
								int r = 0;
								r=rand()%20+5;
								while(true){
									if((r - 5)%4 != 3){
										break;
									}else{
										r=rand()%20+5;
									}
								}
								pinventory.add(r, 1, rand()%4, 0);
								mmmapa.main[py][px] = 0;
							}else if(mmmapa.main[py][px] == 5){
								if(mmmapa.redirectto == -1){
									if(MessageBox(NULL, "Congratulations, You've won the game!\nYes to exit to main menu, no to continue playing", "Congratulations!", MB_YESNO) == IDYES){
										return 0;
									}
								}else{
									changemap(mmmapa.redirectto);
								}
							}
							eventtoget=0;
							if(!bow){
								panimstate=0;
							}else{
								panimstate=8;
							}
							temp=true;
							draw();
						}
					}
				}else{
					eventtoget=0;
				}
				break;
			case 5:
				cont = false;
				eventtoget=0;
				break;
			case 6:
				if(temp){
					temp = false;
					if(!bow){
						if(panimstate == 0){
							panimstate = 2;
						}else if(panimstate == 1){
							panimstate = 3;
						}
					}
					draw();
				}else if(!temp){
					eventtoget=0;
					if(!bow){
						if(panimstate == 2){
							panimstate = 0;
						}else if(panimstate == 3){
							panimstate = 1;
						}
						for(int k = 0; k < enemies.size(); k++){
							if(enemies[k].x == px && enemies[k].y == py - 1){
								enemies[k].hp -= pinventory.items[0].dealtdamage;
								if(enemies[k].hp <= 0){
									/*php += enemies[k].attack * 2;
									if(php > 20){
										php = 20;
									}*/
									arrows += enemies[k].arrowsin;
									enemies[k].~enemy();
									enemies.erase(enemies.begin() + k);
								}
							}
						}
					}
					temp = true;
					if(bow && arrows > 0){
						projectiles.push_back(projectile(px, py, 0, 0));
						arrows--;
					}
					draw();
				}
				break;
			case 7:
				if(temp){
					if(!bow){
						if(panimstate == 0){
							panimstate = 1;
						}else if(panimstate == 1){
							panimstate = 5;
							temp = false;
						}
					}else{
						if(panimstate == 8){
							panimstate = 9;
						}
						temp = false;
					}
					draw();
				}else if(!temp){
					eventtoget=0;
					if(!bow){
						panimstate = 1;
						for(int k = 0; k < enemies.size(); k++){
							if(enemies[k].x == px - 1 && enemies[k].y == py){
								enemies[k].hp -= pinventory.items[0].dealtdamage;
								if(enemies[k].hp <= 0){
									/*php += enemies[k].attack * 2;
									if(php > 20){
										php = 20;
									}*/
									arrows += enemies[k].arrowsin;
									enemies[k].~enemy();
									enemies.erase(enemies.begin() + k);
								}
							}
						}
					}
					temp = true;
					if(bow && arrows > 0){
						projectiles.push_back(projectile(px, py, 3, 0));
						arrows--;
					}
					draw();
				}
				break;
			case 8:
				if(temp){
					temp = false;
					if(!bow){
						if(panimstate == 0){
							panimstate = 6;
						}else if(panimstate == 1){
							panimstate = 7;
						}
					}
					draw();
				}else if(!temp){
					eventtoget=0;
					if(!bow){
						if(panimstate == 6){
							panimstate = 0;
						}else if(panimstate == 7){
							panimstate = 1;
						}
						for(int k = 0; k < enemies.size(); k++){
							if(enemies[k].x == px && enemies[k].y == py + 1){
								enemies[k].hp -= pinventory.items[0].dealtdamage;
								if(enemies[k].hp <= 0){
									/*php += enemies[k].attack * 2;
									if(php > 20){
										php = 20;
									}*/
									arrows += enemies[k].arrowsin;
									enemies[k].~enemy();
									enemies.erase(enemies.begin() + k);
								}
							}
						}
					}
					temp = true;
					if(bow && arrows > 0){
						projectiles.push_back(projectile(px, py, 2, 0));
						arrows--;
					}
					draw();
				}
				break;
			case 9:
				if(temp){
					if(!bow){
						if(panimstate == 1){
							panimstate = 0;
						}else if(panimstate == 0){
							panimstate = 4;
							temp = false;
						}
					}else{
						if(panimstate == 9){
							panimstate = 8;
						}
						temp = false;
					}
					draw();
				}else if(!temp){
					eventtoget=0;
					if(!bow){
						panimstate = 0;
						for(int k = 0; k < enemies.size(); k++){
							if(enemies[k].x == px + 1 && enemies[k].y == py){
								enemies[k].hp -= pinventory.items[0].dealtdamage;
								if(enemies[k].hp <= 0){
									/*php += enemies[k].attack * 2;
									if(php > 20){
										php = 20;
									}*/
									arrows += enemies[k].arrowsin;
									enemies[k].~enemy();
									enemies.erase(enemies.begin() + k);
								}
							}
						}
					}
					temp = true;
					if(bow && arrows > 0){
						projectiles.push_back(projectile(px, py, 1, 0));
						arrows--;
					}
					draw();
				}
				break;
			case 10:
				reset(cemap);
				eventtoget=0;
				draw();
				break;
			case 11:
				bow=!bow;
				if(panimstate==0){
					panimstate=8;
				}else if(panimstate==1){
					panimstate=9;
				}else if(panimstate==8){
					panimstate=0;
				}else if(panimstate==9){
					panimstate=1;
				}
				eventtoget=0;
				break;
			case 12:
				if(cemap == 0){
					cemap = 1;
				}else{
					cemap = 0;
				}
				reset(cemap);
				eventtoget=0;
				break;
			case 14:
				isinventory = true;
				draw();
				eventtoget = 0;
				break;
			case 15:
				pinventory.use(0, isinventory, bow, panimstate, php);
				eventtoget = 0;
				break;
			case 16:
				pinventory.use(1, isinventory, bow, panimstate, php);
				eventtoget = 0;
				break;
			case 17:
				pinventory.use(2, isinventory, bow, panimstate, php);
				eventtoget = 0;
				break;
			case 18:
				//pinventory.use(3, isinventory, bow, panimstate, php);
				eventtoget = 0;
				break;
			case 19:
				//pinventory.use(4, isinventory, bow, panimstate, php);
				eventtoget = 0;
				break;
			default:
				eventtoget = 0;
				draw();
				break;
			}
			//
			int fordeletion[32];
			bool iszero = false;
			memset(fordeletion, 0, sizeof(int)*32);
			for(int i = 0; i < projectiles.size(); i++){
				if(!projectiles[i].update(px,py,php,enemies,arrows, monsterstrenght)){
					if(i==0){
						iszero=true;
					}else{
						for(int j = 0; j<32; j++){
							if(fordeletion[j]==0){
								fordeletion[j]=i;
								break;
							}
						}
					}
				}
			}
			if(iszero){
				projectiles[0].~projectile();
				projectiles.erase(projectiles.begin());
			}
			for(int j = 0; j<32; j++){
				if(fordeletion[j]!=0){
					projectiles[j].~projectile();
					projectiles.erase(projectiles.begin()+fordeletion[j]-1);
				}
			}
			if(php <= 0){
				reset(cemap);
			}
			draw();
			//
			if(updenem){
				ptp a;
				for(int i = 0; i < enemies.size(); i++){
					a = enemies[i].update(px,py,php,enemies, pinventory.armor);//, projectiles);
					if(a.is){
						projectiles.push_back(projectile(a.x,a.y,a.d,a.t));
					}
				}
				if(php <= 0){
					reset(cemap);
				}
				draw();
				updenem = false;
			}else{
				updenem = true;
			}
		}else{
			switch(eventtoget){
			case 0:
				break;
			case 5:
				eventtoget = 0;
				isinventory = false;
				draw();
				break;
			case 6:
				if(pinventory.sel > -1){
					pinventory.sel--;
				}else{
					pinventory.sel = pinventory.items.size() - 1;
				}
				eventtoget = 0;
				draw();
				break;
			case 8:
				if(pinventory.sel < pinventory.items.size() - 1){
					pinventory.sel++;
				}else{
					pinventory.sel = -1;
				}
				eventtoget = 0;
				draw();
				break;
			case 13:
				if(pinventory.sel != -1){
					pinventory.use(pinventory.sel, isinventory, bow, panimstate, php);
				}else{
					isinventory = false;
				}
				draw();
				eventtoget = 0;
				break;
			case 14:
				isinventory = false;
				draw();
				eventtoget = 0;
				break;
			case 15:
				pinventory.usekey(0);
				eventtoget = 0;
				break;
			case 16:
				pinventory.usekey(1);
				eventtoget = 0;
				break;
			case 17:
				pinventory.usekey(2);
				eventtoget = 0;
				break;
			case 18:
				pinventory.usekey(3);
				eventtoget = 0;
				break;
			case 19:
				pinventory.usekey(4);
				eventtoget = 0;
				break;
			default:
				eventtoget = 0;
				draw();
				break;
			}
			//6, 8
		}
		tend = clock();
	}
	eventtoget = 0;
	return 0;
}

HANDLE makemenu(menu menu){
	tbuffer = CreateConsoleScreenBuffer( GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	COORD SIZE_COORD = { 85, 26 };
	SetConsoleScreenBufferSize(tbuffer, SIZE_COORD);
	WriteConsole(tbuffer, menu.title, menu.titlel, &written, NULL);
	WriteConsole(tbuffer, "\n\n", 2, &written, NULL);
	for(int i = 0; i<menu.poscount; i++){
		if(menuselectedposition==i){
			SetConsoleTextAttribute(tbuffer, 2);
		}else if(menuselectedposition>=menu.poscount){
			menuselectedposition = 0;
		}else if(menuselectedposition<0){
			menuselectedposition = menu.poscount - 1;
		}
		WriteConsole(tbuffer,menu.names[i], menu.namesl[i], &written, NULL);
		WriteConsole(tbuffer, "\n", 1, &written, NULL);
		SetConsoleTextAttribute(tbuffer, 7);
	}
	return tbuffer;
}

void diffmenu(){
	std::string title = "Choose Difficulty. Current: ";
	menu tempmenu;
	tempmenu.title = title.c_str();
	tempmenu.titlel = title.length();
	tempmenu.names[0] = "Walk in the park (Monster str. x0.1)";
	tempmenu.namesl[0] = 36;
	tempmenu.names[1] = "Very Easy (Monster str. x0.5)";
	tempmenu.namesl[1] = 29;
	tempmenu.names[2] = "Easy (Monster str. x0.75)";
	tempmenu.namesl[2] = 25;
	tempmenu.names[3] = "Medium (Monster str. x1)";
	tempmenu.namesl[3] = 24;
	tempmenu.names[4] = "Hard (Monster str. x1.25)";
	tempmenu.namesl[4] = 25;
	tempmenu.names[5] = "Insane (Monster str. x1.5)";
	tempmenu.namesl[5] = 26;
	tempmenu.names[6] = "Suicide (Monster str. x2)";
	tempmenu.namesl[6] = 25;
	tempmenu.names[7] = "I'm crazy pro player, come at me (Monster str. x5)";
	tempmenu.namesl[7] = 50;
	tempmenu.names[8] = "\nBack";
	tempmenu.namesl[8] = 5;
	tempmenu.poscount = 9;
	while(1){
		if(eventtoget==6){
			menuselectedposition--;
			eventtoget=0;
		}else if(eventtoget==8){
			menuselectedposition++;
			eventtoget=0;
		}else if(eventtoget==13){
			switch(menuselectedposition){
			case 0:
				monsterstrenght = 0.1f;
				break;
			case 1:
				monsterstrenght = 0.5f;
				break;
			case 2:
				monsterstrenght = 0.75f;
				break;
			case 3:
				monsterstrenght = 1.0f;
				break;
			case 4:
				monsterstrenght = 1.25f;
				break;
			case 5:
				monsterstrenght = 1.5f;
				break;
			case 6:
				monsterstrenght = 2.0f;
				break;
			case 7:
				monsterstrenght = 5.0f;
				break;
			case 8:
				menuselectedposition=0;
				eventtoget=0;
				return;
				break;
			}
			eventtoget=0;
		}else{
			eventtoget=0;
		}
		std::ostringstream newtitle;
		newtitle << monsterstrenght;
		title = "Choose Difficulty. Current: ";
		title += newtitle.str();
		tempmenu.title = title.c_str();
		tempmenu.titlel = title.length();
		if(activebuffer == 1){
			buffer = makemenu(tempmenu);
			activebuffer = 0;
			SetConsoleActiveScreenBuffer(buffer);
		}else if(activebuffer == 0){
			buffer2 = makemenu(tempmenu);
			activebuffer = 1;
			SetConsoleActiveScreenBuffer(buffer2);
		}
	}
}

void mainmenu(){
	menu tempmenu;
	tempmenu.title = "Main Menu";
	tempmenu.titlel = 9;
	tempmenu.names[0] = "New Game";
	tempmenu.namesl[0] = 8;
	tempmenu.names[1] = "Difficulty";
	tempmenu.namesl[1] = 10;
	tempmenu.names[2] = "Exit";
	tempmenu.namesl[2] = 4;
	tempmenu.poscount = 3;
	while(1){
		if(eventtoget==6){
			menuselectedposition--;
			eventtoget=0;
		}else if(eventtoget==8){
			menuselectedposition++;
			eventtoget=0;
		}else if(eventtoget==13){
			eventtoget=0;
			if(menuselectedposition == 0){
				menuselectedposition=0;
				game();
			}else if(menuselectedposition == 1){
				menuselectedposition=0;
				diffmenu();
			}else if(menuselectedposition == 2){
				menuselectedposition=0;
				return;
			}
		}else{
			eventtoget=0;
		}
		if(activebuffer == 1){
			buffer = makemenu(tempmenu);
			activebuffer = 0;
			SetConsoleActiveScreenBuffer(buffer);
		}else if(activebuffer == 0){
			buffer2 = makemenu(tempmenu);
			activebuffer = 1;
			SetConsoleActiveScreenBuffer(buffer2);
		}
	}
}

int main(){
	mainmenu();
	keysrunning = false;
	keys.detach();
	return 0;
}