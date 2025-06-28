#ifndef TIPO_H
	#define TIPO_H

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	typedef struct {
		int  value;
		char descrizione[50];
	} tipo_inf;

	/* confronta due valori di tipo_inf: 0 se uguali, <0 o >0 altrimenti */
	int compare(tipo_inf a, tipo_inf b);

	/* copia src in *dest */
	void copy(tipo_inf *dest, tipo_inf src);

	/* stampa a video */
	void print_tipo(tipo_inf v);

#endif // TIPO_H
