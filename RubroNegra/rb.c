#include <stdio.h>
#include <stdlib.h>

#include "rb.h"

// COM112 - Algoritmos e Estruturas de Dados II
// Atividade 06
// 2019005687– Matheus Martins Batista
// 2020003596 - Kaique de Souza Leal Silva
// rb

struct no{
    int chave;
    char cor;
    struct no *esq;
    struct no *dir;
    struct no *pai;
};

struct arvore{
    no *sentinelaRaiz;
    no *sentinelaFolha;
    int numElementos;
};

//Cria uma nova árvore inicializando a sentinela
rb *criaArvore(){ //OK
    rb *arv = (rb*) malloc(sizeof(rb));
    if(arv == NULL){
        return NULL;
    }
    else{
        no *sent = (no*) malloc(sizeof(no));
        if(sent == NULL){
            return NULL;
        }
        else{ //Preencher os campos da árvore
            sent->chave = -1000;
            sent->esq = NULL;
            sent->dir = NULL;
            sent->pai = NULL;
            sent->cor = 'p';
            arv->sentinelaRaiz = sent;
            arv->numElementos = 0;

            no *sentFolha = (no*) malloc(sizeof(no));
            if(sentFolha == NULL){
                return NULL;
            }
            sentFolha->chave = -2399;
            sentFolha->esq = NULL;
            sentFolha->dir = NULL;
            sentFolha->pai = NULL;
            sentFolha->cor = 'p';
            arv->sentinelaFolha = sentFolha;
            return arv;
        }
    }
}

//Popula uma árvore binária de pesquisa a partir de números contidos no arquivo
//Retorna -1 caso haja erros durante a inserção e/ou leitura do arquivo
//Retorna 0 caso contrário
int carregaArvore(rb *arv, char *nomeArquivo){ //OK
    int chave;
    FILE *arq = fopen(nomeArquivo, "r");
    if(arq == NULL){
        return -1;
    }
    else{
        while(!feof(arq)){
            if(fscanf(arq, "%d", &chave) == 0){
                printf("Erro ao ler do arquivo de entrada\n");
                fclose(arq);
                return 1;
            }
            if(insereNo(arv, chave) == -1){
                printf("Erro ao inserir um nó");
                fclose(arq);
                return 1;
            }
        }
        fclose(arq);
        return 0;
    }
}

//Aloca um novo nó e o insere na árvore
//Retorna 0 caso a inserção aconteça e -1 caso contrário
int insereNo(rb *arv, int chave){
    no *aux;
    no *pai;

    //CRIAR O NOVO NÓ E INSTANCIÁ-LO
    no *novoNo = (no*) malloc(sizeof(no));
    if(novoNo == NULL){
        printf("Erro ao alocar memoria");
        return -1;
    }
    novoNo->chave = chave;
    novoNo->esq = arv->sentinelaFolha; //toda folha aponta para a sentinelaFolha
    novoNo->dir = arv->sentinelaFolha; //toda folha aponta para a sentinelaFolha
    novoNo->pai = NULL;
    novoNo->cor = 'v'; //todo nó inserido é vermelho

    //INSERIR O NOVO NÓ NO SEU LUGAR CORRETO
    if(arv->numElementos == 0) //árvore está vazia
    {
        arv->sentinelaRaiz->dir = novoNo;
        novoNo->pai = arv->sentinelaRaiz;
        novoNo->cor = 'p'; //a raiz é sempre preta
        arv->numElementos++;
        return 0;
    }

    aux = arv->sentinelaRaiz->dir;
    pai = arv->sentinelaRaiz;
    while(aux != arv->sentinelaFolha)
    {
        pai = aux;
        if (chave < aux->chave)
            aux = aux->esq;
        else
            aux = aux->dir;
    }
    if (chave < pai->chave)
        pai->esq = novoNo;
    else
        pai->dir = novoNo;
    novoNo->pai = pai;
    if(novoNo->pai->cor == 'v')
        balanceamentoInsercao(arv, novoNo);
    arv->numElementos++;
    return 0;
}

