#include <stdio.h>

#include "../includes/vue_modele.h"
#include "./vue_3d_tests.h"

/*----------------------------------file manipulate-------------------*/
START_TEST(file_open_fail) {
  char *file_name = "sadflasdf";  // Arrange
  FILE *f = NULL;                 // Arrange
  int status = 1;
  f = fopen(file_name, "r");       // Act
  ck_assert_int_eq(FAIL, status);  // Assert
  ck_assert_ptr_eq(f, NULL);       // Assert
}
END_TEST

START_TEST(file_open_ok) {
  char *file_name = "objects/cube.obj";  // Arrange
  FILE *f = NULL;                        // Arrange
  int status = 0;
  f = fopen(file_name, "r");          // Act
  ck_assert_int_eq(SUCCESS, status);  // Assert
  ck_assert_ptr_ne(f, NULL);          // Assert
  fclose(f);
}
END_TEST

START_TEST(count_vtx_fct) {
  char *file_name = "objects/cube.obj";               // Arrange
  FILE *f = NULL;                                     // Arrange
  object_data *res = calloc(1, sizeof(object_data));  // Arrange
  int status = 0;
  f = fopen(file_name, "r");                                // Act
  if (!status) status = parse_object_file(file_name, res);  // Act
  ck_assert_int_eq(SUCCESS, status);                        // Assert
  ck_assert_int_eq(res->vertices_count, 8);                 // Assert
  ck_assert_int_eq(res->polygons_count / 2, 18);            // Assert
  ck_assert_ptr_ne(f, NULL);                                // Assert
  fclose(f);
  destroy_object(res);
  free(res);

  // ck_assert_ptr_eq(f, NULL);  // Assert
}
END_TEST

START_TEST(read_vertices) {
  char *file_name = "objects/cube.obj";               // Arrange
  FILE *f = NULL;                                     // Arrange
  object_data *res = calloc(1, sizeof(object_data));  // Arrange
  int status = 0;
  f = fopen(file_name, "r");                                  // Act
  if (!status) status = parse_object_file(file_name, res);    // Act
  ck_assert_int_eq(SUCCESS, status);                          // Assert
  ck_assert_int_eq((int)(res->vertices_array[0] * 10), 5);    // Assert
  ck_assert_int_eq((int)(res->vertices_array[1] * 10), -5);   // Assert
  ck_assert_int_eq((int)(res->vertices_array[2] * 10), -5);   // Assert
  ck_assert_int_eq((int)(res->vertices_array[3] * 10), 5);    // Assert
  ck_assert_int_eq((int)(res->vertices_array[4] * 10), -5);   // Assert
  ck_assert_int_eq((int)(res->vertices_array[5] * 10), 5);    // Assert
  ck_assert_int_eq((int)(res->vertices_array[6] * 10), -5);   // Assert
  ck_assert_int_eq((int)(res->vertices_array[7] * 10), -5);   // Assert
  ck_assert_int_eq((int)(res->vertices_array[8] * 10), 5);    // Assert
  ck_assert_int_eq((int)(res->vertices_array[9] * 10), -5);   // Assert
  ck_assert_int_eq((int)(res->vertices_array[10] * 10), -5);  // Assert
  ck_assert_int_eq((int)(res->vertices_array[11] * 10), -5);  // Assert
  ck_assert_int_eq((int)(res->vertices_array[12] * 10), 5);   // Assert
  ck_assert_int_eq((int)(res->vertices_array[13] * 10), 5);   // Assert
  ck_assert_int_eq((int)(res->vertices_array[14] * 10), -5);  // Assert
  ck_assert_int_eq((int)(res->vertices_array[15] * 10), 5);   // Assert
  ck_assert_int_eq((int)(res->vertices_array[16] * 10), 5);   // Assert
  ck_assert_int_eq((int)(res->vertices_array[17] * 10), 5);   // Assert
  ck_assert_int_eq((int)(res->vertices_array[18] * 10), -5);  // Assert
  ck_assert_int_eq((int)(res->vertices_array[19] * 10), 5);   // Assert
  ck_assert_int_eq((int)(res->vertices_array[20] * 10), 5);   // Assert
  ck_assert_int_eq((int)(res->vertices_array[21] * 10), -5);  // Assert
  ck_assert_int_eq((int)(res->vertices_array[22] * 10), 5);   // Assert
  ck_assert_int_eq((int)(res->vertices_array[23] * 10), -5);  // Assert
  //  ck_assert_int_eq(res->fct_vtx[3], 3);                // Assert
  ck_assert_int_eq(res->polygons_array[3], 3);  // Assert
  ck_assert_int_eq(res->polygons_array[4], 3);  // Assert
  ck_assert_int_eq(res->polygons_array[5], 1);  // Assert
  fclose(f);
  destroy_object(res);
  free(res);
}
END_TEST

