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

uint8_t check_combination(Card hand[5], Card hand_sorted[5]) {

  /** Return the combination from the card array hand,
   *  hand_sorted is an copy of the array hand but sorted from min to max values.
   ******************************************************************************/

  uint8_t c ;

  uint8_t pos=0 ;

  if (count_card(hand_sorted,0,&pos) == 2) {

      /** Get minimum an PAIR. **/

      /** Mark the cards as component of an combination.      **/
      mark_card_as_part_of_combination(hand, hand_sorted,pos-1) ;
      mark_card_as_part_of_combination(hand, hand_sorted,pos-2) ;

      uint8_t save_pos=pos ;
      if (count_card(hand_sorted,pos,&pos) == 2) {

        /** Get TWO_PAIRS because the pos argument point
         *  on the following index from the first PAIR.
         * ********************************************/

        /** Mark the cards as component of an combination.      **/
        mark_card_as_part_of_combination(hand, hand_sorted,pos-1) ;
        mark_card_as_part_of_combination(hand, hand_sorted,pos-2) ;

        #ifdef DEBUG
          fprintf(stdout,"RETURN TWO_PAIRS\n") ;
        #endif

        return TWO_PAIRS ;
      }
      if (count_card(hand_sorted,save_pos,&pos) == 3) {

        /** Get FULL_HOUSE because the pos argument point
         *  on the following index from the first PAIR.
         * **********************************************/

        /** Mark the cards as component of an combination.      **/
        mark_card_as_part_of_combination(hand, hand_sorted,pos-1) ;
        mark_card_as_part_of_combination(hand, hand_sorted,pos-2) ;
        mark_card_as_part_of_combination(hand, hand_sorted,pos-3) ;

        #ifdef DEBUG
          fprintf(stdout,"RETURN FULL_HOUSE\n") ;
        #endif

        return FULL_HOUSE ;
      }

      #ifdef DEBUG
        fprintf(stdout,"RETURN PAIR\n") ;
      #endif

    return PAIR ;
  }

  pos=0 ;

  if (count_card(hand_sorted,0,&pos) == 3) {

    /** Get minimum an BRELAN. **/

    /** Mark the cards as component of an combination.      **/
    mark_card_as_part_of_combination(hand, hand_sorted,pos-1) ;
    mark_card_as_part_of_combination(hand, hand_sorted,pos-2) ;
    mark_card_as_part_of_combination(hand, hand_sorted,pos-3) ;


    if (pos == 3 ) {
      if (count_card(hand_sorted,3,&pos) == 2) {

        /** Get FULL_HOUSE because the 3 argument point
         *  on the following index from the first BRELAN.
         * **********************************************/

        /** Mark the cards as component of an combination.      **/
        mark_card_as_part_of_combination(hand, hand_sorted,pos-1) ;
        mark_card_as_part_of_combination(hand, hand_sorted,pos-2) ;

        #ifdef DEBUG
          fprintf(stdout,"RETURN FULL_HOUSE\n") ;
        #endif

        return FULL_HOUSE ;
      }
    }

    #ifdef DEBUG
      fprintf(stdout,"RETURN BRELAN\n") ;
    #endif

    return BRELAN ;
  }

  pos=0 ;

  if (count_card(hand_sorted,0,&pos) == 4) {

    /** Get an FOUR. **/

    /** Mark the cards as component of an combination.      **/
    mark_card_as_part_of_combination(hand, hand_sorted,pos-1) ;
    mark_card_as_part_of_combination(hand, hand_sorted,pos-2) ;
    mark_card_as_part_of_combination(hand, hand_sorted,pos-3) ;
    mark_card_as_part_of_combination(hand, hand_sorted,pos-4) ;


    #ifdef DEBUG
      fprintf(stdout,"RETURN FOUR\n") ;
    #endif

    return FOUR ;
  }

  if ( (hand_sorted[0].value) == (hand_sorted[1].value - 1) && (hand_sorted[0].value) == (hand_sorted[2].value - 2) && (hand_sorted[0].value) == (hand_sorted[3].value - 3) && (hand_sorted[0].value) == (hand_sorted[4].value - 4) ) {

    /** Get an QUINTE or an QUINTE_FLUSH or an ROYAL_FLUSH. **/

    /** Mark the cards as component of an combination.  **/
    mark_card_as_part_of_combination(hand, hand_sorted,0) ;
    mark_card_as_part_of_combination(hand, hand_sorted,1) ;
    mark_card_as_part_of_combination(hand, hand_sorted,2) ;
    mark_card_as_part_of_combination(hand, hand_sorted,3) ;
    mark_card_as_part_of_combination(hand, hand_sorted,4) ;

    uint8_t color = hand_sorted[0].type ;
    _Bool flush = true ;

    for (c=1 ; c < 5 ; c++) {
      /** Check if the suite is from the same color. **/
      if (hand_sorted[c].type != color) {
        flush=false ;
        break ;
      }
    }

    if (hand_sorted[4].value == 14 && flush) {

      /** The last card from the sorted array is an AS (value == 14). **/

      #ifdef DEBUG
        fprintf(stdout,"RETURN ROYAL_FLUSH\n") ;
      #endif

      return ROYAL_FLUSH ;
    }
    else if (flush) {

      /** Get an suite from the same color. **/

      #ifdef DEBUG
        fprintf(stdout,"RETURN QUINTE_FLUSH\n") ;
      #endif

      return QUINTE_FLUSH ;
    }

    /** Else get a QUINTE. **/
    #ifdef DEBUG
      fprintf(stdout,"RETURN QUINTE\n") ;
    #endif

    return QUINTE ;

  }


  uint8_t color = hand_sorted[0].type ;
  for (c=1 ; c < 5 ; c++) {
    /** Check if the cards are from the same color. **/
    if (hand_sorted[c].type != color) {
      break ;
    }
    if (hand_sorted[4].type == color && c == 4) {

      #ifdef DEBUG
        fprintf(stdout,"RETURN COLOR\n") ;
      #endif

      /** Get a color. **/

      return COLOR ;
    }

  }


  #ifdef DEBUG
    fprintf(stdout,"RETURN HIGHEST_CARD\n") ;
  #endif

  /** Get no combination. **/

  return HIGHEST_CARD ;
}

