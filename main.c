#include <stdio.h>
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
// Zhenia HI!!!!!
typedef struct {
    size_t capacity_m; // Розмір блока
    size_t size_m;	   // Фактичний розмір стрічки
    char*  data;	   // Вказівник на блок пам'яті

} my_str_t;

//? -3 -- null pointer exception
//? рахує кількість символів без останнього ('\0')
const size_t strlen(const char* str) {
	if (!str)
		return -3;

	int length = 0;
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
void my_str_free(my_str_t* str);

//! Повертає розмір стрічки:
//? -3 -- null pointer exception
size_t my_str_size(const my_str_t* str) {
	if (!str)
		return -3;
	return str->size_m;
}

//! Повертає розмір буфера:
size_t my_str_capacity(const my_str_t* str);

//! Повертає булеве значення, чи стрічка порожня:
int my_str_empty(const my_str_t* str);

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
int my_str_putc(my_str_t* str, size_t index, char c);

//! Додає символ в кінець.
//! Повертає 0, якщо успішно, -1, якщо буфер закінчився.
int my_str_pushback(my_str_t* str, char c);

//! Викидає символ з кінця.
//! Повертає його, якщо успішно, -1, якщо буфер закінчився.
int my_str_popback(my_str_t* str);

//! Копіює стрічку. Якщо reserve == true,
//! то із тим же розміром буферу, що й вихідна,
//! інакше -- із буфером мінімального достатнього розміру.
//! Старий вміст стрічки перед тим звільняє, за потреби.
int my_str_copy(const my_str_t* from,  my_str_t* to, int reserve);

//! Очищає стрічку -- робить її порожньою. Складність має бути О(1).
void my_str_clear(my_str_t* str);

//! Вставити символ у стрічку в заданій позиції, змістивши решту символів праворуч.
//! Якщо це неможливо, повертає -1, інакше 0.
//? -3 -- null pointer exception
int my_str_insert_c(my_str_t* str, char c, size_t pos) {
	if (str->size_m >= str->capacity_m)
		return -1;
	if (!str)
		return -3;

	int size = str->size_m;
	while (size-- != pos) 
		*(str->data + size + 1) = *(str->data + size);
	*(str->data + pos) = c;
	str->size_m++;

	return 0;
}

//! Вставити стрічку в заданій позиції, змістивши решту символів праворуч.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_insert(my_str_t* str, const my_str_t* from, size_t pos);

//! Вставити C-стрічку в заданій позиції, змістивши решту символів праворуч.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_insert_cstr(my_str_t* str, const char* from, size_t pos);

//! Додати стрічку в кінець.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_append(my_str_t* str, const my_str_t* from);

//! Додати С-стрічку в кінець.
//! Якщо це неможливо, повертає -1, інакше 0.
int my_str_append_cstr(my_str_t* str, const char* from);

//! Порівняти стрічки, повернути 0, якщо рівні (за вмістом!)
//! -1, якщо перша менша, 1 -- якщо друга.
//! Поведінка має бути такою ж, як в strcmp.
int my_str_cmp(my_str_t* str, const char* from);

//! Скопіювати підстрічку, із beg включно, по end не включно ([beg, end)).
//! Якщо end виходить за межі str -- скопіювати скільки вдасться, не вважати
//! це помилкою. Якщо ж в ціловій стрічці замало місця, або beg більший
//! за розмір str -- це помилка. Повернути відповідний код завершення.
int my_str_substr(const my_str_t* str, const char* to, size_t beg, size_t end);


//! Повернути вказівник на С-стрічку, еквівалентну str.
//! Вважатимемо, що змінювати цю С-стрічку заборонено.
//! Якщо в буфері було зарезервовано на байт більше за макс. розмір, можна
//! просто додати нульовий символ в кінці та повернути вказівник data.
const char* my_str_get_cstr(my_str_t* str) {
	*(str->data + 1) = '\0';
	return str->data;
}

//! Знайти першу підстрічку в стрічці, повернути номер її
//! початку або -1u, якщо не знайдено. from -- місце, з якого починати шукати.
//! Якщо більше за розмір -- вважати, що не знайдено.
size_t my_str_find(const my_str_t* str, const my_str_t* tofind, size_t from);

//! Знайти перший символ в стрічці, повернути його номер
//! або -1u, якщо не знайдено. from -- місце, з якого починати шукати.
//! Якщо більше за розмір -- вважати, що не знайдено.
size_t my_str_find_c(const my_str_t* str, char tofind, size_t from);

//! Знайти символ в стрічці, для якого передана
//! функція повернула true, повернути його номер
//! або -1u, якщо не знайдено:
size_t my_str_find_if(const my_str_t* str, int (*predicat)(char));

//! Прочитати стрічку із файлу. Повернути, 0, якщо успішно, -1,
//! якщо сталися помилки. Кінець вводу -- не помилка, однак,
//! слід не давати читанню вийти за межі буфера!
//! Рекомендую скористатися fgets().
size_t my_str_read_file(my_str_t* str, FILE* file);

//! Аналог my_str_read_file, із stdin
size_t my_str_read(my_str_t* str);


int main() {
	my_str_t x;
	my_str_create(&x, 10);
	return 0;
}
