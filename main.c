#include "hashing.h"
#include "qualis.h"
#include "myLibrary.h"
#include <stdio.h>

int main()
{
    char opcao;
    hashTable h;

    if(!testaArquivo(&h)) ///Tenta ler ou criar o arquivo binario, se falhar retorna 0.
        return 0;

    for(;;){
        menuChoice(&opcao); ///Printf e getche com as opcoes do menu.
        switch(opcao){
        case 'i':
            importarArquivoCSV(&h);
            break;
        case 'p':
            exportarTabela(h);
            break;
        case 'a':
            addPeriManual(&h); ///Adicionar um periodico manualmente.
            break;
        case 'c':
            consultarPeriodico(h);
            break;
        case 'x':
            excluirPeriodico(&h);
            break;
        case 'e':
            excluirTdsPeriodicos(&h);
            break;
        case 'l':
            listarDados(h); ///Listar todos os periodicos pela ordem do ISSN
            break;
        case 'u':
            otimizarArquivo(h, opcao); ///Atualiza o arquivo binario de acordo com a tabela em memoria
            break;
        case 'z':
            otimizarArquivo(h, opcao);
            puts("Fechando...");
            return 0;
        default:
            puts("Opcao Invalida!\n");
        }
        system("pause");
        system("cls");
    }
}
