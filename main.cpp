#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const char PLAYER = 'X';
const char AI = 'O';
const char EMPTY = ' ';

// Function declarations
void printBoard(const vector<char>& board);
bool isGameOver(const vector<char>& board);
bool checkDraw(const vector<char>& board); // Declaration added
int minimax(vector<char> board, int depth, bool isMaximizing);
void makeAIMove(vector<char>& board);
bool isMoveValid(const vector<char>& board, int move);
void makePlayerMove(vector<char>& board, int move, char playerSymbol);
bool checkWin(const vector<char>& board, char playerSymbol);
void playPlayerVsPlayer();
void playPlayerVsAI();

// Printing the Tic-Tac-Toe board
void printBoard(const vector<char>& board) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i > 0) {
            cout << endl << "_____|_____|_____" << endl;
        }
        if (i % 3 == 0) {
            cout << "     |     |     " << endl;
        }
        cout << "  " << (board[i] == ' ' ? (char)(i + '1') : board[i]) << "  ";
        if (i % 3 < 2) {
            cout << "|";
        }
    }
    cout << endl;
}

// Check if the game is over by checking for wins or a draw
bool isGameOver(const vector<char>& board) {
    for (int i = 0; i < 3; i++) {
        if (board[i] == board[i + 3] && board[i] == board[i + 6] && board[i] != EMPTY) return true;
        if (board[i * 3] == board[i * 3 + 1] && board[i * 3] == board[i * 3 + 2] && board[i * 3] != EMPTY) return true;
    }
    if (board[0] == board[4] && board[0] == board[8] && board[0] != EMPTY) return true;
    if (board[2] == board[4] && board[2] == board[6] && board[2] != EMPTY) return true;
    
    return checkDraw(board);
}

// Check for a draw in the game
bool checkDraw(const vector<char>& board) {
    for (int i = 0; i < board.size(); i++) {
        if (board[i] == EMPTY) return false;
    }
    return true;
}

// Minimax algorithm for AI decision-making
int minimax(vector<char> board, int depth, bool isMaximizing) {
    if (isGameOver(board)) {
        if (board[4] == AI) return 1;
        else if (board[4] == PLAYER) return -1;
        return 0;
    }

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] == EMPTY) {
                board[i] = AI;
                bestScore = max(bestScore, minimax(board, depth + 1, false));
                board[i] = EMPTY;
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] == EMPTY) {
                board[i] = PLAYER;
                bestScore = min(bestScore, minimax(board, depth + 1, true));
                board[i] = EMPTY;
            }
        }
        return bestScore;
    }
}

// Function for AI to make a move
void makeAIMove(vector<char>& board) {
    int bestMove = -1;
    int bestScore = -1000;

    for (int i = 0; i < 9; i++) {
        if (board[i] == EMPTY) {
            board[i] = AI;
            int score = minimax(board, 0, false);
            board[i] = EMPTY;

            if (score > bestScore) {
                bestScore = score;
                bestMove = i;
            }
        }
    }

    board[bestMove] = AI;
}

// Function to validate a move
bool isMoveValid(const vector<char>& board, int move) {
    return (move >= 0 && move < 9 && board[move] == EMPTY);
}

// Function for a player to make a move
void makePlayerMove(vector<char>& board, int move, char playerSymbol) {
    board[move] = playerSymbol;
}

// Check if a player has won
bool checkWin(const vector<char>& board, char playerSymbol) {
    for (int i = 0; i < 3; i++) {
        if (board[i] == playerSymbol && board[i + 3] == playerSymbol && board[i + 6] == playerSymbol) return true;
        if (board[i * 3] == playerSymbol && board[i * 3 + 1] == playerSymbol && board[i * 3 + 2] == playerSymbol) return true;
    }
    if ((board[0] == playerSymbol && board[4] == playerSymbol && board[8] == playerSymbol) ||
        (board[2] == playerSymbol && board[4] == playerSymbol && board[6] == playerSymbol)) return true;
    return false;
}

// Function to start a Player vs Player game
void playPlayerVsPlayer() {
    vector<char> board(9, EMPTY);
    char currentPlayer = PLAYER;

    cout << "Player vs Player Tic-Tac-Toe\n";
    while (true) {
        printBoard(board);
        int move;
        while (true) {
            cout << "Player " << currentPlayer << ", enter your move (1-9): ";
            cin >> move;
            if (isMoveValid(board, move - 1)) {
                makePlayerMove(board, move - 1, currentPlayer);
                break;
            } else {
                cout << "Invalid move. Try again.\n";
            }
        }

        if (checkWin(board, currentPlayer)) {
            printBoard(board);
            cout << "Player " << currentPlayer << " wins!\n";
            break;
        } else if (checkDraw(board)) {
            printBoard(board);
            cout << "It's a draw!\n";
            break;
        }

        currentPlayer = (currentPlayer == PLAYER) ? 'O' : 'X';
    }
}

// Function to start a Player vs AI game
void playPlayerVsAI() {
    vector<char> board(9, EMPTY);

    cout << "Player vs AI Tic-Tac-Toe\n";
    char playerSymbol;
    while (true) {
        cout << "Choose your symbol (X or O): ";
        cin >> playerSymbol;
        if (playerSymbol == PLAYER || playerSymbol == AI) {
            break;
        } else {
            cout << "Invalid symbol. Choose either X or O.\n";
        }
    }

    cout << "You are " << playerSymbol << " and the AI is " << (playerSymbol == PLAYER ? AI : PLAYER) << ".\n";

    while (true) {
        if (playerSymbol == PLAYER) {
            printBoard(board);
            int move;
            while (true) {
                cout << "Enter your move (1-9): ";
                cin >> move;
                if (isMoveValid(board, move - 1)) {
                    makePlayerMove(board, move - 1, PLAYER);
                    break;
                } else {
                    cout << "Invalid move. Try again.\n";
                }
            }

            if (checkWin(board, PLAYER)) {
                printBoard(board);
                cout << "You win!\n";
                break;
            } else if (checkDraw(board)) {
                printBoard(board);
                cout << "It's a draw!\n";
                break;
            }
        } else {
            printBoard(board);
            cout << "AI is making its move..." << endl;
            makeAIMove(board);

            if (checkWin(board, AI)) {
                printBoard(board);
                cout << "AI wins!\n";
                break;
            } else if (checkDraw(board)) {
                printBoard(board);
                cout << "It's a draw!\n";
                break;
            }
        }

        playerSymbol = (playerSymbol == PLAYER) ? AI : PLAYER;
    }
}

// Driver function
int main() {
    int choice;
    while (true) {
        cout << "Tic-Tac-Toe Menu:\n";
        cout << "1. Player vs Player\n";
        cout << "2. Player vs AI\n";
        cout << "3. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                playPlayerVsPlayer();
                break;
            case 2:
                playPlayerVsAI();
                break;
            case 3:
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please choose again.\n";
                break;
        }
    }

    return 0;
}