#include <string.h>
#include <errno.h>
#include "my_str_t.h"


//! Рахує кількість символів у с-стрічці без останнього ('\0')
static size_t cstr_len(const char* str) {
    if (!str) {
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return (size_t)EXIT_FAILURE;
    }
    size_t length = 0;
    while (*(str + ++length)) {}
    return length;
}

//! Створити стрічку із буфером вказаного розміру. Пам'ять виділяється динамічно.
//! Варто виділяти buf_size+1 для спрощення роботи my_str_get_cstr().
int my_str_create(my_str_t* str, size_t buf_size) {
    if (!str) {
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return EXIT_FAILURE;
    }

    str->data = malloc(buf_size + 1);

    if (!str->data) {
        fprintf(stderr, "Memory allocation error: %s\n", strerror(ENOMEM));
        return EXIT_FAILURE;
    }
    str->size_m = 0;
    str->capacity_m = buf_size;

    return EXIT_SUCCESS;
}

//! Створити стрічку із буфером вказаного розміру із переданої С-стрічки.
//! Якщо розмір -- 0, виділяє блок, рівний розміру С-стрічки, якщо
//! менший за її розмір -- вважати помилкою.
//! Пам'ять виділяється динамічно.
int my_str_from_cstr(my_str_t* str, const char* cstr, size_t buf_size) {
    size_t str_length = cstr_len(cstr);

    if (!str) {
        return fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return EXIT_FAILURE;
    }
    if (buf_size < str_length)
        return EXIT_FAILURE;

    str->size_m = str_length;
    if (buf_size <= 0)
        str->capacity_m = str->size_m + 1;
    else
        str->capacity_m = buf_size;
    str->data = malloc(buf_size);

    if (!str->data) {
        fprintf(stderr, "Memory allocation error: %s\n", strerror(ENOMEM));
        return EXIT_FAILURE;
    }

    for (int i = 0; i < str->size_m; i++)
        *(str->data + i) = *(cstr + i);
    return EXIT_SUCCESS;
}

//! Звільнє пам'ять, знищуючи стрічку:
void my_str_free(my_str_t* str){
    if (!str)
        return;
    free(str->data);
    str->data = 0;
    str->size_m = 0;
    str->capacity_m = 0;
}

//! Повертає розмір стрічки:
size_t my_str_size(const my_str_t* str) {
    if (!str) {
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return (size_t)EXIT_FAILURE;
    }
    return str->size_m;
}

//! Повертає розмір буфера:
size_t my_str_capacity(const my_str_t* str) {
    if (!str) {
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return (size_t) EXIT_FAILURE;
    }
    return str->capacity_m;
}

//! Повертає булеве значення, чи стрічка порожня:
int my_str_empty(const my_str_t* str){
    if (!str || str->size_m == 0)
        return 1;
    return 0;
}

//! Повертає символ у вказаній позиції, або -1, якщо вихід за межі стрічки
int my_str_getc(const my_str_t* str, size_t index) {
    if (!str) {
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return EXIT_FAILURE;
    }

    if (index < 0 || index >= str->size_m)
        return EXIT_FAILURE;

    return *(str->data + index);
}

//! Записує символ у вказану позиції (заміняючи той, що там був),
int my_str_putc(my_str_t* str, size_t index, char c) {
    if (!str) {
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return EXIT_FAILURE;
    }
    if (index < 0 || index >= str->size_m)
        return EXIT_FAILURE;
    *(str->data + index) = c;
    return EXIT_SUCCESS;
}


//! Додає символ в кінець.
//! Повертає 0, якщо успішно, -1, якщо буфер закінчився.
int my_str_pushback(my_str_t* str, char c){
    if (!str) {
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return EXIT_FAILURE;;
    }
    if (str->capacity_m <= str->size_m)
        return EXIT_FAILURE;
    *(str->data + str->size_m++) = c;
    return EXIT_SUCCESS;
}

//! Викидає символ з кінця.
//! Повертає його, якщо успішно, -1, якщо буфер закінчився.
int my_str_popback(my_str_t* str){
    if (!str) {
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return EXIT_FAILURE;
    }
    if(0 < str->size_m <= str->capacity_m){
        char c_to_pop = *(str->data + str->size_m - 1);
        *(str->data + --str->size_m) = 0;
        return c_to_pop;
    }
    return EXIT_FAILURE;
}

