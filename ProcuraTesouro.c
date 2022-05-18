// ProcuraTesouro
// @Bernardo Vieira nº24246
// @Leonardo Rodrigues nº24325

#include <stdio.h>
// Biblioteca para poder ser usado a variavél booleana (bool)
#include <stdbool.h>
// Biblioteca para poder ser usado o random
#include <stdlib.h>
// Biblioteca usada para calcular a distância entre 2 pontos
#include <math.h>

// Criação de variavéis globais
int nLinhas = 0, nColunas = 0, posicaoLinhaAtual=999, posicaoColunaAtual=999; // variavéis que definem posição do tabuleiro e a posição de início de jogo
int linha, coluna, jogada;
int posicaoTesouroColuna, posicaoTesouroLinha; // variavéis que guardam a localização do tesouro em um jogo
double distancia;                              // variável que guarda a distância euclediana
bool fim;                                      // booleano que diz se o jogo terminou ou não
int passos = 0;                                     // numero de passos para achar o tesouro

// Função que faz 4 perguntas ao jogador: nº linhas da matriz, nº colunas da matriz e
// posição onde quer começar o jogo na linha e na coluna.
// É ainda gerada a posição aleatória do tesouro no tabuleiro através da função gerarRandom
void pedeTabuleiro()
{
    int i=0,j=0;

    printf("Quantas linhas?: \n");
    scanf("\n%d", &nLinhas);

    printf("Quantas colunas?: \n");
    scanf("\n%d", &nColunas);

    //While loop para verificar se a linha inicial não excede o nº de linhas total
    while(posicaoLinhaAtual>=nLinhas)
    {
        if(i==0)
        {
            printf("Qual a linha de partida?: \n");
            scanf("\n%d", &posicaoLinhaAtual);
            i++;
        }
        else
        {
            printf("A sua linha de partida excede os limites do tabuleiro, digite uma nova linha inicial: \n");
            scanf("\n%d", &posicaoLinhaAtual);
        }

    }

    //While loop para verificar se a coluna inicial não excede o nº de colunas total
    while(posicaoColunaAtual>=nColunas)
    {
        if(j==0)
        {
            printf("Qual a coluna de partida: \n");
            scanf("\n%d", &posicaoColunaAtual);
            j++;
        }
        else
        {
            printf("A sua coluna de partida excede os limites do tabuleiro, digite uma nova coluna inicial: \n");
            scanf("\n%d", &posicaoColunaAtual);
        }

    }


    posicaoTesouroLinha = gerarPosicaoAleatoria(nLinhas - 1);
    posicaoTesouroColuna = gerarPosicaoAleatoria(nColunas - 1);
}

// Função que define os limites do tabuleiro em termos de linhas e colunas
// @params - recebe o nº de linhas e colunas escolhidas pelo jogador
// @return - limites do tabuleiro de jogo
char **limitesTabuleiro(int nLinhas, int nColunas)
{
    char **limites;
    int linha;

    limites = malloc(nLinhas * sizeof(char *));
    if (limites == NULL)
    {
        return NULL;
    }

    for (linha = 0; linha < nLinhas; linha++)
    {
        limites[linha] = malloc(nColunas * sizeof(char));
        if (limites[linha] == NULL)
            return NULL;
    }
    return limites;
}

// Função que permite escolher a posição inicial do jogador
void iniciaTabuleiro(char **matriz, char **matrizClone)
{
    for (linha = 0; linha < nLinhas; linha++)
    {
        for (coluna = 0; coluna < nColunas; coluna++)
        {
            if (coluna == posicaoColunaAtual && linha == posicaoLinhaAtual)
            {
                matriz[linha][coluna] = '&';
            }
            else
            {
                matriz[linha][coluna] = 'X';
            }
            matrizClone[linha][coluna] = matriz[linha][coluna];
        }
    }
}

