#include <stdlib.h>
#include <stdio.h>
#include "liste.h"

/* testina: restituisce inf del nodo p */
tipo_inf head(lista p) {
    return p->inf;
}

/* puntatore al next/prev */
lista tail(lista p) {
    return p ? p->pun : NULL;
}
lista prev_elem(lista p) {
    return p ? p->prev : NULL;
}

/* crea un nuovo nodo */
elem* new_elem(tipo_inf v) {
    elem *p = malloc(sizeof *p);
    if (!p) { perror("malloc"); exit(1); }
    copy(&p->inf, v);
    p->pun  = NULL;
    p->prev = NULL;
    return p;
}

/* inserimento in testa */
lista insert_elem(lista head, elem *e) {
    e->pun = head;
    if (head) head->prev = e;
    e->prev = NULL;
    return e;
}

/* cancellazione di un nodo */
lista delete_elem(lista head, elem *e) {
    if (!e) return head;
    if (e == head) {
        head = e->pun;
        if (head) head->prev = NULL;
    } else {
        e->prev->pun = e->pun;
        if (e->pun) e->pun->prev = e->prev;
    }
    free(e);
    return head;
}

/* ricerca lineare */
elem* search(lista head, tipo_inf v) {
    for (elem *p = head; p; p = p->pun) {
        if (compare(p->inf, v) == 0)
            return p;
    }
    return NULL;
}

/* ricerca in lista ordinata */
elem* ord_search(lista head, tipo_inf v) {
    for (elem *p = head; p && compare(p->inf, v) <= 0; p = p->pun) {
        if (compare(p->inf, v) == 0)
            return p;
    }
    return NULL;
}

/* inserimento in lista ordinata */
lista ord_insert_elem(lista head, elem *e) {
    if (!head || compare(e->inf, head->inf) < 0) {
        return insert_elem(head, e);
    }
    elem *p = head;
    while (p->pun && compare(p->pun->inf, e->inf) < 0) {
        p = p->pun;
    }
    /* inserisci e dopo p */
    e->pun      = p->pun;
    if (p->pun) p->pun->prev = e;
    p->pun      = e;
    e->prev     = p;
    return head;
}
