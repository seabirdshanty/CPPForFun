#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <array>
using namespace std;

array<double, 6> statMe;

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

int raceChange() { // dictates race for character

	int death = rand() % 7 + 0;
	int commonRace[8][8]{ // Race Stat changes, 
						  // str, con, int, dex, wis, cha, size, speed
		{ 0, 0, 0, 0, 0, 0, 1, 30 }, // Human, ANY
		{ 0, -2, 2, 2, 0, 0 , 1, 30 }, // Elf
		{ 0, 0, 0, 0, 0, 0, 1, 30 }, // Orc, ANY
		{ -2, 0 , 0 , 2, 0, 2, 1, 20 }, // Halfing
		{ 0, 2, 0, 0, 2, -2, 1, 20 }, // Dwarf
		{ -2, 2, 0, 0, 0, 2, 0, 30 }, // Gnome
		{ 0, 0, 0, 0, 0, 0, 1, 30 }, // Half-Orc, ANY
		{ 0, 0, 0, 0, 0, 0, 1, 30 } // Half-Elf, ANY
	};

	cout << "Race: ";

	switch (death) {
	case 0:
		cout << "Human\n";
		// +2 Any
		statMe[anystat()] += 2;
		break;
	case 1:
		cout << "Elf\n";
		statMe[1] += commonRace[death][1];
		statMe[2] += commonRace[death][2];
		statMe[3] += commonRace[death][3];
		break;
	case 2:
		cout << "Orc (?)\n";
		// Nani the Fuck?
		statMe[anystat()] += 2;
		break;
	case 3:
		cout << "Halfing\n";
		statMe[0] += commonRace[death][0];
		statMe[3] += commonRace[death][3];
		statMe[5] += commonRace[death][5];
		break;
	case 4:
		cout << "Dwarf\n";
		statMe[1] += commonRace[death][1];
		statMe[4] += commonRace[death][4];
		statMe[5] += commonRace[death][5];
		break;
	case 5:
		cout << "Gnome\n";
		statMe[0] += commonRace[death][0];
		statMe[1] += commonRace[death][1];
		statMe[5] += commonRace[death][5];
		break;
	case 6:
		cout << "Half-Orc\n";
		// +2 Any
		statMe[anystat()] += 2;
		break;
	case 7:
		cout << "Half-Elf\n";
		// +2 any.
		statMe[anystat()] += 2;
		break;
	default:
		cout << "ERR: " << death << " ain't a race.\n";
	}

	switch (commonRace[death][6]) {
	case 0: cout << "(Small Creature, "; break;
	case 1:  cout << "(Medium Creature, "; break;
	default: cout << "(Cuthulu Awakens, ";
	}

	cout << "Mvmt " << commonRace[death][7] << "ft. )\n" << endl;

	return death;
}


int forHealthAndHome(int healthy, int cons) {
	array<int, 7> hitDice{ 10, 6, 12, 10, 8, 6, 12 };
	int hitPointer = rollMe(hitDice[healthy]) + cons;
	return hitPointer;
}

int skillKill(int jab) {

	int jobSkill[7][10]{
		{ 2, 5, 12, 14, 18, 24, 26, 28, 32, -1 }, //Freelancer
		{ 5, 8, 11, 13, 19, 22, 23, 24, 30, 34 }, //White Mage (HEALER)
		{ 0, 2, 3, 8, 12, 16, 22, 24, 28, 31 }, // Monk
		{ 0, 2, 3, 7, 10, 16, 24, 27, 28, 32 }, // Catmaster
		{ 2, 5, 7, 17, 20, 23, 25, 26, 28, 34 }, // Performer
		{ 1, 4, 6, 9, 13, 21, 24, 29, 30, 34 }, // Black Mage
		{ 2, 5, 7, 11, 12, 17, 20, 24, 28, 32 } // Dark Knight
	};

	cout << "\n\nClass Skills:\n--------------------\n\n";
	for (int n = 0; n < 10; n++) {
		switch (jobSkill[jab][n]) {
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

	return 0;
}

int generateCharacter() {

	int statMod, jobber, leveMete = 1;
	double statCal;
	array<double, 4> multiD;
	array<double, 6> modMe;
	array<string, 6> statName{ "STR", "CON", "INT", "DEX", "WIS", "CHA" };
	array<string, 7> jobCl{ "Freelancer", "White Mage", "Monk", "Catmaster", "Performer", "Black Mage", "Dark Knight" };

	jobber = rand() % 6 + 0;
	cout << "Job: " << jobCl[jobber] << ", " << leveMete << " Level(s)" << endl;

	for (int dnd = 0; dnd < statMe.size(); dnd++) {

		statMe[dnd] = 0;

		for (int dice = 0; dice < multiD.size(); dice++) { // rolls dice 4 times
			multiD[dice] = rollMe(6);
		} // for dice

		statCal = multiD[0] + multiD[1] + multiD[2] + multiD[3]; //adds dice up
		statCal += 2; // adds the +2 modifier

		statMe[dnd] += statCal;

	} // for dnd

	  ///////////////////////////////
	raceChange(); // Determines race
				  ///////////////////////////////

	cout << "HP: " << forHealthAndHome(jobber, statMe[1]) << "\n";

	for (int dndT = 0; dndT < modMe.size(); dndT++) {
		statMod = (statMe[dndT] - 10) / 2; // calculates modifiers for each stat
		modMe[dndT] = statMod;
		if (modMe[dndT] <= 0) {
			cout << "\t" << statName[dndT] << ": " << statMe[dndT] << " ( " << modMe[dndT] << " )" << "\n"; // displays stats
		}
		else {
			cout << "\t" << statName[dndT] << ": " << statMe[dndT] << " ( +" << modMe[dndT] << " )" << "\n"; // displays stats
		}

	} // for dnd

	  ///////////////////////////////
	skillKill(jobber); // Sets Skills
					   ///////////////////////////////

	return 0;
}

void main() {

	// Lets get the randomizer started
	srand(time(NULL));

	char again;
	int chooseMe;
	// Bravely Default Defaults. Because Why not?
	array<string, 8> party{
		"Agnes Oblige",
		"Tiz Arrior",
		"Edea Lee",
		"Ringabel",
		"Alternis Dim",
		"Yew Genolgia",
		"Magnolia Arche",
		"Janne Wolfe"
	};

	do {

		cout << "Bravely Pathfinder Character Gen\n"
			<< "Uses the 4d6+2 method of stat gen.\n\n"
			<< "\t[1] Agnes Oblige\n"
			<< "\t[2] Tiz Arrior\n"
			<< "\t[3] Edea Lee\n"
			<< "\t[4] Ringabel\n"
			<< "\t[5] Alternis Dim\n"
			<< "\t[6] Yew Genolgia\n"
			<< "\t[7] Magnolia Arche\n"
			<< "\t[8] Janne Wolfe\n\n"

			<< "Please choose a character: ";
		cin >> chooseMe;

		while (chooseMe >= 9 || chooseMe == 0)
		{
			cout << "Invalid Character\n"
				<< "Please choose a character (1 - 8): ";
			cin >> chooseMe;
		} // while

		system("cls");
		chooseMe -= 1;
		cout << "Character: " << party[chooseMe] << endl;

		generateCharacter();

		cout << "\n\n";
		cout << "Generate another character? (y/n) ";
		cin >> again;
		system("cls");

	} while (again == 'Y' || again == 'y');

} // main
