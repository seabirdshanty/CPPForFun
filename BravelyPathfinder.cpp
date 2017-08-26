/* ===================================================================================
	BravelyPathfinder.cpp
	Date	: 2017/08/25
	Author	: seabirdshanty
	Version	: 0.3.12a
	Desc	: A Pathfinder character generation and brave/default fight simulator
		: based off of Bravely Default.
		: Notes are in the code itself!
==================================================================================== */

// #include <fstream>
#include <conio.h> // Just for WaitKey() routine (WHITENITE1 AT C++, YOU ARE A GODSEND)
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <array>
#include <stdlib.h>
#include <windows.h>
#include <algorithm>
using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // For use of SetConsoleTextAttribute()

// DECLARE EVEYRTHING BEFORE MAIN SO EVEYRTHING CAN BE CALLED EASILY!
// Also dont have to load up everything before main now :3
void StoryMode(), CustomWaitKey(string text);
int rollMe(int diceSides), anystat(), menu(), doBattle(int desu1, int desu2);
void logos(), generateCharacter(int goober), recallInfo(int showUp), genMenu(), genMenu2(), fightMenu(),
WaitKey(), healthBar(int healthy, int health), playerFight(string playa1, string playa2, int playerID, int yATK, int yBR, int eHP, int eCMD, bool hyped);

void colorMe(string text, int color) {
	/* COLOR INDEX
	system("color %");

    0 = Black       8 = Gray
    1 = Blue        9 = Light Blue
    2 = Green       10 = Light Green
    3 = Aqua        11 = Light Aqua
    4 = Red         12 = Light Red
    5 = Purple      13 = Light Purple
    6 = Yellow      14 = Light Yellow
    7 = White       15 = Bright White
	
	*/
	if (color > 15 || color < 1)
		color = 7;
	
	SetConsoleTextAttribute(console, color); // sets to color
	cout << text;
	SetConsoleTextAttribute(console, 7); // resets
}


int main() {
	char c = ' ';
	
	srand(time(NULL));

	logos();

	cout << "Welcome to the Bravely Pathfinder Generator!\n"
		<< "This generator used the 4d6+2 stat creation, \n"
		<< "as well as slightly homebrewed classes. These \n"
		<< "are all based off the game \"Bravely Default\"\n"
		<< "which I love with all of my heart and soul.\n\n"
		<< "I hope this program helps you on any creation\n"
		<< "endevors you persue...\n\n"
		<< "\tHappy Pathfinding!\n\t\t";
	colorMe("- seabirdshanty, 2017\n", 3);

	cout << "\nView release notes? (y/n): ";
	cin >> c;
	c = tolower(c);

	if (c == 'y') {

		system("cls");

		logos();

		colorMe("Changes in 0.3.12a\n", 3);
		cout << "+ Added Fort, Will, Save, CMD, and AC generation\n"
			<< "+ Changed the battle algarythm a bit\n"
			<< "+ Added HP Bars in battle\n"
			<< "+ Colors!\n"
			<< "+ Added WaitKey() so system(\"pause\") isnt used anymore\n"
			<< "- Removed some bugs\n" << endl;

		colorMe("Changes in 0.2.5a\n", 3);
		cout << "+ Made it so Generation and Display became 2 different entities\n"
			<< "+ Skill generation now based on each job\n"
			<< "+ New Menus\n"
			<< "+ FAster loading time!\n"
			<< "+ Added ability to save 2 sets of character Info\n"
			<< "+ Implemented Bravely's Brave/Default system... somewhat\n"
			<< "+ Stopped some Gobals from being global\n"
			<< "+ Implemented Menus and Flavor Text\n" << endl;

		colorMe("Changes in 0.2.2a\n", 3);
		cout << "+ Made Skill generation possible (random)\n"
			<< "+ Application Icon! What a nice flower.\n"
			<< "+ Merged some functions into a generateCharacter() funciton\n"
			<< "+ HP Generation and faux levels added\n"
			<< "+ Made rollDice able to roll any side of dice\n" << endl;

		colorMe("Changes in 0.2.0a\n", 3);
		cout << "+ BravelyDnD is now Bravely Patfinder\n"
			<< "+ Added Race generation + Racial Stat changes\n" << endl;

		WaitKey();
	}

	int shogun;

	do {
		shogun = menu();

		if (!cin || cin.fail()) {
		cin.clear(); cin.get();
		shogun = -1;

		}

		if (shogun > 5 || shogun < 0 ) {
			colorMe("ERR: Invalid input.\n", 14);
			Sleep(300);
		}
		else if (shogun == 1)
			genMenu();
		else if (shogun == 2)
			genMenu2();
		else if (shogun == 3)
			fightMenu();
		else if (shogun == 4)
			StoryMode();
		else if (shogun == 5)
			break;

	} while (shogun != 5);

	return 0;

} // main

