#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include<math.h>
#define N 10

struct info{
    int valor;
    int prox;
};

typedef struct info tipoInfo;

struct listaEE {

    int tamanhoLista;
    int primeiro;
    int ultimo;
    // 0 ocupado, 1 livre
    int posLivre[N];
    tipoInfo elemento[N];
};

typedef struct listaEE tipoListaEE;

void inicializaLista (tipoListaEE *listaAux){

    // Inicializa elementos da lista
    listaAux->tamanhoLista = 0;
    listaAux->primeiro = -1;
    listaAux->ultimo = -1;

    int i;
    for (i=0; i<N; i++){
        listaAux->elemento[i].valor = 0;
        listaAux->elemento[i].prox = -1;
        listaAux-> posLivre[i] = 1;
    }
}

int insereElementoFinal (tipoListaEE *listaAux, int x){
    int i, j = 0;
    int posicao = 0;
    if (listaAux->tamanhoLista == N){
        return 1;
    }
    else{
        while(listaAux->posLivre[posicao] == 0)
            posicao++;

        if (listaAux->tamanhoLista == 0)
            listaAux->primeiro = posicao;
        else
            listaAux->elemento[listaAux->ultimo].prox = posicao;

        listaAux->elemento[posicao].valor = x;
        listaAux->elemento[posicao].prox = -1;
        listaAux->tamanhoLista++;
        listaAux->ultimo = posicao;
        listaAux->posLivre[posicao] = 0;
        return 0;
    }
}

void retiraElemento (tipoListaEE *listaAux, int x){
    int posicao = listaAux->primeiro, j, posante = -1;

    while(posicao != listaAux->ultimo && listaAux->elemento[posicao].valor != x) {
        posante = posicao;
        posicao = listaAux->elemento[posicao].prox;
    }

    if (listaAux->elemento[posicao].valor == x){

        if (listaAux->tamanhoLista == 1){
            listaAux->elemento[posicao].valor = 0;
            listaAux->posLivre[posicao] = 1;
            listaAux->ultimo = -1;
            listaAux->primeiro = -1;
            listaAux->tamanhoLista--;
        }
        else if(listaAux->primeiro == posicao){
            listaAux->primeiro = listaAux->elemento[posicao].prox;
            listaAux->elemento[posicao].prox = -1;
            listaAux->elemento[posicao].valor = 0;
            listaAux->posLivre[posicao] = 1;
            listaAux->tamanhoLista--;
        }
        else if(listaAux->ultimo == posicao){
            listaAux->ultimo = posante;
            listaAux->elemento[posante].prox = -1;
            listaAux->elemento[posicao].valor = 0;
            listaAux->elemento[posicao].prox = -1;
            listaAux->posLivre[posicao] = 1;
            listaAux->tamanhoLista--;
        }
        else if (listaAux->ultimo != posicao && listaAux->primeiro != posicao){
            listaAux->elemento[posante].prox = listaAux->elemento[posicao].prox;
            listaAux->elemento[posicao].valor = 0;
            listaAux->elemento[posicao].prox = -1;
            listaAux->posLivre[posicao] = 1;
            listaAux->tamanhoLista--;
        }
    }
    else{
        printf("\nnao existe");
    }
}

int proxPosLivre(tipoListaEE *listaAux){

    int i;
    for (i=0;i < N;i++){
        if (listaAux->posLivre[i] == 1)
        return i;
    }
    return -1;
}

void ordenar (tipoListaEE *listaAux){
    int flag=1, apontador,index_ant;
    tipoInfo current, next;

    while (flag == 1) {
        apontador = listaAux->primeiro;
        flag = 0;

        while (apontador != listaAux->ultimo){

            if (apontador == listaAux->primeiro){
                current = listaAux->elemento[apontador];
                next = listaAux->elemento[current.prox];

                if (current.valor > next.valor){
                    if(current.prox == listaAux->ultimo)
                        listaAux->ultimo = apontador;

                    listaAux->primeiro = current.prox;
                    listaAux->elemento[apontador].prox = next.prox;
                    listaAux->elemento[current.prox].prox = apontador;
                    index_ant = current.prox;
                    flag = 1;
                }
                else{
                    index_ant = apontador;
                    apontador = current.prox;
                }

            }
            else{
                current = listaAux->elemento[apontador];
                next = listaAux->elemento[current.prox];
                if (current.valor > next.valor){

                    if(current.prox == listaAux->ultimo)
                        listaAux->ultimo = apontador;

                    listaAux->elemento[index_ant].prox = current.prox;
                    index_ant = current.prox;
                    listaAux->elemento[apontador].prox = next.prox;
                    listaAux->elemento[current.prox].prox = apontador;
                    flag = 1;
                }
                else {
                    index_ant = apontador;
                    apontador = current.prox;
                }
            }
        }
    }
}

void imprimeLista(tipoListaEE *listaAux){
    int i;
    tipoInfo current;
    printf("\n");
    i = listaAux->primeiro;
    if (i != -1){
        if (listaAux->primeiro == listaAux->ultimo){
            current = listaAux->elemento[i];
            printf ("%d ", current.valor);
        }
        else{
            while (i != listaAux->ultimo){
                current = listaAux->elemento[i];
                printf("%d ", current.valor);
                i = listaAux->elemento[i].prox;
            }
            printf("%d ", listaAux->elemento[i].valor);
        }
        printf("\n");
    }
    //else
        //printf("lista vazia");
}

int main(){

    tipoListaEE o;
    inicializaLista (&o);

    int L, i = 1;
    int j = 0, k = 0, l = 0, m = 0, n = 0, u = 0, p = 0, q = 0;

    scanf("%d", &L);

        while(i <= L && L <= 100){

            int acao, RA;
            scanf("%d %d", &acao, &RA);

            if (RA <= 146000 && RA >= 66000){

                if (acao == 1){

                    if (insereElementoFinal(&o, RA) == 0){
                        if(RA >= 66000 && RA < 76000)
                            j++;

                        if(RA >= 76000 && RA < 86000)
                            k++;

                        if(RA >= 86000 && RA < 96000)
                            l++;

                        if(RA >= 96000 && RA < 106000)
                            m++;

                        if(RA >= 106000 && RA < 116000)
                            n++;

                        if(RA >= 116000 && RA < 126000)
                            u++;

                        if(RA >= 126000 && RA < 136000)
                            p++;

                        if(RA >= 136000 && RA < 146000)
                            q++;
                        ordenar(&o);
                        imprimeLista(&o);
                    }
                    else{
                        printf("\nlista cheia");
                        imprimeLista(&o);
                    }
                }
                if (acao == 2){
                    retiraElemento(&o, RA);
                    ordenar(&o);
                    imprimeLista(&o);
                }
                i++;
            }
            else
                i++;
        }
    printf("\n2011: %d\n", j);
    printf("2012: %d\n", k);
    printf("2013: %d\n", l);
    printf("2014: %d\n", m);
    printf("2015: %d\n", n);
    printf("2016: %d\n", u);
    printf("2017: %d\n", p);
    printf("2018: %d\n", q);
    return 0;

/*7
1 86102
1 66104
1 136105
1 96106
2 66104
2 66105
1 106100*/
}
