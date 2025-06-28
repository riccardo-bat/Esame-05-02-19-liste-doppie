#include "tipo.h"
#include "liste.h"

#define MAX_CARTE 52

//prototipi 
long int int_input(char*, int, int);
char char_input(char* msg);
void pesca(lista* carte_utente);
void stampa(lista carte_utente);

int main(){
    //int numero_giocatori = 2;
    size_t cards_per_player = int_input("\n\nQuante carte devono essere assegnate per ogni giocatore? ", 1, MAX_CARTE / 2);

    //utilizzo due liste per far pescare cards_per_player carte per ogni giocatore
    lista carte_utente_1 = NULL;
    lista carte_utente_2 = NULL;

    for(int i=0; i<cards_per_player; i++){
        printf("\nPescaggio per utente 1...");
        pesca(&carte_utente_1);
        printf("\nPescaggio per utente 2...");
        pesca(&carte_utente_2);
    }

    //stampa del mazzo generato
    printf("\nMAZZO GENERATO PER L'UTENTE 1: \n");  
    stampa(carte_utente_1);
    printf("\nMAZZO GENERATO PER L'UTENTE 2: \n");  
    stampa(carte_utente_2);

    return 0;
}

long int int_input(char* msg, int minimum_value, int max_value){
    printf("%s", msg);
    char buffer[100];

    while(fgets(buffer, sizeof(buffer), stdin) == NULL){
        printf("\nInput fallito\n");
    }

    //da string ad int
    char* endptr = NULL; //indica il primo carattere non convertito
    int base = 10;
    long int cpp = strtol(buffer, &endptr, base);

    //se endptr = buffer vuol dire che non è stato convertito alcun carattere in intero
    if(endptr == buffer){
        printf("\t- Errore nell'acquisizione dell'input");
        return int_input(msg, minimum_value, max_value);
    }

    //effettuo dei controlli per verificare che l'inut sia corretto
    if(cpp < minimum_value || cpp > max_value){
        printf("\t- Input non valido, riprovare");
        return int_input(msg, minimum_value, max_value);
    }

    return cpp;
}

char char_input(char* msg){
    printf("%s", msg); 
    char buffer; 

    while((buffer = getchar()) == '\n'){
        printf("\nInput fallito\n");
    }

    //per evitare che il "\n" rimanga salvato nel terminale, questo viene consumato
    while (getchar() != '\n' && getchar() != EOF)
        ;

    //effettuare il controllo che sia == 'F', 'C', 'Q', 'P'
    return buffer;
}

/**
 * pescaggio delle carte dal mazzo
 * l'input delle carte è gestito da tastiera
 */
void pesca(lista* carte_utente){
    char seme = char_input("\nSeme della carta da pescare: "); 
    int valore = int_input("Valore della carta da pescare: ", 1, 13);

    //creo la carta value + seme
    tipo_inf carta_da_inserire;   
    char tmp[2] = { seme, '\0' };
    strcpy(carta_da_inserire.descrizione, tmp);
    carta_da_inserire.value = valore;

    //aggiungo la carta alla lista in base all'ordine delle carte
    *carte_utente = ord_insert_elem(*carte_utente, new_elem(carta_da_inserire));
}

void stampa(lista carte_utente){
    while(carte_utente != NULL){
        printf("\t%d%s", carte_utente->inf.value, carte_utente->inf.descrizione);  
        carte_utente = carte_utente->pun;
    }

}  