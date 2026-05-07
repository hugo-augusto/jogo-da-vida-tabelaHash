#pragma once

#include "double_hash.h" // Inclui a tabela hash com endereçamento duplo

// Definição do tipo Automato
typedef struct
{
    int n;             // Dimensão do Automato (n x n)
    HashTable *tabela; // Ponteiro para a tabela hash que representa o Automato
} Automato;

// Função para inicializar o autômato
Automato *alocarReticulado(int n);

// Função para desalocar a memória do Automato
void desalocarReticulado(Automato **tab);

// Função para ler o Automato
void LeituraReticulado(Automato *tab);

// Função para evoluir o estado do Automato para a geração N de acordo com as regras do Jogo da Vida
Automato *evoluirReticulado(Automato *tab, int n, int geracoes);

// Função para imprimir o estado do Automato na tela
void imprimeReticulado(Automato *tab);
