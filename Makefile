CC = gcc
CFLAGS = -Wall

#Regole 

#Fase di linking
esame: compito.o liste.o tipo.o 
	$(CC) $(CFLAGS) -o $@ $^

#Fase di traduzione
compito.o: compito.c liste.h tipo.h 
	$(CC) $(CFLAGS) -c $^

liste.o: liste.c liste.h 
	$(CC) $(CFLAGS) -c $^

tipo.o: tipo.c tipo.h 
	$(CC) $(CFLAGS) -c $^


clean: 
	del /F *.o *.out *.gch

.PHONY: clean