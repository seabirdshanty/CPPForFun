// #include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <array>
using namespace std;

int rollMe(int diceSides), anystat(), menu();
void logos(), generateCharacter(int goober), recallInfo(int showUp), doBattle(int desu1, int desu2), genMenu(), genMenu2(), fightMenu();

int main() {

	srand(time(NULL));

	logos();

	cout << "Welcome to the Bravely Pathfinder Generator!\n"
		<< "This generator used the 4d6+2 stat creation, \n"
		<< "as well as slightly homebrewed classes. These \n"
		<< "are all based off the game \"Bravely Default\"\n"
		<< "which I love with all of my heart and soul.\n\n"
		<< "I hope this program helps you on any creation\n"
		<< "endevors you persue.\n\n"
		<< "\tHappy Pathfinding!\n\t\t- seabirdshanty, 2017\n"
		<< endl;


	system("pause");

	int shogun;

	do {
		shogun = menu();

		cin.clear(); cin.get();

		if (shogun > 4 || shogun < 0)
			cout << "ERR: Invalid input. " << endl;
		else if (shogun == 1)
			genMenu();
		else if (shogun == 2)
			genMenu2();
		else if (shogun == 3)
			fightMenu();
		else if (shogun == 4)
			break;

	} while (shogun != 4);

	return 0;

} // main

  ///////////////////////////////////// GLOBALS
  ///////////////////////////////////////////////////////

  // alignment1, aligment2, Job, Race, HP, str, con, int, dex, wis, cha
array<int, 11> charaSaveA;
array<int, 11> charaSaveB;
array<double, 6> statMe;

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

/////////////////////////////////// MENUS
///////////////////////////////////////////////////////

void logos() {
	cout << "+----------------------------------------------+" << endl
		<< "|                                              |" << endl
		<< "|             BRAVELY PATHFINDER GEN           |" << endl
		<< "|                                              |" << endl
		<< "+----------------------------------------------+" << endl
		<< endl;
}

int menu() {

	system("cls");

	int select;

	logos();

	cout << "Bravely Pathfinder build 0.2.5a\n"
		<< "coded with love by seabirdshanty\n\n"
		<< "\t [1] Generate Character\n"
		<< "\t [2] Generate Entire Party (4)\n"
		<< "\t [3] Have 2 Characters Battle\n"
		<< "\t [4] Exit\n\n"
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

	if (select > 8 || select < 0)
		genMenu();

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

	system("pause");

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
		cout << "ERR: Invalid.\n";
		fightMenu();
	}
	else
		fightA = select;

	cout << "Please select your second fighter: ";
	cin >> select;
	cin.clear();

	if (cin.fail()) {
		cin.clear(); cin.get();
		cout << "ERR: Invalid.\n";
		fightMenu();
	}
	else
		fightB = select;

	fightA--;
	fightB--;

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
		- BAB
		- Fort, Will, 
		- Items
		- Traits
		- Feats

	*/

	int statMod,
		jobber = rand() % 6 + 0,
		levelMete = 1,
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
	}


}

