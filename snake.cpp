#include <iostream>
//#include <stdio.h>
using namespace std;

// Boolean variable to indicate whether or not the game is over
bool game_over;

// Boolean variable to indicate whether or not we're in a new game
bool new_game;

// This is for the boundary size
const int height, width = 20;

// These are for the x and y cooridnates of the snake's head, and fruit resepctively
int x, y, x_fruit, y_fruit;

// Score
int score;

// These are the possible directions that the snake can have
enum Direction {STOP = 0, UP, DOWN, LEFT, RIGHT};

// Declaration of a variable dir, which holds the snake's direction
Direction dir;

// 1st method
bool Setup() {
    game_over = false;
    dir = STOP;
    x = width/2;
    y = height/2;
    x_fruit = rand() % width;
    y_fruit = rand() % height;
    score = 0;
    new_game = true;
    return new_game
}

void Draw(bool is_game_starting) {
    // The first step before drawing is to clear the console (in case of a new game)
    if (is_game_starting == true) {
        system("cls");
    }
    // This for loop is for drawing the top wall
    for (int i =0; i <= width; i++){
        cout << "#";
    }
    // This for loop is for drawing the bottom wall
    for (int i =0; i <= width; i++){
        cout << "#";
    }
}
int main() {
    cout << "Hello World!" << endl;
    return 0;
}
