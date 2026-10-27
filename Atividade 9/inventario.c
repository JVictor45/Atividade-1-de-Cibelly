#include <stdlib.h>
#include "inventario.h"

// A estrutura fica escondida neste arquivo (TAD opaco).
struct inventario {
    Entidade **vetor;
    int total;
    int capacidade;
};

Inventario *inventarioCriar(int capacidade) {
    if (capacidade <= 0) return NULL;

    Inventario *inv = (Inventario *)malloc(sizeof(Inventario));
    if (inv == NULL) return NULL;

    inv->vetor = (Entidade **)malloc(capacidade * sizeof(Entidade *));
    if (inv->vetor == NULL) {
        free(inv);
        return NULL;
    }

    inv->total = 0;
    inv->capacidade = capacidade;
    return inv;
}

void inventarioDestruir(Inventario *inv) {
    if (inv == NULL) return;

    for (int i = 0; i < inv->total; i++) {
        free(inv->vetor[i]);
    }
    free(inv->vetor);
    free(inv);
}

bool inventarioAdicionar(Inventario *inv, Entidade *e) {
    if (inv == NULL || e == NULL || inv->total >= inv->capacidade) return false;

    inv->vetor[inv->total] = e;
    inv->total++;
    return true;
}

void inventarioRemover(Inventario *inv, int indice) {
    if (inv == NULL || indice < 0 || indice >= inv->total) return;

    free(inv->vetor[indice]);
    inv->vetor[indice] = inv->vetor[inv->total - 1];
    inv->total--;
}

Entidade *inventarioObter(Inventario *inv, int indice) {
    if (inv == NULL || indice < 0 || indice >= inv->total) return NULL;
    return inv->vetor[indice];
}

int inventarioTotal(Inventario *inv) {
    if (inv == NULL) return 0;
    return inv->total;
}

bool inventarioEstaCheio(Inventario *inv) {
    if (inv == NULL) return false;
    return inv->total >= inv->capacidade;
}

int inventarioContarPorTipo(Inventario *inv, TipoEntidade tipo) {
    if (inv == NULL) return 0;

    int quantidade = 0;
    for (int i = 0; i < inv->total; i++) {
        if (inv->vetor[i]->tipo == tipo) {
            quantidade++;
        }
    }
    return quantidade;
}
