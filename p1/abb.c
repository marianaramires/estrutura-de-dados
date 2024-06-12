#include <stdio.h>
#include <stdlib.h>

typedef struct _elemento
{
    int reg;
    struct _elemento *esq;
    struct _elemento *dir;
} elemento;

typedef struct
{
    elemento * raiz;
} tarv;

void abb_constroi(tarv *parv){
    parv->raiz = NULL;
}

void abb_insere_no(tarv * parv, elemento ** ppno, int reg){
    if (*ppno == NULL){
        *ppno = malloc(sizeof(elemento));
        (*ppno)->reg = reg;
        (*ppno)->dir = NULL;
        (*ppno)->esq = NULL;
    } else if((*ppno)->reg < reg){
        abb_insere_no(parv, &((*ppno)->dir), reg);
    } else{
        abb_insere_no(parv, &((*ppno)->esq), reg);
    }
}

void abb_insere(tarv *parv, int reg){
    abb_insere_no(parv, &parv->raiz, reg);
}

elemento* abb_busca_no(tarv *parv, elemento *pno, int reg){
    elemento * ret;
    if(pno == NULL){
        ret = NULL;
    } else if(pno->reg < reg){
        ret = abb_busca_no(parv, pno->dir, reg);
    } else if(pno->reg > reg){
        ret = abb_busca_no(parv, pno->esq, reg);
    } else{
        ret = pno->reg;
    }

    return ret;
}

elemento * abb_busca(tarv *parv, int reg){
    abb_busca_no(parv, parv->raiz, reg);
}

//wip
void destroi_abb_no(tarv *parv, elemento *pno){
    if(parv != NULL){
        destroi_abb_no(parv,pno->dir);
        destroi_abb_no(parv,pno->esq);
        free(pno);
    }
}

//wip
void destroi_abb(tarv *parv){
    destroi_abb_no(parv, parv->raiz);
}

int main(void){
    tarv arvore;
    abb_constroi(&arvore);
    abb_insere(&arvore, 10);
    printf("%d\n", arvore.raiz->reg);

    abb_insere(&arvore, 7);
    printf("%d\n", arvore.raiz->esq->reg);

    abb_insere(&arvore, 15);
    printf("%d\n", arvore.raiz->dir->reg);

    //destroi_abb(&arvore);

    return EXIT_SUCCESS;
}