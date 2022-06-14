#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"
#include <time.h>
//struct de cada no da arvore
struct no {
  int chave;
  struct no *esq;
  struct no* dir;
  struct no* pai;
  int fb;
  int rot;
};


//struct da arvore
struct arvore {
  struct no *sentinela;
};


//função para alocar memória da árvore
arvore *criaArvore() {

  arvore *A = (arvore*) malloc(sizeof(arvore));  

  if( !A ){
    printf("\nErro ao alocar memória!");
    exit(0);
  }

  no *sentinela = (no*) malloc(sizeof(no));

  if( !sentinela ){
    printf("\nErro ao alocar memória!");
    exit(0);
  }
  sentinela -> rot = 0;
  sentinela -> esq = NULL;
  sentinela -> dir = NULL;
  sentinela -> pai = NULL;
  A -> sentinela = sentinela;

  return A;
}

//função para inserir um nó na arvore
void insereNo(arvore *A, int chave) {

  no *aux;
  no *pai;

  //alocando o novo nó
  no* novoNo = (no*) malloc(sizeof(no));

  if (!novoNo) {
    printf("\nErro ao alocar memória!");
    exit(0);
  }
  novoNo -> rot = 0;
  novoNo -> chave = chave;
  novoNo -> esq = NULL;
  novoNo -> dir = NULL;
  novoNo -> pai = NULL;
  novoNo -> fb = 0;

  //inserir o novo nó no seu lugar correto dentro da arvore
  if (A -> sentinela -> dir == NULL) { //arvore vazia

    A -> sentinela -> dir = novoNo;
    novoNo -> pai = A -> sentinela;

    return;
  }

  //arvore não vazia
  aux = A -> sentinela -> dir;

  while (aux != NULL) {

    pai = aux;

    if (chave < aux -> chave)
      aux = aux -> esq;
    else  
      aux = aux -> dir;      
  }

  if (chave < pai -> chave)
    pai -> esq = novoNo;
  else
    pai -> dir = novoNo;

  novoNo -> pai = pai;
  atualizaFB_Insercao(novoNo, A);

  return;
}

void geraNumerosAleatorios(int qtNumeros, char nomeArquivo[]){

  srand(time(NULL)); // gera números aleatórios através de uma "semente" que é gerada a cada execução para evitar repetições

  FILE *file;
  file = fopen(nomeArquivo, "w");

  if(file == NULL)
    exit(EXIT_FAILURE);


  for(int i = 0; i < qtNumeros; i++)
    //fprintf(file, "%d\n", rand() % qtNumeros);
    fprintf(file, "%d\n", qtNumeros-i);

  fclose(file);

}

//função para inserir um nó na arvore
void insereArquivo(arvore *A, char nomeArquivo[]) {

  int chave;
  FILE *file;

  //abrindo o arquivo no modo de leitura
  file = fopen(nomeArquivo, "r");

  //le um numero por linha e insere na arvore até o fim do arquivo
  while (!feof(file)) {
    fscanf(file, "%d\n", &chave);
    insereNo(A, chave);
  }

  //fecha o arquivo
  fclose(file);
}

//função para remover um nó da arvore
void removeNo(arvore *A, int chave) {

  no *aux;
  no *sucessor;

  //encontrar o no na arvore
  aux = A -> sentinela -> dir;

  while (aux != NULL && aux -> chave != chave) {

    if (chave < aux -> chave)
      aux = aux -> esq;
    else 
      aux = aux -> dir;

  }

  //elemento para remoção não existe na arvore
  if (aux == NULL) {
    //printf("\nElemento não encontrado na árvore binária!");
    return;
  }

  //realizar a remoção
  if (aux -> esq != NULL && aux -> dir != NULL){ //nó possui 2 filhos

    sucessor = aux -> dir;

    while(sucessor -> esq != NULL)
      sucessor = sucessor -> esq;

    aux -> chave = sucessor -> chave;
    aux = sucessor;
  }

  if (aux -> esq == NULL && aux -> dir == NULL){ //nó não possui nenhum filho, ou seja, é folha

    if (aux -> chave < aux -> pai -> chave)
      aux -> pai -> esq = NULL;
    else
      aux -> pai -> dir = NULL;

    atualizaFB_Remocao(aux, A);

    free(aux);
    return;
       
  }

  if (aux -> esq != NULL || aux -> dir != NULL){ //nó possui 1 filho

    if (aux -> esq != NULL) {
      if (aux -> chave < aux -> pai -> chave)
        aux -> pai -> esq = aux -> esq;
      else
        aux -> pai -> dir = aux -> esq;
      
      aux -> esq -> pai = aux -> pai;
  }

    if (aux -> dir != NULL) {
      if (aux -> chave < aux -> pai -> chave)
        aux -> pai -> esq = aux -> dir;
      else
        aux -> pai -> dir = aux -> dir;

      aux -> dir -> pai = aux -> pai;

    }

    atualizaFB_Remocao(aux, A);

    free(aux);

    return;
  }

}

//função para percorrer a arvore e imprimir as chaves e o fb de cada nó
void percorreArvore(no *raiz) {

  if (raiz == NULL) 
    return;
  
  printf("%d: %d\t", raiz -> chave, raiz -> fb);
  percorreArvore(raiz -> esq);
  percorreArvore(raiz -> dir);

}

//função para retornar a raiz da arvore binaria
no *retornaRaiz(arvore *A) {
  
  return A -> sentinela -> dir;
}


