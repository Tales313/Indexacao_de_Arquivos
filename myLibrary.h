///Biblioteca com as fun��es chamadas no main.

int testaArquivo(hashTable *h);
///Fun��o usada na inicializa��o do programa. Pega o arquivo bin�rio
///j� existente e cria a tabela hash a partir dele. Se n�o existe um
///arquivo bin�rio, a fun��o cria.

void menuChoice(char *opcao);
///Apenas o printf e getche do menu.

void importarArquivoCSV(hashTable *h);
///Fun��o para importar um arquivo CSV e criar
///o binario e o indice a partir dele.

void exportarTabela(hashTable h);
///Fun��o para exportar os qualis da tabela
///num arquivo csv de saida.

void addPeriManual(hashTable *h);
///Fun��o para adicionar manualmente um periodico.

void excluirPeriodico(hashTable *h);
///Fun��o para excluir manualmente um periodico a partir da chave.

void excluirTdsPeriodicos(hashTable *h);
///Fun��o para excluir todos os registros da tabela e do arquivo.

void listarDados(hashTable h);
///Lista todos os periodicos em ordem crescente do ISSN.

void consultarPeriodico(hashTable h);
///Consultar as informa��es de um periodico a partir do ISSN.

void otimizarArquivo(hashTable h, char opcao);
///Fun��o para criar um arquivo novo, a partir
///da tabela hash atual.

/*FUNCOES DOS CASES
*****************************************************************************
FUNCOES USADAS PELAS FUNCOES DOS CASES */

void criarTabela(hashTable *h);
///Fun��o usada em testaArquivo() para criar uma tabela
///a partir do arquivo binario ja existente.

int addOnFile(periodico p, long int *byte);
///Fun��o usada em addPeriManual() para de fato
///escrever no arquivo binario. Retorna o byte onde
///foi escrito pelo parametro *byte.

int removeFromFile(long int byte);
///Essa fun��o n�o � necess�ria no programa, mas eu resolvi
///deixar ela a�. Ela apenas coloca um -1 no ISSN do periodico
///removido pelo usuario, e coloca um '\0' no titulo e estrato.
