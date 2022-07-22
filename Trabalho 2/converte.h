#ifndef CONVERTE_H
#define CONVERTE_H
#include "btree.h"
#include "rb.h"

//Função que instância a RB e chama a conversão de cada nó recursivamente
rb* converte(btree* bt);
//Função recursiva para converter a arvore 2-3-4 em uma arvore rubro-negra
void converteNos(noBt * btAtual, noRb * rbAtual, rb * rb);

#endif
