#if ! defined(MATRIZ_)
#define MATRIZ_

#include "LISTA.H"
#include "PILHA.H"

/***************************************************************************
 *
 *  $MCD Módulo de definição: Módulo matriz
 *
 *  Arquivo gerado:              MATRIZ.H
 *  Letras identificadoras:      MAT
 *
 *  Projeto: Disciplina INF 1301
 *
 *  Autores: gsg - Gabriel da Silva Gomes
 *			 gsb - Gustavo Severo Barros
 *	      jpmldg - João Pedro Masset Lacombe D Garcia
 *
 *  $HA Histórico de evolução:
 *     Versão       Autor          Data              Observações
 *       1.00        gsg        17/04/2016    Início do desenvolvimento
 *
 *  $ED Descrição do módulo
 *     Este módulo implementa um conjunto simples de funções para criar e
 *     explorar matrizes de listas de pilhas.
 *     A matriz possui uma referência para o nó corrente da matriz.
 *     O módulo é capaz de trabalhar com n matrizes.
 *     Ao iniciar a execução do programa não existe matriz.
 *     A matriz poderá estar vazia. Neste caso o nó corrente
 *     será nulo, embora a cabeça esteja definida.
 *     O nó corrente será nulo se e somente se a matriz estiver vazia.
 *
 ***************************************************************************/

#if defined(MATRIZ_OWN)
#define MATRIZ_EXT
#else
#define MATRIZ_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma matriz */

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
    /* Estrutura da matriz está errada */
    
    MAT_CondRetMatrizNaoExiste,
    /* Matriz não existe */
    
    MAT_CondRetMatrizVazia,
    /* Matriz está vazia */
    
    MAT_CondRetCoordenadaInexistente,
            /* Nó corrente não possui adjacente na direção desejada */
    
    MAT_CondRetFaltouMemoria
    /* Faltou memória ao alocar dados */
    
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
 *  $FC Função: MAT Criar matriz
 *
 *  $ED Descrição da função
 *     Cria uma nova matriz vazia.
 *     Caso já exista uma matriz, esta será destruída.
 *
 *  $EP Parâmetros
 *     $P pMatriz - ponteiro para a matriz a ser criada. Passado por referência.
 *     $P NumeroLinhas - número de linhas da matriz a ser criada.
 *     $P NumeroColunas - número de colunas da matriz a ser criada.
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
 *  $FC Função: MAT Destruir matriz
 *
 *  $ED Descrição da função
 *     Destrói o corpo e a cabeça da matriz, anulando o nó corrente.
 *
 *  $EP Parâmetros
 *     $P pMatriz - ponteiro para a matriz a ser excluída.
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *	  MAT_CondRetMatrizNaoExiste
 *
 ***********************************************************************/


MAT_tpCondRet MAT_DestruirMatriz(MAT_tpMatriz ** pMatriz);

/***********************************************************************
 *
 *  $FC Função: MAT Inserir valor no nó corrente
 *
 *  $ED Descrição da função
 *     Insere valor no nó corrente.
 *
 *  $EP Parâmetros
 *     $P pMatriz - ponteiro para a matriz a ser utilizada.
 *     $P ValorParm - valor a ser inserido no nó corrente.
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
 *  $FC Função: MAT Adicionar linha
 *
 *  $ED Descrição da função
 *     Adiciona uma nova linha, ao final da matriz.
 *
 *  $EP Parâmetros
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
 *  $FC Função: MAT Adicionar coluna
 *
 *  $ED Descrição da função
 *     Adiciona uma nova coluna, ao final da matriz.
 *
 *  $EP Parâmetros
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
 *  $FC Função: MAT Remover Linha
 *
 *  $ED Descrição da função
 *     Remove a última linha da matriz.
 *     Faz nada caso a matriz seja vazia ou não exista.
 *
 *  $EP Parâmetros
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
 *  $FC Função: MAT Remover Coluna
 *
 *  $ED Descrição da função
 *     Remove a última coluna da matriz.
 *     Faz nada caso a matriz seja vazia ou não exista.
 *
 *  $EP Parâmetros
 *     $P pMatriz - ponteiro para a matriz a ser utilizada. Passado por referência.
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
 *  $FC Função: MAT Ir para coordenada específica
 *
 *  $ED Descrição da função
 *     Move o nó corrente para uma coordenada específica (Ex.: L:1 e C: 2).
 *
 *  $EP Parâmetros
 *     $P pMatriz - ponteiro para a matriz a ser utilizada.
 *     $P linha - linha para onde o nó corrente irá avançar.
 *     $P coluna - coluna para onde o nó corrente irá avançar.
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
 *  $FC Função: MAT Ir para coordenada
 *
 *  $ED Descrição da função
 *     Move o nó corrente para uma direção (coordenada).
 *
 *  $EP Parâmetros
 *     $P pMatriz - ponteiro para a matriz a ser utilizada.
 *     $P Coordenada - coordenada para onde o nó corrente irá avançar.
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
 *  $FC Função: MAT Obter Valor Corrente
 *
 *  $ED Descrição da função
 *     Obtem o valor contido no nó corrente.
 *
 *  $EP Parâmetros
 *     $P pMatriz - ponteiro para a matriz a ser utilizada.
 *     $P ValorParm - valor do nó corrente. Este parâmetro é
 *					 passado por referência.
 *
 *  $FV Valor retornado
 *     MAT_CondRetOK
 *     MAT_CondRetMatrizNaoExiste
 *     MAT_CondRetMatrizVazia
 *
 ***********************************************************************/

MAT_tpCondRet MAT_ObterValorCorr(MAT_tppMatriz pMatriz, PIL_tppPilha pPilha);

#undef MAT_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif