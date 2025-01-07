#include "fila_dinamica.c"

/*O código abaixo demonstra o funcionamento da lista após a implementacao do nó-cabeca.
Além das funcoes de inserir e excluir, tambem a funcao de exibir foi adaptada.
*/

int main(){
    printf("Inicializando fila:\n");
    FILA fila;
    inicializarFila(&fila);
    printf("Adicionando 3 elementos:\n");
    REGISTRO adicionar;
    for (int i = 0; i < 3; i++){
        printf("\nDigite o %dº numero a ser adicionado: ", i+1);
        scanf("%d", &adicionar.chave);
        inserirNaFila(&fila, adicionar);
    }
    exibirFila(&fila);
    printf("\nExcluindo um elemento.\n");
    REGISTRO excluido;
    excluirDaFila(&fila, &excluido);
    exibirFila(&fila);
}