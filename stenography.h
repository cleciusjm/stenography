#define EOS '\0'
/**
 * Recebe o conteudo de um arquivo P3 como string,
 *  lê a frase escondida por estenografia e retorna esta
 */
char *readStegFrom(char *content);
/**
 * Escreve uma frase passada no parametro phrase no conteudo do ponteiro content
 */
void writeStegTo(char *content, char *phrase);
