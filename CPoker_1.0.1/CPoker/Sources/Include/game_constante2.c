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

#define SCREEN_WIDTH  (int16_t) 800
#define SCREEN_HEIGHT (int16_t) 600

#define SCREEN_WIDTH_OFFSET 211

#define PATH_TO_ICON   "../Icon/CPoker_Icon.png"

#define PATH_TO_MAIN_IMAGES "../Images/Main_screen/"

#define PATH_TO_CARD_IMAGE  "../Images/Cards_images/"

#define PATH_TO_FRAME_YELLOW "../Images/Frames/frame_yellow_logo.png"
#define PATH_TO_FRAME_ORANGE "../Images/Frames/frame_orange_logo.png"
#define PATH_TO_FRAME_BLUE   "../Images/Frames/frame_blue_logo.png"
#define PATH_TO_FRAME_GRAY   "../Images/Frames/frame_gray_logo.png"



#define PATH_TO_CARD_BACK_FACE PATH_TO_CARD_IMAGE"card_back_face_horizontal.png"

#define PATH_TO_BG_IMAGE        "../Images/playground.png"

#define PATH_TO_BORDER_BG_IMAGE "../Images/playground_border.png"

#define PATH_TO_SCORE_BG        "../Images/score_background.png"


#define PATH_TO_BUTTONS      "../Images/Buttons/"

#define PATH_TO_FONT         "../Font/FreeMonoBold.ttf"

#define BUTTON_WIDTH  200
#define BUTTON_HEIGHT 100

#define CARD_WIDTH  (int8_t) 73
#define CARD_HEIGHT (int8_t) 98

#define CARD_BORDER_OFFSET SCREEN_WIDTH_OFFSET+122                /** distance from the first card from the border.  **/

#define FRAME_WIDTH  (int8_t)  97
#define FRAME_HEIGHT (int8_t) 122

#define FRAME_CARD_OFFSET (int8_t) 12

#define CARD_CARD_X_OFFSET FRAME_WIDTH/2      /** distance beetwen 2 cards offset.               **/


#define FRAME_X_LEFT_POS  SCREEN_WIDTH_OFFSET + FRAME_WIDTH/2
#define FRAME_X_RIGHT_POS SCREEN_WIDTH + SCREEN_WIDTH_OFFSET - FRAME_WIDTH - FRAME_WIDTH/2

#define TOP_BAR_SIZE (int8_t)  9

#define FRAME_Y_TOP_POS     (FRAME_HEIGHT / 2) + TOP_BAR_SIZE
#define FRAME_Y_MIDDLE_POS  (SCREEN_HEIGHT / 2) - (FRAME_HEIGHT/2) + TOP_BAR_SIZE
#define FRAME_Y_BOTTOM_POS  (SCREEN_HEIGHT - FRAME_HEIGHT) - (FRAME_HEIGHT / 2) + TOP_BAR_SIZE // (+ 12)
