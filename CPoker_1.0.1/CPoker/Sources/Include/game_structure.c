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

typedef struct Animate_Cards_Vectors_ {

  Vector distribute_cards_1[10][50]  ;
  Vector distribute_cards_2[10][50]  ;

  Vector clean_cards_1[10][50]  ;
  Vector clean_cards_2[10][50]  ;

  Vector computer_throw_cards[5][50] ;

  Vector player_new_cards[5][50]   ;
  Vector computer_new_cards[5][50] ;

} Anim_Cards_Vectors ;

Anim_Cards_Vectors *anim_cards_vectors ;

typedef struct Main_Images_ {

  SDL_Texture *player_cards_frame_texture   ;

  SDL_Texture *cards_heap_frame_texture     ;

  SDL_Texture *computer_cards_frame_texture ;

  SDL_Texture *throw_cards_frame_texture    ;

  SDL_Texture *card_back_face_texture       ;

  SDL_Texture *background_playground        ;

  SDL_Texture *bg_playground_border         ;

  SDL_Texture *score_field                  ;

} Main_Image ;

Main_Image *main_images ;

typedef struct Animate_Cards_settings_ {
    uint8_t card         ;
    uint8_t step         ;
    uint8_t cards_number ;
    uint8_t pos_to_fill  ;
 
} Anim_Cards ;

Anim_Cards *dist_settings  ;
Anim_Cards *clean_settings ;

typedef struct Throw_Cards_Settings_ {
  uint8_t number ;
  _Bool index[5] ;

  uint8_t counter   ;

  uint8_t start_index ;

  uint8_t cur_index ;
  uint8_t cur_step  ;

} Throw_Cards ;

Throw_Cards *throw_cards ; /** DEBUG **/

typedef Throw_Cards Give_New_Cards_Animation   ;



Give_New_Cards_Animation *give_new_cards_player   ;
Give_New_Cards_Animation *give_new_cards_computer ;



typedef struct Bounding_Box_ {
  uint16_t x1 ;
  uint16_t y1 ;
  uint16_t x2 ;
  uint16_t y2 ;

  _Bool is_frame_empty ;

} BBox ;

BBox bounding_boxes[6] ;

typedef struct Button_ {

  SDL_Texture *button_normal_image    ;
  SDL_Texture *button_mouseover_image ;

  SDL_Texture *button_current_image   ;

  BBox bounding_box ;

  _Bool is_mouseover ;

  _Bool is_allowed ;

} Button ;

Button buttons[6] ;

typedef struct Card_ {

  int8_t  value ;
  int8_t  type  ; /** 0 = Carot ; 1 = Heart ; 2 == Pick ; 3 == Shamrock **/

  SDL_Texture *card_image ;

  _Bool is_moving ;

  _Bool is_back_faced ;

  uint16_t x ;

  uint16_t y ;

  _Bool card_is_throw ;

  uint8_t index ;

  _Bool part_of_combination ;

} Card ;

Card *current_card ;

typedef struct Dragging_ {

  Card *card ;

  uint16_t x ;
  uint16_t y ;

} Dragging ;

Dragging *dragging_card ;

typedef struct Text_ {

  uint16_t x ;
  uint16_t y ;

  uint16_t width  ;
  uint16_t height ;

  SDL_Texture *font_texture ;

  TTF_Font *font ;

  SDL_Color text_color ;

  char *text ;

} Text ;


typedef struct Game_ {

  Card  player[5]   ;
  Card  computer[5] ;

  Card player_hand[5]   ;
  Card computer_hand[5] ;

  uint8_t player_score   ;
  uint8_t computer_score ;

  int8_t round_winner ;

  uint8_t number_of_rounds ;

  uint8_t rounds_counter   ;

  Text player_text   ;
  Text computer_text ;

  Text result_text   ;

  Text winner_text   ;

  Text press_escape  ;

  SDL_Cursor *cursor_type ;

  int8_t GAME_STATUS       ;

  int8_t SAVED_GAME_STATUS ;

  _Bool is_animation_running ;

  _Bool distribute ;  // To rename in something like this:   *_order

  _Bool mouse_over_card ;

  Stack *card_game ;

  Stack *throw_cards_stack ;

} Game ;

Game *game_control ;
