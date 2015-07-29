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

void display_player_cards_frames(SDL_Renderer *pRenderer,SDL_Texture *frame_texture) {

  /** Function for displaying the cards frames from the player.
   *  @note: used by every mainloop iteration.
   *******************************************/

  uint8_t c ;

  for (c=0 ; c < 5 ; c++) {
 
    display_image(pRenderer,
                  frame_texture,
                  CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * c) + (CARD_WIDTH * c) - FRAME_CARD_OFFSET ,  /** Computing the x position (top-left corner) for the current frame. **/
                  FRAME_Y_BOTTOM_POS,                                                 /** Setting the y position (top-left corner) for every frame.         **/
                  FRAME_WIDTH,
                  FRAME_HEIGHT) ;
 
    #ifdef DEBUG
      if (c == 0 || c == 4) {
        fprintf(stdout,"card start: ( %d ) end: ( %d )\n",CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * c) + (CARD_WIDTH * c), CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * c) + (CARD_WIDTH * c) + CARD_WIDTH) ;
      }
    #endif
 
  }

  return ;
}

void display_computer_cards_frames(SDL_Renderer *pRenderer,SDL_Texture *frame_texture) {

  /** Function for displaying the cards frames from the computer.
   *  @note: used by every mainloop iteration.
   *******************************************/

  uint8_t c ;

  for (c=0 ; c < 5 ; c++) {
 
    display_image(pRenderer,
                  frame_texture,
                  CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * c) + (CARD_WIDTH * c) - FRAME_CARD_OFFSET,  /** Computing the x position (top-left corner) for the current card. **/
                  FRAME_Y_TOP_POS,                                                    /** Setting the y position (top-left corner) for every card.         **/
                  FRAME_WIDTH,
                  FRAME_HEIGHT) ;
 
    #ifdef DEBUG
      if (c == 0 || c == 4) {
        fprintf(stdout,"card start: ( %d ) end: ( %d )\n",CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * c) + (CARD_WIDTH * c),CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * c) + (CARD_WIDTH * c) + 97) ;
      }
   #endif

  }

  return ;
}


void display_cards_from_player(SDL_Renderer *pRenderer,SDL_Texture *card_back_face_texture,Card player[5]) {

  /** Function to display the player cards event if they are not returned.
   * Except at game start wenn all cards from the player are not returned.
   * It would be better if this function handle this case but it isn't. (Sorry)
   * **************************************************************************/

  uint8_t c ;

  for (c=0 ; c < 5 ; c++) {
 
    SDL_Rect dstrect  ;
 
    dstrect.x = player[c].x ;
    dstrect.y = player[c].y ;
    dstrect.w = CARD_WIDTH  ;
    dstrect.h = CARD_HEIGHT ;
 
    if (player[c].is_back_faced && ! player[c].is_moving && ! player[c].card_is_throw) {
      /** The card is not returned. **/
      SDL_RenderCopy(pRenderer,
                     card_back_face_texture,
                     NULL,
                     &dstrect) ;
    }
    else if ( ! player[c].is_back_faced && ! player[c].is_moving && ! player[c].card_is_throw) {
      /** The card present his color and value. **/
      SDL_RenderCopy(pRenderer,
                     player[c].card_image,
                     NULL,
                     &dstrect) ;
    }
 
    #ifdef DEDUG
      if (c == 0 || c == 4) {
        fprintf(stdout,"card start: ( %d, %d ) end: ( %d, %d)\n",dstrect.x,dstrect.y,dstrect.x+CARD_WIDTH,dstrect.y+CARD_HEIGHT) ;
      }
    #endif
 
  }

  return ;

}
 
 
void display_cards_from_computer(SDL_Renderer *pRenderer,SDL_Texture *card_back_face_texture,Card computer[5]) {

  /** Function to display the computer cards.
   * Except at game start wenn all cards from the player are not returned.
   * It would be better if this function handle this case but it isn't. (Sorry)
   * **************************************************************************/

  uint8_t c ;

  for (c=0 ; c < 5 ; c++) {
 
    SDL_Rect dstrect  ;
 
    dstrect.x = computer[c].x ;
    dstrect.y = computer[c].y ;
    dstrect.w = CARD_WIDTH  ;
    dstrect.h = CARD_HEIGHT ;
 
    if (computer[c].is_back_faced && ! computer[c].is_moving && ! computer[c].card_is_throw) {
      /** The card is not returned. **/
      SDL_RenderCopy(pRenderer,
                     card_back_face_texture,
                     NULL,
                     &dstrect) ;
                
    }
    else if ( ! computer[c].is_back_faced && ! computer[c].is_moving && ! computer[c].card_is_throw) {
      /** The card present his color and value. **/
      SDL_RenderCopy(pRenderer,
                     computer[c].card_image,
                     NULL,
                     &dstrect) ;
                  
    }
      #ifdef DEBUG
        if (c == 0 || c == 4) {
          fprintf(stdout,"card start: ( %d, %d ) end: ( %d, %d) at %p\n",dstrect.x,dstrect.y,dstrect.x+CARD_WIDTH,dstrect.y+CARD_HEIGHT,computer[c].card_image) ;
        }
      #endif

  }

  return ;

}

