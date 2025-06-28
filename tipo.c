#include "tipo.h"

/**
 * funzione compare per la comparazione dei valori interi di 2 parametri di tipo 'tipo_inf'
 * l'ordine dei semi è: cuori - fiori - picche - quadri
 */

int compare(tipo_inf a, tipo_inf b){
    //valuto prima i semi 
    if(strcmp(a.descrizione, b.descrizione) < 0) return -1; 
    if(strcmp(a.descrizione, b.descrizione) > 0) return 1;

    //se hanno la stessa descrizione, effettua una comparazione sui valori delle carte
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