#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funzioni.h"
#define DIM 100+1

struct PRODUTTORE {                   /* Ho cambiato il nome della struct da AUTO del compito a PRODUTTORE perchè più corretto*/
                      char nome[DIM];
                      int modelli;
                      modello *model_ptr;   /*punta a vettore di puntatori che puntano ad un vettore con tutti i modelli*/
                      produttore prod_ptr;  /*punta al nodo successivo nel caso ci siano più produttori nella stessa casella vettore*/
                  };

struct MODELLO {
                      char nome_modello[DIM];
                      accessori acc_ptr; /*punta ad un vettor di strutture dove ogni struct ha un accessorio ed il prezzo*/
                      int accessori;
                      modello ptr;   /*punta al nodo successivo nel caso ci siano più modelli nella stessa casella vettore*/
               };

struct ACCESSORI {
                   char nome[DIM];
                   float prezzo;
                 };

produttore crea_produttori(produttore vet, char nome_file[], int *dim_modelli) /*crea vettore di strutture, ogni struct è un produttore*/
{                                                                              /*da qua si avranno i puntatori per tutti i modelli e gli accessori*/
    FILE *fp;
    char stringa[DIM], PRODUTTORE[DIM], TESTO[DIM];
    int i;
    int modelli=0, pos;
    produttore Ptr;


    if( (fp=fopen(nome_file, "r"))==NULL ) { printf("Errore apertura file!\n"); return NULL; }


    if( (vet=malloc(26 * sizeof(struct PRODUTTORE)))==NULL ) { printf("Errore di allocazione memoria!\n"); return NULL; }
    for(i=0; i<26; i++) { vet[i].modelli=0; vet[i].prod_ptr=NULL; } /*Inizializzo tutte le struct a 0*/
    /*Alloco un vettore di 26 come le lettere alfabetiche visto che le case automobilistiche al mondo non sono moltissime*/
    /*posso allocare uno spazio predefinito e se si sovrapporanno creerò liste*/


    while( fgets(stringa, DIM, fp)!=NULL )
    {
      sscanf(stringa, "%s %s", PRODUTTORE, TESTO);

      pos=find_pos(PRODUTTORE, 1, 0);

      Ptr=&vet[pos];
      while(Ptr->prod_ptr!=NULL) Ptr=Ptr->prod_ptr;       /*Verifico se la prima struct è occupata*/

      if(Ptr->modelli==0);                                /*Se lo è creo un nuovo nodo della lista*/
      else
         {
             Ptr->prod_ptr=malloc(sizeof(struct PRODUTTORE));
             Ptr=Ptr->prod_ptr;
             Ptr->prod_ptr=NULL;
         }

      strcpy(Ptr->nome, PRODUTTORE);
      Ptr->model_ptr=crea_modelli(Ptr->model_ptr, TESTO, &Ptr->modelli); if(Ptr->model_ptr==NULL) return NULL; /*alloca un vettore lungo quanto i modelli del produttore che punterà*/
      /*ad un vettore comune a tutte le case con tutti i modelli di tutte le case*/
      /*la funz ritorna anche il numero di modelli del produttore*/

      modelli=modelli+Ptr->modelli; /*calcola modelli totali di tutte le case per allocare dopo un vettore*/

    }

    *dim_modelli=modelli;

    fclose(fp);

    return vet;

}

int find_pos(char stringa[], int n, int M) /*Calcola la posizione nella tabella dalla stringa*/
{                                   /*Usa solo la 1' lettera nel caso dei PRODUTTORI perchè pochi e con nomi molto diversi*/
    int pos=0, base=128;
    int i;

    if(n==1)
    {
       pos=stringa[0]%65;  /*65 perchè la 1'lettera è maiuscola vista la formattazione dei file testo*/
    }

    else
    {
       for(i=0; stringa[i]!='\0'; i++)
       pos=( base * pos +stringa[0])%M;
    }

    return pos;
}

