#include "tipo.h"
#include "liste.h"
#include <stdbool.h>

#define MAX_CARTE 52

//prototipi 
long int int_input(char*, int, int);
char* string_input(char* msg);
void pesca(lista* carte_utente);
void stampa(lista carte_utente);
lista scala(lista carte, int* lunghezza);
void stampaScala(lista primaCarta, int lunghezza);  
int cala(lista* carte);

int main(){
    //int numero_giocatori = 2;
    size_t cards_per_player = int_input("\n\nQuante carte devono essere assegnate per ogni giocatore? ", 1, MAX_CARTE / 2);

    //utilizzo due liste per far pescare cards_per_player carte per ogni giocatore
    lista carte_utente_1 = NULL;
    lista carte_utente_2 = NULL;

    for(int i=0; i<cards_per_player; i++){
        printf("\nPescaggio numero [%d] per utente 1...", i+1);
        pesca(&carte_utente_1);
        printf("\nPescaggio numero [%d] per utente 2...", i+1);
        pesca(&carte_utente_2);
    }


    //stampa del mazzo generato
    printf("\nMAZZO GENERATO PER L'UTENTE 1: \n");  
    stampa(carte_utente_1);
    printf("\nMAZZO GENERATO PER L'UTENTE 2: \n");  
    stampa(carte_utente_2);


    //punto 2
    int lunghezza_scala_utente1 = 0; 
    lista scala_utente1 = scala(carte_utente_1, &lunghezza_scala_utente1);
    printf("\n\nPrima scala incontrata per l'utente 1: "); 
    stampaScala(scala_utente1, lunghezza_scala_utente1);

    int lunghezza_scala_utente2 = 0;
    lista scala_utente2 = scala(carte_utente_2, &lunghezza_scala_utente2);
    printf("\n\nPrima scala incontrata per l'utente 2: "); 
    stampaScala(scala_utente2, lunghezza_scala_utente2);


    //punto 2.a
    //printf("\nPunteggio prima scala trovata per l'utente 1: %d", cala(&scala_utente1));
    //printf("\nPunteggio prima scala trovata per l'utente 2: %d", cala(&scala_utente2));

    //implementazione di 2 turni 
    bool break_game = false;
    int numero_turni = 2;
    int punteggio1 = 0, punteggio2 = 0;

    for(int n_turno = 1; n_turno<=numero_turni && !break_game; n_turno++){
        printf("\n\nTURNO NUMERO [%d]", n_turno);
        
        //mano del giocatore 1
        pesca(&carte_utente_1); 
        punteggio1 += cala(&carte_utente_1);
        printf("\nPunteggio giocatore 1: %d", punteggio1);
        printf("\nMAZZO RIMANENTE PER L'UTENTE 1: \n");  
        stampa(carte_utente_1);

        //se l'utente 1 ha già vinto... 
        if(carte_utente_1 == NULL && punteggio1 > punteggio2){
            printf("\nIL VINCITORE E' IL GIOCATORE 1!!!");
            break_game = true;
        } else{
            //mano del giocatore 2
            pesca(&carte_utente_2);
            punteggio2 += cala(&carte_utente_2); //sommo il punteggio di questo turno con quelli precedenti
            printf("\nPunteggio giocatore 2: %d", punteggio2);
            printf("\nMAZZO RIMANENTE PER L'UTENTE 2: \n");  
            stampa(carte_utente_2);

            if(carte_utente_2 == NULL && punteggio2 > punteggio1){
                printf("\nIL VINCITORE E' IL GIOCATORE 2!!!");
                break_game = true;
            }

            //else --> se nessuno dei due ha terminato le carte, non vince nessuno 
        }
    }


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
        printf("\t- Errore nell'acquisizione dell'input\n");
        return int_input(msg, minimum_value, max_value);
    }

    //effettuo dei controlli per verificare che l'inut sia corretto
    if(cpp < minimum_value || cpp > max_value){
        printf("\t- Input non valido, riprovare\n");
        return int_input(msg, minimum_value, max_value);
    }

    return cpp;
}

char* string_input(char* msg){
    printf("%s", msg); 
    int max_car_descrizione = 50;
    char buffer[max_car_descrizione]; 

    while(fgets(buffer, max_car_descrizione - 1, stdin) == NULL){
        printf("\nInput fallito\n");
    }

    if(buffer[strlen(buffer) - 1] == '\n')
        buffer[strlen(buffer) - 1] = '\0';

    //effettuare il controllo che sia == 'F', 'C', 'Q', 'P'
    return buffer;
}

/**
 * pescaggio delle carte dal mazzo
 * l'input delle carte è gestito da tastiera
 */