/*----------------------------------memory manipulate-------------------*/
START_TEST(alloc_mem_ok) {
  object_data *obj = calloc(1, sizeof(object_data));
  obj->vertices_count = 10;
  obj->polygons_count = 20;              // Arrange
  int status = allocate_memory(obj);     // Act
  ck_assert_int_eq(SUCCESS, status);     // Assert
  ck_assert_ptr_ne((void *)&obj, NULL);  // Assert
  destroy_object(obj);
  free(obj);
}
END_TEST

START_TEST(free_mem) {
  object_data *obj = NULL;                           // Arrange
  obj = (object_data *)malloc(sizeof(object_data));  // Arrange
  obj->vertices_count = 100;
  obj->polygons_count = 200;          // Arrange
  int status = allocate_memory(obj);  // Act
  destroy_object(obj);                // Act
  ck_assert_int_eq(SUCCESS, status);  // Assert
  free(obj);
}
END_TEST

/*-----------------------------parse functions------------------*/
START_TEST(fill_obj3d_verteces) {
  // char *buffer = "v -426.750397 4550.81408 2637.903854 ";  // Arrange
  char *file_name = "objects/deer.obj";  // Arrange
  // FILE *f = NULL;                                                  // Arrange
  object_data *obj = NULL;                           // Arrange
  obj = (object_data *)malloc(sizeof(object_data));  // Arrange
  *obj =
      (object_data){.vertices_count = 772, .polygons_count = 1508};  // Arrange
  int status = 0;
  // f = fopen(file_name, "r");                       // Act
  // if (!status) status = allocate_memory(obj);               // Act
  if (!status) status = parse_object_file(file_name, obj);  // Act
  ck_assert_int_eq(SUCCESS, !status);                       // Assert
  ck_assert_int_eq((int)(obj->vertices_array[0] * 1000000),
                   -295424526);  // Assert
  ck_assert_int_eq((int)(obj->vertices_array[1] * 1000000),
                   482015262);                                       // Assert
  ck_assert_int_eq((int)(obj->vertices_array[2] * 1000000), 10099);  // Assert
  destroy_object(obj);                                               // Act
  free(obj);
}
END_TEST

