/*
Name(s): Ellie Chason
Date: 4/16/21
Program Name: Connect Four
Program Description: Program simulates a Connect 4 board where either two users or one user and the computer compete against each other
*/

#include <iostream>
#include <string>

using namespace std;

struct connect_four {
  char board [6][7];
  int p1_wins; //refers to how many times player 1 has won
  int p2_wins; //refers to how many times player 2 has won
  string name1; //refers to player 1's name
  string name2; //refers to player 2's name
};

/*
Summary: Checks if a player has won
Reasoning: examines the board to see if there are four tokens adjacent to each other (either horizontally, vertically, or diagonally)
Input: A pointer to the current game struct and the player's number (1 or 2)
Output: returns the point earned by the player (1 if four in a row, 0 otherwise)
*/
int check_board(connect_four *gameCurrent, int playerNum){
    char mark;
    int point;
    //player 1's token is 'X', player 2's token is 'O'
    if (playerNum == 1){
        mark = 'X';
    }
    else{
        mark = 'O';
    }
    //vertically down check
    point = 0;
    for (int i=0; i<3; i++){ //row
        for (int j=0; j<7; j++){ //column
            if ((gameCurrent->board[i][j] == mark)&&(gameCurrent->board[i+1][j] == mark)&&(gameCurrent->board[i+2][j] == mark)&&(gameCurrent->board[i+3][j] == mark)){
               point++;
               break;
            }
        }
        if (point == 1){
            return point;
            break;
        }
    }
    //horizontally right check
    point = 0; //reassign so player cannot win multiple points
    for (int i=0; i<6; i++){ //row
        for (int j=0; j<4; j++){ //column
            if ((gameCurrent->board[i][j] == mark)&&(gameCurrent->board[i][j+1] == mark)&&(gameCurrent->board[i][j+2] == mark)&&(gameCurrent->board[i][j+3] == mark)){
               point++;
               break;
            }
        }
        if (point == 1){
            return point;
            break;
        }
    }
    //diagonally down-to-right check
    point = 0; //reassign so player cannot win multiple points
    for (int i=0; i<=2; i++){ //row
        for (int j=0; j<=3; j++){ //column
            if ((gameCurrent->board[i][j] == mark)&&(gameCurrent->board[i+1][j+1] == mark)&&(gameCurrent->board[i+2][j+2] == mark)&&(gameCurrent->board[i+3][j+3] == mark)){
               point++;
               break;
            }
        }
        if (point == 1){
            return point;
            break;
        }
    }
    //diagonally down-to-left check
    point = 0; //reassign so player cannot win multiple points
    for (int i=0; i<=2; i++){ //row
        for (int j=3; j<=6; j++){ //column
            if ((gameCurrent->board[i][j] == mark)&&(gameCurrent->board[i+1][j-1] == mark)&&(gameCurrent->board[i+2][j-2] == mark)&&(gameCurrent->board[i+3][j-3] == mark)){
               point++;
               break;
            }
        }
        if (point == 1){
            return point;
            break;
        }
    }

    return point;
}

