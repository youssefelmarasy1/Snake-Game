#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

// Boolean variable to indicate whether or not the game is over
bool game_over;

// Boolean variable to indicate whether or not we're in a new game
bool new_game;

// This is for the boundary size
const int width = 20;
const int height = 20;

// These are for the x and y cooridnates of the snake's head, and fruit, resepctively
int x, y, x_fruit, y_fruit = 0;

// Score
int score;

// These are the possible directions that the snake can have
enum Direction {STOP = 0, UP, DOWN, LEFT, RIGHT};

// Declaration of a variable dir, which holds the snake's direction
Direction dir;

// Holds the ASCII value of the pressed key on the keyboard
char key;
// arrays with up to 100 elements for the x and y coordinates of the tail
int tail_x[100], tail_y[100];
int n_tail;

// 1st method
void Setup() {
    game_over = false;
    dir = STOP;
    x = width/2;
    y = height/2;

    // Uncomment these lines if you want the fruit spawning location to be random in  every game
    // x_fruit = rand() % width;
    // y_fruit = rand() % height;

    // Uncomment these lines if you want the fruit spawning location to be the same every game
    x_fruit = width/4;
    y_fruit = width/4;

    score = 0; // Initializing the score
    n_tail = 0;  // Initialize the tail
}

/* 
This function draws the game's frame. It consists of 3 for loops.
The first for loop draws the top wall.
The second for loop draws the left and right walls, and draws the snake head and fruit in between.
The third for loop draws the bottom wall.
*/
void Draw() {
    // Setting the cursor position to the top-left corner of the console window
    COORD position;
    position.X = 0;
    position.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);

    // This for loop is for drawing the top wall
    for (int i = 0; i < width + 2; i++) {
        cout << "#";
    }
    cout << endl;

    // This for loop is for drawing the left and right walls
    for (int i = 0; i < height; i++) {

        for (int j = 0; j < width; j++) {
            // Drawing the left wall boundary
            if (j == 0) {
                cout << "#";
            }

            // Drawing the snake head when the for loop iterates to x and y positions
            if (i == y && j == x) {
                cout << "O";
            }

            // Drawing the fruit when the for loop iterates to the fruit's x and y positions
            else if (i == y_fruit && j == x_fruit) {
                cout << "F"; // This is the unicode representation of the apple emoji
            }

            // Print the spaces in between the left and right wall boundaries
            else {
                bool print_tail = false;
                // Prints the tail segments
                for (int k = 0; k < n_tail; k++) {
                    
                    if (tail_x[k] == j && tail_y[k] == i) {
                        cout << "o";
                        print_tail = true;
                    }
                    
                }
                if (!print_tail) {
                        cout << " ";
                    }
            }

            // Drawing the right wall boundary
            if (j == width - 1) {
                cout << "#";
            }
        }
        cout << endl;
    }

    // This for loop is for drawing the bottom wall
    for (int i = 0; i < width + 2; i++) {
        cout << "#";
    }
    cout << endl;
    cout << "Score: " << score << endl;
}


void Input(){
    // _kbhit() detects whether or not any key is pressed on the keyboard
    if (_kbhit()){

        // _getch detects which key is pressed and returns its ASCII value
        switch(_getch()){
            case 'a': // a key
                dir = LEFT;
                break;
            case 's': // s key
                dir = DOWN;
                break;
            case 'w': // w key
                dir = UP;
                break;
            case 'd': // d key
                dir = RIGHT;
                break;
            case 72:  // Up arrow key
                dir = UP;
                break;
            case 80:  // Down arrow key
                dir = DOWN;
                break;
            case 75:  // Left arrow key
                dir = LEFT;
                break;
            case 77:  // Right arrow key
                dir = RIGHT;
                break;
            case 'x': // x key
                game_over = true;
                break;
            default:
                // Handle other keys if needed
                break;

        }
    }

    
}

void Logic(){
    // Storing the current coordinates of the first tail segment
    int prev_x = tail_x[0];
    int prev_y = tail_y[0];
    int prev2_x, prev2_y;
    // These two lines are for making the tail segemnts follow the snake's head
    tail_x[0] = x;
    tail_y[0] = y;

    // Moving the rest of the tail segments to follow each other in sequence
    for (int i =1; i < n_tail; i++){
        prev2_x = tail_x[i];
        prev2_y = tail_y[i];
        tail_x[i] = prev_x;
        tail_y[i] = prev_y;
        prev_x = prev2_x;
        prev_y = prev2_y;
    }
    // Moving the snake's head based on the current direction
    switch(dir){
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        default:
            break;
    }
    // Terminates the game if the snake head hits the wall
    if (x > width || x < 0 || y > height || y < 0){
        cout << "Game over: snake head hit the wall!" << endl;
        game_over = true;
    }

    for (int i = 0; i< n_tail; i++){
        // Checking if the snake's head hits any of the tail segements
        if(tail_x[i] == x && tail_y[i] == y){
            // If the condition is true, then the game is over
            cout << "Game over: snake head hit its tail!" << endl;
            game_over = true;
        }
    }
    // Check if the snake's head reaches the fruit, update the score, and spawn a new fruit
    if (x == x_fruit && y== y_fruit){
        score += 10;
        x_fruit = rand() % width;
        y_fruit = rand() % height;
        n_tail++;

    }
}


int main() {
    // Clearing the console
    system("cls");
    Setup();
    while (!game_over) {
        Draw();
        Input();
        Logic();
        // Adding a delay to control the speed of the game (up to your preference)
        Sleep(100);   
    }

    return 0;
}
