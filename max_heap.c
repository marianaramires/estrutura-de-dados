#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

void troca(int *a, int *b){
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

int pai(int n){
    return ((n - 1) / 2);
}

int filho_esq(int n){
    return 2*n + 1;
}

int filho_dir(int n){
    return 2*n + 2;
}

void desce(int v[], int n, int tam){
    int maior = n;
    int esq = filho_esq(n);
    int dir = filho_dir(n);

    if (esq < tam && v[esq] > v[maior])
        maior = esq;
    if (dir < tam && v[dir] > v[maior])
        maior = dir;

    if (maior != n){
        troca(&v[n], &v[maior]);
        desce(v, maior, tam);
    }
}

int constroi_heap(int v[], int tam){
    for (int i = pai(tam); i >= 0; i--)
    {
        desce(v, i, tam);
    }
}

int sobe(int v[], int n){
    while (v[pai(n)] < v[n]){
        troca(&v[pai(n)], &v[n]);
        n = pai(n);
    }
}

int acessa_max(int v[]){
    return v[0];
}

int extrai_max(int v[], int *tam){
    int max = v[0];
    *tam = *tam-1;
    v[0] = v[*tam];
    desce(v,0,*tam);

    return max;
}

void altera_prioridade(int v[], int n, int valor, int tam){
    if (v[n] < valor){
        v[n] = valor;
        sobe(v, n);
    } else if (v[n] > valor){
        v[n] = valor;
        desce(v, n, tam);
    }
}

int insere_elemento(int v[], int k, int *tam, int tam_max){
    int ret = EXIT_SUCCESS;
    if (*tam == tam_max)
        ret = EXIT_FAILURE;
    else{
        v[*tam] = k;
        sobe(v, *tam);
        *tam = *tam + 1;
    }

    return ret;
}

void heapsort(int v[], int tam){
    for(int i=tam-1; i<0; i--){
        troca(&v[0],&v[i]);
        desce(v, 0,tam);
    }
}

void test_pai(){
    assert(pai(0) == 0);
    assert(pai(1) == 0);
    assert(pai(3) == 1);
    assert(pai(7) == 3);
    assert(pai(12) == 5);
}

void test_filho_esq(){
    assert(filho_esq(0) == 1);
    assert(filho_esq(1) == 3);
    assert(filho_esq(2) == 5);
    assert(filho_esq(6) == 13);
    assert(filho_esq(10) == 21);
}

void test_filho_dir(){
    assert(filho_dir(0) == 2);
    assert(filho_dir(1) == 4);
    assert(filho_dir(2) == 6);
    assert(filho_dir(6) == 14);
    assert(filho_dir(10) == 22);
}

void test_desce(){
    int vetor[7] = {1, 5, 3, 4, 10, 2, 0};
    desce(vetor, 1, 7);
    int esperado[7] = {1, 10, 3, 4, 5, 2, 0};
    for (int i = 0; i < 7; i++) {
        assert(vetor[i] == esperado[i]);
    }

    int vetor2[7] = {9, 5, 8, 20, 4, 6, 3};
    desce(vetor2, 1, 7);
    desce(vetor2, 0, 7);
    int esperado2[7] = {20, 9, 8, 5, 4, 6, 3};
    for (int i = 0; i < 7; i++) {
        assert(vetor2[i] == esperado2[i]);
    }

    int vetor3[3] = {3, 2, 1};
    desce(vetor3, 0, 3);
    int esperado3[3] = {3, 2, 1};
    for (int i = 0; i < 3; i++) {
        assert(vetor3[i] == esperado3[i]);
    }

    int vetor4[7] = {7, 6, 5, 4, 3, 2, 10};
    desce(vetor4, 2, 7);
    int esperado4[7] = {7, 6, 10, 4, 3, 2, 5};
    for (int i = 0; i < 7; i++) {
        assert(vetor4[i] == esperado4[i]);
    }
}

void test_constroi_heap(){
    int vetor[7] = {1, 5, 3, 4, 10, 2, 0};
    constroi_heap(vetor, 7);
    int esperado[7] = {10, 5, 3, 4, 1, 2, 0};
    for(int i=0; i<7; i++){
        assert(vetor[i] == esperado[i]);
    }

    int vetor2[3] = {1, 2, 3};
    constroi_heap(vetor2, 3);
    int esperado2[3] = {3, 2, 1};
    for(int i=0; i<3; i++){
        assert(vetor2[i] == esperado2[i]);
    }

    int vetor3[7] = {7, 6, 5, 4, 3, 2, 1};
    constroi_heap(vetor3, 7);
    int esperado3[7] = {7, 6, 5, 4, 3, 2, 1};
    for(int i=0; i<7; i++){
        assert(vetor3[i] == esperado3[i]);
    }

    int vetor4[7] = {10, 20, 5, 35, 50, 6, 100};
    constroi_heap(vetor4, 7);
    int esperado4[7] = {100, 50, 10, 35, 20, 6, 5};
    for(int i=0; i<7; i++){
        assert(vetor4[i] == esperado4[i]);
    }
}

void test_sobe(){
    int vetor[3] = {8, 9, 10};
    sobe(vetor, 2);
    int esperado[3] = {10, 9, 8};
    for(int i =0; i<3; i++){
        assert(vetor[i] == esperado[i]);
    }

    int vetor2[7] = {11, 9, 8, 20, 4, 2, 1};
    sobe(vetor2, 3);
    int esperado2[7] = {20, 11, 8, 9, 4, 2, 1};
    for(int i =0; i<7; i++){
        assert(vetor2[i] == esperado2[i]);
    }

    int vetor3[7] = {25, 24, 23, 22, 21, 24, 19};
    sobe(vetor3, 5);
    int esperado3[7] = {25, 24, 24, 22, 21, 23, 19};
    for(int i =0; i<7; i++){
        assert(vetor3[i] == esperado3[i]);
    }

    int vetor4[7] = {7, 6, 5, 4, 3, 2, 1};
    sobe(vetor4, 6);
    int esperado4[7] = {7, 6, 5, 4, 3, 2, 1};
    for(int i =0; i<7; i++){
        assert(vetor4[i] == esperado4[i]);
    }
}

void test_extrai_max(){
    int vetor[3] = {100, 80, 70};
    int tam = 3;
    int esperado[2] = {80, 70};
    extrai_max(vetor, &tam);
    for (int i = 0; i < 2; i++)
    {
        assert(vetor[i] == esperado[i]);
    }
    

    int vetor2[7] = {45, 34, 33, 29, 27, 25, 23};
    int tam2 = 7;
    int esperado2[6] = {34, 29, 33, 23, 27, 25};
    extrai_max(vetor2, &tam2);
    for (int i = 0; i < 6; i++)
    {
        assert(vetor2[i] == esperado2[i]);
    }
}

void test_altera_prioridade(){
    int max_size = 10;
    int entrada[10] = {100,62,30,50,60,25,20};
    int saida1[]    = {105,100,30,50,60,25,20};
    int saida2[]    = {100,60,30,50,1,25,20};
    int i;
    int tam = 7;
    
    altera_prioridade(entrada, 1, 105, tam);
    for(i=0;i<tam;i++){
        assert(entrada[i]==saida1[i]);
    }
    
    altera_prioridade(entrada,0,1,tam);
    for(i=0;i<tam;i++){
        assert(entrada[i]==saida2[i]);
    }
}

void test_insere_elemento(){
    int max_size = 10;
    int entrada[10] = {100,62,30,50,60,25,20};
    int saida1[]   = {100,70,30,62,60,25,20,50};
    int saida2[]   = {150,100,30,70,60,25,20,50,62};
    int i;
    int tam = 7;
    
    assert(insere_elemento(entrada, 70, &tam, max_size)==EXIT_SUCCESS);
    assert(tam == 8);
    for (i=0;i<tam;i++){
        assert(entrada[i]==saida1[i]);
    }

    assert(insere_elemento(entrada, 150, &tam, max_size)==EXIT_SUCCESS);
    assert(tam == 9);
    for (i=0;i<tam;i++){
        assert(entrada[i]==saida2[i]);
    }
}

void test_heapsort(){
    int entrada[]   = {100,62,30,50,60,25,20};
    int saida[]     = {20 ,25,30,50,60,62,100};
    int tam = sizeof(entrada)/sizeof(entrada[0]);
    int i;

    heapsort(entrada,tam);
    for (i=0;i<tam;i++){
        assert(entrada[i]==saida[i]);
    }
}

int main(void){
    test_pai();
    test_filho_esq();
    test_filho_dir();
    test_desce();
    test_constroi_heap();
    test_sobe();
    test_extrai_max();
    test_altera_prioridade();
    
    return EXIT_SUCCESS;
}