modello *crea_modelli(modello *modello_ptr,char testo[],int *dim)
{
    FILE *Fptr;
    char stringa[DIM];
    int N=0, i;

    if( (Fptr=fopen(testo, "r"))==NULL ) { printf("Errore apertura file!\n"); return NULL; }

     while( fgets(stringa, DIM, Fptr)!=NULL ) N++;
     fclose(Fptr);

     if( (modello_ptr=malloc(N * sizeof(modello)))==NULL ) { printf("Errore di allocazione memoria!\n"); return NULL; }
     for(i=0; i<N; i++)
     modello_ptr[i]=malloc(sizeof(struct MODELLO));


     *dim=N;

     return modello_ptr;
}

modello crea_vet_modelli_tot(modello vet_modelli,int dim_modelli)
{
    int i;

    vet_modelli=malloc(dim_modelli * sizeof(struct MODELLO));
    if(vet_modelli==NULL) { printf("Errore di allocazione memoria!\n"); return NULL; }
    for(i=0; i<dim_modelli; i++) {vet_modelli[i].accessori=0; vet_modelli[i].ptr=NULL; }

    return vet_modelli;
}

produttore aggiungi_informazioni(produttore vet_produttori, char nome_file[],modello vet_modelli, int dim_modelli)
{
    FILE *fp, *FP_mod;
    char stringa[DIM], PRODUTTORE[DIM], TESTO[DIM], TESTO_ACC[DIM], NOME_MODELLO[DIM];
    int pos, i, P;
    produttore Ptr;
    modello MPtr;
    int dim_acc;
    int M=trovaM(dim_modelli); /*funzione per trovare il numero primo da usare in hash*/


    fp=fopen(nome_file, "r");

    while( fgets(stringa, DIM, fp)!=NULL )
    {
      sscanf(stringa, "%s %s", PRODUTTORE, TESTO);

      pos=find_pos(PRODUTTORE, 1, 0);

      Ptr=&vet_produttori[pos];

      while( strcmp(Ptr->nome, PRODUTTORE)!=0)
      Ptr=Ptr->prod_ptr;

      FP_mod=fopen(TESTO, "r");

      for(i=0; i<Ptr->modelli; i++)
      {
        fscanf(FP_mod, "%s %s", NOME_MODELLO, TESTO_ACC);

        P=find_pos(NOME_MODELLO, 2, M);

        MPtr=&vet_modelli[P];

        while(MPtr->ptr!=NULL) MPtr=MPtr->ptr; /*Se c'è la lista la visita fino al punto voluto*/

        if(MPtr->accessori==0); /*se il nodo è vuoto inserisce i dati altrimenti ne crea uno vuoto*/
         else
            {
             MPtr->ptr=malloc(sizeof(struct MODELLO));
             MPtr=MPtr->ptr;
             MPtr->ptr=NULL;
            }

        strcpy(MPtr->nome_modello, NOME_MODELLO);

        MPtr->acc_ptr=crea_accessori(MPtr->acc_ptr, TESTO_ACC, &dim_acc); /*funzione che ritorna un puntatore ad un vettore di struct, ogni struct ha un accessorio*/
        if(MPtr->acc_ptr==NULL) return NULL;

        MPtr->accessori=dim_acc;
        Ptr->model_ptr[i]=MPtr; /*assegna l'indirzzo ottenuto al vettore modelli del produttore corrispondente*/
    }

      fclose(FP_mod);
    }

   fclose(fp);
   return vet_produttori;
}

int trovaM(int dim_modelli) /*trova il valore di M da usare per il calcolo dell'indice nella funzione find_pos*/
{
    int primo=0, exit=0, successivo=0, N, i;

    while(primo==0)     /*cerca il primo numero primo maggiore della dimensione dei modelli totali*/
    {
        exit=0;

        for(i=2; i<N/2 && exit!=1; i++)
        {
            N=dim_modelli+successivo;
            if( N%i==0 )
            exit=1;
        }
        successivo++;
        if(exit==0) primo=1;

    }

    return N;
}

