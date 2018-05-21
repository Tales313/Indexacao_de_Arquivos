#include <stdlib.h>
#include <stdio.h>
#include "hashing.h"

void inicializar(hashTable *h)
{
    int i;
    h->qtd = 0;
    for(i=0; i<TAM; i++)
        h->vetor[i] = NULL;
}

void zerarTabela(hashTable *h)
{
    int i;
    h->qtd = 0;
    for(i=0; i<TAM; i++){
        free(h->vetor[i]);
        h->vetor[i] = NULL;
    }
}

int hash(hashTable h, int key)
{
    int i, colisao = 0;
    int pos = key%TAM;
    for(i=1; h.vetor[pos] != NULL; i++){
        colisao = 1;
        pos = (key+i) % TAM;
    }
    if(colisao){
        i--;
        return (key+i) % TAM;
    }
    return pos;
}

int addOnIndex(hashTable *h, int key, long int byte)
{
    int index;
    if(qtdOcupada(*h) == TAM || buscaChave(*h, key, &index) != -1)
        return 0;
    int cols;
    int pos = hash(*h, key);
    controle *novo = (controle *) malloc(sizeof(controle));
    if(novo == NULL)
        return 0;
    novo->key = key;
    novo->endereco = byte;
    h->vetor[pos] = novo;
    (h->qtd)++;
    return 1;
}

int removeFromIndex(hashTable *h, int pos)
{
    int i, cols;
    if(vazia(*h))
        return 0;
    free(h->vetor[pos]);
    h->vetor[pos] = NULL;
    (h->qtd)--;
    return 1;
}


long int buscaChave(hashTable h, int key, int *index)
{
    int achou = 0, i = 1;
    int pos = key%TAM;
    if(h.vetor[pos] != NULL)
        if(h.vetor[pos]->key == key){
            *index = pos;
            return h.vetor[pos]->endereco;     ///Se achar a chave na tabela, retorna o byte em que
        }                                      ///a estrutura está no arquivo, senão retorna -1.

    while(h.vetor[pos] != NULL){
        if(h.vetor[pos]->key != key)
            pos = (key+i) % TAM;
        else
            achou = 1;
        if(achou){
            *index = pos;
            return h.vetor[pos]->endereco;
        }
        i++;
    }
    return -1;
}

long int *criaVetorMenor(hashTable h, int ordem)
{
    int i, j=0;
    controle *v = (controle *) malloc(qtdOcupada(h)*sizeof(controle));
    long int *v2 = (long int *) malloc(qtdOcupada(h)*sizeof(long int));
    if(v == NULL || v2 == NULL)
        return NULL;                 ///Essa função pega a tabela hash, cria uma outra tabela menor
    for(i=0; i<TAM; i++)             ///ordenada ou não pelo ISSN, e depois cria outro vetor apenas
        if(h.vetor[i] != NULL)       ///com os bytes correspondentes e retorna ele.
            v[j++] = *(h.vetor[i]);
    if(ordem)
        quickSort(v, 0, qtdOcupada(h)-1);
    for(i=0; i<qtdOcupada(h); i++)
        v2[i] = v[i].endereco;
    free(v);
    return v2;
}

int qtdOcupada(hashTable h)
{
    return h.qtd;
}

int vazia(hashTable h)
{
    if(h.qtd == 0)
        return 1;
    return 0;
}

int cheia(hashTable h)
{
    if(h.qtd == TAM)
        return 1;
    return 0;
}

void quickSort(controle *V, int inicio, int fim)
{
    int pivo;
    if(fim > inicio){
        pivo = particiona(V, inicio, fim);
        quickSort(V, inicio, pivo-1);
        quickSort(V, pivo+1, fim);
    }
}

int particiona(controle *V, int inicio, int final)
{
    int esq, dir;
    controle aux, pivo;
    esq = inicio;
    dir = final;
    pivo = V[inicio];
    while(esq < dir){
        while(V[esq].key <= pivo.key)
            esq++;
        while(V[dir].key > pivo.key)
            dir--;
        if(esq < dir){
            aux = V[esq];
            V[esq] = V[dir];
            V[dir] = aux;
        }
    }
    V[inicio] = V[dir];
    V[dir] = pivo;
    return dir;
}
