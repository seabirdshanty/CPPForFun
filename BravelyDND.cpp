#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <array>
using namespace std;

// A whole bunch of globals. someones rolling in their grave, i'm sure.
double d6, statCal;
int statMod, chooseMe;
char again;
array<string, 4> party{ "Agnes Oblige", "Tiz Arrior", "Edea Lee", "Ringabel" };
array<string, 7> jobCl{ "Freelancer", "White Mage", "Monk", "Catmaster", "Performer", "Black Mage", "Templar" }; 
// Freelancer should never show up, because d6 only gens #s 1 - 6
array<string, 6> statName{ "STR", "CON", "INT", "DEX", "WIS", "CHA" };
array<double, 4> multiD;
array<double, 6> statMe;

int rollMe() { // rolls the die
	d6 = rand() % 6 + 1;
	// cout << "DEBUG: d6 is " << d6 << "\n";
	return 0;
}

int statsCharacter() { // generates stats

	for (int dnd = 0; dnd < statMe.size(); dnd++) {

		for (int dice = 0; dice < multiD.size(); dice++) {
			rollMe();
			multiD[dice] = d6;
		} // for dice

		statCal = multiD[0] + multiD[1] + multiD[2] + multiD[3];
		statCal += 2;
		statMod = (statCal - 10) / 2;

		statMe[dnd] = statCal;
		cout << "\t" << statName[dnd] << ": " << statMe[dnd] << " ( " << statMod << " )" << "\n";
	} // for dnd
	return 0;
}

int main() {

	srand(time(NULL)); // grabs time

	/* For straight out generation or debugging.
	for (int k = 0; k < party.size(); k++) {
	cout << "Character: " << party[k] << endl;
	rollMe();
	cout << "Job: " << jobCl[k] << endl;
	statsCharacter();
	cout << "\n\n";
	}
	*/

	do {
  
		cout << "Bravely Default DND Character Gen\n"
			<< "Uses the 4d6 method of stat gen.\n\n"
			<< "\t[1] Agnes Oblige\n"
			<< "\t[2] Tiz Arrior\n"
			<< "\t[3] Edea Lee\n"
			<< "\t[4] Ringabel\n\n"
			<< "Please choose a character: ";
		cin >> chooseMe;
		while (chooseMe >= 5 || chooseMe == 0)
		{
			cout << "Invalid Character\n" 
				<< "Please choose a character (1 - 4): ";
			cin >> chooseMe;
		} // while

		cout << "\n";
		chooseMe -= 1;
		cout << "Character: " << party[chooseMe] << endl;
		rollMe();
		cout << "Job: " << jobCl[chooseMe] << endl;
		statsCharacter();

		cout << "\n";

		cout << "Generate another character? (y/n) ";
		cin >> again;
		system("cls");

	} while (again == 'Y' || again == 'y');

  return 0;
} // main