/*
Summary: Acts as an opponent to player 1
Reasoning: looks for best spot to place token to win as soon as possible and prevent a win from player 1
Input: A pointer to the current game struct and the player's number (typically 'X')
Output: returns nothing (return statements are used as breaks) and adds AI player's mark
*/
void AI(connect_four * game, char mark){ //mark is token that player is using
    char ai_mark;
    ai_mark = 'O';

    //Win immediately
    for (int i=0; i<6; i++){ //row
        for (int j=0; j<7; j++){ //column
            if ((game->board[i][j] == ai_mark) && (game->board[i+1][j] == ai_mark) && (game->board[i+2][j] == ai_mark) && (game->board[i-1][j] == '_')){
                game->board[i-1][j] = ai_mark;
                return;
            }
            else if ((game->board[i][j] == ai_mark) && (game->board[i][j+1] == ai_mark) && (game->board[i][j+2] == ai_mark)){
                if (game->board[i][j-1] == '_'){
                    game->board[i][j-1] = ai_mark;
                    return;
                }
                else if (game->board[i][j+3] == '_'){
                    game->board[i][j+3] = ai_mark;
                    return;
                }
            }
        }
    }
    
    //Work to prevent player 1 win
    for (int i=0; i<6; i++){ //row
        for (int j=0; j<7; j++){ //column
            if (game->board[i][j] == mark){
                //checks if player 1 is close to vertical score. If so, AI places token to prevent
                if ((game->board[i+1][j] == mark) && (game->board[i+2][j] == mark) && (game->board[i-1][j] == '_')){
                    game->board[i-1][j] = ai_mark;
                    return;
                }
                //checks if player 1 has token that has no horizontally adjacent tokens
                else if ((game->board[i][j-1] == '_') && (game->board[i][j+1] == '_')){
                    int first_height, second_height;
                    //finds how "tall" (i.e. what is the smallest index with a token) column to left is
                    for(int check=0; check < 6; check++){
                        if (game->board[5-check][j-1] == '_'){
                            first_height = check; 
                            break;
                        }  
                    }
                    //finds how "tall" (i.e. what is the smallest index with a token) column to right is
                    for(int check=0; check < 6; check++){
                        if (game->board[5-check][j+1] == '_'){
                            second_height = check; 
                            break;
                        }  
                    }
                    //AI places token in "tallest" column
                    if (first_height < second_height){
                        game->board[5-second_height][j+1] = 'O';
                        return;
                    }
                    else{
                        game->board[5-first_height][j-1] = 'O';
                        return;
                    }

                }
                //checks if only horizontally adjacent spot available is to left
                else if ((game->board[i][j-1] == '_') && (game->board[i][j+1] != '_') && (game->board[i+1][j-1] != '_')){ 
                    //places token at available spot closest to bottom
                    for(int check=0; check < 6; check++){
                        if (game->board[5-check][j-1] == '_'){
                            game->board[5-check][j-1] = ai_mark; 
                            return;
                        }  
                    }
                }
                //checks if only horizontally adjacent spot available is to right
                else if ((game->board[i][j-1] != '_') && (game->board[i][j+1] == '_') && (game->board[i+1][j+1] != '_')){ 
                    //places token at available spot closest to bottom
                    for(int check=0; check < 6; check++){
                        if (game->board[5-check][j+1] == '_'){
                            game->board[5-check][j+1] = ai_mark; 
                            return;
                        }  
                    }
                }
                //AI token is placed at random available spot (note: not true random, more like arbitrary)
                else{
                    for(int rand_i =0; rand_i < 6; rand_i++){ //rand refers to random
                        for (int rand_j =0; rand_j < 7; rand_j++){
                            if (game->board[5-rand_i][rand_j] == '_'){
                                game->board[5-rand_i][rand_j] = ai_mark;
                                return;
                            } 
                        } 
                    }
                }      
                
            }
        }
    }
    
}

/*
Summary: runs the Conect 4 game procedure and keeps track of players' scores
Reasoning: uses connect_four struct board, check_board function, and AI function to allow one or two users to play and compare scores
Input: current Connect 4 game and mode ('H' for human v human, 'C' for computer (AI) v human)
Output: returns nothing and prints out current instructions, board status, and score board
*/
void play_game(connect_four * game, char mode) {
    //creates blank game board
    for (int i=0; i<6; i++){ //row
        for (int j=0; j<7; j++){ //column
            game->board[i][j] = '_';
        }
    }

    int player_num, game_score1, game_score2; //game_score1 and game_score2 refer to how many points each player earned during the current game only
    
    player_num = 1; //start with player 1
    game_score1 = 0;
    game_score2 = 0;

    while(player_num>=1){
        int column; //column that player 1 chooses
        
        //shows current board status
        cout << "\n1234567\n";
        for (int i=0; i<6; i++){
            for (int j=0; j<7; j++){
                cout << game->board[i][j];
            }
            cout << "\n";
        }
        //winning statements
        if (game_score1 > game_score2){
            cout << game->name1 << " wins!\n"; //congratulations
            break; //throws while loop
        }       
        else if (game_score2 > game_score1){
            cout << game->name2 << " wins!\n"; //congratulations
            break; //throws while loop
        }

        if ((mode == 'H') || (player_num == 1)){ 
            if (player_num == 1){ //means human's turn
                cout << game->name1
                    << ", which column would you like to drop the token down? Enter '1' for the first column on the left, '2' for the second column on the left, etc.\n";
                cin >> column;
            }
            else if (player_num == 2){//means computer's turn
                cout << game->name2
                    << ", which column would you like to drop the token down? Enter '1' for the first column on the left, '2' for the second column on the left, etc.\n";
                cin >> column;
            }

            for(int i=0; i < 6; i++){
                if (game->board[5-i][column-1] == '_'){
                    if (player_num == 1){
                        game->board[5-i][column-1] = 'X'; //player 1's mark
                    }
                    else{
                        game->board[5-i][column-1] = 'O';//player 2's mark
                    }
                    break;
                }
            }
        }
        else if ((mode == 'C') && (player_num == 2)){
            AI(game, 'X'); 
        }

        //adds point determined by check_board functio to appropriate player
        if (player_num == 1){
            game_score1 += check_board(game, player_num);
            game->p1_wins += game_score1;
            player_num = 2;
        }
        else{
            game_score2 += check_board(game, player_num);
            game->p2_wins += game_score2;
            player_num = 1; 
        }
    }
    //shows current scores
    cout << "Score\n-----\n";
    cout << game->name1 << ": " << game->p1_wins << endl;
    cout << game->name2 << ": " << game->p2_wins << endl;
}

