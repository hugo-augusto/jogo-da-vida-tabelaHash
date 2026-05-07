#pragma once

// Estrutura da Tabela Hash
typedef struct {
    int key;         // A chave que representa uma célula viva (1) ou morta (0)
    int value;       // Valor associado à chave, no caso do Jogo da Vida, será 1 (vivo) ou 0 (morto)
    int is_occupied; // 0 se a posição está vazia, 1 se está ocupada
} HashEntry;

// Estrutura principal da Tabela Hash com endereçamento aberto
typedef struct {
    int size;         // Tamanho da tabela
    HashEntry *table; // Array que representa a tabela hash
    int *pesos;       // Vetor de pesos para as funções hash
} HashTable;

// Função hash1
int hash1(int key, int size, int *pesos);

// Função hash2
int hash2(int key, int size, int *pesos);

// Função para inicializar a Tabela Hash
HashTable *inicializarHash(int size);

// Função para inserir um elemento na Tabela Hash
void inserirHash(HashTable *hashTable, int key, int value);

// Função para buscar um elemento na Tabela Hash
int buscarHash(HashTable *hashTable, int key);

// Função para desalocar a Tabela Hash
void desalocarHash(HashTable **hashTable);
