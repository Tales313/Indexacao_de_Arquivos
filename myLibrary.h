///Biblioteca com as funções chamadas no main.

int testaArquivo(hashTable *h);
///Função usada na inicialização do programa. Pega o arquivo binário
///já existente e cria a tabela hash a partir dele. Se não existe um
///arquivo binário, a função cria.

void menuChoice(char *opcao);
///Apenas o printf e getche do menu.

void importarArquivoCSV(hashTable *h);
///Função para importar um arquivo CSV e criar
///o binario e o indice a partir dele.

void exportarTabela(hashTable h);
///Função para exportar os qualis da tabela
///num arquivo csv de saida.

void addPeriManual(hashTable *h);
///Função para adicionar manualmente um periodico.

void excluirPeriodico(hashTable *h);
///Função para excluir manualmente um periodico a partir da chave.

void excluirTdsPeriodicos(hashTable *h);
///Função para excluir todos os registros da tabela e do arquivo.

void listarDados(hashTable h);
///Lista todos os periodicos em ordem crescente do ISSN.

void consultarPeriodico(hashTable h);
///Consultar as informações de um periodico a partir do ISSN.

void otimizarArquivo(hashTable h, char opcao);
///Função para criar um arquivo novo, a partir
///da tabela hash atual.

/*FUNCOES DOS CASES
*****************************************************************************
FUNCOES USADAS PELAS FUNCOES DOS CASES */

void criarTabela(hashTable *h);
///Função usada em testaArquivo() para criar uma tabela
///a partir do arquivo binario ja existente.

int addOnFile(periodico p, long int *byte);
///Função usada em addPeriManual() para de fato
///escrever no arquivo binario. Retorna o byte onde
///foi escrito pelo parametro *byte.

int removeFromFile(long int byte);
///Essa função não é necessária no programa, mas eu resolvi
///deixar ela aí. Ela apenas coloca um -1 no ISSN do periodico
///removido pelo usuario, e coloca um '\0' no titulo e estrato.