//função para retornar um nó a partir de uma chave
no *retornaNo(arvore *A, int chave) {

  no *elemento = retornaRaiz(A);
  
  while (elemento != NULL) {

    if (chave == elemento -> chave)
      return elemento;

    if(chave < elemento -> chave)
      elemento = elemento -> esq;
    else
      elemento = elemento -> dir;
  
  }

  //se não achou o elemento, a chave não existe na arvore
  //printf("\nElemento não existe na árvore binária!");
  exit(0);
  
}


//função para imprimir os dados de um nó
void imprimeDados(arvore *A) {

  printf("Rot:%d\n",  A -> sentinela ->rot);

  
  
}

//função para atualizar o fator de balanceamento com uma inserção na arvore
void atualizaFB_Insercao(no *no, arvore *A)
{
  
  if(no->chave < no->pai->chave) 
    no->pai->fb--; 
  else 
    no->pai->fb++;
    
  no=no->pai;
  
  while((no -> fb != 2) && (no -> fb != -2) && (no -> fb != 0) && (no != A->sentinela -> dir)) {
  
    if(no->chave < no->pai->chave)
      no->pai->fb--;
    else
      no->pai->fb++;

    no=no->pai;
  }

  if((no->fb==2) || (no->fb==-2)){
    
    balanceamento(no, A);
  }
  return;
}


//função para atualizar o fator de balanceamento com uma remoção na arvore
void atualizaFB_Remocao(no *no, arvore *A) {

  if(no -> chave < no -> pai -> chave) 
    no -> pai -> fb++;
  else
    no -> pai -> fb--;
  
  no = no -> pai;

  while((no -> fb == 0) && (no -> pai != A -> sentinela)) {
  
    if(no->chave < no->pai->chave)
      no->pai->fb++;
    else
      no->pai->fb--;

    no=no->pai;
  }

  if((no -> fb == 2) || (no -> fb == -2)){
    balanceamento(no, A);
    if((no -> pai -> fb == 0) && (no -> pai != A -> sentinela -> dir))
      atualizaFB_Remocao(no -> pai, A);
  }
  return;

}

//função para balancear a arvore apos uma inserção
void balanceamento(no * no, arvore *A)
{

  struct no * filho;
  struct no *neto;

  if(no->fb == -2) { //Rotação a direita
    filho = no->esq;
    if(filho->fb == 1) //Rotação dupla, esq-dir
    {
      neto = filho-> dir;
      rotEsq(filho, A);
      rotDir(no, A);
  
      if(neto -> fb == -1) {
        no -> fb = 1;
        filho->fb = 0;
        neto -> fb = 0;
      }
      else {
        if(neto -> fb == 1)
          filho -> fb = -1;
        else
          filho -> fb = 0;
    
        no -> fb = 0;
        neto ->fb = 0;
      }
    }

    else { //rotação simples a direita
      rotDir(no,A);
      if(filho -> fb == 0) {
        no -> fb = -1;
        filho -> fb = 1;
      }
      else {
        no -> fb = 0;
        filho -> fb = 0;
      }
    }
  }
  else { //rotação a esquerda
    filho = no -> dir;
    if( filho -> fb == -1) { //rotação dupla, dir-esq
      neto = filho -> esq;
      rotDir(filho,A);
      rotEsq(no,A);
      if(neto -> fb == -1) {
        no -> fb = 0;
        filho -> fb = 1;
        neto -> fb = 0;
      }
      else {
        if(neto -> fb == 1) 
          no -> fb = -1;
        else
          no -> fb = 0;
        
        filho -> fb = 0;
        neto -> fb = 0;
      }
    }
    else { //rotação simples a esquerda
      rotEsq(no,A);
      if(filho -> fb == 0) {
        no -> fb = 1;
        filho -> fb = -1;
      }
      else {
        no -> fb = 0;
        filho -> fb = 0;
      }
    }
  } 
  return;
}

//função de rotação a esquerda da arvore
void rotEsq(no * noDesbalanceado, arvore *A)
{
  A -> sentinela ->rot += 1;
  no *filhoDir;
  no *esqFilho;

  filhoDir = noDesbalanceado -> dir;
  esqFilho = filhoDir->esq;

 

  filhoDir->pai = noDesbalanceado->pai;

  if(filhoDir -> chave < noDesbalanceado -> pai -> chave)
    noDesbalanceado->pai->esq = filhoDir;
  else
    noDesbalanceado->pai->dir = filhoDir;
  
  filhoDir -> esq = noDesbalanceado;
  noDesbalanceado->pai = filhoDir;
  noDesbalanceado->dir = esqFilho;

  if(esqFilho != NULL)
    esqFilho->pai = noDesbalanceado;
  
  return;
}

//função de rotação a direita da arvore
void rotDir(no * noDesbalanceado, arvore *A)
{
  A -> sentinela ->rot += 1;
  no *filhoEsq;
  no *dirFilho;

  filhoEsq = noDesbalanceado -> esq;
  dirFilho = filhoEsq->dir;

  filhoEsq->pai = noDesbalanceado->pai;

  if(filhoEsq -> chave < noDesbalanceado->pai->chave)
    noDesbalanceado->pai->esq = filhoEsq;
  else
    noDesbalanceado->pai->dir = filhoEsq;
  
  filhoEsq -> dir = noDesbalanceado;
  noDesbalanceado->pai = filhoEsq;
  noDesbalanceado->esq = dirFilho;

  if(dirFilho != NULL)
    dirFilho->pai = noDesbalanceado;
  
  return;
}

int altura(no *raiz){
    if((raiz == NULL) || (raiz->esq == NULL && raiz->dir == NULL)){
        return 0;
    }  
    else{ //retorna a pilha do lado com maior profundidade
        if(altura(raiz->esq) > altura(raiz->dir)){
            return 1 + altura(raiz->esq);
        }
        else{
            return 1 + altura(raiz->dir);
        }
    }
}