accessori crea_accessori(accessori accessori_ptr, char nome_testo[], int *N)
/*alloca il vettore di struct ACCESSORI inserisce le informazioni */
{
    FILE *Fptr;
    char stringa[DIM];
    int n=0, i;

    if ( (Fptr=fopen(nome_testo, "r"))==NULL ) { printf("Errore apertura file!\n"); return NULL; }

    while( (fgets(stringa, DIM, Fptr))!=NULL )
    n++;

    rewind(Fptr);

    if( (accessori_ptr=malloc(n * sizeof(struct ACCESSORI)))==NULL ) { printf("Errore allocazione memoria!\n"); return NULL; }

    for(i=0; i<n; i++)
    {
        fgets(stringa, DIM, Fptr);
        sscanf(stringa,"%s %f", accessori_ptr[i].nome, &accessori_ptr[i].prezzo );
    }
    *N=n;

    fclose(Fptr);

    return accessori_ptr;

}

void printf_MODELLI(char stringa[], produttore vet_produttori) /*stampa i modelli*/
{
    int pos, i;
    produttore ptr;
    int find=0;

    pos=find_pos(stringa, 1, 0);

    if(pos>25) { printf("Produttore non trovato!\n"); return; }

    ptr=&vet_produttori[pos];

    while( ptr!=NULL && find!=1 )
     {
         if( strcmp(ptr->nome, stringa)==0 ) find=1;
         else ptr=ptr->prod_ptr;
     }

    if(find==0) { printf("Produttore non trovato!\n"); return; }

    printf("I modelli di %s sono:\n", stringa);
    for(i=0; i<ptr->modelli; i++)
    if(ptr->model_ptr[i]->accessori!=0)
    printf("%s \n", ptr->model_ptr[i]->nome_modello);

    /*la dimensione dei modelli non è un valore corretto infatti se vengono cancellati dei modelli non
    viene aggiornato, serve solo per sapoere la lunghezza massima del vettore durante la stampa*/

    printf("\n");

}

void printf_ACCESSORI(modello vet_modelli, int dim_modelli, char stringa[]) /*stampa gli accessori*/
{
   int pos, i;
   modello ptr;
   int find=0;

   pos=find_pos(stringa, 2, trovaM(dim_modelli));

   if(pos>dim_modelli-1) { printf("Modello non trovato!\n"); return; }

   ptr=&vet_modelli[pos];

    while( ptr!=NULL && find!=1 )
     {
         if( strcmp(ptr->nome_modello, stringa)==0 ) find=1;
         else ptr=ptr->ptr;
     }

    if(find==0) { printf("Modello non trovato!\n"); return; }

    printf("Gli accessori di %s sono:\n", stringa);
    for(i=0; i<ptr->accessori; i++)
    if( ptr->acc_ptr[i].prezzo!=0 ) printf("%s \n", ptr->acc_ptr[i].nome);
     /*la dimensione degli accessori non è un valore corretto infatti se vengono cancellati degli accessori non
    viene aggiornata, serve solo per sapoere la lunghezza massima del vettore durante la stampa*/

    printf("\n");
}

int DELETE_PROD(produttore vet_produttori, char stringa[])
{
    int pos;
    produttore ptr;
    int find=0;
    int j;

    pos=find_pos(stringa, 1, 0);

    if(pos>25) { printf("Produttore non trovato!\n"); return 0; }

    ptr=&vet_produttori[pos];

    while( ptr!=NULL && find!=1 )
     {
         if( strcmp(ptr->nome, stringa)==0 ) find=1;
         else ptr=ptr->prod_ptr;
     }

    if(find==0) { printf("Produttore non trovato!\n"); return 0; }

    ptr=&vet_produttori[pos];

    /*Elimino gli accessori e il modello*/
    for(j=0; j<ptr->modelli; j++)
    {
        free(ptr->model_ptr[j]->acc_ptr); /*gli accessori li dealloco*/
        ptr->model_ptr[j]->acc_ptr=NULL;

        ptr->model_ptr[j]->accessori=0;   /*i modelli non li dealloco ma setto i punti che utilizzo per vedere se esistono o no*/
        strcpy( ptr->model_ptr[j]->nome_modello, "\0");
    }

    /*elimino i puntatori ai modelli e setto i valori della struct del produttore per farlo apparire inesistente*/

        free(ptr->model_ptr);
        ptr->model_ptr=NULL;
        ptr->modelli=0;
        strcpy(ptr->nome, "\0");

     return 1;
}

