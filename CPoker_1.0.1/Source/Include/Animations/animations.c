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

void return_a_card(SDL_Renderer *pRenderer,SDL_Texture *back_face_texture, int *sleep, int16_t *counter) {

  /** Implement an animation wenn the player return an card. */

  if (*counter == 0) {

    /** This is the first time the function is executed.
     *  So we change the mainloop pausing time,
     *  set the cursor to an wait cursor
     *  and the game status is set on playing an animation.
     ******************************************************/

    *sleep=5000 ;

    game_control->is_animation_running=true ;

    game_control->cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAITARROW) ;
    SDL_SetCursor(game_control->cursor_type)  ;

    current_card->is_moving=true ;
  }

  (*counter)++ ;

  SDL_Texture *image_to_display ; /** The image can either be tyhe back face or front face of the card. **/

  SDL_Rect dstrect ;

  dstrect.x = current_card->x ;
  dstrect.y = current_card->y ;
  dstrect.h = CARD_HEIGHT ;

  if ((*counter) < 73 ) {
    /** First phase of the animation: the card (back face) width decrease. **/

    dstrect.w= 73 - (*counter) ;

    image_to_display=back_face_texture ;

  }
  else if (((*counter) >= 73) && ((*counter) < 73*2)) {
    /** Second phase of the animation: the card (front face) width increase. **/

    dstrect.w= (int) fabs(73 - (*counter))  ;

    image_to_display=current_card->card_image ;

  }
  else if ((*counter) >= 73*2) {

    /** The animation is finish.
     *  So we reset:
     *  -) the mainloop pausing time,
     *  -) the cursor to the normal arrow.
     *  and the game status is set on playing an animation.
     ******************************************************/

    *sleep=10000 ;

    game_control->cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW) ;
    SDL_SetCursor(game_control->cursor_type)  ;

    game_control->is_animation_running = false ;
    game_control->GAME_STATUS=CARDS_DISCOVER ;

    current_card->is_moving=false ;
    current_card->is_back_faced=false ;

    current_card=NULL ;

    *counter=0 ;

    if (game_done(game_control->player,game_control->computer)) {

      #ifdef DEBUG
        fprintf(stdout,"Switch to ROUND_DONE GAME_STATUS\n") ;
      #endif

      buttons[3].is_allowed = false ;
      buttons[4].is_allowed = true  ;
      game_control->GAME_STATUS = ROUND_DONE ;
    }

    return ;

  }


  SDL_RenderCopyEx(pRenderer,
                   image_to_display,
                   NULL,
                   &dstrect,
                   0,
                   NULL,
                   SDL_FLIP_NONE) ;
             
  return ;             

}

void return_cards_computer_hand(SDL_Renderer *pRenderer,SDL_Texture *back_face_texture, int *sleep, int16_t *counter,uint8_t *index) {

  /** Implement an animation wenn the player return an card. */

  if ( *counter == 0 && *index == 0 ) {
    *sleep=5000 ;

    game_control->is_animation_running=true ;

    game_control->cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAITARROW) ;
    SDL_SetCursor(game_control->cursor_type)  ;

    current_card->is_moving=true ;
  }

  if (*counter == 0 && *index < 5 && *index != 0) {

    /** This is the first time the function is executed.
     *  So we change the mainloop pausing time,
     *  set the cursor to an wait cursor
     *  and the game status is set on playing an animation.
     ******************************************************/

    current_card->is_moving=true ;

  }

  (*counter)++ ;

  SDL_Texture *image_to_display ; /** The image can either be tyhe back face or front face of the card. **/

  SDL_Rect dstrect ;

  dstrect.x = current_card->x ;
  dstrect.y = current_card->y ;
  dstrect.h = CARD_HEIGHT ;

  if ((*counter) < 73 ) {
    /** First phase of the animation: the card (back face) width decrease. **/

    dstrect.w= 73 - (*counter) ;

    image_to_display=back_face_texture ;

  }
  else if (((*counter) >= 73) && ((*counter) < 73*2)) {
    /** Second phase of the animation: the card (front face) width increase. **/

    dstrect.w= (int) fabs(73 - (*counter))  ;

    image_to_display=current_card->card_image ;

  }
  else if ((*counter) >= 73*2) {

    /** The animation is finish.
     *  So we reset:
     *  -) the mainloop pausing time,
     *  -) the cursor to the normal arrow.
     *  and the game status is set on playing an animation.
     ******************************************************/
  
    current_card->is_moving=false ;
    current_card->is_back_faced=false ;
    current_card->card_is_throw=false ;


    *counter=0 ;



    (*index)++ ;

    if (*index == 5) {

      if (game_done(game_control->player,game_control->computer)) {

        #ifdef DEBUG
          fprintf(stdout,"Switch to ROUND_DONE GAME_STATUS\n") ;
        #endif

        buttons[3].is_allowed = false ;
        buttons[4].is_allowed = true  ;
        game_control->GAME_STATUS = ROUND_DONE ;
      }

      game_control->cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW) ;

      SDL_SetCursor(game_control->cursor_type)  ;

      game_control->is_animation_running = false ;

      *sleep=10000 ;

      return ;
    }

    current_card=&game_control->computer[*index] ;


    return ;
  }

  SDL_RenderCopyEx(pRenderer,
                   image_to_display,
                   NULL,
                   &dstrect,
                   0,
                   NULL,
                   SDL_FLIP_NONE) ;
             
  return ;             

}


