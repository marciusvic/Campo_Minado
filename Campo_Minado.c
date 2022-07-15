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
        // Serve para atribuir 0 em todas as posições do campo.
    }

    int lin_bomb, col_bomb;  // Buffer que auxilía no armazenamento das posições das bombas.
    while(verifica_quantidade_de_bombas(lin, col, campo_minado) != 1){          // {Alteração} (1)
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

/*int escolheu_bomba(int lin, int col, struct campo campo_minado[lin][col], ){

}*/

void formata_campo(int lin, int col, struct campo campo_minado[lin][col]){          // {NEW} (1)
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
} // Ordem de jogada: primeiro linha, depois coluna. Ex: 1 B / 7 R / 10 N.



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
    //formata_campo(lin, col, campo_minado);
    

    
    
    return 0;
}

