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

void configure_score_text(SDL_Renderer *pRenderer, Text *text, uint8_t score) {

  /** Function wich update the game scores text fields: the player or the computer score. **/

  char *texture_text=calloc(32,sizeof(char)) ;

  char *spaces=calloc(8,sizeof(char)) ;
  uint8_t c ;
  for (c=(uint8_t) strlen(text->text) ; c < 9 ; c++) {
    /** Add spaces in relationship of updating player or computer score. **/
    strcat(spaces," ") ;
  }

  sprintf(texture_text,"%s %s %02d",text->text,spaces,score) ;

  free(spaces) ;


  SDL_Surface* text_surface   = TTF_RenderText_Blended(text->font, texture_text, text->text_color);

  free(texture_text) ;

  if ( text_surface == NULL ) {

    #ifdef DEBUG
      fprintf(stdout,"Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    #endif

    return ;
  }

  text->font_texture  = SDL_CreateTextureFromSurface( pRenderer, text_surface );

  if( text->font_texture == NULL ) {

     #ifdef DEBUG
      fprintf(stdout,"Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
     #endif

    return ;
  }

  else {
    text->width  = text_surface->w  ;
    text->height = text_surface->h ;

    SDL_FreeSurface( text_surface );
  }

  return ;

}

void configure_result_text(SDL_Renderer *pRenderer, Text *text, int8_t winner) {

  /** Function to configure the text displayed at round end to notify the round winner. **/

  if ( winner == -1 ) {
    text->text="Computer win this round !" ;
    text->text_color.r =  255 ;  /** Color of the computer: orange.      **/
    text->text_color.g =  128 ;  /** Color of the computer: orange.      **/
    text->text_color.b =    0 ;  /** Color of the computer: orange.      **/
    text->text_color.a =  255 ;  /** Color of the computer: orange.      **/

  }
  else if (winner == 1) {
    text->text="Player win this round !" ;
    text->text_color.r =  255 ;  /** Color of the player: yellow.        **/
    text->text_color.g =  255 ;  /** Color of the player: yellow.        **/
    text->text_color.b =    0 ;  /** Color of the player: yellow.        **/
    text->text_color.a =  255 ;  /** Color of the player: yellow.        **/
  }
  else {
    text->text="Nobody win this round !" ;
    text->text_color.r =  192 ;  /** Color for equality text: lightgray. **/
    text->text_color.g =  192 ;  /** Color for equality text: lightgray. **/
    text->text_color.b =  192 ;  /** Color for equality text: lightgray. **/
    text->text_color.a =  255 ;  /** Color for equality text: lightgray. **/

  }


  SDL_Surface* text_surface   = TTF_RenderText_Blended(text->font, text->text, text->text_color);

  if ( text_surface == NULL ) {

    #ifdef DEBUG
      fprintf(stdout, "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    #endif

    return ;
  }

  text->font_texture  = SDL_CreateTextureFromSurface( pRenderer, text_surface );

  if( text->font_texture == NULL ) {

    #ifdef DEBUG
      fprintf(stdout, "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
    #endif

    return ;
  }

  else {
    text->width  = text_surface->w  ;
    text->height = text_surface->h ;

    text->x=  SCREEN_WIDTH_OFFSET + SCREEN_WIDTH/2    - text_surface->w/2  ;  /** We display the text in the middle of the playground. **/
    text->y=  SCREEN_HEIGHT/2 + 28                    - text_surface->h    ;  /** We display the text in the middle of the playground. **/

    SDL_FreeSurface( text_surface );
  }

  return ;

}

void configure_game_winner_text(SDL_Renderer *pRenderer, Text *text) {

  /** Function to configure the game winner text. **/

  char *game_winner_text=calloc(32,sizeof(char)) ;

  if (game_control->player_score > game_control->computer_score) {

    strcpy(game_winner_text,"You win the game !!!") ;
    text->text_color.r =  255 ;  /** Color of the player: yellow.        **/
    text->text_color.g =  255 ;  /** Color of the player: yellow.        **/
    text->text_color.b =   00 ;  /** Color of the player: yellow.        **/
    text->text_color.a =  255 ;  /** Color of the player: yellow.        **/

  }
  else if (game_control->player_score < game_control->computer_score) {

    strcpy(game_winner_text,"You lose the game !!!") ;
    text->text_color.r =  255 ;  /** Color of the computer: orange.      **/
    text->text_color.g =  128 ;  /** Color of the computer: orange.      **/
    text->text_color.b =    0 ;  /** Color of the computer: orange.      **/
    text->text_color.a =  255 ;  /** Color of the computer: orange.      **/

  }
  else {

    strcpy(game_winner_text,"Nobody win the game !!!") ;
    text->text_color.r =  192 ;  /** Color for equality text: lightgray. **/
    text->text_color.g =  192 ;  /** Color for equality text: lightgray. **/
    text->text_color.b =  192 ;  /** Color for equality text: lightgray. **/
    text->text_color.a =  255 ;  /** Color for equality text: lightgray. **/

  }

  SDL_Surface* text_surface   = TTF_RenderText_Blended(text->font, game_winner_text, text->text_color);

  free(game_winner_text) ;

  if ( text_surface == NULL ) {

    #ifdef DEBUG
      fprintf(stdout, "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    #endif

    return ;
  }

  text->font_texture  = SDL_CreateTextureFromSurface( pRenderer, text_surface );

  if( text->font_texture == NULL ) {

    #ifdef DEBUG
      fprintf(stdout, "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
    #endif

    return ;
  }

  else {
    text->width  = text_surface->w  ;
    text->height = text_surface->h ;

    text->x=  SCREEN_WIDTH_OFFSET + SCREEN_WIDTH/2    - text_surface->w/2  ;  /** We display the text in the middle of the playground. **/
    text->y=  SCREEN_HEIGHT/2 + 28                    - text_surface->h    ;  /** We display the text in the middle of the playground. **/

    SDL_FreeSurface( text_surface );
  }

  return ;

}

void configure_game_press_escape_text(SDL_Renderer *pRenderer, Text *text) {

  /** Function to configure the game winner text. **/

  char *press_escape_text=calloc(48,sizeof(char)) ;

  if (game_control->player_score > game_control->computer_score) {

    strcpy(press_escape_text,"Press Escape to return to main menu.") ;
    text->text_color.r =  255 ;  /** Color of the player: yellow.        **/
    text->text_color.g =  255 ;  /** Color of the player: yellow.        **/
    text->text_color.b =   00 ;  /** Color of the player: yellow.        **/
    text->text_color.a =  255 ;  /** Color of the player: yellow.        **/

  }
  else if (game_control->player_score < game_control->computer_score) {

    strcpy(press_escape_text,"Press Escape to return to main menu.") ;
    text->text_color.r =  255 ;  /** Color of the computer: orange.      **/
    text->text_color.g =  128 ;  /** Color of the computer: orange.      **/
    text->text_color.b =    0 ;  /** Color of the computer: orange.      **/
    text->text_color.a =  255 ;  /** Color of the computer: orange.      **/

  }
  else {

    strcpy(press_escape_text,"Press Escape to return to main menu.") ;
    text->text_color.r =  192 ;  /** Color for equality text: lightgray. **/
    text->text_color.g =  192 ;  /** Color for equality text: lightgray. **/
    text->text_color.b =  192 ;  /** Color for equality text: lightgray. **/
    text->text_color.a =  255 ;  /** Color for equality text: lightgray. **/

  }

  SDL_Surface* text_surface   = TTF_RenderText_Blended(text->font, press_escape_text, text->text_color);

  free(press_escape_text) ;

  if ( text_surface == NULL ) {

    #ifdef DEBUG
      fprintf(stdout, "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    #endif

    return ;
  }

  text->font_texture  = SDL_CreateTextureFromSurface( pRenderer, text_surface );

  if( text->font_texture == NULL ) {

    #ifdef DEBUG
      fprintf(stdout, "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
    #endif

    return ;
  }

  else {
    text->width  = text_surface->w  ;
    text->height = text_surface->h ;

    text->x=  SCREEN_WIDTH_OFFSET + SCREEN_WIDTH/2    - text_surface->w/2  ;  /** We display the text in the down middle of the playground. **/
    text->y=  SCREEN_HEIGHT/2 + 28 + 32               - text_surface->h    ;  /** We display the text in the down middle of the playground. **/

    SDL_FreeSurface( text_surface );
  }

  return ;

}


void render_text(SDL_Renderer *pRenderer, Text *text) {

  /** Function to render any text given as argument. **/

  SDL_Rect textrect;

  textrect.x = text->x ;
  textrect.y = text->y ;
  textrect.w = text->width  ;
  textrect.h = text->height ;

  SDL_RenderCopy(pRenderer, text->font_texture, NULL, &textrect) ;

  return ;
}

void update_score_displaying(SDL_Renderer *pRenderer, Text *player, Text *computer) {

  /** Function to update the score after a round end. **/

  if (game_control->round_winner == 1) {
    game_control->player_score++ ;
  }
  else if (game_control->round_winner == -1) {
    game_control->computer_score++ ;
  }

  game_control->round_winner = 0 ;

  configure_score_text(pRenderer, player,   game_control->player_score)   ;  /** Function to find above. **/

  configure_score_text(pRenderer, computer, game_control->computer_score) ;  /** Function to find above. **/

  if (game_control->rounds_counter == game_control->number_of_rounds) {
    /** Case the game is over. **/
    game_control->GAME_STATUS = GAME_END      ;
  }

}

void configure_press_enter_text(SDL_Renderer *pRenderer, Text *text, int image_counter) {

  /** Function to configure the Press Enter invitation by presentation screen.
   *  To make the text blink in orange and yellow.
   * *************************************************************************/

  if ( image_counter == 25 ) {
    text->text_color.r =  255 ;
    text->text_color.g =  128 ;
    text->text_color.b =   32 ;
    text->text_color.a =  255 ;

  }
  else if (image_counter == 50) {
    text->text_color.r =  255 ;
    text->text_color.g =  255 ;
    text->text_color.b =    0 ;
    text->text_color.a =  255 ;
  }
  else if (image_counter == 75)  {
    text->text_color.r =  255 ;
    text->text_color.g =  128 ;
    text->text_color.b =   32 ;
    text->text_color.a =  255 ;

  }
  else if ( image_counter == 100 ) {
    text->text_color.r =  255 ;
    text->text_color.g =  255 ;
    text->text_color.b =    0 ;
    text->text_color.a =  255 ;

  }


  SDL_Surface* text_surface   = TTF_RenderText_Blended(text->font, text->text, text->text_color);

  if ( text_surface == NULL ) {

    #ifdef DEBUG
      fprintf(stdout, "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    #endif

    return ;
  }

  text->font_texture  = SDL_CreateTextureFromSurface( pRenderer, text_surface );

  if( text->font_texture == NULL ) {

    #ifdef DEBUG
      fprintf(stdout, "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
    #endif

    return ;
  }

  else {
    text->width  = text_surface->w  ;
    text->height = text_surface->h ;

    text->x=  1020/2 - text_surface->w/2  ;
    text->y=  574    ;

    SDL_FreeSurface( text_surface );
  }

  return ;

}

void configure_rounds_text(SDL_Renderer *pRenderer, Text *text, int number_of_rounds) {

  /** Function to configure the number of rounds to play text and value which can be cahnge by the user. **/


  char *numbers_of_rounds_text =  calloc(48,sizeof(char)) ;
  sprintf(numbers_of_rounds_text,"Number of rounds to play: %02d [↑|↓]",number_of_rounds) ;

  SDL_Surface* text_surface   = TTF_RenderUTF8_Blended(text->font, numbers_of_rounds_text, text->text_color);

  free(numbers_of_rounds_text) ;

  if ( text_surface == NULL ) {

    #ifdef DEBUG
      fprintf(stdout, "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    #endif

    return ;
  }

  text->font_texture  = SDL_CreateTextureFromSurface( pRenderer, text_surface );

  if( text->font_texture == NULL ) {

    #ifdef DEBUG
      fprintf(stdout, "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
    #endif

    return ;
  }

  else {
    text->width  = text_surface->w  ;
    text->height = text_surface->h ;

    text->x=  1020/2 - text_surface->w/2  ;
    text->y=  512    ;

    SDL_FreeSurface( text_surface );
  }

  return ;

}