void pesca(lista* carte_utente){
    char* seme = string_input("\nSeme della carta da pescare: "); 
    int valore = int_input("Valore della carta da pescare: ", 1, 13);

    //creo la carta value + seme
    tipo_inf carta_da_inserire;   
    strcpy(carta_da_inserire.descrizione, seme);
    carta_da_inserire.value = valore;

    //aggiungo la carta alla lista in base all'ordine delle carte
    *carte_utente = ord_insert_elem(*carte_utente, new_elem(carta_da_inserire));
}

/**
 * @brief Stampa della lista di carte in mano ad ogni giocatore
 * 
 * @param carte_utente 
 */
void stampa(lista carte_utente){
    if(carte_utente == NULL) printf("\nFine gioco"); 
    else{
        while(carte_utente != NULL){
            printf("\t%d%s", carte_utente->inf.value, carte_utente->inf.descrizione);  
            carte_utente = carte_utente->pun;
        }
    }

    printf("\n\n");
}  

/**
 * @brief verifica e restituisce la PRIMA scala che si incontra a partire dall'inizio della lista
 * 
 * @param carte 
 * @param lunghezza 
 * @return puntatore alla prima carta della scala + lunghezza della scala
 */
elem* scala(lista carte, int* lunghezza){
    //carte è la lista di carte del giocatore 
    //lunghezza indica la lunghezza della scala
    //una scala --> 3 carte dello stesso seme consecutive 1q - 2q - 3q

    if(carte == NULL) return NULL;
    //inserisco la prima carta di default all'interno di una possibile scala
    lista primaCartaScala = carte; 
    *lunghezza = 1; 
    lista tailScala = carte; //ultima carta della scala (mi serve per confrontare i valori consecutivi)
    carte = carte->pun;

    //
    //printf("\nCarta aggiunta: %d%s", tailScala->inf.value, tailScala->inf.descrizione);

    /*la scala intera è dotata di due parti: 
        la prima carta 
        la lunghezza della scala

    questo mi permette di non creare un'altra lista
    */  

    while (carte != NULL){
        //printf("\nCarta considerata: %d%s", carte->inf.value, carte->inf.descrizione);

        //se la carta considerata può entrare in scala... 
        if(carte->inf.value == (tailScala->inf.value + 1)
            && strcmp(carte->inf.descrizione, tailScala->inf.descrizione) == 0){
                //primaCartaScala non cambia, la prima carta della scala rimane invariata
                *lunghezza = *lunghezza + 1; //aumenta la lunghezza della scala
                tailScala = carte; //modifico la nuova tail della scala
                //printf("\nCarta aggiunta: %d%s", tailScala->inf.value, tailScala->inf.descrizione);
        } else{ //altrimenti... 
            //se ho già identificato una scala, la ritorno 
            if(*lunghezza >= 3) return primaCartaScala; 

            //altrimenti, devo ripristinare una nuova scala
            primaCartaScala = carte; 
            tailScala = carte; 
            *lunghezza = 1;
            //printf("\nRipristino scala. carta aggiunta: %d%s", tailScala->inf.value, tailScala->inf.descrizione);
        }

        carte = carte->pun;
    } 

    //se scorrendo tutta la lista ho identificato una scala, la ritorno 
    if(*lunghezza >= 3) return primaCartaScala;
    *lunghezza = 0; //ripristino che la lunghezza della scala è pari a 0 (non è stata trovata)
    return NULL;   
    
}

void stampaScala(lista primaCarta, int lunghezza){
    for(int i=0; i<lunghezza; i++){
        printf("%d%s\t", primaCarta->inf.value, primaCarta->inf.descrizione);
        primaCarta = primaCarta->pun;
    }

    printf("\n\n");
}

int cala(lista* carte_utente){
    //cala la prima scala trovata, eliminando quelle carte dalla mano del giocatore
    //cerco la prima scala del giocatore
    int lunghezzaScala = 0; 
    lista primaCartaScala = scala(*carte_utente, &lunghezzaScala);

    //se l'utente non ha scal in mano, il punteggio della scala è 0 
    if(primaCartaScala == NULL) return 0; 

    //elimino le carte appartenenti la scala dal mazzo dell'utente e calcolo il punteggio totale
    int punteggioTotale = 0; 
    printf("\nCarte calate: ");

    for(int i=0; i<lunghezzaScala; i++){
        punteggioTotale += primaCartaScala->inf.value;
        printf("\t%d%s", primaCartaScala->inf.value, primaCartaScala->inf.descrizione);

        if(primaCartaScala->pun != NULL){ //se non devo eliminare l'ultima carta del mezzo... 
            //faccio prima->pun per evitare di perdere il riferimento
            primaCartaScala = primaCartaScala->pun;
            *carte_utente = delete_elem(*carte_utente, primaCartaScala->prev); 
        } else{
            *carte_utente = delete_elem(*carte_utente, primaCartaScala);
        }
        
    }

    return punteggioTotale;
}