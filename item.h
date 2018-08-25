#pragma once
#include <Windows.h>
class item
{
public:
	item(int idi, int amounti, int damagei, int ddamage);
	void drawmything(HANDLE buffer, DWORD &written, bool worn, bool checked);
	void use(bool &bow, int &panimstate, int &php, int &adest, int &aworn);
	~item(void);
	int id;
	int amount;
	int damage;
	int dealtdamage;
	int armor;
};