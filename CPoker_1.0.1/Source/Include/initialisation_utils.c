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

void init_game_control(SDL_Renderer *pRenderer) {
  /** initialize the game control structure. **/

  game_control=malloc(sizeof(Game)) ;


  game_control->card_game=malloc(sizeof(Stack)) ;
  init_stack(game_control->card_game,NULL)      ;  /** initialize the card game container which hold all the cards from the game implement as an stack structure. **/


  /** Generate card game. **/
  if (! generate_card_game(game_control->card_game,"Heart",pRenderer) ) {
    const char *message="Fail to Generate card game !" ;
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game error", message ,NULL) ;
    exit(EXIT_FAILURE) ;
  }

  if (! generate_card_game(game_control->card_game,"Carot",pRenderer) ) {
    const char *message="Fail to Generate card game !" ;
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game error", message ,NULL) ;
    exit(EXIT_FAILURE) ;
  }

  if (! generate_card_game(game_control->card_game,"Pick",pRenderer) ) {
    const char *message="Fail to Generate card game !" ;
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game error", message ,NULL) ;
    exit(EXIT_FAILURE) ;
  }

  if (! generate_card_game(game_control->card_game,"Shamrock",pRenderer) ) {
    const char *message="Fail to Generate card game !" ;
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game error", message ,NULL) ;
    exit(EXIT_FAILURE) ;
  }
  /** Now we get an entire card game ordered as an stack. **/


  game_control->GAME_STATUS=GAME_START ;  /** Represent the curent game phase.
                                            * In relalationship to his value:
                                            * -) Some thing are displayed or not.
                                            * -) Some operations are performed.
                                            *************************************/

  game_control->distribute=false ;       /** Represent the cards distribution order. **/

  game_control->mouse_over_card=false ;  /** To check if the cursor is over a card. **/

  game_control->player_score=0   ;       /** Player score.   **/
  game_control->computer_score=0 ;       /** Computer score. **/


  /** We initalise the text settings which will be display. **/

  game_control->player_text.font   = TTF_OpenFont(PATH_TO_FONT, 20) ;  /** Font setting.  **/

  game_control->player_text.x =  26 ;         /** Player score displaying coordinates.    **/
  game_control->player_text.y = 578 ;         /** Player score displaying coordinates.    **/

  game_control->player_text.text="Player" ;

  game_control->player_text.text_color.r = 255 ;  /** Player score displaying text color. **/
  game_control->player_text.text_color.g = 255 ;  /** Player score displaying text color. **/
  game_control->player_text.text_color.b =   0 ;  /** Player score displaying text color. **/
  game_control->player_text.text_color.a = 255 ;  /** Player score displaying text color. **/

  game_control->computer_text.font = TTF_OpenFont(PATH_TO_FONT, 20) ;  /** Font setting.  **/

  game_control->computer_text.x =  26 ;  /** Computer score displaying coordinates.    **/
  game_control->computer_text.y = 556 ;  /** Computer score displaying coordinates.    **/

  game_control->computer_text.text="Computer" ;

  game_control->computer_text.text_color.r = 255 ;  /** Computer score displaying text color. **/
  game_control->computer_text.text_color.g = 128 ;  /** Computer score displaying text color. **/
  game_control->computer_text.text_color.b =  0  ;  /** Computer score displaying text color. **/
  game_control->computer_text.text_color.a = 255 ;  /** Computer score displaying text color. **/

  configure_score_text(pRenderer, &game_control->player_text,   0) ;
  configure_score_text(pRenderer, &game_control->computer_text, 0) ;

  game_control->winner_text.font  = TTF_OpenFont(PATH_TO_FONT, 50) ;

  game_control->press_escape.font = TTF_OpenFont(PATH_TO_FONT, 28) ;


  game_control->result_text.font = TTF_OpenFont(PATH_TO_FONT, 32) ;

  game_control->rounds_counter = 0 ;

  game_control->throw_cards_stack = malloc(sizeof(Stack)) ; /** initialize the throw cards stack. **/
  init_stack(game_control->throw_cards_stack, NULL) ;


  return ;
}

void init_anim_cards(Anim_Cards *dist_settings, Anim_Cards *clean_settings) {

  /** Initalisation of the cards distribution at round start animation control strcuture settings.  **/
  /** Initalisation of the cards gathering at round end animation control strcuture settings.       **/

  dist_settings->card = 0          ;
  dist_settings->step = 0          ;
  dist_settings->cards_number = 0  ;
  dist_settings->pos_to_fill  = 0  ;

  clean_settings->card = 0         ;
  clean_settings->step = 0         ;
  clean_settings->cards_number = 0 ;
  clean_settings->pos_to_fill  = 0 ;

  return ;
}

