#include "my_str_t.h"
int main() {
    printf("Function to test: int my_str_create\n");
    my_str_t str;
    int s = my_str_create(&str, 3);
    printf("Function returned: %i\nCreated a string with buffer size 3\n\n", s);

    printf("Function to test: int my_str_from_cstr\n");
    char c_str[] ="My string";
    my_str_t str_1;
    my_str_t str_2;
    int s1 = my_str_from_cstr(&str_1, c_str, 20);
    printf("Function returned: %i \nCreated string: ", s1);
    print_str(&str_1);
    int s2 = my_str_from_cstr(&str_2, c_str, 5);
    printf("Function returned: %i \nFailed to create a string\n\n", s2);

    printf("Function to test: my_str_size\n");
    printf("String: ");
    print_str(&str_1);
    int size = my_str_size(&str_1);
    printf("Function returned: %i\n\n", size);

    printf("Function to test: my_str_capacity\n");
    printf("String: ");
    print_str(&str_1);
    int cap = my_str_capacity(&str_1);
    printf("Funcion returned: %i\n\n", cap);

    printf("Function to test: my_str_getc\n");
    printf("String: ");
    print_str(&str_1);
    int c1 = my_str_getc(&str_1, 3);
    int c2 = my_str_getc(&str_1, 10);
    printf("Getting char at position 3\nFuncion returned: %c\n", c1);
    printf("Getting char at position 10\nFuncion returned: %i\n\n", c2);

    printf("Function to test: my_str_putc\n");
    printf("String: ");
    print_str(&str_1);
    int c3 = my_str_putc(&str_1, 10, 'S');
    printf("Putting char at position 10\nFuncion returned: %i\n", c3);
    printf("String now: ");
    print_str(&str_1);
    int c4 = my_str_putc(&str_1, 3, 'S');
    printf("Putting char at position 3\nFuncion returned: %i\n", c4);
    printf("String now: ");
    print_str(&str_1);
    printf("\n\n");

    printf("Function to test: my_str_copy\n");
    printf("String: ");
    print_str(&str_1);
    char string[] ="Simple C string";
    my_str_t str_3;
    my_str_t str_4;
    my_str_from_cstr(&str_3, c_str, 20);
    int copy = my_str_copy(&str_1, &str, 1);
    printf("Buffer in target string is too small\nFuncion returned: %i\nFailed to copy\n\n", copy);
    int copy1 = my_str_copy(&str_1, &str_3, 1);
    printf("Reserve is true\nFuncion returned: %i\n", copy1);
    printf("Copied string: ");
    print_str(&str_3);
    printf("Buffer size: %i\n\n", my_str_capacity(&str_3));
    int copy2 = my_str_copy(&str_1, &str_3, 0);
    printf("Reserve is false\nFuncion returned: %i\n", copy2);
    printf("Copied string: ");
    print_str(&str_3);
    printf("Buffer size: %i\n\n", my_str_capacity(&str_3));


    printf("Function to test: my_str_pushback\n");
    printf("String: ");
    print_str(&str_3);
    int push1 = my_str_pushback(&str_3, '1');
    printf("Buffer size is too small\nFuncion returned: %i\n", c3);
    printf("String now: ");
    print_str(&str_3);
    int push2 = my_str_pushback(&str_1, '1');
    printf("Buffer size is ok\nFuncion returned: %i\n", c4);
    printf("String now: ");
    print_str(&str_1);
    printf("\n\n");

    printf("Function to test: my_str_popback\n");
    printf("String: ");
    print_str(&str_1);
    int popped = my_str_popback(&str_1);
    printf("Funcion returned: %c\nString now: ", popped);
    print_str(&str_1);
    printf("\n\n");

    printf("Function to test: my_str_insert_c\n");
    printf("String: ");
    print_str(&str_1);
    int ins1 = my_str_insert_c(&str_1,'s', 10);
    printf("Inserting char at position 10\nFuncion returned: %i\n", ins1);
    printf("String now: ");
    print_str(&str_1);
    int ins2 = my_str_insert_c(&str_1,'s', 4);
    printf("Inserting char at position 4\nFuncion returned: %i\n", ins2);
    printf("String now: ");
    print_str(&str_1);
    printf("\n\n");

    printf("Function to test: my_str_insert\n");
    printf("String: ");
    print_str(&str_1);
    char x[] = "sssss";
    my_str_t str_5;
    my_str_from_cstr(&str_5, x, 10);
    int ins_s1 = my_str_insert(&str_1, &str_5, 10);
    printf("Inserting string at position 10\nFuncion returned: %i\n", ins1);
    printf("String now: ");
    print_str(&str_1);
    int ins_s2 = my_str_insert(&str_1,&str_5, 4);
    printf("Inserting string at position 4\nFuncion returned: %i\n", ins2);
    printf("String now: ");
    print_str(&str_1);

}