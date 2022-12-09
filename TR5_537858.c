/**
 * @file TR5_537858.c
* @author Éverton Da Cunha Sousa | 537858 (evertoncc22@alu.ufc.br)
 * @brief Emplementar funcões (criar, adicionar e remover) base de um heap | Quinto Trabalho de Laboratório de Programação 
 * @version 0.1
 * @date 2022-10-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "heap.h"

HEAP* HEAP_create(int n, COMP* compara) {
    HEAP* heap = malloc(sizeof(HEAP));
    heap->elems = malloc(n * sizeof(void*));
    heap->N = n;
    heap->P = 0;
    heap->comparador = compara;

    return heap;
}

void HEAP_organiza(HEAP* heap, int pos) {
    while (heap->comparador(heap->elems[pos], heap->elems[(pos - 1) / 2]) < 0) {
        void* aux = heap->elems[pos];
        heap->elems[pos] = heap->elems[(pos - 1) / 2];
        heap->elems[(pos - 1) / 2] = aux;    
        pos = (pos - 1) / 2;
    }    
}

void HEAP_add(HEAP* heap, void* newelem) {
  if (heap->P < heap->N) {
    heap->elems[heap->P] = newelem;

    int pos = heap->P;

    HEAP_organiza(heap, pos);

    heap->P++;
  }
}

void* HEAP_remove(HEAP* heap) {
    if (heap->P > 0) {
        void* min = heap->elems[heap->P / 2];
        int pos = heap->P / 2;

        for (int i = heap->P / 2 + 1; i < heap->P; i++) {
            if (heap->comparador(heap->elems[i], min) > 0) {
                min = heap->elems[i];
                pos = i;
            }
        }

        void* aux = heap->elems[heap->P - 1];
        heap->elems[heap->P] = heap->elems[pos];
        heap->elems[pos] = aux;

        HEAP_organiza(heap, pos);
        
        heap->P--;

        return min;
    }
}