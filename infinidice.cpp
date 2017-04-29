/* ==================================================================
  | INFINIDICE   - Generates 3 sets of 4d6-lowest number stats.     |
  | This took forever for me to figure out. seabirdshanty2017       |
/* ================================================================== */

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <array>

using namespace std;

int main() {
	srand(time(NULL));

	int i,f = 0, d = 4, rolls[4], min, max, sum;
	array<string, 6>stat = {"STR","CON","INT","DEX","WIL","CHA"};

	while (!cin.eof())
	{
		f++;
		cout << "COMPLIATION " << f << endl << endl;

		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 6; k++) {

					for (i = 0; i < d; i++)
						rolls[i] = rand() % 6 + 1;

					max = min = rolls[0];
					for (i = 1; i < d; i++) {
						if (rolls[i] > max)
							max = rolls[i];
						if (rolls[i] < min)
							min = rolls[i];
					}

					sum = (rolls[0] + rolls[1] + rolls[2] + rolls[3]) - min;
				    cout << "GEN " << j << "\t" << stat[k] << " " << sum << endl;
			}

			cout << endl;
		}

		system("pause");
		system("cls");
	}
}
