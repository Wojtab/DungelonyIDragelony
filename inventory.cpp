#include "inventory.h"
//1, 2, 3, 4, 5
int kbind[5] ={0,1,2,3,4};

inventory::inventory(void)
{
	this->add(0,1,0,25);
	this->add(1,1,0,20);
	this->add(2,0,0,0);
	aworn[0] = 0;
	aworn[1] = 0;
	aworn[2] = 0;
	aworn[3] = 0;
	iworn[0] = 0;
	iworn[1] = 0;
	iworn[2] = 0;
	iworn[3] = 0;
	armor = 0;
}

void inventory::add(int id, int number, int damaged, int damage){
	/*if(id < 5){
		switch(id){
		case 0:
			break;
		case 1:
			if(!has[1]){
				has[1] = true;
			}
			break;
		case 2:
			if(!has[2]){
				has[2] = true;
			}
			hppotacount++;
			break;
		case 3:
			break;
		case 4:
			break;
		};
	}else if(!has[id]){
		has[id] = true;
		if(adestroy[id - 5] < number){
			adestroy[id - 5] = number;
		}
	}
	count = 0;
	for(int i = 0; i < sizeof(has)/sizeof(byte); i++){
		if(has[i]){
			count++;
		}
	}*/
	bool broken = false;
	for(int i = 0; i < items.size(); i++){
		if(items[i].id == id && items[i].damage == damaged && items[i].dealtdamage == damage){
			items[i].amount += number;
			broken = true;
			break;
		}
	}
	if(!broken){
		items.push_back(item(id, number, damaged, damage));
	}
}

int calculatearmor(int i, int j){
	int k = 0;
	switch(j){
	case 0:
		k=(float)i*0.65;
		break;
	case 1:
		return (i*0.85);
		break;
	case 2:
		return i;
		break;
	case 3:
		return (i*1.2);
		break;
	}
	return k;
}

void inventory::use(int id, bool &isinventory, bool &bow, int &panimstate, int &php){
	if(isinventory){
		if(items[sel].id >= 5 && items[sel].id < 25){
			int toadest = adestroy[items[sel].id-5];
			int toaworn = aworn[(items[sel].id-5)%4];
			items[sel].use(bow, panimstate, php, toadest, toaworn);
			if(iworn[(items[sel].id-5)%4] == sel+1){
				iworn[(items[sel].id-5)%4] = 0;
			}else{
				iworn[(items[sel].id-5)%4] = sel+1;
			}
			adestroy[items[sel].id-5] = toadest;
			aworn[(items[sel].id-5)%4] = toaworn;
		}else{
			int nobodycaresaboutme = 0;
			items[sel].use(bow, panimstate, php, nobodycaresaboutme, nobodycaresaboutme);
		}
	}else{
			int nobodycaresaboutme = 0;
			items[id].use(bow, panimstate, php, nobodycaresaboutme, nobodycaresaboutme);
	}
	armor = 0;
	switch(aworn[0]){
	case 0:
		break;
	case 1:
		armor += calculatearmor(38, adestroy[0]);
		break;
	case 2:
		armor += calculatearmor(53, adestroy[4]);
		break;
	case 3:
		armor += calculatearmor(80, adestroy[8]);
		break;
	case 4:
		armor += calculatearmor(136, adestroy[12]);
		break;
	case 5:
		armor += calculatearmor(216, adestroy[16]);
		break;
	};
	switch(aworn[1]){
	case 0:
		break;
	case 1:
		armor += calculatearmor(7, adestroy[1]);
		break;
	case 2:
		armor += calculatearmor(9, adestroy[5]);
		break;
	case 3:
		armor += calculatearmor(14, adestroy[9]);
		break;
	case 4:
		armor += calculatearmor(21, adestroy[13]);
		break;
	case 5:
		armor += calculatearmor(36, adestroy[17]);
		break;
	};
	switch(aworn[2]){
	case 0:
		break;
	case 1:
		armor += calculatearmor(18, adestroy[2]);
		break;
	case 2:
		armor += calculatearmor(24, adestroy[6]);
		break;
	case 3:
		armor += calculatearmor(39, adestroy[10]);
		break;
	case 4:
		armor += calculatearmor(66, adestroy[14]);
		break;
	case 5:
		armor += calculatearmor(103, adestroy[18]);
		break;
	};
	switch(aworn[3]){
	case 0:
		break;
	case 1:
		armor += calculatearmor(11, adestroy[3]);
		break;
	case 2:
		armor += calculatearmor(17, adestroy[7]);
		break;
	case 3:
		armor += calculatearmor(25, adestroy[11]);
		break;
	case 4:
		armor += calculatearmor(45, adestroy[15]);
		break;
	case 5:
		armor += calculatearmor(69, adestroy[19]);
		break;
	};
}

