// Course: IGME 309-02
// Student Name: Andrew Broderick
// Assignment Number: 01

#include <iostream>
#include "header.h"
using namespace std;

bool active = true;
int numGuesses = 0;
int solution = rand() % 100 + 1;
int input = 0;
char yesNo = 'a';

int main() {
	cout << "Welcome to the Game!" << endl << "Please guess the number between 1 and 100.\n" << endl;

	while(active){
		// Take input. Increase number of guesses accordingly.
		cout << "Enter a number (-1 to quit): ";
		cin >> input;
		numGuesses++;

		if (input == -1) { 
			// Option to quit.
			cout << "You're about to quit the game. Keep playing? (y/n)" << endl;
			cin >> yesNo;
			if (yesNo == 'n') {
				active = false;
				return 0;
			}
		}
		else if (input == solution) { 
			// Win. Option to quit or reset.
			cout << "Your guess is correct! The number of guesses is " << numGuesses << "." << endl;
			cout << "Continue to play ? (y / n)" << endl;
			cin >> yesNo;
			if (yesNo == 'n') {
				active = false;
				return 0;
			}
			else if (yesNo == 'y') {
				reset();
			}
		}
		else if (input > solution) {
			// Provide feedback.
			cout << "Your guess is high." << endl;
		}
		else if (input < solution) {
			// Provide feedback.
			cout << "Your guess is low." << endl;
		}
	}
}

// Resets the game so that the player can play again after they win.
void reset() {
	numGuesses = 0;
	solution = rand() % 100 + 1;
	input = 0;
	yesNo = 'a';

	cout << "Replay: new target number is generated!" << endl;
}
