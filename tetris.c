#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

static int highscore = 0;
static int current_menu = 0;
static int timeoutcount = 0;

void highscores(){
    clear_strings();
    display_string(0, "Highscore:");
    display_string(1, itoaconv(highscore));
    display_string(3, "BTN4: go back");
    display_update();
    
    while(current_menu == 2 || getbtns() == 2){
        if (getbtns() == 4){
            current_menu = 0;
        }
    }
}

void play(){
    clear_strings();
    display_update();

    
    while(current_menu == 1){
        clear_board();
        //draw_game_border();
        
        display_image();
        while(getbtns() == 0){}
    }
}

void start_menu(){
    while (getbtns() == 4){}

    clear_strings();
    display_string(0, "NotTetrisButVery");
    display_string(1, "SimilarToTetris");
    display_string(2, "-Game");
    display_string(3, "B4: Play, B3: HS");
    display_update();
    while(current_menu == 0){
        if (getbtns() == 4)
        {
            current_menu = 1;
        }
        if(getbtns() == 2)
        {
            current_menu = 2;
        }
    }
}

void game(){
    switch (current_menu)
    {
    case 0:
        start_menu();
        break;
    
    case 1:
        play();
        break;
    
    case 2:
        highscores();
        break;
    
    default:
        game();
    }
}