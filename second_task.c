//
// Created by Yevhenii on 21/10/2018.
//

#include "second_task.h"

void store_data(const char *filepath, const char *data) {
    FILE *fp = fopen(filepath, "w");

    if (fp == NULL) {
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    printf("%s", "> output file was successfully created...");
    fputs(data, fp);
    printf("%s", "> data was successfully stored to output file...");
    fclose(fp);
}

int main(int argc, char * argv[]) {
    if(argc != 3)
    {
        printf("%s", "You should pass 2 arguments: name of the input file, name of the output file...");
        return -1;
    }

    my_str_t str;
    my_str_create(&str, 100);

    FILE *file;
    file = fopen(argv[1], "r");

    if (file) {
        while (my_str_read_file_until_blankspace(&str, file) != -1)
            my_str_pushback(&str, ' ');

        for (size_t i = 0; i < str.size_m; i++) {
            if (!isalpha(my_str_getc(&str, i)) && !isblank(my_str_getc(&str, i)))
                my_str_remove_c(&str, i);
            if(isupper(my_str_getc(&str, i)))
                my_str_putc(&str, i, (char)tolower(my_str_getc(&str, i)));
        }
        fclose(file);
        store_data(argv[2], my_str_get_cstr(&str));
        return 0;
    }
    else{
        printf("%s", "File wasn't found...");
        return -1;
    }
}

