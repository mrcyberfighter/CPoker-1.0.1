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

void configure_bounding_boxes(void) {

  /** Called at start to configure the frames, bounding boxes,
   *  in which the cards are set in the game. And the throw cards heap.
   *  For drag-and-drop, card frame exchange, throw card purpose.
   * ******************************************************************/

  uint8_t c ;

  for (c=0 ; c < 5 ; c++) {
    /** Configure the player cards frames bounding boxes. **/
  
    bounding_boxes[c].x1 = CARD_BORDER_OFFSET + (CARD_CARD_X_OFFSET * c) + (CARD_WIDTH * c) ;
    bounding_boxes[c].y1 = FRAME_Y_BOTTOM_POS ;
  
    bounding_boxes[c].x2 = CARD_BORDER_OFFSET + (CARD_CARD_X_OFFSET * c) + (CARD_WIDTH * c) + CARD_WIDTH ;
    bounding_boxes[c].y2 = FRAME_Y_BOTTOM_POS + FRAME_HEIGHT ;
  }

  /** Configure the cards throw heap frame bounding box. **/
  bounding_boxes[5].x1 = FRAME_X_RIGHT_POS  ;
  bounding_boxes[5].y1 = FRAME_Y_MIDDLE_POS ;

  bounding_boxes[5].x2 = FRAME_X_RIGHT_POS  + FRAME_WIDTH  ;
  bounding_boxes[5].y2 = FRAME_Y_MIDDLE_POS + FRAME_HEIGHT ;

  bounding_boxes[5].is_frame_empty=true ;
  
}

void drag_and_drop_card(SDL_Renderer *pRenderer, int16_t x, int16_t y) {

  /** Display an image from an card by dragging it. With respect of the point where the image is hooked. **/

  SDL_Rect dstrect  ;

  dstrect.x = x - dragging_card->x ;  /** Compute the upper-left X coordinate corner from the dragged image from the image grip point. **/
  dstrect.y = y - dragging_card->y ;  /** Compute the upper-left Y coordinate corner from the dragged image from the image grip point. **/

  dstrect.w=CARD_WIDTH  ;
  dstrect.h=CARD_HEIGHT ;

  SDL_RenderCopy(pRenderer,dragging_card->card->card_image,NULL,&dstrect) ;

  return ;
}

int8_t compute_drop_card(int16_t x, int16_t y) {

  /** Return in which frame the hooked card is release. For dragging or putting down purpose. **/

  uint8_t c ;

  for (c=0 ; c < 5 ; c++) {
  
    if ( (x >= bounding_boxes[c].x1) && (y >= bounding_boxes[c].y1) && (x <=  bounding_boxes[c].x2 ) && (y <= bounding_boxes[c].y2) ) {
      /** The card is release over an player frame. For card place exchange puprpose. **/
      return c+1 ;
    }
  }
    

  if ( (x >= bounding_boxes[5].x1) && (y >= bounding_boxes[5].y1) && (x <=  bounding_boxes[5].x2 ) && (y <= bounding_boxes[5].y2) ) {
   /** The card is release over the card throw frame. **/
   return 6 ;
  }

  return 0 ;  /** **/
}


int8_t mouse_over_card(int16_t mouse_x, int16_t mouse_y) {

  /** Function to detect if the mouse cursor is over an player card which apperance change in case:
   *  @sea:
   *  \file ./SDL2_functions/SDL2_functions.c
   *  @function:get_events(); for further informations about the cursor change.
   ************************************************************************************************/

  uint8_t c ;

  for (c=0 ; c < 5 ; c++) {
    if ( (mouse_x >= bounding_boxes[c].x1) && (mouse_x <= bounding_boxes[c].x2) && (mouse_y >= bounding_boxes[c].y1) && (mouse_y <= bounding_boxes[c].y2) ) {
      return c ;
    }
  
  }

  return -1 ;
}

void exchange_card(Card player[5], Card card1, Card card2) {
  /** Function for exchange 2 cards places on the playground. **/


  Card tmp_card ;

  tmp_card.value = card1.value ;
  tmp_card.type  = card1.type ;
  tmp_card.card_image = card1.card_image ;
  tmp_card.is_moving = false ;
  tmp_card.is_back_faced = card1.is_back_faced ;
  tmp_card.card_is_throw = card1.card_is_throw ;
  /** We invert every setting from the cards except the coordinates and the index: what makes the place exchange.
   * tmp_card.x= card1.x ;
   * tmp_card.y= card1.y ;
   * tmp_card.index =  card1.index ;
   * *******************************/

  card1.value = card2.value ;
  card1.type  = card2.type ;
  card1.card_image = card2.card_image ;
  card1.is_moving = false ;
  card1.is_back_faced = card2.is_back_faced ;
  card1.card_is_throw = card2.card_is_throw ;
  /** We invert every setting from the cards except the coordinates and the index: what makes the place exchange.
   * card1.x = tmp_card.x         ;  is wrong !!!
   * card1.y = tmp_card.y         ;  is wrong !!!
   * card1.index = tmp_card.index ;  is wrong !!!
   * *******************************************/

  card2.value = tmp_card.value ;
  card2.type  = tmp_card.type ;
  card2.card_image = tmp_card.card_image ;
  card2.is_moving = false ;
  card2.is_back_faced = tmp_card.is_back_faced ;
  card2.card_is_throw = tmp_card.card_is_throw ;
  /** We invert every setting from the cards except the coordinates and the index: what makes the place exchange.
   * card2.x= card2.x           ; is wrong !!!
   * card2.y= card2.y           ; is wrong !!!
   * card2.index =  card2.index ; is wrong !!!
   * *****************************************/

  #ifdef DEBUG
    fprintf(stdout,"Card 1 (card to exchange)\n%d of %s\nx %d\ty %d\nindex %d\n-------------------------------------\n",card1.value,"Shamrock",card1.x,card1.y,card1.index) ;
    fprintf(stdout,"Card 2 (card in moving)\n%d of %s\nx %d\ty %d\nindex %d\n-------------------------------------\n",card2.value,"Shamrock",card2.x,card2.y,card2.index) ;
  #endif

  bounding_boxes[card1.index].is_frame_empty = false ;
  bounding_boxes[card2.index].is_frame_empty = false ;  

  player[card1.index]=card1 ;
  player[card2.index]=card2 ;

  return ;

}

void insert_card_in_an_empty_frame(Card player[5], Card card, uint8_t new_index) {

  /** Set card at new index an remove his reference from his previous place.
   *  @note: This can only append if the player has thrown a card so as an frame is empty.
   * *************************************************************************************/

  bounding_boxes[card.index].is_frame_empty=true ;


  uint8_t old_index=card.index ;

  card.is_moving = false ;
  card.x= CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * new_index) + (CARD_WIDTH * new_index) ;
  card.y= FRAME_Y_BOTTOM_POS  + FRAME_CARD_OFFSET  ;
  card.index =  new_index ;

  remove_a_card_from_hand(player,old_index,true) ; /** @sea: at \file ./Utilities/Cards/cards_utils.c **/ 

  player[new_index] = card ;


  bounding_boxes[new_index].is_frame_empty = false ;

  return ;

}
