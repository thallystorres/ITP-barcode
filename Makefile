# Variáveis
CC = gcc
CFLAGS = -g -std=c99 -Wall -Wextra -Werror -pedantic

# Diretórios
BUILD_DIR = build
SRC_DIR = resources

# Fontes
ANALISAR_CODIGO = $(SRC_DIR)/analisarcodigo.c
ANALISE_PBM = $(SRC_DIR)/analisepbm.c
MANIPULAR_PBM = $(SRC_DIR)/manipularpbm.c
TABELA_LR = $(SRC_DIR)/tabelalr.c
VERIFICADOR = $(SRC_DIR)/verificador.c

# Objetos
OBJECTS_EXTRACT = $(BUILD_DIR)/analisarcodigo.o $(BUILD_DIR)/analisepbm.o $(BUILD_DIR)/tabelalr.o $(BUILD_DIR)/verificador.o
OBJECTS_GENERATE = $(BUILD_DIR)/manipularpbm.o $(BUILD_DIR)/analisepbm.o $(BUILD_DIR)/tabelalr.o $(BUILD_DIR)/verificador.o

# Regras principais
all: setup_dirs extract generate

extract: extract.c $(OBJECTS_EXTRACT)
	$(CC) $(OBJECTS_EXTRACT) extract.c -o extract $(CFLAGS)

generate: generate.c $(OBJECTS_GENERATE)
	$(CC) $(OBJECTS_GENERATE) generate.c -o generate $(CFLAGS)

# Regras para criar os objetos
$(BUILD_DIR)/analisarcodigo.o: $(ANALISAR_CODIGO)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/analisepbm.o: $(ANALISE_PBM)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/manipularpbm.o: $(MANIPULAR_PBM)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/tabelalr.o: $(TABELA_LR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR)/verificador.o: $(VERIFICADOR)
	$(CC) -c $< -o $@ $(CFLAGS)

# Criar o diretório build
setup_dirs:
	mkdir -p $(BUILD_DIR)

# Limpeza
clean:
	rm -f extract generate
	rm -rf $(BUILD_DIR)

# Declaração de regras falsas
.PHONY: all clean setup_dirs
