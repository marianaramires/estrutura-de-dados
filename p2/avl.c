#include<stdlib.h>
#include<stdio.h>

typedef int titem;

typedef struct _node{
    titem item;
    struct _node *esq;
    struct _node *dir;
    int h;
}tnode;

int max(int a, int b){
    return (a>b?a:b);
}

int altura(tnode *arv){
    int ret;
    if (arv == NULL){
        ret = -1;
    }else{
        ret = arv->h;
    }
    return ret;
}

void avl_insere(tnode **pparv, titem reg){
    if((*pparv)==NULL){
        (*pparv) = (tnode *) malloc(sizeof(tnode));
        (*pparv)->item = reg;
        (*pparv)->esq = NULL;
        (*pparv)->dir = NULL;
        (*pparv)->h = 0;
    } else if(((*pparv)->item - reg) > 0){ /*ESQUERDA*/
        avl_insere(&(*pparv)->esq, reg);
    } else{ /*DIREITA*/
        avl_insere(&(*pparv)->dir, reg);
    }

    (*pparv)->h = max(altura((*pparv)->esq), altura((*pparv)->dir)) +1;
    avl_rebalencear(pparv);
}

int avl_busca(tnode **parv, titem reg){
    int ret;
    int cmp;

    if(*parv != NULL){
        cmp = (*parv)->item - reg;
        if(cmp > 0){ /* é menor, vai para a esquerda */
            avl_busca(&(*parv)->esq, reg);
        } else if(cmp > 0){ /* é maior, vai para a direita*/
            avl_busca(&(*parv)->dir, reg);
        } else{ /* achou :D */
            return EXIT_SUCCESS;
        }
    } else{
        return EXIT_FAILURE;
    }
}

void _rd(tnode **parv){
    tnode *y = (*parv);
    tnode *x = y->esq;
    tnode *A = x->esq;
    tnode *B = x->dir;
    tnode *C = y->dir;

    x->dir = y;
    y->esq = B;
    *parv = x;
    y->h = max(altura(B), altura(C)) +1;
    x->h = max(altura(A), altura(y)) +1;
}

void _re(tnode **parv){
    tnode *x = *parv;
    tnode *y = x->dir;
    tnode *A = x->esq;
    tnode *B = y->esq;
    tnode *C = y->dir;

    x->dir = B;
    y->esq = x;
    *parv = y;
    x->h = max(altura(A), altura(B)) +1;
    y->h = max(altura(x), altura(C)) +1;
}

void avl_rebalancear(tnode **parv){
    int fb, fbf;
    tnode *filho;
    fb = altura((*parv)->esq) - altura((*parv)->dir);

    if(fb == -2){
        filho = (*parv)->dir;
        fbf = altura(filho->esq) - altura(filho->dir);
        if(fbf <= 0){ /* caso 1: (->->) - (->)*/
            _re(parv);
        } else { /* caso 2: (->->) - (<-)*/
            _rd(&(*parv)->dir);
            _re(parv);
        }
    } else if(fb == 2){
        filho = (*parv)->esq;
        fbf = altura(filho->esq) - altura(filho->dir);
        if (fbf >= 0) /* caso 3: (<-<-) - (<-)*/
        {
            _rd(parv);
        } else { /* caso 4: (<-<-) - (->)*/
            _re(&(*parv)->esq);
            _rd(parv);
        } 
    }
}

tnode ** percorre_esq(tnode ** arv){
    tnode * aux = *arv;
    if(aux->esq == NULL){
        return aux;
    } else {
        while (aux->esq->esq != NULL)
        {
            aux = aux->esq;
            return &(aux->esq);
        }
    }
}

void avl_remove(tnode **parv, titem reg){
    int cmp;
    tnode *aux;
    tnode **sucessor;

    if(*parv != NULL){
        cmp = (*parv)->item - reg;
        if(cmp > 0){ /* vai para ESQUERDA */
            avl_remove(&((*parv)->esq), reg);
        } else if(cmp < 0){ /* vai para DIREITA */
            avl_remove(&((*parv)->dir), reg);
        } else{ /* achou :D */
            if((*parv)->esq == NULL && (*parv)->dir == NULL){ /* caso 1: nó folha */
                free(*parv);
                *parv = NULL;
            } else if((*parv)->esq == NULL || (*parv)->dir == NULL){ /* caso 2: tem 1 filho */
                aux = *parv;

                if((*parv)->esq == NULL){
                    *parv = (*parv)->dir;
                } else{
                    *parv = (*parv)->esq;
                }

                free(aux);
            } else { /* caso 3: tem 2 filhos */
                sucessor = percorre_esq(&(*parv)->dir);
                (*parv)->item = (*sucessor)->item;
                avl_remove(&(*parv)->dir, (*sucessor)->item);
            }
        }
        if(*parv == NULL){
            (*parv)->h = max(altura((*parv)->esq), altura((*parv)->dir)) +1;
            avl_rebalancear(parv);
        }
    }
}

void avl_destroi(tnode *parv){
    if(parv != NULL){
        avl_destroi(parv->esq);
        avl_destroi(parv->dir);
        free(parv);
    }
}