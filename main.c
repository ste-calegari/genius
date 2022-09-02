#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define FACIL 3000
#define MEDIO 2000
#define DIFICIL 1000

//RECORDS
struct jogador{
    char nome[5];
    int pontuacao;
};

void ler_recordes() {
    char ch;
    FILE *fp;
    int a;
    fp = fopen("RECORDES.txt", "r");
    printf("RANKING   NOMES    PONTOS\n\n");
    ch = fgetc(fp);
    while(ch != EOF){
        printf("%c", ch);
        ch = fgetc(fp);
    }

    do{
    printf("\n\n");
    printf("APERTE 0 PARA VOLTAR AO MENU\n");
    scanf("%i", &a);
    system("cls");
    }while(a != 0);
    system("cls");
    rewind(fp);
    fclose(fp);
}

void verificar_recordes(int pontos,struct jogador *j, struct jogador *p) {
    int i,posicao,k=0;
    FILE *fp;
    fp = fopen("RECORDES.txt", "r");
    for(i=1;i<=5;i++) {
        fscanf(fp, "%d        %s        %d\n", &posicao, j[i].nome, &j[i].pontuacao);
        p[k] = j[i];
        k++;
    }
    for(i=1;i<=5;i++) {
        if(pontos > j[i].pontuacao) {
            if(pontos>j[1].pontuacao){
                printf("\n\tVOCE BATEU O RECORDE DE PONTOS!!\n\n\t\t");
                printf("PARABENS");
            }
            printf("\n\n\tDIGITE UM NOME COM NO MAXIMO 4 CARACTERES\n\n\t");
            scanf("%s", j[0].nome);
            j[0].pontuacao = pontos;
            p[0] = j[i];
            j[i] = j[0];
            break;
        }
    }
    i++;
    k=0;
    for( ;i<=5;i++) {
        j[i] = p[k];
        k++;
    }
    fclose(fp);
    fp = fopen("RECORDES.txt", "w");
    printf("\n");
    for(i=1;i<=5;i++) {
        fprintf(fp,"%d        %s        %d\n", i, j[i].nome, j[i].pontuacao);
    }
    fclose(fp);
    system("cls");
    ler_recordes();
}

//FILA
typedef struct elemento {
    int dado;
    struct elemento *proximo;
} Elemento;

typedef struct fila {
    Elemento *inicio;
    Elemento *fim;
} Fila;

