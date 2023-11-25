/**
 * @file vue_analyseur.c
 * @brief Back-end for parcing and reading the 3D object data,
 * all functions written in C language.
 */

#include "../includes/vue_modele.h"

int parse_object_file(char *file, object_data *object_3d) {
  int run_code = SUCCESS;
  if (file == NULL || object_3d == NULL)
    run_code = FAIL;
  else {
    FILE *f = fopen(file, "r");
    if (f != NULL) {
      count_on_first_pass(f, object_3d);
      run_code = allocate_memory(object_3d);
      if (run_code != FAIL) {
        fseek(f, 0, SEEK_SET);
        run_code = parse_vertices_indices(f, object_3d);
      }
      fclose(f);
    } else
      run_code = FAIL;
  }
  return run_code;
}

int allocate_memory(object_data *object_3d) {
  int run_code = SUCCESS;
  if (object_3d->vertices_count)
    object_3d->vertices_array =
        calloc(object_3d->vertices_count * 3, sizeof(double));
  if (object_3d->polygons_count)
    object_3d->polygons_array =
        calloc(object_3d->polygons_count * 2, sizeof(int));
  if (object_3d->polygons_array == NULL || object_3d->vertices_array == NULL)
    run_code = FAIL;
  return run_code;
}

void count_on_first_pass(FILE *file, object_data *object_3d) {
  char *str = NULL;
  size_t length = 0;
  while (getline(&str, &length, file) != EOF) {
    if (strncmp(str, "v ", 2) == 0) {
      object_3d->vertices_count++;
    } else if (strncmp(str, "f ", 2) == 0) {
      char *index_poly = strtok(str + 2, " ");
      while (index_poly != NULL) {
        if (atoi(index_poly)) object_3d->polygons_count++;
        index_poly = strtok(NULL, " ");
      }
    }
  }
  if (str != NULL) {
    free(str);
    str = NULL;
  }
}

void destroy_object(object_data *object_3d) {
  if (object_3d != NULL) {
    if (object_3d->vertices_array != NULL) {
      free(object_3d->vertices_array);
      object_3d->vertices_array = NULL;
    }
    if (object_3d->polygons_array != NULL) {
      free(object_3d->polygons_array);
      object_3d->polygons_array = NULL;
    }
  }
}

int parse_vertices_indices(FILE *file, object_data *object_3d) {
  int run_code = SUCCESS;
  char *str = NULL;
  size_t length = 0, i = 0;
  int v_counter = 0, p_counter = 0;

  while (getline(&str, &length, file) != EOF) {
    if (strncmp(str, "v ", 2) == 0) {
      v_counter++;
      double x, y, z;
      sscanf(str, "v %lf %lf %lf", &x, &y, &z);
      object_3d->vertices_array[i++] = x;
      object_3d->vertices_array[i++] = y;
      object_3d->vertices_array[i++] = z;
    } else if (strncmp(str, "f ", 2) == 0) {
      int index1 = 0;
      bool first = false;
      char *facet_index = strtok(str + 2, " ");
      while (facet_index != NULL) {
        int p_index = atoi(facet_index);
        if (p_index) {
          if (p_index < 0) p_index += v_counter + 1;
          object_3d->polygons_array[p_counter] = p_index - 1;
          if (!first) {
            index1 = p_index - 1;
            first = true;
          } else {
            object_3d->polygons_array[++p_counter] = p_index - 1;
          }
          p_counter++;
        }
        facet_index = strtok(NULL, " ");
      }
      object_3d->polygons_array[p_counter] = index1;
      p_counter++;
    }
  }
  if (str) {
    free(str);
    str = NULL;
  }
  if (object_3d->vertices_array[object_3d->vertices_count * 3 - 1] == 0 ||
      object_3d->polygons_array[object_3d->polygons_count * 2 - 1] == 0)
    run_code = FAIL;
  return run_code;
}
