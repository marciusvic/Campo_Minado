// CAMPO MINADO DO HIKIN E DO MARCIN;
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int bomba;
    int numero;
    int revelado;
}campo;
// se a posição for numero == 0 && bomba == 0, esta posição está vazia, portanto, deve-se realizar a chamada recursiva.


int verifica_quantidade_de_bombas(int lin, int col, campo campo_minado[lin][col]){
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


void criar_campo(int lin, int col, campo campo_minado[lin][col]){
    srand((unsigned)time(NULL)); // gera uma semente aleatoria
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            campo_minado[i][j].bomba = 0;
            campo_minado[i][j].numero = 0;
            campo_minado[i][j].revelado = 0;
        }
        // atribui 0 em todas as posições do campo.
    }

    int lin_bomb, col_bomb;  // buffer que auxilía no armazenamento das posições das bombas.
    while(verifica_quantidade_de_bombas(lin, col, campo_minado) != 1){
        lin_bomb = rand()%10; // gera numero aleatorio de 0 a 9
        col_bomb = rand()%20;// gera numero aleatorio de 0 a 19
        if(lin_bomb != 0 && col_bomb!= 0){
            campo_minado[lin_bomb][col_bomb].bomba = 1;
        }
    }
} // função que reseta o campo minado e define as posições das bombas.


void gera_numeros(int lin, int col, campo campo_minado[lin][col]){
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            if(campo_minado[i][j].bomba == 1){
                for(int k = -1; k < 2; k++){
                    for(int n = -1; n < 2; n++){
                        if(((i+k) >= 0 && (j+n) >= 0) && ((i+k) < lin && (j+n) < col)){
                            campo_minado[i+k][j+n].numero++;
                        }
                    }
                }
            }
        }
    }
}


void formata_campo(int lin, int col, campo campo_minado[lin][col]){
    char c = 'a';
    char caractere = '-';
    printf("       ");
    for(int i = 0; i < col; i++){
        printf ("%c   ", c++);
    }
    printf("\n\n");
    for(int i = 0; i < lin; i++){
        printf("%.2d   |", i+1);
        for(int j = 0; j < col; j++){
            if(campo_minado[i][j].revelado == 0){
                caractere = '-';
                printf(" %c |", caractere);
            }// printar casas nao reveladas
            else if(campo_minado[i][j].revelado == 1 && campo_minado[i][j].numero == 0 && campo_minado[i][j].bomba == 0){
                caractere = ' ';
                printf(" %c |", caractere);
            }// printar casas vazias já reveladas
            else if(campo_minado[i][j].revelado == 1 && campo_minado[i][j].bomba == 0 && campo_minado[i][j].numero > 0){
                printf(" %d |", campo_minado[i][j].numero);
            }// printar numeros
            else if(campo_minado[i][j].bomba == 1 && campo_minado[i][j].revelado == 1){
                caractere = 'X';
                printf(" %c |", caractere);
            }
        }
        printf("\n");
    }
    printf("\n");
} // ordem de jogada: primeiro linha, depois coluna. Ex: b1 / r7 / n10.


void revelar(int jogar_linha, int jogar_coluna, int lin, int col, campo campo_minado[lin][col]){
    // Casos base
    if((jogar_linha < 0 || jogar_linha >= lin) || (jogar_coluna < 0 || jogar_coluna >= col)){     // Garante que o programa não tente revelar posições inexistentes
        return;   // (>= lin e >= col por que o campo começa no 0, então o limite é sempre lin -1 e col -1)
    }
    if(campo_minado[jogar_linha][jogar_coluna].numero > 0){
        campo_minado[jogar_linha][jogar_coluna].revelado = 1;     // Revela a célula que contém o número, e retorna;
        return;
    }
    if(campo_minado[jogar_linha][jogar_coluna].revelado == 1){    // Igonora células já reveladas;
        return;
    }

    campo_minado[jogar_linha][jogar_coluna].revelado = 1;
    revelar(jogar_linha + 1, jogar_coluna, lin, col, campo_minado);  // baixo
    revelar(jogar_linha - 1, jogar_coluna, lin, col, campo_minado);  // cima
    revelar(jogar_linha, jogar_coluna + 1, lin, col, campo_minado);  // direita
    revelar(jogar_linha, jogar_coluna - 1, lin, col, campo_minado);  // esquerda
    revelar(jogar_linha + 1, jogar_coluna - 1, lin, col, campo_minado);  // diagonal inferior esquerda
    revelar(jogar_linha + 1, jogar_coluna + 1, lin, col, campo_minado);  // diagonal inferior direita
    revelar(jogar_linha - 1, jogar_coluna + 1, lin, col, campo_minado);  // diagonal superior direita
    revelar(jogar_linha - 1, jogar_coluna - 1, lin, col, campo_minado);  // diagonal superior esquerda

}


