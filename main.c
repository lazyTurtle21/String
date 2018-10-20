#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct {
    size_t capacity_m; // Розмір блока
    size_t size_m;	   // Фактичний розмір стрічки
    char*  data;	   // Вказівник на блок пам'яті

} my_str_t;

static int print(const char* str, size_t size) {
    for (int i = 0; i < size; i++)
        printf("%c ", *(str + i));
    printf("\n");
    return 0;
}

static int print_str(const my_str_t* str){
    if (!str)
        return -3;
    for (int i = 0; i < str->size_m; i++)
        printf("%c ", *(str->data + i));
    printf("\n");
}


//? -3 -- null pointer exception
//? рахує кількість символів без останнього ('\0')
const size_t strlen(const char* str) {
    if (!str)
        return -3;

    size_t length = 0;
    while (*(str + ++length)) {}
    return length;
}

//! Створити стрічку із буфером вказаного розміру. Пам'ять виділяється динамічно.
//! Варто виділяти buf_size+1 для спрощення роботи my_str_get_cstr().
//? -3 -- null pointer exception
int my_str_create(my_str_t* str, size_t buf_size) {
    if (!str)
        return -3;

    str->data = malloc((buf_size + 1));

    if (!str->data)
        return -1;

    str->size_m = 0;
    str->capacity_m = buf_size;

    return 0;
}

//! Створити стрічку із буфером вказаного розміру із переданої С-стрічки.
//! Якщо розмір -- 0, виділяє блок, рівний розміру С-стрічки, якщо
//! менший за її розмір -- вважати помилкою.
//! Пам'ять виділяється динамічно.
//! 0 -- якщо все ОК, -1 -- недостатній розмір буфера, -2 -- не вдалося виділити пам'ять

//? -3 -- null pointer exception
//? чи вартує в цій функції використати my_str_create?
//? чи треба тут (str->capacity_m = str->size_m + 1) виділяти +1 резервний байт місця?
//? чи треба записувати '\0' в кінець str->data?
int my_str_from_cstr(my_str_t* str, const char* cstr, size_t buf_size) {
    size_t str_length = strlen(cstr);

    if (!str)
        return -3;
    if (buf_size < str_length)
        return -1;

    str->size_m = str_length;
    if (buf_size <= 0)
        str->capacity_m = str->size_m + 1;
    else
        str->capacity_m = buf_size;
    str->data = malloc(buf_size);

    if (!str->data)
        return -2;

    for (int i = 0; i < str->size_m; i++)
        *(str->data + i) = *(cstr + i);

    return 0;
}

//! Звільнє пам'ять, знищуючи стрічку:
void my_str_free(my_str_t* str){
    free(str->data);
    str->data = 0;
    str->size_m = 0;
    str->capacity_m = 0;
}

//! Повертає розмір стрічки:
//? -3 -- null pointer exception
size_t my_str_size(const my_str_t* str) {
    if (!str)
        return -3;
    return str->size_m;
}

//! Повертає розмір буфера:
//? -3 -- null pointer exception
size_t my_str_capacity(const my_str_t* str) {
    if (!str)
        return -3;
    return str->capacity_m;
}


//! Повертає булеве значення, чи стрічка порожня:
int my_str_empty(const my_str_t* str){
    if (!str || str->size_m == 0)
        return 1;
    return 0;
}

//! Повертає символ у вказаній позиції, або -1, якщо вихід за межі стрічки
//! Тому, власне, int а не char
//? -3 -- null pointer exception
int my_str_getc(const my_str_t* str, size_t index) {
    if (!str)
        return -3;

    if (index < 0 || index >= str->size_m)
        return -1;

    return *(str->data + index);
}

//! Записує символ у вказану позиції (заміняючи той, що там був),
//! Повертає 0, якщо позиція в межах стрічки,
//! Поветає -1, не змінюючи її вмісту, якщо ні.
//? -3 -- null pointer exception
int my_str_putc(my_str_t* str, size_t index, char c) {
    if (!str)
        return -3;
    if (index < 0 || index > str->size_m)
        return -1;
    *(str->data + index) = c;
    return 0;
}

