#include "tipo.h"

/**
 * funzione compare per la comparazione dei valori interi di 2 parametri di tipo 'tipo_inf'
 * 
 */

int compare(tipo_inf a, tipo_inf b){
    //se a.value < b.value torno subito -1
    if(a.value < b.value) return -1;
    else if(a.value > b.value) return 1;
    else return 0;
}

void copy(tipo_inf *dest, tipo_inf src){
    *dest = src;
    /*dest->value = src.value;
    dest->descrizione = src.descrizione;*/
}

void print_tipo(tipo_inf v){
    printf("\n\t- Descrizione: %s", v.descrizione);
    printf("\n\t- Value: [%d]", v.value);
}