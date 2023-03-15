#include "mini_lib.h"
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#define IOBUFFER_SIZE 10
#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0

struct FILE_elm_list *file_list = NULL;

int stop_Io(char *msg, int EXIT_VALUE)
{
    mini_exit_io();
    if (EXIT_VALUE == EXIT_FAILURE)
        mini_perror(msg); // pour différencier le exit_succes du exit_falure
    return EXIT_VALUE;
}

struct MYFILE *mini_fopen(char *file, char mode)
{

    if (file == NULL)
    {
        stop_Io("ERROR: File=Null \n", EXIT_FAILURE);
    }

    size_t descripteur_de_fichier;

    switch (mode)
    {
    case 'r':
        descripteur_de_fichier = (size_t)open(file, O_RDONLY);
        if (descripteur_de_fichier == -1)
        {
            stop_Io("ERROR: for opening file whith O_RDONLY option \n", EXIT_FAILURE);
        }
        break;
    case 'w':
        descripteur_de_fichier = (size_t)open(file, O_WRONLY);
        if (descripteur_de_fichier == -1)
        {
            stop_Io("ERROR: for opening filewhith O_WRONLY option \n", EXIT_FAILURE);
        }
        break;
    case 'b':
        descripteur_de_fichier = (size_t)open(file, O_RDWR);
        if (descripteur_de_fichier == -1)
        {
            stop_Io("ERROR: for opening file whith O_RDWR option \n", EXIT_FAILURE);
        }
        break;
    case 'a':
        descripteur_de_fichier = (size_t)open(file, 0200); /*O_APPEND=0200*/
        if (descripteur_de_fichier == -1)
        {
            stop_Io("ERROR: for opening file whith O_APPEND option \n", EXIT_FAILURE);
        }
    case 'c':
        descripteur_de_fichier = open(file, O_WRONLY | O_CREAT);
        stop_Io("ERROR: for opening file whith O_APPEND option \n", EXIT_FAILURE);
        break;
    default:
        stop_Io("ERROR: DESCRIPTEUR DE FICHIER \n", EXIT_FAILURE);
        break;
    }

    struct MYFILE *myFile = mini_calloc(sizeof(struct MYFILE), 1);
    myFile->fd = descripteur_de_fichier;
    myFile->read_index = -1;
    myFile->write_index = -1;

    if (file_list == NULL)
    {
        file_list = mini_calloc(sizeof(struct FILE_elm_list), 1);
        file_list->file = myFile;
        file_list->next = NULL;
    }
    else
    {
        struct FILE_elm_list *next_file = mini_calloc(sizeof(struct FILE_elm_list), 1);
        next_file->file = myFile;
        next_file->next = file_list;
        file_list = next_file;
    }

    return myFile;
}

int mini_fclose(struct MYFILE *fichier)
{

    // Fermer le fichier
    if (close(fichier->fd) == -1)
    {
        stop_Io("fclose error :", EXIT_FAILURE);
    }
    // Vider le buffer de sortie
    mini_fflush(fichier);

    // Parcourir file_list pour trouver le fichier, puis le supprimer de file_list
    struct FILE_elm_list *file = file_list;
    struct FILE_elm_list *file_precedant;

    if (file != NULL && file->file->fd == fichier->fd)
    {
        file_list = file_list->next;
        mini_free(file);
        stop_Io("", EXIT_SUCCESS);
    }

    while (file != NULL && file->file->fd != fichier->fd)
    {
        file_precedant = file;
        file = file->next;
    }

    if (file == NULL)
    {
        stop_Io("mini_fclose : le fichier n'existe pas dans la liste des fichiers", EXIT_FAILURE);
    }

    file_precedant->next = file->next;
    mini_free(file);

    stop_Io("", EXIT_SUCCESS);
}

