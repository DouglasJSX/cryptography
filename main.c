#include <stdio.h>
#include <string.h>
#include "sha256.h"

/* Converte os 32 bytes do hash em 64 caracteres hexadecimais. */
static void calcular_hash(const char *texto, char resultado[65])
{
    SHA256_CTX contexto;
    BYTE hash[SHA256_BLOCK_SIZE];
    size_t i;

    sha256_init(&contexto);
    sha256_update(&contexto, (const BYTE *)texto, strlen(texto));
    sha256_final(&contexto, hash);

    for (i = 0; i < SHA256_BLOCK_SIZE; i++)
        sprintf(resultado + i * 2, "%02x", (unsigned int)hash[i]);
}

int main(void)
{
    const char *textos[] = {"abc", "hello world"};
    const char *esperados[] = {
        "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad",
        "b94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9"};
    char texto[1024], resultado[65];
    size_t i;

    puts("SHA-256: dois testes com resultados conhecidos\n");
    for (i = 0; i < 2; i++)
    {
        calcular_hash(textos[i], resultado);
        printf("Texto: %s\nHash: %s\n", textos[i], resultado);
        if (strcmp(resultado, esperados[i]) != 0)
        {
            fputs("FALHA: resultado diferente do esperado.\n", stderr);
            return 1;
        }
        puts("Teste OK\n");
    }

    printf("Digite um texto para calcular outro hash: ");
    fflush(stdout);
    if (!fgets(texto, sizeof(texto), stdin))
        return ferror(stdin) ? 1 : 0;

    if (!strchr(texto, '\n'))
    {
        int proximo = getchar();
        if (proximo != '\n' && proximo != EOF)
        {
            fputs("Texto maior que o limite de 1023 bytes.\n", stderr);
            return 1;
        }
    }
    texto[strcspn(texto, "\r\n")] = '\0';
    calcular_hash(texto, resultado);
    printf("Hash: %s\n", resultado);
    return 0;
}
