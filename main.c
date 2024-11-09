#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void **elementos;
    int frente;
    int final;
    int quantidade;
    int capacidadeMax;
} FilaCircular;

FilaCircular* inicializarFila(int capacidadeInicial) {
    FilaCircular *fila = (FilaCircular *) malloc(sizeof(FilaCircular));
    if (!fila) return NULL;

    fila->elementos = (void **) malloc(sizeof(void*) * capacidadeInicial);
    fila->frente = 0;
    fila->final = -1;
    fila->quantidade = 0;
    fila->capacidadeMax = capacidadeInicial;

    return fila;
}

void liberarFila(FilaCircular *fila) {
    if (fila) {
        free(fila->elementos);
        free(fila);
    }
}

void expandirCapacidade(FilaCircular *fila) {
    int novaCapacidade = fila->capacidadeMax * 2;
    void **novosElementos = (void **) malloc(sizeof(void*) * novaCapacidade);

    for (int i = 0; i < fila->quantidade; i++) {
        novosElementos[i] = fila->elementos[(fila->frente + i) % fila->capacidadeMax];
    }

    free(fila->elementos);
    fila->elementos = novosElementos;
    fila->frente = 0;
    fila->final = fila->quantidade - 1;
    fila->capacidadeMax = novaCapacidade;
}

void adicionarNaFila(FilaCircular *fila, void *item) {
    if (fila->quantidade == fila->capacidadeMax) {
        expandirCapacidade(fila);
    }
    fila->final = (fila->final + 1) % fila->capacidadeMax;
    fila->elementos[fila->final] = item;
    fila->quantidade++;
}

void* retirarDaFila(FilaCircular *fila) {
    if (fila->quantidade == 0) return NULL;
    void *item = fila->elementos[fila->frente];
    fila->frente = (fila->frente + 1) % fila->capacidadeMax;
    fila->quantidade--;
    return item;
}

int main() {
    FilaCircular *fila = inicializarFila(2);

    int a = 1, b = 2, c = 3, d = 4;
    adicionarNaFila(fila, &a);
    adicionarNaFila(fila, &b);
    adicionarNaFila(fila, &c);
    adicionarNaFila(fila, &d);

    int *item;
    while ((item = (int *) retirarDaFila(fila)) != NULL) {
        printf("Elemento removido: %d\n", *item);
    }

    liberarFila(fila);
    return 0;
}
