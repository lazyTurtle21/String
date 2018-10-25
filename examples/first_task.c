#include "my_str_t.h"

int is_vowel(char a){
    char vowels[5] = {'a', 'e', 'i', 'o', 'u'};
    for (int i = 0; i < sizeof(vowels); i++) {
        if(vowels[i] == a)
            return 1;
    }
    return 0;
}

int is_digit(char a){
    if(('0'<=a) && ('9'>=a))
        return 1;
    return 0;
}

int main() {
    printf("Function to test: int my_str_create\n");
    my_str_t str;
    int s = my_str_create(&str, 3);
    printf("Function returned: %i\nCreated a string with buffer size 3\n\n", s);

    printf("Function to test: int my_str_from_cstr\n");
    char c_str[] = "My string";
    my_str_t str_1;
    my_str_t str_2;
    int s1 = my_str_from_cstr(&str_1, c_str, 20);
    printf("Function returned: %i \nCreated string: ", s1);
    my_str_print(&str_1);
    int s2 = my_str_from_cstr(&str_2, c_str, 5);
    printf("Function returned: %i \nFailed to create a string\n\n", s2);



    printf("Function to test: my_str_size\n");
    printf("String: ");
    my_str_print(&str_1);
    int size = my_str_size(&str_1);
    printf("Function returned: %i\n\n", size);

    printf("Function to test: my_str_capacity\n");
    printf("String: ");
    my_str_print(&str_1);
    int cap = my_str_capacity(&str_1);
    printf("Function returned: %i\n\n", cap);

    printf("Function to test: my_str_getc\n");
    printf("String: ");
    my_str_print(&str_1);
    int c1 = my_str_getc(&str_1, 3);
    int c2 = my_str_getc(&str_1, 10);
    printf("Getting char at position 3\nFunction returned: %c\n", c1);
    printf("Getting char at position 10\nFunction returned: %i\n\n", c2);

    printf("Function to test: my_str_putc\n");
    printf("String: ");
    my_str_print(&str_1);
    int c3 = my_str_putc(&str_1, 10, 'S');
    printf("Putting char at position 10\nFunction returned: %i\n", c3);
    printf("String now: ");
    my_str_print(&str_1);
    int c4 = my_str_putc(&str_1, 3, 'S');
    printf("Putting char at position 3\nFunction returned: %i\n", c4);
    printf("String now: ");
    my_str_print(&str_1);
    printf("\n\n");

    printf("Function to test: my_str_copy\n");
    printf("String: ");
    my_str_print(&str_1);
    char string[] = "Simple C string";
    my_str_t str_3;
    my_str_from_cstr(&str_3, c_str, 20);
    int copy = my_str_copy(&str_1, &str, 1);
    printf("Buffer in target string is too small\nFunction returned: %i\nFailed to copy\n\n", copy);
    int copy1 = my_str_copy(&str_1, &str_3, 1);
    printf("Reserve is true\nFunction returned: %i\n", copy1);
    printf("Copied string: ");
    my_str_print(&str_3);
    printf("Buffer size: %i\n\n", my_str_capacity(&str_3));
    int copy2 = my_str_copy(&str_1, &str_3, 0);
    printf("Reserve is false\nFunction returned: %i\n", copy2);
    printf("Copied string: ");
    my_str_print(&str_3);
    printf("Buffer size: %i\n\n", my_str_capacity(&str_3));


    printf("Function to test: my_str_cmp\n");
    char c_str1[] = "My String";
    char c_str2[] = "My Not";
    char c_str3[] = "My Stringggggggg";
    printf("String: ");
    my_str_print(&str_1);
    int cmp1 = my_str_cmp(&str_1, c_str1);
    printf("Comparing with 'My String'\nFunction returned: %i\n", cmp1);
    int cmp2 = my_str_cmp(&str_1, c_str2);
    printf("Comparing with 'My Not'\nFunction returned: %i\n", cmp2);
    int cmp3 = my_str_cmp(&str_1, c_str3);
    printf("Comparing with 'My Stringggggggg'\nFunction returned: %i\n\n", cmp3);


    printf("Function to test: my_str_pushback\n");
    printf("String: ");
    my_str_print(&str_3);
    int push1 = my_str_pushback(&str_3, '1');
    printf("Buffer size is too small\nFunction returned: %i\n", c3);
    printf("String now: ");
    my_str_print(&str_3);
    int push2 = my_str_pushback(&str_1, '1');
    printf("Buffer size is ok\nFunction returned: %i\n", c4);
    printf("String now: ");
    my_str_print(&str_1);
    printf("\n\n");

    printf("Function to test: my_str_popback\n");
    printf("String: ");
    my_str_print(&str_1);
    int popped = my_str_popback(&str_1);
    printf("Function returned: %c\nString now: ", popped);
    my_str_print(&str_1);
    printf("\n\n");

    printf("Function to test: my_str_insert_c\n");
    printf("String: ");
    my_str_print(&str_1);
    int ins1 = my_str_insert_c(&str_1, 's', 10);
    printf("Inserting char at position 10\nFunction returned: %i\n", ins1);
    printf("String now: ");
    my_str_print(&str_1);
    int ins2 = my_str_insert_c(&str_1, 's', 4);
    printf("Inserting char at position 4\nFunction returned: %i\n", ins2);
    printf("String now: ");
    my_str_print(&str_1);
    printf("\n\n");

    printf("Function to test: my_str_insert\n");
    printf("String: ");
    my_str_print(&str_1);
    char s_to_insert[] = "sss";
    my_str_t str_5;
    my_str_from_cstr(&str_5, s_to_insert, 10);
    int ins_s1 = my_str_insert(&str_1, &str_5, 10);
    printf("Inserting string at position 10\nFunction returned: %i\n", ins1);
    printf("String now: ");
    my_str_print(&str_1);
    int ins_s2 = my_str_insert(&str_1, &str_5, 4);


    printf("Inserting string at position 4\nFunction returned: %i\n", ins2);
    printf("String now: ");
    my_str_print(&str_1);
    printf("\n\n");

    printf("Function to test: my_str_insert_cstr\n");
    printf("String: ");
    my_str_print(&str_1);
    int ins_s3 = my_str_insert_cstr(&str_1, s_to_insert, 15);
    printf("Inserting c-string at position 15\nFunction returned: %i\n", ins_s3);
    printf("String now: ");
    my_str_print(&str_1);
    int ins_s4 = my_str_insert_cstr(&str_1, s_to_insert, 10);
    printf("Inserting c-string at position 10\nFunction returned: %i\n", ins_s4);
    printf("String now: ");
    my_str_print(&str_1);
    printf("\n\n");


    printf("Function to test: my_str_append\n");
    printf("String: ");
    my_str_print(&str_1);
    my_str_t str_6;
    my_str_from_cstr(&str_6, "gggggggggggggg", 20);
    int a1 = my_str_append(&str_1, &str_6);

    printf("Buffer size is too small\nFunction returned: %i\n", a1);
    printf("String now: ");
    my_str_print(&str_1);
    char s_to_app[] = "gg";
    my_str_t str_7;
    my_str_from_cstr(&str_7, s_to_app, 10);
    int a2 = my_str_append(&str_1, &str_7);
    printf("Buffer size is ok\nFunction returned: %i\n", a2);
    printf("String now: ");
    my_str_print(&str_1);
    printf("\n\n");

    printf("Function to test: my_str_append_cstr\n");
    printf("String: ");
    my_str_print(&str_1);
    int a3 = my_str_append_cstr(&str_1, "hahahah");
    printf("Buffer size is too small\nFunction returned: %i\n", a3);
    printf("String now: ");
    my_str_print(&str_1);
    int a4 = my_str_append_cstr(&str_1, s_to_app);
    printf("Buffer size is ok\nFunction returned: %i\n", a4);
    printf("String now: ");
    my_str_print(&str_1);
    printf("\n\n");

    printf("Function to test: my_str_find\n");
    printf("String: ");
    my_str_print(&str_1);
    my_str_t to_find1;
    my_str_from_cstr(&to_find1, "ss", 10);
    int f1 = my_str_find(&str_1, &to_find1, 15);
    printf("Searching for 'ss' from index 15\nFunction returned: %i\n", f1);
    int f2 = my_str_find(&str_1, &to_find1, 0);
    printf("Searching for 'ss' from index 0\nFunction returned: %i\n\n", f2);

    printf("Function to test: my_str_find_c\n");
    printf("String: ");
    my_str_print(&str_1);
    int f3 = my_str_find_c(&str_1, 't', 15);
    printf("Searching for 't' from index 15\nFunction returned: %i\n", f3);
    int f4 = my_str_find_c(&str_1, 't', 0);
    printf("Searching for 't' from index 0\nFunction returned: %i\n\n", f4);

    printf("Function to test: my_str_find_if\n");
    printf("String: ");
    my_str_print(&str_1);
    int f5 = my_str_find_if(&str_1, is_digit);
    printf("Searching for digit\nFunction returned: %i\n", f5);
    int f6 = my_str_find_if(&str_1, is_vowel);
    printf("Searching for vowel\nFunction returned: %i\n\n", f6);

    printf("Function to test: my_str_substr\n");
    printf("String: ");
    my_str_print(&str_1);
    int sub1 = my_str_substr(&str_1, &str_3, 0, 15);
    printf("Buffer in target string is too small\nFunction returned: %i\nFailed to copy\n", sub1);
    int sub2 = my_str_substr(&str_1, &str_3, 30, 35);
    printf("Extracting a substring [30, 35)\nFunction returned: %i\nFailed to copy\n", sub2);
    int sub3 = my_str_substr(&str_1, &str_3, 5, 10);
    printf("Extracting a substring [5, 10)\nFunction returned: %i\nCopied string: \n", sub3);
    my_str_print(&str_3);
    int sub4 = my_str_substr(&str_1, &str_3, 14, 30);
    printf("Extracting a substring [14, 30)\nFunction returned: %i\nCopied string: \n", sub4);
    my_str_print(&str_3);
    printf("\n\n");

    printf("Function to test: my_str_remove_c\n");
    printf("String: ");
    my_str_print(&str_1);
    int r1 = my_str_remove_c(&str_1, 30);
    printf("Removing char from position 30\nFunction returned: %i\n", r1);
    printf("String now: ");
    my_str_print(&str_1);
    int r2 = my_str_remove_c(&str_1, 2);
    printf("Removing char from position 2\nFunction returned: %i\n", r2);
    printf("String now: ");
    my_str_print(&str_1);
    printf("\n\n");

    printf("Function to test: my_str_get_cstr\n");
    printf("String: ");
    my_str_print(&str_1);
    printf("Received C-string: %s", my_str_get_cstr(&str_1));
    printf("\n\n");

    printf("Function to test: my_str_clear\n");
    printf("String before: ");
    my_str_print(&str_3);
    my_str_clear(&str_3);
    printf("Function to test: my_str_empty\n");
    printf("Function returned: %i\n", my_str_empty(&str_3));
    int p = my_str_pushback(&str_3, 'M');
    printf("Trying to pushback 'M' after clear()\nFunction returned: %i\n", p);
    printf("String now: ");
    my_str_print(&str_3);

    printf("\n\n");

    printf("Function to test: my_str_free\n");
    printf("String: ");
    my_str_print(&str_1);
    my_str_free(&str_1);
    int k = my_str_pushback(&str_1, 'd');
    printf("Trying to pushback after my_str_free()\nFunction returned: %i\n\n", k);
    my_str_free(&str_1);


    printf("Function to test: my_str_read_file_until_blankspace\n");
    my_str_t f_str;
    my_str_create(&f_str, 100);
    FILE *file;
    file = fopen("examples/test.txt", "r");
    if (file) {
        int read1 = my_str_read_file_until_blankspace(&f_str, file);
        printf("Function returned: %i\nString from file 'test.txt': ", read1);
        my_str_print(&f_str);
        printf("\n\n");
        fclose(file);
    }

    printf("Function to test: my_str_read_file_until_end\n");
    file = fopen("examples/test.txt", "r");
    if (file) {
        int read2 = my_str_read_file_until_end(&f_str, file);
        printf("Function returned: %i\nString from file 'test.txt': ", read2);
        my_str_print(&f_str);
        printf("\n\n");
        fclose(file);
    }
    return 0;
}
