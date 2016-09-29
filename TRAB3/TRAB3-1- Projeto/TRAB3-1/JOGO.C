/***************************************************************************
*  $MCI Módulo de implementação: Módulo JOGO
*
*  Arquivo gerado:              JOGO.C
*  Letras identificadoras:      JGO
*
*  Projeto: Disciplina INF 1301
*
*  Autores: gsg - Gabriel da Silva Gomes
*			     gsb - Gustavo Severo Barros
*	      jpmldg - João Pedro Masset Lacombe D Garcia
*
*  $HA Histórico de evolução:
*     Versão       Autor          Data            Observações
*      1.00     gsg, jpmldg    17/04/2016   Início do desenvolvimento
*
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "LISTA.H"
#include "PILHA.H"
#include "MATRIZ.H"

/***********************************************************************
*
*  $TC Tipo de dados: JGO Condições de Retorno
*
***********************************************************************/

typedef enum
{
	JGO_CondRetOK,
	/* Executou correto */

	JGO_CondRetErroMatriz,
	/* Erro na Matriz */

	JGO_CondRetErroPilha,
	/* Erro na Pilha */

	JGO_CondRetPecasDiferentes,
	/* Peças diferentes */

	JGO_CondRetPecaBloqueada
	/* Peça Nao retiravel */

} JGO_tpCondRet;

/*****  Dados encapsulados no módulo  *****/

#define LINHAS 8
#define COLUNAS 8
#define TAMANHO LINHAS * COLUNAS
#define PECAS 120

/***** Protótipos das funções encapuladas no módulo *****/

JGO_tpCondRet CriarPilhas(PIL_tppPilha *pVetorPilhas);

JGO_tpCondRet GeraTabuleiro(MAT_tppMatriz *pMatriz, PIL_tppPilha *pVetorPilhas);

JGO_tpCondRet PreencheTabuleiro(MAT_tppMatriz matriz, char * pBaralho, int * pTamanhoBaralho);

JGO_tpCondRet ImprimeTabuleiro(MAT_tppMatriz matriz);

JGO_tpCondRet DestroiTabuleiro(MAT_tppMatriz *pMatriz);

void PreencheBaralho(char *pBaralho);

char SorteiaPeca(int i, int j, char *pBaralho, int *pTamanhoBaralho);

JGO_tpCondRet ChecaRetiravel (MAT_tppMatriz* pMatriz, int linha, int coluna, int *retorno);

JGO_tpCondRet RemovePecas (MAT_tppMatriz* pMatriz, int linhaPeca1, int colunaPeca1, int linhaPeca2, int colunaPeca2, int *retorno);

JGO_tpCondRet ChecaGameOver (MAT_tppMatriz* pMatriz, int *retorno);

