#include "tipo.h"
#include "liste.h"

#define MAX_CARTE 52

//prototipi 
long int int_input(char*, int, int);
char char_input(char* msg);
void pesca(lista* carte_utente);
void stampa(lista carte_utente);
lista scala(lista carte, int* lunghezza);
void stampaScala(lista primaCarta, int lunghezza);  

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


    int lunghezza_scala = 0; 
    lista scala_utente1 = scala(carte_utente_1, &lunghezza_scala);
    printf("\n\nPrima scala incontrata per l'utente 1: "); 
    stampaScala(scala_utente1, lunghezza_scala);

    lunghezza_scala = 0;
    lista scala_utente2 = scala(carte_utente_2, &lunghezza_scala);
    printf("\n\nPrima scala incontrata per l'utente 2: "); 
    stampaScala(scala_utente2, lunghezza_scala);

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

/**
 * @brief Stampa della lista di carte in mano ad ogni giocatore
 * 
 * @param carte_utente 
 */
void stampa(lista carte_utente){
    while(carte_utente != NULL){
        printf("\t%d%s", carte_utente->inf.value, carte_utente->inf.descrizione);  
        carte_utente = carte_utente->pun;
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
    return NULL;   
    
}

void stampaScala(lista primaCarta, int lunghezza){
    for(int i=0; i<lunghezza; i++){
        printf("%d%s\t", primaCarta->inf.value, primaCarta->inf.descrizione);
        primaCarta = primaCarta->pun;
    }

    printf("\n\n");
}