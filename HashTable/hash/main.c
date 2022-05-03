#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

int main() {
   //Declaração de Variáveis
   FILE *arq;
   hash *Thash;
   int tamanho;
   char palavra[30];
   int pos;

   //Leitura do Arquivo
   arq = fopen("entrada.txt", "r");
   if (!arq)
   {
       printf("Erro ao abrir o arquivo de entrada\n");
       return 1;
   }

   if(fscanf(arq, "%d", &tamanho) == 0)
   {
       printf("Erro ao ler do arquivo de entrada\n");
       return 1;
   }

   //Criar a Tabela Hash
   Thash = criaHash(tamanho);

   //Inserir dados na Tabela Hash
    while (!feof(arq))
    {
        if(fscanf(arq, "%s", palavra) == 0)
        {
            printf("Erro ao ler do arquivo de entrada\n");
            return 1;
        }
        insere(Thash, palavra);
    }
    fclose(arq);

   //Mostrar ocupação da Hash
   for(int i=0; i<tamanho;i++)
   {
       printf("Posicao %d contem %d palavras\n", i, getTamanhoLista(Thash, i));
   }

   //Procurar um elemento na Hash
    strcpy(palavra, "ABACAXI");
    pos = encontraElemento(Thash, palavra);
    if( pos != -1)
    {
       printf("\nElemento encontrado na hash. Posicao %d.\n", pos);
    } else
    {
        printf("\nElemento não encontrado na hash\n");
    }

    //Procurar um elemento na Hash
    strcpy(palavra, "vanessa");
    pos = encontraElemento(Thash, palavra);
    if( pos != -1)
    {
        printf("\nElemento encontrado na hash. Posicao %d.\n", pos);
    } else
    {
        printf("\nElemento não encontrado na hash\n");
    }

    //Percorrer uma lista da Hash
    percorre(Thash, 1);
    printf("\n");
    percorre(Thash, 13);

    //Remover uma palavra da Hash
    strcpy(palavra, "A");
    pos = removeElemento(Thash, palavra);
    if(pos == -1)
        printf("\nPalavra não encontrada na hash\n");

    //Remover uma palavra da Hash
    strcpy(palavra, "cortina");
    pos = removeElemento(Thash, palavra);
    if(pos == -1)
        printf("\nPalavra não encontrada na hash\n");

    free(Thash);

     return 0;
}

//TESTAR SE É NECESSÁRIO O GETLISTA OU SE É POSSÍVEL ACESSAR ESSE ENDEREÇO DIRETO NA TAD HASH