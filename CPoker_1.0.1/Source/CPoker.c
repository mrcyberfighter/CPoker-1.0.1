/** **************************************************************************************
 * CPocker an poker game against the computer.                                           *                                      
 * Copyright (©) 2015 Brüggemann Eddie (contact <mrcyberfighter@gmail.com>).             *
 *                                                                                       *
 * This file is part of CPocker.                                                         *
 * CPocker is free software: you can redistribute it and/or modify                       *
 * it under the terms of the GNU General Public License as published by                  *
 * the Free Software Foundation, either version 3 of the License, or                     *
 * (at your option) any later version.                                                   *
 *                                                                                       *
 * CPocker is distributed in the hope that it will be useful,                            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                          *
 * GNU General Public License for more details.                                          *
 *                                                                                       *
 * You should have received a copy of the GNU General Public License                     *
 * along with CPocker. If not, see <http://www.gnu.org/licenses/>                        *
 *****************************************************************************************/

/**
 *  CPocker: an poker game against the computer using the SDL2 (Simple Direct media Link ) library.
 *  To compil with linking of the SDL2 library and the math library:
 *
 *  $ gcc CPocker.c -lSDL2 -lm -lSDL2_image -lSDL2_ttf
 *
 * ************************************************************************************************/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <sys/time.h>
#include <unistd.h>

_Bool loop ;

_Bool give_order ;

_Bool quit_game ;

/** Game status enumeration: this are the differents states of the game.                                        **/
enum { GAME_START,           /** Game state at round start.                                                     **/
       CARDS_DISTRIBUTE,     /** Game state after cards distributioon.                                          **/
       CARDS_COVER,          /** Game state all cards not returned.                                             **/
       CARDS_DISCOVER,       /** Game state by playing                                                          **/
       RETURN_A_CARD,        /** Game state by player return a card.                                            **/
       DRAG_CARD_ON,         /** Game state by player dragging a card.                                          **/
       DRAG_CARD_OFF,        /** Game state by player drop a card.                                              **/
       THROW_CARDS,          /** Game state before computer throw his cards.                                    **/
       CARDS_THROW,          /** Game state after computer has throw his cards.                                 **/
       GIVE_NEW_CARDS,       /** Game state before giving new cards.                                            **/
       NEW_CARDS_GIVEN,      /** Game state after new cards has been given.                                     **/
       COMPUTER_SHOW_CARDS,  /** Game state by computer return his cards animation.                             **/
       ROUND_DONE,           /** Game state by round end before displaying the round winner and score updating. **/
       DISPLAY_WINNER,       /** Game state by display round winner animation.                                  **/
       UPDATE_SCORE,         /** Game state by updating score.                                                  **/
       CLEAN_PLAYGROUND,     /** Game state by gathering cards animation.                                       **/
       PLAYGROUND_CLEAN,     /** Game state after gathering cards, and setting up a new round.                  **/
       GAME_END              /** Game state that all rounds have been played.                                   **/
     } ;

 
/** Cards combinations enumeration: this represent the poker cards combination.    **/ 
enum
{  
       HIGHEST_CARD, /** No combination.                                           **/
       PAIR,         /** Two same cards.                                           **/
       TWO_PAIRS,    /** two times two same cards.                                 **/
       BRELAN,       /** Three same cards                                          **/
       QUINTE,       /** suite of the cards without AS.                            **/
       COLOR,        /** five cards from same color.                               **/   
       FULL_HOUSE,   /** An brelan and an pair.                                    **/
       FOUR,         /** Four same cards.                                          **/
       QUINTE_FLUSH, /** Suite of the cards from the same color.                   **/
       ROYAL_FLUSH   /** Suite of the cards from the same color ending with an AS. **/

} ;

#define set_loop(x) loop=x ;


/******* Game constante definition ******/
#include "./Include/game_constante.c"   //
/***************************************/


/****** Data structures defintion: ********/
#include "./Include/Headers/datatypes.h"  //
/*****************************************/