int main (void)
{
	MAT_tppMatriz matriz;
	PIL_tppPilha vetorPilhas[TAMANHO];
	JGO_tpCondRet retornoJogo;
	int i;
	char baralho[PECAS];
	int teste = 0;
	int tamBaralho = PECAS;
	int l1,l2,c1,c2;
	int statusJogo = 1;

	PreencheBaralho(baralho);

	retornoJogo = CriarPilhas(vetorPilhas);
	if (retornoJogo != JGO_CondRetOK){
		printf("Erro Criar Pilha - %d\n", retornoJogo);
	}
	retornoJogo = GeraTabuleiro(&matriz, vetorPilhas);
	if (retornoJogo != JGO_CondRetOK){
		printf("Erro ao gerar tabuleiro - %d\n", retornoJogo);
	}
	retornoJogo = PreencheTabuleiro(matriz, baralho, &tamBaralho);
	if (retornoJogo != JGO_CondRetOK){
		printf("Erro ao preencher tabuleiro - %d\n", retornoJogo);
	}

	system("cls");
	printf("PACIENCIA MAH JONG:\n\n\n");

	retornoJogo = ImprimeTabuleiro(matriz);
	if (retornoJogo != JGO_CondRetOK){
		printf("Erro ao imprimir tabuleiro - %d\n", retornoJogo);
	}

	retornoJogo = ChecaGameOver (&matriz, &statusJogo);
	if (retornoJogo != JGO_CondRetOK){
		printf("Erro ao checar status do jogo - %d\n", retornoJogo);
	}

	while(statusJogo == 1){
		printf("Insira Linha Coluna da primeira e da segunda peca\n");
		scanf("%d %d %d %d",&l1,&c1,&l2,&c2);

		system("cls");

		printf("PACIENCIA MAH JONG:\n\n");

		retornoJogo = RemovePecas(&matriz, l1, c1, l2, c2, &teste);
		if (retornoJogo != JGO_CondRetOK){
			printf("Erro ao remover Pecas", retornoJogo);

			if (retornoJogo == JGO_CondRetPecaBloqueada){
				printf(" - Pecas presas\n");
			} else if (retornoJogo == JGO_CondRetPecasDiferentes){
				printf(" - Pecas diferentes\n");
			} else {
				printf(" - Entradas invalidas\n");
			}
		} else {
			printf("\n");
		}

		retornoJogo = ImprimeTabuleiro(matriz);
		if (retornoJogo != JGO_CondRetOK){
			printf("Erro ao imprimir Matriz - %d\n", retornoJogo);
		}
		retornoJogo = ChecaGameOver (&matriz, &statusJogo);
		if (retornoJogo != JGO_CondRetOK){
			printf("Erro ao checar status do jogo - %d\n", retornoJogo);
		}
	}

	printf("O jogo chegou ao fim!\n");
	if(statusJogo == 0){
		printf("Que pena, voce perdeu, tente novamente mais tarde...\n");
	} else {
		printf("PARABENS, VOCE VENCEU!\n");
	}
	//DestroiTabuleiro(&matriz);

	return 0;
}

/***********************************************************************
*
*  $FC Função: Criar Pilhas
*
*  $ED Descrição da função
*     Cria uma pilha para cada posição do tabuleiro.
*
*  $EP Parâmetros
*     pVetorPilhas - ponteiro para o início do vetor de pilhas.
*
***********************************************************************/

JGO_tpCondRet CriarPilhas(PIL_tppPilha *pVetorPilhas)
{
	int countPilhas;

	for(countPilhas = 0; countPilhas < TAMANHO; countPilhas++)
	{
		pVetorPilhas[countPilhas] = PIL_CriarPilha();
	}

	return JGO_CondRetOK;
} /* Fim função: Criar Pilhas */

/***********************************************************************
*
*  $FC Função: Gera Tabuleiro
*
*  $ED Descrição da função
*     Cria a Matriz que representa o tabuleiro e associa a cada posição da
*     Matriz uma Pilha.
*
*  $EP Parâmetros
*     pVetorPilhas - ponteiro para o início do vetor de pilhas.
*     pMatriz - ponteiro para a cabeça da Matriz que será usada como tabuleiro.
*
***********************************************************************/

JGO_tpCondRet GeraTabuleiro(MAT_tppMatriz *pMatriz, PIL_tppPilha * pVetorPilhas)
{
	int contadorLinhas, contadorColunas;
	MAT_tpCondRet retornoMatriz;

	retornoMatriz = MAT_CriarMatriz(pMatriz, LINHAS, COLUNAS);

	if (retornoMatriz != MAT_CondRetOK)
	{
		return JGO_CondRetErroMatriz;
	}

	for(contadorLinhas = 0; contadorLinhas < LINHAS; contadorLinhas++)
	{
		for(contadorColunas = 0; contadorColunas < COLUNAS; contadorColunas++)
		{
			retornoMatriz = MAT_IrParaCoordenada(*pMatriz, contadorLinhas, contadorColunas);
			if (retornoMatriz != MAT_CondRetOK)
			{
				return JGO_CondRetErroMatriz;
			}

			retornoMatriz = MAT_InserirValor(*pMatriz, pVetorPilhas[LINHAS * contadorLinhas + contadorColunas]);
			if (retornoMatriz != MAT_CondRetOK)
			{
				return JGO_CondRetErroMatriz;
			}
		}
	}

	return JGO_CondRetOK;
} /* Fim função: Gera Tabuleiro */