/*
Summary: runs home menu with options to read game instructions, play game, restart game, or quit
Reasoning: allows user to specify desired options and call appropriate functions
Input: none
Output: returns nothing and prints out option statements
*/
void menu() {
    int selectedOption;
    connect_four * game_obj; // pointer allows for dynamic memory (used in restart game option)
    game_obj = new connect_four;
    game_obj->p1_wins = 0;
    game_obj->p2_wins = 0;
    game_obj->name1 = "Player 1";
    game_obj->name2 = "Player 2";
    do { //do while loop runs the menu until user quits. 
        cout << "\n\nWelcome to Connect Four! Enter the number corresponding to the option you'd like to select below:\n"
            << "1. Read Instructions\n"
            << "2. Play!\n"
            << "3. Restart game\n"
            << "4. Quit\n";
        cin >> selectedOption;

        switch(selectedOption) {
            case 1: //run instructions
                cout << "INSTRUCTIONS\n------------\n"
                     << "Connect Four is played by entering which column you'd like to 'drop' your token down. "
                     << "The token will then reside at the lowest empty slot on the board. "
                     << "The goal of the game is to be the first player to place 4 tokens next to each other, either vertically, horizontally, or diagonally.";
                break;
            case 2: //run game
                char mode_ans, name_ans;
                cout << "This is a two-player game. Are both players present, or would you like to play against the computer? "
                     << "Enter 'H' if you have a human opponent, 'C' if you wish to compete with the computer.\n";
                cin >> mode_ans;
                cout << "Alright, let's get started!\n";

                //default name is Player 1 or Player 2
                cout << game_obj->name1 << ", would you like to rename yourself? Enter 'Y' for yes, 'N' for no.\n";
                cin >> name_ans;
                if (name_ans == 'Y'){
                    cin.ignore();
                    cout << "What is your new name?\n";
                    getline(cin, game_obj->name1);
                }

                if (mode_ans == 'H'){
                    cout << game_obj->name2 << ", would you like to rename yourself? Enter 'Y' for yes, 'N' for no.\n";
                    cin >> name_ans;
                    if (name_ans == 'Y'){
                        cin.ignore();
                        cout << "What is your new name?\n";
                        getline(cin, game_obj->name2);
                    }
                }  
                play_game(game_obj, mode_ans);
                break;
                
            
            case 3:
                cout << "The current game's progress will be restarted.\n";
                delete game_obj;
                game_obj = new connect_four;
                //re-initializes
                game_obj->p1_wins = 0;
                game_obj->p2_wins = 0;
                game_obj->name1 = "Player 1";
                game_obj->name2 = "Player 2";
                break;
            case 4:
                cout << "Aw, leaving so soon? Maybe next time!\n";
                break;
            default:
                cout << "Hmm, I don't think that's a valid choice! Let's try again.";
        }
    }
    while (selectedOption != 4);
    delete game_obj;

}

int main() {
    menu();
}