void set_cards_to_throw_computer(Card computer[5], _Bool cards_to_throw[5]) {

  /** Compute the cards the computer will throw.
   *  And configure the array cards_to_throw accordingly.
   *  Which represent the index of cards to throw (if value == true)
   *****************************************************************/

  Card hand[5] ;

  sort_cards(computer,hand) ;

  uint8_t combination, c,cc ;


  /** Check if the computer get an combination. **/
  if ( (combination = check_combination(computer,hand)) ) {

    for (c=0 ; c < 5 ; c++) {
      /** Initialize the cards to throw on true. **/
      cards_to_throw[c]=true ;
    }

    if ( (combination == PAIR) || (combination == BRELAN) ) {

      /** The computer has an PAIR or an BRELAN. **/

      uint8_t card_max_value=0   ;  /** Variable to get the maximal value from cards which are not component of an combination for future use. **/
      uint8_t card_to_keep_index ;  /** Varaible for the index of card to keep which are not component of an combination for future use.       **/

      for (c=0 ; c < 5 ; c++) {

    if (! computer[c].part_of_combination && computer[c].value > card_max_value) {
      /** Compute the highest card not part of combination. **/
      card_max_value=computer[c].value ;
      card_to_keep_index=computer[c].index ;
    }
    else if (computer[c].part_of_combination) {
      cards_to_throw[c]=false ;  /** Computer keep this card. **/
        }
      }
      if (card_max_value > 10) {
    /** The computer keep one card if this has an value higher than 10. **/
        cards_to_throw[card_to_keep_index]=false ;
      }
      return ;
    }

    else if (combination == TWO_PAIRS) {

      /** The computer has TWO_PAIRS. **/

      for (c=0 ; c < 5 ; c++) {
    if (computer[c].part_of_combination) {
      cards_to_throw[c]=false ;  /** Computer keep card. **/
    }
    else {
      cards_to_throw[c]=true ;  /** Computer throw card. **/
    }
      }
      return ;
    }

    else if (combination == FOUR) {

      /** The computer has FOUR. **/

      for (c=0 ; c < 5 ; c++) {
    if (computer[c].part_of_combination) {
      cards_to_throw[c]=false ;  /** Computer keep card. **/
    }
    if (! computer[c].part_of_combination && computer[c].value < 11) {
      cards_to_throw[c]=true ;  /** Computer throw card. **/
    }
    else {
      cards_to_throw[c]=false ;  /** Computer keep card. **/
    }
      }
      return ;
    }

    else {
      /** The computer get a QUINTE or COLOR or a FULL_HOUSE or a QUINTE_FLUSH or a ROYAL_FLUSH. **/

      for (c=0 ; c < 5 ; c++) {
    /** The computer throw no cards. **/
    cards_to_throw[c]=false ;
      }
    }

  }
  else {
    /** The computer get NOTHING **/

    uint8_t try_it = get_rand(65536*2) % 2  ;

    for (c=0 ; c < 5 ; c++) {
      cards_to_throw[c]=false ;
    }

    /** But... **/

    if ( (hand[0].value == (hand[1].value-1) &&  hand[0].value == (hand[2].value-2) && hand[0].value == (hand[3].value-3)) && (hand[0].value == 8 || hand[0].value == 9) ) {
      /** Computer as nearly a suite...
       *  it fail an card to get an QUINTE:
       *  an 7, 8, a Queen or a King.
       *  The computer try to get an QUINTE because it suffice to get, one value higher or lower card, for getting a suite.
       ********************************************************************************************************************/

       cards_to_throw[hand[4].index]=true ;
       return ;

    }
    else if ( (hand[1].value == (hand[2].value-1) &&  hand[1].value == (hand[3].value-2) && hand[1].value == (hand[4].value-3)) && (hand[1].value == 8 || hand[1].value == 9) ) {
      /** Computer as nearly a suite...
       *  it fail an card to get an QUINTE:
       *  an 7, 8, a Queen or a King.
       *  The computer try to get an QUINTE because it suffice to get, one value higher or lower card, for getting a suite.
       ********************************************************************************************************************/

       cards_to_throw[hand[0].index]=true ;
       return ;

    }
    else if ( (hand[0].value == (hand[1].value-1) &&  hand[0].value == (hand[2].value-2) && hand[0].value == (hand[3].value-3)) && (hand[0].value == 10) && (try_it == 1) ) {
      /** Computer as nearly a QUNITE with an AS...
       *  it fail an AS card to get an QUINTE with an AS:
       *  to try this is risky so the computer don't try it everytime...
       *  only
       *  if (try_it == 1) ;
       ************************************************************************************/

      cards_to_throw[hand[4].index]=true ;
      return ;

    }
    else if ( (hand[1].value == (hand[2].value-1) &&  hand[1].value == (hand[3].value-2) && hand[1].value == (hand[4].value-3)) && (hand[4].value == 14 || hand[1].value == 10) && (try_it == 1) ) {
      /** Computer as nearly a QUNITE with an AS...
       *  it fail an 10 card to get an QUINTE with an AS:
       *  to try this is risky so the computer don't try it everytime...
       *  only
       *  if (try_it == 1) ;
       ************************************************************************************/

      cards_to_throw[hand[0].index]=true ;
      return ;

    }
    else {

      /** Check if the computer can try to get a color **/
      _Bool try_a_color = false ;

      uint8_t carot = 0 ;
      uint8_t pick  = 0 ;
      uint8_t heart = 0 ;
      uint8_t clubs = 0 ;

      uint8_t color_to_try=255 ;

      /** 0 = Carot ; 1 = Heart ; 2 == Pick ; 3 == Shamrock **/
      for (c=0,cc=0 ; c < 5 ; c++) {
        if (hand[c].type == 0) {
          carot++ ;
        }
        else if (hand[c].type == 1) {
          heart++ ;
        }
        else if (hand[c].type == 2) {
          pick++ ;
        }
        else if (hand[c].type == 3) {
          clubs++ ;
        }
      }

      if (carot == 4) {
        /** It fail a carot card to get a color. **/
        color_to_try=0 ;
        try_a_color = true ;
      }
      else if (heart == 4) {
        /** It fail a carot card to get a color. **/
        color_to_try=1 ;
        try_a_color = true ;
      }
      else if ( pick == 4) {
        /** It fail a carot card to get a color. **/
        color_to_try=2 ;
        try_a_color = true ;
      }
      else if (clubs == 4) {
        /** It fail a carot card to get a color. **/
        color_to_try=3 ;
        try_a_color = true ;
      }

      if (try_a_color) {
        /** So the computer try to get an color. **/
  
        switch (color_to_try) {

          case 0 :
  
            for (c=0 ; c < 5 ; c++) {
              if (computer[c].type != 0) {
            /** This card is not a carot card. **/
            cards_to_throw[c]=true ;
            return ;
              }
            }
  
          case 1 :
  
            for (c=0 ; c < 5 ; c++) {
              if (computer[c].type != 1) {
            /** This card is not a heart card. **/
            cards_to_throw[c]=true ;
            return ;
              }
            }
  
          case 2 :
  
            for (c=0 ; c < 5 ; c++) {
              if (computer[c].type != 2) {
            /** This card is not a pick card. **/
            cards_to_throw[c]=true ;
            return ;
              }
            }
  
          case 3 :
  
            for (c=0 ; c < 5 ; c++) {
              if (computer[c].type != 3) {
            /** This card is not a clubs card. **/
            cards_to_throw[c]=true ;
            return ;
              }
            }
        }
      }

      /** The computer cannot try a color. **/


      /** So the computer throw a random number of cards < 3. **/
      uint8_t number_of_cards_to_keep = get_rand(65536*8) % 3 ;

 
      for (c=0 ; c < 5 ; c++) {
        cards_to_throw[c]=true ;
      }

      for (c=4,cc=0 ; cc < number_of_cards_to_keep ; c--, cc++) {
        /** The computer keep the highest values cards
        *  Because the card in th array hand[5] are sorted from min to max.
        *******************************************************************/

        cards_to_throw[hand[c].index]=false ;
      }

    }

    return ;
  }
}

