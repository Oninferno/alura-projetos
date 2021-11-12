#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int main() {
    
    int segundos = time(0);
    srand(segundos);

    int n1 = rand();
    int n2 = rand();

    printf("%d %d\n", n1, n2);
}

/* imprime cabeçalho do nosso jogo
printf("*****************************************\n");
printf("* Bem vindo ao nosso jogo de advinhação *\n");
printf("*****************************************\n");.

#define NUMERO_DE_TENTATIVAS 5 (# = diretiva / define = define uma constante)

Tipos de variáveis
double - numeros decimais (como pi por exemplo) / utiliza a mascara %f
int - numeros inteiros / utiliza a mascara %d
long - "irmão" do int, é um inteiro que tem 8 bytes = 64bits = 2^64

por(var contador=x;condição;incremento)

for (int i = 1; i <= NUMERO_DE_TENTATIVAS; i++){
printf("Tentativa %d de %d\n", i, NUMERO_DE_TENTATIVAS);
printf("Qual é o seu chute? ");

scanf("%d", &chute);
printf("Seu chute foi %d\n", chute);

if(chute < 0)
{
printf("Você não pode chutar números negativos!");
i--;

continue;
}

int acertou = (chute == numerosecreto);
int maior = chute > numerosecreto;
int menor = chute < numerosecreto;


esses dois tem a mesma funcionalidade

switch (nivel) {
    case 1:
        numerodetentativas = 20;
        break;

    case 2:
        numerodetentativas = 10;
        break;

    default:
        numerodetentativas = 5;
        break;
}

if(nivel == 1) {
    numerodetentativas = 20;
} else if (nivel == 2) {
    numerodetentativas = 10;
} else {
    numerodetentativas = 5;
}



um dia eu vou fazer esse logo funcionar !!!!!!

printf("    }}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
            {{            +             +                  +   @          {{
            }}   |                *           o     +                .    }}
            {{  -O-    o               .               .          +       {{
            }}   |                    _,.-----.,_         o    |          }}
            {{           +    *    .-'.         .'-.          -O-         {{
            }}      *            .'.-'   .---.   `'.'.         |     *    }}
            {{ .                /_.-'   /     \\   .'-.\\                 {{
            }}         ' -=*<  |-._.-  |   @   |   '-._|  >*=-    .     + }}
            {{ -- )--         \\`-.    \\     /    .-'/                   {{
            }}       *     +     `.'.    '---'    .'.'    +       o       }}
            {{                  .  '-._         _.-'  .                   {{
            }}         |               `~~~~~~~`       - --===D       @   }}
            {{   o    -O-      *   .                  *        +          {{
            }}         |    BEM VINDO AO JOGO DE ADVINHAÇÃO!              }}
            {{              .     @      o                        *       {{
            }}       o                          *          o           .  }}
            {{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{ ");
printf("\n\n");


*/