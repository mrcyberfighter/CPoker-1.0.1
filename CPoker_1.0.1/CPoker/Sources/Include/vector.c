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

typedef struct Vector_ {
  double x ;
  double y ;
} Vector ;

typedef struct Vertex_ {
  double x ;
  double y ;
} Vertex ;

Vector *from_vertices(Vector *vector, Vertex *vertex1, Vertex *vertex2) {
  /** Generate an Vector from 2 points (vertex). **/
  vector->x = vertex2->x - vertex1->x ;
  vector->y = vertex2->y - vertex1->y ;

  return vector ;
}

void compute_steps(Vector positions[],Vertex *start_vertex, Vertex *end_vertex,double steps) {
  /** Compute an array of Vectors within each representing an position between the start and end point (Vertex)
   *  To get an guideline for animating an trajectory between 2 points.
   * **********************************************************************************************************/


  Vector *distance_vector=malloc(sizeof(Vector)) ;

  /** Define an vector representing the entire distance, between 2 vertex. **/
  from_vertices(distance_vector,start_vertex,end_vertex ) ;

  /** Compute an vector used as unit, in relationship to the number of steps, between 2 points (vertice).     **/
  Vector unit ;
  /**      from start to end  ;    factor < 1.0       ;          from start to end  ;    factor < 1.0       ; **/
  unit.x = distance_vector->x * (steps/(steps*steps)) ; unit.y = distance_vector->y * (steps/(steps*steps)) ;

  /** Current position vector initialize with the start point coordinates. **/
  Vector position_vector ;
  position_vector.x = start_vertex->x ; position_vector.y = start_vertex->y ;

  positions[0]=position_vector ;  /** Store the first position. **/

  int c ;

  for (c=1 ; c < (int) steps ; c++) {
  
    /** Add an unit to the Current position vector          **/
    position_vector.x += unit.x ; position_vector.y += unit.y ;
  
    /** Store the current vector. **/
    positions[c]=position_vector    ;
  
  }

  free(distance_vector) ;

  return ;
}

  
  


