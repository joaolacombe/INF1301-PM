#if ! defined(MATRIZ_)
#define MATRIZ_

#include "LISTA.H"
#include "PILHA.H"

/***************************************************************************
 *
 *  $MCD M�dulo de defini��o: M�dulo matriz
 *
 *  Arquivo gerado:              MATRIZ.H
 *  Letras identificadoras:      MAT
 *
 *  Projeto: Disciplina INF 1301
 *
 *  Autores: gsg - Gabriel da Silva Gomes
 *			 gsb - Gustavo Severo Barros
 *	      jpmldg - Jo�o Pedro Masset Lacombe D Garcia
 *
 *  $HA Hist�rico de evolu��o:
 *     Vers�o       Autor          Data              Observa��es
 *       1.00        gsg        17/04/2016    In�cio do desenvolvimento
 *
 *  $ED Descri��o do m�dulo
 *     Este m�dulo implementa um conjunto simples de fun��es para criar e
 *     explorar matrizes de listas de pilhas.
 *     A matriz possui uma refer�ncia para o n� corrente da matriz.
 *     O m�dulo � capaz de trabalhar com n matrizes.
 *     Ao iniciar a execu��o do programa n�o existe matriz.
 *     A matriz poder� estar vazia. Neste caso o n� corrente
 *     ser� nulo, embora a cabe�a esteja definida.
 *     O n� corrente ser� nulo se e somente se a matriz estiver vazia.
 *
 ***************************************************************************/

#if defined(MATRIZ_OWN)
#define MATRIZ_EXT
#else
#define MATRIZ_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma matriz */

typedef struct MAT_tagMatriz MAT_tpMatriz;
typedef struct MAT_tagMatriz * MAT_tppMatriz;

/***********************************************************************
 *
 *  $TC Tipo de dados: MAT Condicoes de retorno
 *
 *
 ***********************************************************************/

typedef enum
{
    MAT_CondRetOK,
    /* Executou correto */
    
    MAT_CondRetErroEstrutura,
    /* Estrutura da matriz est� errada */
    
    MAT_CondRetMatrizNaoExiste,
    /* Matriz n�o existe */
    
    MAT_CondRetMatrizVazia,
    /* Matriz est� vazia */
    
    MAT_CondRetCoordenadaInexistente,
            /* N� corrente n�o possui adjacente na dire��o desejada */
    
    MAT_CondRetFaltouMemoria
    /* Faltou mem�ria ao alocar dados */
    
} MAT_tpCondRet;


/***********************************************************************
 *
 *  $TC Tipo de dados: MAT Coordenadas
 *
 *
 ***********************************************************************/

typedef enum
{
    MAT_CoordNorte = 0 ,
    /* Coordenada Norte */
    
    MAT_CoordSudoeste = 1 ,
    /* Coordenada Sudoeste */
    
    MAT_CoordOeste = 2 ,
    /* Coordenada Oeste */
    
    MAT_CoordNoroeste = 3 ,
    /* Coordenada Noroeste */
    
    MAT_CoordSul = 4 ,
    /* Coordenada Sul */
    
    MAT_CoordNordeste = 5 ,
    /* Coordenada Nordeste */
    
    MAT_CoordLeste = 6 ,
    /* Coordenada Leste */
    
    MAT_CoordSudeste = 7 ,
    /* Coordneada Sudeste */
    
} MAT_tpCoord;


/***********************************************************************
 *
 *  $FC Fun��o: MAT Criar matriz
 *
 *  $ED Descri��o da fun��o
 *     Cria uma nova matriz vazia.
 *     Caso j� exista uma matriz, esta ser� destru�da.
 *
 *  $EP Par�metros
 *     $P pMatriz - ponteiro para a matriz a ser criada. Passado por refer�ncia.
 *     $P NumeroLinhas - n�mero de linhas da matriz a ser criada.
 *     $P NumeroColunas - n�mero de colunas da matriz a ser criada.
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *	  MAT_CondRetErroEstrutura
 *     MAT_CondRetFaltouMemoria
 *
 ***********************************************************************/

MAT_tpCondRet MAT_CriarMatriz(MAT_tpMatriz **pMatriz, int NumeroLinhas, int NumeroColunas);


/***********************************************************************
 *
 *  $FC Fun��o: MAT Destruir matriz
 *
 *  $ED Descri��o da fun��o
 *     Destr�i o corpo e a cabe�a da matriz, anulando o n� corrente.
 *
 *  $EP Par�metros
 *     $P pMatriz - ponteiro para a matriz a ser exclu�da.
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *	  MAT_CondRetMatrizNaoExiste
 *
 ***********************************************************************/


MAT_tpCondRet MAT_DestruirMatriz(MAT_tpMatriz ** pMatriz);

/***********************************************************************
 *
 *  $FC Fun��o: MAT Inserir valor no n� corrente
 *
 *  $ED Descri��o da fun��o
 *     Insere valor no n� corrente.
 *
 *  $EP Par�metros
 *     $P pMatriz - ponteiro para a matriz a ser utilizada.
 *     $P ValorParm - valor a ser inserido no n� corrente.
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *     MAT_CondRetMatrizVazia
 *     MAT_CondRetMatrizNaoExiste
 *	  MAT_CondRetFaltouMemoria
 *
 ***********************************************************************/