//Remove um elemento da árvore
//Retorna 0 caso a deleção aconteça;
//Retorna -1 caso a árvore esteja vazia
//Retorna -2 caso o elemento não esteja presente na árvore
int removeNo(rb *arv, int chave){ //OK
    no *noRemove = recuperaNo(arv, chave);
    no *predecessor;
    if(noRemove == NULL){
        return -2;
    }
    else{
        if(arv->sentinelaRaiz->dir == NULL){
            printf("Árvore vazia\n");
            return -1;
        }

        if(noRemove->esq != NULL && noRemove->dir != NULL){//Dois filhos
            predecessor = noRemove->esq;
            while(predecessor->dir != NULL){
                predecessor = predecessor->dir;
            }
            noRemove->chave = predecessor->chave;
            noRemove = predecessor;
        }

        if(noRemove->esq == NULL && noRemove->dir == NULL){//Dois filhos
            if(noRemove->chave < noRemove->pai->chave){
                noRemove->pai->esq = NULL;
            }
            else{
                noRemove->pai->dir = NULL;
            }
            atualizaFB_Remocao(arv, noRemove, chave);
            free(noRemove);
            return 0;
        }

        if(noRemove->esq == NULL || noRemove->dir == NULL){//Um filho
            if(noRemove->dir != NULL){//à direita
                if(noRemove->chave < noRemove->pai->chave){ //Ficará à esquerda do pai
                    noRemove->pai->esq = noRemove->dir;
                }
                else{ //Ficará à direita do pai
                    noRemove->pai->dir = noRemove->dir; 
                }
                noRemove->dir->pai = noRemove->pai; 
            }
            else{ //à esquerda
                if(noRemove->chave < noRemove->pai->chave){
                    noRemove->pai->esq = noRemove->esq;
                }
                else{
                    noRemove->pai->dir = noRemove->esq;
                }
                noRemove->esq->pai = noRemove->pai; 
            }
        }
    }
    atualizaFB_Remocao(arv, noRemove, chave);
    free(noRemove);
    arv->numElementos--;
    return 0;
}

//Percorrimento em pré-ordem
//printf("%d: %d\t", raiz->chave, raiz->fb);
void percorre(no *raiz){ //OK
    if(raiz->chave != 2399){
        printf("%d: %c\t", raiz->chave, raiz->cor);
        percorre(raiz->esq);
        percorre(raiz->dir);
    }
}

//Retorna o nó que contém a chave indicada (não trata valores repetidos)
//Retorna NULL caso o elemento não exista na árvore
no *recuperaNo(rb *arv, int chave){ //OK
    no *noAtual;
    noAtual = arv->sentinelaRaiz->dir;
    if(noAtual == NULL){
        return NULL;
    }
    else{
        while(noAtual != NULL){
            if(chave == noAtual->chave){
                return noAtual;
            }
            else{
                if(chave < noAtual->chave){
                    noAtual = noAtual->esq;
                }
                else{
                    noAtual = noAtual->dir;
                }
            }
        }
        return NULL;
    }
}

//Imprime a chave do nó, as chaves de seus filhos e do seu pai
//Se o nó não tiver filho da esquerda e/ou da direita, imprime NULO
//Se o pai for a sentinela, imprime Sentinela
void imprimeNo(rb *arv, no *atual){ //OK
    printf("Chave : %d\n", atual->chave);
    if(atual->dir == NULL && atual->esq == NULL){
        printf("Filho Esq : NULO\n");
        printf("Filho Dir : NULO\n");
    }
    else{
        if(atual->esq == NULL){
            printf("Filho Esq : NULO\n");
            printf("Filho Dir : %d\n", atual->dir->chave);
        }
        else{
            if(atual->dir == NULL){
            printf("Filho Esq : %d\n", atual->esq->chave);
            printf("Filho Dir : NULO\n");
            }
            else{
                printf("Filho Esq : %d\n", atual->esq->chave);
                printf("Filho Dir : %d\n", atual->dir->chave);
            }
        }
    }
    if(atual->pai->chave == -1000){
        printf("Sentinela\n");
    }
    else{
        printf("Pai : %d\n", atual->pai->chave);
    }
}

//Retorna a quantidade de elementos contidos na árvore
int getNumElementos(rb *arv){ //OK
    return arv->numElementos;
}

//Retorna a raiz da árvore (filho direita da sentinela)
no *getRaiz(rb *arv){ //OK
    return arv->sentinelaRaiz->dir;
}

