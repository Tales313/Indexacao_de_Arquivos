#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "hashing.h"
#include "qualis.h"
#include "myLibrary.h"

int testaArquivo(hashTable *h)
{
    FILE *f;
    f = fopen("arquivo.bin", "rb");
    if(f == NULL){
        f = fopen("arquivo.bin", "wb");
        if(f == NULL){
            puts("Falha na leitura/criacao do arquivo.");
            return 0;
        }else{
            fclose(f);
            inicializar(h);
            return 1;
        }
    }else{             ///Se conseguiu ler o arquivo, crie a tabela a partir dele.
        fclose(f);
        inicializar(h);
        criarTabela(h);
        return 1;
    }
}

void menuChoice(char *opcao)
{
    puts("Escolha uma opcao:\n");
    printf("(i) Importar arquivo CSV\n"
           "(p) Exportar tabela de indice\n"
           "(a) Adicionar manualmente um periodico\n"
           "(c) Consultar um periodico\n"
           "(x) Excluir periodico\n"
           "(e) Eliminar todos os periodicos\n"
           "(l) Listar dados\n"
           "(u) Otimizar Arquivo\n"
           "(z) Fechar Programa\n\n"
           "Opcao: ");
    *opcao = getche();
    puts("\n");
}

void importarArquivoCSV(hashTable *h)
{
    char opcao, str[201], c_issn[9], *titulo, *estrato;
    int i, falhas = 0, sucessos = 0, titul_grand = 0;
    long int byte;
    periodico p;
    FILE *csv, *bin;
    puts("Tem certeza de que quer importar o arquivo csv?\n"
         "[s] SIM\n"
         "[n] NAO");
    opcao = getche();
    while(opcao != 's' && opcao != 'n'){
        puts("Opcao invalida, tecle 's' ou 'n': ");
        opcao = getche();
    }
    if(opcao == 's'){
        csv = fopen("arquivo.csv", "rt");
        if(csv == NULL){
            puts("Falha na leitura do CSV.\n");
            return;
        }
        bin = fopen("arquivo.bin", "wb");
        if(bin == NULL){
            puts("Falha na importacao.\n");
            return;
        }
        zerarTabela(h);
        rewind(csv); ///Va para o inicio do arquivo csv
        fgets(str, 200, csv); ///Pule a primeira linha
        fseek(bin, 0L, SEEK_END); ///Va para o final do arquivo binario
        while(1){
            fgets(str, 200, csv); ///Lê uma linha
            if(feof(csv)) ///Se chegou no fim do arquivo, sai do laço.
                break;
            for(i=0; i<4; i++) ///Pega os primeiros 4 digitos
                c_issn[i] = str[i];
            for(i=5; i<9; i++) ///Pega os 4 digitos após o hifen.
                c_issn[i-1] = str[i];
            c_issn[8] = '\0';
            p.issn = atoi(c_issn); ///Pega o ISSN inteiro aqui.
            strtok(str, ";");
            titulo = strtok(NULL, ";"); ///Pega o titulo aqui.
            if(strlen(titulo) < 51){ ///Se o titulo tem o tamanho "certo"
                strcpy(p.titulo, titulo);
                estrato = strtok(NULL, ";");///Pega o estrato aqui
                if(estrato[0] == 'C')
                    estrato[1] = '\0';
                else
                    estrato[2] = '\0';
                strcpy(p.estrato, estrato);
                    if(addOnFile(p, &byte))
                        if(addOnIndex(h, p.issn, byte))
                            sucessos++;
                        else{
                            removeFromFile(byte);
                            falhas++;
                        }
            }else
                titul_grand++;
        }
        fclose(csv);
        fclose(bin);
        printf("Qualis importados com sucesso: %i\n", sucessos);
        printf("Falhas na importacao: %i\n", falhas);
        printf("Qualis nao importados por titulo muito grande: %i\n\n", titul_grand);
    }else
        puts("Importacao Cancelada.\n");
}

