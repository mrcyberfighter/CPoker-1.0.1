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

void init_player_cards_position(Card player[5]) {

  /** Unneeded function because the cards coords are set by giving cards. **/

  uint8_t c ;

  for (c=0 ; c < 5 ; c++) {

    player[c].x = CARD_BORDER_OFFSET + (CARD_CARD_X_OFFSET * c) + (CARD_WIDTH * c) ;
    player[c].y = FRAME_Y_BOTTOM_POS + FRAME_CARD_OFFSET  ;

  }

  return ;
}

_Bool generate_card_game(Stack *card_game,const char *color,SDL_Renderer *pRenderer) {

  /** Generate the card game implemented as an Stack (@sea: the \files:./data_structures/>)
   *
   *  for fidelity to the cards games mechanic: an Stack is an FIFO (First In Last Out) structure.
   *  What permit to distribute the cards from the top of the stack into the players hands.
   *
   *  The card game is composed from objects from type Card contains an image texture member representing the card.
   *
   *  @note: The card game is generated ordered and mixed with the mixing algorithmes (@sea: the \file:/Utilities/Cards/cards_mixing.c).
   *************************************************************************************************************************************/

  uint8_t c ;

  for (c=7 ; c < 15 ; c++) {
    /** Iterate on one color in relationship with the color argument. **/

    Card *card = malloc(sizeof(Card)) ;

    char *image_path=calloc(256,sizeof(char)) ;
   
    card->value=c ;  /** Value from the card **/

    card->type= (strcmp(color,"Carot") == 0) ? 0 : (strcmp(color,"Heart") == 0) ? 1 : (strcmp(color,"Pick") == 0) ? 2 : 3 ;
   
    if (c < 11) {
      /** Format an string to get the card image filepath. **/
      sprintf(image_path,"%s%d_%s.png",PATH_TO_CARD_IMAGE,c,color) ;
    }
    else {
      /** Format an string to get the card image filepath. **/
      sprintf(image_path,"%s%s_%s.png",PATH_TO_CARD_IMAGE,(c == 11) ? "Jack" : (c == 12) ? "Queen" : (c == 13) ? "King" : "As",color) ;
    }

    card->card_image=get_texture_from_image(pRenderer,image_path) ; /** Set the card image. **/

    card->is_moving=false    ;

    card->is_back_faced=true ;

    /** Add the card to the card game, by pushing it on the card game stack. **/
    if (stack_push(card_game,card) != 0) {
      return false ;
    }

  }

 return true ;
}

void give_cards(Stack *card_game,Card player[5],Card computer[5],_Bool invert) {

  uint8_t c, cc ;

  cc=0 ;

  for (c=0 ; c < 10 ; c++) {

    Card *card ;

    /** Take a card from the top of the stack. **/
    stack_pop(card_game,(void *) &card) ;

    #ifdef DEBUG
      if (card->value < 11) {
        fprintf(stdout,"%s %d of %s\n",__func__, card->value, (card->type == 0) ? "Carot" : (card->type == 1) ? "Heart" : (card->type == 2) ? "Pick" : (card->type == 3) ? "Clubs" : "No card") ;
      }
      else {
        fprintf(stdout,"%s %s of %s\n",__func__, (card->value == 11) ? "Jack" : (card->value == 12) ? "Queen" : (card->value == 13) ? "King" : "As" ,(card->type == 0) ? "Carot" : (card->type == 1) ? "Heart" : (card->type == 2) ? "Pick" : (card->type == 3) ? "Clubs" : "No card") ;
      }
    #endif


    if ((c+invert) % 2 == 0) { /** The invert value permit to alternate the order from the card distributing. **/
      /** Set the taken card, from the card stack, in the player hand. **/
 
      /** Identify the card internally **/
      player[cc].value = card->value ;
      player[cc].type  = card->type ;
 
      /** Card image. **/
      player[cc].card_image = card->card_image ;
 
      /** Internal used values. **/
      player[cc].is_moving     = false ;
      player[cc].is_back_faced = true  ;
      player[cc].card_is_throw = false ;
 
      /** Coordinates of the card on the playground in relationship to the current card count. **/
      player[cc].x = CARD_BORDER_OFFSET + (CARD_CARD_X_OFFSET * cc) + (CARD_WIDTH * cc) ;
      player[cc].y = FRAME_Y_BOTTOM_POS + FRAME_CARD_OFFSET                             ;
 
      /** Index of the card in the array of the cards from the computer. **/
      player[cc].index =  cc ;
 
      /** Internally used for cards combination identifying like an pair, full house or quinte flush per example. **/
      player[cc].part_of_combination = false ;
 
    }
    else {
      /** Set the taken card, from the card stack, in the computer hand. **/
 
      /** Identify the card internally **/
      computer[cc].value = card->value ;
      computer[cc].type  = card->type ;
 
      /** Card image. **/
      computer[cc].card_image = card->card_image ;
 
      /** Internal used values. **/
      computer[cc].is_moving     = false ;
      computer[cc].is_back_faced = true  ; // Set on false for debugging.
      computer[cc].card_is_throw = false ;
 
      /** Coordinates of the card on the playground in relationship to the current card count. **/
      computer[cc].x = CARD_BORDER_OFFSET + (CARD_CARD_X_OFFSET * cc) + (CARD_WIDTH * cc) ;
      computer[cc].y = FRAME_Y_TOP_POS    + FRAME_CARD_OFFSET                             ;
 
      /** Index of the card in the array of the cards from the computer. **/
      computer[cc].index =  cc ;
 
      /** Internally used for cards combination identifying like an pair, full house or quinte flush per example. **/
      computer[cc].part_of_combination = false ;
 
    }

    if (c % 2 == 1) {
      cc++ ;
    }
  }
}