void display_a_card_by_animation(SDL_Renderer *pRenderer, SDL_Texture *card_back_face_texture, Vector animation_coords) {

  /** Distribute or gathering cards animation card display function. **/

  if ( (int16_t) round(animation_coords.x) == 0 || (int16_t) round(animation_coords.x) == 0) {
    return ;
  }

  display_image(pRenderer,card_back_face_texture, (int16_t) round(animation_coords.x), (int16_t) round(animation_coords.y), CARD_WIDTH, CARD_HEIGHT ) ;

  return ;
}

void set_next_card_index(Throw_Cards *throw_cards) {

  /** Set the index from the next card from the
   * computer cards throwning
   * or from the give new cards animation.
   * @note: the next card can be whatever in growing order card index.
   *******************************************************************/

  uint8_t c ;

  for (c=throw_cards->cur_index+1 ; throw_cards->index[c] != true || c > 4 ; c++) {
    throw_cards->cur_index++ ;
  }
  if (throw_cards->index[c] == true && c < 5) {
    throw_cards->cur_index++ ;
  }

  return ;
}

void break_computer_throw_cards_animation(void) {

  /** Computer throw cards animation end function. **/

  game_control->GAME_STATUS = CARDS_THROW ;
  game_control->SAVED_GAME_STATUS = CARDS_THROW ;
  game_control->is_animation_running = false ;

  game_control->cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW) ;
  SDL_SetCursor(game_control->cursor_type)  ;

  return ;
}


