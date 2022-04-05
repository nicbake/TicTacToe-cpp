#include <iostream>
#include <cstring>

using namespace std;

void drawBoard(char **board) {
    std::cout<<"\n";
    for (int i = 0; i < 3; i++) {
        std::cout<<board[i][0]<<" | "<<board[i][1]<<" | "<<board[i][2]<<"\n";
        if (i != 2) {
            std::cout<<"---------\n";
        }
    }
    std::cout<<"\n";
}

char** createInital() {
    char** board = new char*[3];

    for(int i = 0; i < 3; i++)
        board[i] = new char[3];

    int count = 0;

    for (int j = 0; j < 3; j++) {
        board[j][0] = '0' + count++;
        board[j][1] = '0' + count++;
        board[j][2] = '0' + count++;
    }
    return board;
}

char** makeCopy(char **board) {
    char** copy = new char*[3];

    for(int i = 0; i < 3; i++)
        copy[i] = new char[3];

    for (int j = 0; j < 3; j++) {
        copy[j][0] = board[j][0];
        copy[j][1] = board[j][1];
        copy[j][2] = board[j][2];
    }
    return copy;
}

bool hasRow(char **board,char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
    }
    return false;
}

bool hasCol(char **board,char player) {
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true;
        }
    }
    return false;
}

bool hasDiag(char **board,char player) {
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    if (board[2][0] == player && board[1][1] == player && board[0][2] == player) {
        return true;
    }
    return false;
}

char checkWin(char **board) {
    if (hasRow(board,'x') == true || hasCol(board,'x') == true || hasDiag(board,'x') == true) {
        return 'x';
    } else if (hasRow(board,'o') == true || hasCol(board,'o') == true || hasDiag(board,'o') == true) {
        return 'o';
    } 

    int x = 0, o = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 'x') {
                x++;
            } else if (board[i][j] == 'o') {
                o++;
            }
        }
    }
    if ((o + x) == 9) {
        return 't';
    } else {
        return 'c';
    }
}

bool printWinner(char **board) {
    char str = checkWin(board);
    if (str == 'x') {
        std::cout<<"\nThe game resulted x winning\n";
        return true;
    } else if (str == 'o') {
        std::cout<<"\nThe game resulted o winning\n";
        return true;
    } else if (str == 't') {
        std::cout<<"\nThe game resulted in a Tie\n";
        return true;
    } else {
        return false;
    }
}

int miniMax(char **board, int depth, int alpha, int beta, bool isMax, char *computer, char *player) {
    char check = checkWin(board);
    if (check == *computer) {
        return (10-depth);
    } else if (check == *player) {
        return (-10-depth);
    } else if (check == 't') {
        return (0-depth);
    }

    if (isMax == true) {
        int bestScore = -10000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'x' && board[i][j] != 'o') {
                    char tmp = board[i][j];
                    board[i][j] = *computer;
                    int score = miniMax(board,depth+1,alpha,beta,false,computer,player);
                    board[i][j] = tmp;
                    
                    if (bestScore < score) {
                        bestScore = score;
                    }

                    if (alpha < score) {
                        alpha = score;
                    }
                    if (beta <= alpha) {
                        break;
                    }

                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 10000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'x' && board[i][j] != 'o') {
                    char tmp = board[i][j];
                    board[i][j] = *player;
                    int score = miniMax(board,depth+1,alpha,beta,true,computer,player);
                    board[i][j] = tmp;
                    if (bestScore > score) {
                        bestScore = score;
                    }

                    if (beta > score) {
                        beta = score;
                    }
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return bestScore;
    }
}

void computerMove(char **board, char *computer, char *player) {
    int bestScore = -10000;
    int depth_tmp = 0;
    int x = -1, y = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 'x' && board[i][j] != 'o') {
                char tmp = board[i][j];
                board[i][j] = *computer;
                int score = miniMax(board,0,-10000,10000,false,computer,player);
                board[i][j] = tmp;

                if (score > bestScore) {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    if (x != -1 && y != -1) 
        board[x][y] = *computer;
}

void playGame(char **board, char *player, char *computer) {
    int lock = 0;
    int check = 0;


    while (lock == 0) {
        drawBoard(board);

        if (check == 0) {
            std::cout<<"input the number that matches your move: ";
            char *move = new char;
            std::cin>>*move;
            if (strcmp(move,(char *)"x") || strcmp(move,(char *)"o")) {
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if ((board[i][j]) == *move) {
                            check = 1;
                            board[i][j] = *player;
                        }
                    }
                }
            }
        }

        if (printWinner(board) == true) {
            drawBoard(board);
            lock = 1;
            break;
        }

        if (lock == 0 && check == 1) {
            computerMove(board,computer,player);
        }

        if (printWinner(board) == true) {
            drawBoard(board);
            lock = 1;
            break;
        }


        check = 0;
    }
}

int main() {

    int lock = 0;
    char *player = new char;

    while (lock == 0) {
        // Introduce the user
        std::cout<<"\nWelcome to a 3x3 version of tictactoe using c++!\n";
        std::cout<<"Users can play either \'x\' or \'o\'\n";
        std::cout<<"Enter the player you want to be: \n";

        std::cin>>*player;


        if (*player == 'x' || *player == 'o') {
            std::cout<<"You chose: "<<*player<<"\n";
            lock = 1;
        }
    }

    char *computer = new char;

    if (*player == 'x') {
        *computer = 'o';
    } else {
        *computer = 'x';
    }

    // Create the board
    char** board = createInital();
    playGame(board,player,computer);

    
    return 0;
}