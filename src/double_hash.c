#include <stdio.h>
#include <stdlib.h>
#include "double_hash.h"

// Função hash1
int hash1(int key, int size, int *pesos) {
    return (key * pesos[0] + pesos[1]) % size;
}

// Função hash2
int hash2(int key, int size, int *pesos) {
    // Para evitar o hash2 de ser zero, usamos (pesos[2] + key) % (size - 1) + 1
    return (key * pesos[2] + pesos[3]) % (size - 1) + 1;
}

// Inicialização da Tabela Hash
HashTable *inicializarHash(int size) {
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    if (hashTable == NULL) {
        printf("Erro de memória\n");
        return NULL;
    }

    hashTable->size = size;
    hashTable->table = (HashEntry *)malloc(size * sizeof(HashEntry));
    if (hashTable->table == NULL) {
        printf("Erro de memória\n");
        free(hashTable);
        return NULL;
    }

    // Inicializa as entradas como não ocupadas
    for (int i = 0; i < size; i++) {
        hashTable->table[i].is_occupied = 0;
    }

    // Aloca e inicializa o vetor de pesos
    hashTable->pesos = (int *)malloc(4 * sizeof(int));
    hashTable->pesos[0] = 1;
    hashTable->pesos[1] = 2;
    hashTable->pesos[2] = 3;
    hashTable->pesos[3] = 4;

    return hashTable;
}

// Inserção na Tabela Hash utilizando dupla hashing
void inserirHash(HashTable *hashTable, int key, int value) {
    int index = hash1(key, hashTable->size, hashTable->pesos);
    int step = hash2(key, hashTable->size, hashTable->pesos);

    while (hashTable->table[index].is_occupied) {
        if (hashTable->table[index].key == key) {
            // Atualiza o valor se a chave já existe
            hashTable->table[index].value = value;
            return;
        }
        // Avança para o próximo índice utilizando a função de hashing duplo
        index = (index + step) % hashTable->size;
    }

    // Insere a nova entrada
    hashTable->table[index].key = key;
    hashTable->table[index].value = value;
    hashTable->table[index].is_occupied = 1;
}

// Busca na Tabela Hash utilizando dupla hashing
int buscarHash(HashTable *hashTable, int key) {
    int index = hash1(key, hashTable->size, hashTable->pesos);
    int step = hash2(key, hashTable->size, hashTable->pesos);

    while (hashTable->table[index].is_occupied) {
        if (hashTable->table[index].key == key) {
            return hashTable->table[index].value;
        }
        // Avança para o próximo índice utilizando a função de hashing duplo
        index = (index + step) % hashTable->size;
    }

    return -1; // Indica que a chave não foi encontrada
}

// Desalocação da Tabela Hash
void desalocarHash(HashTable **hashTable) {
    if (hashTable == NULL || *hashTable == NULL) {
        return;
    }

    free((*hashTable)->table);
    free((*hashTable)->pesos); // Libera o vetor de pesos
    free(*hashTable);
    *hashTable = NULL;
}
