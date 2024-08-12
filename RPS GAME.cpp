#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

// Constants for moves
const int ROCK = 0;
const int PAPER = 1;
const int SCISSORS = 2;

// Vector to store the player's move history
vector<int> playerMoveHistory;

// Function to get the player's move as a string and convert it to an integer
int getPlayerMove() {
    string moveInput;
    cout << "Enter your move (rock, paper, scissors): ";
    cin >> moveInput;

    // Convert input to lowercase to handle case-insensitive input
    transform(moveInput.begin(), moveInput.end(), moveInput.begin(), ::tolower);

    // Match the input string to the corresponding move constant
    if (moveInput == "rock") return ROCK;
    else if (moveInput == "paper") return PAPER;
    else if (moveInput == "scissors") return SCISSORS;
    else {
        // Handle invalid input by recursively calling the function
        cout << "Invalid move. Please enter 'rock', 'paper', or 'scissors'." << endl;
        return getPlayerMove();
    }
}

// Function to display the move using ASCII art for visual appeal
void displayMove(int move) {
    if (move == ROCK) {
        cout << "ROCK:\n"
             << "    _______\n"
             << "---'   ____)\n"
             << "      (_____)\n"
             << "      (_____)\n"
             << "      (____)\n"
             << "---.__(___)\n";
    } else if (move == PAPER) {
        cout << "PAPER:\n"
             << "    _______\n"
             << "---'   ____)____\n"
             << "          ______)\n"
             << "          _______)\n"
             << "         _______)\n"
             << "---.__________)\n";
    } else if (move == SCISSORS) {
        cout << "SCISSORS:\n"
             << "    _______\n"
             << "---'   ____)____\n"
             << "          ______)\n"
             << "       __________)\n"
             << "      (____)\n"
             << "---.__(___)\n";
    }
}

// Function to display the result of each round
void displayRoundResult(int playerMove, int aiMove) {
    cout << "You chose:\n";
    displayMove(playerMove);
    cout << "AI chose:\n";
    displayMove(aiMove);

    // Determine the outcome of the round
    if (playerMove == aiMove) {
        cout << "It's a tie!" << endl;
    } else if ((playerMove == ROCK && aiMove == SCISSORS) ||
               (playerMove == PAPER && aiMove == ROCK) ||
               (playerMove == SCISSORS && aiMove == PAPER)) {
        cout << "You win this round!" << endl;
    } else {
        cout << "AI wins this round!" << endl;
    }
}

// Function to predict the next move based on the player's move history
int predictNextMove() {
    int n = playerMoveHistory.size();

    // If there are less than 3 moves, not enough data to predict, so choose randomly
    if (n < 3) {
        return rand() % 3;
    }

    // Check for simple repeating patterns
    int lastMove = playerMoveHistory[n-1];
    int secondLastMove = playerMoveHistory[n-2];
    int thirdLastMove = playerMoveHistory[n-3];

    if (lastMove == secondLastMove && secondLastMove == thirdLastMove) {
        // Predict that the player will continue the pattern
        return lastMove;
    } else {
        // Predict based on the most frequent move in the history
        int countRock = 0, countPaper = 0, countScissors = 0;
        for (int move : playerMoveHistory) {
            if (move == ROCK) countRock++;
            else if (move == PAPER) countPaper++;
            else countScissors++;
        }
        // Return the move that the player has chosen most frequently
        if (countRock >= countPaper && countRock >= countScissors) return ROCK;
        else if (countPaper >= countRock && countPaper >= countScissors) return PAPER;
        else return SCISSORS;
    }
}

// Function to generate the AI's move based on the predicted player move
int getAIMove() {
    int predictedMove = predictNextMove();

    // AI chooses a move that beats the predicted move
    if (predictedMove == ROCK) return PAPER;  // Paper beats Rock
    else if (predictedMove == PAPER) return SCISSORS;  // Scissors beat Paper
    else return ROCK;  // Rock beats Scissors
}

// Function to update the player's move history after each round
void updateHistory(int playerMove) {
    playerMoveHistory.push_back(playerMove);

    // Limit the history size to avoid excessive memory use
    if (playerMoveHistory.size() > 100) {
        playerMoveHistory.erase(playerMoveHistory.begin());
    }
}

int main() {
    // Variables to store player's name and the number of rounds
    string player;
    cout << "Enter your name: ";
    cin >> player;

    int rounds;
    while (true) {
        // Ask the player for the number of rounds to play
        cout << "Enter the number of rounds: ";
        cin >> rounds;
        if (rounds < 1) {
            cout << "Rounds must be > 0" << endl;
        } else {
            break;
        }
    }

    // Display the matchup and number of rounds
    cout << player << " vs AI for " << rounds << " rounds" << endl;

    // Variables to track wins for both player and AI
    int playerWins = 0, aiWins = 0;

    // Main game loop for each round
    for (int i = 0; i < rounds; ++i) {
        int playerMove = getPlayerMove();  // Get the player's move
        int aiMove = getAIMove();  // Generate the AI's move

        updateHistory(playerMove);  // Update the history with the player's move

        displayRoundResult(playerMove, aiMove);  // Display the result of the round

        // Update the scores based on the round's outcome
        if ((playerMove == ROCK && aiMove == SCISSORS) ||
            (playerMove == PAPER && aiMove == ROCK) ||
            (playerMove == SCISSORS && aiMove == PAPER)) {
            playerWins++;
        } else if (playerMove != aiMove) {
            aiWins++;
        }

        // Display the current score after each round
        cout << "Score: " << player << " " << playerWins << " - AI " << aiWins << endl;
    }

    // Display the final result after all rounds are completed
    cout << player << " wins " << playerWins << " and AI wins " << aiWins << endl;
    return 0;
}
