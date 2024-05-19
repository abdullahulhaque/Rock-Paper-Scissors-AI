#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    const int ROCK = 0;
    const int PAPER = 1;
    const int SCISSORS = 2;

    string player;
    cout << "Enter your name: ";
    cin >> player;

    int rounds;
    while (true) {
        cout << "Enter the number of rounds: ";
        cin >> rounds;
        if (rounds < 1) {
            cout << "Rounds must be > 0" << endl;
        } else {
            break;
        }
    }

    cout << player << " vs AI for " << rounds << " rounds" << endl;

    int playerWins = 0;

    int aiWins = 0;

    int playerMoves[3] = {0, 0, 0}; 
    /* This array will store the counts of how many times the user has chosen ROCK, PAPER, and SCISSORS.*/ 

    for (int i = 0; i < rounds; ++i) {
        int playerMove;

        cout << "Enter your move (0 = Rock, 1 = Paper, 2 = Scissors): ";

        cin >> playerMove;
        
        while (playerMove < 0 || playerMove > 2) {
            cout << "Invalid move. Please enter 0 (Rock), 1 (Paper), or 2 (Scissors): ";
            cin >> playerMove;
        }

        int aiMove;

        // AI to predict player's move based on frequency analysis
        int predictedMove;
        if (playerMoves[ROCK] >= playerMoves[PAPER] && playerMoves[ROCK] >= playerMoves[SCISSORS]) {
            predictedMove = ROCK;
        } else if (playerMoves[PAPER] >= playerMoves[ROCK] && playerMoves[PAPER] >= playerMoves[SCISSORS]) {
            predictedMove = PAPER;
        } else {
            predictedMove = SCISSORS;
        }

        // AI chooses a move that beats the predicted move
        if (predictedMove == ROCK) {
            aiMove = PAPER; // Paper beats Rock
        } else if (predictedMove == PAPER) {
            aiMove = SCISSORS; // Scissors beat Paper
        } else {
            aiMove = ROCK; // Rock beats Scissors
        }

        if (playerMove == aiMove) {
            cout << "Tie" << endl;
        } else if ((playerMove == ROCK && aiMove == SCISSORS) ||
                   (playerMove == SCISSORS && aiMove == PAPER) ||
                   (playerMove == PAPER && aiMove == ROCK)) {
            cout << player << " wins with ";
            if (playerMove == ROCK) cout << "rock" << endl;
            else if (playerMove == PAPER) cout << "paper" << endl;
            else if (playerMove == SCISSORS) cout << "scissors" << endl;
            playerWins++;
        } else {
            cout << "AI wins with ";
            if (aiMove == ROCK) cout << "rock" << endl;
            else if (aiMove == PAPER) cout << "paper" << endl;
            else if (aiMove == SCISSORS) cout << "scissors" << endl;
            aiWins++;
        }

        // Track player's move
        playerMoves[playerMove]++;
    }

    cout << player << " wins " << playerWins << " and AI wins " << aiWins << endl;

    return 0;
}
