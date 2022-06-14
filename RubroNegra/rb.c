#include <stdio.h>
#include <stdlib.h>

#include "rb.h"

// COM112 - Algoritmos e Estruturas de Dados II
// Atividade 06
// 2019005687– Matheus Martins Batista
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
            sentFolha->chave = -2000;
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
    if(arv->numElementos == 0){ //árvore está vazia
    
        arv->sentinelaRaiz->dir = novoNo;
        novoNo->pai = arv->sentinelaRaiz;
        novoNo->cor = 'p'; //a raiz é sempre preta
        arv->numElementos++;
        return 0;
    }

    aux = arv->sentinelaRaiz->dir;
    pai = arv->sentinelaRaiz;
    while(aux != arv->sentinelaFolha){
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
    no *aux = recuperaNo(arv, chave);
    no *sucessor;
    no *x;

    if(arv->numElementos == 0)
        return -1;
    
    //ENCONTRAR O ELEMENTO NA ÁRVORE
    if(aux == arv->sentinelaFolha){
        printf("elemento não encontrado na árvore.\n");
        return -2;
    }

    //REALIZAR A REMOÇÃO
    if((aux->esq != arv->sentinelaFolha) && (aux->dir != arv->sentinelaFolha)){ //NÓ POSSUI DOIS FILHOS
    
        sucessor = aux->dir;
        while (sucessor->esq != arv->sentinelaFolha) //FILHO MAIS À ESQUERDA DA SUBÁRVORE DA DIREITA
            sucessor = sucessor->esq;
        aux->chave = sucessor->chave; //CÓPIA
        aux = sucessor;
    }
    if((aux->esq == arv->sentinelaFolha) && (aux->dir == arv->sentinelaFolha)){ //NÓ É FOLHA
    
        if (aux->chave < aux->pai->chave)
            aux->pai->esq = arv->sentinelaFolha;
        else
            aux->pai->dir = arv->sentinelaFolha;
        if(aux->cor == 'p'){
            arv->sentinelaFolha->pai = aux->pai;
            balanceamentoRemocao(arv, arv->sentinelaFolha, aux->pai, chave);
        }
        arv->sentinelaFolha->pai = NULL;
        free(aux);
        return 0;
    }
    if((aux->esq != arv->sentinelaFolha) || (aux->dir != arv->sentinelaFolha)){ //NÓ POSSUI UM FILHO
        if (aux->esq != arv->sentinelaFolha) { //AUX POSSUI FILHO À ESQUERDA
            x = aux->esq;
            if (aux->chave < aux->pai->chave) {
                aux->pai->esq = aux->esq;
            } else
                aux->pai->dir = aux->esq;
            aux->esq->pai = aux->pai;
        }
        if (aux->dir != arv->sentinelaFolha) {
            x = aux->dir;
            if (aux->chave < aux->pai->chave) {
                aux->pai->esq = aux->dir;
            } else
                aux->pai->dir = aux->dir;
            aux->dir->pai = aux->pai;
        }
        if (aux->cor == 'p')
            balanceamentoRemocao(arv, x,  aux->pai, chave);
    }
    free(aux);
    return 0;
}

//Percorrimento em pré-ordem
//printf("%d: %c\t", raiz->chave, raiz->cor);
void percorre(no *raiz){ //OK
    if(raiz->chave == -2000)
        return;
        
    printf("%d: %c\t", raiz->chave, raiz->cor);
    percorre(raiz->esq);
    percorre(raiz->dir);
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
void balanceamentoRemocao(rb *arv, no *noX, no *pai, int chave){
    
    no *irmao;
    while((noX != arv->sentinelaRaiz->dir) && (noX->cor == 'p'))
    {
        no *pai = noX->pai;
        if (pai->esq == noX) // o elemento é filho da esquerda
        {
            irmao = pai->dir;
            //IMPLEMEMTAR AS REGRAS DA TABELA
            if (irmao->cor == 'v') //CASO 1
            {
                irmao->cor = 'p';
                pai->cor = 'v';
                rotacaoEsq(arv, pai);
                irmao = pai->dir;
            }
            if ((irmao->esq->cor == 'p') && (irmao->dir->cor == 'p')) //CASO 2
            {
                irmao->cor = 'v';
                noX = pai;
            } else {
                if ((irmao->esq->cor == 'v') && (irmao->dir->cor == 'p'))  //CASO 3
                {
                    irmao->esq->cor = 'p';
                    irmao->cor = 'v';
                    rotacaoDir(arv, irmao);
                    irmao = pai->dir;
                }
                irmao->cor = pai->cor; //CASO 4
                pai->cor = 'p';
                irmao->dir->cor = 'p';
                rotacaoEsq(arv, pai);
                noX = arv->sentinelaRaiz->dir;
            }
        }
        else //o nó é um filho da direita
        {
            irmao = pai->esq;
            if (irmao->cor == 'v') //CASO 1
            {
                irmao->cor = 'p';
                pai->cor = 'v';
                rotacaoDir(arv, pai);
                irmao = pai->esq;
            }
            if ((irmao->esq->cor == 'p') && (irmao->dir->cor == 'p')) {
                irmao->cor = 'v';
                noX = pai;
            } else {
                if ((irmao->esq->cor == 'p') && (irmao->dir->cor == 'v')) {
                    irmao->dir->cor = 'p';
                    irmao->cor = 'v';
                    rotacaoEsq(arv, irmao);
                    irmao = pai->esq;
                }
                irmao->cor = pai->cor;
                pai->cor = 'p';
                irmao->esq->cor = 'p';
                rotacaoDir(arv, pai);
                noX = arv->sentinelaRaiz->dir;
            }
        }
    }
    noX->cor = 'p';
    return;
};