//? -3 -- null pointer exception
//! Додає символ в кінець.
//! Повертає 0, якщо успішно, -1, якщо буфер закінчився.
int my_str_pushback(my_str_t* str, char c){
    if (!str)
        return -3;
    if (str->capacity_m < str->size_m)
        return -1;
    *(str->data + str->size_m++) = c;
    return 0;
}

//! Викидає символ з кінця.
//! Повертає його, якщо успішно, -1, якщо буфер закінчився.
//? -3 -- null pointer exception
int my_str_popback(my_str_t* str){
    if (!str)
        return -3;
    if(str->size_m <= str->capacity_m){
        char c_to_pop = *(str->data + str->size_m - 1);
        *(str->data + str->size_m - 1) = 0;
        str->size_m -= 1;
        return c_to_pop;
    }
    return -1;
}

//! Копіює стрічку. Якщо reserve == true,
//! то із тим же розміром буферу, що й вихідна,
//! інакше -- із буфером мінімального достатнього розміру.
//! Старий вміст стрічки перед тим звільняє, за потреби.
int my_str_copy(const my_str_t* from,  my_str_t* to, int reserve){
    if (!from || !to)
        return -3;

    if (to->capacity_m < from->size_m)
        return -1;

    if (reserve == 1)
        to->capacity_m = from->capacity_m;
    else
        to->capacity_m = from->size_m + 1;
    to->size_m = from->size_m;
    for (int i = 0; i < from->size_m; i++)
        *(to->data + i) = *(from->data + i);
    return 0;
}

//! Очищає стрічку -- робить її порожньою. Складність має бути О(1).
void my_str_clear(my_str_t* str){
    tr->data = 0;
    str->size_m = 0;
    str->capacity_m = 0;
}

//! Вставити символ у стрічку в заданій позиції, змістивши решту символів праворуч.
//! Якщо це неможливо, повертає -1, інакше 0.
//? -3 -- null pointer exception
int my_str_insert_c(my_str_t* str, char c, size_t pos) {
    if (!str)
        return -3;
    if (str->size_m >= str->capacity_m)
        return -1;

    size_t size = str->size_m;
    while (size-- != pos)
        *(str->data + size + 1) = *(str->data + size);
    *(str->data + pos) = c;
    str->size_m++;

    return 0;
}

//! Вставити стрічку в заданій позиції, змістивши решту символів праворуч.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_insert(my_str_t* str, const my_str_t* from, size_t pos){
    if (!str || !from)
        return -3;
    if (str->size_m + from->size_m > str->capacity_m)
        return -1;

    size_t size = str->size_m;
    size_t insert_size = from->size_m;

    while (size-- != pos)
        *(str->data + size + insert_size - 1) = *(str->data + size);
    while(--insert_size)
        *(str->data + size + insert_size) = *(from->data + insert_size);

    str->size_m += from->size_m;
    return 0;
}

//! Вставити C-стрічку в заданій позиції, змістивши решту символів праворуч.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_insert_cstr(my_str_t* str, const char* from, size_t pos) {
    if (!str || !from)
        return -3;
    if (str->size_m + strlen(from) > str->capacity_m)
        return -1;

    size_t size = str->size_m;
    size_t insert_size = strlen(from);
    while (size-- != pos)
        *(str->data + size + insert_size) = *(str->data + size);
    while (*(from))
        *(str->data + pos++) = *(from++);
    str->size_m += insert_size;
    return 0;
}

//! Додати стрічку в кінець.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_append(my_str_t* str, const my_str_t* from){
    if(str->capacity_m - str->size_m < from->size_m)
        return -1;
    for (int i = 0; i < from->size_m; i++)
        my_str_pushback(str, *(from->data + i));
    return 0;
}