START_TEST(move) {
  char *file_name = "objects/cube.obj";               // Arrange
  FILE *f = NULL;                                     // Arrange
  object_data *res = calloc(1, sizeof(object_data));  // Arrange
  int status = 0;
  f = fopen(file_name, "r");                          // Act
  if (f) status = parse_object_file(file_name, res);  // Act

  double x = 1.32;
  double y = 1.4563;
  double z = 1.134;
  shift_X(res, x);
  shift_Y(res, y);
  shift_Z(res, z);
  ck_assert_int_eq(SUCCESS, status);                         // Assert
  ck_assert_double_eq((res->vertices_array[0]), 0.5 + x);    // Assert
  ck_assert_double_eq((res->vertices_array[1]), -0.5 + y);   // Assert
  ck_assert_double_eq((res->vertices_array[2]), -0.5 + z);   // Assert
  ck_assert_double_eq((res->vertices_array[3]), 0.5 + x);    // Assert
  ck_assert_double_eq((res->vertices_array[4]), -0.5 + y);   // Assert
  ck_assert_double_eq((res->vertices_array[5]), 0.5 + z);    // Assert
  ck_assert_double_eq((res->vertices_array[6]), -0.5 + x);   // Assert
  ck_assert_double_eq((res->vertices_array[7]), -0.5 + y);   // Assert
  ck_assert_double_eq((res->vertices_array[8]), 0.5 + z);    // Assert
  ck_assert_double_eq((res->vertices_array[9]), -0.5 + x);   // Assert
  ck_assert_double_eq((res->vertices_array[10]), -0.5 + y);  // Assert
  ck_assert_double_eq((res->vertices_array[11]), -0.5 + z);  // Assert
  ck_assert_double_eq((res->vertices_array[12]), 0.5 + x);   // Assert
  ck_assert_double_eq((res->vertices_array[13]), 0.5 + y);   // Assert
  ck_assert_double_eq((res->vertices_array[14]), -0.5 + z);  // Assert
  ck_assert_double_eq((res->vertices_array[15]), 0.5 + x);   // Assert
  ck_assert_double_eq((res->vertices_array[16]), 0.5 + y);   // Assert
  ck_assert_double_eq((res->vertices_array[17]), 0.5 + z);   // Assert
  ck_assert_double_eq((res->vertices_array[18]), -0.5 + x);  // Assert
  ck_assert_double_eq((res->vertices_array[19]), 0.5 + y);   // Assert
  ck_assert_double_eq((res->vertices_array[20]), 0.5 + z);   // Assert
  ck_assert_double_eq((res->vertices_array[21]), -0.5 + x);  // Assert
  ck_assert_double_eq((res->vertices_array[22]), 0.5 + y);   // Assert
  ck_assert_double_eq((res->vertices_array[23]), -0.5 + z);  // Assert
  // ck_assert_int_eq(res->fct_vtx[3], 3);               // Assert
  ck_assert_int_eq(res->polygons_array[1], 2);  // Assert
  ck_assert_int_eq(res->polygons_array[2], 2);  // Assert
  ck_assert_int_eq(res->polygons_array[3], 3);  // Assert
  fclose(f);
  destroy_object(res);
  free(res);
}
END_TEST

START_TEST(rescale) {
  char *file_name = "objects/cube.obj";  // Arrange
  FILE *f = NULL;                        // Arrange
  int status = 0;
  object_data *res = calloc(1, sizeof(object_data));  // Arrange
  f = fopen(file_name, "r");                          // Act
  if (f) status = parse_object_file(file_name, res);  // Act
  double scale = 0.6;
  scale_object(res, scale);
  ck_assert_int_eq(SUCCESS, status);  // Assert
  ck_assert_double_eq((res->vertices_array[0]),
                      0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[1]),
                      -0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[2]),
                      -0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[3]),
                      0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[4]),
                      -0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[5]),
                      0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[6]),
                      -0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[7]),
                      -0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[8]),
                      0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[9]),
                      -0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[10]),
                      -0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[11]),
                      -0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[12]),
                      0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[13]),
                      0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[14]),
                      -0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[15]),
                      0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[16]),
                      0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[17]),
                      0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[18]),
                      -0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[19]),
                      0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[20]),
                      0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[21]),
                      -0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[22]),
                      0.25 * (scale - scale * -1));  // Assert
  ck_assert_double_eq((res->vertices_array[23]),
                      -0.25 * (scale - scale * -1));  // Assert
  // ck_assert_int_eq(res->fct_vtx[3], 3);               // Assert
  ck_assert_int_eq(res->polygons_array[9], 5);   // Assert
  ck_assert_int_eq(res->polygons_array[10], 5);  // Assert
  ck_assert_int_eq(res->polygons_array[11], 7);  // Assert
  fclose(f);
  destroy_object(res);
  free(res);
}
END_TEST

