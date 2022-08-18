#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct _Data {
    int dia;
    int mes;
    int ano;
}typedef Data;

struct _No {
    char nome[31];
    Data nascimento;
    char email[41];
    char telefone[16];
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



No *novoNo(char nomeContato[31], Data nascimentoContato, char emailContanto[41], char telefoneContato[16]) {
    No *no = (No*)malloc(sizeof(No));

    strcpy(no->nome, nomeContato); 
    no->nascimento.dia = nascimentoContato.dia;
    no->nascimento.mes = nascimentoContato.mes;
    no->nascimento.ano = nascimentoContato.ano;
    strcpy(no->email, emailContanto);
    strcpy(no->telefone, telefoneContato);
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

No *inserirNo(No *no, char nomeContato[31], Data nascimentoContato, char emailContanto[41], char telefoneContato[16]) {
    if(no == NULL) {
        return (novoNo(nomeContato, nascimentoContato, emailContanto, telefoneContato));
    }

    if((strcmp(nomeContato, no->nome)) < 0) {
        no->esquerda = inserirNo(no->esquerda, nomeContato, nascimentoContato, emailContanto, telefoneContato);
    }else if((strcmp(nomeContato, no->nome)) > 0) {
        no->direita = inserirNo(no->direita, nomeContato, nascimentoContato, emailContanto, telefoneContato);
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

          strcpy(no->nome, aux->nome); 

          no->esquerda = apagaNo(no->direita, aux->nome);
      }
    }

    if(no == NULL) {
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

No *buscarNo(No *no, char nomeContato[31]){
    while (no)
    {
        if (strcmp(nomeContato, no->nome) > 0)
        {
            no = no->direita;
        }
        else if (strcmp(nomeContato, no->nome) < 0)
        {
            no = no->esquerda;
        }else{
            return no;
        }
    }
    return NULL;
}

No *AtualizarNo(No *no, char nomeAntigoContato[31], char nomeContato[31], Data nascimento, char emailContato[41], char telefoneContanto[16]) {
    int flag = 1;
     if(strcmp(no->nome, nomeAntigoContato) > 0) {
        no = no->direita;
        while(flag) {
            if(strcmp(no->nome, nomeAntigoContato) == 0) {
                flag = 0;
                strcpy(no->nome, nomeContato);
                no->nascimento.dia = nascimento.dia;
                no->nascimento.mes = nascimento.mes;
                no->nascimento.ano = nascimento.ano;
                strcpy(no->email, emailContato);
                strcpy(no->telefone, telefoneContanto);
                return no;
            }else {
                printf("Nome Não Encontrado!\n");
            }
        }
    }else if(strcmp(no->nome, nomeAntigoContato) < 0) {
        no = no->esquerda;
        while(flag) {
            if(strcmp(no->nome, nomeAntigoContato) == 0) {
                flag = 0;
                strcpy(no->nome, nomeContato);
                no->nascimento.dia = nascimento.dia;
                no->nascimento.mes = nascimento.mes;
                no->nascimento.ano = nascimento.ano;
                strcpy(no->email, emailContato);
                strcpy(no->telefone, telefoneContanto);
                return no;
            }else {
                printf("Nome Não Encontrado!\n");
            }
        }
    }else {
        printf("Nome Não Encontrado!\n");
    }


}


// void criaArquivo(FILE *arquivo) {
//     arquivo = fopen("database.txt", "r");

//     if(arquivo != NULL) {
//         return;
//     }else {
//         arquivo = fopen("database.txt","a");
//         fclose(arquivo);
//     }

// }

// void escreverNoArquivo(FILE *arquivo, char nomeContato[31], Data nascimento, char emailContato[41], char telefone[16]) {
//     arquivo = fopen("database.txt", "a");
//     fprintf(arquivo, "%s %d/%d/%d %s %s", nomeContato, nascimento.dia, nascimento.mes, nascimento.ano, emailContato, telefone);
//     // fwrite();
//     fclose(arquivo);
// }

// void gravaNoArquivoEstruturaDaArqvore(No *no, FILE* arquivo) { 
//     if(no != NULL) {
//         fprintf(arquivo,"%s %d/%d/%d %s %s",no->nome, no->nascimento.dia, no->nascimento.mes, no->nascimento.ano, no->email, no->telefone);
//         gravaNoArquivoEstruturaDaArqvore(no->esquerda, arquivo);
//         gravaNoArquivoEstruturaDaArqvore(no->direita, arquivo);
//     }else{
//         printf("Erro ao salvar estrutura!");
//     }
// }


// void atualizaArquivo(No *no) { 
//     FILE *arquivo;

//     arquivo = fopen("database.txt", "w");
//     gravaNoArquivoEstruturaDaArqvore(no, arquivo);
//     fclose(arquivo);
// }




void salvarArquivo(No *no) {
    FILE *arq = fopen("database.txt", "wb");
    int result;
    int quantidade;

    if(arq) {
        fprintf(arq, "%d\n", quantidade);
        result = fwrite(no, sizeof(No), quantidade, arq);
        printf("Numero de Baitchês gravados: %d\n", result);
        fclose(arq);
    }else {
        printf("Problemas para criar o arquivo\n");
   	    return;
    }
}

// // Esse Caralho não ta funcionando ainda

void lerArquivo(No *no) {
    FILE *arq = fopen("database.txt", "rb");
    
    printf("A\n");
    int quantidade;

    if(arq) {
        printf("B\n");
        fscanf(arq, "%d\n", &quantidade);
        fread(&no, sizeof(No), quantidade, arq);
        // printf("\nNome: %s\nData: %d/%d/%d\n", no->nome, no->nascimento.dia, no->nascimento.mes, no->nascimento.ano);
        fclose(arq);
    }else {
        printf("Problemas para abrir o arquivo\n");
   	    return;
    }
}


// void ler(){
//     No *no;
//     FILE *file = fopen("database.batman", "rb");

//     if(file){
//         while(!feof(file)){
//             if(fread(&no, sizeof(No), 1, file))
//                 printf("\nNome: %s\nData: %d/%d/%d\n", no->nome, no->nascimento.dia, no->nascimento.mes, no->nascimento.ano);
//         }
//         fclose(file);
//     }
//     else
//         printf("\nErro ao abrir arquivo!\n");
// }

void printPreOrder(No *no) {
    if(no != NULL) {
        printf("%s\n", no->nome);
        printf("%d/%d/%d\n", no->nascimento.dia, no->nascimento.mes, no->nascimento.ano);
        printf("%s\n", no->email);
        printf("%s\n", no->telefone);
        printPreOrder(no->esquerda);
        printPreOrder(no->direita);
    }
}

void printInOrder(No *no) {
    if(no != NULL) {
        printInOrder(no->esquerda);
        printf("%s\n", no->nome);
        printf("%d/%d/%d\n", no->nascimento.dia, no->nascimento.mes, no->nascimento.ano);
        printf("%s\n", no->email);
        printf("%s\n", no->telefone);
        printInOrder(no->direita);
    }
}

void printPosOrder(No *no) {
    if(no != NULL) {
        printPosOrder(no->esquerda);
        printPosOrder(no->direita);
        printf("%s\n", no->nome);
        printf("%d/%d/%d\n", no->nascimento.dia, no->nascimento.mes, no->nascimento.ano);
        printf("%s\n", no->email);
        printf("%s\n", no->telefone);
    }
}

void menuSistema() {
    printf("--------------------------\n");
    printf("0 -> Sair da Agenda\n");
    printf("--------------------------\n");
    printf("1 -> Inserir Contatos\n");
    printf("--------------------------\n");
    printf("2 -> Deletar Contatos\n");
    printf("--------------------------\n");
    printf("3 -> Mostrar Contatos\n");
    printf("--------------------------\n");
    printf("4 -> Buscar Contatos\n");
    printf("--------------------------\n");
    printf("5 -> Alterar Contatos\n");
    printf("--------------------------\n");
    printf("6 -> Salvar Contatos\n");
    printf("--------------------------\n");
}

void menuMostrar() {
    printf("--------------------------\n");
    printf("0 -> Voltar ao Menu\n");
    printf("--------------------------\n");
    printf("1 -> Mostrar Pre Order\n");
    printf("--------------------------\n");
    printf("2 -> Mostrar In Order\n");
    printf("--------------------------\n");
    printf("3 -> Mostrar Pos Order\n");
    printf("--------------------------\n");
}

int main() {
    No *no = NULL;

    // FILE *arquivo;
    // criaArquivo(arquivo);

    char nomeContato[31];
    char nomeAntigoContato[31];
    Data nascimentoContato;
    char emailContato[41];
    char telefoneContato[16];

    int opt, optMostrar;
    int flag = 1;
    int flagMostrar = 1;
    
    // lerArquivo(no);

    while(flag) {

        menuSistema();

        printf("Opção: ");
        scanf("%d", &opt);
        printf("\n");

        switch(opt) {

            case 0:
                // system("clear");
                printf("Saiu da Agenda!\n");
                
                flag = 0;
                // atualizaArquivo(no);
                break;
            
            case 1:
                // system("clear");
                printf("Inserir Contato\n");
                
                printf("Digite o Nome: ");
                scanf("%s", &nomeContato);
                printf("\n");
                // -------------------
                printf("Digite a Data de Nascimento: ");
                scanf("%d/%d/%d", &nascimentoContato.dia, &nascimentoContato.mes, &nascimentoContato.ano);
                printf("\n");
                //-------------------------
                printf("Digite o Email: ");
                scanf("%s", &emailContato);
                printf("\n");
                // -------------------
                printf("Digite o Telefone: ");
                scanf("%s", &telefoneContato);
                printf("\n");
                // -------------------
                no = inserirNo(no, nomeContato, nascimentoContato, emailContato, telefoneContato);
                // escreverNoArquivo(arquivo, nomeContato, nascimentoContato,emailContato, telefoneContato);
                break;
            
            case 2:
                // system("clear");
                printf("Deletar Contato\n");
                
                printf("Digite o Nome: ");
                scanf("%s", &nomeContato);
                printf("\n");
                
                no = apagaNo(no, nomeContato);
                // atualizaArquivo(no);
                break;

            case 3:
                flagMostrar = 1;
                // system("clear");
                while(flagMostrar) {
                    menuMostrar();
                    scanf("%d", &optMostrar);
                    switch (optMostrar) {
                    case 0:
                        flagMostrar = 0;
                        break;
                    
                    case 1:
                        // system("clear");
                        printf("Mostrar Pre Order!\n");
                        printPreOrder(no);
                        break;

                    case 2:
                        // system("clear");
                        printf("Mostrar In Order!\n");
                        printInOrder(no);
                        break;

                    case 3:
                        // system("clear");
                        printf("Mostrar Pos Order!\n");
                        printPosOrder(no);
                        break;

                    default:
                        // system("clear");
                        printf("Comando Invalido!\n");
                        break;
                    }
                }
                break;
            case 4:
                // system("clear");
                printf("Digite o nome da pessoa: ");
                scanf("%s", &nomeContato);
                No *resultadoBusca = buscarNo(no, nomeContato);
                //-------------------------
                printf("\nResultado da busca");
                printf("\n");
                //-------------------------
                if (resultadoBusca)
                {
                    printf("Nome: %s\n", resultadoBusca->nome);
                    printf("Idade: %d/%d/%d\n", resultadoBusca->nascimento.dia, resultadoBusca->nascimento.mes, resultadoBusca->nascimento.ano);
                    printf("E-mail: %s\n", resultadoBusca->email);
                    printf("Telefone: %s\n", resultadoBusca->telefone);
                }else
                    printf("!!Nenhum nome encontrado!!\n");
                    printf("\n");
                //-------------------------
                break;

            case 5:
                // system("clear");
                // printf("Ler Arquivo!\n");
                // ler();
                // lerArquivo(no);
                printf("Atualiza Conatato!\n");
                printf("Digite o Contato que deseja Atualizar: ");
                scanf("%s", &nomeAntigoContato);
                printf("\n");

                no = apagaNo(no, nomeAntigoContato);

                printf("Digite o Nome: ");
                scanf("%s", &nomeContato);
                printf("\n");
                // -------------------
                printf("Digite a Data de Nascimento: ");
                scanf("%d/%d/%d", &nascimentoContato.dia, &nascimentoContato.mes, &nascimentoContato.ano);
                printf("\n");
                //-------------------------
                printf("Digite o Email: ");
                scanf("%s", &emailContato);
                printf("\n");
                // -------------------
                printf("Digite o Telefone: ");
                scanf("%s", &telefoneContato);
                printf("\n");
                // -------------------
                
                no = inserirNo(no, nomeContato, nascimentoContato, emailContato, telefoneContato);

                // no = AtualizarNo(no, nomeAntigoContato, nomeContato, nascimentoContato, emailContato, telefoneContato);

                break;

            case 6:
                // system("clear");
                printf("Salvar Arquivo!\n");
                salvarArquivo(no);
                break;

            case 7:
                printf("Ler Arquivo!\n");
                lerArquivo(no);
                break;

            default:
                printf("Comando Invalido!\n");
                break;
        }
    }

    return 0;
}