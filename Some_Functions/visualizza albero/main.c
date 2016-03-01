#include <stdio.h>
#include <stdlib.h>


typedef struct node_t {
                        char *nome;
                        char *cognome;
                        int voto;
                        struct node_t *figlio_sx, *fratello;
                      }*NODO;



void visualizza_albero(NODO Ptr);


int main()
{


    return 0;
}


void visualizza_albero(NODO Ptr)
{
    if(Ptr!=NULL)
       printf("%s %s %d \n", Ptr->cognome, Ptr->nome, Ptr->voto);
    else return;

    if(Ptr->figlio_sx!=NULL) visualizza_albero(Ptr->figlio_sx);
    if(Ptr->fratello!=NULL) visualizza_albero(Ptr->fratello);

}
