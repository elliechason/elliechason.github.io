/*
Name(s): Ellie Chason
Date: 5/31/21
Program Name: Survive
Program Description: User enters keys to travel across board while avoiding enemies
*/

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

const int spaces = 15;

//Acts as game board
struct survive {
  string board [15][15];
  int level;
  string name1; //refers to player 1's name
};

//parent class for user and enemy, contains their coordinates on the gameboard
class character {
    public:
    int x_coord, y_coord;
};

//User class contains how many lives left and what token the user has
class user : public character {
    public:
    int lives;
    string token;
    /*
    Summary: Constructor for user
    Reasoning: automatically places X token in middle of board
    Input: none
    Output: none
    */
    user(){
        x_coord = 7;
        y_coord = 7;
        lives = 3;
        token = "X";
    }
    /*
    Summary: Moves user token in chosen direction
    Reasoning: Print statement asks what direction, switch statement modifies coordinates
    Input: Direction
    Output: direction question
    */
 void moveUser() {
        int dir;
        do{
            cout << "Enter the number of the direction you'd like to move in.\n"
                << "1. UP\n2. DOWN\n3. LEFT\n4. RIGHT\n5. RANDOM TELEPORT (Warning: This could teleport to a spot occupied by an enemy.)\n";
            cin >> dir;
        
            switch(dir){
                case 1:
                    y_coord -= 1;
                    break;
                case 2:
                    y_coord += 1;
                    break;
                case 3:
                    x_coord -= 1;
                    break;
                case 4:
                    x_coord += 1;
                    break;
                case 5: 
                    x_coord = rand() % 14;
                    y_coord = rand() % 14;  
                    break;
                default:
                    cout << "\nThat is not an acceptable option. Please try again.\n";
            }
        }
        while(dir>5 || dir<1);
    }
};
//child class of character
class enemy : public character {
    public:
    string token;
    /*
    Summary: constructor sets O token at designated spot
    Reasoning: Takes in different x and y for different enemies
    Input: X and Y coordinate for specific enemy
    Output: none
    */
    enemy(int x, int y){
        x_coord = x;
        y_coord = y;
        token = "O";
    }
    /*
    Summary: Moves enemy token towards user coordinates
    Reasoning: Determines whether above, below, to left, or to right of user
    Input: X and Y coordinates of user
    Output: none
    */
    void moveEnemy(int x_p, int y_p){
        if (x_p > x_coord){
            x_coord +=1;
        }
        else if (x_p < x_coord){
            x_coord -=1;
        }
        else if (y_p > y_coord){
            y_coord +=1;
        }
        else if (y_p < y_coord){
            y_coord -=1;
        }

    }

};