int mini_fread(void *buffer, int size_element, int number_element, struct MYFILE *file)
{

    if (file->read_index == -1)
    {
        file->buffer_read = mini_calloc(sizeof(char), IOBUFFER_SIZE);
        file->read_index = 0;
        if (read(file->fd, file->buffer_read, IOBUFFER_SIZE) == -1)
        {
            stop_Io("read error", EXIT_FAILURE);
        }
    }

    int num_bytes_to_read = size_element * number_element;
    int i = 0;

    while (i < num_bytes_to_read)
    {
        ((char *)buffer)[i] = ((char *)file->buffer_read)[file->read_index];
        file->read_index++;

        if (file->read_index >= IOBUFFER_SIZE)
        {
            if (read(file->fd, file->buffer_read, IOBUFFER_SIZE) == -1)
            {
                stop_Io("read error", EXIT_FAILURE);
            }

            file->read_index = 0;
        }
        i++;
    }

    return file->read_index - 1;
}

int mini_fwrite(void *buffer, int size_element, int number_element, struct MYFILE *file)
{

    if (file->write_index == -1)
    {
        file->buffer_write = mini_calloc(sizeof(char), IOBUFFER_SIZE);
        file->write_index = 0;
    }

    int num_bytes_written = size_element * number_element;

    int i = 0;

    while (i < num_bytes_written)
    {

        ((char *)file->buffer_write)[file->write_index] = ((char *)buffer)[i];
        file->write_index++;

        if (file->write_index >= IOBUFFER_SIZE)
        {
            if (write(file->fd, file->buffer_write, file->write_index) == -1)
            {
                stop_Io("write error", EXIT_FAILURE);
                ;
            }
            file->write_index = 0;
        }

        i++;
    }
    return i;
}

int mini_fgetc(struct MYFILE *file)
{
    char *buffer = mini_calloc(sizeof(char), 1);
    if (mini_fread(buffer, sizeof(char), 1, file) == -1)
    {
        return -1;
    }
    return *buffer;
}

int mini_fputc(struct MYFILE *file, char c)
{
    char *buffer = mini_calloc(sizeof(char), 1);
    *buffer = c;
    if (mini_fwrite(buffer, sizeof(char), 1, file) == -1)
    {
        stop_Io("WRITE ERROR: for fputc \n", EXIT_FAILURE);
    }
    stop_Io("", EXIT_SUCCESS);
}

int mini_fflush(struct MYFILE *file)
{
    int count;
    if (file->write_index != -1)
    {
        if ((count = (write(file->fd, file->buffer_write, file->write_index))) == -1)
        {
            stop_Io("WRITE ERROR: for flushing the buffer \n", EXIT_FAILURE);
        }
        file->write_index = 0;
    }

    return count;
}

MYFILE *mini_touch(char *file_name)
{
    MYFILE *file = mini_calloc(sizeof(struct MYFILE), 1);
    int fd;

    if ((fd = open((char *)file_name, O_RDWR | O_CREAT, 0666)) == -1)
    {
        stop_Io("open error", EXIT_FAILURE);
    }

    file->fd = fd;
    file->read_index = -1;
    file->write_index = -1;
    return file;
}

void mini_cp(char *src, char *dst)
{
    MYFILE *src_file = mini_fopen(src, 'r');
    MYFILE *dst_file = mini_fopen(dst, 'c'); /*ou 'w', si on part du fait que dest est un fichier déjà éxistante.*/

    char c = mini_fgetc(src_file);

    while (c != -1)
    {
        mini_fputc(dst_file, c);
        c = mini_fgetc(src_file);
    }
    mini_exit_io();
}

void mini_echo(char *buffer)
{
    MYFILE *file_tmp = mini_fopen("/dev/stdout", 'b'); /*pour accédé à la sortue standard*/
    mini_fwrite(buffer, sizeof(char), mini_strlen(buffer), file_tmp);
    mini_exit_io();
}

void mini_cat(char *src)
{
    MYFILE *file = mini_fopen(src, 'b');
    char str = mini_fgetc(file);

    while (str != -1)
    {
        char *buffer = mini_calloc(sizeof(char), 2);
        buffer[0] = str;
        mini_echo(buffer);
        str = mini_fgetc(file); /*récursivité*/
    }
}

void mini_exit_io()
{
    if (file_list != NULL)
    {
        FILE_elm_list *temp_file = file_list;
        while (temp_file != NULL)
        {
            mini_fflush(temp_file->file);
            temp_file = temp_file->next;
        }
    }
}
