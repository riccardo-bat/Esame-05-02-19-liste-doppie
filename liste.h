#ifndef LISTE_H
#define LISTE_H

#include "tipo.h"

typedef struct elem {
    tipo_inf       inf;
    struct elem   *pun;   /* successivo */
    struct elem   *prev;  /* precedente */
} elem, *lista;

/* accesso */
tipo_inf  head(lista p);
lista      tail(lista p);
lista      prev_elem(lista p);

/* costruzione/cancellazione */
elem*      new_elem(tipo_inf v);
lista      insert_elem(lista head, elem *e);
lista      delete_elem(lista head, elem *e);

/* ricerca */
elem*      search(lista head, tipo_inf v);
elem*      ord_search(lista head, tipo_inf v);

/* inserimento ordinato */
lista      ord_insert_elem(lista head, elem *e);

#endif // LISTE_H