/***********************************************************************
*
*  $FC Função: Preenche Tabuleiro
*
*  $ED Descrição da função
*     Preenche cada pilha da Matriz com uma quantidade calculada de peças de
*     modo que se empilhem como uma pirâmide.
*
*  $EP Parâmetros
*     pMatriz - ponteiro para a cabeça da Matriz que é o tabuleiro.
*     pBaralho - ponteiro para o início do vetor com todas as peças do jogo.
*     pTamanhoBaralho - Tamanho do vetor pBaralho.
*
***********************************************************************/

JGO_tpCondRet PreencheTabuleiro(MAT_tppMatriz matriz, char* pBaralho, int* pTamanhoBaralho)
{
	int contadorLinhas, contadorColunas, contadorAltura;
	PIL_tppPilha pilha = NULL;
	MAT_tpCondRet retMatriz;
	PIL_tpCondRet retPilha;

	for(contadorAltura = 0; contadorAltura < LINHAS / 2; contadorAltura++)
	{
		for(contadorLinhas = contadorAltura; contadorLinhas < LINHAS - contadorAltura; contadorLinhas++)
		{
			for(contadorColunas = contadorAltura; contadorColunas < COLUNAS - contadorAltura; contadorColunas++)
			{
				char caracter;
				retMatriz = MAT_IrParaCoordenada(matriz, contadorLinhas, contadorColunas);
				if(retMatriz != MAT_CondRetOK){
					return JGO_CondRetErroMatriz;
				}
				retMatriz = MAT_ObterValorCorr(matriz, &pilha);
				if(retMatriz != MAT_CondRetOK){
					return JGO_CondRetErroMatriz;
				}

				caracter = SorteiaPeca(contadorLinhas, contadorColunas, pBaralho, pTamanhoBaralho);
				retPilha = PIL_EmpilhaValor(pilha, caracter);
				if(retPilha != PIL_CondRetOK){
					return JGO_CondRetErroPilha;
				}

			}
		}
	}

	return JGO_CondRetOK;
} /* Fim função: Preenche Tabuleiro */

/***********************************************************************
*
*  $FC Função: Imprime Tabuleiro
*
*  $ED Descrição da função
*     Cria a Matriz que representa o tabuleiro e associa a cada posição da
*     Matriz uma Pilha.
*
*  $EP Parâmetros
*     pVetorPilhas - ponteiro para o início do vetor de pilhas.
*     pMatriz - ponteiro para a cabeça da Matriz que será usada como tabuleiro.
*
***********************************************************************/

JGO_tpCondRet ImprimeTabuleiro(MAT_tppMatriz matriz)
{
	int contadorLinhas, contadorColunas, contadorAltura, tamanho;
	char conteudo;
	MAT_tpCondRet retMatriz;
	PIL_tpCondRet retPilha;
	PIL_tppPilha pilha;

	printf("|  |  ");

	for(contadorColunas = 0; contadorColunas < COLUNAS; contadorColunas++)
	{
		printf("|%d |", contadorColunas);
	}

	printf("\n");
	printf("\n");

	for(contadorLinhas = 0; contadorLinhas < LINHAS; contadorLinhas++)
	{
		printf("| %d|  ", contadorLinhas);

		for(contadorColunas = 0; contadorColunas < COLUNAS; contadorColunas++)
		{
			retMatriz = MAT_IrParaCoordenada(matriz, contadorLinhas, contadorColunas);
			if(retMatriz != MAT_CondRetOK){
				return JGO_CondRetErroMatriz;
			}
			retMatriz = MAT_ObterValorCorr(matriz, &pilha);
			if(retMatriz != MAT_CondRetOK){
				return JGO_CondRetErroMatriz;
			}

			retPilha = PIL_ObterValorTopo(pilha, &conteudo);
			retPilha = PIL_ObterTamanho(pilha, &tamanho);
			if(retPilha != PIL_CondRetOK){
				printf("Got here -2");
				return JGO_CondRetErroPilha;
			}

			printf("|%d%c|", tamanho, conteudo);
		}

		printf("\n");
	}

	return JGO_CondRetOK;
} /* Fim função: Imprime Tabuleiro */