// Função que permite ao jogador movimentar-se no tabuleiro
void direcoesTabuleiro(char **matriz, int posicao, char **matrizClone)
{
    for (linha = 0; linha < nLinhas; linha++)
    {
        for (coluna = 0; coluna < nColunas; coluna++)
        {
            if (matriz[linha][coluna] == '~')
            {
                matriz[linha][coluna] = 'O';
                matrizClone[linha][coluna] = matriz[linha][coluna];
            }
        }
    }
    int anteriorlinha = posicaoLinhaAtual;
    int anteriorColuna = posicaoColunaAtual;

    if (posicao == 1)
    {

        posicaoLinhaAtual -= 1;
        matriz[posicaoLinhaAtual][posicaoColunaAtual] = '&';
        matriz[anteriorlinha][anteriorColuna] = '~';
    }
    else if (posicao == 2)
    {
        posicaoLinhaAtual = posicaoLinhaAtual + 1;
        matriz[posicaoLinhaAtual][posicaoColunaAtual] = '&';
        matriz[anteriorlinha][anteriorColuna] = '~';
    }
    else if (posicao == 3)
    {
        posicaoColunaAtual += 1;
        matriz[posicaoLinhaAtual][posicaoColunaAtual] = '&';
        matriz[anteriorlinha][anteriorColuna] = '~';
    }
    else if (posicao == 4)
    {
        posicaoColunaAtual -= 1;
        matriz[posicaoLinhaAtual][posicaoColunaAtual] = '&';
        matriz[anteriorlinha][anteriorColuna] = '~';
    }
    else if (posicao == 0)
    {
        printf("Paciencia... O tesouro estava na posicao (%d,%d) e valia 100.000.000 '$'", posicaoTesouroLinha, posicaoTesouroColuna);
        fim = true;
    }
    else
    {
        printf("Inserir valor valido\n");
    }
}

// Função que imprime na consola a matriz conforme as linhas e colunas pedidas pelo jogador
void imprimeTabuleiro(char **matriz)
{
    for (linha = 0; linha < nLinhas; linha++)
    {
        for (coluna = 0; coluna < nColunas; coluna++)
        {
            printf(" %c ", matriz[linha][coluna]);
        }
        printf("\n");
    }

    return 0;
}

