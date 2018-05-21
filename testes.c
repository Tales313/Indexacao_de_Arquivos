#include <stdio.h>
#include <conio.h>
#include "hashing.h"
#include "testes.h"
#include "qualis.h"

void printarVetor(hashTable h) ///printar o vetor da tabela hash
{
    if(vazia(h)){
        puts("Vetor vazio.\n");
        return;
    }
    int i, issn, priPorVez, pausaPrint = 0;
    char proxPrint;
    long int byte;

    puts("Voce quer listar quantos de cada vez? ");
    scanf("%i", &priPorVez);
    for(i=0; i<TAM; i++)
        if(h.vetor[i] != NULL){
            if(pausaPrint >= priPorVez){
                printf("Printando %i de cada vez.\n"
                 "Pressione ENTER para continuar ou 'z' se quiser sair da listagem.\n\n", priPorVez);
                proxPrint = getche();
                printf("\b");
                if(proxPrint == 'z')
                    break;
                pausaPrint = 0;
            }
            issn = h.vetor[i]->key;
            byte = h.vetor[i]->endereco;
            printf("[indice: %i] [byte: %i] ISSN: %i\n", i, byte, issn);
            pausaPrint++;
        }
    printf("==============\nQuantidade total de registros: %i\n\n", qtdOcupada(h));
}

void printarOPrimeiro(hashTable h) ///printar a primeira estrutura do arquivo
{
    if(vazia(h)){
        puts("Arquivo vazio.\n");
        return;
    }
    periodico p;
    FILE *f = fopen("arquivo.bin", "rb");
    rewind(f);
    fread(&p, sizeof(periodico), 1, f);
    printf("ISSN: %i\n", p.issn);
    printf("Titulo: %s\n", p.titulo);
    printf("Estrato: %s\n", p.estrato);
    fclose(f);
}

void printaVetorMenor(hashTable h){
    long int *v = criaVetorMenor(h, 0);
    int i;

    for(i=0; i<qtdOcupada(h); i++)
        printf("b: %i\n", v[i]);
}
