#include <sys/stat.h>
#ifndef MINI_LIB
#define MINI_LIB

// signatures fonction de mini_memory's
typedef struct malloc_element
{
    void *zone;
    int taille_zone;
    int statut;
    struct malloc_element *next_malloc;
} malloc_element;
extern malloc_element *malloc_list;

void *mini_calloc(int size_element, int number_element);

void mini_free(void *ptr);

void mini_exit();

// signatures fonction de mini_string's

void mini_printf(char *);

int mini_scanf(char *, int);

int mini_strlen(char *);

int mini_strcpy(char *s, char *d);

int mini_strncpy(char *s, char *d, int n);

int mini_strcmp(char *s1, char *s2);

void mini_perror(char *message);

void mini_exit_string();

// signatures fonction de mini_io's
typedef struct MYFILE
{
    int fd;
    void *buffer_read;
    void *buffer_write;
    int read_index;
    int write_index;
} MYFILE;

typedef struct FILE_elm_list
{
    MYFILE *file;
    struct FILE_elm_list *next; /*liste chainée*/
} FILE_elm_list;

extern FILE_elm_list *file_list;

MYFILE *mini_fopen(char *, char);

int mini_fclose(MYFILE *file);

int mini_fread(void *buffer, int size_element, int number_element, MYFILE *file);

int mini_fwrite(void *buffer, int size_element, int number_element, MYFILE *file);

int mini_fflush(MYFILE *file);

int mini_fgetc(MYFILE *file);

int mini_fputc(MYFILE *file, char c);

MYFILE *mini_touch(char *file_name);

void mini_cp(char *src, char *dst);

void mini_echo(char *string);

void mini_cat(char *file_name);

void mini_head(int n, char *file_name);

void mini_tail(int n, char *file_name);

void mini_clean(char *file_name);

void mini_grep(char *file_name, char *mot);

char *mini_itoa(int a);

void mini_wc(char *file_name);

void mini_exit_io();

//// Part 3
int link(const char *existingpath, const char *newpath);
int chdir(const char *path);
//int mkdir(const char *path, mode_t mode);

#endif


