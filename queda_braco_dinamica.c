#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include<math.h>

typedef struct NO {
    int force_inicial;
    int force_current;
    int lutadorID;
    struct NO *prox; /**criando um ponteiro para a estrutura adjacente**/
}NO;

typedef struct FILA{
    /**criando um ponteiro para o topo**/
    int controleLutador;
    NO *inicio;
    NO *fim;
}FILA;

void inicializaFila(FILA *f){
    f -> inicio = NULL;
    f -> fim = NULL;
    f -> controleLutador = 0;
}

void enfileira(int new_force_inicial, FILA *f){
    NO *ptr = (NO*) malloc(sizeof(NO));

    if (ptr == NULL){ /**Verifica se a alocacao foi realizada**/
        printf("Erro de alocacao do novo no.\n");
        return;
    }else{
        ptr -> force_inicial = new_force_inicial;
        ptr -> force_current = new_force_inicial;
        f -> controleLutador = f -> controleLutador + 1;
        ptr -> lutadorID = f -> controleLutador;
        ptr -> prox = NULL;

        /**caso fila vazia**/
        if(f->inicio == NULL){
            f->inicio = ptr;
        } else{
            f -> fim -> prox = ptr; /** adiciona no fim da fila **/
        }
        f->fim = ptr;
        return;
    }
}

int desenfileira(FILA *f){
    NO *ptr = f->inicio;
    int get_force_current;

    if (ptr == NULL){
        printf ("\nFila está vazia.");
        return;
    }else{
        get_force_current = ptr -> force_current;
        ptr -> prox = NULL;
        free(ptr);
        if (f -> inicio == NULL){
            f -> fim == NULL;
        }
    }
    return get_force_current;
}

void imprimeFila (FILA * f){
    NO *ptr = f->inicio;

    if (ptr == NULL){
        printf ("Fila esta vazia.\n");
        return;
    }else{
        printf("Rodada(FILA) atual: ");
        while(ptr != NULL){
            printf("%d(%d) ", ptr -> lutadorID, ptr -> force_current);
            ptr = ptr -> prox;
        }
    }
    printf("\n\n");
}

int inicializaCampeonato(FILA *f, int flag_dado){
    int N;
    int K;
    int force;
    int force_max;
    time_t t;
    int i;

    if (flag_dado == 0){
        printf("Forneca o valor de N e K:\n");
        scanf("%d %d", &N, &K);
        for(i = 0; i < pow(2, N); i++){
            scanf("%d",&force);
            enfileira(force, f);
        }
    }
    else{
        N = 3;
        K = 10;
        force_max = 1000;
        printf("****************************************************************\n");
        printf("**                                                            **\n");
        printf("** Notacao: i(Force_max)                                      **\n");
        printf("**                                                            **\n");
        printf("**    Onde, i representa o i-esimo competidor                 **\n");
        printf("**           Force_max representa forca do i-esimo competidor **\n");
        printf("**                                                            **\n");
        printf("**                                                            **\n");
        printf("****************************************************************\n");
        srand((unsigned) time(&t));/* Intializes random number generator */
        for(i = 0; i < pow(2, N); i++){
            enfileira((1+ rand() %(force_max-1)), f);/* Generate random numbers from 1 to force_max */
        }
    }
    return K;
}

NO *lutaSimples (NO *startNO, NO *nextNO, int K){
    int competidor1; //armazena a forca corrente do primeiro competidor
    int competidor2; //armazena a forca corrente do segundo competidor
    NO *winnerNO;

    competidor1 = startNO -> force_current;
    competidor2 = nextNO -> force_current;

    if (competidor1 > competidor2){
        winnerNO = startNO;
        nextNO -> force_current = 0;
        startNO -> force_current = competidor1 - competidor2 + K;
        if (startNO -> force_current > startNO -> force_inicial){
            startNO -> force_current = startNO -> force_inicial;
        }
    }else{
        winnerNO = nextNO;
        startNO -> force_current = 0;
        nextNO -> force_current = competidor2 - competidor1 + K;
        if (nextNO -> force_current > nextNO -> force_inicial){
            nextNO -> force_current = nextNO -> force_inicial;
        }
    }
    return winnerNO;
}
NO *roundCampeonato(FILA *f, NO *startNO, int K){
    NO *nextNO;
    NO *winnerNO;

    nextNO = startNO -> prox;

    if (nextNO -> prox == NULL){    // condicao de saida da recurssao
        //obtendo no vencedor e avaliando quem sera o proximo no
        winnerNO = lutaSimples(startNO, nextNO, K);
        if(winnerNO == startNO){
            winnerNO -> prox = NULL;
            f -> fim = winnerNO;
        }else{
            if(winnerNO == nextNO && startNO == f->inicio){
                f -> inicio = winnerNO;
            }
        }
        return winnerNO;

    } else{
        //obtendo no vencedor e avaliando quem sera o proximo no
        winnerNO = lutaSimples(startNO, nextNO, K);
        winnerNO -> prox = roundCampeonato(f, nextNO -> prox, K);

        if (winnerNO == f-> inicio -> prox){
            f -> inicio = winnerNO;
        }
        //removendo no perdedor
        if(winnerNO == startNO){
            free(nextNO);
        }else{
            free(startNO);
        }
    }
    return winnerNO;
}

void fullCampeonato(FILA *f, int K){
    int i;
    while(f -> inicio != f -> fim){
        NO *auxNO = roundCampeonato(f, f -> inicio, K);
        imprimeFila(f);
    }
}

int main(){
    FILA *f1 = (FILA*) malloc(sizeof(FILA));
    int K;
    int flag_dado; //flag para inserir dado manualmente ou automaticamente

    if (f1 == NULL){
        printf("Erro de alocacao.\n");
        exit(-1);
    }else{
        flag_dado = 1; //se flag_dado = 0 os dados são iseridos na tela do executavel
        inicializaFila(f1);
        K = inicializaCampeonato(f1, flag_dado);
        imprimeFila(f1);
        fullCampeonato(f1, K);
//        NO *debugNO = roundCampeonato(f1, f1->inicio, K);
    }
    return 0;
}
