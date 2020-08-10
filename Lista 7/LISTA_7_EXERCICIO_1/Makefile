FLEX=flex
BISON=bison
CC=gcc
CFLAGS=c99
LIBS=

PROGRAMA = l7e1
LEXICO = lexico.l

$(PROGRAMA): $(LEXICO)
	$(FLEX) $(LEXICO)
	$(CC) lex.yy.c $(LIBS) -o $(PROGRAMA)

clean:
	rm -f lex.yy.c
	rm -f l7e1