Fila *inicializaFila() { //INICIALIZA FILA
    Fila *f;
    f = (Fila *)malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

void colocaDado(int d, Fila *f) { //COLOCA DADO
    Elemento *novoDado;
    novoDado = (Elemento *)malloc(sizeof(Elemento));
    novoDado->dado = d;
    novoDado->proximo = NULL;
    if (f->inicio == NULL && f->fim == NULL)
    {
        f->fim = f->inicio = novoDado;
    }
    else
    {
        f->fim->proximo = novoDado;
        f->fim = novoDado;
    }
}

int retiraDado(Fila *f) { //RETIRA DADO
    int saida = f->inicio->dado;
    Elemento *retirado;
    retirado = (Elemento *)malloc(sizeof(Elemento));
    retirado = f->inicio;
    if (f->fim != f->inicio) {
        f->inicio = f->inicio->proximo;
    }
    else
    {
        f->fim = f->inicio = NULL;
    }
    free(retirado);
    return saida;
}

void imprimeFilaOriginal(Fila *f, int T) { //IMPRIME FILA ORIGINAL
    int tempo;
    Elemento *iterador;
    iterador = (Elemento *)malloc(sizeof(Elemento));
    iterador = f->inicio;
    Elemento *aux;
    aux = (Elemento *)malloc(sizeof(Elemento));
    aux = f->inicio;

    while (iterador != NULL) {
        printf("\n\tSEQUENCIA ORIGINAL\n\n");
        printf("\t%i\n",iterador->dado);
        tempo = clock();
        while(clock() - tempo < T);
        system("cls");
        iterador = iterador->proximo;
    }

    printf("\n\tSEQUENCIA ORIGINAL FINAL\n\n");
    while(aux!=NULL){
        printf("\t%i", aux->dado);
        aux=aux->proximo;
    }
	printf("\n");
}

void colocaDado_fO(Fila *fOriginal){ //COLOCA DADO NA FILA ORIGINAL
    int x;
    x=1+(rand()%4);
    colocaDado(x, fOriginal);
}

void lerDado_fJ (Fila *fJogador){ //COLOCA DADO NA FILA DO JOGADOR
    int y;
    scanf("%d", &y);
    colocaDado(y, fJogador);
}

int comparaFilas (Fila *fOriginal, Fila *fJogador){ //COMPARA AS DUAS FILAS
    Elemento *auxOriginal=fOriginal->inicio;
    Elemento *auxJogador=fJogador->inicio;
    int x;
    while(auxOriginal!=NULL&&auxJogador!=NULL){
        if(auxOriginal->dado==auxJogador->dado){
            x=0;
        }
        if(auxOriginal->dado!=auxJogador->dado){
            return 1;
        }
        auxOriginal=auxOriginal->proximo;
        auxJogador=auxJogador->proximo;
    }
    return x;
}

int tamanhoFila(Fila *f){ //PEGA TAMANHO FILA
    Elemento *aux;
    int tamanho=0;
    aux=f->inicio;
    while(aux!=NULL){
        tamanho++;
        aux=aux->proximo;
    }
    return tamanho;
}

void limparFila (Fila *f){ //LIMPA FILA
    while(f->fim!=NULL){
        retiraDado(f);
    }
}

//INTRUÇÕES
void intrucoes(){
    int a;
    printf("\n\t\t\tCOMO JOGAR\n\n\tEscolha a dificuldade!\n\tMemorize a sequencia de numeros!\n\tRepita a sequencia perfeitamente!\n\n\tQuanto mais partidas maior sua pontuacao!!\n");
    printf("");
    do{
    printf("\n\n");
    printf("APERTE 0 PARA VOLTAR AO MENU\n\n");
    scanf("%i", &a);
    system("cls");
    }while(a != 0);
}

//JOGO
int jogo(Fila *fOriginal, Fila *fJogador){ //JOGO -- RETORNA NÚMERO DE PARTIDAS
    int partidas=0, parada=0, tempo, T, escolha;
    printf("\n\tESCOLHA DIFICULDADE\n\n\t1)Facil\n\t2)Medio\n\t3)Dificil\n\n\t");
    scanf("%d", &escolha);
    switch(escolha){
        case(1):
            T=FACIL;
            break;
        case(2):
            T=MEDIO;
            break;
        case(3):
            T=DIFICIL;
            break;
    }

    tempo = clock();
    while(clock() - tempo < 2000);
    system("cls");

        while(parada!=1){
            colocaDado_fO(fOriginal);
            imprimeFilaOriginal(fOriginal, T);
            //esperar 3 segundos e apagar tudo

            tempo = clock();
            while(clock() - tempo < 3000);
            system("cls");

            printf("\n\tSEQUENCIA DO JOGADOR\n\n");
            for (int tamanho=0; tamanho<tamanhoFila(fOriginal); tamanho++){
                printf("\t");
                lerDado_fJ(fJogador);
            }
            parada=comparaFilas(fOriginal,fJogador);
            limparFila(fJogador);

            //fazer esperar o tempo e apagar tudo, 5 segundos.
            tempo = clock();
            while(clock() - tempo < 1000);
            system("cls");

            partidas++;
        }

    return partidas;
}

void Menu(Fila *fOriginal, Fila *fJogador){
    int escolha, x, tempo, pontos;
    struct jogador p[5],j[6];
    printf("\n\t\t\tGENIUS\n\n\t1)Instrucoes\n\t2)Jogar\n\t3)Records\n\nDigite 0 para sair\n\n\t");
    scanf("%d", &escolha);
    switch(escolha){
        case 1://COLOCAR INSTRUÇÕES
            tempo = clock();
            while(clock() - tempo < 1000);
            system("cls");
            intrucoes();
            limparFila(fOriginal);
            limparFila(fJogador);
            Menu(fOriginal,fJogador);
            break;

        case 2:
            tempo = clock();
            while(clock() - tempo < 1000);
            system("cls");
            x=jogo(fOriginal, fJogador);
            printf("\n\n\t\t GAME OVER\n\n\t\tPARTIDAS : %d\n",x-1);
            verificar_recordes(x-1, j, p);
            system("cls");
            limparFila(fOriginal);
            limparFila(fJogador);
            Menu(fOriginal,fJogador);
            break;

        case 3: //COLOCAR RECORDS
            tempo = clock();
            while(clock() - tempo < 1000);
            system("cls");
            ler_recordes();
            limparFila(fOriginal);
            limparFila(fJogador);
            Menu(fOriginal, fJogador);
            break;

        case 0:
            system("cls");
            exit(0);
            break;
    }

}

int main(void)
{
    srand(time(NULL));
    Fila *fOriginal = inicializaFila();
    Fila *fJogador = inicializaFila();
    Menu(fOriginal, fJogador);

    return 0;
}
