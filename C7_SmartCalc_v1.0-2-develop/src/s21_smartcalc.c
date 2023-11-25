#include "s21_smartcal.h"
double functions(double number, char symb) {
  double res = 0.0;
  double base = 0.0;
  switch (symb) {
    case 'c':
      res = cos(number);
      break;
    case 's':
      res = sin(number);
      break;
    case 't':
      res = tan(number);
      break;
    case 'a':
      res = acos(number);
      break;
    case 'n':
      res = asin(number);
      break;
    case 'f':
      res = atan(number);
      break;
    case 'q':
      res = sqrt(number);
      break;
    case 'l':
      res = log(number);
      break;
    case 'g':
      base = 10.0;  // Основание логарифма
      res = log(number) / log(base);
      break;
    case '^':
      break;
    default:
      res = 0.0;
      break;
  }
  return res;
}
int calculator(char *inputstring, char *number_x, double *result) {
  int flag = 1;
  char fin_str[MAX_SIZE + 50] = {0};
  double x_value = 0.0;
  if (strlen(number_x)) x_value = atof(number_x);
  if (strlen(inputstring) < 256) {
    flag = checking_enter_string(inputstring, fin_str);

    if (flag == 0) {
      char polsk_not[MAX_SIZE + 50] = {0};
      polish_notation(fin_str, polsk_not);
      for (int i = 0; i < (int)strlen(polsk_not); i++) {
        printf("%c", polsk_not[i]);
      }
      *result = calculate(polsk_not, x_value, &flag);
    }
  } else {
    flag = 2;
  }
  return flag;
}

int checking_enter_string(char *string, char *fin_str) {
  int flag = 1;
  int length = strlen(string);
  if (check_brackets(string, length) == 0) {
    validator(string, length, fin_str);
    flag = 0;
  }
  if (fin_str != NULL) {
    if (fin_check(fin_str) != 0) {
      flag = 1;
    }
  }
  return flag;
}

int check_brackets(char *string, int length) {
  int flag = 1;
  int count_brackets = 0;
  for (int i = 0; i < length; i++) {
    char x = string[i];
    if (x == '(') {
      count_brackets++;
    } else if (x == ')') {
      count_brackets--;
    }
  }
  if (count_brackets == 0) {
    flag = 0;
  }
  return flag;
}

void validator(char *string, int length, char *exit_str) {
  int index = 0;
  for (int i = 0; i < length; i++) {
    if (strncmp(string + i, "cos", 3) == 0) {
      exit_str[index++] = 'c';
      i += 2;
    } else if (strncmp(string + i, "sin", 3) == 0) {
      exit_str[index++] = 's';
      i += 2;
    } else if (strncmp(string + i, "tan", 3) == 0) {
      exit_str[index++] = 't';
      i += 2;
    } else if (strncmp(string + i, "acos", 4) == 0) {
      exit_str[index++] = 'a';
      i += 3;
    } else if (strncmp(string + i, "asin", 4) == 0) {
      exit_str[index++] = 'n';
      i += 3;
    } else if (strncmp(string + i, "atan", 4) == 0) {
      exit_str[index++] = 'f';
      i += 3;
    } else if (strncmp(string + i, "sqrt", 4) == 0) {
      exit_str[index++] = 'q';
      i += 3;
    } else if (strncmp(string + i, "ln", 2) == 0) {
      exit_str[index++] = 'l';
      i++;
    } else if (strncmp(string + i, "log", 3) == 0) {
      exit_str[index++] = 'g';
      i += 2;
    } else if (strncmp(string + i, "mod", 3) == 0) {
      exit_str[index++] = ' ';
      exit_str[index++] = 'm';
      exit_str[index++] = ' ';
      i += 2;
    } else if (i == 0 && string[i] == '-') {
      exit_str[index++] = '(';
      exit_str[index++] = '0';
      exit_str[index++] = '-';
      exit_str[index++] = string[i + 1];
      i++;
      exit_str[index++] = ')';
    } else if (string[i] == '(' && string[i + 1] == '-') {
      exit_str[index++] = '(';
      exit_str[index++] = '(';
      exit_str[index++] = '0';
      exit_str[index++] = '-';
      exit_str[index++] = string[i + 2];
      i += 2;
      exit_str[index++] = ')';
    } else if ((string[i] >= '0' && string[i] <= '9') &&
               (string[i + 1] == '(' || string[i + 1] == 'a' ||
                string[i + 1] == 'c' || string[i + 1] == 's' ||
                string[i + 1] == 't' || string[i + 1] == 'm' ||
                string[i + 1] == 'l')) {
      exit_str[index++] = string[i];
      exit_str[index++] = '*';
    } else if (string[i] == ')' &&
               (string[i + 1] == '(' || string[i + 1] == 'a' ||
                string[i + 1] == 'c' || string[i + 1] == 's' ||
                string[i + 1] == 't' || string[i + 1] == 'm' ||
                string[i + 1] == 'l')) {
      exit_str[index++] = string[i];
      exit_str[index++] = '*';
    } else if (string[i] == 'x' &&
               (string[i + 1] >= '0' && string[i + 1] <= '9')) {
      exit_str[index++] = string[i];
      exit_str[index++] = '*';
    } else if ((string[i] >= '0' && string[i] <= '9') && string[i + 1] == 'x') {
      exit_str[index++] = string[i];
      exit_str[index++] = '*';
    } else {
      exit_str[index++] = string[i];
    }
  }
}