void computer_throw_cards_animation(SDL_Renderer *pRenderer,SDL_Texture *card_back_face_texture,Vector cards_throw[5][50],Throw_Cards *throw_cards, int *sleep) {

  /** Computer throw cards naimation function.
   *  The function need a Throw_Cards structure to control the animation.
   *  Each vector represent the current card postion.
   *  For each card their an Vector array from size depending from the length of the travel to reach the throw card frame.
   *  ********************************************************************************************************************/

  if (throw_cards->number > 0) {
    if (throw_cards->cur_index == throw_cards->start_index && throw_cards->cur_step == 0) {

      /** First time this function is called:
       *  So we initialize the setting for an animation.
       *************************************************/

      game_control->cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAITARROW) ;
      SDL_SetCursor(game_control->cursor_type)  ;

      game_control->is_animation_running = true ;

      game_control->computer[throw_cards->cur_index].is_moving=true ;
      game_control->computer[throw_cards->cur_index].card_is_throw=true ;
    }


    if (throw_cards->cur_step == 0) {

      switch (throw_cards->cur_index) {

        /** We set the pausing time from the mainloop.
         *  In relationship to the length to travel from the current card. */

        case 0 :
          *sleep=5250*2 ;
          break ;
        case 1 :
          *sleep=6375*2 ;
          break ;
        case 2 :
          *sleep=7500*2 ;
          break ;
        case 3 :
          *sleep=10000*2 ;
          break ;
        case 4 :
          *sleep=12500*2 ;
          break ;

      }

    }



    throw_cards->cur_step++ ;

    if ( throw_cards->cur_index == 0 && throw_cards->cur_step == 50 ) {

      /** The first card has reach the throw card frame. **/

      throw_cards->counter++ ;

      throw_a_card(game_control->throw_cards_stack, &game_control->computer[throw_cards->cur_index]) ;
      remove_a_card_from_hand(game_control->computer,throw_cards->cur_index,false) ;

      if (throw_cards->counter == throw_cards->number) {

        /** There are no more card to throw. **/

        *sleep=10000 ;
        break_computer_throw_cards_animation() ;
        return ;
      }

      /** Compute next card to throw. **/
      set_next_card_index(throw_cards) ;

      throw_cards->cur_step = 0 ;  /** This is card moving step unit. **/

      game_control->computer[throw_cards->cur_index].is_moving=true ;
      game_control->computer[throw_cards->cur_index].card_is_throw=true ;

      if (bounding_boxes[5].is_frame_empty) {

        /** Case the throw card heap was empty before. **/

        bounding_boxes[5].is_frame_empty=false ;
      }

    }
    else if (throw_cards->cur_index == 1 && throw_cards->cur_step == 40 ) {

      /** The second card has reach the throw card frame. **/

      throw_cards->counter++ ;

      throw_a_card(game_control->throw_cards_stack, &game_control->computer[throw_cards->cur_index]) ;
      remove_a_card_from_hand(game_control->computer,throw_cards->cur_index,false) ;

      if (throw_cards->counter == throw_cards->number) {

        /** There are no more card to throw. **/

        *sleep=10000 ;
        break_computer_throw_cards_animation() ;
        return ;
      }

      /** Compute next card to throw. **/
      set_next_card_index(throw_cards) ;

      throw_cards->cur_step = 0 ;  /** This is card moving step unit. **/

      game_control->computer[throw_cards->cur_index].is_moving=true ;
      game_control->computer[throw_cards->cur_index].card_is_throw=true ;

      if (bounding_boxes[5].is_frame_empty) {

        /** Case the throw card heap was empty before. **/

        bounding_boxes[5].is_frame_empty=false ;
      }
    }
    else if (throw_cards->cur_index == 2 && throw_cards->cur_step == 30 ) {

      /** The third card has reach the throw card frame. **/

      throw_cards->counter++ ;

      throw_a_card(game_control->throw_cards_stack, &game_control->computer[throw_cards->cur_index]) ;
      remove_a_card_from_hand(game_control->computer,throw_cards->cur_index,false) ;

      if (throw_cards->counter == throw_cards->number) {

        /** There are no more card to throw. **/

        *sleep=10000 ;
        break_computer_throw_cards_animation() ;
        return ;
      }


      /** Compute next card to throw. **/
      set_next_card_index(throw_cards) ;

      throw_cards->cur_step = 0 ;  /** This is card moving step unit. **/

      game_control->computer[throw_cards->cur_index].is_moving=true ;
      game_control->computer[throw_cards->cur_index].card_is_throw=true ;

      if (bounding_boxes[5].is_frame_empty) {

        /** Case the throw card heap was empty before. **/

        bounding_boxes[5].is_frame_empty=false ;
      }
    }
    else if (throw_cards->cur_index == 3 && throw_cards->cur_step == 20 ) {

      /** The fourth card has reach the throw card frame. **/

      throw_cards->counter++ ;

      throw_a_card(game_control->throw_cards_stack, &game_control->computer[throw_cards->cur_index]) ;
      remove_a_card_from_hand(game_control->computer,throw_cards->cur_index,false) ;

      if (throw_cards->counter == throw_cards->number) {

        /** There are no more card to throw. **/

        *sleep=10000 ;
        break_computer_throw_cards_animation() ;
        return ;
      }


      /** Compute next card to throw. **/
      set_next_card_index(throw_cards) ;

      throw_cards->cur_step = 0 ;  /** This is card moving step unit. **/

      game_control->computer[throw_cards->cur_index].is_moving=true ;
      game_control->computer[throw_cards->cur_index].card_is_throw=true ;

      if (bounding_boxes[5].is_frame_empty) {

        /** Case the throw card heap was empty before. **/

        bounding_boxes[5].is_frame_empty=false ;
      }
    }
    else if (throw_cards->cur_index == 4 && throw_cards->cur_step == 10  ) {

      /** The fives card has reach the throw card frame. **/

      throw_a_card(game_control->throw_cards_stack, &game_control->computer[throw_cards->cur_index]) ;
      remove_a_card_from_hand(game_control->computer,throw_cards->cur_index,false) ;

       /** There are no more card to throw. **/
       *sleep=10000 ;
       break_computer_throw_cards_animation() ;
       return ;
 
    }

    /** Display the current card to throw during the animation. **/
    display_image(pRenderer,
                 card_back_face_texture,
                 (int16_t) round(cards_throw[throw_cards->cur_index][throw_cards->cur_step].x),
                 (int16_t) round(cards_throw[throw_cards->cur_index][throw_cards->cur_step].y),
                 CARD_WIDTH,
                 CARD_HEIGHT) ;
  }
  else {

    /** The computer has no cards to throw. **/

    break_computer_throw_cards_animation() ;
  }

  return ;
}

void break_give_new_cards_animation(void) {

  if (! game_control->distribute && ! give_order) {
    give_order=true ;
    return ;
  }
  else if (game_control->distribute && give_order) {
    give_order=false ;
    return ;
  }


  game_control->GAME_STATUS = NEW_CARDS_GIVEN ;
  game_control->cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW) ;
  SDL_SetCursor(game_control->cursor_type)  ;
  game_control->is_animation_running = false ;

  return ;
}