void init_button_image(SDL_Renderer *pRenderer) {

  /** Initialisation of the buttons images. **/

  SDL_Texture *button_distribute_cards      = get_texture_from_image(pRenderer,PATH_TO_BUTTONS"distribute_cards_button_image.png") ;

  SDL_Texture *button_computer_play         = get_texture_from_image(pRenderer,PATH_TO_BUTTONS"computer_play_button_image.png") ;

  SDL_Texture *button_give_new_card         = get_texture_from_image(pRenderer,PATH_TO_BUTTONS"give_new_cards_button_image.png") ;

  SDL_Texture *button_show_cards            = get_texture_from_image(pRenderer,PATH_TO_BUTTONS"show_cards_button_image.png") ;

  SDL_Texture *button_update_score          = get_texture_from_image(pRenderer,PATH_TO_BUTTONS"update_score_image.png") ;

  SDL_Texture *button_new_round             = get_texture_from_image(pRenderer,PATH_TO_BUTTONS"new_round_button_image.png") ;



  SDL_Texture *button_distribute_cards_mouseover      = get_texture_from_image(pRenderer,PATH_TO_BUTTONS"distribute_cards_button_image_mouseover.png") ;

  SDL_Texture *button_computer_play_mouseover         = get_texture_from_image(pRenderer,PATH_TO_BUTTONS"computer_play_button_image_mouseover.png") ;

  SDL_Texture *button_give_new_card_mouseover         = get_texture_from_image(pRenderer,PATH_TO_BUTTONS"give_new_cards_button_image_mouseover.png") ;

  SDL_Texture *button_show_cards_mouseover            = get_texture_from_image(pRenderer,PATH_TO_BUTTONS"show_cards_button_image_mouseover.png") ;

  SDL_Texture *button_update_score_mouseover          = get_texture_from_image(pRenderer,PATH_TO_BUTTONS"update_score_image_mouseover.png") ;

  SDL_Texture *button_new_round_mouseover             = get_texture_from_image(pRenderer,PATH_TO_BUTTONS"new_round_button_image_mouseover.png") ;


  initialise_button(0, button_distribute_cards,  button_distribute_cards_mouseover) ;  /** Function to find at \file ./Utilities/buttons_utils.c **/

  initialise_button(1, button_computer_play,     button_computer_play_mouseover)    ;  /** Function to find at \file ./Utilities/buttons_utils.c **/

  initialise_button(2, button_give_new_card,     button_give_new_card_mouseover)    ;  /** Function to find at \file ./Utilities/buttons_utils.c **/

  initialise_button(3, button_show_cards,        button_show_cards_mouseover)       ;  /** Function to find at \file ./Utilities/buttons_utils.c **/

  initialise_button(4, button_update_score,      button_update_score_mouseover)     ;  /** Function to find at \file ./Utilities/buttons_utils.c **/

  initialise_button(5, button_new_round,         button_new_round_mouseover)        ;  /** Function to find at \file ./Utilities/buttons_utils.c **/

  return ;

}

void init_main_images(Main_Image *main_images, SDL_Renderer *pRenderer) {

  /** Generating textures from images for displaying images (only the main here). **/

  main_images->player_cards_frame_texture   = get_texture_from_image(pRenderer,PATH_TO_FRAME_YELLOW)    ;

  main_images->cards_heap_frame_texture     = get_texture_from_image(pRenderer,PATH_TO_FRAME_BLUE)      ;

  main_images->computer_cards_frame_texture = get_texture_from_image(pRenderer,PATH_TO_FRAME_ORANGE)    ;

  main_images->throw_cards_frame_texture    = get_texture_from_image(pRenderer,PATH_TO_FRAME_GRAY)      ;

  main_images->card_back_face_texture       = get_texture_from_image(pRenderer,PATH_TO_CARD_BACK_FACE)  ;


  main_images->background_playground        = get_texture_from_image(pRenderer,PATH_TO_BG_IMAGE)        ;

  main_images->bg_playground_border         = get_texture_from_image(pRenderer,PATH_TO_BORDER_BG_IMAGE) ;

  main_images->score_field                  = get_texture_from_image(pRenderer,PATH_TO_SCORE_BG)        ;

  return ;
}

void init_cards_anim_vectors(Anim_Cards_Vectors *anim_cards_vectors) {

  /** Function to compute all needed vectors by the game for cards moving animations.
   *  All functions are to find at \file ./Utilities/animations_compute_trajectories.c
   * *********************************************************************************/


  distribute_cards_animations_compute_trajectories(anim_cards_vectors->distribute_cards_1,0) ;
  distribute_cards_animations_compute_trajectories(anim_cards_vectors->distribute_cards_2,1) ;

  clean_cards_animations_compute_trajectories(anim_cards_vectors->clean_cards_1,0) ;
  clean_cards_animations_compute_trajectories(anim_cards_vectors->clean_cards_2,1) ;



  computer_new_cards_animations_compute_trajectories(anim_cards_vectors->player_new_cards,   false) ;
  computer_new_cards_animations_compute_trajectories(anim_cards_vectors->computer_new_cards, true) ;

  computer_throw_cards_animations_compute_trajectories(anim_cards_vectors->computer_throw_cards) ;

  return ;
}