int fin_check(char *string) {
  int length = strlen(string);
  int flag = 0;
  for (int i = 0; i < length; i++) {
    if (string[i] == '+' || string[i] == '-' || string[i] == '/' ||
        string[i] == '*' || string[i] == '^') {
      if (string[i + 1] == '+' || string[i + 1] == '-' ||
          string[i + 1] == '/' || string[i + 1] == '*' ||
          string[i + 1] == '^') {
        flag = 1;
      }
    }
    if ((strchr("cstanfqlgm", string[i]) != NULL) && string[i + 1] == '(' &&
        (string[i + 2] == '\0' || string[i + 2] == ')')) {
      flag = 1;
    }
    if (i == 0 &&
        (string[i] == '^' || (string[i] == ' ' && string[i + 1] == 'm'))) {
      flag = 1;
    }
  }
  return flag;
}

int is_stack_numb_empty(stack_numbers *stack) {
  int flag = 1;
  if (stack->top_index != 0) {
    flag = 0;
  }
  return flag;
}
int is_stack_char_empty(stack_chars *stack) {
  int flag = 1;
  if (stack->top_index != 0) {
    flag = 0;
  }
  return flag;
}

stack_numbers *initialize_numbers(int size) {
  stack_numbers *stack = malloc(sizeof(stack_numbers));
  if (stack != NULL) {
    stack->arr = malloc(size * sizeof(double));
    stack->top_index = 0;
    stack->size = 0;
  }
  return stack;
}

stack_chars *initialize_chars(int size) {
  stack_chars *stack = malloc(sizeof(stack_chars));
  if (stack != NULL) {
    stack->arr = malloc(size * sizeof(char));
    stack->top_index = 0;
    stack->size = 0;
  }
  return stack;
}

double pop_numbers(stack_numbers *stack) {
  int empty = is_stack_numb_empty(stack);
  double number = 0.0;
  if (empty == 0) {
    number = stack->arr[stack->top_index - 1];
    stack->top_index--;
  }
  return number;
}

char pop_chars(stack_chars *stack) {
  int empty = is_stack_char_empty(stack);
  char char_stack = '0';
  if (empty == 0) {
    char_stack = stack->arr[stack->top_index - 1];
    stack->top_index--;
  }
  return char_stack;
}

void push_chars(char x, stack_chars *stack) {
  stack->arr[stack->top_index] = x;
  stack->top_index++;
}

void push_numbers(double x, stack_numbers *stack) {
  stack->arr[stack->top_index] = x;
  stack->top_index++;
}

void cleaner_numbers(stack_numbers *stack) {
  if (stack != NULL) {
    if (stack->arr != NULL) {
      free(stack->arr);
      stack->top_index = 0;
    }
    free(stack);
  }
}

void cleaner_chars(stack_chars *stack) {
  if (stack != NULL) {
    if (stack->arr != NULL) {
      free(stack->arr);
      stack->top_index = 0;
    }
    free(stack);
  }
}
char peek_chars(stack_chars *stack) {
  char flag = '0';
  if (stack->top_index != 0) {
    flag = stack->arr[stack->top_index - 1];
  }
  return flag;
}
char peek_numbers(stack_numbers *stack) {
  float flag = 0.0;
  if (stack->top_index != 0) {
    flag = stack->arr[stack->top_index - 1];
  }
  return flag;
}