/*
Summary: Runs the Survive game
Reasoning: Contains different levels and life checker
Input: the game object and the user object
Output: boolean variable indicating if game is ongoing
*/
bool play_game(survive * game, user * p1) {
    enemy e1(4, 2), e2(14, 12), e3(3, 6), e4(1, 14), e5(8, 11), e6(6, 5), e7(10, 9);

    for (int i=0; i<spaces; i++){ //row
        for (int j=0; j<spaces; j++){ //column
            if (j==p1->x_coord & i==p1->y_coord){
                game->board[i][j] = p1->token + "|";
            }
            else{
                game->board[i][j] = "_|";
            }
            //Using a switch statement without breaks allows the enemies from lower levels to be displayed as well
            switch(game->level){
                case 6:
                    if (j==e7.x_coord & i==e7.y_coord){
                        game->board[i][j] = e7.token + "|";
                    }
                case 5:
                    if (j==e6.x_coord & i==e6.y_coord){
                        game->board[i][j] = e6.token + "|";
                    }
                case 4:
                    if (j==e5.x_coord & i==e5.y_coord){
                        game->board[i][j] = e5.token + "|";
                    }
                case 3:
                    if (j==e4.x_coord & i==e4.y_coord){
                        game->board[i][j] = e4.token + "|";
                    }
                case 2:
                    if (j==e3.x_coord & i==e3.y_coord){
                        game->board[i][j] = e3.token + "|";
                    }
                case 1: 
                    if (j==e1.x_coord & i==e1.y_coord){
                        game->board[i][j] = e1.token + "|";
                    }
                    else if (j==e2.x_coord & i==e2.y_coord){
                        game->board[i][j] = e2.token + "|";
                    }
            }
            
            cout << game->board[i][j];
        }
        cout << "\n";

    }
    int moves;
    moves = 1;

    bool alive;
    alive = true; //alive while not out of lives


    while (alive) {
        if (moves>=80){
            cout << "\nCongratulations, you win!\n";
            return false;
        }
        //Checks if enemy has moved to same square as user
        if (game->board[p1->y_coord][p1->x_coord] == "O|"){
            p1->lives -=1; //one life is lost
            game->level = 1;
            alive = false;
            cout << "\nYou lose.\n";
            if (p1->lives > 0){
                cout << "Lives left: " << p1->lives << endl;
            }
            else{
                cout << "You are out of lives. Game over.\n";
                return false;
            }
            break;
        }
        //allows player to move 2 turns, third turn is enemy
        if (moves%3!=0){

            game->board[p1->y_coord][p1->x_coord] = "_|";
            p1->moveUser();
            
            game->board[p1->y_coord][p1->x_coord] = p1->token + "|";
            for (int i=0; i<spaces; i++){
                for (int j=0; j<spaces; j++){
                    cout << game->board[i][j];
                }
                cout << "\n";
            }
        }
        else{
            cout << "\nEnemy is moving...\n";
            //based on game level, different number of opponents appear
            switch(game->level){
                case 6:
                    game->board[e7.y_coord][e7.x_coord] = "_|";
                    e7.moveEnemy(p1->x_coord, p1->y_coord);
                    game->board[e7.y_coord][e7.x_coord] = e7.token + "|";
                case 5:
                    game->board[e6.y_coord][e6.x_coord] = "_|";
                    e6.moveEnemy(p1->x_coord, p1->y_coord);
                    game->board[e6.y_coord][e6.x_coord] = e6.token + "|";
                case 4:
                    game->board[e5.y_coord][e5.x_coord] = "_|";
                    e5.moveEnemy(p1->x_coord, p1->y_coord);
                    game->board[e5.y_coord][e5.x_coord] = e5.token + "|";
                case 3:
                    game->board[e4.y_coord][e4.x_coord] = "_|";
                    e4.moveEnemy(p1->x_coord, p1->y_coord);
                    game->board[e4.y_coord][e4.x_coord] = e4.token + "|";
                case 2:
                    game->board[e3.y_coord][e3.x_coord] = "_|";
                    e3.moveEnemy(p1->x_coord, p1->y_coord);
                    game->board[e3.y_coord][e3.x_coord] = e3.token + "|";
                case 1: 
                    game->board[e1.y_coord][e1.x_coord] = "_|";
                    game->board[e2.y_coord][e2.x_coord] = "_|";
                    e1.moveEnemy(p1->x_coord, p1->y_coord);
                    e2.moveEnemy(p1->x_coord, p1->y_coord);
                    game->board[e1.y_coord][e1.x_coord] = e1.token + "|";
                    game->board[e2.y_coord][e2.x_coord] = e2.token + "|";
            }
            //displays board
            for (int i=0; i<spaces; i++){
                for (int j=0; j<spaces; j++){
                    cout << game->board[i][j];
                }
                cout << "\n";
            }
        }
        //announces reaching new level and when new life is earned (every other level)
        switch(moves){
            case 5:
                game->level = 2;
                cout << "\nYou've reached Level 2!\n";
                break;
            case 10:
                game->level = 3;
                p1->lives ++;
                cout << "\nYou've reached Level 3 and earned a life!\n";
                break;
            case 17:
                game->level = 4;
                cout << "\nYou've reached Level 4!\n";
                break;
            case 30:
                game->level = 5;
                p1->lives ++;
                cout << "\nYou've reached Level 5 and earned a life!\n";
                break;
            case 50:
                game->level = 6;
                cout << "\nYou've reached Level 6, the final level! Stay alive for 30 more turns to win!\n";
                break;
            
            default:
                break;
        }
        moves++;
    }
    return true;
}

/*
Summary: runs home menu with options to read game instructions, play game, restart game, or quit
Reasoning: allows user to specify desired options and call appropriate functions
Input: none
Output: returns nothing and prints out option statements
*/
void menu() {
    int selectedOption;

    survive * game_obj; // pointer allows for dynamic memory (used in restart game option)
    game_obj = new survive;

    user * player1;
    player1 = new user;

    game_obj->name1 = "Player 1";

    do { //do while loop runs the menu until user quits. 
        cout << "\n\nWelcome to Survive! Enter the number corresponding to the option you'd like to select below:\n"
            << "1. Read Instructions\n"
            << "2. Play!\n"
            << "3. Quit\n";
        cin >> selectedOption;

        switch(selectedOption) {
            case 1: //run instructions
                cout << "INSTRUCTIONS\n------------\n"
                     << "Survive is played by moving your X token two spaces per turn. After your turn, enemy O tokens will move towards you. Once they reach your square, the game is over. Try and see how long you can survive!";
                break;
            case 2: //run game
                char name_ans;

                game_obj->level = 1;
                player1->lives = 3;

                cout << "Alright, let's get started!\n";

                //default name is Player 1
                cout << game_obj->name1 << ", would you like to rename yourself? Enter 'Y' for yes, 'N' for no.\n";
                cin >> name_ans;
                if (name_ans == 'Y'){
                    cin.ignore();
                    cout << "What is your new name?\n";
                    getline(cin, game_obj->name1);
                }

                bool activeGame;
                activeGame = true;
                while (activeGame) {
                    activeGame = play_game(game_obj, player1);
                    //resets player oordinates
                    player1->x_coord = 7;
                    player1->y_coord = 7;
                }
                break;
                
            case 3:
                cout << "Aw, leaving so soon? Maybe next time!\n";
                break;
            default:
                cout << "Hmm, I don't think that's a valid choice! Let's try again.";
        }
    }
    while (selectedOption != 3);
    delete game_obj;

}

int main() {
    menu();
}