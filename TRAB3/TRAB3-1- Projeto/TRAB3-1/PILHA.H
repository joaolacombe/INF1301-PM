#if ! defined(PILHA_)
#define PILHA_

#include "LISTA.H"

/***************************************************************************
 *
 *  $MCD Módulo de definição: Módulo Pilha
 *
 *  Arquivo gerado:              PILHA.H
 *  Letras identificadoras:      PIL
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
 *     explorar pilhas.
 *     A pilha possui uma referência para o nó corrente da matriz.
 *     O módulo é capaz de trabalhar com n matrizes.
 *     Ao iniciar a execução do programa não existe matriz.
 *     A matriz poderá estar vazia. Neste caso o nó corrente
 *     será nulo, embora a cabeça esteja definida.
 *     O nó corrente será nulo se e somente se a matriz estiver vazia.
 *
 ***************************************************************************/

#if defined(PILHA_OWN)
#define PILHA_EXT
#else
#define PILHA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma pilha */

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
    /* Pilha não existe */
    
    PIL_CondRetPilhaVazia,
    /* Pilha está vazia */
    
    PIL_CondRetFaltouMemoria
    /* Faltou memória ao alocar dados */
    
} PIL_tpCondRet;

/***********************************************************************
 *
 *  $FC Função: PIL Criar pilha
 *
 *  $ED Descrição da função
 *     Cria uma nova pilha vazia.
 *     Caso já exista uma pilha no parâmetro passado, esta será destruída.
 *
 *  $EP Parâmetros
 *     $P pPilha - ponteiro para a pilha a ser criada. Passado por referência.
 *
 *  $FV Valor retornado
 *     PIL_CondRetOK
 *     PIL_CondRetFaltouMemoria
 *
 *  Assertivas de Entrada:
 *     - Não possui.
 *
 *  Assertivas de Saída:
 *     - Se existe memória disponível, retorna um ponteiro para cabeça da pilha criada.
 *
 ***********************************************************************/

PIL_tppPilha PIL_CriarPilha();

/***********************************************************************
 *
 *  $FC Função: PIL Destruir pilha
 *
 *  $ED Descrição da função
 *     Destrói o corpo e a cabeça da pilha, anulando o nó corrente.
 *
 *  $EP Parâmetros
 *     $P pPilha - ponteiro para a pilha a ser excluída.
 *
 *  $FV Valor retornado
 *     PIL_CondRetOK
 *	   PIL_CondRetPilhaNaoExiste
 *
 *  Assertivas de Entrada:
 *     - Deve existir um ponteiro para a pilha a ser destruida.
 *  
 *  Assertivas de Saída:
 *     - Se a pilha não é nula, ela é destruida e seu ponteiro aponta para NULL.
 *
 ***********************************************************************/

PIL_tpCondRet PIL_DestruirPilha(PIL_tppPilha pPilha);

/***********************************************************************
 *
 *  $FC Função: PIL Inserir valor no topo da Pilha
 *
 *  $ED Descrição da função
 *     Insere valor no topo da pilha.
 *
 *  $EP Parâmetros
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
 *  Assertivas de Saída:
 *     - Se existe memória disponível e a pilha não é nula, o valor a 
 *       ser inserido é inserido no topo da pilha e o número de elementos
 *       da pilha é incrementado.
 *
 ***********************************************************************/

PIL_tpCondRet PIL_EmpilhaValor(PIL_tppPilha pPilha, char ValorParm);

/***********************************************************************
 *
 *  $FC Função: PIL Remove valor no topo da Pilha
 *
 *  $ED Descrição da função
 *     Remove valor no topo da pilha.
 *
 *  $EP Parâmetros
 *     $P pPilha - ponteiro para a pilha a ser utilizada.
 *
 *  $FV Valor retornado
 *     PIL_CondRetOK
 *     PIL_CondRetPilhaNaoExiste
 *
 *  Assertivas de Entrada:
 *     - Deve existir um ponteiro para a pilha a ser utilizada.
 *
 *  Assertivas de Saída:
 *     -  Se a pilha não é nula e não é vazia, o valor do topo da pilha é 
 *        removido e o número de elementos da pilha é decrementado.
 *
 ***********************************************************************/

PIL_tpCondRet PIL_DesempilhaValor(PIL_tppPilha pPilha);

/***********************************************************************
 *
 *  $FC Função: PIL Obter Valor do Topo da Pilha
 *
 *  $ED Descrição da função
 *     Obtem o valor contido no topo da pilha.
 *
 *  $EP Parâmetros
 *     $P pPilha   - ponteiro para a pilha a ser utilizada.
 *     $P ValorParm - valor do topo da pilha. Este parâmetro é
 *					 passado por referência.
 *
 *  $FV Valor retornado
 *     PIL_CondRetOK
 *     PIL_CondRetPilhaNaoExiste
 *     PIL_CondRetPilhaVazia
 *
 *  Assertivas de Entrada:
 *     - Deve existir um ponteiro para a pilha a ser utilizada.
 *	   - Deve existir um ponteiro por onde será passado, por referência, 
 *       o valor do topo da pilha.
 *
 *  Assertivas de Saída:
 *     -  Se a pilha não é nula e não é vazia, ValorParm é atualizado.
 *
 ***********************************************************************/

PIL_tpCondRet PIL_ObterValorTopo(PIL_tppPilha pPilha, char * ValorParm);

/***********************************************************************
 *
 *  $FC Função: PIL Obter Tamanho da Pilha
 *
 *  $ED Descrição da função
 *     Obtem o tamanho da pilha.
 *
 *  $EP Parâmetros
 *     $P pPilha        - ponteiro para a pilha a ser utilizada.
 *     $P pTamanhoPilha - Tamanho da Pilha. Este parâmetro é
 *					 passado por referência.
 *
 *  $FV Valor retornado
 *     PIL_CondRetOK
 *     PIL_CondRetPilhaNaoExiste
 *
 *  Assertivas de Entrada:
 *     - Deve existir um ponteiro para a pilha a ser utilizada.
 *	   - Deve existir um ponteiro por onde será passado, por referência,
 *       o tamanho da pilha.
 *
 *  Assertivas de Saída:
 *     -  Se a pilha não é nula, pTamanhoPilha é atualizado.
 *
 ***********************************************************************/

PIL_tpCondRet PIL_ObterTamanho(PIL_tppPilha pPilha, int * pTamanhoPilha);

#undef MAT_EXT

/********** Fim do módulo de definição: Módulo Pilha **********/

#else
#endif