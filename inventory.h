#pragma once
#include <Windows.h>
#include <vector>
#include "item.h"
class inventory
{
public:
	inventory(void);
	HANDLE draw(int php, int arrows, int arrowslimit);
	std::vector <item> items;
	void add(int id, int count, int damaged, int damage);
	void use(int id, bool &isinventory, bool &bow, int &panimstate, int &php);
	void usekey(int id);
	~inventory(void);
	bool has[25];//miecz, bow, hp pota, pota, pota, leather c, h, l, b, chain c, h, l, b, iron c, h, l, b, holy c, h, l, b, demonic c, h, l, b
	int adestroy[20];
	int aworn[4];
	int iworn[4];
	int armor;
	int sel;
	/*int sworddmg;
	int bowdmg;
	int hppotacount;*/
	int count;
};