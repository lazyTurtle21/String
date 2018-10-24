#include "my_str_t.h"


void write_data(FILE* file, const char *data) {
    fputs(data, file);
}


int main(int argc, char * argv[]) {
    if(argc != 3) {
        printf("%s", "You have to pass 2 arguments: name of the input file, name of the output file");
        return -1;
    }

    FILE *input= fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    if (!output) {
        printf("Unable to create output file.\n");
        exit(EXIT_FAILURE);
    }

    if (!input) {
        printf("Unable to find input file.\n");
        exit(EXIT_FAILURE);
    }

    my_str_t word;

    if (my_str_create(&word, 100)){
        printf("Unable to create string.");
        exit(EXIT_FAILURE);
    }

    while (my_str_read_file_until_blankspace(&word, input) != -1){
        my_str_pushback(&word, ' ');

        for (size_t i = 0; i < word.size_m; i++) {
            if (ispunct(my_str_getc(&word, i))) {
                my_str_remove_c(&word, i);
                i--;
            }
            if (isupper(my_str_getc(&word, i)))
                my_str_putc(&word, i, (char) tolower(my_str_getc(&word, i)));
        }

        write_data(output, my_str_get_cstr(&word));
        my_str_clear(&word);

    }

    fclose(input);
    fclose(output);


    return 0;
}

