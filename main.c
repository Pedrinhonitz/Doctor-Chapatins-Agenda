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
    // Date aniversario;
    // char email[41];
    // char telefone[16];
    struct _No *esquerda;
    struct _No *direita;
    int altura;
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



No *novoNo(char nomeContato) {
    // No *no = (no *)
    //     malloc(sizeof(No));
    No *no = malloc(sizeof(No));
    
    no->nome = nomeContato;
    // no->aniversario = aniversarioContato;
    // no->email = emailContanto;
    // no->telefone = telefoneContato;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 1;

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

No *rotacaoDireita(No *x) {
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

No *inserirNo(No *no, char nomeContato) {
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

No *apagaNo(No *no, char nomeContato) {
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
          
          // strcpy() MUDAR
          no->nome = aux->nome;

          no->esquerda = apagaNo(no->direita, aux->nome);
      }
    }

    if (no == NULL) {
        return no;
    }

/* --------------- */
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
        printf("%c ", no->nome);
        printPreOrder(no->esquerda);
        printPreOrder(no->direita);
    }
}

void printInOrder(No *no) {
    if (no != NULL) {
        printPreOrder(no->esquerda);
        printf("%c ", no->nome);
        printPreOrder(no->direita);
    }
}

void printPosOrder(No *no) {
    if (no != NULL) {
        printPreOrder(no->esquerda);
        printPreOrder(no->direita);
        printf("%c ", no->nome);
    }
}

int main() {
    No *no = NULL;

    int tamanho;

    char nomeContato[31];

    scanf("%d", &tamanho);

    for(int i=0; i<tamanho; i++) {
        scanf("%c", &nomeContato);
        no = inserirNo(no, nomeContato);
    }
    printf("\n");

    // printPreOrder(root);
    // root = deleteNode(root, 3);

    // printf("\nAfter deletion: ");
    
    printf("PRE ORDER: \n");
    printPreOrder(no);
    printf("\n");
    printf("\n");

    printf("IN ORDER: \n");
    printInOrder(no);
    printf("\n");
    printf("\n");

    printf("POS ORDER: \n");
    printPosOrder(no);
    printf("\n");
    printf("\n");

  return 0;
}