void kabum(int lin, int col, campo campo_minado[lin][col]){
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            if(campo_minado[i][j].bomba == 1){
                campo_minado[i][j].revelado = 1;
            }
        }
    }
}


int vitoria(int lin, int col, campo campo_minado[lin][col]){
    int verificador = 0;
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            if(campo_minado[i][j].revelado == 0 && campo_minado[i][j].bomba == 0){
                verificador = 1;
            }
        }
    }
    if(verificador == 0){
        return 1;
    } else{
        return 0;
    }
}


void dica(int lin, int col, campo campo_minado[lin][col], int verifica){
    int contador = 0;  // Servem pra contar e pra verificar :D
    int bolean = 0;
    char aux;
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            if(campo_minado[i][j].revelado == 1 && campo_minado[i][j].numero == verifica){
                for(int k = -1; k < 2; k++){
                    for(int n = -1; n < 2; n++){
                        if(campo_minado[i+k][j+n].revelado == 0){
                            contador++;
                        }
                    }
                }
            }
            if(contador - verifica > 1){
                bolean = 1;
                aux = j + '0';
                aux = aux + 49;
                printf("\nEscolher uma das casas ao redor de %c%d seria uma boa jogada.\n\n", aux, (i + 1));
                return;
            }
            else if(contador - verifica > 2){
                bolean = 1;
                aux = j + '0';
                aux = aux + 49;
                printf("\nEscolher uma das casas ao redor de %c%d seria uma boa jogada.\n\n", aux, (i + 1));
                return;
            }
        }
    }
    if(bolean == 0){
        dica(lin, col, campo_minado, verifica+1);
    }
}


void bot(int lin, int col, campo campo_minado[lin][col], int *lin_bot, int *col_bot){
    int numero_revelado = 1; // inicial do que ele procurar primeiro
    int conta_oculto = 0; // contar quantas casas nao reveladas tem ao redor do numero_revelado
    int casas_maximas = 8; //  o maximo de casas nao reveladas possiveis ao redor do numero_revelado
    int aux = 0;
    for(numero_revelado = 1; numero_revelado < 6; numero_revelado++){
        for(casas_maximas = 8; casas_maximas > (numero_revelado + 1); casas_maximas--){
            for(int i = 0; i < lin; i++){
                for(int j = 0; j < col; j++){
                    if(campo_minado[i][j].revelado == 1 && campo_minado[i][j].numero > 0){
                        if(campo_minado[i][j].numero == numero_revelado){ //  se for igual ao inicial
                            for(int k = -1; k < 2; k++){
                                for(int m = -1; m < 2; m++){ // passar ao redor
                                    if(((i+k) >= 0 && (j+m) >= 0) && ((i+k) < lin && (j+m) < col)){
                                        if(campo_minado[i+k][j+m].revelado == 0){ // contando quantas casas nao reveladas tem ao redor do numero_revelado (inicial)
                                            conta_oculto++;
                                        }
                                    }
                                }
                            }
                            if(conta_oculto == casas_maximas){
                                for(int k = -1; k < 2; k++){
                                    for(int m = -1; m < 2; m++){
                                        if(((i+k) >= 0 && (j+m) >= 0) && ((i+k) < lin && (j+m) < col)){
                                            if(campo_minado[i+k][j+m].revelado == 0 && (i+k) != i && (j+m) != j && (i+k) != 0 && (j+m) != 0){
                                                if(aux != 1){
                                                *lin_bot = i+k;
                                                *col_bot = j+m;
                                                }
                                                aux = 1;
                                            }
                                        }
                                    }
                                }
                            }
                            else{
                                conta_oculto = 0;
                            }
                        }
                    }
                }
            }
        }
    }
}

