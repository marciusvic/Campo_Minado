#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

struct campo{
    int bomba;
    int numero;
    int revelado;
    int marcado;
    };

void criar_campo_minado(int lin, int col, struct campo campo_minado[lin][col]){
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            campo_minado[i][j].bomba = 0;
            campo_minado[i][j].numero = 0;
            campo_minado[i][j].revelado = 0;
            campo_minado[i][j].marcado = 0;
        }
    }
} // essa função irá montar o campo minado, com todas as posições de bombas ja determinadas

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
            if(campo_minado[i][j].revelado == 0){
                printf("* ");
            }
        }
        printf("\n");
    }
    //essa função ira imprimir o campo minado para o usuario
    //ainda sera mudada as condições do if adcionando caso tenha marcações, bombas, ou numero o
}

int main(){
    
    int lin = 10, col = 20;
    
    struct campo campo_minado[lin][col];
    
    criar_campo_minado(lin, col, campo_minado);
    
    print_mina(lin, col, campo_minado);

    return 0;
}