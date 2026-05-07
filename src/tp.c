#include <stdio.h>
#include <stdlib.h>
#include "automato.h"

int main()
{
    int n, geracoes;

    // Lê a dimensão do automato e o número de gerações.
    scanf("%d %d", &n, &geracoes);

    // Inicializa o autômato
    Automato *automato = alocarReticulado(n);

    // Lê o estado inicial do reticulado.
    LeituraReticulado(automato);

    // Evolui o autômato para o número especificado de gerações.
    automato = evoluirReticulado(automato, n, geracoes);

    // Imprime o estado do reticulado após as gerações.
    imprimeReticulado(automato);

    // Desaloca a memória usada pelo autômato.
    desalocarReticulado(&automato);

    return 0;
}
