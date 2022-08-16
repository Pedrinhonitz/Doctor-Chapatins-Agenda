#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// struct _Date {
//     int dia;
//     int mes;
//     int ano;
// }typedef Date;

struct _No {
    char nome[31];
    int altura;
    struct _No *esquerda;
    struct _No *direita;
};

typedef struct _No No;

int max(int x, int y) {
    if(x > y) {
        return x;    
    }else {
        return y;
    }
}

int alturaArvore(No *tamanho) {
    if (tamanho == NULL) {
        return 0;
    }

    return tamanho->altura;
}



No *novoNo(char nomeContato[31]) {
    No *no = (No*)malloc(sizeof(No));

    strcpy(no->nome, nomeContato); // O erro que tava dando do valor modificavel, é porque na struct a gente ta usando char e pra modificar precisa usar strcpy
    no->altura = 1;
    no->esquerda = NULL;
    no->direita = NULL;

    return (no);
}

No *rotacaoDireita(No *y) {
    No *x = y->esquerda;
    No *aux = x->direita;

    x->direita = y;
    y->esquerda = aux;

    y->altura = max(alturaArvore(y->esquerda), alturaArvore(y->direita)) + 1;
    x->altura = max(alturaArvore(x->esquerda), alturaArvore(x->direita)) + 1;

    return x;
}

No *rotacaoEsquerda(No *x) { 
    No *y = x->direita;
    No *aux = y->esquerda;

    y->esquerda = x;
    x->direita = aux;

    x->altura = max(alturaArvore(x->esquerda), alturaArvore(x->direita)) + 1;
    y->altura = max(alturaArvore(y->esquerda), alturaArvore(y->direita)) + 1;

    return y;
}

int verificaBalanceamento(No *altura) {
    if (altura == NULL){
        return 0;
    }
      
    return alturaArvore(altura->esquerda) - alturaArvore(altura->direita);
}

No *inserirNo(No *no, char nomeContato[31]) {
    if(no == NULL) {
        return (novoNo(nomeContato));
    }

    if((strcmp(nomeContato, no->nome)) < 0) {
        no->esquerda = inserirNo(no->esquerda, nomeContato);
    }else if((strcmp(nomeContato, no->nome)) > 0) {
        no->direita = inserirNo(no->direita, nomeContato);
    }else {
      return no;
    }

    no->altura = 1 + max(alturaArvore(no->esquerda), alturaArvore(no->direita));

    int balanceamento = verificaBalanceamento(no);

    if((balanceamento > 1) && (strcmp(nomeContato, no->esquerda->nome) < 0)) {
        return rotacaoDireita(no);
    }

    if((balanceamento < -1) && (strcmp(nomeContato, no->direita->nome) > 0)) {
        return rotacaoEsquerda(no);
    }

    if((balanceamento > 1) && (strcmp(nomeContato, no->esquerda->nome) < 0)) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    } 
    if((balanceamento < -1) && (strcmp(nomeContato, no->direita->nome) > 0)) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

No *menorNo(No *no) {
    No *aux = no;

    while(aux->esquerda != NULL) {
        aux = aux->esquerda;
    }

    return aux;
}

No *apagaNo(No *no, char nomeContato[31]) {
    if (no == NULL) {
        return no;
    }

    if(strcmp(nomeContato, no->nome) < 0) {
        no->esquerda = apagaNo(no->esquerda, nomeContato);
    
    }else if(strcmp(nomeContato, no->nome) > 0) {
        no->direita = apagaNo(no->direita, nomeContato);
    
    }else {
    
      if((no->esquerda == NULL) || (no->direita == NULL)) {
          No *aux = no->esquerda ? no->esquerda : no->direita;

          if(aux == NULL) {
              aux = no;
              no = NULL;
          }else
              *no = *aux;
              free(aux);

      }else {
          No *aux = menorNo(no->direita);

          strcpy(no->nome, aux->nome); //tava dando erro, coloquei strcpy

          no->esquerda = apagaNo(no->direita, aux->nome);
      }
    }

    if (no == NULL) {
        return no;
    }

    no->altura = 1 + max(alturaArvore(no->esquerda), alturaArvore(no->direita));

    int balancemento = verificaBalanceamento(no);
    
    if((balancemento > 1) && (verificaBalanceamento(no->esquerda)>= 0)) {
        return rotacaoDireita(no);
    }

    if((balancemento > 1) && (verificaBalanceamento(no->esquerda) < 0)) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    if((balancemento < -1) && (verificaBalanceamento(no->direita) <= 0)) {
        return rotacaoEsquerda(no);
    }

    if((balancemento < -1) && (verificaBalanceamento(no->direita) > 0)) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    return no;
}

void printPreOrder(No *no) {
    if (no != NULL) {
        printf("%s\n", no->nome);
        printPreOrder(no->esquerda);
        printPreOrder(no->direita);
    }
}

void printInOrder(No *no) {
    if (no != NULL) {
        printPreOrder(no->esquerda);
        printf("%s\n", no->nome);
        printPreOrder(no->direita);
    }
}

void printPosOrder(No *no) {
    if (no != NULL) {
        printPreOrder(no->esquerda);
        printPreOrder(no->direita);
        printf("%s\n", no->nome);
    }
}

void menuSistema() {
    printf("--------------------------\n");
    printf("0 -> Sair da Agenda\n");
    printf("--------------------------\n");
    printf("1 -> Inserir Contato\n");
    printf("--------------------------\n");
    printf("2 -> Deletar Contato\n");
    printf("--------------------------\n");
    printf("3 -> Atualizar Contato\n");
    printf("--------------------------\n");
    printf("4 -> Buscar Contato\n");
    printf("--------------------------\n");
    printf("5 -> Salvar Contato\n");
    printf("--------------------------\n");
}


int main() {
    No *no = NULL;

    char nomeContato[30];
    int opt;

    menuSistema();


    printf("Opção: ");
    scanf("%d", &opt);
    printf("\n");
//    __fpurge(stdin);

    // root = deleteNode(root, 3);
    for(int i=0; i<10; i++) {
        printf("Digite o Nome: ");
        scanf("%s", &nomeContato);
        printf("\n");
        no = inserirNo(no, nomeContato);
    }
    
    // printf("PRE ORDER: \n");
    // printPreOrder(no);
    // printf("\n");
    // printf("\n");

    printf("IN ORDER: \n");
    printInOrder(no);
    printf("\n");
    // printf("\n");

    // printf("POS ORDER: \n");
    // printPosOrder(no);
    // printf("\n");
    // printf("\n");

  return 0;
}