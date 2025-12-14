#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Biblioteca necessária para funções de string (strcpy, strcmp)

// Define uma constante para o comprimento máximo que cada texto pode ter.
#define MAX_STR_LEN 50 //Tamanho máximo de cada string/texto



// === PARTE 1 : LISTA ESTATICA(VETOR DE STRINGS)
/*=============================================================
 Uma lista estática é uma estrutra de dados de tamanho fixo,
implementada usndo um vetor(ou array).
Toda memória necessária é alocada de uma só vez, quando a variável é declarada.
===============================================================
*/ 

// Define uma constante para o número  máximo de itens que nossa lista pode conter.
#define TAM_MAX 10 // Define o numero maximo de itens na lista estática

// Estrutura que representa a lista estática
typedef struct {
    char dados[TAM_MAX][MAX_STR_LEN];
    int quantidade;
} ListaEstatica;

// Funções da Lista Estática

// Esta função prepara a lista para ser usada.
// Ela simplesmente define o contador quantidade como 0, indicando que a lista está vazia.
// Recebemos um ponteiro(*lista) para modificar a variável original passada para a função
void inicializarListaEstatica(ListaEstatica *lista);

void inserirListaEstatica(ListaEstatica *lista, const char* texto);
void removerListaEstatica(ListaEstatica *lista, const char* texto);
void listarListaEstatica(const ListaEstatica *lista);


// === PARTE 2 : LISTA ENCADEADA(VETOR DE STRINGS)
/*=============================================================
Uma lista encadeada é uma estrutura de dados de tamanho dinâmico.
Ela é composta por "nós" separados na memória,
onde cada nó contém um dado e um ponteiro que "aponta" para o próximo nó da sequência.
===============================================================
*/ 


// Estrutura de nó(cada elemento da lista)
// - char* dado: Este é o ponteiro. Ele nao armazena o texto em si, mas sim o endereço
// de memória onde o texto está guardado.
// Isso é muito flexível, pois cada texto pode ter um tamanho diferente, e alocamos apenas
// a memoria necessaria para cada um.
// - struct No *proximo: Este é o ponteiro que cria a "ligação". Ele aramazena o endereço do próximo nó na lista.
// O ultimo nó da lista terá este ponteiro apontando para NULL.
typedef struct No{
    char* dado;        //Ponteiro para a string (alocada dinamicamente)
    struct No *proximo;
} No;


// Isso é um atalho. Em vez de escrever No* sempre que quisermos nos referir a nossa lista, podemos simplesmente usar
// A "lista" em si é apenas um ponteiro para o primeiro nó(a "cabeça" da lista).
typedef No* ListaEncadeada;

// Funções da Lista Encadeada
void inicializadorListaEncadeada(ListaEncadeada *lista);

void inserirListaEncadeada(ListaEncadeada *lista, const char* texto);
void removerListaEncadeada(ListaEncadeada *lista, const char* texto);
void listarListaEncadeada(const ListaEncadeada lista);
void liberarListaEncadeada(ListaEncadeada *lista); // Função nova para limpar a memória


// ----------------------------------------------
// -------------- FUNÇÃO PRINCIPAL --------------
// ----------------------------------------------

void menuListaEstatica();
void menuListaEncadeada();

int main() {
    int opcao;
    do {
        printf("\n--- MANIPULAÇÃO DE LISTA(TEXTO) ---\n");
        printf("1. Lista Estatica\n");
        printf("2. Lista Encadeada\n");
        printf("0. Sair do Programa\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            menuListaEstatica();
            break;
        
        case 2:
            menuListaEncadeada();
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            break;
        }

    } while (opcao != 0);

    return 0;
}


// ------------------------------------------------
// -  IMPLEMENTAÇÃO DAS FUNÇÕES - LISTA ESTÁTICA  -
// ------------------------------------------------

void inicializarListaEstatica(ListaEstatica *lista) {
    lista->quantidade = 0;
}