///////////////////////////////////// GLOBALS
///////////////////////////////////////////////////////
// someone is surely rolling in their grave.....

// alignment1, aligment2, Job, Race, HP, str, con, int, dex, wis, cha
array<int, 13> charaSaveA;
array<int, 13> charaSaveB;
array<double, 6> statMe;

array<int, 4> offense1{ 0, 0, 0, 1 }; // HP, ATTACK+STR, CMD, BRAVE
array<int, 4> offense2{ 0, 0, 0, 1 };

array<string, 8> party{"Agnes Oblige", "Tiz Arrior", "Edea Lee", "Ringabel", "Alternis Dim", "Yew Genolgia", "Magnolia Arche", "Janne Wolfe"};
array<string, 7> jobCl{ "Freelancer", "White Mage", "Monk", "Catmaster", "Performer", "Black Mage", "Dark Knight" };
int commonRace[8][8]{ // Race Stat changes, 
	 // str, con, int, dex, wis, cha, size, speed (min weight )
	{ 0, 0, 0, 0, 0, 0, 1, 30 }, // Human, ANY
	{ 0, -2, 2, 2, 0, 0 , 1, 30 }, // Elf
	{ 0, 0, 0, 0, 0, 0, 1, 30 }, // Orc, ANY
	{ -2, 0 , 0 , 2, 0, 2, 1, 20 }, // Halfing
	{ 0, 2, 0, 0, 2, -2, 1, 20 }, // Dwarf
	{ -2, 2, 0, 0, 0, 2, 0, 30 }, // Gnome
	{ 0, 0, 0, 0, 0, 0, 1, 30 }, // Half-Orc, ANY
	{ 0, 0, 0, 0, 0, 0, 1, 30 } // Half-Elf, ANY
};
int jobSkill[7][10]{
	{ 2, 5, 12, 14, 18, 24, 26, 28, 32, -1 }, //Freelancer
	{ 5, 8, 11, 13, 19, 22, 23, 24, 30, 34 }, //White Mage (HEALER)
	{ 0, 2, 3, 8, 12, 16, 22, 24, 28, 31 }, // Monk
	{ 0, 2, 3, 7, 10, 16, 24, 27, 28, 32 }, // Catmaster
	{ 2, 5, 7, 17, 20, 23, 25, 26, 28, 34 }, // Performer
	{ 1, 4, 6, 9, 13, 21, 24, 29, 30, 34 }, // Black Mage
	{ 2, 5, 7, 11, 12, 17, 20, 24, 28, 32 } // Dark Knight
};
array<int, 7> hitDice{ 10, 6, 12, 10, 8, 6, 12 };

///////////////////////////////////// MENUS
///////////////////////////////////////////////////////

void WaitKey()
{
	colorMe("\n\t Continue ==>", 6);
	while (_kbhit()) _getch(); // Empty the input buffer
	_getch(); // Wait for a key
	while (_kbhit()) _getch(); // Empty the input buffer (some keys sends two messages)
	system("cls");
}

void logos() {


	SetConsoleTextAttribute(console, 5);
	cout << "+----------------------------------------------+" << endl
		<< "|                                              |" << endl
		<< "|             BRAVELY PATHFINDER GEN           |" << endl
		<< "|                                              |" << endl
		<< "+----------------------------------------------+" << endl
		<< endl;
	SetConsoleTextAttribute(console, 7);
}

int menu() {

	system("cls");

	int select;

	logos();

	cout << "Bravely Pathfinder build 0.3.12a\n"
		<< "coded with love by seabirdshanty\n\n"
		<< "\t [1] Generate Character\n"
		<< "\t [2] Generate Entire Party (4)\n"
		<< "\t [3] Have 2 Characters Battle\n"
		<< "\t [4] Story Mode (DEMO)\n"
		<< "\t [5] Exit\n\n"
		<< "Please take a number: ";

	cin >> select;

	return select;

}