void throw_a_card(Stack *throw_cards_stack,Card *card) {

  /** Function to throw a card to get a new. **/

  #ifdef DEBUG
    if (card->value < 11) {
      fprintf(stdout,"%s %d of %s\n",__func__,card->value,(card->type == 0) ? "Carot" : (card->type == 1) ? "Heart" : (card->type == 2) ? "Pick" : (card->type == 3) ? "Clubs" : "No card") ;
    }
    else {
      fprintf(stdout,"%s %s of %s\n",__func__,(card->value == 11) ? "Jack" : (card->value == 12) ? "Queen" : (card->value == 13) ? "King" : "As" ,(card->type == 0) ? "Carot" : (card->type == 1) ? "Heart" : (card->type == 2) ? "Pick" : (card->type == 3) ? "Clubs" : "No card") ;
    }
    fprintf(stdout,"%s index of %d",__func__,card->index) ;
  #endif

  Card *card_throw=malloc(sizeof(Card)) ;

  card_throw->value=card->value ;
  card_throw->type=card->type ;

  card_throw->card_image=card->card_image ;

  card_throw->is_moving = false ;

  card_throw->is_back_faced = true ;

  card_throw->x = 0 ;
  card_throw->y = 0 ;

  card_throw->card_is_throw = false ;

  card_throw->index = 0 ;

  card_throw->part_of_combination = false ;


  /** Push the thrown card on the thrown cards stack. **/
  stack_push(throw_cards_stack,card_throw) ;

  if (bounding_boxes[5].is_frame_empty) {
    /** Case this is the first thrown card: we must notifuy it to display an returned card in the thrown cards frame. **/
    bounding_boxes[5].is_frame_empty=false ;
  }
}



void set_throw_cards(Throw_Cards *throw_cards,_Bool index[5]) {

  /** Computer card(s) throw animation settings called after the computer choice the cards to keep
   *  throught configurating the boolean index array:
   *  @sea: the function <set_cards_to_throw_computer> define in \file ./Utilities/Cards/cards_combinations.c
   **********************************************************************************************************/

  uint8_t c ;
  _Bool start=true ;

  throw_cards->number=0 ;

  for (c=0 ; c < 5 ; c++) {
    if (index[c]) {
      throw_cards->number++ ;
    }
    if (index[c] && start) {
      throw_cards->cur_index   = c ;
      throw_cards->start_index = c ;
      start=false ;
    }
    throw_cards->index[c]=index[c] ;
  }

  throw_cards->counter=0   ;
  throw_cards->cur_step=0  ;

  return ;
}

void remove_a_card_from_hand(Card hand[5],uint8_t index,_Bool is_player) {

  /** Remove a card from the player or computer hand by settings following special values to identify the card in not yet in the game. **/

  hand[index].value = -1 ;
  hand[index].type  = -1 ;
  hand[index].card_image = NULL ;
  hand[index].is_moving = false ;
  hand[index].is_back_faced = true ;
  hand[index].x= 0 ;
  hand[index].y= 0 ;
  hand[index].index = index ;

  hand[index].card_is_throw = true ;

  if (is_player) {
    bounding_boxes[index].is_frame_empty=true ; /** Mark the frame as empty for cards place changing purpose. **/
  }

  return ;
}