void inserirListaEstatica(ListaEstatica *lista, const char* texto) {
    // Primeiro, ela verifica se lista->quantdade já atingiu TAM_MAX.
    // Se Sim, a list está cheia e a função retorna.
    if (lista->quantidade == TAM_MAX) {
        printf("Erro: Lista cheia! Não é possíve");
        return;
    }
    // A inserção ocorre na primeira "linha" livro da matriz.
    // Para strings, não podemos fazer "lista->dados[i] = texto;", porque em C não se pode atribuir vetores/setrings ....
    // Precisamos copiar o conteúdo da string para a posição correta na nossa matriz dados.
    strcpy(lista->dados[lista->quantidade], texto);
    // Após a copia, lista->quantidade é incrementado, pois agora temos mais um item na lista.
    lista->quantidade++;
    printf("Texto \"%s\" inserido com sucesso. \n", texto);
}

void removerListaEstatica(ListaEstatica *lista, const char* texto) {
    int i, pos = -1;
    // Para compara strings, usamos strcmp(). Retorna 0 se forem iguais.
    // A função percorre os itens em uso na lista (de 0 até quantidade).
    // Para comparar strings, usamos strcmp(string1, string2).
    // Essa função retorna 0 se as trings forem identicas. Se encontrar, quarda a posição (pos) e para o loop.
    for (i = 0; i < lista->quantidade; i++) {
        if (strcmp(lista->dados[i], texto) == 0) {
            pos = i;
            break;
        }
    }
    
    // Tratamento de erro: Se o loop terminar e pos continuar -1, o item não foi encontrado.
    if (pos == -1) {
        printf("Erro: Texto \"%s\" não encontrado na lista.\n", texto);
        return;
    }

    // Fechar a Lacuna: Se removemos um item do meio da lista, criamos um "buraco".
    // Para preenche lo, movemos todos os itens subsequentes uma posição para a esquerda.
    // O loop for começa na posição do item removido e copia cada item i+1 para a posição i.
    // Deslocar os elementos posteriores para a esquerda usando strcpy.
    for (i = pos;i < lista->quantidade - 1; i++) {
        strcpy(lista->dados[i], lista->dados[i+ 1]);
    }

    // Atualização do Contador: finalmente, quantidade é decrementado para refletir que a lista tem um item a menos.
    lista->quantidade--;
    printf("Texto \"%s\" removido com sucesso.\n", texto);

}

void listarListaEstatica(const ListaEstatica *lista) {
    if (lista->quantidade == 0) {
        printf("A lista estatica está vazia.\n");
        return;
    }
    printf("Itens da Lista Estatica: [");
    for (int i = 0; i < lista->quantidade; i++) {
        printf("\"%s\" ", lista->dados[i]);
    }
    printf("]\n");

}


// -------------------------------------------------
// -  IMPLEMENTAÇÃO DAS FUNÇÕES - LISTA ENCADEADA  -
// -------------------------------------------------

// Uma lista encadeada vazia é representada por um ponteiro de cabeça que aponta para NULL.
// Esta função simplesmente atribui NULL ao ponteiro que representa nossa lista.
void inicializarListaEncadeada(ListaEncadeada *lista) {
    *lista = NULL;
}


void inserirListaEncadeada(ListaEncadeada *lista, const char* texto) {
    // 1. Alocar memória para o NOVO NÓ
    // Alocação do Nó: malloc(sizeof(No)) pede ao sistema operacional memória suficiente para um nó
    // novoNo gora aponta para essa memoria.
    No* novoNo = (No*) malloc(sizeof(No));

    if (novoNo == NULL) {
        printf("Erro: Falha na Alocação de memoria para o no\n");
        return;
    }

    // 2. Alocar memória para a STRING DENTRO DO NÓ
    // strlen(texto) + 1 para incluir o caractere nulo '\0' no final
    // alocação da String: malloc(strlen(texto) + 1) aloca memória para o texto.
    // strlen conta os caratecteres. e o +1 é vital para o caractere nulo (\0) que  finaliza toda string em C.
    // novoNo->dado agora aponta para este espaço.
    novoNo->dado = (char*) malloc(strlen(texto) + 1);

    if (novoNo->dado == NULL) {
        printf("Erro: Falha na alocação de memoria para o texto.\n");
        free(novoNo); // Libera o nó que já foi alocado
        return;
    }

    // 3. Copiar o texto para a memória recém- alocada
    // Cópia do texto: srtcpy copia o texto de entrada para a área de memória recém-alocada apontada pro novoNo->dado ....
    strcpy(novoNo->dado, texto);

    // 4. Ligar o novo nó á lista
    // O ponteiro próximo do novo nó passa a apontar para o que era o antigo priemrio nó da lista.
    novoNo->proximo = *lista;
    // A cabeça da lista (*lista) é atualizada para apontar para o novoNo, o novoNo é agora o primeiro item.
    *lista = novoNo;

    printf("Text \"%s\" inserido com sucesso. \n", texto);
}


