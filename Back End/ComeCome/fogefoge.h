#ifndef _FOGEFOGE_H_
#define _FOGEFOGE_H_

#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define ESQUERDA 'a'
#define BOMBA 'b'

void move(char direcao);
int acabou();

int ehDirecao(char direcao);

void fantasmas();

int ondeVaiOFantasma(int xAtual, int yAtual, 
    int* xDestino, int* yDestino);

void explodePilula();
void explodePilula2(int x, int y, int somaX, int somaY, int qtd);

#endif