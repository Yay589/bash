#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "mini_lib.h"
#include<stdio.h>

#define BUF_SIZE 16
#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0

char *buffer;
int Index  = -1;

void stop_string(char* msg, int EXIT_VALUE){
    if (EXIT_VALUE==EXIT_FAILURE)mini_perror(msg);//pour différencier le exit_succes du exit_falure 
    mini_exit(EXIT_VALUE);
}

void mini_printf(char *text) {

    if(Index  == -1) {
        buffer = mini_calloc(sizeof(char), BUF_SIZE);
        Index  = 0;
    }

    // la partie suivante renvien à faire: printf("\n%s\n", text);

    int i;
    for(i = 0; text[i] != '\0'; i++) {
        if(text[i] == '\n' || Index == BUF_SIZE) {
            
            if(text[i] == '\n') {
                buffer[Index++] = text[i];
            }

            write(1, buffer, Index);
            for(int j = 0; j < Index; j++) {
                buffer[j] = '\0';
            }
            Index = 0;
        }
        else {
            buffer[Index++] = text[i];
        }
    }

}
//--------
int mini_scanf(char *buffer, int size_buffer) {
    if (size_buffer <= 0) {
        stop_string("SCANING ERROR",EXIT_FAILURE);
    }

    int count = read(1, buffer, size_buffer-1);
    
    if(count == -1) {
        stop_string("READING ERROR",EXIT_FAILURE);
    }
    buffer[count] = '\0';

    return count;
}
//--------
int mini_strlen(char *s) {
    if (s == NULL) {
        stop_string("STRLEN ERROR: arggument null",EXIT_FAILURE);
    }
    char *temp = s;
    int len = 0;
    while(*temp != '\0') {     
        if(*temp != '\n') {
            len++;
        }   
        temp++;
    }
    return len;
}
//--------
int mini_strcpy(char *s, char *d) {
    

    if(s==NULL || d==NULL) {
        stop_string("STRCPY ERROR: argument ",EXIT_FAILURE);
    }
    
    //Vérifier de le buffer n'est pas saturé
    d = mini_calloc(sizeof(char), mini_strlen(s));

    int count = 0;

    while(*s != '\0') {

        *(d++) = *(s++);
        count++;
    }
    
    return count;
}
//--------
int mini_strcmp(char *s1, char *s2) {

    if(s1 == NULL || s2 == NULL) {
        stop_string("STRCMP ERROR: argument null",EXIT_FAILURE);
    }

    while(*s1 != '\0') {
        if (*s1 != *s2 || *s2 == '\0') {
            return -1;
        }
        s1++;
        s2++;
    }

    if(*s2 != '\0') {
        return -1;
    }

    return 0;
}
//--------
void mini_exit_string() {
    if(Index  != -1) {
        write(1, buffer, Index );/*pour déplacer la tête de lecture dans la sortie standard*/
        Index  = -1;
    }
}
//--------
char *mini_itoa(int entier){
    int digits = 0;
    int decimale = entier;
    while (decimale != 0)/*plus grand chiffre du nombre 'entier' */
    {
        decimale = decimale / 10;
        digits++;
    }
    char *returning = mini_calloc(sizeof(char), (digits + 1));
    // char *returning = calloc(1, digits + 1);
    *(returning + digits) = '\0';
    for (int i = 0; entier != 0; i++)
    {
        int temp = entier % 10;
        *(returning + digits - (i + 1)) = (char)(temp + 48);
        entier = entier / 10;
    }
    return returning;
}
//--------
void mini_perror(char *message) {
    
    // Error number of errno has maximum 3 digits
    char *errno_str = mini_itoa(errno);
    mini_printf(message);
    mini_printf(" with error code: ");
    mini_printf(errno_str);
    mini_printf("\n");
    mini_exit();
}
