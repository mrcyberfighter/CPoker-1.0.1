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

int get_rand(int modulo) {

  /** Simply random function. **/

  struct timeval tv ;
  gettimeofday(&tv,NULL) ;

  srand((unsigned int) tv.tv_usec) ;

  return (int) ((rand() % modulo) < 0) ? 0 : (rand() % modulo) ;
}

void reinsert_card_in_game(List *card_game, Card *card_datas) {

  int c = 0 ;

  ListElt *insert_after = list_head(card_game) ;

  while (list_insert_next(card_game, insert_after, card_datas) != 0) {

    c++ ;

    if (c == 31) {
      insert_after = list_head(card_game) ;
      c=0 ;
    }

    insert_after = list_next(insert_after) ;
 }

 return ;

}

void mix_card_game_classic(Stack *card_game) {

  /** Mix the card game by taken an random card from the game and reinsert in the game at an random position. **/

  int c ;

  for (c=0 ; c < 32 ; c++) {


     int cc ;
     uint8_t get_cards ;


     ListElt *card_to_rm  = list_head(card_game) ;
     ListElt *card_to_add = list_head(card_game) ;

     /** Compute an random card taking position. **/

     get_cards=get_rand(32) ;

     while (get_cards == 0) {
         get_cards=get_rand(32) ;
     }

     for (cc=0 ; cc < get_cards ; cc++ ) {
        card_to_rm=list_next(card_to_rm) ;
     }

     /** Taken one card from the game. **/
     Card *card_datas = malloc(sizeof(Card)) ;
     if (list_remove_next((List *) card_game,card_to_rm,(void *) &card_datas) !=  0) {
       /** This should never append. **/
       continue ;
     }

     usleep(get_rand(25)) ;  /** For random utils. **/

     /** Compute an random insert position. **/

     get_cards=get_rand(32) ;

     while (get_cards == 0) {
         get_cards=get_rand(32) ;
     }

     for (cc=0 ; cc < get_cards ; cc++ ) {
        card_to_add=list_next(card_to_add) ;
     }

     if (list_insert_next((List *) card_game,card_to_add,card_datas) != 0) {
       /** This should never append. **/
       reinsert_card_in_game((List *) card_game, card_datas) ;
     }
 
     usleep(get_rand(25)) ; /** For random utils. **/

  }

  return ;
}

