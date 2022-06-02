#include <stdio.h>

typedef struct {
    char descricao[50];
    int preco;
    int quantidade;
}produto;

void main (){

    produto k;
    
    FILE *f = fopen("myfile1.bin", "rb");
    
    while (fread (&k, sizeof(k), 1, f)){
    
        printf("descricao: %s\n", k.descricao);

        printf("preco: %d\n", k.preco);

        printf("quantidade: %d\n", k.quantidade);
    }

    fclose(f);
}