#if ! defined(PILHA_)
#define PILHA_

#include "LISTA.H"

/***************************************************************************
 *
 *  $MCD M�dulo de defini��o: M�dulo Pilha
 *
 *  Arquivo gerado:              PILHA.H
 *  Letras identificadoras:      PIL
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
 *     explorar pilhas.
 *     A pilha possui uma refer�ncia para o n� corrente da matriz.
 *     O m�dulo � capaz de trabalhar com n matrizes.
 *     Ao iniciar a execu��o do programa n�o existe matriz.
 *     A matriz poder� estar vazia. Neste caso o n� corrente
 *     ser� nulo, embora a cabe�a esteja definida.
 *     O n� corrente ser� nulo se e somente se a matriz estiver vazia.
 *
 ***************************************************************************/

#if defined(PILHA_OWN)
#define PILHA_EXT
#else
#define PILHA_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma pilha */

typedef struct PIL_tagPilha PIL_tpPilha;
typedef struct PIL_tagPilha * PIL_tppPilha;

/***********************************************************************
 *
 *  $TC Tipo de dados: PIL Condicoes de retorno
 *
 *
 ***********************************************************************/

typedef enum
{
    PIL_CondRetOK,
    /* Executou correto */
    
    PIL_CondRetPilhaNaoExiste,
    /* Pilha n�o existe */
    
    PIL_CondRetPilhaVazia,
    /* Pilha est� vazia */
    
    PIL_CondRetFaltouMemoria
    /* Faltou mem�ria ao alocar dados */
    
} PIL_tpCondRet;

/***********************************************************************
 *
 *  $FC Fun��o: PIL Criar pilha
 *
 *  $ED Descri��o da fun��o
 *     Cria uma nova pilha vazia.
 *     Caso j� exista uma pilha no par�metro passado, esta ser� destru�da.
 *
 *  $EP Par�metros
 *     $P pPilha - ponteiro para a pilha a ser criada. Passado por refer�ncia.
 *
 *  $FV Valor retornado
 *     PIL_CondRetOK
 *     PIL_CondRetFaltouMemoria
 *
 *  Assertivas de Entrada:
 *     - N�o possui.
 *
 *  Assertivas de Sa�da:
 *     - Se existe mem�ria dispon�vel, retorna um ponteiro para cabe�a da pilha criada.
 *
 ***********************************************************************/

PIL_tppPilha PIL_CriarPilha();

/***********************************************************************
 *
 *  $FC Fun��o: PIL Destruir pilha
 *
 *  $ED Descri��o da fun��o
 *     Destr�i o corpo e a cabe�a da pilha, anulando o n� corrente.
 *
 *  $EP Par�metros
 *     $P pPilha - ponteiro para a pilha a ser exclu�da.
 *
 *  $FV Valor retornado
 *     PIL_CondRetOK
 *	   PIL_CondRetPilhaNaoExiste
 *
 *  Assertivas de Entrada:
 *     - Deve existir um ponteiro para a pilha a ser destruida.
 *  
 *  Assertivas de Sa�da:
 *     - Se a pilha n�o � nula, ela � destruida e seu ponteiro aponta para NULL.
 *
 ***********************************************************************/

PIL_tpCondRet PIL_DestruirPilha(PIL_tppPilha pPilha);

/***********************************************************************
 *
 *  $FC Fun��o: PIL Inserir valor no topo da Pilha
 *
 *  $ED Descri��o da fun��o
 *     Insere valor no topo da pilha.
 *
 *  $EP Par�metros
 *     $P pPilha - ponteiro para a pilha a ser utilizada.
 *     $P ValorParm - valor a ser inserido no topo da pilha.
 *
 *  $FV Valor retornado
 *     PIL_CondRetOK
 *     PIL_CondRetPilhaNaoExiste
 *	   PIL_CondRetFaltouMemoria
 *
 *  Assertivas de Entrada:
 *     - Deve existir um ponteiro para a pilha a ser utilizada;
 *	   - Deve existir um valor a ser inserido na pilha.
 *
 *  Assertivas de Sa�da:
 *     - Se existe mem�ria dispon�vel e a pilha n�o � nula, o valor a 
 *       ser inserido � inserido no topo da pilha e o n�mero de elementos
 *       da pilha � incrementado.
 *
 ***********************************************************************/

PIL_tpCondRet PIL_EmpilhaValor(PIL_tppPilha pPilha, char ValorParm);

/***********************************************************************
 *
 *  $FC Fun��o: PIL Remove valor no topo da Pilha
 *
 *  $ED Descri��o da fun��o
 *     Remove valor no topo da pilha.
 *
 *  $EP Par�metros
 *     $P pPilha - ponteiro para a pilha a ser utilizada.
 *
 *  $FV Valor retornado
 *     PIL_CondRetOK
 *     PIL_CondRetPilhaNaoExiste
 *
 *  Assertivas de Entrada:
 *     - Deve existir um ponteiro para a pilha a ser utilizada.
 *
 *  Assertivas de Sa�da:
 *     -  Se a pilha n�o � nula e n�o � vazia, o valor do topo da pilha � 
 *        removido e o n�mero de elementos da pilha � decrementado.
 *
 ***********************************************************************/

PIL_tpCondRet PIL_DesempilhaValor(PIL_tppPilha pPilha);

/***********************************************************************
 *
 *  $FC Fun��o: PIL Obter Valor do Topo da Pilha
 *
 *  $ED Descri��o da fun��o
 *     Obtem o valor contido no topo da pilha.
 *
 *  $EP Par�metros
 *     $P pPilha   - ponteiro para a pilha a ser utilizada.
 *     $P ValorParm - valor do topo da pilha. Este par�metro �
 *					 passado por refer�ncia.
 *
 *  $FV Valor retornado
 *     PIL_CondRetOK
 *     PIL_CondRetPilhaNaoExiste
 *     PIL_CondRetPilhaVazia
 *
 *  Assertivas de Entrada:
 *     - Deve existir um ponteiro para a pilha a ser utilizada.
 *	   - Deve existir um ponteiro por onde ser� passado, por refer�ncia, 
 *       o valor do topo da pilha.
 *
 *  Assertivas de Sa�da:
 *     -  Se a pilha n�o � nula e n�o � vazia, ValorParm � atualizado.
 *
 ***********************************************************************/

PIL_tpCondRet PIL_ObterValorTopo(PIL_tppPilha pPilha, char * ValorParm);

/***********************************************************************
 *
 *  $FC Fun��o: PIL Obter Tamanho da Pilha
 *
 *  $ED Descri��o da fun��o
 *     Obtem o tamanho da pilha.
 *
 *  $EP Par�metros
 *     $P pPilha        - ponteiro para a pilha a ser utilizada.
 *     $P pTamanhoPilha - Tamanho da Pilha. Este par�metro �
 *					 passado por refer�ncia.
 *
 *  $FV Valor retornado
 *     PIL_CondRetOK
 *     PIL_CondRetPilhaNaoExiste
 *
 *  Assertivas de Entrada:
 *     - Deve existir um ponteiro para a pilha a ser utilizada.
 *	   - Deve existir um ponteiro por onde ser� passado, por refer�ncia,
 *       o tamanho da pilha.
 *
 *  Assertivas de Sa�da:
 *     -  Se a pilha n�o � nula, pTamanhoPilha � atualizado.
 *
 ***********************************************************************/

PIL_tpCondRet PIL_ObterTamanho(PIL_tppPilha pPilha, int * pTamanhoPilha);

#undef MAT_EXT

/********** Fim do m�dulo de defini��o: M�dulo Pilha **********/

#else
#endif