/******* Vector utlities: *******/
#include "./Include/vector.c"   //
/*******************************/


/****** Game structure definition: ******/
#include "./Include/game_structure.c"   //
/***************************************/
  

/************ Display functions: **************/
#include "./Include/images_utils.c"           //
#include "./Include/displaying_utils.c"       //
/*********************************************/


/** Cards manipluation specific functions: **/
#include "./Include/Headers/cards.h"        //
/*******************************************/


/********** Buttons utilities **********/
#include "./Include/buttons_utils.c"   //
/**************************************/


/***** Text displaying utlities *****/
#include "./Include/text_utils.c"   //
/***********************************/


/****** Drag-n-Drop utilities: **********/
#include "./Include/drag_and_drop.c"    //
/***************************************/


/**** Game animations utlities functions: ****/
#include "./Include/Headers/animations.h"    //
/********************************************/


/******** Game initialisation functions: *****/
#include "./Include/initialisation_utils.c"  //
/********************************************/


/******* SDL2 library specific functions. *******/
#include "./Include/Headers/SDL2_functions.h"   //
/***********************************************/


/******* Game settings functions: *******/
#include "./Include/game_settings.c"    //
/***************************************/


void display_start_screen(SDL_Window *pWindow, SDL_Renderer *pRenderer, uint8_t *number_of_rounds) ;

void game_mainloop(SDL_Window *pWindow, SDL_Renderer *pRenderer,uint8_t *number_of_rounds) ;