int main(){
    
    int lin = 10, col = 20;
    campo campo_minado[lin][col];  // Implementação do Typedef
    
    criar_campo(lin, col, campo_minado);
    gera_numeros(lin, col, campo_minado);
    int opcao = 0;
    int verifica = 1;
    int jogar_linha = -1; // essas variaveis sao para escolher a jogada revelar. o valor é -1 pois nao tem chance de ser uma casa com uma bomba ex: 0, 0
    int jogar_coluna = -1;
    char jogar_coluna_char;
    int lin_bot, col_bot;
    // Em "jogar_coluna_char", o "_char" foi colocado porquê será necessário convertê-lo para int depois.
    printf("Seja Bem-vindo ao Campo Minado!\n\n");
    while(opcao != 2){
        printf("Digite o número da opção que você deseja:\n");
        printf("1 - Tutorial\n");
        printf("2 - Começar o Jogo\n\n");
        scanf("%d", &opcao);
        if(opcao == 1){
            printf("\nTutorial: O campo minado iniciará com todas as células ocultas, você deve escolher uma delas(exemplo: a5/c5/r3, e assim por diante).\nAo faze-lo, ocorrerá uma das seguintes possibilidades:\nCaso a posição escolhida for vazia, todas as células ao redor dela serão reveladas em cadeia, parando ao revelar um número.\nCaso a posição escolhida for um número n, significa que em volta daquela casa haverá n bombas\nCaso a posição escolhida for uma bomba, você perde o jogo.\n\n"); //turorial do jogo aqui
            printf("Tendo agora uma básica noção do jogo, escolha a opção que você deseja:\n");
            printf("2 - Começar o jogo\n");
            printf("3 - Ver uma demonstração\n");
            scanf("%d", &opcao);
            if(opcao == 3){
                int confere_inicio = 0;
                int verifica_vitoria_bot = 0; 
                int verifica_derrota_bot = 0;
                while(verifica_vitoria_bot == 0 && verifica_derrota_bot == 0){
                    verifica_vitoria_bot = vitoria(lin, col, campo_minado);
                    if(confere_inicio >= 1){
                        bot(lin, col, campo_minado, &lin_bot, &col_bot);
                    }
                    else{
                        lin_bot = 0;
                        col_bot = 0;
                    }
                    if(campo_minado[lin_bot][col_bot].bomba == 0){
                        revelar(lin_bot, col_bot, lin, col, campo_minado);
                    }
                    else{
                        revelar(lin_bot, col_bot, lin, col, campo_minado);
                        verifica_derrota_bot = 1;
                    }
                    formata_campo(lin, col, campo_minado);
                    confere_inicio++;
                }
                
                printf("\nEssa foi a demonstração do campo minado!\n\n");
                main();
            }
        }  
    }

    opcao = 0;
    time_t start = time(NULL);
    time_t end;
    long tempo = 0;
    int conta_tempo = 0;
    int verificador = 1;
    while(campo_minado[jogar_linha][jogar_coluna].bomba != 1 && verificador == 1){
        if(vitoria(lin, col, campo_minado) == 1){
            verificador = 0;
            formata_campo(lin, col, campo_minado);
            printf("\nParabens, você completou o Campo Minado!\n\n");
        }
        else{
            formata_campo(lin, col, campo_minado);
            printf("\nEscolha uma opção:\n");
            printf("1 - Revelar uma posição\n");
            printf("2 - Pedir Ajuda\n");
            if(conta_tempo != 0){
                printf("3 - Ver o tempo de jogo\n\n");
            } else{
                printf("\n");
            }
            scanf("%d", &opcao);
            if(opcao == 1){
                conta_tempo++;
                if(conta_tempo == 1){
                    start = time(NULL);
                }
                printf("\nDigite uma Letra(minúscula) e um Número, respectivamente:\n");
                scanf(" %c %d", &jogar_coluna_char, &jogar_linha);
                jogar_linha = jogar_linha - 1; // -1 pois a matriz começa a contar sua linha em 0
                jogar_coluna = jogar_coluna_char - 97; // - 97 pois é o valor da diferença entre caracters minusculos e inteiros na tabela ascii;
                while(campo_minado[jogar_linha][jogar_coluna].revelado == 1){
                    printf("Este local já foi revelado! tente outra posição.\n\n");
                    scanf(" %c %d", &jogar_coluna_char, &jogar_linha);
                    jogar_linha = jogar_linha - 1;
                    jogar_coluna = jogar_coluna_char - 97;
                }
                if(campo_minado[jogar_linha][jogar_coluna].numero > 0 && campo_minado[jogar_linha][jogar_coluna].bomba == 0){
                    campo_minado[jogar_linha][jogar_coluna].revelado = 1;
                }
                else if(campo_minado[jogar_linha][jogar_coluna].numero == 0 && campo_minado[jogar_linha][jogar_coluna].bomba == 0 && campo_minado[jogar_linha][jogar_coluna].revelado == 0){
                    revelar(jogar_linha, jogar_coluna, lin, col, campo_minado);
                }
            }
            if(opcao == 2){
                dica(lin, col, campo_minado, verificador);
            }
            if(opcao == 3){
                while(opcao == 3){
                    end = time(NULL);
                    tempo = end - start;
                    printf("\nTEMPO DE JOGO: %lds\n\n", tempo);
                    printf("Escolha uma opção:\n");
                    printf("1 - Revelar uma posição\n");
                    printf("2 - Pedir Ajuda\n");
                    printf("3 - Ver o tempo de jogo\n");
                    scanf("%d", &opcao);
                }
            }
        }
    }
    if(verificador == 1){
        kabum(lin, col, campo_minado);  // Revela a localização de todas as bombas caso o usuário escolha uma célula que contenha uma.
        formata_campo(lin, col, campo_minado);
        printf("\nVocê perdeu!\n");
    }
    printf("Deseja jogar novamente?\n1 - SIM\n2 - NÃO\n\n");
    scanf("%d", &opcao);
    printf("\n");
    if(opcao == 1){
        main();
    }
    else if(opcao == 2){
        printf("Fim de jogo.\n");
    }


    return 0;
}