START_TEST(rotateX_test) {
  char *file_name = "objects/cube.obj";               // Arrange
  FILE *f = NULL;                                     // Arrange
  object_data *res = calloc(1, sizeof(object_data));  // Arrange
  int status = 0;
  f = fopen(file_name, "r");                                // Act
  if (!status) status = parse_object_file(file_name, res);  // Act

  double x = 90;
  double sin_x = sin(x * M_PI / 180.0);
  double cos_x = cos(x * M_PI / 180.0);
  rotate_X(res, x);

  ck_assert_int_eq(SUCCESS, status);                   // Assert
  ck_assert_double_eq((res->vertices_array[0]), 0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[1]),
                      cos_x * -0.5 + sin_x * -0.5);    // Assert
  ck_assert_double_eq((res->vertices_array[3]), 0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[4]),
                      cos_x * -0.5 - sin_x * -0.5);  // Assert

  ck_assert_double_eq((res->vertices_array[6]), -0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[7]),
                      cos_x * -0.5 - sin_x * -0.5);     // Assert
  ck_assert_double_eq((res->vertices_array[9]), -0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[10]),
                      cos_x * -0.5 + sin_x * -0.5);     // Assert
  ck_assert_double_eq((res->vertices_array[12]), 0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[13]),
                      cos_x * 0.5 - sin_x * 0.5);       // Assert
  ck_assert_double_eq((res->vertices_array[15]), 0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[16]),
                      cos_x * 0.5 + sin_x * 0.5);        // Assert
  ck_assert_double_eq((res->vertices_array[18]), -0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[19]),
                      cos_x * 0.5 + sin_x * 0.5);        // Assert
  ck_assert_double_eq((res->vertices_array[21]), -0.5);  // Assert
  // ck_assert_double_eq((res->vertices_array[22]), -0.5);  // Assert
  //  ck_assert_int_eq(res->fct_vtx[3], 3);               // Assert
  //  ck_assert_int_eq(res->polygons[3].vertices[0], 6);  // Assert
  //  ck_assert_int_eq(res->polygons[3].vertices[1], 7);  // Assert
  //  ck_assert_int_eq(res->polygons[3].vertices[2], 3);  // Assert
  fclose(f);
  destroy_object(res);
  free(res);
}
END_TEST

START_TEST(rotateZ_test) {
  char *file_name = "objects/cube.obj";               // Arrange
  FILE *f = NULL;                                     // Arrange
  object_data *res = calloc(1, sizeof(object_data));  // Arrange
  int status = 0;
  f = fopen(file_name, "r");                                // Act
  if (!status) status = parse_object_file(file_name, res);  // Act

  double x = 90;
  double sin_x = sin(-x * M_PI / 180.0);
  double cos_x = cos(x * M_PI / 180.0);
  rotate_Z(res, x);
  ck_assert_int_eq(SUCCESS, status);                    // Assert
  ck_assert_double_eq((res->vertices_array[2]), -0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[1]),
                      cos_x * -0.5 + sin_x * 0.5);     // Assert
  ck_assert_double_eq((res->vertices_array[5]), 0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[4]),
                      cos_x * -0.5 + sin_x * 0.5);  // Assert

  ck_assert_double_eq((res->vertices_array[8]), 0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[7]),
                      cos_x * -0.5 + sin_x * -0.5);      // Assert
  ck_assert_double_eq((res->vertices_array[11]), -0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[10]),
                      cos_x * -0.5 + sin_x * -0.5);      // Assert
  ck_assert_double_eq((res->vertices_array[14]), -0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[13]),
                      cos_x * 0.5 + sin_x * 0.5);       // Assert
  ck_assert_double_eq((res->vertices_array[17]), 0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[16]),
                      cos_x * 0.5 + sin_x * 0.5);       // Assert
  ck_assert_double_eq((res->vertices_array[20]), 0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[19]),
                      cos_x * 0.5 + sin_x * -0.5);       // Assert
  ck_assert_double_eq((res->vertices_array[23]), -0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[22]),
                      cos_x * 0.5 + sin_x * -0.5);  // Assert
  // ck_assert_int_eq(res->fct_vtx[3], 3);               // Assert
  // ck_assert_int_eq(res->polygons[3].vertices[0], 6);  // Assert
  // ck_assert_int_eq(res->polygons[3].vertices[1], 7);  // Assert
  // ck_assert_int_eq(res->polygons[3].vertices[2], 3);  // Assert
  fclose(f);
  destroy_object(res);
  free(res);
}
END_TEST

