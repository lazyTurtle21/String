//
// Created by Yevhenii on 21/10/2018.
//

#ifndef STRANGE_ONE_SECOND_TASK_H
#define STRANGE_ONE_SECOND_TASK_H

#include <stdio.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct {
    size_t capacity_m; // Розмір блока
    size_t size_m;	   // Фактичний розмір стрічки
    char*  data;	   // Вказівник на блок пам'яті
} my_str_t;

int my_str_create(my_str_t* str, size_t buf_size);
int my_str_read_file_until_blankspace(my_str_t* str, FILE* file);
int my_str_pushback(my_str_t* str, char c);
int my_str_getc(const my_str_t* str, size_t index);
int my_str_remove_c(my_str_t* str, size_t pos);
int my_str_putc(my_str_t* str, size_t index, char c);
const char* my_str_get_cstr(my_str_t* str);

#endif //STRANGE_ONE_SECOND_TASK_H