void set_cards_to_give_new(Give_New_Cards_Animation *new_cards, Card cards[5]) {

  /** Give new cards animation settings configuration function **/

  uint8_t c ;

  _Bool start=true ;

  new_cards->number=0 ;

  for (c=0 ; c < 5 ; c++) {
    /** Initialise the array. **/
    new_cards->index[c]=false ;
  }

  for (c=0; c < 5 ; c++) {
    if (cards[c].card_is_throw) {
      new_cards->index[c]=true ;
      new_cards->number++ ;
    }
    if ( cards[c].card_is_throw &&  start ) {
      new_cards->start_index=c ;
      new_cards->cur_index=c ;
      start=false ;
    }
  }

  new_cards->counter=0   ;
  new_cards->cur_step=0 ;
}

void give_new_cards(void) {

  /** Internally (not animation) give new cards. **/

  if (! game_control->distribute) {

    /** The player is served first. **/

    uint8_t c ;

    for ( c=0 ; c < 5 ; c++) {
 
      if (give_new_cards_player->index[c] == true) {
   
        Card *card ;
   
        int ret ;
   
        ret = stack_pop(game_control->card_game,(void *) &card) ; /** Take a card from the card game. **/
   
        while ( ret != 0) {
          /** This should not append.  **/
          ret = stack_pop(game_control->card_game,(void *) &card) ;
        }
   
        /** Give the taken card to the player.
         * @Note: The other members from the card are set otherwhere.
         *        In the give new cards animation.                    */
        game_control->player[c].value               = card->value      ;
        game_control->player[c].type                = card->type       ; /** 0 = Carot ; 1 = Heart ; 2 == Pick ; 3 == Clubs **/
        game_control->player[c].card_image          = card->card_image ;
        game_control->player[c].index               = c                ;
        game_control->player[c].part_of_combination = false            ;
   
   
        #ifdef DEBUG
          if (game_control->player[c].value < 11) {
            fprintf(stdout,"%s %d of %s\n",__func__,game_control->player[c].value,(game_control->player[c].type == 0) ? "Carot" : (game_control->player[c].type == 1) ? "Heart" : (game_control->player[c].type == 2) ? "Pick" : (game_control->player[c].type == 3) ? "Clubs" : "No card") ;
          }
          else {
            fprintf(stdout,"%s %s of %s\n",__func__,(game_control->player[c].value == 11) ? "Jack" : (game_control->player[c].value == 12) ? "Queen" : (game_control->player[c].value == 13) ? "King" : (game_control->player[c].value == 14) ? "As" : "No Card",(game_control->player[c].type == 0) ? "Carot" : (game_control->player[c].type == 1) ? "Heart" : (game_control->player[c].type == 2) ? "Pick" : (game_control->player[c].type == 3) ? "Clubs" : "No card") ;
          }
        #endif
   
      }
    }

    /** The computer is served next. **/

    for ( c=0 ; c < 5 ; c++) {
 
      if (give_new_cards_computer->index[c] == true) {
   
        Card *card ;
   
        int ret ;
   
        ret = stack_pop(game_control->card_game,(void *) &card) ;  /** Take a card from the card game. **/
   
        while ( ret != 0) {
          /** This should not append.  **/
          ret = stack_pop(game_control->card_game,(void *) &card) ;
        }
   
        /** Give the taken card to the computer.
         *  @Note: The other members from the card are set otherwhere.
         *         In the give new cards animation.                     */
        game_control->computer[c].value               = card->value      ;
        game_control->computer[c].type                = card->type       ; /** 0 = Carot ; 1 = Heart ; 2 == Pick ; 3 == Clubs **/
        game_control->computer[c].card_image          = card->card_image ;
        game_control->computer[c].index               = c                ;
        game_control->computer[c].part_of_combination = false            ;
   
         #ifdef DEBUG
          if (game_control->computer[c].value < 11) {
            fprintf(stdout,"%s %d of %s\n",__func__,game_control->computer[c].value,(game_control->computer[c].type == 0) ? "Carot" : (game_control->computer[c].type == 1) ? "Heart" : (game_control->computer[c].type == 2) ? "Pick" : (game_control->computer[c].type == 3) ? "Clubs" : "No card") ;
          }
          else {
            fprintf(stdout,"%s %s of %s\n",__func__,(game_control->computer[c].value == 11) ? "Jack" : (game_control->computer[c].value == 12) ? "Queen" : (game_control->computer[c].value == 13) ? "King" : (game_control->computer[c].value == 14) ? "As" : "No Card",(game_control->computer[c].type == 0) ? "Carot" : (game_control->computer[c].type == 1) ? "Heart" : (game_control->computer[c].type == 2) ? "Pick" : (game_control->computer[c].type == 3) ? "Clubs" : "No card") ;
          }
         #endif
    
      }
    }

  }
  else {

    /** The computer is served first. **/

    uint8_t c ;

    for ( c=0 ; c < 5 ; c++) {
 
      if (give_new_cards_computer->index[c] == true) {
   
        Card *card ;
   
        int ret ;
   
        ret = stack_pop(game_control->card_game,(void *) &card) ;  /** Take a card from the card game. **/
   
        while ( ret != 0) {
          /** This should not append.  **/
          ret = stack_pop(game_control->card_game,(void *) &card) ;
        }
   
        /** Give the taken card to the computer.
         *  @Note: The other members from the card are set otherwhere.
         *         In the give new cards animation.                     */
        game_control->computer[c].value               = card->value      ;
        game_control->computer[c].type                = card->type       ; /** 0 = Carot ; 1 = Heart ; 2 == Pick ; 3 == Clubs **/
        game_control->computer[c].card_image          = card->card_image ;
        game_control->computer[c].index               = c                ;
        game_control->computer[c].part_of_combination = false            ;
   
   
        #ifdef DEBUG
          if (game_control->computer[c].value < 11) {
            fprintf(stdout,"%s %d of %s\n",__func__,game_control->computer[c].value,(game_control->computer[c].type == 0) ? "Carot" : (game_control->computer[c].type == 1) ? "Heart" : (game_control->computer[c].type == 2) ? "Pick" : (game_control->computer[c].type == 3) ? "Clubs" : "No card") ;
          }
          else {
            fprintf(stdout,"%s %s of %s\n",__func__,(game_control->computer[c].value == 11) ? "Jack" : (game_control->computer[c].value == 12) ? "Queen" : (game_control->computer[c].value == 13) ? "King" : (game_control->computer[c].value == 14) ? "As" : "No Card",(game_control->computer[c].type == 0) ? "Carot" : (game_control->computer[c].type == 1) ? "Heart" : (game_control->computer[c].type == 2) ? "Pick" : (game_control->computer[c].type == 3) ? "Clubs" : "No card") ;
          }
         #endif
   
      }
    }

    for ( c=0 ; c < 5 ; c++) {
 
      if (give_new_cards_player->index[c] == true) {
   
        Card *card ;
   
        int ret ;
   
        ret = stack_pop(game_control->card_game,(void *) &card) ;  /** Take a card from the card game. **/
   
        while ( ret != 0) {
          /** This should not append.  **/
          ret = stack_pop(game_control->card_game,(void *) &card) ;
        }
   
        /** Give the taken card to the player.
         * @Note: The other members from the card are set otherwhere.
         *        In the give new cards animation.                    */
        game_control->player[c].value               = card->value      ;
        game_control->player[c].type                = card->type       ;  /** 0 = Carot ; 1 = Heart ; 2 == Pick ; 3 == Clubs **/
        game_control->player[c].card_image          = card->card_image ;
        game_control->player[c].index               = c                ;
        game_control->player[c].part_of_combination = false            ;
   
   
        #ifdef DEBUG
          if (game_control->player[c].value < 11) {
            fprintf(stdout,"%s %d of %s\n",__func__,game_control->player[c].value,(game_control->player[c].type == 0) ? "Carot" : (game_control->player[c].type == 1) ? "Heart" : (game_control->player[c].type == 2) ? "Pick" : (game_control->player[c].type == 3) ? "Clubs" : "No card") ;
          }
          else {
            fprintf(stdout,"%s %s of %s\n",__func__,(game_control->player[c].value == 11) ? "Jack" : (game_control->player[c].value == 12) ? "Queen" : (game_control->player[c].value == 13) ? "King" : (game_control->player[c].value == 14) ? "As" : "No Card",(game_control->player[c].type == 0) ? "Carot" : (game_control->player[c].type == 1) ? "Heart" : (game_control->player[c].type == 2) ? "Pick" : (game_control->player[c].type == 3) ? "Clubs" : "No card") ;
          }
        #endif
   
      }
    }

  }

  return ;
}

