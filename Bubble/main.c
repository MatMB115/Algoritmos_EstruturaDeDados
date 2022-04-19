#include <stdio.h>
#include <string.h>

#include "bolha.h"

int main() {
    char nomeArquivo[30];
    tReturn *rep;

    scanf(" %s", nomeArquivo);
    rep = leArquivo(nomeArquivo);
    if(getErro(rep) == 0){
      bolha(getVet(rep), getTam(rep));
      imprimeVet(getVet(rep), getTam(rep));
    }
    else{
      trataErro(getErro(rep));
    }
    return 0;
}