//! Копіює стрічку. Якщо reserve == true,
//! то із тим же розміром буферу, що й вихідна,
//! інакше -- із буфером мінімального достатнього розміру.
//! Старий вміст стрічки перед тим звільняє, за потреби.
int my_str_copy(const my_str_t* from,  my_str_t* to, int reserve){
    if (!from || !to) {
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return EXIT_FAILURE;
    }

    if (to->capacity_m < from->size_m)
        return EXIT_FAILURE;

    if (reserve == 1)
        to->capacity_m = from->capacity_m;
    else
        to->capacity_m = from->size_m;

    to->size_m = from->size_m;
    for (int i = 0; i < from->size_m; i++)
        *(to->data + i) = *(from->data + i);

    return EXIT_SUCCESS;
}

//! Очищає стрічку -- робить її порожньою. Складність має бути О(1).
void my_str_clear(my_str_t* str){
    if (!str)
        return;
    str->size_m = 0;
}

//! Вставити символ у стрічку в заданій позиції, змістивши решту символів праворуч.
int my_str_insert_c(my_str_t* str, char c, size_t pos) {
    if (!str){
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return EXIT_FAILURE;
    }

    if (str->size_m >= str->capacity_m || pos >= str->size_m)
        return EXIT_FAILURE;

    size_t size = str->size_m;
    while (size-- != pos)
        *(str->data + size + 1) = *(str->data + size);

    *(str->data + pos) = c;
    str->size_m++;

    return EXIT_SUCCESS;
}

//! Вставити стрічку в заданій позиції, змістивши решту символів праворуч.
int my_str_insert(my_str_t* str, const my_str_t* from, size_t pos){
    if (!str || !from) {
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return EXIT_FAILURE;
    }
    if ((str->size_m + from->size_m > str->capacity_m) ||(pos >= str->size_m))
        return EXIT_FAILURE;

    size_t size = str->size_m;
    size_t insert_size = from->size_m;

    while (size != pos){
        *(str->data + size + insert_size) = *(str->data + size);
        size--;
    }

    while(insert_size){
        *(str->data + size + insert_size) = *(from->data + insert_size - 1);
        insert_size--;
    }

    str->size_m += from->size_m;
    return EXIT_SUCCESS;
}

//! Вставити C-стрічку в заданій позиції, змістивши решту символів праворуч.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_insert_cstr(my_str_t* str, const char* from, size_t pos) {
    if (!str || !from){
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return EXIT_FAILURE;
    }

    if ((str->size_m + cstr_len(from)) > str->capacity_m ||(pos >= str->size_m))
        return EXIT_FAILURE;

    int size = str->size_m;
    int insert_size = cstr_len(from);

    while (size-- != pos)
        *(str->data + size + insert_size) = *(str->data + size);

    while (*(from))
        *(str->data + pos++) = *(from++);

    str->size_m += insert_size;

    return EXIT_SUCCESS;
}

//! Додати стрічку в кінець.
int my_str_append(my_str_t* str, const my_str_t* from){
    if (!str || !from) {
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return EXIT_FAILURE;
    }

    if(str->capacity_m - str->size_m < from->size_m)
        return EXIT_FAILURE;

    for (int i = 0; i < from->size_m; i++)
        my_str_pushback(str, *(from->data + i));

    return EXIT_SUCCESS;
}

//! Додати С-стрічку в кінець.
int my_str_append_cstr(my_str_t* str, const char* from){
    if (!str || !from) {
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return EXIT_FAILURE;
    }

    int len = cstr_len(from);
    if(str->capacity_m - str->size_m < len)
        return EXIT_FAILURE;

    for (int i = 0; i < len; i++)
        my_str_pushback(str, *(from + i));

    return EXIT_SUCCESS;
}


//! Порівняти стрічки, повернути 0, якщо рівні (за вмістом!)
//! від'ємне значення, якщо перша менша, додатнє -- якщо друга.
int my_str_cmp(my_str_t* str1, const char* str2){
    if (!str1){
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return EXIT_FAILURE;
    }

    int counter = 0;
    for (int i = 0; i < str1->size_m; i ++){
        if (*(str2 + i) == '\0')
            return str1->size_m - counter;
        if (*(str2 + i) == *(str1->data + i))
            counter ++;
    }
    int str2_len = str1->size_m;
    while(*(str2 + str2_len++)){}

    return counter - str2_len;
}



//! Скопіювати підстрічку, із beg включно, по end не включно ([beg, end)).
//! Якщо end виходить за межі str -- скопіювати скільки вдасться, не вважати
//! це помилкою. Якщо ж в ціловій стрічці замало місця, або beg більший
//! за розмір str -- це помилка. Повернути відповідний код завершення.
int my_str_substr(const my_str_t* str, char* to, size_t beg, size_t end){
    return 0;
}


