// CAMPO MINADO DO HIKIN E DO MARCIN;
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


struct campo{
    int bomba;
    int numero;
    int revelado;
};
// se a posição for numero == 0 && bomba == 0, esta posição está vazia, portanto, deve-se realizar a chamada recursiva.


int verifica_quantidade_de_bombas(int lin, int col, struct campo campo_minado[lin][col]){
    int x = 0;
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            if(campo_minado[i][j].bomba == 1){
                x++;
            }
        }
    }
    if(x == 40){
        return 1;
    }
    else{
        return 0;
    }
} // função para verificar se realmente há 40 bombas no campo, pois um laço (na função criar_campo_minado) com o condicional "i <= 40" pode gerar menos de 40//


void criar_campo(int lin, int col, struct campo campo_minado[lin][col]){
    srand((unsigned)time(NULL)); // gera uma semente aleatoria
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            campo_minado[i][j].bomba = 0;
            campo_minado[i][j].numero = 0;
            campo_minado[i][j].revelado = 0;
        }
        // serve para atribuir 0 em todas as posições do campo.
    }

    int lin_bomb, col_bomb;  // buffer que auxilía no armazenamento das posições das bombas.
    while(verifica_quantidade_de_bombas(lin, col, campo_minado) != 1){
        lin_bomb = rand()%10; // gera numero aleatorio de 0 a 9
        col_bomb = rand()%20;// gera numero aleatorio de 0 a 19
        campo_minado[lin_bomb][col_bomb].bomba = 1;
    }
} // função que reseta o campo minado e define as posições das bombas.


void gera_numeros(int lin, int col, struct campo campo_minado[lin][col]){
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            if(campo_minado[i][j].bomba == 1){
                for(int k = -1; k < 2; k++){
                    for(int n = -1; n < 2; n++){
                        if(((i+k) >= 0 && (j+n) >= 0)  && ((i+k) < lin && (j+n) < col)){
                            campo_minado[i+k][j+n].numero++;
                        }
                    }
                }
            }
        }
    }
}

void formata_campo(int lin, int col, struct campo campo_minado[lin][col]){
    char c = 'a';
    char caractere = '+';
    printf("     ");
    for(int i = 0; i < col; i++){
        printf ("%c     ", c++);
    }
    printf("\n");
    for(int i = 0; i < lin; i++){
        printf("%.2d ", i+1);
        for(int j = 0; j < col; j++){
            if(campo_minado[i][j].revelado == 0){
                caractere = '+';
                printf("| %c | ", caractere);
            }// printar casas nao reveladas
            else if(campo_minado[i][j].revelado == 1 && campo_minado[i][j].numero == 0 && campo_minado[i][j].bomba == 0){
                caractere = ' ';
                printf("| %c | ", caractere);
                // CHAMAR A FUNÇÃO RECURSIVA AQUI.
            }//printar casar vazias
            else if(campo_minado[i][j].revelado == 1 && campo_minado[i][j].bomba == 0 && campo_minado[i][j].numero > 0){
                printf("| %d | ", campo_minado[i][j].numero);
            }//printar numeros
            else if(campo_minado[i][j].bomba == 1){
                // EXIBIR A LOCALIZAÇÃO DE TODAS AS BOMBAS DO CAMPO, E FINALIZAR O JOGO.
            }
        }
        printf("\n");
    }
} // ordem de jogada: primeiro linha, depois coluna. Ex: 1 B / 7 R / 10 N.



int main(){
    
    int lin = 10, col = 20;
    struct campo campo_minado[lin][col];
    
    criar_campo(lin, col, campo_minado);
    gera_numeros(lin, col, campo_minado);
    int opcao = 0;
    printf("Seja Bem-vindo ao Campo Minado\n");
    while(opcao != 2){
        printf("Digite o número das opções a seguir:\n");
        printf("1.Tutorial\n");
        printf("2.Começar o Jogo\n");
        scanf("%d", &opcao);
        if(opcao == 1){
            printf("Tutorial: O campo do jogo iniciará com todas as casas estando não-reveladas, você deve revelar alguma casa, e acontecerá isso:\nse a posição escolhida for vazia, debloqueará em cascata várias posições vazias\nse a posição escolhida for um número n, isso significa que em volta daquela casa haverá n bombas\nse a opsição escolhida for uma bomba, você perde o jogo."); //turorial do jogo aqui
        }
    }
    opcao = 0;
    int jogar_linha = -1, jogar_coluna = -1; // essas variaveis sao para escolher a jogada revelar, o valor é -1 pois nao tem chance de ser uma casa com uma bomba ex: 0, 0
    while(campo_minado[jogar_linha][jogar_coluna].bomba != 1){
        printf("O que você deseja fazer?\n");
        printf("1.Revelar\n");
        printf("2.Pedir Ajuda\n");
        printf("3.Ver o tempo de jogo\n");
        scanf("%d", &opcao);
        if(opcao == 1){
            printf("Entre respectivamente com um Número e uma Letra(minúscula)");
            scanf("%d %c", &jogar_linha, &jogar_coluna);
            jogar_linha = jogar_linha - 1; // -1 pois a matriz começa a contar sua linha em 0
            jogar_coluna = jogar_coluna - 97; // - 97 pois é o valor da diferença entre caracters minusculos e inteiros na tabela asc;
        }
    }
    
    return 0;
}