/***********************************************************************
*
*  $FC Função: Destrói Tabuleiro
*
*  $ED Descrição da função
*     Esvazia o tabuleiro e destrói a Matriz que representa o tabuleiro.
*
*  $EP Parâmetros
*     pMatriz - ponteiro para a cabeça da Matriz usada como tabuleiro.
*
***********************************************************************/

JGO_tpCondRet DestroiTabuleiro(MAT_tppMatriz *pMatriz)
{
	int contadorLinhas, contadorColunas;
	MAT_tpCondRet retMatriz;
	PIL_tpCondRet retPilha;
	PIL_tppPilha pilha;

	for(contadorLinhas = 0; contadorLinhas < LINHAS; contadorLinhas++)
	{
		for(contadorColunas = 0; contadorColunas < COLUNAS; contadorColunas++)
		{
			MAT_IrParaCoordenada(*pMatriz, contadorLinhas, contadorColunas);
			if(retMatriz != MAT_CondRetOK){
				return JGO_CondRetErroMatriz;
			}
			MAT_ObterValorCorr(*pMatriz, &pilha);
			if(retMatriz != MAT_CondRetOK){
				return JGO_CondRetErroMatriz;
			}

			if(pilha != NULL)
			{
				retPilha = PIL_DestruirPilha(pilha);
				if(retPilha != PIL_CondRetOK){
					return JGO_CondRetErroPilha;
				}
			}
		}
	}

	MAT_DestruirMatriz(pMatriz);

	return JGO_CondRetOK;
} /* Fim função: Destrói Tabuleiro */

/***********************************************************************
*
*  $FC Função: Sorteia Peça
*
*  $ED Descrição da função
*     Sorteia de maneira aleatória uma peça.
*
*  $EP Parâmetros
*
*		 linha - inteiro que representa a linha na qual a peça será usada.
*     coluna - inteiro que representa a coluna na qual a peça será usada.
*     pBaralho - ponteiro para o início do vetor com todas as peças do jogo.
*     pTamanhoBaralho - Tamanho do vetor pBaralho.
*
***********************************************************************/

char SorteiaPeca(int linha, int coluna, char *pBaralho, int *pTamanhoBaralho)
{
	int indicePecaSorteada, contadorPecas, l;
	char pecaSorteada;

	srand(time(NULL) * (linha + coluna + 1));
	indicePecaSorteada = rand() % (*pTamanhoBaralho);

	pecaSorteada = pBaralho[indicePecaSorteada];
	pBaralho[indicePecaSorteada] = 'Z';

	for(contadorPecas = 0; contadorPecas < PECAS - 1; contadorPecas++)
	{
		if(pBaralho[contadorPecas] == 'Z')
		{
			pBaralho[contadorPecas] = pBaralho[contadorPecas + 1];
			pBaralho[contadorPecas + 1] = 'Z';
		}
	}

	(*pTamanhoBaralho)--;

	return pecaSorteada;
} /* Fim função: Sorteia Peça */

/***********************************************************************
*
*  $FC Função: Preenche Baralho
*
*  $ED Descrição da função
*     Preenche o baralho com quantidades de tipos de peças iguais.
*
*  $EP Parâmetros
*     pBaralho - ponteiro para o início do vetor que irá receber as peças do jogo.
*
***********************************************************************/

