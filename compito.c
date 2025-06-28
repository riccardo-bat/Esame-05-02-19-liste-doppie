#include "tipo.h"
#include "liste.h"

#define MAX_CARTE 52

//prototipi 
long int cards_per_player();

int main(){
    int numero_giocatori = 2;
    size_t cards_perPlayer = cards_per_player();



    return 0;
}

long int cards_per_player(){
    printf("\nQuante carte devono essere assegnate per ogni giocatore? ");
    char buffer[100];

    while(fgets(buffer, sizeof(buffer), stdin) == NULL){
        printf("\nInput fallito\n");
    }

    //da string ad int
    char* endptr = NULL; //indica il primo carattere non convertito
    long int cpp = strtol(buffer, &endptr, 10);

    //se endptr = buffer vuol dire che non è stato convertito alcun carattere in intero
    if(endptr == buffer){
        printf("\n\t- Errore nell'acquisizione dell'input");
        return cards_per_player();
    }

    return cpp;
}