//! Повернути вказівник на С-стрічку, еквівалентну str.
//! Вважатимемо, що змінювати цю С-стрічку заборонено.
//! Якщо в буфері було зарезервовано на байт більше за макс. розмір, можна
//! просто додати нульовий символ в кінці та повернути вказівник data.
const char* my_str_get_cstr(my_str_t* str) {
    if (!str || !(str->data))
        return NULL;
    *(str->data + str->size_m) = '\0';
    return str->data;
}

//! Знайти першу підстрічку в стрічці, повернути номер її
//! початку або -1u, якщо не знайдено. from -- місце, з якого починати шукати.
//! Якщо більше за розмір -- вважати, що не знайдено.
size_t my_str_find(const my_str_t* str, const my_str_t* tofind, size_t from){
    if (!str || !tofind) {
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return (size_t)EXIT_FAILURE;
    }

    if (str->size_m <= from)
        return (size_t)EXIT_FAILURE;

    size_t size = str->size_m;
    size_t subsize = tofind->size_m;
    size_t j;
    for (from; from < size - subsize; from ++){
        for (j = 0; j < subsize; j++){
            if (*(str->data + from + j) != *(tofind-> data + j))
                break;
        }
        if (j == subsize)
            return from;
    }
    return (size_t)EXIT_FAILURE;
}

//! Знайти перший символ в стрічці, повернути його номер
//! або -1u, якщо не знайдено. from -- місце, з якого починати шукати.
//! Якщо більше за розмір -- вважати, що не знайдено.
size_t my_str_find_c(const my_str_t* str, char tofind, size_t from){
    if (!str) {
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return (size_t)EXIT_FAILURE;
    }
    if (from >= str->size_m)
        return (size_t)EXIT_FAILURE;

    for (from; from < str->size_m; from++){
        if (*(str->data + from) == tofind)
            return from;
    }
    return (size_t)EXIT_FAILURE;
}

//! Знайти символ в стрічці, для якого передана
//! функція повернула true, повернути його номер
//! або -1u, якщо не знайдено:
size_t my_str_find_if(const my_str_t* str, int (*predicate)(char)){
    if (!str) {
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return (size_t) EXIT_FAILURE;
    }

    for (size_t i = 0; i < str->size_m; i++){
        if (predicate(*(str->data + i)) == 1)
            return i;
    }
    return (size_t)EXIT_FAILURE;
}

//! Прочитати стрічку із файлу. Повернути, 0, якщо успішно, -1,
//! якщо сталися помилки. Кінець вводу -- не помилка, однак,
//! слід не давати читанню вийти за межі буфера!
//! Рекомендую скористатися fgets().
//! the name of functionn was changed
int my_str_read_file_until_end(my_str_t* str, FILE* file) {
    if (!str || !file) {
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return EXIT_FAILURE;
    }

    if (!fgets(str->data, str->capacity_m, file))
        return EXIT_FAILURE;

    str->size_m = cstr_len(str->data);
    return EXIT_SUCCESS;
}

//! this function was added to the interface
int my_str_read_file_until_blankspace(my_str_t* str, FILE* file) {
    if (!str || !file) {
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return EXIT_FAILURE;
    }

    char format[32];
    snprintf(format, sizeof(format), "%%%ds", str->capacity_m - 1);
    int res = fscanf(file, format, str->data + str->size_m);

    if (res == -1)
        return EXIT_FAILURE;

    str->size_m = cstr_len(str->data);

    return EXIT_SUCCESS;
}

//! Аналог my_str_read_file, із stdin
int my_str_read(my_str_t* str){
    if (!str){
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return EXIT_FAILURE;
    }
    if (!fgets(str->data, str->capacity_m + 1, stdin))
        return EXIT_FAILURE;
    str->size_m = cstr_len(str->data);
    return EXIT_SUCCESS;
}


//! FUNCTIONS ADDED TO THE INTERFACE

//! Removes character in position <pos> from string
int my_str_remove_c(my_str_t* str, size_t pos) {
    if (!str) {
        return fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return EXIT_FAILURE;
    }
    if (pos > str->size_m)
        return EXIT_FAILURE;

    while (pos < str->size_m)
    {
        *(str->data + pos) = *(str->data + pos + 1);
        pos++;
    }

    if (pos == str->size_m)
        str->size_m--;

    return EXIT_SUCCESS;
}

//! Prints a string
int print_str(const my_str_t* str){
    if (!str){
        fprintf(stderr, "Null pointer error: %s\n", strerror(EFAULT));
        return EXIT_FAILURE;
    }
    for (int i = 0; i < str->size_m; i++)
        printf("%c", *(str->data + i));
    printf("\n");
}