void give_new_cards_animation(SDL_Renderer *pRenderer,SDL_Texture *card_back_face_texture,Vector cards_add[5][50],Give_New_Cards_Animation *new_cards, int *sleep) {

   /** Give new cards animation.
   *  The function need a Give_New_Cards_Animation structure to control the animation.
   *  Each vector represent the current card postion.
   *  For each card their an Vector array from size depending from the length of the travel to reach his destination.
   *  ***************************************************************************************************************/

  if (new_cards->number && game_control->GAME_STATUS == GIVE_NEW_CARDS) {
    if (new_cards->cur_index == new_cards->start_index && new_cards->cur_step == 0) {

      /** First time this function is called:
       *  So we initialize the setting for an animation.
       *************************************************/

      game_control->cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAITARROW) ;
      SDL_SetCursor(game_control->cursor_type)  ;
      game_control->is_animation_running = true ;

    }


    if (new_cards->cur_step == 0) {

      /** We set the pausing time from the mainloop.
       *  In relationship to the length to travel from the current card. */

      switch (new_cards->cur_index) {
        case 0 :
          *sleep=12500*2 ;
          break ;
        case 1 :
          *sleep=10000*2 ;
          break ;
        case 2 :
          *sleep=7500*2 ;
          break ;
        case 3 :
          *sleep=6375*2 ;
          break ;
        case 4 :
          *sleep=5250*2 ;
          break ;

      }

    }



    new_cards->cur_step++ ;

    if ( new_cards->cur_index == 0 && new_cards->cur_step == 10 ) {

      /** The first card has reach his destination. **/
        
      new_cards->cur_step = 0 ;

      if (! give_order) {
        /** Case the player receive the cards first. **/
        game_control->player[0].is_moving=false ;
        game_control->player[0].card_is_throw=false ;
        game_control->player[0].is_back_faced=true ;

        game_control->player[0].x= CARD_BORDER_OFFSET    ;
        game_control->player[0].y= FRAME_Y_BOTTOM_POS + FRAME_CARD_OFFSET ;

        bounding_boxes[0].is_frame_empty = false ;
      }
      else {
        /** Case the computer receive the cards first. **/
        game_control->computer[0].is_moving=false ;
        game_control->computer[0].card_is_throw=false ;
        game_control->computer[0].is_back_faced=true ;

        game_control->computer[0].x= CARD_BORDER_OFFSET   ;
        game_control->computer[0].y= FRAME_Y_TOP_POS + FRAME_CARD_OFFSET ;
      }

      new_cards->counter++ ;


      if (new_cards->counter == new_cards->number) {

        /** There are no more card to give. **/

        *sleep=10000 ;
        break_give_new_cards_animation() ;
        return ;
      }

      /** Compute next card to give. **/
      set_next_card_index((Throw_Cards *)new_cards) ;
      return ;

    }
    else if (new_cards->cur_index == 1 && new_cards->cur_step == 20 ) {

        /** The second card has reach his destination. **/

        new_cards->cur_step = 0 ;

        if (! give_order) {
          /** Case the player receive the cards first. **/
          game_control->player[1].is_moving=false ;
          game_control->player[1].card_is_throw=false ;
          game_control->player[1].is_back_faced=true ;

          game_control->player[1].x= CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * 1) + (CARD_WIDTH * 1) ;
          game_control->player[1].y= FRAME_Y_BOTTOM_POS  + FRAME_CARD_OFFSET ;

          bounding_boxes[1].is_frame_empty = false ;
        }
        else {
          game_control->computer[1].is_moving=false ;
          game_control->computer[1].card_is_throw=false ;
          game_control->computer[1].is_back_faced=true ;

          game_control->computer[1].x= CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * 1) + (CARD_WIDTH * 1) ;
          game_control->computer[1].y= FRAME_Y_TOP_POS     + FRAME_CARD_OFFSET ;
        }

        new_cards->counter++ ;


        if (new_cards->counter == new_cards->number) {
          /** There are no more card to give. **/

          *sleep=10000 ;
          break_give_new_cards_animation() ;
          return ;
        }

        /** Compute next card to give. **/
        set_next_card_index((Throw_Cards *)new_cards) ;
        return ;




    }
    else if (new_cards->cur_index == 2 && new_cards->cur_step == 30 ) {




        new_cards->cur_step = 0 ;

        if (! give_order) {
          /** Case the player receive the cards first. **/
          game_control->player[2].is_moving=false ;
          game_control->player[2].card_is_throw=false ;
          game_control->player[2].is_back_faced=true ;

          game_control->player[2].x= CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * 2) + (CARD_WIDTH * 2) ;
          game_control->player[2].y= FRAME_Y_BOTTOM_POS  + FRAME_CARD_OFFSET ;

          bounding_boxes[2].is_frame_empty = false ;
        }
        else {
          /** Case the computer receive the cards first. **/
          game_control->computer[2].is_moving=false ;
          game_control->computer[2].card_is_throw=false ;
          game_control->computer[2].is_back_faced=true ;

          game_control->computer[2].x= CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * 2) + (CARD_WIDTH * 2) ;
          game_control->computer[2].y= FRAME_Y_TOP_POS     + FRAME_CARD_OFFSET ;
        }

        new_cards->counter++ ;


        if (new_cards->counter == new_cards->number) {
          /** There are no more card to give. **/

          *sleep=10000 ;
          break_give_new_cards_animation() ;
          return ;
        }

        /** Compute next card to give. **/
        set_next_card_index((Throw_Cards *)new_cards) ;
        return ;

    }
    else if (new_cards->cur_index == 3 && new_cards->cur_step == 40 ) {

  
        new_cards->cur_step = 0 ;

        if (! give_order) {
          /** Case the player receive the cards first. **/
          game_control->player[3].is_moving=false ;
          game_control->player[3].card_is_throw=false ;
          game_control->player[3].is_back_faced=true ;

          game_control->player[3].x= CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * 3) + (CARD_WIDTH * 3) ;
          game_control->player[3].y= FRAME_Y_BOTTOM_POS  + FRAME_CARD_OFFSET ;

          bounding_boxes[3].is_frame_empty = false ;
        }
        else {
          /** Case the computer receive the cards first. **/
          game_control->computer[3].is_moving=false ;
          game_control->computer[3].card_is_throw=false ;
          game_control->computer[3].is_back_faced=true ;

          game_control->computer[3].x= CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * 3) + (CARD_WIDTH * 3) ;
          game_control->computer[3].y= FRAME_Y_TOP_POS     + FRAME_CARD_OFFSET ;
        }

        new_cards->counter++ ;


        if (new_cards->counter == new_cards->number) {
          /** There are no more card to give. **/

          *sleep=10000 ;
          break_give_new_cards_animation() ;
          return ;
        }

        /** Compute next card to give. **/
        set_next_card_index((Throw_Cards *)new_cards) ;
        return ;


    }
    else if (new_cards->cur_index == 4 && new_cards->cur_step == 50  ) {


       if (! give_order) {
         /** Case the player receive the cards first. **/
         game_control->player[4].is_moving=false ;
         game_control->player[4].card_is_throw=false ;
         game_control->player[4].is_back_faced=true ;

         game_control->player[4].x= CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * 4) + (CARD_WIDTH * 4) ;
         game_control->player[4].y= FRAME_Y_BOTTOM_POS  + FRAME_CARD_OFFSET ;

         bounding_boxes[4].is_frame_empty = false ;
        }
        else {
          /** Case the computer receive the cards first. **/
          game_control->computer[4].is_moving=false ;
          game_control->computer[4].card_is_throw=false ;
          game_control->computer[4].is_back_faced=true ;

          game_control->computer[4].x= CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * 4) + (CARD_WIDTH * 4) ;
          game_control->computer[4].y= FRAME_Y_TOP_POS     + FRAME_CARD_OFFSET ;
        }

 
       /** There are no more card to give. **/
       *sleep=10000 ;
       break_give_new_cards_animation() ;
       return ;
 
    }

    /** Display the current card during the animation. **/
    display_image(pRenderer,
                 card_back_face_texture,
                 (int16_t) round(cards_add[new_cards->cur_index][new_cards->cur_step].x),
                 (int16_t) round(cards_add[new_cards->cur_index][new_cards->cur_step].y),
                 CARD_WIDTH,
                 CARD_HEIGHT) ;
  }
  else if (new_cards->number == 0) {

    /** No need to give new cards. **/
    break_give_new_cards_animation() ;
  }
  return ;
}