uint8_t get_highest_card(Card hand[5]) {

  /** Return the highest card value. **/

  uint8_t max_value=0 ;

  uint8_t c ;
  for (c=0 ; c < 5 ; c++) {
    if (hand[c].part_of_combination) {
      if (hand[c].value > max_value) {
        max_value=hand[c].value ;
      }
    }
  }

  return max_value ;
}

uint8_t get_lowest_pair_from_two_pairs(Card hand[5]) {

  /** Return the highest card value. **/

  uint8_t max_value = 0 ;

  uint8_t min_value = 0 ;

  uint8_t c ;

  for (c=0 ; c < 5 ; c++) {
    if (hand[c].part_of_combination) {
      if (hand[c].value > max_value) {
        max_value=hand[c].value ;
      }
    }
  }


  for (c=0 ; c < 5 ; c++) {
    if (hand[c].part_of_combination) {
      if (hand[c].value > min_value && hand[c].value != max_value) {
        min_value=hand[c].value ;
      }
    }
  }

  return min_value ;
}

uint8_t get_rest_highest_card(Card hand[5]) {

  /** Return the highest card value, which is not component of an combination. **/

  uint8_t max_value=0 ;

  uint8_t c ;
  for (c=0 ; c < 5 ; c++) {
    if (! hand[c].part_of_combination) {
      if (hand[c].value > max_value) {
        max_value=hand[c].value ;
      }
    }
  }

  return max_value ;
}