START_TEST(rotateY_test) {
  char *file_name = "objects/cube.obj";               // Arrange
  FILE *f = NULL;                                     // Arrange
  object_data *res = calloc(1, sizeof(object_data));  // Arrange
  int status = 0;
  f = fopen(file_name, "r");                                // Act
  if (!status) status = parse_object_file(file_name, res);  // Act

  double y = 90;
  double sin_y = sin(y * M_PI / 180.0);
  double cos_y = cos(y * M_PI / 180.0);
  rotate_Y(res, y);
  ck_assert_int_eq(SUCCESS, status);  // Assert
  ck_assert_double_eq((res->vertices_array[0]),
                      cos_y * 0.5 + sin_y * -0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[3]),
                      cos_y * 0.5 + sin_y * 0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[6]),
                      cos_y * -0.5 + sin_y * 0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[9]),
                      cos_y * -0.5 + sin_y * -0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[12]),
                      cos_y * 0.5 + sin_y * -0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[15]),
                      cos_y * 0.5 + sin_y * 0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[18]),
                      cos_y * -0.5 + sin_y * 0.5);  // Assert
  ck_assert_double_eq((res->vertices_array[21]),
                      cos_y * -0.5 + sin_y * -0.5);  // Assert
  // ck_assert_int_eq(res->fct_vtx[3], 3);               // Assert
  // ck_assert_int_eq(res->polygons[3].vertices[0], 6);  // Assert
  // ck_assert_int_eq(res->polygons[3].vertices[1], 7);  // Assert
  // ck_assert_int_eq(res->polygons[3].vertices[2], 3);  // Assert
  fclose(f);
  destroy_object(res);
  free(res);
}
END_TEST

Suite *vue_3d_common_suite() {
  Suite *s_3dObj;
  TCase *tc_file_operations, *tc_memory, *tc_parse, *tc_affine;

  s_3dObj = suite_create("file manipulation suite");

  tc_file_operations = tcase_create("opening file");
  tcase_add_test(tc_file_operations, file_open_fail);
  tcase_add_test(tc_file_operations, file_open_ok);
  tcase_add_test(tc_file_operations, count_vtx_fct);
  tcase_add_test(tc_file_operations, read_vertices);
  suite_add_tcase(s_3dObj, tc_file_operations);

  tc_memory = tcase_create("memory manipul");
  tcase_add_test(tc_memory, alloc_mem_ok);
  tcase_add_test(tc_memory, free_mem);
  suite_add_tcase(s_3dObj, tc_memory);

  tc_parse = tcase_create("parse func");
  tcase_add_test(tc_parse, fill_obj3d_verteces);
  // tcase_add_test(tc_parse, fill_facet_ok);
  // tcase_add_test(tc_parse, count_vtx_of_facet_ok);
  // tcase_add_test(tc_parse, parse_vertices_ok);
  suite_add_tcase(s_3dObj, tc_parse);

  tc_affine = tcase_create("affine func");
  tcase_add_test(tc_affine, move);
  tcase_add_test(tc_affine, rescale);
  tcase_add_test(tc_affine, rotateX_test);
  tcase_add_test(tc_affine, rotateZ_test);
  tcase_add_test(tc_affine, rotateY_test);

  suite_add_tcase(s_3dObj, tc_affine);

  return s_3dObj;
}
