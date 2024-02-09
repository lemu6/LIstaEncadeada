
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 100
 
//Estrutura da lista que será criada
typedef struct lista {
    char *nome;
    struct lista *proximo;
} Dados;
 
//Funções para manusear os dados (irão retornar dados)
Dados *inicia_dados  (char *nome);
Dados *insere_dados  (Dados *dados, char *nome);
Dados *delbusca_dados(Dados *dados, char *chave);
Dados *deleta_dados  (Dados *dados, int nTipo);
int   checa_vazio    (Dados *dados);
int aux=0;

//Inicializando os dados da lista
Dados *principal = NULL;
//Criando uma lista vazia
void criavazia(void){

    char *nome;
    //Alocando dados para uma String
    nome = (char *)malloc(TAM);
    //Lendo String Nome
    fprintf(stdout, "\n\nDigite o Nome: \n----> ");
    scanf("%s", nome);
    fprintf(stdout, "\n");
    free(principal);
    principal = inicia_dados(nome);
}
//Iniciando os dados da lista vazia
Dados *inicia_dados(char *nome) {
    Dados *novo;
    //Alocando memória para a posição atual da lista
    novo = (Dados *)malloc(sizeof(Dados));
    //Lançando os dados lidos
    novo->nome = (char *)malloc(strlen(nome)+1);
    strncpy(novo->nome, nome, strlen(nome)+1);
    //Apontando para a próxima posição da lista
    novo->proximo = NULL;
    return novo;
}
//Inserindo no início da lista
void insereinicio(void){
    char *nome;
    //Reservando espaço para String
    nome = (char *)malloc(TAM);
    //Armazenando String Nome
    fprintf(stdout, "\n\nDigite o Nome: \n----> ");
    scanf("%s", nome);
    //Lançando dados no ínicio da lista
    principal = insere_dados(principal, nome);
}
//Inserindo dados recebidos
Dados *insere_dados(Dados *dados, char *nome) {
    Dados *inicio;
    //Alocando memória para a posição atual
    inicio = (Dados *)malloc(sizeof(Dados));
    //Lançando os dados lidos
    inicio->nome = (char *)malloc(strlen(nome)+1);
    strncpy(inicio->nome, nome, strlen(nome)+1);
    //O próximo valor aponta para a lista já existente
    inicio->proximo = dados;
    return inicio;
}
//Inserção de dados no final de uma lista
void inserefim(void) {
    char *nome;
    //Alocação de espaço para String Nome
    nome = (char *)malloc(TAM);
    //Armazenando String Nome
    fprintf(stdout, "\n\nDigite o Nome: \n----> ");
    scanf("%s", nome);
    fprintf(stdout, "\n");
    //Criando listas auxiliares
    Dados *final,*aux;
    //Alocando dados para a posição final da lista
    final = (Dados *)malloc(sizeof(Dados));
    //Setando o Nome
    final->nome = (char *)malloc(strlen(nome)+1);
    strncpy(final->nome, nome, strlen(nome)+1);
    //A proxima posição será Nulo
    final->proximo=NULL;
    //A lista auxiliar será igual a Principal
    aux=principal;
    //Enquanto o próximo de auxiliar não for Nulo
    while(aux->proximo!=NULL){
        aux=aux->proximo;
    }
    //O último valor, será Nulo, e depois apontando para
    //o Final
    aux->proximo=NULL;
    aux->proximo=final;
}
//Função que testa se a lista está vazia
void listavazia(void){
    if (principal == NULL)
        fprintf(stdout, "\n\nLista esta Vazia!\n\n ");
    else
        fprintf(stdout, "\n\nLista nao esta Vazia!\n\n ");
    getchar();
}
//Exibindo dados da lista
void exibe(void) {
    //Se não estiver vazio, exibe os dados
    if (!checa_vazio(principal))
        exibe_dados(principal);
}
//Exibindo todos os dados do menu
void exibe_dados(Dados *dados) {
    fprintf(stdout, "Cadastro:\n\n");
    fprintf(stdout, "------------------------\n");
    //Exibindo todos os valores da lista
    for (; dados != NULL; dados = dados->proximo) {
        fprintf(stdout, "Nome: %s\n", dados->nome);
        fprintf(stdout, "------------------------\n");
    }
    getchar();
}
//Exibindo o tamanho da lista
void exibetam(void){
    //Se não estiver vazio, exibe os dados
    if (!checa_vazio(principal))
        exibe_tamanho(principal);
}
//Exibindo o tamanho total (bytes) e quantid
void exibe_tamanho(Dados *nova){
  int aux=0, tamanho=0;
  fprintf(stdout, "\n------------------------\n");
  //Correndo todos os valores da Lista
  for (; nova != NULL; nova = nova->proximo) {
    aux++;
    tamanho+=sizeof(nova);
  }
  fprintf(stdout, "Total de Elementos: %d\nTamanho Total: %d bytes\n",aux,tamanho);
  fprintf(stdout, "------------------------\n");
  getchar();
}

//Deletando valor buscado
void delbusca(void) {
    char *chave;
    //Se não estiver vazio
    if (!checa_vazio(principal)) {
        chave = (char *)malloc(TAM);
        //Armazenando o valor digitado
        fprintf(stdout, "Digite o nome para buscar: \n--> ");
        scanf("%s", chave);
        //Deletando a chave buscada
        principal = delbusca_dados(principal, chave);
    }
}
 