void PreencheBaralho(char *pBaralho)
{
	int contador;

	for(contador = 0; contador < PECAS / 4; contador++)
	{
		pBaralho[contador] = 'A';
	}

	for(contador = PECAS / 4; contador < PECAS/ 2 ; contador++)
	{
		pBaralho[contador] = 'B';
	}

	for(contador = 2 * PECAS / 4; contador < 3 * PECAS / 4; contador++)
	{
		pBaralho[contador] = 'C';
	}

	for(contador = 3 * PECAS / 4; contador < PECAS; contador++)
	{
		pBaralho[contador] = 'D';
	}
} /* Fim função: Preenche Baralho */

/***********************************************************************
*
*  $FC Função: Checa Retirável
*
*  $ED Descrição da função
*     Verifica se uma peça pode ser removida.
*
*  $EP Parâmetros
*     pMatriz - ponteiro para a cabeça da Matriz usada como tabuleiro.
*     linha - inteiro que representa a linha da peça
*     coluna - inteiro que representa a coluna da peça
*     retorno - 0 se não for possível remover e 1 caso seja possível.
*
***********************************************************************/

JGO_tpCondRet ChecaRetiravel (MAT_tppMatriz *pMatriz, int linha, int coluna, int *retorno)
{
	//Pilhas utilizadas na análise.
	PIL_tppPilha pilhaAnterior  = NULL;
	PIL_tppPilha pilhaPosterior = NULL;
	PIL_tppPilha pilhaAtual     = NULL;

	//Valores de pilha
	int tamanhoPilhaAnterior  = 0;
	int tamanhoPilhaPosterior = 0;
	int tamanhoPilhaAtual     = 0;

	//Variáveis de retorno.
	MAT_tpCondRet retornoMatriz;
	PIL_tpCondRet retornoPilha;

	//Valor default de retorno é 0.
	(*retorno) = 0;

	//Pega pilha a ser avaliada.
	retornoMatriz = MAT_IrParaCoordenada(*pMatriz, linha, coluna);

	if (retornoMatriz != MAT_CondRetOK)
	{
		return JGO_CondRetErroMatriz;
	}

	retornoMatriz = MAT_ObterValorCorr(*pMatriz, &pilhaAtual);

	if (retornoMatriz != MAT_CondRetOK)
	{
		return JGO_CondRetErroMatriz;
	}

	retornoPilha = PIL_ObterTamanho(pilhaAtual, &tamanhoPilhaAtual);

	if (retornoPilha != PIL_CondRetOK)
	{
		return JGO_CondRetErroPilha;
	}

	//Pega a pilha anterior, se houver.
	if (coluna - 1 >= 0)
	{
		retornoMatriz = MAT_IrParaCoordenada(*pMatriz, linha, coluna - 1);

		if (retornoMatriz != MAT_CondRetOK)
		{
			return JGO_CondRetErroMatriz;
		}

		retornoMatriz = MAT_ObterValorCorr(*pMatriz, &pilhaAnterior);

		if (retornoMatriz != MAT_CondRetOK)
		{
			return JGO_CondRetErroMatriz;
		}

		retornoPilha = PIL_ObterTamanho(pilhaAnterior, &tamanhoPilhaAnterior);

		if (retornoPilha != PIL_CondRetOK)
		{
			return JGO_CondRetErroPilha;
		}
	}

	//Pega a pilha posterior, se houver.
	if (coluna + 1 <= COLUNAS - 1)
	{
		retornoMatriz = MAT_IrParaCoordenada(*pMatriz, linha, coluna + 1);

		if (retornoMatriz != MAT_CondRetOK)
		{
			return JGO_CondRetErroMatriz;
		}

		retornoMatriz = MAT_ObterValorCorr(*pMatriz, &pilhaPosterior);

		if (retornoMatriz != MAT_CondRetOK)
		{
			return JGO_CondRetErroMatriz;
		}

		retornoPilha = PIL_ObterTamanho(pilhaPosterior, &tamanhoPilhaPosterior);

		if (retornoPilha != PIL_CondRetOK)
		{
			return JGO_CondRetErroPilha;
		}
	}

	//Compara altura das pilhas e retorna.
	if (tamanhoPilhaAtual > tamanhoPilhaAnterior || tamanhoPilhaAtual > tamanhoPilhaPosterior)
	{
		return JGO_CondRetOK;
	}

	(*retorno) = 1;

	return JGO_CondRetOK;
} /* Fim função: Checa Retirável */

