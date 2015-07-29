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

SDL_Texture *get_texture_from_image(SDL_Renderer *pRenderer, const char *filepath) {

  /** Generate an SDL_Texture object from an image filepath. **/

  SDL_Surface *image_surface = IMG_Load(filepath);

  if (image_surface == NULL) {
    /** Display an error message and quit the programme in case of error. **/
    char *message=calloc(256,sizeof(char)) ;
    sprintf(message,"Failed to load image %s!\n%s",filepath,SDL_GetError()) ;
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error image loading", message ,NULL) ;
    free(message) ;
    #ifdef DEBUG
      fprintf(stdout,"image_surface error (%s)\n",SDL_GetError());
    #endif
    exit(EXIT_FAILURE) ;
  
  }

  SDL_Texture *image_texture = SDL_CreateTextureFromSurface(pRenderer,image_surface) ;

  if (image_texture == NULL) {
    /** Exit the programme in case of error. **/
    exit(EXIT_FAILURE) ;
  
  }

  SDL_FreeSurface(image_surface) ; /** We clean up the surface. **/

  return image_texture ;
}


void display_image(SDL_Renderer *pRenderer,SDL_Texture *frame_texture, uint16_t offset_x, uint16_t offset_y, uint16_t width, uint16_t height ) {

  /** Function to display an image. **/

  SDL_Rect dstrect ;

  dstrect.x = offset_x ;
  dstrect.y = offset_y ;
  dstrect.w = width    ;
  dstrect.h = height   ;
 
  SDL_RenderCopy(pRenderer,frame_texture,NULL,&dstrect) ;

  return ;
}