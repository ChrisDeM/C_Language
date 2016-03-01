#include <stdio.h>
#include <stdlib.h>
#include "Funzioni.h"
#define DIM 100+1


int main(int argc, char *argv[])
{

    produttore vet_produttori;
    char stringa[DIM], stringa2[DIM];
    int scelta=8;
    int dim_modelli;
    modello vet_modelli;


    if(argc!=2) { printf("Errore da linea di comando!\n"); return 0; }

    vet_produttori=crea_produttori(vet_produttori, argv[1], &dim_modelli); if(vet_produttori==NULL) return 0;
    vet_modelli=crea_vet_modelli_tot(vet_modelli, dim_modelli); /*alloca un vettore che contiene tutti i modelli di tutti i produttori*/
    if(vet_modelli==NULL) return 0;                                                            /*ogni produttore punterà ad i suoi modelli*/

    vet_produttori=aggiungi_informazioni(vet_produttori, argv[1], vet_modelli, dim_modelli); if(vet_produttori==NULL) return 0; /*inserisce tutte le informazioni dei file in una struttura dati*/

    printf("Possibili scelte: \n");
    printf("1: Visualizza modelli di un produttore\n2: Visualizza accessori di un modello\n3: Cancella un produttore e tutto cio' ad esso associato\n");
    printf("4: Cancella un modello e tutto cio' ad esso associato\n5: Cancella un accessorio\n6: Incorpora produttore 2 in 1\n7: Esci\n");

    while(scelta!=7)
    {
        printf("Che vuoi fare? "); scanf("%d", &scelta);

        switch(scelta)
        {
            case 1: printf("Dammi il produttore di cui vuoi vedere i modelli: "); scanf("%s", stringa);
                    printf_MODELLI(stringa, vet_produttori);
                    break;

            case 2: printf("Dammi il modello di cui vuoi vedere gli accessori: "); scanf("%s", stringa);
                    printf_ACCESSORI(vet_modelli, dim_modelli, stringa);
                    break;

            case 3: printf("Dammi il produttore che vuoi cancellare: "); scanf("%s", stringa);
                    if( DELETE_PROD(vet_produttori, stringa) ) printf("Produttore, relativi modelli e accessori cancellati!\n\n");
                    else printf("Produttore non trovato!\nn");
                    break;
            case 4: printf("Dammi il modello che vuoi cancellare: "); scanf("%s", stringa);
                    if( DELETE_MOD(stringa, vet_modelli, dim_modelli) ) printf("Modello e suoi accessori cancellato!\n\n");
                    else printf("Modello non trovato!\n\n");
                    break;

            case 5: printf("Dammi l'accessorio da eliminare: "); scanf("%s", stringa);
                    if( DELETE_ACC(stringa, vet_modelli, dim_modelli) ) printf("Accessorio eliminato!\n\n");
                    else printf("Accessorio non trovato!\n\n");
                    break;

            case 6: printf("Dammi il primo produttore ed il secondo: "); scanf("%s %s", stringa, stringa2);
                    if( incorpora(vet_produttori, stringa, stringa2) ) printf("%s incorporato in %s\n\n", stringa2, stringa);
                    else printf("Non e' stato possibile unire!\n\n");

                    break;


           }


    }

    return 0;
}
