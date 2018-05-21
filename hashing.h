#include <stdlib.h>
#define TAM 10007

typedef struct {
    int key;
    long int endereco;
}controle;

typedef struct {
    controle *vetor[TAM];
    int qtd;
}hashTable;

void inicializar(hashTable *h);
///Inicializa a tabela hash com quantidade = 0
///e com todos os ponteiros nulos.

void zerarTabela(hashTable *h);
///O mesmo da função acima, mas para tabelas
///já criadas e usadas.

int hash(hashTable h, int key);

int addOnIndex(hashTable *h, int key, long int byte);
///Adiciona um registro na tabela.

int removeFromIndex(hashTable *h, int pos);
///Remove um registro da tabela.

long int buscaChave(hashTable h, int key, int *index);
///Procura por uma chave específica na tabela, retorna
///o byte dela no arquivo e diz o índice dela pelo *index.

long int *criaVetorMenor(hashTable h, int ordem);
///Pega todos os registros na tabela hash, cria um vetor
///de tamanho qtdOcupada(h) apenas com os bytes dos registros.
///Se o parametro int ordem for != 0, esse vetor vem ordenado pelas chaves.

int qtdOcupada(hashTable h);
///Retorna a quantidade de posicoes ocupadas na tabela.

int vazia(hashTable h);
///Testa se a tabela está vazia.

int cheia(hashTable h);
///Testa se a tabela está cheia.

void quickSort(controle *V, int inicio, int fim);
int particiona(controle *V, int inicio, int final);
///Função quickSort para ordenar o vetor pelas chaves
///na função criaVetorMenor().
