#include <stdio.h>
#include <stdlib.h>
#define max 10
#include <string.h>



typedef struct node_t {
                        char *stringa;
                        struct node_t *next;
                      } *NODE;

struct node_t *splitStr(char *str);
struct node_t *new_NODO(char *stringa, NODE next_ptr, int count);
struct node_t *inizializza(char *stringa, NODE nodo_iniziale, int count);
void printf_LISTA(NODE lista_ptr);


int main()
{
    char stringa[max];
    NODE lista_ptr;

    printf("Dammi la stringa:"); scanf("%s", stringa);

    lista_ptr=splitStr(stringa);

    if(lista_ptr!=NULL)
    printf_LISTA(lista_ptr);


    return 0;
}

struct node_t *splitStr(char *str)
{
    char *stringa;
    int count, i=0, indice, j;
    NODE lista=malloc(sizeof(struct node_t));

    lista->stringa=NULL;

    if(str[0]=='\0') { printf("Stringa nulla!\n"); return NULL; }

    while(str[i]!='\0')
    {
        count=0; indice=i;

        while(str[i]!='.' && str[i]!='\0')
         {
           i++;
           count++;
         }
        i++;

        stringa=malloc((count+1)*sizeof(char));

        for(j=0; j<count; j++)
          {
              stringa[j]=str[indice];
              indice++;
          }
         stringa[j]='\0';


         if(lista->stringa==NULL) lista=inizializza(stringa, lista, count+1);
         else lista->next=new_NODO(stringa, lista->next, count+1);


         if(str[i-1]=='\0') return lista;

    }


    return lista;
}

struct node_t *new_NODO(char *stringa, NODE next_ptr, int count)
{
   NODE tmp=malloc(sizeof(struct node_t));

   tmp->stringa=malloc(count*sizeof(char));
   tmp->stringa=stringa;
   tmp->next=next_ptr;

   return tmp;
}

struct node_t *inizializza(char *stringa, NODE nodo_iniziale, int count)
{
     nodo_iniziale->stringa=malloc(count*sizeof(char));
     nodo_iniziale->stringa=stringa;
     nodo_iniziale->next=NULL;

   return nodo_iniziale;
}

void printf_LISTA(NODE lista_ptr)
{
    NODE tmp;

    tmp=lista_ptr;

    while(tmp!=NULL)
    {
        printf("%s\n", tmp->stringa);
        tmp=tmp->next;
    }

}