void genMenu() {
	system("cls");
	int select;
	char select2;

	logos();
	cout << "C H O O S E Y O U R C H A R A C T E R....\n"
		<< "A tome lies before you, holding knowlege of 4\ngreat warriors of light and their allies.\n\n";

	cout << endl
		<< "\t[1] Agnes Oblige\n"
		<< "\t[2] Tiz Arrior\n"
		<< "\t[3] Edea Lee\n"
		<< "\t[4] Ringabel\n"
		<< "\t[5] Alternis Dim\n"
		<< "\t[6] Yew Genolgia\n"
		<< "\t[7] Magnolia Arche\n"
		<< "\t[8] Janne Wolfe\n\n";

	cout << "As you open the tome, a familliar voice calls\nout:"
		<< "\"Who do you choose, dear tactician?\"\n"
		<< "Please, enter their number now: ";
	cin >> select;

	cin.clear(); cin.get();

	if (select > 8 || select < 0) {
		colorMe("ERR: Invalid input.\n", 14);
		Sleep(300);
		genMenu();
	}

	system("cls");

	select -= 1;
	cout << "Character: " << party[select] << endl;
	generateCharacter(1);
	recallInfo(1);

	cout << endl
		<< "Generate another character? (y/n)";
	cin >> select2;

	if (select2 == 'Y' || select2 == 'y')
		genMenu();

}

void genMenu2() {

	system("cls");

	for (int i = 0; i < 4; i++) {
		cout << "Character: " << party[i] << endl;
		generateCharacter(1);
		recallInfo(1);

		cout << endl << "+--+---+---+---+---+---+---+---+--+" << endl << endl;
	}

	WaitKey();

}

void fightMenu() {

	system("cls");

	logos();
	cout << "C H O O S E Y O U R F I G H T E R....\n"
		<< "Two brave warriors step into the arena,\nbut only one will return victorious.\n\n";

	int fightA = 0, fightB = 0, select;
	char select2;

	cout << endl
		<< "\t[1] Agnes Oblige\n"
		<< "\t[2] Tiz Arrior\n"
		<< "\t[3] Edea Lee\n"
		<< "\t[4] Ringabel\n"
		<< "\t[5] Alternis Dim\n"
		<< "\t[6] Yew Genolgia\n"
		<< "\t[7] Magnolia Arche\n"
		<< "\t[8] Janne Wolfe\n\n";

	cout << "Please select your first fighter: ";
	cin >> select;

	if (cin.fail()) {
		cin.clear(); cin.get();
		colorMe("ERR: Invalid input.\n", 14);
		Sleep(300);
		fightMenu();
	}
	else
		fightA = select;

	cout << "Please select your second fighter: ";
	cin >> select;
	cin.clear();

	if (cin.fail()) {
		cin.clear(); cin.get();
		colorMe("ERR: Invalid input.\n", 14);
		Sleep(300);
		fightMenu();
	}
	else
		fightB = select;

	// cout << "DEBUG: fightA is " << fightA << endl << "DEBUG: fightB is " << fightB << endl;

	fightA--;
	fightB--;

	// cout << "DEBUG: fightA-- is " << fightA << endl << "DEBUG: fightB-- is " << fightB << endl;

	if (fightA > 7 || fightA < 0 ) {
		cout << "ERR: Not a fighter! Matching a random character..\n";
		fightA = rand() % 7 + 0;
	}

	if (fightB > 7 || fightB < 0 ) {
		cout << "ERR: Not a fighter! Matching a random character..\n";
		fightB = rand() % 7 + 0;
	}

	while (fightA == fightB) {
		cout << "ERR: One cannot fight one's self! Matching Random opponent..\n";
		fightB = rand() % 7 + 0;
	};

	// Silly easter Egg
	if( ( fightA == 3 && fightB == 4 ) || ( fightA == 4 && fightB == 3 ) ) {
		cout << "ERR: One cannot fight one's se-- Or. Well. Hmm.\n";
	}



	cout << "Are " << party[fightA] << " and " << party[fightB] << " ok? (y/n) ";
	cin >> select2;

	if (select2 == 'y' || select2 == 'Y') {
		system("cls");
		doBattle(fightA, fightB);

		cout << endl
			<< "Generate another fight? (y/n) ";
		cin >> select2;

		if (select2 == 'Y' || select2 == 'y')
			fightMenu();
		else
			menu();
	}
	else
		fightMenu();


}

