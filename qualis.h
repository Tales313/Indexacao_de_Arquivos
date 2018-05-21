#define TAMTITULO 51 /* Tamanho da string */

typedef struct {
    int issn; /* identificador �nico da publica��o seriada*/
    char titulo[TAMTITULO]; /* titulo do periodico */
    char estrato[3]; /* Estrato: A1, A2, B1, B2, B3, B4, B5, C */
}periodico;