void distribute_cards(SDL_Renderer *pRenderer,SDL_Texture *card_back_face_texture,Vector distribute_cards[10][50],Anim_Cards *anim_cards_settings, int *sleep, _Bool invert) {

  /** Distribute cards animation.
   *  The function need a Anim_Cards structure to control the animation.
   *  Each vector represent the current card postion.
   *  For each card their an Vector array from size depending from the length of the travel to reach the throw card frame.
   *  ********************************************************************************************************************/

  if (game_control->GAME_STATUS == CARDS_DISTRIBUTE) {
      if ((anim_cards_settings->step == 0) && (anim_cards_settings->card == 0)) {

        /** First time this function is called:
          *  So we initialize the setting for an animation.
          *************************************************/

        *sleep=12500 ;
        game_control->cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAITARROW) ;
        SDL_SetCursor(game_control->cursor_type)  ;
        game_control->is_animation_running = true ;

      }

      /** Display the current card to throw during the animation. **/
      display_a_card_by_animation(pRenderer,card_back_face_texture ,distribute_cards[anim_cards_settings->card][anim_cards_settings->step]) ;

      anim_cards_settings->step++ ;

      if ((anim_cards_settings->step == 10) && (anim_cards_settings->card == 0 )) {

        /** The first card has reach his destination, even the player or the computer hand first
         *  depending from the value from the boolean variable invert. **/

        anim_cards_settings->card++ ;
        anim_cards_settings->step=0 ;

        anim_cards_settings->pos_to_fill++  ;
        anim_cards_settings->cards_number++ ;
      }
     else if ((anim_cards_settings->step == 10) && (anim_cards_settings->card == 1)) {
       /** The first card has reach his destination, even the player or the computer hand first
         *  depending from the value from the boolean variable invert. **/
 
       anim_cards_settings->card++ ;
       anim_cards_settings->step=0 ;
 
       /** The first card is distribute for the player and the computer
        *  so we set the sleep value for the next card animation.       */
       *sleep -= 2500  ;
 
       anim_cards_settings->cards_number++ ;

      }
      else if ((anim_cards_settings->step == 20) && (anim_cards_settings->card == 2 )) {
        /** The second card has reach his destination, even the player or the computer hand first
         *  depending from the value from the boolean variable invert. **/

        anim_cards_settings->card++ ;
        anim_cards_settings->step=0 ;

        anim_cards_settings->pos_to_fill++  ;
        anim_cards_settings->cards_number++ ;
      }
      else if ((anim_cards_settings->step == 20) && (anim_cards_settings->card == 3)) {
        /** The second card has reach his destination, even the player or the computer hand first
         *  depending from the value from the boolean variable invert. **/

        anim_cards_settings->card++ ;
        anim_cards_settings->step=0 ;

        /** The second card is distribute for the player and the computer
         *  so we set the sleep value for the next card animation.         */
        *sleep -= 2500  ;

        anim_cards_settings->cards_number++ ;
      }
      else if ((anim_cards_settings->step == 30) && (anim_cards_settings->card == 4)) {
        /** The third card has reach his destination, even the player or the computer hand first
         *  depending from the value from the boolean variable invert. **/

        anim_cards_settings->card++ ;
        anim_cards_settings->step=0 ;

        anim_cards_settings->cards_number++ ;
        anim_cards_settings->pos_to_fill++  ;
      }
      else if ((anim_cards_settings->step == 30) && (anim_cards_settings->card == 5)) {
        /** The third card has reach his destination, even the player or the computer hand first
         *  depending from the value from the boolean variable invert. **/

        anim_cards_settings->card++ ;
        anim_cards_settings->step=0 ;

        /** The third card is distribute for the player and the computer
         *  so we set the sleep value for the next card animation.         */
        *sleep -= 1125 ;

        anim_cards_settings->cards_number++ ;
      }
      else if ((anim_cards_settings->step == 40) && (anim_cards_settings->card == 6 )) {
        /** The fourth card has reach his destination, even the player or the computer hand first
         *  depending from the value from the boolean variable invert. **/

        anim_cards_settings->card++ ;
        anim_cards_settings->step=0 ;

        anim_cards_settings->cards_number++ ;
        anim_cards_settings->pos_to_fill++  ;
      }
      else if ((anim_cards_settings->step == 40) && (anim_cards_settings->card == 7 )) {
        /** The fourth card has reach his destination, even the player or the computer hand first
         *  depending from the value from the boolean variable invert. **/

        anim_cards_settings->card++ ;
        anim_cards_settings->step=0 ;

        /** The fourth card is distribute for the player and the computer
         *  so we set the sleep value for the next card animation.         */
        *sleep -= 1125 ;
        anim_cards_settings->cards_number++ ;
      }
      else if ((anim_cards_settings->step == 50) && (anim_cards_settings->card == 8)) {
        /** The fives card has reach his destination, even the player or the computer hand first
         *  depending from the value from the boolean variable invert. **/

        anim_cards_settings->card++ ;
        anim_cards_settings->step=0 ;

        anim_cards_settings->cards_number++ ;
        anim_cards_settings->pos_to_fill++  ;
      }
      else if ((anim_cards_settings->step == 50) && (anim_cards_settings->card == 9)) {
        /** The fives card has reach his destination, even the player or the computer hand first
         *  depending from the value from the boolean variable invert. **/

        /** The anilation has reach his end we reset the settings to play. **/
        game_control->GAME_STATUS=CARDS_COVER ;
        anim_cards_settings->card=0 ;
        anim_cards_settings->step=0 ;
        *sleep=10000 ;
        anim_cards_settings->cards_number++ ;
        game_control->cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW) ;
        SDL_SetCursor(game_control->cursor_type)  ;
        game_control->is_animation_running = false ;
      }


  }

  if ( game_control->GAME_STATUS == CARDS_DISTRIBUTE ) {
    /** Display the cards in relationship to which has reach the destination. **/
    display_back_face_card(pRenderer,card_back_face_texture, anim_cards_settings->pos_to_fill, anim_cards_settings->cards_number, invert) ;
  }
  else if (game_control->GAME_STATUS == CARDS_COVER ) {
    /** Display all cards returned **/
    display_back_face_card(pRenderer,card_back_face_texture, 5, 10, invert) ;
    anim_cards_settings->cards_number=0 ;
    anim_cards_settings->pos_to_fill=0  ;
  }

  return ;
}

