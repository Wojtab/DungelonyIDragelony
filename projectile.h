#pragma once
#include <vector>
#include "enemy.h"
class projectile
{
public:
	int x;
	int y;
	int type;	
	int dmg;									
	int range;									// 0
	int direction;								//3 1
	projectile(int x, int y, int dir, int type);// 2
	bool update(int px, int py, int &php, std::vector <enemy> &enemies, int &arrows, float damagemultiplier);
	void draw(int k, HANDLE buffer, DWORD &written);
	~projectile(void);
private:
	int flied;
};