void removerListaEncadeada(ListaEncadeada *lista, const char* texto) {
    // Usamos dois ponteiros, atual e anterior, para percorrer a lista. atual avança, e atenrior o segue
    // Paramos quando atual apnta par ao nó a ser removido.
    No *atual = *lista;
    No *anterior = NULL;

    while (atual != NULL && strcmp(atual->dado, texto) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Erro: Texto \"%s\" não encontrado a lista.\n", texto);
        return;
    }

    // Se o nó a ser removido for o primeiro ( anterior == NULL), a cabeça da lista (*lista pasa a ser o segundo (atu....))
    // Se o estiver no meio/fim, o ponteiro proximo do nó anterior "pula" o  atual e aponta par ao atual->proximo.
    if (anterior == NULL) {
        *lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    
    // Liberação de memória (MUITO IMPORTANTE): para evitar vazaento de memória (memory leak), precisamos devolver......
    // Primeiro, free(atual->dado): Libera a memopria que foi usada para quardar o texto.
    // Depois, free(atual): libera a memoria do proprio nó. Se fizessemos o contario perderiamo a referencia para a ......

    // Antes de liberar o nó, precisamos liberar a string DENTRO dele.
    free(atual->dado);
    // AGORA podemos liberar o nó.
    free(atual);
    printf("Texto \"%s\" removido com sucesso.\n", texto);

}

void listarListaEncadeada(const ListaEncadeada lista) {
    No *temp = lista;
    if (temp == NULL) {
        printf("A lista encadeada esta vazia.\n");
        return;
    }
    printf("Itens da Lista encadeada: [ ");
    while (temp != NULL) {
        printf("\"%s\" ", temp->dado); // Usar %s para imprimir
        temp = temp->proximo;
    }
    printf("]\n");

}
    

void liberarListaEncadeada(ListaEncadeada *lista) {
    No *atual = *lista;
    No *proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual->dado); //Liberar a string
    }
    
}

// ============================ MENUS ==========================


void menuListaEstatica() {
    ListaEstatica lista;
    inicializarListaEstatica(&lista);
    int opcao;
    char texto[MAX_STR_LEN];
    
    do {
        printf("\n----- MENU LISTA ESTÁTICA -----\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();
        
        switch (opcao) {
            case 1:
                printf("Digite o texto: ");
                fgets(texto, MAX_STR_LEN, stdin);
                texto[strcspn(texto, "\n")] = '\0';
                inserirListaEstatica(&lista, texto);
                break;
            
            case 2:
                printf("Digite o texto a remover: ");
                fgets(texto, MAX_STR_LEN, stdin);
                texto[strcspn(texto, "\n")] = '\0';
                removerListaEstatica(&lista, texto);
                break;

            case 3:
                listarListaEstatica(&lista);
                break;

            case 0:
                printf("Voltando...\n");
                break;

            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);
}

void menuListaEncadeada() {
    ListaEncadeada lista;
    inicializarListaEncadeada(&lista);
    int opcao;
    char texto[MAX_STR_LEN];
    
    do {
        printf("\n----- MENU LISTA ENCADEADA -----\n");   
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();
        
        switch (opcao) {
            case 1:
                printf("Digite o texto: ");
                fgets(texto, MAX_STR_LEN, stdin);
                texto[strcspn(texto, "\n")] = '\0';
                inserirListaEncadeada(&lista, texto);
                break;
            
            case 2:
                printf("Digite o texto a remover: ");
                fgets(texto, MAX_STR_LEN, stdin);
                texto[strcspn(texto, "\n")] = '\0';
                removerListaEncadeada(&lista, texto);
                break;

            case 3:
                listarListaEncadeada(lista);
                break;

            case 0:
                printf("Voltando...\n");
                break;

            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);
    
    liberarListaEncadeada(&lista);
}