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
#ifndef LIST_H

#define LIST_H

#include <stdlib.h>
#include <string.h>

typedef struct ListElt_ {
  void *data ;
  struct ListElt_ *next ;
} ListElt ;

typedef struct List_ {

  int size ;

  int (*corresp)(const void *data1, const void *data2) ;

  void (*destroy)(void *data) ;

  ListElt *head ;
  ListElt *tail ;

} List ;

void list_init(List *list, void (*destroy)(void *data)) ;

void list_destroy(List *list) ;

int list_insert_next(List *list, ListElt *elt, const void *data) ;

int list_remove_next(List *list, ListElt *elt, void **data) ;

#define list_size(list) ((list)->size)

#define list_head(list) ((list)->head)

#define list_tail(list) ((list)->tail)

#define list_is_head(list, elt) ((elt) == (list)->head) ? 1 : 0

#define list_is_tail(list, elt) ((elt) == (list)->tail) ? 1 : 0

#define list_data(elt) ((elt)->data)

#define list_next(elt) ((elt)->next)

#endif

