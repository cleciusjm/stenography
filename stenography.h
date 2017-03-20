#define EOS '\0'
typedef struct {
	unsigned int* data;
	unsigned int h;
	unsigned int w;
	unsigned int max;
} P3Image;

/**
 * Recebe o conteudo de um arquivo P3 como string,
 *  lê a frase escondida por estenografia e retorna esta
 */
char *readStegFrom(P3Image *content);
/**
 * Escreve uma frase passada no parametro phrase no conteudo do ponteiro content
 */
void writeStegTo(P3Image *content, char *phrase);
