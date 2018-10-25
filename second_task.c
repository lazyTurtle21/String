#include <string.h>
#include <errno.h>
#include "my_str_t.h"


void write_data(FILE* file, const char *data) {
    fputs(data, file);
}


int main(int argc, char * argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Wrong number of arguments: %s\n", strerror(EINVAL));
        return EINVAL;
    }

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    if (!output) {
        fprintf(stderr, "Error creating the file: %s\n", strerror(errno));
        return errno;
    }

    if (!input) {
        fprintf(stderr, "Error opening the file: %s\n", strerror(errno));
        return errno;
    }

    my_str_t word;

    if (my_str_create(&word, 100)){
        fprintf(stderr, "Unable to create string: %s\n", strerror(ENOMEM));
        return ENOMEM;
    }

    while (my_str_read_file_until_blankspace(&word, input) != -1){
        my_str_pushback(&word, ' ');

        for (size_t i = 0; i < word.size_m; i++) {
            if (ispunct(my_str_getc(&word, i))) {
                my_str_remove_c(&word, i);
                i--;
            }
            if (isupper(my_str_getc(&word, i)))
                my_str_putc(&word, i, (char)tolower(my_str_getc(&word, i)));
        }

        write_data(output, my_str_get_cstr(&word));
        my_str_clear(&word);

    }

    fclose(input);
    fclose(output);


    return EXIT_SUCCESS;
}