//! Додати С-стрічку в кінець.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_append_cstr(my_str_t* str, const char* from){
    int c_str_len = strlen(from);
    if(str->capacity_m - str->size_m < c_str_len)
        return -1;
    for (int i = 0; i < c_str_len; i++)
        my_str_pushback(str, *(from + i));
    return 0;
}

//! Порівняти стрічки, повернути 0, якщо рівні (за вмістом!)
//! -1, якщо перша менша, 1 -- якщо друга.
//! Поведінка має бути такою ж, як в strcmp.
int my_str_cmp(my_str_t* str, const char* from){
    if (!str)
        return -3;

    size_t counter = 0;
    for (int i = 0; i < str->size_m; i ++){
        if (!*(from + i))
            return 1;
        if (*(from + i) == *(str->data + i))
            counter ++;
    }
    if (!*(from + counter) && counter == str->size_m)
        return 0;
    return -1;
}

//! Скопіювати підстрічку, із beg включно, по end не включно ([beg, end)).
//! Якщо end виходить за межі str -- скопіювати скільки вдасться, не вважати
//! це помилкою. Якщо ж в ціловій стрічці замало місця, або beg більший
//! за розмір str -- це помилка. Повернути відповідний код завершення.
int my_str_substr(const my_str_t* str, char* to, size_t beg, size_t end);


//! Повернути вказівник на С-стрічку, еквівалентну str.
//! Вважатимемо, що змінювати цю С-стрічку заборонено.
//! Якщо в буфері було зарезервовано на байт більше за макс. розмір, можна
//! просто додати нульовий символ в кінці та повернути вказівник data.
const char* my_str_get_cstr(my_str_t* str) {
    if (!str || !(str->data))
        return -3;
    *(str->data + 1) = '\0';
    *(str->data + str->size_m) = '\0';
    return str->data;
}

//! Знайти першу підстрічку в стрічці, повернути номер її
//! початку або -1u, якщо не знайдено. from -- місце, з якого починати шукати.
//! Якщо більше за розмір -- вважати, що не знайдено.
size_t my_str_find(const my_str_t* str, const my_str_t* tofind, size_t from){
    if (!str || !tofind)
        return -3;

    if (str->size_m < from)
        return -1;

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
    return -1;

}
//! Знайти перший символ в стрічці, повернути його номер
//! або -1u, якщо не знайдено. from -- місце, з якого починати шукати.
//! Якщо більше за розмір -- вважати, що не знайдено.
size_t my_str_find_c(const my_str_t* str, char tofind, size_t from){
    if (!str)
        return -3;
    if (from > str->size_m)
        return -1;

    for (from; from < str->size_m; from++){
        if (*(str->data + from) == tofind)
            return from;
    }
    return -1;
}

//! Знайти символ в стрічці, для якого передана
//! функція повернула true, повернути його номер
//! або -1u, якщо не знайдено:
size_t my_str_find_if(const my_str_t* str, int (*predicate)(char)){
    if (!str)
        return -3;

    for (size_t i = 0; i < str->size_m; i++){
        if (predicate(*(str->data + i)) == 1)
            return i;
    }
    return -1;
}

//! Прочитати стрічку із файлу. Повернути, 0, якщо успішно, -1,
//! якщо сталися помилки. Кінець вводу -- не помилка, однак,
//! слід не давати читанню вийти за межі буфера!
//! Рекомендую скористатися fgets().
size_t my_str_read_file(my_str_t* str, FILE* file);

//! Аналог my_str_read_file, із stdin
size_t my_str_read(my_str_t* str){
    if (!str)
        return -3;
    fgets(str->data, str->capacity_m + 1, stdin);
    str->size_m = strlen(str->data);
    return 0;
}



int main() {
    my_str_t x;
    my_str_from_cstr(&x, "Hello", 10);
    my_str_putc(&x, 10, 'r');
    printf("%s", x.data);
    printf("%i", x.size_m);

    return 0;
}
