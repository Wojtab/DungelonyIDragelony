#include "item.h"

char *Namesarray0[256];
char *ADamagenames0[4];
int armorarray[20] = {38,7,18,11,53,9,24,17,80,14,39,25,136,21,66,45,216,36,103,69};
void initiatearraysofnames(){
	Namesarray0[0] = "Sword. DMG: ";
	Namesarray0[1] = "Bow. DMG: ";
	Namesarray0[2] = "HP Potion. Amount: ";
	Namesarray0[3] = "potion";
	Namesarray0[4] = "potion";
	Namesarray0[5] = "Leather Armor. Defense: ";
	Namesarray0[6] = "Leather Helmet. Defense: ";
	Namesarray0[7] = "Leather Greaves. Defense: ";
	Namesarray0[8] = "boots";
	Namesarray0[9] = "Chain Armor. Defense: ";
	Namesarray0[10] = "Chain Helmet. Defense: ";
	Namesarray0[11] = "Chain Greaves. Defense: ";
	Namesarray0[12] = "boots";
	Namesarray0[13] = "Iron Armor. Defense: ";
	Namesarray0[14] = "Iron Helmet. Defense: ";
	Namesarray0[15] = "Iron Greaves. Defense: ";
	Namesarray0[16] = "boots";
	Namesarray0[17] = "Holy Armor. Defense: ";
	Namesarray0[18] = "Holy Helmet. Defense: ";
	Namesarray0[19] = "Holy Greaves. Defense: ";
	Namesarray0[20] = "boots";
	Namesarray0[21] = "Demonic Armor. Defense: ";
	Namesarray0[22] = "Demonic Helmet. Defense: ";
	Namesarray0[23] = "Demonic Greaves. Defense: ";
	Namesarray0[24] = "boots";
	//////////////////////////////////////////////
	ADamagenames0[0] = "Ragged ";
	ADamagenames0[1] = "Worn ";
	ADamagenames0[2] = "";
	ADamagenames0[3] = "Fine ";
}

item::item(int idi, int amounti, int damagei, int ddamage)
{
	if(idi >= 0 && idi <= 24){
		id = idi;
	}else{
		id = 0;
	}
	amount = amounti;
	damage = damagei;
	dealtdamage = ddamage;
	switch(damagei){
	case 0:
		armor = (int)((float)armorarray[id-5]*0.65);
		break;
	case 1:
		armor = (int)((float)armorarray[id-5]*0.85);
		break;
	case 2:
		armor = armorarray[id-5];
		break;
	case 3:
		armor = (int)((float)armorarray[id-5]*1.2);
		break;
	}
	initiatearraysofnames();
}

void item::drawmything(HANDLE buffer, DWORD &written, bool worn, bool checked){
	//DWORD tw = written;
	if(worn){
		SetConsoleTextAttribute(buffer, 6);
	}
	if(checked){
		SetConsoleTextAttribute(buffer, 2);
	}
	if(id >= 5 && id <= 24){
		WriteConsole(buffer, ADamagenames0[damage], strlen(ADamagenames0[damage]), &written, NULL);
	}
	int lol = strlen(Namesarray0[id]);
	WriteConsole(buffer, Namesarray0[id], strlen(Namesarray0[id]), &written, NULL);
	if(id == 0 || id == 1){
		char aaa = 48 + ((dealtdamage-(dealtdamage%10))/10);
		char *aaap = &aaa;
		WriteConsole(buffer, aaap, 1, &written, NULL);
		char bbb = 48 + (dealtdamage%10);
		char *bbbp = &bbb;
		WriteConsole(buffer, bbbp, 1, &written, NULL);
	}else if(id == 2 || id == 3 || id == 4){
		char aaa = 48 + ((amount-(amount%10))/10);
		char *aaap = &aaa;
		WriteConsole(buffer, aaap, 1, &written, NULL);
		char bbb = 48 + (amount%10);
		char *bbbp = &bbb;
		WriteConsole(buffer, bbbp, 1, &written, NULL);
	}else if(id >= 5 && id <= 24){
		char zerozerozero = 48+((armor-(armor%100))/100);
		char *zerozerozerop = &zerozerozero;
		WriteConsole(buffer, zerozerozerop, 1, &written, NULL);
		char aaa = 48 + (((armor%100)-(armor%10))/10);
		char *aaap = &aaa;
		WriteConsole(buffer, aaap, 1, &written, NULL);
		char bbb = 48 + (armor%10);
		char *bbbp = &bbb;
		WriteConsole(buffer, bbbp, 1, &written, NULL);
	}
	SetConsoleTextAttribute(buffer, 7);
}

void item::use(bool &bow, int &panimstate, int &php, int &adest, int &aworn){
	if(id==0){
		bow = false;
		if(panimstate == 8){
			panimstate = 0;
		}else if(panimstate == 9){
			panimstate = 1;
		}
	}else if(id==1){
		bow = true;
		if(panimstate == 0){
			panimstate = 8;
		}else if(panimstate == 1){
			panimstate = 9;
		}
	}else if(id==2){
		if(php != 100 && amount > 0){
			php += 50;
			if(php > 100){
				php = 100;
			}
			amount--;
		}
	}else if(id >= 5 && id < 25){
		if((id - 5)%4 == 0){
			if(aworn == (id-5)/4+1){
				aworn = 0;
			}else{
				aworn = (id-5)/4+1;
			}
		}else if((id - 5)%4 == 1){
			if(aworn == (id-6)/4+1){
				aworn = 0;
			}else{
				aworn = (id-6)/4+1;
			}
		}else if((id - 5)%4 == 2){
			if(aworn == (id-7)/4+1){
				aworn = 0;
			}else{
				aworn = (id-7)/4+1;
			}
		}else if((id - 5)%4 == 3){
			if(aworn == (id-8)/4+1){
				aworn = 0;
			}else{
				aworn = (id-8)/4+1;
			}
		}
		adest = damage;
	}
}

item::~item(void)
{
}