///////////////////////////////////// GENERATION
///////////////////////////////////////////////////////

int rollMe(int diceSides) { // used for dice rolls
	int d6 = rand() % diceSides + 1;
	// cout << "DEBUG: d6 is " << d6 << "\n";
	return d6;
}

int anystat() { // rolls a stat for the ANYSTAT character
	int statterbatter = rand() % 5 + 0;
	// cout << "ANY STAT:  +2 added to " << statName[statterbatter] << endl;
	return statterbatter;
}

void generateCharacter( int goober ) {

	/*
		Need to add...
		- Items
		- Traits
		- Feats
	*/

	int statMod[6],
		jobber = rand() % 6 + 0,
		levelMete = 5,
		death = rand() % 7 + 0,
		HP,
		mtfk = 3;

	double statCal;

	array<double, 4> multiD;

	// generates alignment
	array<int, 2> alignIt{ rand() % 3 + 0, rand() % 3 + 0 };

	for (int dnd = 0; dnd < statMe.size(); dnd++) {

		statMe[dnd] = 0;

		for (int dice = 0; dice < multiD.size(); dice++) { // rolls dice 4 times
			multiD[dice] = rollMe(6);
		} // for dice

		statCal = multiD[0] + multiD[1] + multiD[2] + multiD[3]; //adds dice up
		statCal += 2; // adds the +2 modifier

		statMe[dnd] += statCal;
		statMod[dnd] = statCal;
		statMod[dnd] -= 10;
		statMod[dnd] /= 2;

	} // for dnd

	switch (death) {
		case 0:
			statMe[anystat()] += 2;
			break;
		case 1:
			statMe[1] += commonRace[death][1];
			statMe[2] += commonRace[death][2];
			statMe[3] += commonRace[death][3];
			break;
		case 2:
			statMe[anystat()] += 2;
			break;
		case 3:
			statMe[0] += commonRace[death][0];
			statMe[3] += commonRace[death][3];
			statMe[5] += commonRace[death][5];
			break;
		case 4:
			statMe[1] += commonRace[death][1];
			statMe[4] += commonRace[death][4];
			statMe[5] += commonRace[death][5];
			break;
		case 5:
			statMe[0] += commonRace[death][0];
			statMe[1] += commonRace[death][1];
			statMe[5] += commonRace[death][5];
			break;
		case 6:
			statMe[anystat()] += 2;
			break;
		case 7:
			statMe[anystat()] += 2;
			break;
		default: ;
	}

	int hpp = (statMe[1] - 10) / 2;

	HP = rollMe(hitDice[jobber]) + rollMe(hitDice[jobber]) + rollMe(hitDice[jobber]) + hpp;
	HP *= levelMete;

	/*// EXPERIMENTS //////////////////////////////////////////////// THESE ARE ALL IN recallInfo() FOR NOW
	// str, con, int, dex, wis, cha

	int g_AC = 10 + statMod[3] + 1; // 10 + AB + SB + DEX
	int g_tAC = g_AC - 1; // AC - ( Armor Bonus - Sheild Bonus )
	int g_ffAC = g_AC - statMod[3]; //AC - dex

	// THESE ARE CLASS DEPENDENT. EACH ONE SHOULD HAVE THEIR OWN MD ARRAY FOR EACH CLASS AND LEVEL

	int g_fort = 3 + statMod[1];  // +con
	int g_will = 3 + statMod[3]; // +dex
 	int g_ref = 3 + statMod[4]; // +wis
	int g_bab = 1; // deps on level

	/////////// -------------------------------------+

	int g_cmd = 10 + g_bab + statMod[0] + statMod[3]; // 10 + BAB +

	int g_init = statMod[3];

	//////////////////////////////////////////////////////////////*/

	int bren = 5;

	if (goober == 1) {
		charaSaveA[0] = alignIt[0];
		charaSaveA[1] = alignIt[1];
		charaSaveA[2] = jobber;
		charaSaveA[3] = death;
		charaSaveA[4] = HP;

		for (int i = 0; i < 6; i++) {
			charaSaveA[bren] = statMe[i];
			bren++;
		} // for dndT

		charaSaveA[11] = 10 + statMod[3] + 1; // CMD
		charaSaveA[12] = statMod[3]; // initiative
	}
	else if (goober == 2) {
		charaSaveB[0] = alignIt[0];
		charaSaveB[1] = alignIt[1];
		charaSaveB[2] = jobber;
		charaSaveB[3] = death;
		charaSaveB[4] = HP;

		for (int i = 0; i < 6; i++) {
			charaSaveB[bren] = statMe[i];
			bren++;
		} // for dndT

		charaSaveB[11] = 10 + statMod[3] + 1;
		charaSaveB[12] = statMod[3];

	}


}

