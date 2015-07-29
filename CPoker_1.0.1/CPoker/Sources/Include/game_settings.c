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

void set_new_round_settings(uint8_t *computer_return_cards_index) {

  /** Function called at round end
   *  to set up the settings for playing a new round. */

  init_anim_cards(dist_settings, clean_settings) ;

  current_card = NULL ;

  if (game_control->distribute) {
    /** We invert the cards distributing, gving new cards and gathering cards order. **/
    game_control->distribute=false ;
    give_order=false ;
  }
  else {
    /** We invert the cards distributing, gving new cards and gathering cards order. **/
    game_control->distribute=true ;
    give_order=true ;
  }

  free(give_new_cards_player)   ;
  free(give_new_cards_computer) ;

  give_new_cards_player   = malloc(sizeof(Give_New_Cards_Animation)) ;
  give_new_cards_computer = malloc(sizeof(Give_New_Cards_Animation))  ;

  /** Mix the card game. **/
  mix_card() ;

  /** Give cards internally function (not the animation).  **/
  give_cards(game_control->card_game,game_control->player,game_control->computer,game_control->distribute) ;


  /** The computer check which cards he wants to throw before he knows which cards he have now. **/
  _Bool computer_cards_to_throw_index[5] ;
  /** computer_cards_to_throw_index is initialize in this functions. Used as buffer for to throw indexes **/
  set_cards_to_throw_computer(game_control->computer, computer_cards_to_throw_index) ;
  free(throw_cards) ;
  throw_cards=malloc(sizeof(Throw_Cards)) ;
  /** Configuring the throw_cards strcuture. **/
  set_throw_cards(throw_cards, computer_cards_to_throw_index) ;
  /***********************************************************************************************/


  memset(dragging_card,'\0',sizeof(Dragging)) ;


  game_control->GAME_STATUS       = GAME_START ;
  game_control->SAVED_GAME_STATUS = GAME_START ;

  bounding_boxes[0].is_frame_empty = false ;
  bounding_boxes[1].is_frame_empty = false ;
  bounding_boxes[2].is_frame_empty = false ;
  bounding_boxes[3].is_frame_empty = false ;
  bounding_boxes[4].is_frame_empty = false ;

  bounding_boxes[5].is_frame_empty = true ;  /** Throw card heap empty. **/


  buttons[5].is_allowed   = false ;  /** Set the last button on not allowed.                   **/
  buttons[0].is_allowed   = true  ;  /** Set the first button ("Distribute cards") as allowed. **/


  *computer_return_cards_index = 0 ;


  game_control->cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW) ;
  SDL_SetCursor(game_control->cursor_type)  ;
  game_control->is_animation_running = false ;

  return ;
}

void init_game_settings(SDL_Renderer *pRenderer) {

  /** Game initialisation function. **/

  init_game_control(pRenderer) ;  /** Set up game_control strcuture **/


  init_button_image(pRenderer) ;  /** Configuring buttons images. **/

  /** Setting up images management. **/
  main_images = malloc(sizeof(Main_Image)) ;
  init_main_images(main_images, pRenderer) ;


  configure_bounding_boxes() ;  /** Bounding boxes configuration for drag and drop from player's cards and mouse over marking **/

  /** Cards distributing animation settings structure. **/
  dist_settings  = malloc(sizeof(Anim_Cards)) ;
  clean_settings = malloc(sizeof(Anim_Cards)) ;

  /** Settings up data needed for cards distributing and gathering animation. **/
  init_anim_cards(dist_settings, clean_settings) ;


  dragging_card = malloc(sizeof(Dragging)) ;  /** Player card dragging structure initialisation. **/

  current_card  = malloc(sizeof(Card))     ;  /** Global variable Card structure for the player card returning animation. **/

  current_card  = NULL ;


  /** Computer throw cards animation settings structure. **/
  throw_cards = malloc(sizeof(Throw_Cards)) ; /** Global variable. **/

  /** Computing cards moving, animation coordinates, represent as Vectors objects. **/
  anim_cards_vectors = malloc(sizeof(Anim_Cards_Vectors)) ;
  init_cards_anim_vectors(anim_cards_vectors) ;



  /** Give new cards animation settings as throw cards like strcuture. **/
  give_new_cards_player   = malloc(sizeof(Give_New_Cards_Animation)) ;
  give_new_cards_computer = malloc(sizeof(Give_New_Cards_Animation)) ;

  return ;
}

void first_round_settings(SDL_Renderer *pRenderer) { 

  game_control->GAME_STATUS=GAME_START ;  /** Represent the curent game phase.
                                            * In relalationship to his value:
                                            * -) Some thing are displayed or not.
                                            * -) Some operations are performed.
                                            *************************************/

  game_control->SAVED_GAME_STATUS = GAME_START ;

  game_control->distribute=false ;       /** Represent the cards distribution order. **/

  game_control->mouse_over_card=false ;  /** To check if the cursor is over a card. **/

  game_control->player_score=0   ;       /** Player score.   **/
  game_control->computer_score=0 ;       /** Computer score. **/

  game_control->rounds_counter = 0 ;

  configure_score_text(pRenderer, &game_control->player_text,   0) ;
  configure_score_text(pRenderer, &game_control->computer_text, 0) ;

  current_card  = NULL ;

  init_anim_cards(dist_settings, clean_settings) ;

  /** Mix cards for the first time. **/
  mix_card() ;
  
  /** Distribute cards to set this in the player and computer hands. Implement as an array from objects from type Card  **/
  give_cards(game_control->card_game,game_control->player,game_control->computer,game_control->distribute) ;


  /** Settings to check what cards the computer will throw for the first round. **/
  _Bool computer_cards_to_throw_index[5] ; /** Cards of computer sorted indexes represent as boolean values array .  **/
  set_cards_to_throw_computer(game_control->computer, computer_cards_to_throw_index) ; /** computer_cards_to_throw_index is initialize in this functions. Used as buffer for to throw indexes **/              
  set_throw_cards(throw_cards, computer_cards_to_throw_index) ;
  /** End of settings what cards the computer will throw for the first round. **/     

  memset(dragging_card,'\0',sizeof(Dragging)) ;

  memset(give_new_cards_player,   '\0', sizeof(Give_New_Cards_Animation)) ;
  memset(give_new_cards_computer, '\0', sizeof(Give_New_Cards_Animation)) ;

  bounding_boxes[0].is_frame_empty = false ;
  bounding_boxes[1].is_frame_empty = false ;
  bounding_boxes[2].is_frame_empty = false ;
  bounding_boxes[3].is_frame_empty = false ;
  bounding_boxes[4].is_frame_empty = false ;

  bounding_boxes[5].is_frame_empty = true ;  /** Throw card heap empty. **/


  buttons[5].is_allowed   = false ;  /** Set the last button on not allowed.                   **/
  buttons[0].is_allowed   = true  ;  /** Set the first button ("Distribute cards") as allowed. **/

  game_control->cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW) ;
  SDL_SetCursor(game_control->cursor_type)  ;
  game_control->is_animation_running = false ;

  return ;
}