void recallInfo( int showUp ) {

	array<int, 11> takedown;

	if(showUp == 1) {
		for (int i = 0; i < 11; i++) {
			takedown[i] = charaSaveA[i];
		}

	}
	else if(showUp == 2) {
		for (int i = 0; i < 11; i++) {
			takedown[i] = charaSaveB[i];
		}
	}

	int leveMete = 1;
	string aliA[2][4]{ { "Lawful", "Neutral", "Chaotic", "?" },{ "Good", "Neutral", "Evil", "?" } };
	array<string, 6> statName{ "STR", "CON", "INT", "DEX", "WIS", "CHA" };
	// array<string, 7> jobCl{ "Freelancer", "White Mage", "Monk", "Catmaster", "Performer", "Black Mage", "Dark Knight" };
	array<double, 6> modMe;

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

	int brow = 5;

	for (int i = 0; i < 6; i++) {
		int statMod = (takedown[brow] - 10) / 2;
		modMe[i] = statMod;
		if (modMe[i] <= 0) {
			cout << "\t" << statName[i] << ": " << takedown[brow] << " ( " << modMe[i] << " )" << "\n"; // displays stats
		}
		else {
			cout << "\t" << statName[i] << ": " << takedown[brow] << " ( +" << modMe[i] << " )" << "\n"; // displays stats
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

void doBattle(int desu1, int desu2) {

		int grace, counter;
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
		 << playa2 << ", the " <<  jobCl[charaSaveB[2]] << "!" << endl;
	cout << "Its all or nothing! Lets do this!\n" << endl;

	array<int, 4> offense1{ 0, 0, 0, 1 };
	array<int, 4> offense2{ 0, 0, 0, 1 };
	int attack, round = 0;
	bool hyperA = false, hyperB = false;

	offense1[0] = charaSaveA[4];
	offense2[0] = charaSaveB[4];

	offense1[2] = ((charaSaveA[6] - 10) / 2) * -1;
	offense2[2] = ((charaSaveB[6] - 10) / 2) * -1;

	do {
		round++;
		cout << "--- Round " << round << " ---" << endl;

		offense1[1] = rollMe(20) + ((charaSaveA[5] - 10) / 2);
		offense2[1] = rollMe(20) + ((charaSaveB[5] - 10) / 2);

		cout << playa1 << " (HP: " << offense1[0] << ") braves! (roll: " << offense1[1] << " Braves: " << offense1[3] << " )\n";
		cout << playa2 << " (HP: " << offense2[0] << ") defaults! (roll: " << offense2[1] << " Braves: " << offense2[3] << " )\n";
		

		if (hyperA == true && hyperB == false ) {
			cout << "... but " << playa1 << " cannot brave nor default! (Braves: " << offense1[3] << " )\n";
			for (int i = 0; i < 3; i++) {
				attack = rollMe(hitDice[charaSaveA[2]]);
				offense1[0] -= attack;
				offense1[3]++;
				offense2[3]--;
				cout << "*** " << playa2 << " inflicts " << attack << " damage! *** (Braves: " << offense2[3] << " )\n";
			}
			hyperA = false;
		}
		else if (hyperB == true && hyperA == false ) {
			cout << "... but " << playa2 << " cannot brave nor default! (Braves: " << offense2[3] << " )\n";
			for (int i = 0; i < 3; i++) {
				attack = rollMe(hitDice[charaSaveA[2]]);
				offense2[0] -= attack;
				offense2[3]++;
				offense1[3]--;
				cout << "*** " << playa1 << " inflicts " << attack << " damage! *** (Braves: " << offense1[3] << " )\n";
			}
			hyperB = false;
		}
		else if (hyperA == false && hyperB == false) {

			if (offense1[1] > offense2[1]) { // if player1 is harder than player2
				if (offense1[3] < -2) {
					cout << "Cannot Attack! Not enough Braves!\n\n";
					hyperA = true;
				}
				else {
					if (offense1[3] > 2) {
						attack = rollMe(hitDice[charaSaveA[2]]) + rollMe(hitDice[charaSaveA[2]]) + rollMe(hitDice[charaSaveA[2]]);
						offense2[0] -= attack;
						offense2[3]++;
						offense1[3] -= 6;
						hyperA = true;
						cout << "*** HYPER BRAVE! " << playa1 << " inflicts " << attack << " damage! ***\n";
					}
					else {
						attack = rollMe(hitDice[charaSaveA[2]]);
						offense2[0] -= attack;
						offense2[3]++;
						offense1[3]--;
						cout << "*** " << playa1 << " inflicts " << attack << " damage! *** \n";
					}
				}
			}
			else if (offense1[1] < offense2[1]) {
				if (offense1[3] < -2) {
					cout << "Cannot Attack! Not enough Braves!\n\n";
					hyperB = true;
				}
				else {

					if (offense2[3] > 2) {
						attack = rollMe(hitDice[charaSaveA[2]]) + rollMe(hitDice[charaSaveA[2]]) + rollMe(hitDice[charaSaveA[2]]);
						offense1[0] -= attack;
						offense1[3]++;
						offense2[3] -= 6;
						cout << "*** HYPER BRAVE! " << playa2 << " inflicts " << attack << " damage! ***\n";
						hyperB = true;
					}
					else {
						attack = rollMe(hitDice[charaSaveA[2]]);
						offense1[0] -= attack;
						offense1[3]++;
						offense2[3]--;
						cout << "*** " << playa2 << " inflicts " << attack << " damage! ***\n";
					}
				}

			}
			else if (offense1[1] == offense2[1]) {
				cout << "The spells and swords clash... but nothing happens!\n";
			}
		}
		else if (hyperA == true && hyperB == true) {
			cout << "Both Braved too hard... \n";
			hyperA = false; hyperB = false;
		}

		cout << endl;

		if (offense1[0] < -10)
			break;
		else if (offense2[0] < -10)
			break;
		else if (round >= 50)
			break;

		

	} while (offense1[0] > offense1[2] || offense2[0] > offense2[2]);


	if (offense1[0] > offense2[0]) {
		cout << "*** " << playa1 << " WINS !!! *** \n";
	}
	else {
		cout << "*** " << playa2 << " WINS !!! *** \n";
	}

	cout << endl << endl;

}