void recallInfo( int showUp ) {

	array<int, 13> takedown;

	if(showUp == 1) {
		for (int i = 0; i < 13; i++) {
			takedown[i] = charaSaveA[i];
		}

	}
	else if (showUp == 2) {
		for (int i = 0; i < 13; i++) {
			takedown[i] = charaSaveB[i];
		}
	}

	int leveMete = 1, brow;
	string aliA[2][4]{ { "Lawful", "Neutral", "Chaotic", "?" },{ "Good", "Neutral", "Evil", "?" } };
	array<string, 6> statName{ "STR", "CON", "INT", "DEX", "WIS", "CHA" };
	// array<string, 7> jobCl{ "Freelancer", "White Mage", "Monk", "Catmaster", "Performer", "Black Mage", "Dark Knight" };
	array<double, 6> statMod;

	if (takedown[0] == takedown[1])
		cout << "Alignment: True Neutral " << endl;
	else
		cout << "Alignment: " << aliA[0][takedown[0]] << " " << aliA[1][takedown[1]] << endl;

	cout << "Job: " << jobCl[takedown[2]] << ", " << leveMete << " Level(s)" << endl;

	cout << "Race: ";

	switch (takedown[3]) {
	case 0: cout << "Human\n"; break;
	case 1: cout << "Elf\n"; break;
	case 2: cout << "Orc (?)\n"; break;
	case 3: cout << "Halfing\n"; break;
	case 4: cout << "Dwarf\n"; break;
	case 5: cout << "Gnome\n"; break;
	case 6: cout << "Half-Orc\n"; break;
	case 7: cout << "Half-Elf\n"; break;
	default:;
	}

	switch (commonRace[takedown[3]][6]) {
	case 0:
		cout << "(Small Creature, ";
		break;
	case 1:
		cout << "(Medium Creature, ";
		break;
	default:
		cout << "(Cuthulu Awakens, ";
	}

	cout << "Mvmt " << commonRace[takedown[3]][7] << "ft. )\n" << endl;

	cout << "HP: " << takedown[4] << "\n";

	// EXPERIMENTS ////////////////////////////////////////////////
	// str, con, int, dex, wis, cha

	brow = 5;

	for (int i = 0; i < 6; i++) {
		int statModd = (takedown[brow] - 10) / 2;
		statMod[i] = statModd;
		brow++;
	}

	int g_AC = 10 + statMod[3] + 1; // 10 + AB + SB + DEX
	int g_tAC = g_AC - 1; // AC - ( Armor Bonus - Sheild Bonus )
	int g_ffAC = g_AC - statMod[3]; //AC - dex

	// THESE ARE CLASS DEPENDENT. EACH ONE SHOULD HAVE THEIR OWN 
	// MD ARRAY FOR EACH CLASS AND LEVEL

	int g_fort = 3 + statMod[1];  // +con
	int g_will = 3 + statMod[3]; // +dex
	int g_ref = 3 + statMod[4]; // +wis
	int g_bab = 1; // deps on level

	/////////// -------------------------------------+

	int g_cmd = 10 + g_bab + statMod[0] + statMod[3]; // 10 + BAB + str + dex
	// int g_init = statMod[3]; // dex roll

	/////////// -------------------------------------+

	cout << "AC:\t" << takedown[11] // g_AC
		<< "\tFort:\t" << g_fort
		<< "\tBAB:\t" << g_bab
		<< endl
		<< "T:\t" << g_tAC
		<< "\tRef:\t" << g_ref
		<< "\tCMD:\t" << g_cmd
		<< endl
		<< "FF:\t" << g_ffAC
		<< "\tWill:\t" << g_will
		<< "\tInit:\t" << takedown[12] //g_init
		<< endl
		<< endl;


	//////////////////////////////////////////////////////////////

	// int 
	brow = 5;

	for (int i = 0; i < 6; i++) {
		if (statMod[i] <= 0) {
			cout << "\t" << statName[i] << ": " << takedown[brow] << " ( " << statMod[i] << " )" << "\n"; // displays stats
		}
		else {
			cout << "\t" << statName[i] << ": " << takedown[brow] << " ( +" << statMod[i] << " )" << "\n"; // displays stats
		}
		brow++;
	}

	cout << "\n\nClass Skills:\n--------------------\n\n";
	for (int n = 0; n < 10; n++) {
		switch (jobSkill[takedown[2]][n]) {
		case 0: cout << "Acrobatics\n"; break;
		case 1: cout << "Appraise\n"; break;
		case 2: cout << "Bluff\n"; break;
		case 3: cout << "Climb\n"; break;
		case 4: cout << "Craft\n"; break;
		case 5: cout << "Diplomacy\n"; break;
		case 6: cout << "Disable Divice\n"; break;
		case 7: cout << "Disguise\n"; break;
		case 8: cout << "Escape Artist\n"; break;
		case 9: cout << "Fly\n"; break;
		case 10: cout << "Handle Animal\n"; break;
		case 11: cout << "Heal\n"; break;
		case 12: cout << "Intimidate\n"; break;
		case 13: cout << "Knowledge (arcana)\n"; break;
		case 14: cout << "Knowledge (dungeoneering)\n"; break;
		case 15: cout << "Knowledge (engineering)\n"; break;
		case 16: cout << "Knowledge (geography)\n"; break;
		case 17: cout << "Knowledge (history)\n"; break;
		case 18: cout << "Knowledge (local)\n"; break;
		case 19: cout << "Knowledge (nature)\n"; break;
		case 20: cout << "Knowledge (nobility)\n"; break;
		case 21: cout << "Knowledge (planes)\n"; break;
		case 22: cout << "Knowledge (religion)\n"; break;
		case 23: cout << "Linguistics\n"; break;
		case 24: cout << "Perception\n"; break;
		case 25: cout << "Perform\n"; break;
		case 26: cout << "Profession\n"; break;
		case 27: cout << "Ride\n"; break;
		case 28: cout << "Sense Motive\n"; break;
		case 29: cout << "Slight of Hand\n"; break;
		case 30: cout << "Spellcraft\n"; break;
		case 31: cout << "Stealth\n"; break;
		case 32: cout << "Survival\n"; break;
		case 33: cout << "Swim\n"; break;
		case 34: cout << "Use Magic Device\n"; break;
			//default: cout << "ERR: " << jobSkill[jab][n] << " is not a skill.\n";
		default:;
		}
	}

}