void gathering_cards_animation(SDL_Renderer *pRenderer,SDL_Texture *card_back_face_texture,Vector distribute_cards[10][50],Anim_Cards *anim_cards_settings, int *sleep, _Bool invert) {

  /** Gathering cards animation.
   *  The function need a Anim_Cards structure to control the animation.
   *  Each vector represent the current card postion.
   *  For each card their an Vector array from size depending from the length of the travel to reach the throw card frame.
   *  ********************************************************************************************************************/

  if (game_control->GAME_STATUS == CLEAN_PLAYGROUND) {
      if ((anim_cards_settings->step == 0) && (anim_cards_settings->card == 0)) {

        /** First time this function is called:
          *  So we initialize the setting for an animation.
          *************************************************/

        *sleep=5250 ;  /** We set the pausing time from the mainloop. **/

        game_control->cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAITARROW) ;
        SDL_SetCursor(game_control->cursor_type)  ;
        game_control->is_animation_running = true ;

        if (! invert) {
          /** Case we gather the player card first. **/
          game_control->player[0].card_is_throw   = true ;
        }
        else {
          /** Case we gather the computer card first. **/
          game_control->computer[0].card_is_throw = true ;
        }
      }

      anim_cards_settings->step++ ;

      display_a_card_by_animation(pRenderer,card_back_face_texture ,distribute_cards[anim_cards_settings->card][anim_cards_settings->step]) ;


      if ((anim_cards_settings->step == 50) && (anim_cards_settings->card == 0 )) {

        /** The first card has reach the throw card frame.
         *  Even from the player or the computer hand first
         *  depending from the value from the boolean variable invert. **/

        if (! bounding_boxes[5].is_frame_empty) {

          /** Case the throw card heap was empty before. **/

          bounding_boxes[5].is_frame_empty=false ;
        }

        anim_cards_settings->card++ ;
        anim_cards_settings->step=0 ;

        anim_cards_settings->pos_to_fill++  ;
        anim_cards_settings->cards_number++ ;

        if (! invert) {
          /** Case we gather the player card. **/
          game_control->computer[0].card_is_throw = true ;
        }
        else {
          /** Case we gather the computer card. **/
          game_control->player[0].card_is_throw   = true ;
        }

      }
     else if ((anim_cards_settings->step == 50) && (anim_cards_settings->card == 1)) {
 
       /** The first card has reach the throw card frame.
         * Even from the player or the computer hand first
         * depending from the value from the boolean variable invert. **/
 
       anim_cards_settings->card++ ;
       anim_cards_settings->step=0 ;
 
       *sleep=6375 ;  /** We set the pausing time from the mainloop. **/
 
       anim_cards_settings->cards_number++ ;

       if (! invert) {
         /** Case we gather the player card. **/
         game_control->player[1].card_is_throw   = true ;
      }
      else {
        /** Case we gather the computer card. **/
        game_control->computer[1].card_is_throw = true ;
      }

      }
      else if ((anim_cards_settings->step == 40) && (anim_cards_settings->card == 2 )) {

        /** The second card has reach the throw card frame.
         *  Even from the player or the computer hand first
         *  depending from the value from the boolean variable invert. **/

        anim_cards_settings->card++ ;
        anim_cards_settings->step=0 ;

        anim_cards_settings->pos_to_fill++  ;
        anim_cards_settings->cards_number++ ;

        if (! invert) {
          /** Case we gather the player card first. **/
          game_control->computer[1].card_is_throw = true ;
        }
        else {
          /** Case we gather the computer card first. **/
          game_control->player[1].card_is_throw   = true ;
        }

      }
      else if ((anim_cards_settings->step == 40) && (anim_cards_settings->card == 3)) {

        /** The second card has reach the throw card frame.
         *  Even from the player or the computer hand first
         *  depending from the value from the boolean variable invert. **/

        anim_cards_settings->card++ ;
        anim_cards_settings->step=0 ;

        *sleep=7500 ;  /** We set the pausing time from the mainloop. **/

        anim_cards_settings->cards_number++ ;

        if (! invert) {
          /** Case we gather the player card. **/
          game_control->player[2].card_is_throw   = true ;
        }
        else {
          /** Case we gather the computer card. **/
          game_control->computer[2].card_is_throw = true ;
        }

      }
      else if ((anim_cards_settings->step == 30) && (anim_cards_settings->card == 4)) {

        /** The third card has reach the throw card frame.
         *  Even from the player or the computer hand first
         *  depending from the value from the boolean variable invert. **/

        anim_cards_settings->card++ ;
        anim_cards_settings->step=0 ;

        anim_cards_settings->cards_number++ ;
        anim_cards_settings->pos_to_fill++  ;

        if (! invert) {
          /** Case we gather the player card. **/
          game_control->computer[2].card_is_throw = true ;
        }
        else {
          /** Case we gather the computer card. **/
          game_control->player[2].card_is_throw   = true ;
        }

      }
      else if ((anim_cards_settings->step == 30) && (anim_cards_settings->card == 5)) {

        /** The third card has reach the throw card frame.
         *  Even from the player or the computer hand first
         *  depending from the value from the boolean variable invert. **/

        anim_cards_settings->card++ ;
        anim_cards_settings->step=0 ;

        *sleep=10000 ;  /** We set the pausing time from the mainloop. **/

        anim_cards_settings->cards_number++ ;

        if (! invert) {
          /** Case we gather the player card. **/
          game_control->player[3].card_is_throw   = true ;
        }
        else {
          /** Case we gather the computer card. **/
          game_control->computer[3].card_is_throw = true ;
        }

      }
      else if ((anim_cards_settings->step == 20) && (anim_cards_settings->card == 6 )) {

        /** The fourth card has reach the throw card frame.
         *  Even from the player or the computer hand first
         *  depending from the value from the boolean variable invert. **/

        anim_cards_settings->card++ ;
        anim_cards_settings->step=0 ;

        anim_cards_settings->cards_number++ ;
        anim_cards_settings->pos_to_fill++  ;

        if (! invert) {
          /** Case we gather the player card. **/
          game_control->computer[3].card_is_throw = true ;
        }
        else {
          /** Case we gather the computer card. **/
          game_control->player[3].card_is_throw   = true ;
        }

      }
      else if ((anim_cards_settings->step == 20) && (anim_cards_settings->card == 7 )) {

        /** The fourth card has reach the throw card frame.
         *  Even from the player or the computer hand first
         *  depending from the value from the boolean variable invert. **/

        anim_cards_settings->card++ ;
        anim_cards_settings->step=0 ;

        *sleep=12500 ;  /** We set the pausing time from the mainloop. **/

        anim_cards_settings->cards_number++ ;

        if (! invert) {
          /** Case we gather the player card. **/
          game_control->player[4].card_is_throw   = true ;
        }
        else {
          /** Case we gather the computer card. **/
          game_control->computer[4].card_is_throw = true ;
        }

      }
      else if ((anim_cards_settings->step == 10) && (anim_cards_settings->card == 8)) {

        /** The fives card has reach the throw card frame.
         *  Even from the player or the computer hand first
         *  depending from the value from the boolean variable invert. **/

        anim_cards_settings->card++ ;
        anim_cards_settings->step=0 ;

        anim_cards_settings->cards_number++ ;
        anim_cards_settings->pos_to_fill++  ;

        if (! invert) {
          /** Case we gather the player card. **/
          game_control->computer[4].card_is_throw = true ;
        }
        else {
          /** Case we gather the computer card. **/
          game_control->player[4].card_is_throw   = true ;
        }

      }
      else if ((anim_cards_settings->step == 10) && (anim_cards_settings->card == 9)) {

        /** The fives card has reach the throw card frame.
         *  Even from the player or the computer hand first
         *  depending from the value from the boolean variable invert. **/


        /** The animation is finish we process the settings. **/
        game_control->GAME_STATUS=PLAYGROUND_CLEAN ;

        anim_cards_settings->card=0 ;
        anim_cards_settings->step=0 ;

        *sleep=10000 ; /** We reset the pausing time from the mainloop on the default value. **/

        anim_cards_settings->cards_number++ ;
      }


  }


  display_throw_cards(pRenderer,card_back_face_texture) ;

  return ;
}

