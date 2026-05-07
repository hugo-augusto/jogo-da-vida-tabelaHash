# 🧬 Jogo da Vida — TP3 | Estruturas de Dados I

Simulador do **Jogo da Vida de Conway** implementado em C, utilizando **Tabela Hash com Endereçamento Duplo** para representação do reticulado celular.

> Trabalho Prático III — Estruturas de Dados I  
> Professor: Pedro Henrique Lopes Silva

---

## 📋 Descrição

O [Jogo da Vida](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life), proposto por John Conway em 1970, é um autômato celular que evolui em um reticulado bidimensional. Cada célula pode estar **viva** (`1`) ou **morta** (`0`), e seu estado na próxima geração é determinado pelas seguintes regras:

| Situação | Resultado |
|---|---|
| Célula viva com 2 ou 3 vizinhos vivos | Permanece viva |
| Célula viva com menos de 2 vizinhos vivos | Morre (solidão) |
| Célula viva com mais de 3 vizinhos vivos | Morre (superpopulação) |
| Célula morta com exatamente 3 vizinhos vivos | Nasce (reprodução) |

O reticulado é armazenado em uma **Tabela Hash com Hashing Duplo**, substituindo o uso de matriz convencional.

---

## 🗂️ Estrutura do Projeto

```
.
├── tp.c            # Ponto de entrada (main)
├── automato.h      # Interface do TAD AutomatoCelular
├── automato.c      # Implementação do TAD AutomatoCelular
├── double_hash.h   # Interface da Tabela Hash
├── double_hash.c   # Implementação da Tabela Hash com Hashing Duplo
└── README.md
```

---

## ⚙️ Compilação

Usando as diretivas exigidas pelo enunciado:

```bash
gcc -c double_hash.c -Wall
gcc -c automato.c -Wall
gcc -c tp.c -Wall
gcc double_hash.o automato.o tp.o -o exe
```

Ou de forma simplificada:

```bash
gcc -g -o exe *.c -Wall
```

---

## ▶️ Execução

```bash
./exe < arquivo_de_teste.in
```

---

## 📥 Formato de Entrada

A primeira linha contém dois inteiros: a **dimensão N** do reticulado (N×N) e o **número de gerações** a evoluir. Em seguida, uma matriz N×N de valores binários representa o estado inicial das células.

```
5 5
0 0 0 0 0
0 0 0 0 0
0 1 1 1 0
0 0 1 0 0
0 0 0 0 0
```

## 📤 Formato de Saída

Uma matriz N×N com o estado das células após as gerações solicitadas (zeros também são impressos).

```
0 0 1 0 0
0 1 0 1 0
1 0 0 0 1
0 1 0 1 0
0 0 1 0 0
```

---

## 🔍 Verificação de Memória

Para verificar vazamentos de memória com Valgrind:

```bash
valgrind --leak-check=full -s ./exe < arquivo_de_teste.in
```

Saída esperada:
```
== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

---

## 🏗️ Detalhes de Implementação

### Tabela Hash com Hashing Duplo

- **hash1(key)** = `(key * 1 + 2) % size`
- **hash2(key)** = `(key * 3 + 4) % (size - 1) + 1`

Colisões são resolvidas pelo deslocamento: `index = (index + step) % size`

### TAD AutomatoCelular

| Função | Descrição | Complexidade |
|---|---|---|
| `alocarReticulado(n)` | Aloca o autômato e inicializa a hash | O(n²) |
| `desalocarReticulado(tab)` | Libera toda a memória alocada | O(1) |
| `LeituraReticulado(tab)` | Lê o estado inicial da entrada padrão | O(n²) |
| `evoluirReticulado(tab, n, g)` | Evolui o autômato por `g` gerações (recursivo) | O(n² · g) |
| `imprimeReticulado(tab)` | Imprime o estado atual do reticulado | O(n²) |

---

## 👥 Autores

- Fábio Tavares Pinto
- Hugo Augusto Silva de Faria