_Bool game_done(Card player[5], Card computer[5]) {

  /** Check if all cards are returned to process at round winner computing. **/

  uint8_t c ;


  for (c=0 ; c < 5 ; c++) {
    if (computer[c].is_back_faced) {
      return false ;
    }
  }

  for (c=0 ; c < 5 ; c++) {
    if (player[c].is_back_faced) {
      return false ;
    }
  }

  return true ;

}

void sort_cards(Card cards_to_sort[5], Card cards_sorted[5]) {
  /** Card sorting algorithme for easier further combinations identification. **/

  uint8_t c ;

  for (c=0 ; c < 5 ; c++) {
    Card card ;

    if (cards_to_sort[c].value == -1) {
      card.value = 127 ;
      card.type  = 127 ;
    }
    else {
      card.value = cards_to_sort[c].value ;
      card.type  = cards_to_sort[c].type ;
    }
    card.card_image = cards_to_sort[c].card_image ;
    card.is_moving = false ;
    card.is_back_faced = cards_to_sort[c].is_back_faced ;
    card.card_is_throw = cards_to_sort[c].card_is_throw ;
    card.x= cards_to_sort[c].x ;
    card.y= cards_to_sort[c].y ;
    card.index =  cards_to_sort[c].index ;

    cards_sorted[c]=card ;
  }

  int8_t pos_min  ;  // index from the found value
  int8_t idx_sort ;  // index from the not sorted table part
  int8_t min_val  ;  // next value

  c=0 ;

  while ( c < 5) {
    min_val=cards_sorted[c].value ;
    pos_min=c ;
    idx_sort=c ;
    while (idx_sort < 5) {
      /** search the littles value in the not sorted part of the table **/
      if ( cards_sorted[idx_sort].value < min_val && cards_sorted[idx_sort].value != -1 ) {
        /** littles value found **/
        min_val=cards_sorted[idx_sort].value ; /** Store the table minimal value from his not sorted part **/
        pos_min=idx_sort ;                     /** Store the table minimal value index from the not sorted part of the table **/
      }
      idx_sort++ ;
    }

    /** Exchange the cards **/
    Card tmp ;
    tmp=cards_sorted[pos_min] ;
    cards_sorted[pos_min]=cards_sorted[c] ;
    cards_sorted[c]=tmp ;
    c++ ;
  }

  return ;
}

