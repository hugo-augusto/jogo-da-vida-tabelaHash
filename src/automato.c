#include <stdio.h>
#include <stdlib.h>
#include "automato.h"

// aloca o automato com a Tabela Hash
Automato *alocarReticulado(int n)
{
    Automato *tab = (Automato *)malloc(sizeof(Automato));
    if (tab == NULL)
    {
        printf("Erro de memoria\n");
        return NULL;
    }

    tab->n = n;
    tab->tabela = inicializarHash(n * n); // Inicializa a Tabela Hash com tamanho adequado

    if (tab->tabela == NULL)
    {
        printf("Erro de memoria ao inicializar a tabela hash\n");
        free(tab);
        return NULL;
    }

    return tab;
}

// Desaloca o Automato e a Tabela Hash
void desalocarReticulado(Automato **tab)
{
    if (tab == NULL || *tab == NULL || (*tab)->tabela == NULL)
    {
        return;
    }

    desalocarHash(&((*tab)->tabela)); // Desaloca a Tabela Hash
    free(*tab);
    *tab = NULL;
}

// Lê o estado inicial do Automato e insere na Tabela Hash
void LeituraReticulado(Automato *tab)
{
    int valor;
    for (int i = 0; i < tab->n; i++)
    {
        for (int j = 0; j < tab->n; j++)
        {
            scanf("%d", &valor);
            if (valor == 1)
            { // Se a célula está viva, insere na Tabela Hash
                inserirHash(tab->tabela, i * tab->n + j, 1);
            }
        }
    }
}

// Evolui o Automato de acordo com as regras do Jogo da Vida
Automato *evoluirReticulado(Automato *tab, int n, int geracoes)
{
    if (geracoes == 0)
    {
        return tab;
    }

    Automato *novoAutomato = alocarReticulado(n);
    if (novoAutomato == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int key = i * n + j;
            int vizinhosVivos = 0;

            // Contagem de vizinhos vivos
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    if (di == 0 && dj == 0)
                        continue;

                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < n && nj >= 0 && nj < n)
                    {
                        int vizinhoKey = ni * n + nj;
                        if (buscarHash(tab->tabela, vizinhoKey) == 1)
                        {
                            vizinhosVivos++;
                        }
                    }
                }
            }

            int cellState = buscarHash(tab->tabela, key);
            if (cellState == 1)
            { // Se a célula está viva
                if (vizinhosVivos == 2 || vizinhosVivos == 3)
                {
                    inserirHash(novoAutomato->tabela, key, 1); // Permanece viva
                }
            }
            else
            { // Se a célula está morta
                if (vizinhosVivos == 3)
                {
                    inserirHash(novoAutomato->tabela, key, 1); // Torna-se viva
                }
            }
        }
    }

    desalocarReticulado(&tab); // Desaloca o automato anterior
    
    return evoluirReticulado(novoAutomato, n, geracoes - 1);
}

// Imprime o estado atual do Automato na tela
void imprimeReticulado(Automato *tab)
{
    printf("\n");

    for (int i = 0; i < tab->n; i++)
    {
        for (int j = 0; j < tab->n; j++)
        {
            int key = i * tab->n + j;
            int valor = buscarHash(tab->tabela, key);
            if (valor == -1)
            {
                printf("0 "); // Se não encontrado na tabela, está morto
            }
            else
            {
                printf("%d ", valor); // Imprime 1 se está vivo
            }
        }
        printf("\n");
    }
}
