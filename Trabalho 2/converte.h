#ifndef CONVERTE_H
#define CONVERTE_H
#include "btree.h"
#include "rb.h"

//Converte uma BTree 2-3-4 para uma RubroNegra
rb* converte(btree* bt);

int verificaCaso(noBt* no);

#endif