int DELETE_MOD(char stringa[], modello vet_modelli, int dim_modelli)
{
    int pos;
    modello ptr;
    int find=0;

    pos=find_pos(stringa, 2, trovaM(dim_modelli));

    if(pos>dim_modelli-1) { printf("Modello non trovato!\n"); return 0; }

    ptr=&vet_modelli[pos];

    while( ptr!=NULL && find!=1 )
     {
         if( strcmp(ptr->nome_modello, stringa)==0 ) find=1;
         else ptr=ptr->ptr;
     }

    if(find==0) { printf("Modello non trovato!\n"); return 0; }
    /*i modelli non li elimino davvero ma setto i loro valori come fossero inesistenti.
     Gli accessori invece gli elimino fisicamente in quanto propri del modello*/

    free(ptr->acc_ptr);
    ptr->acc_ptr=NULL;

    ptr->accessori=0;
    strcpy( ptr->nome_modello, "\0");

    return 1;
}

int DELETE_ACC(char stringa[], modello vet_modelli, int dim)
{
    int i, j;
    modello ptr;
    int del;

    for(i=0; i<dim; i++)
    {
        ptr=&vet_modelli[i];

        for(j=0; j<ptr->accessori; j++)
        {
            if( strcmp(ptr->acc_ptr[j].nome, stringa)==0 )
              {
                  strcpy(ptr->acc_ptr[j].nome, "\0");
                  ptr->acc_ptr[j].prezzo=0;
                  del++;
              }
        }
    }
    if(del==0) return 0;

    return 1;
}

int incorpora(produttore vet_produttori,char stringa[], char stringa2[])
{
    int pos=find_pos(stringa,1,0);
    int pos2=find_pos(stringa2,1,0);
    int modelli_tot;
    modello *tmp;
    int i, j, find=0;
    produttore ptr, ptr2;

     /*Controllo esistano nella struttura dati i produttori cercati*/
    if(pos>25 && pos2>25) { printf("Produttore/i inesistenti!\n"); return 0; }

    ptr=&vet_produttori[pos];
    while( ptr!=NULL && find!=1 )
     {
         if( strcmp(ptr->nome, stringa)==0 ) find=1;
         else ptr=ptr->prod_ptr;
     }
    if(find==0) { printf("Produttore non trovato!\n"); return 0; }

    find=0;

    ptr2=&vet_produttori[pos2];
    while( ptr2!=NULL && find!=1 )
     {
         if( strcmp(ptr2->nome, stringa2)==0 ) find=1;
         else ptr2=ptr2->prod_ptr;
     }
    if(find==0) { printf("Produttore non trovato!\n"); return 0; }

    modelli_tot=ptr->modelli + ptr2->modelli;

    /*tramite l'ausilio di un vettore di puntatori temporaneo salvo i modelli del 1*
     produttore per allocare nuovamente lo spazio per ospitare i modelli del 2* che saranno inglobati,
     infine elimino il 2*produttore*/

    tmp=malloc(ptr->modelli * sizeof(modello)); if(tmp==NULL) { printf("Errore di allocazione!\n"); return 0; }
    for(i=0; i<ptr->modelli; i++) tmp[i]=malloc(sizeof(struct MODELLO));


    for(i=0; i<ptr->modelli; i++)  tmp[i]=ptr->model_ptr[i];

    free(ptr->model_ptr);

    ptr->model_ptr=malloc(modelli_tot * sizeof(malloc)); if(ptr->model_ptr==NULL) { printf("Errore di allocazione!\n"); return 0; }
    for(i=0; i<modelli_tot; i++) ptr->model_ptr[i]=malloc(sizeof(struct MODELLO));

    for(i=0; i<ptr->modelli; i++)
    ptr->model_ptr[i]=tmp[i];

    for(j=0; i<modelli_tot; i++, j++)
    ptr->model_ptr[i]=ptr2->model_ptr[j];

    free(tmp);

    free(ptr2->model_ptr);
    ptr2->modelli=0;
    strcpy(ptr2->nome, "\0");

    ptr->modelli=modelli_tot;

    return 1;
}