int8_t compare_hands(Card player[5], Card computer[5]) {

  /** Compare cards from player and computer and
   *  Return the highest card.
   *  Used for compare: HIGHEST_CARD, QUINTE, COLOR and QUINTE_FLUSH
   * ***************************************************************/

  uint8_t c ;

  for (c=0 ; c < 5 ; c++) {
    if (player[c].value > computer[c].value) {
      return  1 ;
    }
    else if (player[c].value < computer[c].value) {
      return -1 ;
    }
  }

  return 0 ;
}

int8_t compare_full_house(Card player[5], Card computer[5]) {

  /** Compare 2 FULL_HOUSE **/

  uint8_t player_brelan_value   = 0  ;
  uint8_t computer_brelan_value = 0  ;

  uint8_t player_pair_value   = 0  ;
  uint8_t computer_pair_value = 0  ;

  if (player[0].value == player[1].value && player[1].value == player[2].value) {
    /** The 3 first cards are the brelan from the FULL_HOUSE. **/
    player_brelan_value=player[0].value ;
    player_pair_value=player[3].value   ;
  }
  else if (player[2].value == player[3].value && player[3].value == player[4].value) {
    /** The 2 first cards are the pair from the FULL_HOUSE. **/
    player_brelan_value=player[2].value ;
    player_pair_value=player[0].value   ;
  }

  if (computer[0].value == computer[1].value && computer[1].value == computer[2].value) {
    /** The 3 first cards are the brelan from the FULL_HOUSE. **/
    computer_brelan_value=computer[0].value ;
    computer_pair_value=computer[3].value   ;
  }
  else if (computer[2].value == computer[3].value && computer[3].value == computer[4].value) {
    /** The 2 first cards are the pair from the FULL_HOUSE. **/
    computer_brelan_value=computer[2].value ;
    computer_pair_value=computer[0].value   ;
  }

  if (player_brelan_value > computer_brelan_value) {
    return  1 ;
  }
  else if (player_brelan_value < computer_brelan_value) {
    return -1 ;
  }
  else {
    /** This is impossible that the brelan are the same with an 32 card game. **/
    if (player_pair_value > computer_pair_value) {
      return  1 ;
    }
    else if (player_pair_value < computer_pair_value) {
      return -1 ;
    }
    else {
      return 0  ;
    }
  }

}

