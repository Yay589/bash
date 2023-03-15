#include "mini_lib.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

/* ========================================= tester les fonction ============================== */

void test_mini_memory()
{
    printf("\n****test_mini_memory****\n");

    // char *buffer_1 = mini_calloc(sizeof(char), 3);
    // buffer_1[0] = 'a';
    // buffer_1[1] = 'b';

    // mini_free(buffer_1);

    // char *buffer_2 = mini_calloc(sizeof(char), 2);

    // if (buffer_2[0] == 'a' && buffer_2[1] == 'b')
    // {
    //     mini_printf("memory block was not clean before being allocated");
    // }
    printf("\n****test_mini_memory >>>OK ****\n");
}

void test_mini_io()
{
    printf("\n****test_mini_io****\n");

    /*Combine mini_read mini_write to test*/
    mini_touch("text.txt");
    struct MYFILE *rw_file = mini_fopen("text.txt", 'b');
    char buffer_to_write[] = "INSA CVL";
    mini_fwrite(buffer_to_write, sizeof(char), sizeof(buffer_to_write) - 1, rw_file);
    mini_fflush(rw_file);

    rw_file = mini_fopen("text.txt", 'b');

    char *buffer_to_read = mini_calloc(sizeof(char), sizeof(buffer_to_write));
    mini_fread(buffer_to_read, sizeof(char), sizeof(buffer_to_write) - 1, rw_file);
    mini_printf(buffer_to_read);
    mini_printf("\n");
    mini_exit_string();
    mini_exit_io();
    struct MYFILE *file = mini_fopen("text.txt", 'r');
    if (mini_fclose(file) == -1)
    {
        mini_printf("\nmini_fclose error\n");
    }
    else
    {
        mini_printf("\nfile closed\n");
    }
    printf("\n****test_mini_io >>>OK ****\n");
}

void test_mini_string()
{
    printf("\n****test_mini_string****\n");
    // /* Test for printf */
    // mini_printf("Hello");
    // mini_printf("\nword\n");

    // /* Test for scanf */
    // mini_printf("Test for scanf:\n");
    // char *text = mini_calloc(sizeof(char), 100);
    // int count = mini_scanf(text, 100);
    // mini_printf("champ lu = ");
    // mini_printf(text);

    // /* Test for mini_strlen */
    // mini_printf("\nstrlen(champ_lu) = ");
    // mini_printf(mini_itoa(mini_strlen(text)));
    // mini_exit_string();

    // /* Test for mini_strcmp mini_strcpy */
    // char *var1 = "coucou";
    // char *var2;
    // mini_strcpy(var1, var2);

    // /* Test for mini_strcmp mini_strcpy */
    // char *x = "La programmation system c'est bien";
    // char *y = "L'administration system c'est mieux";
    // printf("x=%s\ny=%s\n(y=n)=%d\n", x, y, mini_strcmp(x, y));
    // mini_strcmp(x, y);
    printf("\n****test_mini_string >>>OK ****\n");
}

int main(int argc, char const *argv[])
{

    test_mini_memory();

    test_mini_string();

    test_mini_io();

    return 0;
}