uint8_t count_card(Card hand[5],uint8_t start_count,uint8_t *pos) {

  /** Card counting algorithme for easier further combinations identification. **/

  /** It count cards from the same value.
   *  The array hand is an sorted array.
   *************************************/

  uint8_t c, counter ;

  counter=1 ;

  _Bool set_counter = false ;

  /** Take attention at the count start index **/
  for (c=start_count ; c < 5 ; c++) {

    uint8_t cc ;

    int8_t val_card ;

    if (hand[c].value == -1) {
      continue ;
    }

    if (set_counter == false) {
 
      /** to not count 2 differents combination like in an full house (an pair and an brelan). **/
 
      val_card=hand[c].value ; /** value to compare. **/
    }

    for (cc=c+1 ; cc < 5 ; cc++) {
 
      if (hand[cc].value == val_card) {
        /** The card value match. **/
   
        counter++ ;
   
        set_counter=true ;  /** So we get 2 cards from the same value. **/
   
        c++ ;
   
        *pos=cc+1 ; /** We must keep the position for combinations which required more than one count. **/
   
      }
    }

  }

  return counter ;
}

void mark_card_as_part_of_combination(Card computer[5],Card hand[5], uint8_t index) {

  /** Internal used for the combinations identification. **/
  computer[hand[index].index].part_of_combination = true ;

  return ;

}

void gather_cards(Stack *throw_cards_stack, Card player[5], Card computer[5], uint8_t invert) {

  /** Internally function (not animation) to gather the cards wenn the round or the game is over.
   *  -) We throw all the cards from the player and the computer. *
   *  -) We pop every card from the trhow stack to insert it in the card game stack.
   * ********************************************************************************************/

  uint8_t c, cc, counter ;

  counter=0 ;

  for (c=invert, cc=0 ; c < (10+invert) ; c++) {
    /** We throw all the cards from theplayer and the computer. **/

    if (c % 2 == 0) {
      throw_a_card(throw_cards_stack, &player[cc]) ;
      remove_a_card_from_hand(game_control->player, player[cc].index,true) ;
    }
    else {
      throw_a_card(throw_cards_stack,&computer[cc]) ;
      remove_a_card_from_hand(game_control->computer, computer[cc].index,false) ;
    }

    if (counter % 2 == 1) {
      cc++ ;
    }
    counter++ ;
  }

  cc=stack_size(throw_cards_stack) ;

  for (c=0 ; c < cc ; c++) {
    /** We take all the cards from the throw stack to reinsert it in the game at the end of it. **/

    Card *card = malloc(sizeof(Card)) ;

    /** Pop a card from the throw stack. **/
    if (stack_pop(throw_cards_stack,(void *) &card) != 0) {
      /** This should not append. **/
      exit(EXIT_FAILURE) ;
    }

    /** Reinsert card in the game. **/
    if (list_insert_next((List *) game_control->card_game, list_tail(game_control->card_game),card) != 0) {
      /** This should not append. **/
      exit(EXIT_FAILURE) ;
    }
  }

}


