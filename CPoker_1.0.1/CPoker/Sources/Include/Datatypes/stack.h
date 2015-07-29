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


#ifndef STACK_H

#define STACK_H

#ifndef CARD_GAME
 #include "list.c"
#endif



typedef List Stack ;

#define init_stack list_init    

#define destroy_stack list_destroy

#define stack_peek(stack) ((stack)->head == NULL) ? NULL : (stack)->head->data

#define stack_size(stack)  ((stack)->size)

#endif