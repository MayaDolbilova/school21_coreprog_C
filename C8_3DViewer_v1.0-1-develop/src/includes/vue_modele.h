/**
 * @file vue_model.h
 * @brief Main back-end header file for Vue_3D project
 * @author Team (TL: lostnola@student.21-school.ru)
 * lostnola@student.21-school.ru
 * rosamonj@student.21-school.ru
 * jereninf@student.21-school.ru
 * @version 0.1
 * @date 2023-09-03
 *
 * @copyright Open
 *
 */
#ifndef VUE_MODELE_H
#define VUE_MODELE_H

/**
 *  @page backend_page Main back-end header file vue_model.h
 *  @brief The main back-end for the project is written in C language
 *  conforming to the C11 standard.\
 */

#define _GNU_SOURCE
#include <locale.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/** @struct object_data
 *  @bried contains all the info from
 *  3D wirefrime definition .obj file.
 */
typedef struct KTO_3HAET_KAK {
  size_t vertices_count;   //!< Total number of vertices
  double *vertices_array;  //!< Array of vertex coordinates
  size_t polygons_count;   //!< Total number of facets
  int *polygons_array;     //!< Array of facets
} object_data;

/** @enum state
 * @brief boolean values and execution statuses *
 */
enum state {
  FALSE,        //!< logical false=0
  TRUE,         //!< logical true=1
  SUCCESS = 0,  //!< process status success=0
  FAIL,         //!< process status fail=1
};

/*********************************************************/
/** @page analyseur Parcing and data-handling C functions.
 *  @brief File vue_analyseur.c contains parsing functions
 *  Namely, the functions for reading object files,
 *  allocating memory, writing data, counting and reading
 *  the vertices and vertex indices, and freeing memory.
 *
 *  @subsubsection parcer Parcing object files and writing data.
 *  @brief These are the most important back-end processes.
 *  @fn int parse_object_file(char *file, object_data *object_3d);
 *  @brief Function for parsing object files and writing data.
 *  @param filename pointer to a string with the file name and path
 *  @param object_3d pointer to a main structure for object data
 *  @return run status: OK = 0, ERROR = 1
 */
int parse_object_file(char *file, object_data *object_3d);

/** @fn int allocate_memory(object_data *object_3d);
 *  @brief Allocates memory for the object data based on the
 *  information read from the object file.
 *  @param object_3d pointer to a main structure for object data
 *  @return run status: OK = 0, ERROR = 1
 */
int allocate_memory(object_data *object_3d);

/** @fn void count_on_first_pass(FILE *file, object_data *object_3d);
 * @brief Counts vertices and their indices in the object
 * file, in order to allocate memory for them.
 * @param file pointer to the .obj file
 * @param object_3d pointer to a main structure for object data
 */
void count_on_first_pass(FILE *file, object_data *object_3d);

/** @fn void destroy_object(object_data *object_3d);
 * @brief Destroy the data object and free allocated memory.
 * @param object_3d pointer to a main structure for object data
 */
void destroy_object(object_data *object_3d);

/** @fn int parse_vertices_indices(FILE *file, object_data *object_3d);
 * @brief Reads vertices and vertex indices, checks them and
 * writes them to the data object.
 * @param file pointer to obj file
 * @param object_3d pointer to an object with data
 * @return status code: 0 - OK, 1 - ERROR
 */
int parse_vertices_indices(FILE *file, object_data *object_3d);

/*********************************************************/
/** @page affine Affine transformations C functions.
 *
 *  @brief File vue_affine.c contains all necessary functions
 *  for affine transformations
 *  Namely, the functions for shifting, rotating and
 *  scaling the 3d object.
 *
 *  @subsubsection affine1 Move, Rotate and Scale the Object
 *  @brief The transformations of shift and rotation
 *  are done along one of the axis X, Y or Z; Hence three
 *  functions for each action.
 */

void rotate_X(object_data *object_3d, double angle);
void rotate_Y(object_data *object_3d, double angle);
void rotate_Z(object_data *object_3d, double angle);

void scale_object(object_data *object_3d, const double scale);

void shift_X(object_data *object_3d, const double distance);
void shift_Y(object_data *object_3d, const double distance);
void shift_Z(object_data *object_3d, const double distance);

#endif
