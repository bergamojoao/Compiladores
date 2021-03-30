CC=gcc

PROGRAMA = regalloc

$(PROGRAMA): 
	$(CC) -c *.c -I.
	$(CC) *.o -o $(PROGRAMA)

clean:
	rm -f *.o
	rm -f *.exe
	rm -f $(PROGRAMA)
