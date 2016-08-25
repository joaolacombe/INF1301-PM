#if ! defined( ARVORE_ )
#define ARVORE_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo árvore
*
*  Arquivo gerado:              ARVORE.H
*  Letras identificadoras:      ARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Autores: avs - Arndt von Staa
*			gg - Gabriel Gomes
*			gs - Gustavo Severo
*			jg - Joao Garcia
*
*  $HA Histórico de evolução:
*     Versão	Autor		Data      Observações
*		4.00   gg,gs,jg  28/03/2016	 Alteração de métodos para o recebimento de
									 ponteiro para árvore como parâmetro e
									 alteração no nó da árvore para armazenamento de 
									 um ponteiro de uma lista de caracteres.
*       3.00	 avs	 28/02/2003	 Uniformização da interface das funções e
*									 de todas as condições de retorno.
*       2.00	 avs	 03/08/2002	 Eliminação de código duplicado, reestruturação
*       1.00	 avs	 15/08/2001  Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este módulo implementa um conjunto simples de funções para criar e
*     explorar árvores binárias.
*     A árvore possui uma cabeça que contém uma referência para a raíz da
*     árvore e outra para um nó corrente de uma árvore.
*     A cada momento o módulo admite mais de uma árvore.
*     Ao iniciar a execução do programa não existe árvore.
*     A árvore poderá estar vazia. Neste caso a raiz e o nó corrente
*     serão nulos, embora a cabeça esteja definida.
*     O nó corrente de uma árvore será nulo se e somente se a árvore estiver
*     vazia.
*
***************************************************************************/
 
#if defined( ARVORE_OWN )
   #define ARVORE_EXT
#else
   #define ARVORE_EXT extern
#endif

#include "LISTA.H"
/***********************************************************************
*
*  $TC Tipo de dados: ARV Condicoes de retorno
*
*
***********************************************************************/

   typedef enum {

         ARV_CondRetOK = 0 ,
               /* Executou correto */

         ARV_CondRetNaoCriouRaiz = 1 ,
               /* Não criou nó raiz */

         ARV_CondRetErroEstrutura = 2 ,
               /* Estrutura da árvore está errada */

         ARV_CondRetNaoEhFolha = 3 ,
               /* Não é folha relativa à direção de inserção desejada */

         ARV_CondRetArvoreNaoExiste = 4 ,
               /* Árvore não existe */

         ARV_CondRetArvoreVazia = 5 ,
               /* Árvore está vazia */

         ARV_CondRetNohEhRaiz = 6 ,
               /* Nó corrente é raiz */

         ARV_CondRetNaoPossuiFilho = 7 ,
               /* Nó corrente não possui filho na direção desejada */

         ARV_CondRetFaltouMemoria = 8
               /* Faltou memória ao alocar dados */

   } ARV_tpCondRet ;

   typedef struct tpArvore* ptArvore;

/***********************************************************************
*
*  $FC Função: ARV Criar árvore
*
*  $ED Descrição da função
*     Cria uma nova árvore vazia.
*     Caso já exista uma árvore, esta será destruída.
*
*  $EP Parâmetros
*     $P pArvore   - é o parâmetro que receberá o ponteiro para árvore.
*					 Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*
***********************************************************************/

   ARV_tpCondRet ARV_CriarArvore(ptArvore* pArvore);


/***********************************************************************
*
*  $FC Função: ARV Destruir árvore
*
*  $EP Parâmetros
*     $P pArvore   - é o parâmetro que receberá o ponteiro para árvore.
*					 Este parâmetro é passado por referência.
*	
*  $ED Descrição da função
*     Destrói o corpo e a cabeça da árvore, anulando a árvore corrente.
*     Faz nada caso a árvore corrente não exista.
*
***********************************************************************/

   void ARV_DestruirArvore(ptArvore* pArvore);


/***********************************************************************
*
*  $FC Função: ARV Adicionar filho à esquerda
*
*  $EP Parâmetros
*     $P pArvore   - é o parâmetro que receberá o ponteiro para árvore.
*					 Este parâmetro é passado por referência.
*     $P ValorParm - é o parâmetro que receberá o ponteiro para a lista.
*                    Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetErroEstrutura
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoEhFolha     - caso não seja folha para a esquerda
*
***********************************************************************/


   ARV_tpCondRet ARV_InserirEsquerda(ptArvore* pArvore, LIS_tppLista* ValorParm ) ;


/***********************************************************************
*
*  $FC Função: ARV Adicionar filho à direita
*
*  $EP Parâmetros
*     $P pArvore   - é o parâmetro que receberá o ponteiro para árvore.
*					 Este parâmetro é passado por referência.
*     $P ValorParm - é o parâmetro que receberá o ponteiro para a lista.
*                    Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetErroEstrutura
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoEhFolha     - caso não seja folha para a direita
*
***********************************************************************/


   ARV_tpCondRet ARV_InserirDireita(ptArvore* pArvore, LIS_tppLista* ValorParm);


/***********************************************************************
*
*  $FC Função: ARV Ir para nó pai
*
*  $EP Parâmetros
*     $P pArvore   - é o parâmetro que receberá o ponteiro para árvore.
*					 Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*     ARV_CondRetNoEhRaiz
*
***********************************************************************/

   ARV_tpCondRet ARV_IrPai(ptArvore* pArvore) ;


/***********************************************************************
*
*  $FC Função: ARV Ir para nó à esquerda
*
*  $EP Parâmetros
*     $P pArvore   - é o parâmetro que receberá o ponteiro para árvore.
*					 Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*     ARV_CondRetNaoPossuiFilho   - nó corrente não possui filho à esquerda
*
***********************************************************************/

   ARV_tpCondRet ARV_IrNoEsquerda(ptArvore* pArvore);


/***********************************************************************
*
*  $FC Função: ARV Ir para nó à direita
*
*  $EP Parâmetros
*     $P pArvore   - é o parâmetro que receberá o ponteiro para árvore.
*					 Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*     ARV_CondRetNaoPossuiFilho   - nó corrente não possui filho à direita
*
***********************************************************************/

   ARV_tpCondRet ARV_IrNoDireita(ptArvore* pArvore) ;


/***********************************************************************
*
*  $FC Função: ARV Obter valor corrente
*
*  $EP Parâmetros
*     $P pArvore   - é o parâmetro que receberá o ponteiro para árvore.
*					 Este parâmetro é passado por referência.
*     $P ValorParm - é o parâmetro que receberá o ponteiro para a lista 
*					 contido no nó.
*                    Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetArvoreNaoExiste
*     ARV_CondRetArvoreVazia
*
***********************************************************************/

   ARV_tpCondRet ARV_ObterValorCorr(ptArvore* pArvore, int * ValorParm);

#undef ARVORE_EXT

/********** Fim do módulo de definição: Módulo árvore **********/

#else
#endif
