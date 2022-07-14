#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct campo{
    int bomba;
    int numero;
    int revelado;
    };
    // se a posição for numero == 0 && bomba == 0, essa posição está vazia
    
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

void criar_campo_minado(int lin, int col, struct campo campo_minado[lin][col]){
    srand((unsigned)time(NULL)); // semente aleatoria
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            campo_minado[i][j].bomba = 0;
            campo_minado[i][j].numero = 0;
            campo_minado[i][j].revelado = 0;
        }
    }
    int lin_bomb, col_bomb;
    for (int i = 0; verifica_quantidade_de_bombas(lin, col, campo_minado) != 1; i++){
            lin_bomb = rand()%10; // gera numero aleatorio de 0 a 9
            col_bomb = rand()%20;// gera numero aleatorio de 0 a 19
            campo_minado[lin_bomb][col_bomb].bomba = 1;
        }
    } // essa função irá montar o campo minado, com todas as posições de bombas ja determinadas

void gerar_casas_numeros(int lin, int col, struct campo campo_minado[lin][col]){
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            if(campo_minado[i][j].bomba == 1){
                for(int k = -1; k < 2; k++){
                    for(int n = -1; n < 2; n++){
                        if(((i+k) >= 0 && (j+n) >= 0)  && ((i+k) <lin && (j+n) <col)){
                            campo_minado[i+k][j+n].numero++;
                        }
                    }
                }
                //campo_minado[i][j].numero--;
            }
        }
    }
}

void print_mina(int lin, int col, struct campo campo_minado[lin][col]){
    char c = 'a';
    printf("   ");
    for(int i = 0; i < col; i++){
        printf ("%c ", c++);
    }
    printf("\n");
    for(int i = 0; i < lin; i++){
        printf("%02d ", i+1);
        for(int j = 0; j < col; j++){
            if(campo_minado[i][j].revelado == 0 /* campo_minado[i][j].bomba == 0*/){
                printf("* ");
            }
            /*if(campo_minado[i][j].bomba == 1){
                printf("o ");
            }* fins de teste*/
        }
        printf("\n");
    }
    //essa função ira imprimir o campo minado para o usuario
    //ainda sera mudada as condições do if adcionando caso tenha marcações, bombas, ou numero
    //implementar para caso campo_minado[][].bomba == 1 && campo_minado[][].revelado == 0 && campo_minado[][].numero > 0
}

 

int main(){
    
    int lin = 10, col = 20;
    
    struct campo campo_minado[lin][col];
    
    criar_campo_minado(lin, col, campo_minado);
    
    print_mina(lin, col, campo_minado);
    
    /*int x = 0;
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            if(campo_minado[i][j].bomba == 1){
                x++;
            }
        }
    }
    
    printf("\n%d", x);*/
    
    
    
    return 0;
}