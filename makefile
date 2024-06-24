# Nome do executável
EXEC = todo

# Compilador
CC = gcc

# Flags do compilador
CFLAGS = -Wall -g

# Arquivos fonte
SRC = main.c tarefa.c

# Arquivos objeto (gerados a partir dos arquivos fonte)
OBJ = $(SRC:.c=.o)

# Regra padrão
all: $(EXEC)

# Regra para compilar o executável
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para compilar os arquivos objeto
%.o: %.c tarefa.h
	$(CC) $(CFLAGS) -c $<

# Regra de limpeza
clean:
	rm -f $(OBJ) $(EXEC)

# Regra de limpeza completa (inclui arquivos de backup)
distclean: clean
	rm -f *~ *.bak