int priority(char x) {
  int prior = 0;
  if ((x >= 48 && x <= 57) || x == 46 || x == 120) {
    prior = 0;
  } else if (x == ')' || x == '(') {
    prior = 1;
  } else if (x == '+' || x == '-') {
    prior = 2;
  } else if (x == 'm' || x == '/' || x == '*') {
    prior = 3;
  } else if (x == 'c' || x == 's' || x == 't' || x == 'a' || x == 'n' ||
             x == 'f' || x == 'q' || x == 'l' || x == 'g' || x == '^') {
    prior = 4;
  }

  return prior;
}

void polish_notation(char *string, char *fin_str) {
  int length = strlen(string);
  int prior = 0;
  int index = 0;
  int prior_top = 0;
  stack_chars *s = initialize_chars(MAX_SIZE);
  for (int i = 0; i < length; i++) {
    prior = priority(string[i]);
    if (prior == 1 && string[i] == ')') {
      while (peek_chars(s) != '(' && s->top_index != 0) {
        fin_str[index++] = pop_chars(s);
      }
      pop_chars(s);
    }
    if (prior == 0) {
      fin_str[index++] = string[i];
      if (priority(string[i + 1]) != 0) {
        fin_str[index++] = ' ';
      }
    }
    if (s->top_index != 0) {
      prior_top = priority(s->arr[s->top_index - 1]);
    }
    if (prior <= prior_top && prior != 0 && prior != 1 && s->top_index != 0) {
      while (prior <= prior_top && prior != 0 && s->top_index != 0) {
        fin_str[index++] = pop_chars(s);
        prior_top = priority(s->arr[s->top_index - 1]);
      }
    }
    if (string[i] != ')' && prior != 0) {
      push_chars(string[i], s);
    }
  }
  while (s->top_index != 0) {
    fin_str[index++] = pop_chars(s);
  }
  cleaner_chars(s);
}

double calculate(char *polsk, double x, int *error) {
  int length = strlen(polsk);
  double res = 0.0;
  int prior = 0;
  double top_number = 0.0;
  double under_top_number = 0.0;
  char number[MAX_SIZE + 100] = {0};
  double mid_numb = 0.0;
  int index = 0;
  double mid_res = 0.0;
  stack_numbers *s = initialize_numbers(MAX_SIZE);

  for (int i = 0; i < length; i++) {
    prior = priority(polsk[i]);
    if (polsk[i] == 'x') {
      push_numbers(x, s);
    } else if (polsk[i] == ' ') {
      // printf("ha");
    } else {
      if (prior == 2 || prior == 3) {
        if (s->top_index != 0) {
          top_number = pop_numbers(s);
          under_top_number = pop_numbers(s);
          mid_res = counting(top_number, under_top_number, polsk[i], &error);
          push_numbers(mid_res, s);
        }

      } else if (prior == 4) {
        if (polsk[i] != '^') {
          top_number = pop_numbers(s);
          mid_res = functions(top_number, polsk[i]);
          push_numbers(mid_res, s);
        } else {
          top_number = pop_numbers(s);
          under_top_number = pop_numbers(s);
          mid_res = pow(under_top_number, top_number);
          push_numbers(mid_res, s);
        }
      } else {
        while (polsk[i] != 32 && i < length) {
          number[index++] = polsk[i];
          if (priority(polsk[i + 1]) == 0) {
            i++;
          } else {
            break;
          }
        }
        mid_numb = atof(number);
        memset(number, 0, sizeof(number));
        index = 0;

        push_numbers(mid_numb, s);
      }
    }
  }
  res = pop_numbers(s);
  cleaner_numbers(s);
  return res;
}

double counting(double first_n, double second_n, char symb, int **error) {
  double res = 0.0;
  double remainder = 0.0;
  switch (symb) {
    case '+':
      res = first_n + second_n;
      break;
    case '-':
      res = second_n - first_n;
      break;
    case '/':
      if (first_n != 0) {
        res = second_n / first_n;
      } else {
        res = 0.0;
        **error = 1;
      }
      break;
    case '*':
      res = second_n * first_n;
      break;
    case 'm':
      if (first_n != 0) {
        remainder = second_n / first_n;
        res = second_n - (first_n * (int)remainder);
      } else {
        res = 0.0;
        **error = 1;
      }
      break;
    default:
      **error = 1;
      break;
  }
  return res;
}

// int main() {
// char str[MAX_SIZE]={0};
// strcpy(str, "2^2");
// char *x = "5";
// double res = 1.0;
// int error = 0;
// error = calculator(str, x, &res);
// printf("\n%d", error);
// printf("\n%f", res);
// return 0;
// }
