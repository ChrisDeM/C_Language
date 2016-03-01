#include <stdio.h>
#include <stdlib.h>
#define max 10

void searchStr(char *str, int *start, int *lenght);

int main()
{
    char stringa[max];
    int lenght, start;

    printf("Dammi stringa:");
    scanf("%s", stringa);

    searchStr(stringa, &start, &lenght);

    if(lenght!=0) /*SE LA LUNGHEZZA RITORNATA E' ZERO VUOL DIRE CHE LA STRINGA ERA NULLA*/
       printf("La ripetizione inizia all'indice %d ed e' lunga %d", start, lenght);
    else printf("stringa nulla!");

    return 0;
}

void searchStr(char *str, int *start, int *lenght)
{
    char carattere='\0';
    int indice, indice_MAX;
    int lunghezza=0, lunghezza_MAX=0;
    int i=0;

    while(str[i-1]!='\0') /* i-1 COSì CICLA ANCORA UNA VOLTA PER AGGIORNARE
                             SE NECESSARIO LA LUNGHEZZA MASSIMA*/
    {

        if(carattere!=str[i])
           {
               if(lunghezza>lunghezza_MAX)
                   {
                      lunghezza_MAX=lunghezza;
                      indice_MAX=indice;
                   }

               carattere=str[i];
               lunghezza=1;
               indice=i;
           }
        else lunghezza++;

        i++;

    }

    *start=indice_MAX;
    *lenght=lunghezza_MAX;

}


