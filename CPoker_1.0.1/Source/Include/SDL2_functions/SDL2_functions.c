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

SDL_Window* sdl_create_window(const char *title,int screen_x_pos, int screen_y_pos, int width, int height,int flags) {

  /* screen_x_pos && screen_y_pos == SDL_WINDOWPOS_CENTERED or SDL_WINDOWPOS_UNDEFINED ;
   *
   * flags :
   * SDL_WINDOW_FULLSCREEN		fullscreen window
   * SDL_WINDOW_FULLSCREEN_DESKTOP	fullscreen window at the current desktop resolution
   * SDL_WINDOW_OPENGL 			window usable with OpenGL context
   * SDL_WINDOW_HIDDEN			window is not visible
   * SDL_WINDOW_BORDERLESS		no window decoration
   * SDL_WINDOW_RESIZABLE		window can be resized
   * SDL_WINDOW_MINIMIZED		window is minimized
   * SDL_WINDOW_MAXIMIZED		window is maximized
   * SDL_WINDOW_INPUT_GRABBED		window has grabbed input focus
   * SDL_WINDOW_ALLOW_HIGHDPI		window should be created in high-DPI mode if supported (>= SDL 2.0.1)
   **********************************************************************************************************/

  return SDL_CreateWindow(title, screen_x_pos, screen_y_pos, width, height, flags) ;
}

SDL_Renderer* sdl_create_renderer(SDL_Window *window,int index,int flags) {

   /*
    * index : the index of the rendering driver to initialize, or -1 to initialize the first one supporting the requested flags
    *
    * flags
    * SDL_RENDERER_SOFTWARE		the renderer is a software fallback
    * SDL_RENDERER_ACCELERATED		the renderer uses hardware acceleration
    * SDL_RENDERER_PRESENTVSYNC		present is synchronized with the refresh rate
    * SDL_RENDERER_TARGETTEXTURE	the renderer supports rendering to texture
    *
    * Note that providing no flags gives priority to available SDL_RENDERER_ACCELERATED renderers.
    **********************************************************************************************/

   return SDL_CreateRenderer(window,(index != -1) ? index : -1  ,(flags == 0) ? SDL_RENDERER_ACCELERATED : flags ) ;
}

void get_events(int16_t *mouse_x, int16_t *mouse_y) {

  SDL_Event event;


  while (SDL_PollEvent(&event)) { /** Get user events. **/
  


    switch(event.type) {

      case SDL_QUIT:
	/** User press the cross to close the application. **/
	quit_game=true ;
	set_loop(false) ;
	break;

      case SDL_KEYDOWN :

	if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
	  /** The user fallback to the previous screen. **/
	  set_loop(false) ;
	  break ;
	}

      case SDL_MOUSEMOTION :
   
       *mouse_x = event.motion.x ;  /** We keep the mouse position at everytime in the game. **/
       *mouse_y = event.motion.y ;  /** We keep the mouse position at everytime in the game. **/

   
   
	if ( ! game_control->is_animation_running && game_control->GAME_STATUS != DRAG_CARD_ON && game_control->GAME_STATUS != GAME_START ) {

	  if ( mouse_over_card(event.motion.x,event.motion.y) != -1 && ! game_control->is_animation_running ) {
	    /** The mouse is over an card. **/
	    if ( game_control->cursor_type != SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND) ) {
	      /** We set the cursor to an hand cursor to notify the user that he can return or drag-and-drop the card. **/
	      game_control->cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND) ;
	      SDL_SetCursor(game_control->cursor_type)  ;
	      game_control->mouse_over_card=true ;
	    }
	
	  }
	  else {
	    if ( game_control->cursor_type != SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW) && ! game_control->is_animation_running && ! is_mouse_in_buttons_bboxes(event.motion.x) ) {
	      /** We reset the cursor to default. **/
	      game_control->cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW) ;
	      SDL_SetCursor(game_control->cursor_type)  ;
	      game_control->mouse_over_card=false ;
	    }
	  }

       }
  

  
      if ( ! game_control->is_animation_running ) {
	/** The mouse is over an button. **/
	mouse_over_button(event.motion.x,event.motion.y) ;
	break ;
      }

  
  
      break ;
  
      case SDL_MOUSEBUTTONDOWN :

	if (event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_PRESSED) {

	  int8_t ret ;

	  if ( ! game_control->is_animation_running && ((ret=mouse_over_card(event.button.x,event.button.y)) != -1)  ) {
	    if (game_control->player[ret].is_back_faced) {
	      /** We process an card returning aniation. **/
	      current_card = &game_control->player[ret] ;
	      game_control->GAME_STATUS = RETURN_A_CARD ;
	      break ;
	    }
	    else if (! game_control->player[ret].is_back_faced && game_control->GAME_STATUS != DRAG_CARD_ON) {
	      /** The user can drag an card. **/	  
	      dragging_card->card = &game_control->player[ret] ;
	      dragging_card->x    =  event.button.x - game_control->player[ret].x  ;
	      dragging_card->y    =  event.button.y - game_control->player[ret].y  ;
	      	  
	      game_control->player[ret].is_moving = true ;
	  
	      game_control->GAME_STATUS = DRAG_CARD_ON ;
	  
	      game_control->cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL) ;
	      SDL_SetCursor(game_control->cursor_type)  ;
	  
	      break ;
	    }

	  }
	  else if ( ! game_control->is_animation_running && (ret = press_button(event.button.x,event.button.y)) != -1 ) {
	
	    /** The user press an button which is allowed. **/
	
	    do_change_game_status(ret) ;
	
	    break ;
	  }
	

      }
  
      case SDL_MOUSEBUTTONUP :

	if ( game_control->GAME_STATUS == DRAG_CARD_ON) {
	  /** The user release an card he is dragging, so we process. **/
	  game_control->GAME_STATUS = DRAG_CARD_OFF ;
	  game_control->cursor_type = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW) ;
	  SDL_SetCursor(game_control->cursor_type)  ;
	}

	break ;

    }
  }

  return ;
}

void clear(SDL_Renderer *pRenderer,uint8_t bg_red, uint8_t bg_green, uint8_t bg_blue,uint8_t bg_alpha) {
  SDL_SetRenderDrawColor(pRenderer, bg_red, bg_green, bg_blue, bg_alpha) ;
  SDL_RenderClear(pRenderer);
}

void display(SDL_Renderer *pRenderer) {
  SDL_RenderPresent(pRenderer);
}

void update(SDL_Window *pWindow) {
  SDL_UpdateWindowSurface(pWindow);
}

void clean_up(SDL_Renderer *pRenderer, SDL_Window *pWindow) {
  SDL_DestroyRenderer(pRenderer);
  SDL_DestroyWindow(pWindow);
}