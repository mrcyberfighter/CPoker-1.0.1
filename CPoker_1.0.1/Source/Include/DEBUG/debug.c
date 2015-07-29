void print_combination(Card computer[5], Card hand[5]) {

  /** DEBUG funtion **/

  sort_cards(computer, hand) ;

  uint8_t combination, c ;

  if ( (combination = check_combination(computer, hand)) ) {

    fprintf(stdout,"Combination : %s\n", (combination == PAIR) ? "Pair" : (combination == TWO_PAIRS) ? "two pairs" : (combination == FULL_HOUSE) ? "full house" : (combination == BRELAN) ? "brelan" :  (combination == FOUR) ? "four" : (combination == QUINTE) ? "quinte" : (combination == QUINTE_FLUSH) ? "quinte flush" : (combination == ROYAL_FLUSH) ? "royal flush" : "bicycle") ;

    for (c=0 ; c < 5 ; c++) {
      if (hand[c].value < 11) {
       fprintf(stdout,"%s %d of %s\n",__func__,hand[c].value,(hand[c].type == 0) ? "Carot" : (hand[c].type == 1) ? "Heart" : (hand[c].type == 2) ? "Pick" : (hand[c].type == 3) ? "Shamrock" : "No card") ;
      }
      else {
        fprintf(stdout,"%s %s of %s\n",__func__,(hand[c].value == 11) ? "Jack" : (hand[c].value == 12) ? "Queen" : (hand[c].value == 13) ? "King" : (hand[c].value == 14) ? "As" : "No Card",(hand[c].type == 0) ? "Carot" : (hand[c].type == 1) ? "Heart" : (hand[c].type == 2) ? "Pick" : (hand[c].type == 3) ? "Shamrock" : "No card") ;
      }
    }

  }
  else {
    fprintf(stdout,"Combination : highest card\n") ;

    for (c=0 ; c < 5 ; c++) {
      if (hand[c].value < 11) {
       fprintf(stdout,"%s %d of %s\n",__func__,hand[c].value,(hand[c].type == 0) ? "Carot" : (hand[c].type == 1) ? "Heart" : (hand[c].type == 2) ? "Pick" : (hand[c].type == 3) ? "Shamrock" : "No card") ;
      }
      else {
        fprintf(stdout,"%s %s of %s\n",__func__,(hand[c].value == 11) ? "Jack" : (hand[c].value == 12) ? "Queen" : (hand[c].value == 13) ? "King" : (hand[c].value == 14) ? "As" : "No Card",(hand[c].type == 0) ? "Carot" : (hand[c].type == 1) ? "Heart" : (hand[c].type == 2) ? "Pick" : (hand[c].type == 3) ? "Shamrock" : "No card") ;
      }
    }
  }

  for (c=0 ; c < 5 ; c++) {
    if (computer[c].value < 11) {
      fprintf(stdout,"%s %d of %s part of combination: %d \n",__func__,computer[c].value,(computer[c].type == 0) ? "Carot" : (computer[c].type == 1) ? "Heart" : (computer[c].type == 2) ? "Pick" : (computer[c].type == 3) ? "Shamrock" : "No card",computer[c].part_of_combination) ;
    }
    else {
      fprintf(stdout,"%s %s of %s part of combination: %d \n",__func__,(computer[c].value == 11) ? "Jack" : (computer[c].value == 12) ? "Queen" : (computer[c].value == 13) ? "King" : (computer[c].value == 14) ? "As" : "No Card",(computer[c].type == 0) ? "Carot" : (computer[c].type == 1) ? "Heart" : (computer[c].type == 2) ? "Pick" : (computer[c].type == 3) ? "Shamrock" : "No card",computer[c].part_of_combination) ;
    }
  }
}



void set_player_cards(Card hand[5]) {

  /** For debug purpose. **/

  hand[0].value= 9 ;
  hand[0].type= 2  ;

  hand[1].value= 13 ;
  hand[1].type= 3  ;

  hand[2].value= 13 ;
  hand[2].type= 1  ;

  hand[3].value= 10 ;
  hand[3].type= 0  ;

  hand[4].value= 10 ;
  hand[4].type= 2  ;


}
void set_computer_cards(Card hand[5]) {

  /** For debug purpose. **/

  hand[0].value= 9 ;
  hand[0].type= 2  ;

  hand[1].value= 13 ;
  hand[1].type= 3  ;

  hand[2].value= 13 ;
  hand[2].type= 1  ;

  hand[3].value= 8 ;
  hand[3].type= 0  ;

  hand[4].value= 8 ;
  hand[4].type= 2  ;


}