///////////////////////////////////// BATTLE
///////////////////////////////////////////////////////

int doBattle(int desu1, int desu2) {

	SetConsoleTextAttribute(console, 7);

	bool hyperA = false, hyperB = false;
	int grace, counter = 51, round = 0;
	string playa1, playa2;

	for (int burgerPants = 0; burgerPants < 2; burgerPants++) {
		if (burgerPants == 0) {
			playa1 = party[desu1];
			// cout << "Character: " << party[desu1] << endl;
		}
		else {
			playa2 = party[desu2];
			// cout << "Character: " << party[desu2] << endl;
		}

		grace = burgerPants + 1;
		generateCharacter(grace);
		// recallInfo(grace);

	}

	cout << "* * * * * * * * * * * * * * * * * * * * * * * * * \n"
		<< "\t\tB A T T L E\n"
		<< "* * * * * * * * * * * * * * * * * * * * * * * * * \n\n";

	cout << playa1 << ", the " << jobCl[charaSaveA[2]] << " wishes to battle\n"
		<< playa2 << ", the " << jobCl[charaSaveB[2]] << "!" << endl;
	cout << "Its all or nothing! Lets do this!\n" << endl;

	// Set HP
	offense1[0] = charaSaveA[4];
	offense2[0] = charaSaveB[4];

	// Set ATK + STR
	offense1[1] = charaSaveA[5] + 2;
	offense2[1] = charaSaveB[5] + 2;

	// Set CMD
	offense1[2] = charaSaveA[11];
	offense2[2] = charaSaveB[11];

	do {

		round++;
		if (round > 1) {
			cout << "* * * * * * * * * * * * * * * * * * * * * * * * * \n"
				<< "\t\tB A T T L E\n"
				<< "* * * * * * * * * * * * * * * * * * * * * * * * * \n\n";
		}

		cout << "{============+} Round " << round << " {+============}" << endl;

		// Add Braves
		offense1[3]++;
		offense2[3]++;

		if (offense1[3] >= 4) {
			offense1[3] = 3;
			hyperA = true;
		}
		else if (offense1[3] <= -4) offense1[3] = -3;

		if (offense2[3] >= 4) {
			offense2[3] = 3;
			hyperB = true;
		}
		else if (offense2[3] <= -4) offense2[3] = -3;

		cout << "Plyr 1: " << playa1 << "\t"; healthBar(charaSaveA[4], offense1[0]); cout << " [ B: " << offense1[3] << " ]" << endl;
		cout << "Plyr 2: " << playa2 << "\t"; healthBar(charaSaveB[4], offense2[0]); cout << " [ B: " << offense1[3] << " ]" << endl;

		playerFight(playa1, playa2, 0, offense1[1], offense1[3], offense2[0], offense2[2], hyperA);

		playerFight(playa1, playa2, 1, offense2[1], offense2[3], offense1[0], offense1[2], hyperB);


		if (offense1[0] < -10)
			break;
		if (offense2[0] < -10)
			break;

		if (offense1[3] < 2)
			hyperA = false;
		if (offense2[3] < 2)
			hyperB = false;

		if (round >= counter)
			break;

		WaitKey();

	} while (round < counter);

	if (offense1[0] > offense2[0])
		cout << "*** " << playa1 << " WINS !!! ***";
	else
		cout << "*** " << playa2 << " WINS !!! ***";

	cout << endl;

	return 0;

}

