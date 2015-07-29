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

void cards_animation_compute_a_trajectory(Vector positions[],uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint8_t factor) {

  /** Presetting for computing an array of vectors representing the guideline from one card trajectory,
   *  throught the function @compute_steps define in \file ./Utilities/vector.c
   ****************************************************************************************************/

  Vertex *start_vertex = malloc(sizeof(Vertex)) ;
  Vertex *end_vertex   = malloc(sizeof(Vertex)) ;

  start_vertex->x = x_start ;
  start_vertex->y = y_start ;

  end_vertex->x   = x_end   ;
  end_vertex->y   = y_end   ;

  double steps = 10 * factor ;

  compute_steps(positions,start_vertex,end_vertex,steps) ;

  free(start_vertex) ;
  free(end_vertex)   ;

  return ;

}

void distribute_cards_animations_compute_trajectories(Vector positions[10][50],uint8_t invert_order) {

  /** Compute all the trajectories needed for the animation for distributing cards at start.
   *  Even the player or the computer first served throught the invert_order argument value.
   *****************************************************************************************/

  uint8_t multiplier=0, cc=1, c ;


  uint16_t x_end ;
  uint16_t y_end ;

  uint8_t factor=1 ;

  for (c=invert_order ; c < 10+invert_order ; c++) {

    x_end = CARD_BORDER_OFFSET  + (FRAME_Y_TOP_POS * multiplier) + (CARD_WIDTH * multiplier) ;

    if (c % 2 == 0) {
      /** Player get a card.   **/
      y_end = FRAME_Y_BOTTOM_POS + FRAME_CARD_OFFSET ;
    }
    else {
      /** Computer get a card. **/
      y_end = FRAME_Y_TOP_POS    + FRAME_CARD_OFFSET ;
    }
    
    cards_animation_compute_a_trajectory(positions[cc-1], FRAME_X_LEFT_POS + FRAME_CARD_OFFSET , FRAME_Y_MIDDLE_POS + FRAME_CARD_OFFSET , x_end, y_end, factor) ;

    if (cc % 2 == 0) {
      /** Because two distribute cards (player and computer) are on the same x coordinates. **/
      multiplier++ ;
      factor++ ;
    }
    cc++ ;
  }

  return ;
}

void clean_cards_animations_compute_trajectories(Vector positions[10][50],uint8_t invert_order) {

  // To recomment because function copy

  /** Compute all the trajectories needed for the animation for distributing cards at start.
   *  Even the player or the computer first served throught the invert_order argument value.
   *****************************************************************************************/

  uint8_t multiplier=0, cc=1, c ;


  uint16_t x_start ;
  uint16_t y_start ;

  uint8_t factor=5 ;


  for (c=invert_order ; c < 10+invert_order ; c++) {

    x_start = CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * multiplier) + (CARD_WIDTH * multiplier) ;

    if (c % 2 == 0) {
      /** Player card cleaning.   **/
      y_start = FRAME_Y_BOTTOM_POS + FRAME_CARD_OFFSET ;
    }
    else {
      /** Computer card cleaning. **/
      y_start = FRAME_Y_TOP_POS    + FRAME_CARD_OFFSET ;
    }
    
    cards_animation_compute_a_trajectory(positions[cc-1], x_start , y_start , FRAME_X_RIGHT_POS + FRAME_CARD_OFFSET , FRAME_Y_MIDDLE_POS + FRAME_CARD_OFFSET, factor) ;

    if (cc % 2 == 0) {
      /** Because two distribute cards (player and computer) are on the same x coordinates. **/
      multiplier++ ;
      factor-- ;
    }
    cc++ ;
  }

  return ;
}

void computer_new_cards_animations_compute_trajectories(Vector positions[5][50],_Bool invert_order) {

  /** Compute all the trajectories needed for the animation of giving new cards.
   *  Even the player or the computer first served throught the invert_order argument value.
   *****************************************************************************************/

  uint16_t x_end  ;
  uint16_t y_end = (invert_order == false) ? FRAME_Y_BOTTOM_POS + FRAME_CARD_OFFSET : FRAME_Y_TOP_POS + FRAME_CARD_OFFSET  ;

  uint8_t factor=1 ;

  uint8_t c ;

  for (c=0 ; c < 5 ; c++) {

    x_end = CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * c) + (CARD_WIDTH * c) ;

    cards_animation_compute_a_trajectory(positions[c], FRAME_X_LEFT_POS + FRAME_CARD_OFFSET , FRAME_Y_MIDDLE_POS + FRAME_CARD_OFFSET, x_end, y_end,factor) ;
    factor++ ;

  }


}

void computer_throw_cards_animations_compute_trajectories(Vector positions[5][50]) {

  /** Compute all the trajectories needed for the animation of computer throw cards.
   **********************************************************************************/

  uint16_t x_end = FRAME_X_RIGHT_POS  + FRAME_CARD_OFFSET ;

  uint16_t y_end = FRAME_Y_MIDDLE_POS + FRAME_CARD_OFFSET   ;

  uint8_t factor=5 ;

  uint8_t c ;

  for (c=0 ; c < 5 ; c++) {

    cards_animation_compute_a_trajectory(positions[c], CARD_BORDER_OFFSET  + (CARD_CARD_X_OFFSET * c) + (CARD_WIDTH * c), FRAME_Y_TOP_POS + FRAME_CARD_OFFSET, x_end, y_end,factor) ;
    factor-- ;

  }


}