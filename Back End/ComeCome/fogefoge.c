#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fogefoge.h"
#include "mapa.h"
#include "ui.h"

MAPA m;
POSICAO heroi;
int temPilula = 0;

void copiaMapa(MAPA* destino, MAPA* origem) {
    destino->linhas = origem->linhas;
    destino->colunas = origem->colunas;

    alocaMapa(destino);
    for(int i = 0; i < origem->linhas; i++) {
        strcpy(destino->matriz[i], origem->matriz[i]);
    }
}

void andaNoMapa(MAPA* m, int xOrigem, int yOrigem,
    int xDestino, int yDestino) {
    
    char personagem = m->matriz[xOrigem][yOrigem];
    m->matriz[xDestino][yDestino] = personagem;
    m->matriz[xOrigem][yOrigem] = VAZIO;
}

int ehValida(MAPA* m, int x, int y) {
    if(x >= m->linhas)
        return 0;
    if(y >= m->colunas)
        return 0;

    return 1;
}

int ehVazia(MAPA* m, int x, int y) {
    return m->matriz[x][y] == VAZIO;
}

int encontraMapa(MAPA* m, POSICAO* p, char c) {

    for(int i = 0; i < m->linhas; i++) {
        for(int j = 0; j < m->colunas; j++) {
            if(m->matriz[i][j] == c) {
                p->x = i;
                p->y = j;
                return 1;
            }
        }
    }

    return 0;
}

int ehParede(MAPA* m, int x, int y) {
    return m->matriz[x][y] == PAREDE_VERTICAL ||
        m->matriz[x][y] == PAREDE_HORIZONTAL;
}

int ehPersonagem(MAPA* m, char personagem, int x, int y) {
    return m->matriz[x][y] == personagem;
}

int podeAndar(MAPA* m, char personagem, int x, int y) {
    return
        ehValida(m, x, y) &&
        !ehParede(m, x, y) &&
        !ehPersonagem(m, personagem, x, y);
}

void liberaMapa(MAPA* m) {
    for(int i = 0; i < m->linhas; i++) {
        free(m->matriz[i]);
    }

    free(m->matriz);
}

void alocaMapa(MAPA* m) {
    m->matriz = malloc(sizeof(char*) * m->linhas);

    for(int i = 0; i < m->linhas; i++) {
        m->matriz[i] = malloc(sizeof(char) * (m->colunas + 1));
    }
}

void leMapa(MAPA* m) {
    FILE* f;
    f = fopen("mapa.txt", "r");

    if(f == 0) {
        printf("Erro na leitura do mapa\n");
        exit(1);
    }

    fscanf(f,"%d %d", &(m->linhas), &(m->colunas));
    alocaMapa(m);

    for(int i = 0; i < 5; i++) {
        fscanf(f, "%s", m->matriz[i]);
    }

    fclose(f);
}

void imprimeParte(char desenho[4][7], int parte) {
    printf("%s", desenho[parte]);
}

//novo imprimeMapa com alteração
void imprimeMapa(MAPA* m) {
    for(int i = 0; i < m->linhas; i++) {
        
        for(int parte = 0; parte < 4; parte++) {
            for(int j = 0; j < m->colunas; j++) {

                switch (m->matriz[i][j]) {
                case FANTASMA:
                    imprimeParte(desenhoFantasma, parte);
                    break;
                
                case HEROI:
                    imprimeParte(desenhoHeroi, parte);
                    break;

                case PILULA:
                    imprimeParte(desenhoPilula, parte);
                    break;
                
                case PAREDE_VERTICAL:
                case PAREDE_HORIZONTAL:
                    imprimeParte(desenhoParede, parte);
                    break;

                case VAZIO:
                    imprimeParte(desenhoVazio, parte);
                    break;
                }
            }

            printf("\n");
        }
    }
}

/* velho imprimeMapa
void imprimeMapa(MAPA* m) {
    for(int i = 0; i < m->linhas; i++) {
        printf("%s\n", m->matriz[i]);
    }
}
*/

void fantasmas() {
    MAPA copia;

    copiaMapa(&copia, &m);

    for(int i = 0; i < m.linhas; i++){
        for(int j = 0; j < m.colunas; j++) {

            if(copia.matriz[i][j] == FANTASMA) {

                int xDestino;
                int yDestino;

                int encontrou = ondeVaiOFantasma(i, j, 
                    &xDestino, &yDestino);

                if(encontrou) {
                    andaNoMapa(&m, i, j, xDestino, yDestino);
                }
            }
        }
    }

    liberaMapa(&copia);
}

int ondeVaiOFantasma(int xAtual, int yAtual, 
    int* xDestino, int* yDestino) {

    int opcoes[4][2] = {
        { xAtual, yAtual +1},
        { xAtual +1, yAtual},
        { xAtual, yAtual -1},
        { xAtual -1, yAtual}
    };

    srand(time(0));
    for(int i = 0; i < 10; i++) {
        int posicao = rand() % 4;

        if(podeAndar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1])) {
            *xDestino = opcoes[posicao][0];
            *yDestino = opcoes[posicao][1];

            return 1;
        }
    }

    return 0;
}

int acabou() {

    POSICAO pos;
    int fogeFogeNoMapa = encontraMapa(&m, &pos, HEROI);
    return !fogeFogeNoMapa;
}

int ehDirecao(char direcao) {
    return direcao == 'a' ||
        direcao == 'w' ||
        direcao == 's' ||
        direcao == 'd';

}

void move(char direcao) {

    if(!ehDirecao(direcao))
        return;

    int proximox = heroi.x;
    int proximoy = heroi.y;

    switch (direcao) {
        case ESQUERDA:
            proximoy--;
            break;
        case CIMA:
            proximox--;
            break;
        case BAIXO:
            proximox++;
            break;
        case DIREITA:
            proximoy++;
            break;
    }

    if(!podeAndar(&m, HEROI, proximox, proximoy))
        return;

    if(ehPersonagem(&m, PILULA, proximox, proximoy)) {
        temPilula = 1;
    }

    andaNoMapa(&m, heroi.x, heroi.y,
        proximox, proximoy);
    heroi.x = proximox;
    heroi.y = proximoy;
}

void explodePilula() {
    if(!temPilula) return;

    explodePilula2(heroi.x, heroi.y, 0, 1, 3);
    explodePilula2(heroi.x, heroi.y, 0, -1, 3);
    explodePilula2(heroi.x, heroi.y, 1, 0, 3);
    explodePilula2(heroi.x, heroi.y, -1, 0, 3);

    temPilula = 0;
}

void explodePilula2(int x, int y, int somaX, int somaY, int qtd) {

    if(qtd == 0) return;

    int novoX = x + somaX;
    int novoY = y + somaY;

    if(!ehValida(&m, novoX, novoY)) return;
    if(ehParede(&m, novoX, novoY)) return;

    m.matriz[novoX][novoY] = VAZIO;
    explodePilula2(novoX, novoY, somaX, somaY, qtd -1);   
}

int main() {

    leMapa(&m);
    encontraMapa(&m, &heroi, HEROI);

    do {
        printf("Tem pilula: %s\n", (temPilula ? "SIM" : "NAO"));
        imprimeMapa(&m);

        char comando;
        scanf(" %c", &comando);
        move(comando);
        if(comando == BOMBA) explodePilula(heroi.x, heroi.y, 3);

        fantasmas();

    } while (!acabou());

    liberaMapa(&m);

}

