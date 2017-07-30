#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define N 50
using namespace std;
// created  by Arya H - VAC
void copy(int array1[N][N], int array2[N][N]) { //copies array
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++)
			array2[j][i] = array1[j][i];
	}
}
void life(int array[N][N], char choice) { //main logic of the game
	int temp[N][N];
	copy(array, temp);
	for (int j = 1; j < N - 1; j++) {
		for (int i = 1; i < N - 1; i++) {
			if (choice == 's') {
				int count = 0;
				count = array[j - 1][i] + array[j - 1][i - 1] +
					array[j][i - 1] + array[j + 1][i - 1] +
					array[j + 1][i] + array[j + 1][i + 1] +
					array[j][i + 1] + array[j - 1][i + 1];
				//The cell dies.
				if (count < 2 || count > 3)
					temp[j][i] = 0;
				//The cell stays the same.
				if (count == 2)
					temp[j][i] = array[j][i];
				//The cell either stays alive, or is "born".
				if (count == 3)
					temp[j][i] = 1;
			}
		}
	}
	//Copies the completed temp array back to the main array.
	copy(temp, array);
}
bool compare(int array1[N][N], int array2[N][N]) {
	int count = 0;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			if (array1[j][i] == array2[j][i])
				count++;
		}
	}

	if (count == N * N)
		return true;
	else
		return false;
}
void print(int array[N][N]) { // output
	for (int j = 1; j < N - 1; j++) {
		for (int i = 1; i < N; i++) {
			if (array[j][i] == 1)
				cout << '*';
			else
				cout << ' ';
		}
		cout << endl;
	}
}

int main(void) {
	char ch, again,cont;
	bool comparison;
	int I, S = 1400; // init
	string decoration;

	cout << endl << "This program is a C++ implementation of John Conway's Game of Life.";
	cout << "\n\nEnter iteration I and timestep S(milliseconds:default[1400]):\n";
	cin >> I >> S;
	I -= 1;
	int gen0[N][N];
	int game[N][N];
	int backup[N][N];
	do {
		//Loop to check for proper inputs.
		do {
			cout << "\nEnter 's' to start: \n";
			cin >> ch;
		} while (ch != 's');
		system("CLS");
		int i = 0;
		//Loop that does the bulk of the simulation.
		do {
			//Generates the initial random state of the game board.
			srand(time(NULL));
			for (int j = 1; j < N - 1; j++) {
				for (int i = 1; i < N - 1; i++)
					gen0[j][i] = rand() % 2;
			}
			//Initializes the arrays by copying the gen0 array to the game array.
			if (i == 0)
				copy(gen0, game);
			copy(game, backup);
			print(game);
			life(game, ch);
			i++;
			if (i % I == 1 && i != 1) {
				cout << endl;
				do {
					cout << "\ncycle: " << i  << endl << "Would you like to continue this simulation? (y/n): ";
					cin >> cont;
				} while (cont != 'y' && cont != 'n');
				if (cont == 'n')
					break;
			}
			comparison = compare(game, backup);
			if (comparison == false)
				cout << "\ncycle: " << i << endl;
			Sleep(S); //timestep;
			system("cls");
			if (comparison == true)
				cout << endl;
		} while (comparison == false);
		do {
			cout << "\nWould you like to run another simulation? (y/n): ";
			cin >> again;
		} while (again != 'y' && again != 'n');
	} while (again == 'y');
	return 0;
}
