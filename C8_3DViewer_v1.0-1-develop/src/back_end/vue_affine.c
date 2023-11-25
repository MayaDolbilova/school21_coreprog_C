/**
 * @file vue_affine.c
 * @brief Implementation of affine transformations
 */
#include "../includes/vue_modele.h"

void rotate_X(object_data *object_3d, double angle) {
  angle = angle * M_PI / 180;
  for (size_t i = 0; i < object_3d->vertices_count * 3; i += 3) {
    double Y = object_3d->vertices_array[i + 1];
    double Z = object_3d->vertices_array[i + 2];
    object_3d->vertices_array[i + 1] = Y * cos(angle) + Z * sin(angle);
    object_3d->vertices_array[i + 2] = -Y * sin(angle) + Z * cos(angle);
  }
}
void rotate_Y(object_data *object_3d, double angle) {
  angle = angle * M_PI / 180;
  for (size_t i = 0; i < object_3d->vertices_count * 3; i += 3) {
    double X = object_3d->vertices_array[i];
    double Z = object_3d->vertices_array[i + 2];
    object_3d->vertices_array[i] = X * cos(angle) + Z * sin(angle);
    object_3d->vertices_array[i + 2] = -X * sin(angle) + Z * cos(angle);
  }
}
void rotate_Z(object_data *object_3d, double angle) {
  angle = angle * M_PI / 180;
  for (size_t i = 0; i < object_3d->vertices_count * 3; i += 3) {
    double X = object_3d->vertices_array[i];
    double Y = object_3d->vertices_array[i + 1];
    object_3d->vertices_array[i] = X * cos(angle) + Y * sin(angle);
    object_3d->vertices_array[i + 1] = -X * sin(angle) + Y * cos(angle);
  }
}

void scale_object(object_data *object_3d, const double scale) {
  if (scale != 0) {
    for (size_t i = 0; i < object_3d->vertices_count * 3; i++) {
      object_3d->vertices_array[i] *= scale;
    }
  }
}

void shift_X(object_data *object_3d, const double distance) {
  for (size_t i = 0; i < object_3d->vertices_count * 3; i += 3) {
    object_3d->vertices_array[i] += distance;
  }
}
void shift_Y(object_data *object_3d, const double distance) {
  for (size_t i = 1; i < object_3d->vertices_count * 3; i += 3) {
    object_3d->vertices_array[i] += distance;
  }
}
void shift_Z(object_data *object_3d, const double distance) {
  for (size_t i = 2; i < object_3d->vertices_count * 3; i += 3) {
    object_3d->vertices_array[i] += distance;
  }
}