void inventory::usekey(int id){

}

HANDLE inventory::draw(int php, int arrows, int arrowslimit){
	char ramka[6] = {218,196,191,179,217,192};
	char *ramkap[6] = {&ramka[0], &ramka[1], &ramka[2], &ramka[3], &ramka[4], &ramka[5]};
	HANDLE tbuffer = CreateConsoleScreenBuffer( GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	COORD SIZE_COORD = { 85, 26 };
	SetConsoleScreenBufferSize(tbuffer, SIZE_COORD);
	DWORD written;
	char aaa = 219;
	const char* lol = &aaa;
	int rsel = 0;
	for(int i = 0; i < 25; i++){
		if(has[i]){
			if(i == sel){
				break;
			}
		}
		rsel++;
	}
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

	if(php == 100){
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
	WriteConsole(tbuffer, "/100 ", 5, &written, NULL);
	//armor
	char armorhunderts = 48 + ((armor - (armor%100)) / 100);
	char* armorhundertsp = &armorhunderts;
	WriteConsole(tbuffer, armorhundertsp, 1, &written, NULL);
	char armortens = 48 + (((armor%100) - (armor%10)) / 10);
	char* armortensp = &armortens;
	WriteConsole(tbuffer, armortensp, 1, &written, NULL);
	char armorones = 48 + (armor%10);
	char* armoronesp = &armorones;
	WriteConsole(tbuffer, armoronesp, 1, &written, NULL);
	//arrows
	WriteConsole(tbuffer, "         Arrows:", 16, &written, NULL);
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
	WriteConsole(tbuffer, "\n", 1, &written, NULL);
	for(int i = 0; i < 80; i++){
		WriteConsole(tbuffer, lol, 1, &written, NULL);
	}
	WriteConsole(tbuffer, "\n", 1, &written, NULL);
	WriteConsole(tbuffer, "Twoje rzeczy:\n", 14, &written, NULL);
	
	int loldatint = 0;
	if(items.size() >= 20 && sel >= 20){
		loldatint = sel-18;
	}
	if(items.size()!=0){
		for(int i = 0 + loldatint; i < items.size(); i++){
			if(i==sel){
				if(iworn[0] == i + 1 || iworn[1] == i + 1 || iworn[2] == i + 1 || iworn[3] == i + 1){
					items[i].drawmything(tbuffer, written, true, true);
				}else{
					items[i].drawmything(tbuffer, written, false, true);
				}
			}else{
				if(iworn[0] == i + 1 || iworn[1] == i + 1 || iworn[2] == i + 1 || iworn[3] == i + 1){
					items[i].drawmything(tbuffer, written, true, false);
				}else{
					items[i].drawmything(tbuffer, written, false, false);
				}
			}
			WriteConsole(tbuffer, "\n", 1, &written, NULL);
			if(i == loldatint+20){
				break;
			}
		}
	}
	int a = 0;
	if(has[2]){
		a = 1;
	}
	/*if(sel!=-1&&sel<2+a){
		for(int i = 0; i < 15 - count; i++){
			WriteConsole(tbuffer, "\n", 1, &written, NULL);
		}
	}else{*/
	if(items.size() < 20){
		for(int i = 0; i < 20 - items.size(); i++){
			WriteConsole(tbuffer, "\n", 1, &written, NULL);
		}
	}else if(sel >= 20 && sel <= 40){
		for(int i = 0; i < sel - 21; i++){
			WriteConsole(tbuffer, "\n", 1, &written, NULL);
		}
	}
	//}
	if(sel == -1){
		SetConsoleTextAttribute(tbuffer, 2);
	}
	WriteConsole(tbuffer, "Wroc do gry.", 12, &written, NULL);
	if(sel == -1){
		SetConsoleTextAttribute(tbuffer, 7);
	}
	return tbuffer;
}

inventory::~inventory(void)
{
}