// Função que permite ao jogador mover-se um passo de cada vez e consoante a sua posicao no tabuleiro
// @params - recebe duas matrizes (original e um clone desta)
// @return - cada uma das jogadas/ movimentos do jogador e respetivas opções de direções que pode escolher
int andarTabuleiro(char **matriz, char **matrizClone)
{
    if (posicaoLinhaAtual == posicaoTesouroLinha && posicaoColunaAtual == posicaoTesouroColuna)
    {
        printf("Parabens! Chegou ao tesouro em %i passos! Ganhou 100.000.000\n", passos);
        fim = true;
        return jogada;
    }
    else
    {
        for (linha = 0; linha < nLinhas; linha++)
        {
            for (coluna = 0; coluna < nColunas; coluna++)
            {
                if (matriz[linha][coluna] == '-' && matrizClone[linha][coluna] == 'O')
                    matriz[linha][coluna] = 'O';
                else if (matriz[linha][coluna] == '~' && matrizClone[linha][coluna] == 'O')
                    matriz[linha][coluna] = 'O';
                else if (matriz[linha][coluna] == '-' && matrizClone[linha][coluna] == 'X')
                    matriz[linha][coluna] = 'X';
            }
        }
        if (fim != true)
        {
            if (posicaoLinhaAtual == 0 && posicaoColunaAtual == 0)
            {
                if (matriz[posicaoColunaAtual + 1][posicaoLinhaAtual] != '~' && matriz[posicaoColunaAtual][posicaoLinhaAtual + 1] != '~')
                {
                    matriz[posicaoColunaAtual + 1][posicaoLinhaAtual] = '-';
                    matriz[posicaoColunaAtual][posicaoLinhaAtual + 1] = '-';
                }
                else if (matriz[posicaoColunaAtual + 1][posicaoLinhaAtual] == '~' && matriz[posicaoColunaAtual][posicaoLinhaAtual + 1] != '~')
                {
                    matriz[posicaoColunaAtual][posicaoLinhaAtual + 1] = '-';
                }
                else if (matriz[posicaoColunaAtual][posicaoLinhaAtual + 1] == '~' && matriz[posicaoColunaAtual + 1][posicaoLinhaAtual] != '~')
                {
                    matriz[posicaoColunaAtual + 1][posicaoLinhaAtual] = '-';
                }
                imprimeTabuleiro(matriz);
                printf("Em que direcao quer ir?");
                printf("\n2:Sul  3:Este ou 0 para desistir\n");
                scanf("%d", &jogada);
            }

            else if (posicaoLinhaAtual == nLinhas - 1 && posicaoColunaAtual == nColunas - 1)
            {
                if (matriz[posicaoColunaAtual - 1][posicaoLinhaAtual] != '~' && matriz[posicaoColunaAtual][posicaoLinhaAtual - 1] != '~')
                {
                    matriz[posicaoColunaAtual - 1][posicaoLinhaAtual] = '-';
                    matriz[posicaoColunaAtual][posicaoLinhaAtual - 1] = '-';
                }
                else if (matriz[posicaoColunaAtual - 1][posicaoLinhaAtual] == '~' && matriz[posicaoColunaAtual][posicaoLinhaAtual - 1] != '~')
                {
                    matriz[posicaoColunaAtual][posicaoLinhaAtual - 1] = '-';
                }
                else if (matriz[posicaoColunaAtual][posicaoLinhaAtual - 1] == '~' && matriz[posicaoColunaAtual - 1][posicaoLinhaAtual] != '~')
                {
                    matriz[posicaoColunaAtual - 1][posicaoLinhaAtual] = '-';
                }
                imprimeTabuleiro(matriz);
                printf("Em que direcao quer ir?");
                printf("\n1:Norte  4:Oeste ou 0 para desistir\n");
                scanf("%d", &jogada);
            }

            else if (posicaoLinhaAtual == 0 && posicaoColunaAtual == nColunas - 1)
            {

                if (matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] != '~')
                {
                    matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] = '-';
                    matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] = '-';
                }

                else if (matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] == '~' && matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] != '~')
                {
                    matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] = '-';
                }
                else if (matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] == '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] != '~')
                {
                    matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] = '-';
                }
                imprimeTabuleiro(matriz);
                printf("Em que direcao quer ir?");
                printf("\n2:Sul  4:Oeste ou 0 para desistir\n");
                scanf("%d", &jogada);
            }

            else if (posicaoLinhaAtual == nLinhas - 1 && posicaoColunaAtual == 0)
            {

                if (matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] != '~')
                {

                    matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] = '-';
                    matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] = '-';
                }

                else if (matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] == '~' && matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] != '~')
                {
                    matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] = '-';
                }
                else if (matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] == '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] != '~')
                {
                    matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] = '-';
                }
                imprimeTabuleiro(matriz);
                printf("Em que direcao quer ir?");
                printf("\n1:Norte  3:Este ou 0 para desistir\n");
                scanf("%d", &jogada);
            }
            else if (posicaoLinhaAtual == 0 && posicaoColunaAtual != 0)
            {
                if (matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] != '~')
                {
                    matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] = '-';
                    matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] = '-';
                    matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] = '-';
                }

                else if (matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] == '~' && matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] != '~')
                {
                    matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] = '-';
                    matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] = '-';
                }
                else if (matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] == '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] != '~')
                {
                    matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] = '-';
                    matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] = '-';
                }
                else if (matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] == '~')
                {
                    matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] = '-';
                    matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] = '-';
                }
                imprimeTabuleiro(matriz);
                printf("Em que direcao quer ir?");
                printf("\n2:Sul  3:Este  4:Oeste ou 0 para desistir\n");
                scanf("%d", &jogada);
            }
            else if (posicaoLinhaAtual == nLinhas - 1)
            {
                if (matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] != '~')
                {
                    matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] = '-';
                    matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] = '-';
                    matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] = '-';
                }

                else if (matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] == '~' && matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] != '~')
                {
                    matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] = '-';
                    matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] = '-';
                }
                else if (matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] == '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] != '~')
                {
                    matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] = '-';
                    matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] = '-';
                }
                else if (matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] == '~')
                {
                    matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] = '-';
                    matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] = '-';
                }
                imprimeTabuleiro(matriz);
                printf("Em que direcao quer ir?");
                printf("\n1:Norte  3:Este  4:Oeste ou 0 para desistir\n");
                scanf("%d", &jogada);
            }
            else if (posicaoColunaAtual == 0 && posicaoLinhaAtual != 0)
            {
                if (matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] != '~' && matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] != '~')
                {
                    matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] = '-';
                    matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] = '-';
                    matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] = '-';
                }

                else if (matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] == '~' && matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] != '~')
                {
                    matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] = '-';
                    matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] = '-';
                }
                else if (matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] == '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] != '~' && matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] != '~')
                {
                    matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] = '-';
                    matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] = '-';
                }
                else if (matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] != '~' && matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] == '~')
                {
                    matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] = '-';
                    matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] = '-';
                }
                imprimeTabuleiro(matriz);
                printf("Em que direcao quer ir?");
                printf("\n1:Norte  2:Sul  3:Este ou 0 para desistir\n");
                scanf("%d", &jogada);
            }
            else if (posicaoColunaAtual == nColunas - 1)
            {
                if (matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] != '~')
                {
                    matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] = '-';
                    matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] = '-';
                    matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] = '-';
                }

                else if (matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] == '~' && matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] != '~')
                {
                    matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] = '-';
                    matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] = '-';
                }
                else if (matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] == '~' && matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] != '~')
                {
                    matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] = '-';
                    matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] = '-';
                }
                else if (matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] == '~')
                {
                    matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] = '-';
                    matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] = '-';
                }
                imprimeTabuleiro(matriz);
                printf("Em que direcao quer ir?");
                printf("\n1:Norte  2:Sul  4:Oeste ou 0 para desistir \n");
                scanf("%d", &jogada);
            }
            else
            {
                if (matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] != '~')
                {
                    matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] = '-';
                    matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] = '-';
                    matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] = '-';
                    matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] = '-';
                }

                else if (matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] == '~' && matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] != '~')
                {
                    matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] = '-';
                    matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] = '-';
                    matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] = '-';
                }
                else if (matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] == '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] != '~')
                {
                    matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] = '-';
                    matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] = '-';
                    matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] = '-';
                }
                else if (matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] == '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] != '~')
                {
                    matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] = '-';
                    matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] = '-';
                    matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] = '-';
                }
                else if (matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] != '~' && matriz[posicaoLinhaAtual][posicaoColunaAtual + 1] == '~')
                {
                    matriz[posicaoLinhaAtual - 1][posicaoColunaAtual] = '-';
                    matriz[posicaoLinhaAtual + 1][posicaoColunaAtual] = '-';
                    matriz[posicaoLinhaAtual][posicaoColunaAtual - 1] = '-';
                }
                imprimeTabuleiro(matriz);
                printf("Em que direcao quer ir?");
                printf("\n1:Norte 2:Sul  3:Este  4:Oeste ou 0 para Desistir \n");
                scanf("%d", &jogada);
            }
        }
    }
    return jogada;
}