int8_t compute_round_winner(Card player[5], Card computer[5]) {

  /** Compare the player and computer hands and return which has the highest combination. **/

  Card player_sorted_cards[5]   ;
  Card computer_sorted_cards[5] ;

  uint8_t player_hand   ;
  uint8_t computer_hand ;

  sort_cards(player,   player_sorted_cards)   ;
  sort_cards(computer, computer_sorted_cards) ;

  player_hand   = check_combination(player,   player_sorted_cards)   ;
  computer_hand = check_combination(computer, computer_sorted_cards) ;

  if (player_hand > computer_hand) {
    return 1  ;
  }
  else if (player_hand < computer_hand) {
    return -1 ;
  }
  else {

    /** Player and computer have the same combination. We process...  **/

    uint8_t hands = player_hand ;

    if (hands == PAIR || hands == BRELAN || hands == FOUR ) {
      if ( get_highest_card(player) > get_highest_card(computer) ) {
        return  1 ;
      }
      else if (get_highest_card(player) < get_highest_card(computer) ) {
        return -1 ;
      }
      else {
  
        /** We compute the resting cards (not from combination) or for making an egality return 0 ; **/
        if ( get_rest_highest_card(player) > get_rest_highest_card(computer) ) {
          return  1 ;
        }
        else if ( get_rest_highest_card(player) < get_rest_highest_card(computer) ) {
          return -1 ;
        }
        else {
          return 0  ;
        }
      }
    }
    else if (hands == TWO_PAIRS) {

      /** We compute the highest PAIR from the TWO_PAIRS ; **/
      if ( get_highest_card(player) > get_highest_card(computer) ) {
        return  1 ;
      }
      else if (get_highest_card(player) < get_highest_card(computer) ) {
        return -1 ;
      }
      else {
  
        /** We compute the two pairs lower pair ; **/
        if (get_lowest_pair_from_two_pairs(player) > get_lowest_pair_from_two_pairs(computer)) {
          return 1 ;
        }
        else if (get_lowest_pair_from_two_pairs(player) < get_lowest_pair_from_two_pairs(computer)) {
          return -1 ;
        }
        else {
          /** We compute the resting cards (not from combination) or for making an egality return 0 ; **/
          if ( get_rest_highest_card(player) > get_rest_highest_card(computer) ) {
            return  1 ;
          }
          else if ( get_rest_highest_card(player) < get_rest_highest_card(computer) ) {
            return -1 ;
          }
          else {
            return 0  ;
          }
        }
      }
    }
    else if (hands == FULL_HOUSE) {
      return compare_full_house(player_sorted_cards, computer_sorted_cards) ;
    }
    else if (hands == HIGHEST_CARD || hands == QUINTE || hands == COLOR || hands == QUINTE_FLUSH) {
      return compare_hands(player_sorted_cards, computer_sorted_cards) ;
    }
    else {
      /** The two players get a ROYAL_FLUSH */
      return 0 ;
    }

  }

}



