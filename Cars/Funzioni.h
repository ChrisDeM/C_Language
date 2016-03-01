#ifndef FUNZIONI_H_INCLUDED
#define FUNZIONI_H_INCLUDED

typedef struct PRODUTTORE *produttore;
typedef struct MODELLO *modello;
typedef struct ACCESSORI *accessori;

produttore crea_produttori(produttore vet, char nome_file[], int *dim_modelli);
int find_pos(char stringa[], int n, int M);
modello *crea_modelli(modello *modello_ptr,char testo[],int *dim);
modello crea_vet_modelli_tot(modello vet_modelli, int dim_modelli);
produttore aggiungi_informazioni(produttore vet_produttori, char nome_file[], modello vet_modelli, int dim_modelli);
int trovaM(int dim_modelli);
accessori crea_accessori(accessori accessori_ptr, char nome_testo[], int *N);
void printf_MODELLI(char stringa[], produttore vet_produttori);
void printf_ACCESSORI(modello vet_modelli, int dim_modelli, char stringa[]);
int DELETE_PROD(produttore vet_produttori, char stringa[]);
int DELETE_MOD(char stringa[], modello vet_modelli, int dim_modelli);
int DELETE_ACC(char stringa[], modello vet_modelli, int dim);
int incorpora(produttore vet_produttori,char stringa[], char stringa2[]);
#endif // FUNZIONI_H_INCLUDED