MAT_tpCondRet MAT_InserirValor(MAT_tpMatriz *pMatriz, PIL_tppPilha pPilha);

/***********************************************************************
 *
 *  $FC Fun��o: MAT Adicionar linha
 *
 *  $ED Descri��o da fun��o
 *     Adiciona uma nova linha, ao final da matriz.
 *
 *  $EP Par�metros
 *     $P pMatriz - ponteiro para a matriz a ser utilizada.
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *     MAT_CondRetMatrizNaoExiste
 *     MAT_CondRetFaltouMemoria
 *
 ***********************************************************************/

MAT_tpCondRet MAT_AdicionarLinha(MAT_tppMatriz pMatriz);

/***********************************************************************
 *
 *  $FC Fun��o: MAT Adicionar coluna
 *
 *  $ED Descri��o da fun��o
 *     Adiciona uma nova coluna, ao final da matriz.
 *
 *  $EP Par�metros
 *     $P pMatriz - ponteiro para a matriz a ser utilizada.
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *     MAT_CondRetMatrizNaoExiste
 *     MAT_CondRetFaltouMemoria
 *
 ***********************************************************************/

MAT_tpCondRet MAT_AdicionarColuna(MAT_tppMatriz pMatriz);

/***********************************************************************
 *
 *  $FC Fun��o: MAT Remover Linha
 *
 *  $ED Descri��o da fun��o
 *     Remove a �ltima linha da matriz.
 *     Faz nada caso a matriz seja vazia ou n�o exista.
 *
 *  $EP Par�metros
 *     $P pMatriz - ponteiro para a matriz a ser utilizada.
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *     MAT_CondRetMatrizNaoExiste
 *     MAT_CondRetMatrizVazia
 *
 ***********************************************************************/

MAT_tpCondRet MAT_RemoverLinha(MAT_tppMatriz pMatriz);

/***********************************************************************
 *
 *  $FC Fun��o: MAT Remover Coluna
 *
 *  $ED Descri��o da fun��o
 *     Remove a �ltima coluna da matriz.
 *     Faz nada caso a matriz seja vazia ou n�o exista.
 *
 *  $EP Par�metros
 *     $P pMatriz - ponteiro para a matriz a ser utilizada. Passado por refer�ncia.
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *     MAT_CondRetMatrizNaoExiste
 *     MAT_CondRetMatrizVazia
 *
 ***********************************************************************/

MAT_tpCondRet MAT_RemoverColuna(MAT_tppMatriz pMatriz);

/***********************************************************************
 *
 *  $FC Fun��o: MAT Ir para coordenada espec�fica
 *
 *  $ED Descri��o da fun��o
 *     Move o n� corrente para uma coordenada espec�fica (Ex.: L:1 e C: 2).
 *
 *  $EP Par�metros
 *     $P pMatriz - ponteiro para a matriz a ser utilizada.
 *     $P linha - linha para onde o n� corrente ir� avan�ar.
 *     $P coluna - coluna para onde o n� corrente ir� avan�ar.
 *
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *     MAT_CondRetMatrizNaoExiste
 *     MAT_CondRetMatrizVazia
 *     MAT_CondRetCoordenadaInexistente
 *
 ***********************************************************************/

MAT_tpCondRet MAT_IrParaCoordenada(MAT_tppMatriz pMatriz, int linha, int coluna);

/***********************************************************************
 *
 *  $FC Fun��o: MAT Ir para coordenada
 *
 *  $ED Descri��o da fun��o
 *     Move o n� corrente para uma dire��o (coordenada).
 *
 *  $EP Par�metros
 *     $P pMatriz - ponteiro para a matriz a ser utilizada.
 *     $P Coordenada - coordenada para onde o n� corrente ir� avan�ar.
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *     MAT_CondRetMatrizNaoExiste
 *     MAT_CondRetMatrizVazia
 *	  MAT_CondRetCoordenadaInexistente
 *
 ***********************************************************************/

MAT_tpCondRet MAT_IrPara(MAT_tppMatriz pMatriz, MAT_tpCoord Coordenada);

/***********************************************************************
 *
 *  $FC Fun��o: MAT Obter Valor Corrente
 *
 *  $ED Descri��o da fun��o
 *     Obtem o valor contido no n� corrente.
 *
 *  $EP Par�metros
 *     $P pMatriz - ponteiro para a matriz a ser utilizada.
 *     $P ValorParm - valor do n� corrente. Este par�metro �
 *					 passado por refer�ncia.
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *     MAT_CondRetMatrizNaoExiste
 *     MAT_CondRetMatrizVazia
 *
 ***********************************************************************/

MAT_tpCondRet MAT_ObterValorCorr(MAT_tppMatriz pMatriz, PIL_tppPilha pPilha);

#undef MAT_EXT

/********** Fim do m�dulo de defini��o: M�dulo matriz **********/

#else
#endif