void healthBar(int healthy, int health) {
	cout << "<3 [";

	int robust = healthy;

	double heal10 = healthy; // normal health
	heal10 /= 10;
	// cout << "DEBUG: heal10 is " << heal10 << endl;

	array<int, 10> hMet = {
		0,
		robust - (heal10 * 9),
		robust - (heal10 * 8),
		robust - (heal10 * 7),
		robust - (heal10 * 6),
		robust - (heal10 * 5),
		robust - (heal10 * 4),
		robust - (heal10 * 3),
		robust - (heal10 * 2),
		robust - heal10

	};

	//for(int i = 0; i < hMet.size(); i++)
	//	cout << "DEBUG: hMet[" << i << "] is " << hMet[i] << endl;

	SetConsoleTextAttribute(console, 2);

	if (health <  hMet[0])
		cout << "----------";
	if (health >= hMet[0] && health < hMet[1])
		cout << "|---------";
	if (health >= hMet[1] && health < hMet[2])
		cout << "||--------";
	if (health >= hMet[2] && health < hMet[3])
		cout << "|||-------";
	if (health >= hMet[3] && health < hMet[4])
		cout << "||||------";
	if (health >= hMet[4] && health < hMet[5])
		cout << "|||||-----";
	if (health >= hMet[5] && health < hMet[6])
		cout << "||||||----";
	if (health >= hMet[6] && health < hMet[7])
		cout << "|||||||---";
	if (health >= hMet[7] && health < hMet[8])
		cout << "||||||||--";
	if (health >= hMet[8] && health < hMet[9])
		cout << "|||||||||-";
	if (health >= hMet[9])
		cout << "||||||||||";

	SetConsoleTextAttribute(console, 7);

	cout << "] " << health << "/" << robust;

	// return 0;
}

void playerFight(string playa1, string playa2, int playerID, int yATK, int yBR, int eHP, int eCMD, bool hyped) {

	int damage = eHP, bravery = yBR, attack = 0, atkRoll, grace = rollMe(3);
	string you, them;

	if (playerID == 0) {
		you = playa1;
		them = playa2;
	}
	else {
		you = playa2;
		them = playa1;
	}

	cout << endl << "+--- " << you << "'s turn ---+ " << endl;
	atkRoll = rollMe(20) + ((yATK - 10) / 2);

	cout << you << " braves! \t\t(roll: " << atkRoll << ")\n";
	cout << them << " defaults! \t(CMD: " << eCMD << ")\n";


	if (atkRoll >= eCMD) { // if player1 is harder than player2
		if (bravery <= 0) { // if brave is equal or less than 0, cant attack
			SetConsoleTextAttribute(console, 4);
			cout << "... but " << you << " cannot brave nor default! (Braves: " << yBR << " )\n";
		}
		else {
			if (bravery >= 3) {
				attack = rollMe(10) + rollMe(10) + rollMe(10);
				bravery -= 6;
				hyped = true;
				SetConsoleTextAttribute(console, 13);
				cout << "*** HYPER BRAVE! " << you << " inflicts " << attack << " damage! ***\n";
			}
			else {
				attack = rollMe(10);
				bravery--;
				SetConsoleTextAttribute(console, 13);
				cout << "*** " << you << " inflicts " << attack << " damage! *** \n";
			}
		}
	}
	else {
		SetConsoleTextAttribute(console, 4);
		cout << you << "'s attack was blocked!\n";
	}

	SetConsoleTextAttribute(console, 7);

	cout << endl;

	if (playerID == 0) {
		offense2[0] -= attack;
		offense1[3] = bravery;
	}
	else {
		offense1[0] -= attack;
		offense2[3] = bravery;
	}

}