void mix_card_game_heaps(Stack *card_game) {

  /** Mix algorithm which construct 5 cards heaps randomly and push it in an different order to reconstruct the card game. **/

  Queue mix_heaps[5] ;

  uint8_t c  ;

  uint8_t sum=0 ;

  uint8_t sizes[5] ;

  for (c=0 ; c < 5 ; c++) {
    init_queue(&mix_heaps[c],NULL) ;
  }


  for (c=0 ; c < 5 ; c++) {

    int cc, limit ;

    if (c != 4) {
      limit=get_rand(8) ;
    }
    else {
      limit= (32-sum < 0) ? 0 : 32-sum ;
    }

    if (limit == 0 && c != 4) {
      limit=2 ;
    }

    sizes[c]=limit ;

    sum += limit ;



    for (cc=0 ; cc < limit ; cc++) {

      Card *card = malloc(sizeof(Card)) ;

      /** Take a card from the card game. **/
      if (stack_pop(card_game,(void *) &card) != 0) {
	/** This should not append. **/
	continue ;
      }

      /** Push the taken card on the current stack. **/
      enqueue(&mix_heaps[c],card) ;

    }
    usleep(get_rand(55)) ;
  }



  for (c=0 ; c < sizes[4] ; c++) {
    /** Flush the heap 5 and put it content inn the card game. **/

    Card *card ;

    /** Take a card from the heap. **/
    dequeue(&mix_heaps[4],(void *) &card) ;

    #ifdef DEBUG
      if (card->value < 11) {
       fprintf(stdout,"%s %d of %s\n",__func__,card->value,(card->type == 0) ? "Carot" : (card->type == 1) ? "Heart" : (card->type == 2) ? "Pick" : "Shamrock") ;
      }
      else {
        fprintf(stdout,"%s %s of %s\n",__func__,(card->value == 11) ? "Jack" : (card->value == 12) ? "Queen" : (card->value == 13) ? "King" : "As" ,(card->type == 0) ? "Carot" : (card->type == 1) ? "Heart" : (card->type == 2) ? "Pick" : "Shamrock") ;
      }
    #endif

    /** Set card in the game. **/
    stack_push(card_game,card) ;

  }

  for (c=0 ; c < sizes[2] ; c++) {
    /** Flush the heap 3 and put it content inn the card game. **/

    Card *card ;

    /** Take a card from the heap. **/
    dequeue(&mix_heaps[2],(void *) &card) ;

    #ifdef DEBUG
      if (card->value < 11) {
       fprintf(stdout,"%s %d of %s\n",__func__,card->value,(card->type == 0) ? "Carot" : (card->type == 1) ? "Heart" : (card->type == 2) ? "Pick" : "Shamrock") ;
      }
      else {
        fprintf(stdout,"%s %s of %s\n",__func__,(card->value == 11) ? "Jack" : (card->value == 12) ? "Queen" : (card->value == 13) ? "King" : "As" ,(card->type == 0) ? "Carot" : (card->type == 1) ? "Heart" : (card->type == 2) ? "Pick" : "Shamrock") ;
      }
    #endif

    /** Set the card in the game. **/
    stack_push(card_game,card) ;

  }

  for (c=0 ; c < sizes[0] ; c++) {
    /** Flush the heap 1 and put it content inn the card game. **/

    Card *card ;

    /** Take a card from the heap. **/
    dequeue(&mix_heaps[0],(void *) &card) ;

    #ifdef DEBUG
      if (card->value < 11) {
       fprintf(stdout,"%s %d of %s\n",__func__,card->value,(card->type == 0) ? "Carot" : (card->type == 1) ? "Heart" : (card->type == 2) ? "Pick" : "Shamrock") ;
      }
      else {
        fprintf(stdout,"%s %s of %s\n",__func__,(card->value == 11) ? "Jack" : (card->value == 12) ? "Queen" : (card->value == 13) ? "King" : "As" ,(card->type == 0) ? "Carot" : (card->type == 1) ? "Heart" : (card->type == 2) ? "Pick" : "Shamrock") ;
      }
    #endif

    /** Set card in the game. **/
    stack_push(card_game,card) ;

  }

  for (c=0 ; c < sizes[3] ; c++) {
    /** Flush the heap 4 and put it content inn the card game. **/

    Card *card ;

    /** Take a card from the heap. **/
    dequeue(&mix_heaps[3],(void *) &card) ;

    #ifdef DEBUG
      if (card->value < 11) {
       fprintf(stdout,"%s %d of %s\n",__func__,card->value,(card->type == 0) ? "Carot" : (card->type == 1) ? "Heart" : (card->type == 2) ? "Pick" : "Shamrock") ;
      }
      else {
        fprintf(stdout,"%s %s of %s\n",__func__,(card->value == 11) ? "Jack" : (card->value == 12) ? "Queen" : (card->value == 13) ? "King" : "As" ,(card->type == 0) ? "Carot" : (card->type == 1) ? "Heart" : (card->type == 2) ? "Pick" : "Shamrock") ;
      }
    #endif

    /** Set the card in the game. **/
    stack_push(card_game,card) ;

  }

  for (c=0 ; c < sizes[1] ; c++) {
    /** Flush the heap 2 and put it content inn the card game. **/
    Card *card ;

    /** Take a card from the heap. **/
    dequeue(&mix_heaps[1],(void *) &card) ;

    #ifdef DEBUG
      if (card->value < 11) {
       fprintf(stdout,"%s %d of %s\n",__func__,card->value,(card->type == 0) ? "Carot" : (card->type == 1) ? "Heart" : (card->type == 2) ? "Pick" : "Shamrock") ;
      }
      else {
        fprintf(stdout,"%s %s of %s\n",__func__,(card->value == 11) ? "Jack" : (card->value == 12) ? "Queen" : (card->value == 13) ? "King" : "As" ,(card->type == 0) ? "Carot" : (card->type == 1) ? "Heart" : (card->type == 2) ? "Pick" : "Shamrock") ;
      }
    #endif

    /** Set the card in the game. **/
    stack_push(card_game,card) ;

  }

  return ;
}

void mix_card_game_alternate(Stack *card_game) {

  /** Mix algorithm wich construct 2 heaps from the card game
   *  and alterantively take an card from an heap, and put it in the card game.
   ****************************************************************************/

  Queue *half_game_1 = malloc(sizeof(Queue)) ;
  Queue *half_game_2 = malloc(sizeof(Queue)) ;

  init_queue(half_game_1,NULL) ;
  init_queue(half_game_2,NULL) ;

  uint8_t c ;

  for (c=0 ; c < 32 ; c++) {
    /** Loop to construct the two heaps. **/
    Card *card ;

    /** Take an card from the card game. **/
    stack_pop(card_game,(void *) &card) ;

    if (c % 2 == 0) {
      /** push the card on the first heap. **/
      enqueue(half_game_1,card) ;
    }
    else {
      /** push the card on the second heap. **/
      enqueue(half_game_2,card) ;
    }
  }


  for (c=0 ; c < 32 ; c++) {
    Card *card ;

    if (c % 2 == 0) {
      /** Take a card from the heap one. **/
      dequeue(half_game_2,(void *) &card) ;
    }
    else {
      /** Take a card from the heap two. **/
      dequeue(half_game_1,(void *) &card) ;
    }

    /** Push the card on the card game. **/
    stack_push(card_game,card) ;
  }

  free(half_game_1) ;
  free(half_game_2) ;

  return ;
}


void mix_card(void) {

  /** Cards mix algorithmes **/
  uint8_t mix_times, c ;

  mix_times=get_rand(25)  ;

  for (c=0 ; c < mix_times ; c++) {
    mix_card_game_classic(game_control->card_game) ;
  }

  mix_times=get_rand(25)  ;


  for (c=0 ; c < mix_times ; c++) {
    mix_card_game_alternate(game_control->card_game) ;
    mix_card_game_heaps(game_control->card_game) ;
  }

  /** End of cards mixing. **/

  return ;

}