void display_result_text(SDL_Renderer *pRenderer, Text *text, int *sleep, int16_t *counter) {

  /** Display the round winner by blinking the the text during a short time. **/

  if (*counter == 0) {

    /** First time this function is called:
     *  So we initialize the setting for an animation.
     *************************************************/

    game_control->is_animation_running=true ;

    game_control->cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAITARROW) ;
    SDL_SetCursor(game_control->cursor_type)  ;

    *sleep=1500000/3 ;  /** Mainloop pausing time high value needed for blinking. **/

    /** Setting up the text to display in relationship to the round result.
     *  Sea \file ./Utilities/text_utils.c
     **********************************************************************/
    configure_result_text(pRenderer, text, game_control->round_winner) ;

    (*counter) += 2 ;

  }

  if ((*counter) % 2 == 0 && game_control->is_animation_running && (*counter) < 11) {
    render_text(pRenderer, text) ;  /** Render text sea: \file ./Utilities/text_utils.c **/
  }

  (*counter)++ ;

  if (*counter == 13) {

    /** End of the animation: we reset settings. **/


    *sleep=10000 ;
    *counter=0 ;

    game_control->cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW) ;

    SDL_SetCursor(game_control->cursor_type)  ;

    game_control->is_animation_running = false ;

    game_control->GAME_STATUS = UPDATE_SCORE  ;

    return ;

  }

  return ;
}

