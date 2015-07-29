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

#include "list.h"

void list_init(List *list, void (*destroy)(void *data)) {

  list->size=0 ;

  list->destroy=destroy ;

  list->head=NULL ;

  list->tail=NULL ;
  
  return ;
}

void list_destroy(List *list) {

  void *data ;

  if (list_size(list) > 0) {

    while (list_remove_next(list, NULL, &data) != -1) {
      if (list->destroy) {
	if (data) {
	  list->destroy(data) ;
	}
      }
    }

  }

  memset(list,'\0',sizeof(List)) ;

  return ;
}

int list_insert_next(List *list, ListElt *elt, const void *data) {

  ListElt *new_elt ;

  if ((new_elt = malloc(sizeof(ListElt))) == NULL) {
    return -1 ;
  }

  new_elt->data = (void *) data ;

  if (elt == NULL) {
    /** Case we insert at first position. **/

    /** This don't work wenn mixed with none NULL elt arg values. **/

    if (list_size(list) == 0) {
      /** Case list empty. **/
      list->tail = new_elt ;
    }

    new_elt->next = list->head ;
    list->head    = new_elt    ;

  }
  else {
    /** Case we insert after elt. **/

    if (elt->next == NULL) {
      /** Case we append to list. **/
      list->tail=new_elt ;
    }

    new_elt->next = elt->next ;
    elt->next     = new_elt   ;
  

  }

  list->size++ ;

  return 0 ;

}

int list_remove_next(List *list, ListElt *elt, void **data) {

  ListElt *old_elt ;

  if (list->size == 0) {
    return -1 ;
  }

  if ( elt == NULL ) {

    *data=list->head->data  ;
    old_elt=list->head     ;
    list->head=list->head->next ;

    if (list_size(list) == 1) {
      list->tail=NULL ;
    }

  }
  else {
    if ( elt->next == NULL ) {
      return -1 ;
    }

    *data=elt->next->data     ;
    old_elt=elt->next         ;
    elt->next=elt->next->next ;
  }

  free(old_elt) ;

  list->size-- ;

  return 0 ;
}