/***********************************************************************
*
*  $FC Função: Remove Pecas
*
*  $ED Descrição da função
*     Verifica se um par de peças pode ser removido.
*
*  $EP Parâmetros
*     pMatriz - ponteiro para a cabeça da Matriz usada como tabuleiro.
*     linhaPeca1 - inteiro que representa a linha da peça 1
*     colunaPeca1 - inteiro que representa a coluna da peça 1
*     linhaPeca2 - inteiro que representa a linha da peça 2
*     colunaPeca2 - inteiro que representa a coluna da peça 2
*     retorno - 0 se não for possível remover e 1 caso seja possível.
*
***********************************************************************/

JGO_tpCondRet RemovePecas (MAT_tppMatriz* pMatriz, int linhaPeca1, int colunaPeca1, int linhaPeca2, int colunaPeca2, int *retorno)
{
	//Pilhas utilizadas na análise.
	PIL_tppPilha pilha1 = NULL;
	PIL_tppPilha pilha2 = NULL;

	//Valores de pilha
	char pecaPilha1 = NULL;
	char pecaPilha2 = NULL;

	//Variáveis de retorno.
	MAT_tpCondRet retornoMatriz;
	PIL_tpCondRet retornoPilha;
	JGO_tpCondRet retornoJogo;
	int retornoChecaRetiravel = 0;

	//Valor default de retorno é 0.
	(*retorno) = 0;

	//Pega pilha 1.
	retornoMatriz = MAT_IrParaCoordenada(*pMatriz, linhaPeca1, colunaPeca1);

	if (retornoMatriz != MAT_CondRetOK){
		return JGO_CondRetErroMatriz;
	}

	retornoMatriz = MAT_ObterValorCorr(*pMatriz, &pilha1);

	if (retornoMatriz != MAT_CondRetOK){
		return JGO_CondRetErroMatriz;
	}

	retornoPilha = PIL_ObterValorTopo(pilha1, &pecaPilha1);

	if (retornoPilha != PIL_CondRetOK){
		return JGO_CondRetErroPilha;
	}

	retornoJogo = ChecaRetiravel(pMatriz, linhaPeca1, colunaPeca1, &retornoChecaRetiravel);

	if (retornoJogo != JGO_CondRetOK){
		return retornoJogo;
	}

	if (retornoChecaRetiravel != JGO_CondRetOK){
		return JGO_CondRetPecaBloqueada;
	}

	//Pega pilha 2.

	retornoMatriz = MAT_IrParaCoordenada(*pMatriz, linhaPeca2, colunaPeca2);

	if (retornoMatriz != MAT_CondRetOK){
		return JGO_CondRetErroMatriz;
	}

	retornoMatriz = MAT_ObterValorCorr(*pMatriz, &pilha2);

	if (retornoMatriz != MAT_CondRetOK){
		return JGO_CondRetErroMatriz;
	}

	retornoPilha = PIL_ObterValorTopo(pilha2, &pecaPilha2);

	if (retornoPilha != PIL_CondRetOK){
		return JGO_CondRetErroPilha;
	}

	retornoJogo = ChecaRetiravel(pMatriz, linhaPeca2, colunaPeca2, &retornoChecaRetiravel);

	if (retornoJogo != JGO_CondRetOK){
		return retornoJogo;
	}

	if (retornoChecaRetiravel != JGO_CondRetOK){
		return JGO_CondRetPecaBloqueada;
	}

	//Compara Peças
	if (pecaPilha1 != pecaPilha2){
		return JGO_CondRetPecasDiferentes;
	}

	//Faz a remoção
	retornoPilha = PIL_DesempilhaValor(pilha1);

	if (retornoPilha != PIL_CondRetOK){
		return JGO_CondRetErroPilha;
	}

	retornoPilha = PIL_DesempilhaValor(pilha2);

	if (retornoPilha != PIL_CondRetOK){
		return JGO_CondRetErroPilha;
	}

	(*retorno) = 1;

	return JGO_CondRetOK;

} /* Fim função: Remove Pecas */