void exportarTabela(hashTable h)
{
    int i;
    periodico p;
    char opcao;
    FILE *bin, *csv;
    puts("Tem certeza de que quer exportar a tabela atual?\n"
         "[s] SIM\n"
         "[n] NAO");
    opcao = getche();
    while(opcao != 's' && opcao != 'n'){
        puts("Opcao invalida, tecle 's' ou 'n': ");
        opcao = getche();
    }
    if(opcao == 's'){
        csv = fopen("saida.csv", "wt");
        if(csv == NULL){
            puts("Falha na exportacao.\n");
            return;
        }
        bin = fopen("arquivo.bin", "rb");
        if(bin == NULL){
            puts("Falha na exportacao.\n");
            return;
        }
        fprintf(csv, "ISSN;Titulo;Estrato\n");
        long int *v = criaVetorMenor(h, 0);
        if(v == NULL){
            puts("Falha na exportacao.\n");
            return;
        }
        for(i=0; i<qtdOcupada(h); i++){
            fseek(bin, v[i], SEEK_SET);
            fread(&p, sizeof(periodico), 1, bin);
            fprintf(csv, "%i;%s;%s\n", p.issn, p.titulo, p.estrato);
        }
        fclose(csv);
        fclose(bin);
        puts("\nExportacao Concluida.\n");
    }else
        puts("\nExportacao Cancelada.");
}

void addPeriManual(hashTable *h)
{
    periodico p;
    int index;
    long int byte;
    printf("Digite o issn: ");
    scanf("%i", &p.issn);
    fflush(stdin);
    byte = buscaChave(*h, p.issn, &index);
    if(byte != -1){///Se a chave já existe na tabela...
        puts("Essa chave ja existe na tabela.\n");
        return;
    }
    printf("Digite o titulo: ");
    scanf("%50[^\n]s", p.titulo);
    fflush(stdin);
    printf("Digite o estrato: ");
    scanf("%2[^\n]s", p.estrato);
    fflush(stdin);
    if(addOnFile(p, &byte)){
        if(addOnIndex(h, p.issn, byte))
            printf("Periodico Adicionado com Sucesso!\n");
        else{
            removeFromFile(byte);
            printf("Erro na adicao do periodico.\n");
            return;
        }
    }else
        printf("Erro na adicao do periodico.\n");
}

void excluirPeriodico(hashTable *h)
{
    if(vazia(*h)){
        puts("Nao existem periodicos no registro.\n");
        return;
    }
    periodico p;
    int pos;
    printf("Digite o issn do periodico que voce quer excluir: ");
    scanf("%i", &p.issn);
    fflush(stdin);
    long int byte = buscaChave(*h, p.issn, &pos);
    if(byte != -1){ ///Se a chave existe na tabela...
        if(removeFromFile(byte))
            if(removeFromIndex(h, pos))
                puts("Periodico excluido com sucesso!\n");
        else
            puts("Erro na exclusao do registro.\n");
    }else
        printf("A chave %i nao existe no registro.\n", p.issn);
}

void excluirTdsPeriodicos(hashTable *h)
{
    FILE *f;
    char opcao;
    if(vazia(*h)){
        puts("Nao existem registros.");
        return;
    }
    puts("Tem certeza de que quer excluir todos os periodicos?\n"
         "[s] SIM\n"
         "[n] NAO");
    opcao = getche();
    while(opcao != 's' && opcao != 'n'){
        puts("Opcao invalida, tecle 's' ou 'n': ");
        opcao = getche();
    }
    if(opcao == 's'){
        f = fopen("arquivo.bin", "wb"); ///Cria um arquivo vazio por cima do existente.
        if(f == NULL){
            puts("Falha na exclusao dos arquivos.\n");
            return;
        }
        fclose(f);
        zerarTabela(h);
        puts("\nTodos os periodicos foram excluidos.\n");
        return;
    }else
        puts("\nOperacao cancelada.");
}

void listarDados(hashTable h)
{
    int i, priPorVez, pausaPrint = 0;
    char proxPrint;
    periodico p;
    long int *v;
    if(vazia(h)){
        puts("Nao existem registros.");
        return;
    }
    v = criaVetorMenor(h, 1); ///Pega os bytes onde estão os periodicos, para usar
    if(v == NULL){            ///no for() ali em baixo.
        puts("Falha na listagem dos dados.");
        return;
    }
    FILE *f = fopen("arquivo.bin", "rb");
    if(f == NULL){
        puts("Falha na leitura do arquivo.");
        return;
    }
    puts("Voce quer listar quantos de cada vez? ");
    scanf("%i", &priPorVez);
    for(i=0; i<qtdOcupada(h); i++){
        if(pausaPrint >= priPorVez){
            printf("Printando %i de cada vez.\n"
                 "Pressione ENTER para continuar ou 'z' se quiser sair da listagem.\n\n", priPorVez);
            proxPrint = getche();
            printf("\b");
            if(proxPrint == 'z')
                break;
            pausaPrint = 0;
        }
        fseek(f, v[i], SEEK_SET);
        fread(&p, sizeof(periodico), 1, f);
        printf("ISSN: %i\n", p.issn);
        printf("Titulo: %s\n", p.titulo);
        printf("Estrato: %s\n\n================\n\n", p.estrato);
        pausaPrint++;
    }
    printf("Quantidade total de registros: %i\n\n", qtdOcupada(h));
    free(v);
    fclose(f);
}