void display_game_winner_text(SDL_Renderer *pRenderer, Text *text_winner, Text *text_press_ecape, int *sleep, int16_t *counter) {

  /** Display the game winner by blinking the the text as long as the player doesn't return to main screen or quit. **/

  if (*counter == 0) {

    /** First time this function is called:
     *  So we initialize the setting for an animation.
     *************************************************/

    *sleep=1500000/3 ;  /** Mainloop pausing time high value needed for blinking. **/

    /** Setting up the text to display in relationship to the game result.
     *  Sea \file ./Utilities/text_utils.c
     **********************************************************************/
    configure_game_winner_text(pRenderer, text_winner) ;

    configure_game_press_escape_text(pRenderer, text_press_ecape) ;

    buttons[5].is_allowed = false  ;

    (*counter) += 2 ;

    gather_cards(game_control->throw_cards_stack,game_control->player,game_control->computer,game_control->distribute) ;

    return ;

  }

  if ((*counter) % 2 == 0 ) {
    render_text(pRenderer, text_winner)      ;  /** Render text sea: \file ./Utilities/text_utils.c **/
    render_text(pRenderer, text_press_ecape) ;  /** Render text sea: \file ./Utilities/text_utils.c **/
  }

  (*counter)++ ;

  if (*counter == 255) {

    *counter=1 ;

    return ;

  }

  return ;
}