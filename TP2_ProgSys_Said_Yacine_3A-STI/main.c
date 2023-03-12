#include "mini_lib.h"
#include <unistd.h>
#include <sys/wait.h>

void test_mini_memory();

void test_mini_string();

void test_mini_io();



/* ========================================= tester les fonction ============================== */

void test_mini_memory() {
    char* buffer_1 = mini_calloc(sizeof(char), 3);
    buffer_1[0] = 'a';
    buffer_1[1] = 'b';

    mini_free(buffer_1);

    char* buffer_2 = mini_calloc(sizeof(char), 2);
    
    if(buffer_2[0] == 'a' && buffer_2[1] == 'b') {
        mini_printf("memory block was not clean before being allocated");
    }
}

void test_mini_io() {

    // /*Combine mini_read mini_write to test*/
    // mini_touch("text.txt");
    // struct MYFILE *rw_file = mini_open("text.txt", 'b');
    // char buffer_to_write[] = "c is language for prog-system";
    // mini_fwrite(buffer_to_write, sizeof(char), sizeof(buffer_to_write)-1, rw_file);
    // mini_fflush(rw_file);

    // rw_file = mini_open("text.txt", 'b');

    // char *buffer_to_read = mini_calloc(sizeof(char), sizeof(buffer_to_write));
    // mini_fread(buffer_to_read, sizeof(char), sizeof(buffer_to_write)-1, rw_file);
    // mini_printf(buffer_to_read);
    // mini_exit_string();
    // mini_exit_io();

    struct MYFILE* file = mini_fopen("text.txt", 'r');
    if (mini_fclose(file) == -1) {
        mini_printf("\nmini_fclose error\n");
    }else {
        mini_printf("\nsuccessfully close file\n");
    }

}


void test_mini_string() {

    /* Test for printf */
    mini_printf("Hello");
    mini_printf("\n word\n");

    /* Test for scanf */
    // char *text = mini_calloc(sizeof(char), 100);
    // int count = mini_scanf(text, 100);
    // mini_printf(text);

    /* Test for mini_strlen mini_strcmp mini_strcpy */

    mini_exit_string();

}