void consultarPeriodico(hashTable h)
{
    periodico p;
    if(vazia(h)){
        puts("Nao existem registros.");
        return;
    }
    printf("Digite a chave do periodico que voce quer consultar: ");
    scanf("%i", &p.issn);
    fflush(stdin);
    if(p.issn < 1){
        puts("Issn invalido.\n");
        return;
    }
    int pos;
    long int byte = buscaChave(h, p.issn, &pos);
    if(byte != -1){ ///Se a chave existe na tabela...
        FILE *f = fopen("arquivo.bin", "rb");
        if(f == NULL){
            printf("Falha na leitura do arquivo.\n");
            return;
        }
        fseek(f, byte, SEEK_SET); ///Vá para a posicao onde se encontra o qualis.
        fread(&p, sizeof(periodico), 1, f); ///Atribua esse qualis a variavel p.
        printf("ISSN: %i\n", p.issn);
        printf("Titulo: %s\n", p.titulo);
        printf("Estrato: %s\n", p.estrato);
        printf("Posicao na tabela: %i\n", pos);
        fclose(f);
    }else
        printf("A chave %i nao existe no registro.\n", p.issn);
}

void otimizarArquivo(hashTable h, char o)
{
    int i;
    periodico p;
    FILE *f1 = fopen("arquivo.bin", "rb");
    FILE *f2 = fopen("arquivo2.bin", "wb");
    long int *v = criaVetorMenor(h, 0);
    if(f1 == NULL || f2 == NULL || v == NULL){
        puts("Falha na atualizacao do arquivo.\n");
        return;
    }
    for(i=0; i<qtdOcupada(h); i++){          ///Em uma iteração do for(), o programa lê um periodico
        fseek(f1, v[i], SEEK_SET);           ///do arquivo velho e adiciona no arquivo novo.
        fread(&p, sizeof(periodico), 1, f1);
        fseek(f2, 0L, SEEK_END);
        fwrite(&p, sizeof(periodico), 1, f2);
    }
    fclose(f1);
    fclose(f2);
    free(v);
    remove("arquivo.bin");                   ///Remove o arquivo velho e faz o novo
    rename("arquivo2.bin", "arquivo.bin");   ///ter o mesmo nome.
    if(o == 'u')
        puts("Arquivo otimizado com sucesso.\n");
}


/*FUNCOES DOS CASES
*****************************************************************************
FUNCOES USADAS PELAS FUNCOES DOS CASES */



void criarTabela(hashTable *h)
{
    periodico p;
    long int byte;
    FILE *f = fopen("arquivo.bin", "rb");
    rewind(f);
    while(fread(&p, sizeof(periodico), 1, f) == 1){
        byte = ftell(f) - sizeof(periodico);         ///Em uma iteração do while, o programa lê uma váriavel
        addOnIndex(h, p.issn, byte);                 ///do arquivo e adiciona o indice na tabela hash.
    }
    fclose(f);
}

int addOnFile(periodico p, long int *byte)
{
    FILE *f;
    if((f = fopen("arquivo.bin", "rb+")) == NULL)
        if((f = fopen("arquivo.bin", "wb+")) == NULL)
            return 0;
    fseek(f, 0L, SEEK_END);
    if((fwrite(&p, sizeof(periodico), 1, f)) != 1){ ///Se o fwrite falhar...
        fclose(f);
        return 0;
    }
    fseek(f, -sizeof(periodico), SEEK_END);
    *byte = ftell(f);
    fclose(f);
    return 1;
}

int removeFromFile(long int byte)
{
    FILE *f;
    periodico p;
    if((f = fopen("arquivo.bin", "rb+")) == NULL)
        return 0;
    p.issn = -1;
    p.titulo[0] = '\0';
    p.estrato[0] = '\0';
    fseek(f, byte, SEEK_SET); ///va para onde está a estrutura a ser "removida"
    if((fwrite(&p, sizeof(periodico), 1, f)) != 1){
        fclose(f);
        return 0;
    }
    fclose(f);
    return 1;
}
