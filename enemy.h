#pragma once
#include <vector>
#include <Windows.h>
struct ptp{
	bool is;
	int x;
	int y;
	int d;
	int t;
};
typedef ptp projtoput;
class enemy
{
public:
	int type;
	int hp;
	int x;
	int y;
	int attack;
	int arrowsin;
	int random;
	int randminus;
	int mana;
	int maxmana;
	bool moveulazymob;
	bool damaged;
	bool mt;
	bool manauser;
	enemy(int, int, int, float);
	projtoput update(int px, int py, int &php, std::vector <enemy> &enemies, int armor);//, std::vector <projectile> &projectiles);
	void draw(int k, HANDLE buffer, DWORD &written);
	~enemy(void);
private:
	int lhp;
};