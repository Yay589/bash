#include "mini_lib.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <errno.h>
#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0


struct malloc_element *molloc_list=NULL;

void *mini_calloc (int size_element, int number_element){
    int taille_demandee=size_element*number_element;

    
    if (molloc_list!=NULL){
        struct malloc_element *cursor=molloc_list;

        while (cursor!=NULL)
        {
            if (cursor->statut==0 && cursor->taille_zone>taille_demandee){
                return cursor->zone;
            }
            cursor=cursor->next_malloc;
        }   

        
    }
    
    /*SI IL N'Y A PAS DE ZONE ALOUABLE, EXECUTER LE CODE CI-DESSOUS*/

    void *Buffer=sbrk(taille_demandee);
    if (Buffer==(void*)-1){
        perror("error occur for allocating using sbrk");
        return NULL;
    }
    for(int i=0;i<number_element;i++)
    {
         *((char*)Buffer+i)='\0';
    }    
    /*return ptr;exo4*/
    if (molloc_list==NULL){//si molloc_list est NULL on lui ajoute un element

        molloc_list=sbrk(sizeof(struct malloc_element)+taille_demandee);
        molloc_list->zone=Buffer;
        molloc_list->taille_zone=size_element;
        molloc_list->statut=1;
        molloc_list->next_malloc=NULL;// l'element suvant est null car c'est la fin de notre liste chainée
    }
    
    return Buffer;

    
}


/*mini free malloc */
void mini_free(void*ptr){
    printf("\n****mini_free****\n");

    struct malloc_element *ptr_molloc_list=molloc_list;
    while (ptr_molloc_list !=NULL){   
        if((ptr_molloc_list->zone= ptr)) ptr_molloc_list->statut=0;
        ptr_molloc_list=ptr_molloc_list->next_malloc;
    }
}
//--------
void mini_exit(int EXIT_VALUE) {
    mini_exit_string();
    mini_exit_io();
    _Exit(EXIT_VALUE);
}