void display_throw_cards(SDL_Renderer *pRenderer,SDL_Texture *card_back_face_texture) {

  /** display an returned card texture for representing the throw cards heap. **/

  if (! bounding_boxes[5].is_frame_empty) {
    display_image(pRenderer, card_back_face_texture, FRAME_X_RIGHT_POS + FRAME_CARD_OFFSET ,FRAME_Y_MIDDLE_POS + FRAME_CARD_OFFSET, CARD_WIDTH, CARD_HEIGHT) ;
  }

  return ;
}

void display_back_face_card(SDL_Renderer *pRenderer, SDL_Texture *card_back_face_texture, uint8_t pos,uint8_t number_of_cards,_Bool invert) {

  /** Function used for displaying cards by the distributing animation wenn they reach their destination (in the cards frames).
   *  And wenn all cards are cover.
   * **************************************************************************************************************************/

  uint8_t c ;

  if (pos < 0) {
    return ;
  }

  if (number_of_cards % 2 == 0) {
    /** Actually the player and the computer have the same number of cards in their frame. **/
    for (c=0 ; c < pos ; c++) {
  
      display_image(pRenderer,
                    card_back_face_texture, 
                    CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * c) + (CARD_WIDTH * c) ,
                    FRAME_Y_BOTTOM_POS + FRAME_CARD_OFFSET ,
                    CARD_WIDTH,
                    CARD_HEIGHT) ;
                
      display_image(pRenderer,
                    card_back_face_texture, 
                    CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * c) + (CARD_WIDTH * c) ,
                    FRAME_Y_TOP_POS + FRAME_CARD_OFFSET ,
                    CARD_WIDTH,
                    CARD_HEIGHT) ;
                
    }
 
  }
  else {
 
    if ( ! invert ) {
 
      for (c=0 ; c < pos ; c++) {
   
        display_image(pRenderer,
                      card_back_face_texture, 
                      CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * c) + (CARD_WIDTH * c) ,
                      FRAME_Y_BOTTOM_POS + FRAME_CARD_OFFSET ,
                      CARD_WIDTH,
                      CARD_HEIGHT) ;
   
        if (c == pos-1) {
          /** Actually the player and the computer have not the same number of cards in their frame,
           *  and the computer have more cards.
            ************************************/
          break ;
        }
   
        display_image(pRenderer,
                      card_back_face_texture, 
                      CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * c) + (CARD_WIDTH * c) ,
                      FRAME_Y_TOP_POS + FRAME_CARD_OFFSET ,
                      CARD_WIDTH,
                      CARD_HEIGHT) ;
      }
   }
   else {
     for (c=0 ; c < pos ; c++) {
   
        display_image(pRenderer,
                      card_back_face_texture, 
                      CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * c) + (CARD_WIDTH * c) ,
                      FRAME_Y_TOP_POS + FRAME_CARD_OFFSET,
                      CARD_WIDTH,
                      CARD_HEIGHT) ;

        if (c == pos-1) {
          /** Actually the player and the computer have not the same number of cards in their frame,
           *  and the player have more cards.
            **********************************/
          break ;
        }

        display_image(pRenderer,
                      card_back_face_texture, 
                      CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * c) + (CARD_WIDTH * c) ,
                      FRAME_Y_BOTTOM_POS + FRAME_CARD_OFFSET ,
                      CARD_WIDTH,
                      CARD_HEIGHT) ;
   
   
      }
   }


  }

  return ;
}