///////////////////////////////////// STORYMODE
///////////////////////////////////////////////////////
// not implemented yet.
// void StoryMode(), StoryMode_CharacterIntro(), StoryMode_LegendsForetold();

void StoryMode() {
	int choice = 5;

	system("cls");
	cout << "\n\t\tNOTE: This is... kinda a demo. Don't expect\n\t\tanything nice for a while ya hear?\n\n";
	WaitKey();

	while (choice != 3 || !cin || cin.fail() || choice == 0 ) {

		colorMe("\t\t          ooooooooooooooooooooo\n\t\t_____oooooooooooooooooooooooooooooo_______\n\t\t__oooooooO THE TOWERING FOREST Oooooooo___\n\t\toooooooooooooooooooooooooooooooooooooooooo\n\n", 2);

		cout << "\t\t   You find yourself in a forest clearing..\n\t\tThe trees sway in the wind as the\n\t\tsun shines through their branches\n";
		cout << "\t\tYou cannot see very far through the trees, \n\t\tsave for another small clearing ahead, and \n\t\tsome small animals teetering about...\n";
		cout << "\n\t\t\t1. Investigate the forest\n\t\t\t2. Check the trees\n\t\t\t3. Check the clearing\n\t\t\t4. Look at the animals\n\n\t\t\tPress a key:  ";
		cin >> choice;
		

		if (!cin || cin.fail()) // or if(cin.fail())
		{
			choice = -1;
			// user didn't input a number
			cin.clear();
			cin.get();
			// next, request user reinput
		}


		switch (choice) {
		case -1:
			colorMe("\t\t\t    ERR: Invalid number.", 14);
			Sleep(300);
			system("cls");
			break;
		case 1:
			system("cls");
			cout << "\n\n\t\tYou were guided to this forest by\n\t\tsome { otherworldly force }...\n\n\t\tYou feel as if something important is here.\n";
			CustomWaitKey("\n\t\t<==-");
			break;
		case 2:
			system("cls");
			cout << "\n\n\t\tThe trees stand tall above you.\n\t\tThey seem to be a type of oak...\n\n\t\tAs long as no monsters pop up\n\t\tyou should be fine.\n";
			CustomWaitKey("\n\t\t<==-");
			break;
		case 3:
			system("cls");
			cout << "\n\n\t\tThe small clearing in front of you\n\t\tlooks wonderfully calm...\n\n\t\tPerhaps you could rest there.\n";
			CustomWaitKey("\n\t\t [Exit to Main Menu] -==>");
			break;
		case 4:
			system("cls");
			cout << "\n\n\t\tA turtle, a hair, and a line of ants\n\t\tgreet you as you stare at them...\n\n\t\tYou wave back to them as you go one with\n\t\tyour buisness.\n";
			CustomWaitKey("\n\t\t<==-");
			break;
		default:
			system("cls");
			cout << "\n\n\t\tAs you stare off into the\n\t\tdistance, a {voice} whispers\n\t\tto you...\n"
				<< "\n\t\t\"The numbers will guide thee\n\tforeward...\"\n";
			CustomWaitKey("\n\t\t<==-");
		}

	}

	menu();

}

void CustomWaitKey(string text)
{
	colorMe(text, 6);
	while (_kbhit()) _getch(); // Empty the input buffer
	_getch(); // Wait for a key
	while (_kbhit()) _getch(); // Empty the input buffer (some keys sends two messages)
	system("cls");
}