// Função que calcula a distância euclidiana (arredondada às décimas) do jogador ao tesouro
// @params - recebe 4 parametros, sendo linha, coluna e posição atual da linha e na coluna
// @return - distância do tesouro em número de jogadas/ passos
double distanciaPontos(int linha, int coluna, int posicaoLinhaAtual, int posicaoColunaAtual)
{
    return sqrt(pow(posicaoLinhaAtual - linha, 2) + pow(posicaoColunaAtual - coluna, 2) * 1.0);
}

// Função que gera uma posicao aleatoria para colocar o tesouro
// @params - numero que define o valor maximo da posição que pode ser gerada aleatoriamente
// @return - retorna a posicao aleatorio do tesouro (ver printf comentado na função 'main')
int gerarPosicaoAleatoria(int a)
{
    int posicao = (rand() % a);
    return posicao;
}

// Função Principal onde são invocadas as restantes funções e variavéis globais
int main(void)
{
    //srand muda a seed do rand através do tempo
    srand((unsigned)time(NULL));
    pedeTabuleiro();
    char **matrizOriginal = limitesTabuleiro(nLinhas, nColunas);
    char **matrizClone = limitesTabuleiro(nLinhas, nColunas);
    iniciaTabuleiro(matrizOriginal, matrizClone);
    while (fim != true)
    {
        //printf("%i,%i", posicaoTesouroLinha, posicaoTesouroColuna);
        printf("\nDistancia ao tesouro: %.2lf passos\n\n", distancia = distanciaPontos(posicaoTesouroLinha, posicaoTesouroColuna, posicaoLinhaAtual, posicaoColunaAtual));
        jogada = andarTabuleiro(matrizOriginal, matrizClone);
        direcoesTabuleiro(matrizOriginal, jogada, matrizClone);
        passos++;
    }
}