int main(int argc, char *argv[]) {

  SDL_Init(SDL_INIT_VIDEO) ;

  /** initialize the SDL_image library. **/
  if (IMG_Init(IMG_INIT_PNG) == 0) {
    /** Display an error message and quit the programme in case of error. **/
    char *message=calloc(256,sizeof(char)) ;
    sprintf(message,"Cannot initialise SDL2 Image library !\n%s",SDL_GetError()) ;
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Internal Error", message ,NULL) ;
    free(message) ;
    exit(EXIT_FAILURE) ;
  }

  /** initialize the SDL_ttf library. **/
  if (TTF_Init() != 0) {
    /** Display an error message and quit the programme in case of error. **/
    char *message=calloc(256,sizeof(char)) ;
    sprintf(message,"SDL ttf library initialisation error (%s)\n",SDL_GetError()) ;
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Internal Error", message ,NULL) ;
    free(message) ;
    exit(EXIT_FAILURE) ;
  }

  /** Windows creation  **/
  SDL_Window* pWindow = NULL;
  pWindow = sdl_create_window("CPocker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800 + 200 + 20 , 618, SDL_WINDOW_SHOWN) ;

  if (pWindow == NULL) {
    /** Display an error message and quit the programme in case of error. **/
    char *message=calloc(256,sizeof(char)) ;
    sprintf(message,"Cannot create window !\n%s",SDL_GetError()) ;
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Internal Error", message ,NULL) ;
    free(message) ;
    exit(EXIT_FAILURE) ;
  }

  /** Main Renderer creation **/
  SDL_Renderer *pRenderer  ;
  if ((pRenderer = sdl_create_renderer(pWindow,-1,SDL_RENDERER_ACCELERATED)) == NULL) {
    /** Display an error message and quit the programme in case of error. **/
    char *message=calloc(256,sizeof(char)) ;
    sprintf(message,"Cannot create renderer !\n%s",SDL_GetError()) ;
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Internal Error", message ,NULL) ;
    free(message) ;
    exit(EXIT_FAILURE) ;
  }

  /** Creation of an window icon **/
  SDL_Surface *tiny_icon_surface = IMG_Load(PATH_TO_ICON) ;

  SDL_SetWindowIcon(pWindow, tiny_icon_surface) ;

  SDL_FreeSurface(tiny_icon_surface);

  uint8_t number_of_rounds = 20 ; /** Number of rounds to play in a game: 20 per default **/

  /** Data for game presentation screen. **/

  quit_game=false ;

  /** Initialize the settings for all the game **/
  init_game_settings(pRenderer) ;

  main_screen:  /** Return to main screen from the game. **/


  /************* Main screen displaying function *************/
  display_start_screen(pWindow, pRenderer, &number_of_rounds) ;


  if (quit_game) {
    /** Case the user want ot quit the programme. **/
    clean_up(pRenderer,pWindow) ;

    IMG_Quit() ;
    TTF_Quit() ;
    SDL_Quit() ;

    exit(EXIT_SUCCESS) ;

  }


  /************* Game mainloop function. *************/
  game_mainloop(pWindow, pRenderer,&number_of_rounds) ;


  if (quit_game) {
    /** Case the user want ot quit the programme. **/
    clean_up(pRenderer,pWindow) ;

    IMG_Quit() ;
    TTF_Quit() ;
    SDL_Quit() ;

    exit(EXIT_SUCCESS) ;

  }

  goto main_screen ;  /** Return to main screen from the game. **/

  exit(EXIT_SUCCESS) ; /** Never reach. **/

}

void display_start_screen(SDL_Window *pWindow, SDL_Renderer *pRenderer, uint8_t *number_of_rounds) {

  /************* Main screen displaying function *************/

  /********************************* Load the needed images textures for the main screen animation.  ******************************/
  SDL_Texture *main_screen_image_1_texture = get_texture_from_image(pRenderer, PATH_TO_MAIN_IMAGES"CPocker_main_screen_heart.png") ;
  SDL_Texture *main_screen_image_2_texture = get_texture_from_image(pRenderer, PATH_TO_MAIN_IMAGES"CPocker_main_screen_pick.png")  ;
  SDL_Texture *main_screen_image_3_texture = get_texture_from_image(pRenderer, PATH_TO_MAIN_IMAGES"CPocker_main_screen_carot.png") ;
  SDL_Texture *main_screen_image_4_texture = get_texture_from_image(pRenderer, PATH_TO_MAIN_IMAGES"CPocker_main_screen_clubs.png") ;

  SDL_Texture *image_to_display_texture    = main_screen_image_1_texture ;

  /** Text "Press Enter" invitation settings **/
  Text press_enter_text ;

  press_enter_text.font = TTF_OpenFont(PATH_TO_FONT, 32) ;

  press_enter_text.text = "Press ENTER to start game !!!" ;

  configure_press_enter_text(pRenderer, &press_enter_text,100) ;


  /** Text for number of rounds configuration. **/
  Text number_of_rounds_text ;

  number_of_rounds_text.font = TTF_OpenFont(PATH_TO_FONT, 28) ;

  number_of_rounds_text.text_color.r =  23+128 ;
  number_of_rounds_text.text_color.g = 123+128 ;
  number_of_rounds_text.text_color.b =  23+128 ;
  number_of_rounds_text.text_color.a =     255 ;

  configure_rounds_text(pRenderer, &number_of_rounds_text, *number_of_rounds) ;



  set_loop(true)    ;  /** Setting mainloop boolean value on true.    **/

  int sleep=10000   ;  /** Configure mainloop pausing time.           **/

  int img_counter=0 ;  /** Counter variable needed for the animation. **/

  while (loop) {

    if (img_counter == 25) {
      image_to_display_texture=main_screen_image_2_texture ;
      configure_press_enter_text(pRenderer, &press_enter_text,img_counter) ;
    }
    else if (img_counter == 50) {
      image_to_display_texture=main_screen_image_3_texture ;
      configure_press_enter_text(pRenderer, &press_enter_text,img_counter) ;
    }
    else if (img_counter == 75) {
      image_to_display_texture=main_screen_image_4_texture ;
      configure_press_enter_text(pRenderer, &press_enter_text,img_counter) ;
    }
    else if  (img_counter == 100) {
      image_to_display_texture=main_screen_image_1_texture ;
      configure_press_enter_text(pRenderer, &press_enter_text,img_counter) ;
      img_counter = 0 ;
    }

    clear(pRenderer,63,63,63,255) ;

    display_image(pRenderer, image_to_display_texture, 0, 0, 1020, 618) ;

    render_text(pRenderer, &press_enter_text) ;

    render_text(pRenderer, &number_of_rounds_text) ;

    SDL_Event event;

    while (SDL_PollEvent(&event)) { /** Get user actions. **/
  
      switch(event.type) {

        case SDL_QUIT: /** User want to quit. **/
      
          quit_game=true ;
          set_loop(false) ;
      
          break;
      
        case SDL_KEYDOWN :
      
          if (event.key.keysym.scancode == SDL_SCANCODE_UP || event.key.keysym.scancode == SDL_SCANCODE_KP_8) {
            /** User press ARROW UP. **/
        
            if (*number_of_rounds < 99) {
              (*number_of_rounds)++ ;
              configure_rounds_text(pRenderer, &number_of_rounds_text, *number_of_rounds) ;
              break ;
            }
          }
      
          else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN || event.key.keysym.scancode == SDL_SCANCODE_KP_2) {
            /** User press ARROW DOWN. **/
        
            if (*number_of_rounds > 1) {
              (*number_of_rounds)-- ;
              configure_rounds_text(pRenderer, &number_of_rounds_text, *number_of_rounds) ;
              break ;
            }
          }
      
          /** User press Return **/
          else if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
            set_loop(false) ;
            break ;
          }
      }
    }

    display(pRenderer) ;
  
    update(pWindow) ;

    usleep(sleep) ;

    img_counter++ ;

  }

  return ;
}