//Função recursiva que retorna a altura da árvore
//A altura é maior distância entre a raiz e uma folha
int getAltura(no *raiz){ //OK
    if((raiz == NULL) || (raiz->esq == NULL && raiz->dir == NULL)){
        return 0;
    }  
    else{ //retorna a pilha do lado com maior profundidade
        if(getAltura(raiz->esq) > getAltura(raiz->dir)){
            return 1 + getAltura(raiz->esq);
        }
        else{
            return 1 + getAltura(raiz->dir);
        }
    }
}

//Rotação à esquerda no nó desbalanceado
void rotacaoEsq(rb *arv, no *noDesbalanceado){ //OK
    
    no *filhoDir;
    no *esqFilho;
    
    filhoDir = noDesbalanceado -> dir;
    esqFilho = filhoDir->esq;
    
    filhoDir->pai = noDesbalanceado->pai;
    
    if(filhoDir -> chave < noDesbalanceado -> pai -> chave){
        noDesbalanceado->pai->esq = filhoDir; 
    }
    else{
        noDesbalanceado->pai->dir = filhoDir;
    }
    
    filhoDir -> esq = noDesbalanceado;
    noDesbalanceado->pai = filhoDir;
    noDesbalanceado->dir = esqFilho;
    
    if(esqFilho != NULL){
        esqFilho->pai = noDesbalanceado;
    }
}

//Rotação à direita no no desbalanceado
void rotacaoDir(rb *arv, no *noDesbalanceado){ //OK
      
    no *filhoEsq;
    no *dirFilho;
    
    filhoEsq = noDesbalanceado -> esq;
    dirFilho = filhoEsq->dir;
    
    filhoEsq->pai = noDesbalanceado->pai;
    
    if(filhoEsq -> chave < noDesbalanceado->pai->chave){
        noDesbalanceado->pai->esq = filhoEsq;
    }
    else{
        noDesbalanceado->pai->dir = filhoEsq;
    }
    filhoEsq -> dir = noDesbalanceado;
    noDesbalanceado->pai = filhoEsq;
    noDesbalanceado->esq = dirFilho;
    
    if(dirFilho != NULL){
        dirFilho->pai = noDesbalanceado;
    }
}

//Verifica se houve desbalanceamento na inserção
//Se houve, faz o balanceamento
//Implementação do RB-INSERT-FIXUP(T, z) do Cormen
void balanceamentoInsercao(rb *arv, no *novoNo){
    //quebra da propriedade 3
    no *pai = novoNo->pai;
    no *avo = pai->pai;
    no *tio;
    if (novoNo->chave < avo->chave) //o nó está a esquerda do avô
    {
        tio = avo->dir;
        //IMPLEMENTAR AS REGRAS DA TABELA
        if(tio->cor == 'v') //CASO 1
        {
            pai->cor = 'p';
            tio->cor = 'p';
            avo->cor = 'v';
            if (avo->pai->cor == 'v')
                balanceamentoInsercao(arv, avo);
        }
        else //o tio é preto
        {
            if(novoNo->chave >= pai->chave) //o nó é um filho da direita -> CASO 2
            {
                novoNo = pai;
                rotacaoEsq(arv, novoNo);
                pai = novoNo->pai; //atualizar a variável pai
            }
            pai->cor = 'p';
            avo->cor = 'v';
            rotacaoDir(arv, avo);
        }
    }
    else //o nó desbalanceado está à direita do avô
    {
        tio = avo->esq;
        //IMPLEMENTAR AS REGRAS DA TABELA
        if(tio->cor == 'v') //CASO 1
        {
            pai->cor = 'p';
            tio->cor = 'p';
            avo->cor = 'v';
            if (avo->pai->cor == 'v')
                balanceamentoInsercao(arv, avo);
        }
        else //o tio é preto
        {
            if(novoNo->chave < pai->chave) //o nó é um filho da esquerda -> CASO 2
            {
                novoNo = pai;
                rotacaoDir(arv, novoNo);
                pai = novoNo->pai; //atualizar a variável pai
            }
            pai->cor = 'p';
            avo->cor = 'v';
            rotacaoEsq(arv, avo);
        }
    }
    arv->sentinelaRaiz->dir->cor = 'p'; //sempre colore a raiz de preto
    return;
}


//Verifica se houve desbalanceamento na remoção
//Se houve, faz o balanceamento
//sucessor é o nó que ficou no lugar do nó removido
void balanceamentoRemocao(rb *arv, no *sucessor, no *pai, int chave);
