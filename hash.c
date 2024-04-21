#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAXSIZE 5
#define MAXCHAR 10

typedef struct _hash
{
    char key[MAXCHAR];
    char valor[MAXCHAR];
} elemento;

typedef struct _table
{
    elemento Table[MAXSIZE];
    int tam;
} hash;

void inicializa(hash *Tabela)
{
    for (int i = 0; i < MAXSIZE; i++)
    {
        Tabela->Table[i].key[0] = '\0';
        Tabela->Table[i].valor[0] = '\0';
    }
    Tabela->tam = 0;
}

void print_tabela(hash *Tabela){
    for(int i=0;i<MAXSIZE;i++){
        printf("\"%s\" ", Tabela->Table[i].valor);
    }
    printf("\n");
}

int h(char *key)
{
    int tam = strlen(key);
    int total = 0;

    for (int i = 0; i < tam; i++)
    {
        total += key[i];
    }

    return total;
}

int insere(hash *Tabela, char *key)
{
    int v_hash = h(key);
    int pos = v_hash % MAXSIZE;
    int comeco = pos;

    if (((Tabela->tam) + 1) == MAXSIZE)
    {
        free(key);
        return EXIT_FAILURE;
    }
    else
    {
        while (Tabela->Table[pos].valor[0] != '\0' && strcmp(Tabela->Table[pos].valor, "*") != 0)
        {
            pos = (pos + 1) % MAXSIZE;

            if (pos == comeco)
                return EXIT_FAILURE;
        }

        strcpy(Tabela->Table[pos].valor, key);
        strcpy(Tabela->Table[pos].key, key);
        Tabela->tam+=1;

        return EXIT_SUCCESS;
    }
}

int busca(hash *Tabela, char *key)
{
    int pos = h(key) % MAXSIZE;
    int primeiro = pos;

    while (Tabela->Table[pos].valor[0] != '\0')
    {
        if(strcmp(Tabela->Table[pos].valor, key) == 0)
            return EXIT_SUCCESS;

        pos = (pos + 1) % MAXSIZE;
    }

    return EXIT_FAILURE;
}

int remove_elemento(hash *Tabela, char *key){
    int pos = h(key) % MAXSIZE;

    while(Tabela->Table[pos].valor[0] != '\0'){
        if (strcmp(Tabela->Table[pos].key, key) == 0){
            strcpy(Tabela->Table[pos].key, "*");
            strcpy(Tabela->Table[pos].valor, "*");
            Tabela->tam-=1;
            return EXIT_SUCCESS;
        }
        pos = (pos+1) % MAXSIZE;
    }

    return EXIT_FAILURE;
}

int main(void){
    hash tabela;
    inicializa(&tabela);
    
    insere(&tabela, "abc");
    print_tabela(&tabela);

    insere(&tabela, "bc");
    print_tabela(&tabela);

    insere(&tabela, "bbc");
    print_tabela(&tabela);

    insere(&tabela, "fbc");
    print_tabela(&tabela);

    remove_elemento(&tabela, "abc");
    print_tabela(&tabela);

    printf("%d\n", busca(&tabela, "fbc"));
    printf("%d\n", busca(&tabela, "bcd"));

    remove_elemento(&tabela, "bbc");
    print_tabela(&tabela);

	return EXIT_SUCCESS;
}