void game_mainloop(SDL_Window *pWindow, SDL_Renderer *pRenderer,uint8_t *number_of_rounds) {




  game_control->number_of_rounds = *number_of_rounds ;

  /** Initalize the settings for the first round. **/
  first_round_settings(pRenderer) ;



  give_order = game_control->distribute ;  /** Order which get new cards first. **/

  int sleep=10000   ;  /** Configure pausing time. **/

  int16_t counter=0 ;  /** Return a card animation counter. **/

  int16_t mouse_x=0 ;  /** We keep this informations continually along the mainloop. **/
  int16_t mouse_y=0 ;  /** We keep this informations continually along the mainloop. **/

  uint8_t computer_return_cards_index = 0 ;


  set_loop(true) ;     /** Setting mainloop boolean value on true. **/

  /** Mainloop **/
  while (loop) {

    clear(pRenderer,63,63,63,255) ;  

    display_image(pRenderer, main_images->background_playground, SCREEN_WIDTH_OFFSET, TOP_BAR_SIZE, 800, 600) ;  /** Always displayed. **/

    display_image(pRenderer, main_images->bg_playground_border,  SCREEN_WIDTH_OFFSET, TOP_BAR_SIZE, 800, 600) ;  /** Always displayed. **/

    display_player_cards_frames(pRenderer,   main_images->player_cards_frame_texture)   ;  /** Always displayed. **/
    display_computer_cards_frames(pRenderer, main_images->computer_cards_frame_texture) ;  /** Always displayed. **/



    display_image(pRenderer, main_images->cards_heap_frame_texture,  FRAME_X_LEFT_POS                     , FRAME_Y_MIDDLE_POS                    , FRAME_WIDTH, FRAME_HEIGHT) ;  /** Always displayed. **/

    if ( game_control->GAME_STATUS != GAME_END ) {
      display_image(pRenderer, main_images->card_back_face_texture,  FRAME_X_LEFT_POS + FRAME_CARD_OFFSET , FRAME_Y_MIDDLE_POS + FRAME_CARD_OFFSET, CARD_WIDTH,  CARD_HEIGHT)  ; /** Always displayed Except at game end. **/
    }

    display_image(pRenderer, main_images->throw_cards_frame_texture, FRAME_X_RIGHT_POS                    , FRAME_Y_MIDDLE_POS                    , FRAME_WIDTH, FRAME_HEIGHT) ;  /** Always displayed. **/

    display_image(pRenderer, buttons[0].button_current_image,   6                            , 0                ,                    BUTTON_WIDTH, BUTTON_HEIGHT) ;  /** Always displayed. **/
    display_image(pRenderer, buttons[1].button_current_image,   6                            , 100-((11*1)/1)   ,                    BUTTON_WIDTH, BUTTON_HEIGHT) ;  /** Always displayed. **/
    display_image(pRenderer, buttons[2].button_current_image,   6                            , 200-((11*2)/1)   ,                    BUTTON_WIDTH, BUTTON_HEIGHT) ;  /** Always displayed. **/
    display_image(pRenderer, buttons[3].button_current_image,   6                            , 300-((11*3)/1)   ,                    BUTTON_WIDTH, BUTTON_HEIGHT) ;  /** Always displayed. **/
    display_image(pRenderer, buttons[4].button_current_image,   6                            , 400-((11*4)/1)   ,                    BUTTON_WIDTH, BUTTON_HEIGHT) ;  /** Always displayed. **/
    display_image(pRenderer, buttons[5].button_current_image,   6                            , 500-((11*5)/1)   ,                    BUTTON_WIDTH, BUTTON_HEIGHT) ;  /** Always displayed. **/

    display_image(pRenderer, main_images->score_field       ,   9                            , (500-((11*5)/1)+100),  191 , 64) ;  /** Always displayed. **/

    render_text(pRenderer, &game_control->player_text)   ;  /** Always displayed. **/
    render_text(pRenderer, &game_control->computer_text) ;  /** Always displayed. **/


    
    if (game_control->GAME_STATUS == RETURN_A_CARD) {
      return_a_card(pRenderer, main_images->card_back_face_texture, &sleep, &counter) ;  /** Always displayed Except at game end. **/
    }

    if (game_control->GAME_STATUS == DRAG_CARD_OFF) {
      /** Release mouse key by dragging a card. **/
  
      int8_t ret ;
  
      if ( (ret=compute_drop_card(mouse_x, mouse_y)) ) {
        /** Case the dragged card is an frame. **/
        if (ret == 6 && game_control->SAVED_GAME_STATUS < CARDS_THROW) {
          /** Case the dragged card is over the throw card frame. **/
          throw_a_card(game_control->throw_cards_stack, dragging_card->card)        ;
          remove_a_card_from_hand(game_control->player, dragging_card->card->index,true) ;
        }
        else if (ret >= 1 && ret <= 5) {
          /** Case the dragged card is over an player's frame. **/
          if ( ! bounding_boxes[ret-1].is_frame_empty) {
            /** Case there an card in the frame. **/
            exchange_card(game_control->player,game_control->player[dragging_card->card->index], game_control->player[ret-1]) ;
          }
          else {
            /** Case the frame is empty. **/
            insert_card_in_an_empty_frame(game_control->player,game_control->player[dragging_card->card->index],ret-1) ;
          }
          //show_cards_from_player(game_control->player) ;
        }
      }
  
      /** Reset the settings. **/
      dragging_card->card->is_moving=false     ;
      game_control->GAME_STATUS=CARDS_DISCOVER ;
    }

    if ( game_control->GAME_STATUS != GAME_END ) {
      display_throw_cards(pRenderer, main_images->card_back_face_texture) ;  /** Always displayed Except at game end. **/
    }
  

    if (! (game_control->GAME_STATUS == CARDS_DISTRIBUTE) && ! (game_control->GAME_STATUS == CARDS_COVER) && ! (game_control->GAME_STATUS == GAME_START) && ! (game_control->GAME_STATUS == PLAYGROUND_CLEAN) && ! (game_control->GAME_STATUS == GAME_END) ) {
      /** Display cards from player and user. **/
      display_cards_from_player(pRenderer, main_images->card_back_face_texture,game_control->player) ;
      display_cards_from_computer(pRenderer, main_images->card_back_face_texture,game_control->computer) ;
  
    }

    if (game_control->GAME_STATUS == THROW_CARDS) {
      /** Computer throw cards animation. **/
      computer_throw_cards_animation(pRenderer, main_images->card_back_face_texture, anim_cards_vectors->computer_throw_cards, throw_cards, &sleep) ;
    }

    if (game_control->GAME_STATUS == DRAG_CARD_ON) {
      /** Mouse moving by user dragging a card. **/
      drag_and_drop_card(pRenderer,mouse_x,mouse_y) ;
    }



    if ((game_control->GAME_STATUS == CARDS_DISTRIBUTE) || (game_control->GAME_STATUS == CARDS_COVER)) {
      if (! game_control->distribute) {
        /** Distributing cards animation: player first served.   **/
        distribute_cards(pRenderer, main_images->card_back_face_texture, anim_cards_vectors->distribute_cards_1, dist_settings, &sleep, game_control->distribute) ;
      }
      else {
        /** Distributing cards animation: computer first served. **/
        distribute_cards(pRenderer, main_images->card_back_face_texture, anim_cards_vectors->distribute_cards_2, dist_settings, &sleep, game_control->distribute) ;
      }

    }

    if (game_control->GAME_STATUS == GIVE_NEW_CARDS) {
  
      if (! give_order) {
        /** Give new cards animation: player first served.   **/
        give_new_cards_animation(pRenderer, main_images->card_back_face_texture, anim_cards_vectors->player_new_cards, give_new_cards_player,     &sleep) ;
      }
      else {
        /** Give new cards animation: computer first served. **/
        give_new_cards_animation(pRenderer, main_images->card_back_face_texture, anim_cards_vectors->computer_new_cards, give_new_cards_computer, &sleep) ;
      }
    }

    if (game_control->GAME_STATUS == COMPUTER_SHOW_CARDS) {
      /** Computer show his cards animation. **/
      if (computer_return_cards_index == 0) {
        current_card=&game_control->computer[computer_return_cards_index] ;
      }
  
      if (computer_return_cards_index < 5) {
        return_cards_computer_hand(pRenderer, main_images->card_back_face_texture, &sleep, &counter, &computer_return_cards_index) ;
      }
    }

    if (game_control->GAME_STATUS == DISPLAY_WINNER) {
      /** Display round result text animation. **/
      display_result_text(pRenderer, &game_control->result_text, &sleep, &counter)  ;
    }

    if (game_control->GAME_STATUS == UPDATE_SCORE) {
      /** Internally score updating. **/
      update_score_displaying(pRenderer, &game_control->player_text, &game_control->computer_text) ;
    }

    if (game_control->GAME_STATUS == GAME_END) {
      /** Display game result text animation. **/
      display_game_winner_text(pRenderer, &game_control->winner_text, &game_control->press_escape, &sleep, &counter) ;
    }

    if (game_control->GAME_STATUS == CLEAN_PLAYGROUND) {
      /** Gather all cards at round end animation. **/
      if (! game_control->distribute) {
        /** Case player was served first.   **/
        gathering_cards_animation(pRenderer, main_images->card_back_face_texture, anim_cards_vectors->clean_cards_1, clean_settings, &sleep,game_control->distribute) ;
      }
      else {
        /** Case computer was served first. **/
        gathering_cards_animation(pRenderer, main_images->card_back_face_texture, anim_cards_vectors->clean_cards_2, clean_settings, &sleep,game_control->distribute) ;
      }
    }

    if (game_control->GAME_STATUS == PLAYGROUND_CLEAN) {
      /** Internally cards gathering and reset settings for a new round. **/
      gather_cards(game_control->throw_cards_stack,game_control->player,game_control->computer,game_control->distribute) ;
      set_new_round_settings(&computer_return_cards_index) ;
    }

    display(pRenderer) ;
  
    update(pWindow) ;

    get_events(&mouse_x,&mouse_y) ;

    usleep(sleep) ;
  
  }

  return ;

}