/***********************************************************************
*
*  $FC Função: Checa GameOver
*
*  $ED Descrição da função
*     Verifica se ainda é possível continuar o jogo.
*
*  $EP Parâmetros
*     pMatriz - ponteiro para a cabeça da Matriz usada como tabuleiro.
*     retorno - 0 se não for possível continuar o jogo, 1 caso seja possível e 2 caso de vitoria.
*
***********************************************************************/

JGO_tpCondRet ChecaGameOver (MAT_tppMatriz* pMatriz, int *retorno)
{
	//Pilha utilizada na análise.
	PIL_tppPilha pilha = NULL;

	//Valores de pilha
	char pecaPilha = NULL;

	//Contadores
	int contadorPecasA = 0;
	int contadorPecasB = 0;
	int contadorPecasC = 0;
	int contadorPecasD = 0;
	int contadorLinhas;
	int contadorColunas;

	//Variáveis de retorno.
	MAT_tpCondRet retornoMatriz;
	PIL_tpCondRet retornoPilha;
	JGO_tpCondRet retornoJogo;
	int retornoChecaRetiravel = 0;

	//Valor default de retorno é 0.
	(*retorno) = 1;

	//Percorre toda a Matriz e conta quantas pecas retiráveis existem de cada tipo.
	for (contadorLinhas = 0; contadorLinhas < LINHAS; contadorLinhas++){
		for (contadorColunas = 0; contadorColunas < COLUNAS; contadorColunas++){
			retornoMatriz = MAT_IrParaCoordenada(*pMatriz, contadorLinhas, contadorColunas);

			if (retornoMatriz != MAT_CondRetOK){
				return JGO_CondRetErroMatriz;
			}

			retornoMatriz = MAT_ObterValorCorr(*pMatriz, &pilha);

			if (retornoMatriz != MAT_CondRetOK){
				return JGO_CondRetErroMatriz;
			}

			retornoPilha = PIL_ObterValorTopo(pilha, &pecaPilha);

			if (retornoPilha != PIL_CondRetOK && retornoPilha != PIL_CondRetPilhaVazia){
				return JGO_CondRetErroPilha;
			}

			retornoJogo = ChecaRetiravel(pMatriz, contadorLinhas, contadorColunas, &retornoChecaRetiravel);

			if (retornoJogo != JGO_CondRetOK){
				return retornoJogo;
			}

			if (retornoChecaRetiravel == 1){
				if (pecaPilha == 'A'){
					contadorPecasA++;
				} else if (pecaPilha == 'B'){
					contadorPecasB++;
				} else if (pecaPilha == 'C'){
					contadorPecasC++;
				} else if (pecaPilha == 'D'){
					contadorPecasD++;
				}
			}
		}
	}

	//Verifica se ainda existe alguma jogada possível.
	if (contadorPecasA < 2 && contadorPecasB < 2 && contadorPecasC < 2 && contadorPecasD < 2)
	{
		if (contadorPecasA == 0 && contadorPecasB == 0 && contadorPecasC == 0 && contadorPecasD == 0){
			*retorno = 2; /*Caso de vitoria*/
			return JGO_CondRetOK;
		}
		*retorno = 0; /*Caso de derrota*/
		return JGO_CondRetOK;
	}
	*retorno = 1;
	return JGO_CondRetOK;

} /* Fim função: Checa GameOver */