//Deletando os valores buscados
Dados *delbusca_dados(Dados *dados, char *chave) {
    int achou=0,cont=0;
    Dados *juntou, *aux, *nova=dados;        
 
    //Correndo a lista e verificando se encontrou a string buscada, se sim, aumenta o contador e seta a variável de busca
    for (; nova != NULL; nova = nova->proximo) {
        if (strcmp(chave, nova->nome) == 0) {
            achou=1;
            cont++;
        }
    }
 
    //Se encontrou a busca
    if(achou==1){
        int ind=0;
        //Correndo a lista
        for(ind=0;ind<cont;ind++){
            //Se encontrou na primeira casa apaga a primeira casa
            if(strcmp(chave,dados->nome)==0){
                aux=dados;
                dados=dados->proximo;
                free(aux);
            }
            //Senão, procura até encontrar
            else{
                aux=dados;
                //Posiciona na frente do encontro para exclusão
                while(strcmp(chave,aux->nome)!=0){
                    aux=aux->proximo;
                }
 
                juntou=dados;
                //Enquanto o auxiliar juntou for diferente do posicionado para exclusão
                while(juntou->proximo!=aux){
                    juntou=juntou->proximo;
                }
                //Aponta para o próximo valor válido
                juntou->proximo=aux->proximo;
 
                free(aux);
            }
        }
        fprintf(stdout, "Excluido.\n");
    }
    else
        fprintf(stdout, "Nenhum resultado encontrado.\n");
 
    getchar();
    return dados;
}
//Função que busca os dados
void busca(void) {
    char *chave;
    //Senão estiver vazio a lista
    if (!checa_vazio(principal)) {
        chave = (char *)malloc(TAM);
        //Lendo o nome que será buscado
        fprintf(stdout, "Digite o nome para buscar: \n--> ");
        scanf("%s", chave);
        //chamando a função que irá procurar o nome
        busca_dados(principal, chave);
    }
}
//Percorre cada ponta da lista verificando busca
void busca_dados(Dados *dados, char *chave) {

    int achou = 0;
    fprintf(stdout, "Cadastro:\n\n");
    //Percorrendo todas as posições
    for (; dados != NULL; dados = dados->proximo) {
        //Se encontrou, mostra os dados
        if (strcmp(chave, dados->nome) == 0) {
            fprintf(stdout, "------------------------\n");
            fprintf(stdout, "Nome: %s\n", dados->nome);
            fprintf(stdout, "------------------------\n");
            achou++;
        }
    }
    //Mostrando o resultado da busca
    if (achou == 0)
        fprintf(stdout, "Nenhum resultado encontrado.\n");
    else
        fprintf(stdout, "Foram encontrado(s) %d registro(s).\n", achou);
    	aux++;
 
    getchar();
}
//Função que testa se a lista esta vazia
int checa_vazio(Dados *dados) {
    //Se a lista estiver vazia
    if (dados == NULL) {
            fprintf(stdout, "Lista vazia!\n");
            getchar();
            return 1;
    } else
            return 0;
}
//     Função Principal
int main(void) {
    char op;
    int chave=0;
    do {
        fprintf(stdout, "Escolha uma opcao: \n");
        fprintf(stdout, "1 - Criar lista vazia\n");
        if(chave==1){
            fprintf(stdout, "2 - Inserir no Inicio\n");
            fprintf(stdout, "3 - Inserir no Fim \n");
        }
        fprintf(stdout, "4 - Lista Vazia...\n");
        if(chave==1){
            fprintf(stdout, "5 - Exibir toda a Lista\n");
            fprintf(stdout, "6 - Exibir o tamanho da Lista\n");
            fprintf(stdout, "7 - Eliminar elemento buscado\n");
            fprintf(stdout, "8 - Busca Dados\n");
        }
        fprintf(stdout, "9 - Sair\n\n");
        fprintf(stdout, "Resposta: ");
        scanf("%c", &op);
        if((chave==0)&&((op!='1')&&(op!='d')&&(op!='4')))
            op='z';
        switch(op) {
            //Criando lista vazia
            case '1':
                chave=1;
                criavazia();
                break;
            //Inserindo no início
            case '2':
                insereinicio();
                break;
            //Inserindo no final
            case '3':
                //Se a lista não estiver vazia
                if(principal!=NULL){
                    inserefim();
                }
                //senão inclui no inicio
                else{
                    insereinicio();
                }
                break;
            //Checando se a lista está vazia
            case '4':
                listavazia();
                break;
            //Exibindo todos elementos
            case '5':
                exibe();
                break;
            //Exibindo tamanho da lista
            case '6':
                exibetam();
                break;
            //Deleta elemento buscado
            case '7':
                delbusca();
                break;
            //Buscando elementos
            case '8':
                busca();
                break;
            //Saindo e finalizando o programa
            case '9':
                exit(0);
                break;
            default:
                fprintf(stderr,"Digite uma opcao valida!\n");
                getchar();
                break;
        }
        getchar();
    }
    while (op > 0);
    return 0;
}