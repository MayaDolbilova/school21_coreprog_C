#ifndef SRC_S21_SMART_CALC_1_0_H_
#define SRC_S21_SMART_CALC_1_0_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256

typedef struct {
  double *arr;
  int size;
  int top_index;
} stack_numbers;

typedef struct {
  char *arr;
  int size;
  int top_index;
} stack_chars;

double functions(double number, char symb);
int calculator(char *inputstring, char *number_x, double *result);
int checking_enter_string(char *string, char *fin_str);
int check_brackets(char *string, int length);
void validator(char *string, int length, char *exit_str);
int fin_check(char *string);
int is_stack_numb_empty(stack_numbers *stack);
int is_stack_char_empty(stack_chars *stack);
stack_numbers *initialize_numbers(int size);
stack_chars *initialize_chars(int size);
double pop_numbers(stack_numbers *stack);
char pop_chars(stack_chars *stack);
void push_chars(char x, stack_chars *stack);
void push_numbers(double x, stack_numbers *stack);
void cleaner_numbers(stack_numbers *stack);
void cleaner_chars(stack_chars *stack);
char peek_chars(stack_chars *stack);
char peek_numbers(stack_numbers *stack);
int priority(char x);
void polish_notation(char *string, char *fin_str);
double calculate(char *polsk, double x, int *error);
double counting(double first_n, double second_n, char symb, int **error);
#endif  //  SRC_S21_SMART_CALC_1_0_H_
