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

void initialise_button(uint8_t index, SDL_Texture *button_normal_image, SDL_Texture *button_mouseover_image) {

  /** Initialise a button in relation ship to his index in the button hierarchy. **/

  buttons[index].button_normal_image    = button_normal_image    ;

  buttons[index].button_mouseover_image = button_mouseover_image ;

  buttons[index].button_current_image   = button_normal_image    ;

  /** Buttons images inner offset :
   *  -) offset left    3px
   *  -) offset right   4px
   *  -) offset top    11px
   *  -) offset bottom 12px
   *
   * Buttons images offset from border: 6px
   *
   ****************************************/

  buttons[index].bounding_box.x1 = 6 + 3                              ;
  buttons[index].bounding_box.y1 = (100*index) - (11*index) + 11      ;
  buttons[index].bounding_box.x2 = 6 + BUTTON_WIDTH - 4               ;
  buttons[index].bounding_box.y2 = (100*index) - (11*index) + 11+ 77  ;

  buttons[index].is_mouseover = false ;

  buttons[index].is_allowed   = (index == 0) ? true : false  ;

  return ;
}

_Bool is_mouse_in_buttons_bboxes(mouse_x) {

  /** Check if mouse in buttons region. **/

  if (mouse_x <= SCREEN_WIDTH_OFFSET) {
    return true ;
  }
  return false ;
}

void mouse_over_button(mouse_x,mouse_y) {

  /** Check if mouse is over the current allowed button. **/

  uint8_t c ;

  for (c=0 ; c < 6 ; c++) {

    if (buttons[c].is_allowed) {
      /** Button must be allowed **/
      if (! buttons[c].is_mouseover && (buttons[c].bounding_box.x1 <= mouse_x &&  buttons[c].bounding_box.x2 >= mouse_x && buttons[c].bounding_box.y1 <= mouse_y  && buttons[c].bounding_box.y2 >= mouse_y) ) {
   
        /** Only the first time, in an mainloop unit, the mouse is over the button we change the settings.
         *  Throught the is_mouseover member from it.
         ************************************************************************************************/
   
        buttons[c].button_current_image = buttons[c].button_mouseover_image ;
        buttons[c].is_mouseover=true ;
   
        game_control->cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND) ;
        SDL_SetCursor(game_control->cursor_type)  ;
           
        break ;
      }
    }

    if (buttons[c].is_mouseover && ! (buttons[c].bounding_box.x1 <= mouse_x &&  buttons[c].bounding_box.x2 >= mouse_x && buttons[c].bounding_box.y1 <= mouse_y  && buttons[c].bounding_box.y2 >= mouse_y)) {
 
      /** Only if the mouse is leave the button and was over we reset settings. **/
 
      buttons[c].button_current_image = buttons[c].button_normal_image ;
      buttons[c].is_mouseover=false ;
 
      game_control->cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW) ;
      SDL_SetCursor(game_control->cursor_type)  ;
       
      break ;
    }
  }

  return ;
}

int8_t press_button(mouse_x,mouse_y) {

  /** Return which button is pressed or not. **/

  uint8_t c ;

  for (c=0 ; c < 6 ; c++) {

    /** Button must be allowed **/

    if ( buttons[c].is_mouseover && (buttons[c].bounding_box.x1 <= mouse_x &&  buttons[c].bounding_box.x2 >= mouse_x && buttons[c].bounding_box.y1 <= mouse_y  && buttons[c].bounding_box.y2 >= mouse_y) ) {
      return c ;
    }
  }

  return -1 ;
}

void do_change_game_status(int8_t code) {

  /** Called by button pressing.
   *  Mainly to change the current GAME STATUS and setting the next button to be allowed.
   * ************************************************************************************/

  switch (code) {

    case 0 :
 
      if (game_control->GAME_STATUS == GAME_START) {
   
        /** User press the "Distribute cards" button. **/
   
        #ifdef DEBUG
          fprintf(stdout,"Switch to CARDS_DISTRIBUTE GAME_STATUS \n") ;
        #endif
     
        game_control->GAME_STATUS=CARDS_DISTRIBUTE ;
    
        buttons[code].is_allowed   = false ;
        buttons[code+1].is_allowed = true  ;
   
      }
      break ;
 
    case 1 :
 
      /** User press the "Computer play" button. **/
 
      if (game_control->GAME_STATUS == CARDS_DISCOVER || game_control->GAME_STATUS == CARDS_COVER) {
        #ifdef DEBUG
          fprintf(stdout,"Switch to THROW_CARDS GAME_STATUS\n") ;
        #endif
     
        game_control->GAME_STATUS=THROW_CARDS ;
   
        buttons[code].is_allowed   = false ;
        buttons[code+1].is_allowed = true  ;
      }
 
      break ;
 
    case 2 :
 
      /** User press the "Give new cards" button. **/
 
      if (game_control->GAME_STATUS == CARDS_THROW || game_control->GAME_STATUS == CARDS_DISCOVER) {
   
        set_cards_to_give_new(give_new_cards_player,   game_control->player) ;
        set_cards_to_give_new(give_new_cards_computer, game_control->computer) ;
   
        give_new_cards() ;
     
   
        #ifdef DEBUG
          fprintf(stdout,"Switch to GIVE_NEW_CARDS GAME_STATUS\n") ;
        #endif
     
        game_control->GAME_STATUS=GIVE_NEW_CARDS ;
   
        game_control->SAVED_GAME_STATUS=GIVE_NEW_CARDS ;
   
        buttons[code].is_allowed   = false ;
        buttons[code+1].is_allowed = true  ;
      }
 
      break ;
 
    case 3 :
 
      /** User press the "Show cards" button. **/
 
      if (game_control->GAME_STATUS ==  NEW_CARDS_GIVEN  || game_control->GAME_STATUS == CARDS_DISCOVER) {
   
        #ifdef DEBUG
          fprintf(stdout,"Switch to COMPUTER_SHOW_CARDS GAME_STATUS\n") ;
        #endif
     
        game_control->GAME_STATUS=COMPUTER_SHOW_CARDS ;
   
        buttons[code].is_allowed   = false ;
        //buttons[code+1].is_allowed = true  ;
      }
 
      break ;
 
    case 4 :
 
      /** User press the "Update score" button. **/
 
      if (game_control->GAME_STATUS == ROUND_DONE ) {
   
        #ifdef DEBUG
          fprintf(stdout,"Switch to DISPLAY_WINNER GAME_STATUS\n") ;
        #endif
   
        game_control->rounds_counter++ ;
   
        game_control->round_winner = compute_round_winner(game_control->player, game_control->computer) ;
        game_control->GAME_STATUS  = DISPLAY_WINNER ;
        buttons[code].is_allowed   = false ;
        buttons[code+1].is_allowed = true  ;
   
   
   
      }
   
      break ;
 
    case 5 :
 
      /** User press the "New round" button. **/
 
      if (game_control->GAME_STATUS == UPDATE_SCORE) {
   
        #ifdef DEBUG
          fprintf(stdout,"Switch to CLEAN_PLAYGROUND GAME_STATUS\n") ;
        #endif
   
        game_control->GAME_STATUS = CLEAN_PLAYGROUND ;
      }
 
    default :
 
      break ;
  }

}