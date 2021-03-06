/***************************************************************************
 *  $MCI M�dulo de implementa��o: M�dulo Pilha
 *
 *  Arquivo gerado:              PILHA.C
 *  Letras identificadoras:      PIL
 *
 *  Projeto: Disciplina INF 1301
 *
 *  Autores: gsg - Gabriel da Silva Gomes
 *			 gsb - Gustavo Severo Barros
 *	         jpmldg - Jo�o Pedro Masset Lacombe D Garcia
 *
 *  $HA Hist�rico de evolu��o:
 *     Vers�o       Autor          Data            Observa��es
 *      1.00         gsg        17/04/2016   In�cio do desenvolvimento
 *
 ***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#define LISTA_OWN
#include "LISTA.H"
#undef LIST_OWN

#define PILHA_OWN
#include "PILHA.H"
#undef PILHA_OWN

/***********************************************************************
 *
 *  $TC Tipo de dados: PIL Descritor do elemento da pilha
 *
 *
 *  $ED Descri��o do tipo
 *     Descreve a organiza��o da entrada da pilha
 *
 ***********************************************************************/


/***********************************************************************
 *
 *  $TC Tipo de dados: LIS Descritor da cabe�a da pilha
 *
 ***********************************************************************/

typedef struct PIL_tagPilha
{
    LIS_tppLista pCabecaLista;
    /* Ponteiro para a cabe�a da lista */
    
    int numElementos;
    /* N�mero de elementos da pilha */
    
} PIL_tpPilha;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void DestruirValor( char * pValor ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
 *
 *  Fun��o: PIL Criar pilha
 *
 ****/

PIL_tppPilha PIL_CriarPilha()
{
    LIS_tpCondRet condRetLista;
    PIL_tpPilha * pPilha = NULL;
    /* Cria cabe�a da Pilha */
    
    pPilha = (PIL_tpPilha*) malloc (sizeof(PIL_tpPilha));
    
    if (pPilha == NULL)
    {
        return NULL;
    }
    
    pPilha->numElementos = 0;
    pPilha->pCabecaLista = LIS_CriarLista(DestruirValor);
    
    return pPilha;

} /* Fim fun��o: PIL Criar pilha */

/***************************************************************************
 *
 *  Fun��o: PIL Destruir pilha
 *
 ****/

PIL_tpCondRet PIL_DestruirPilha(PIL_tpPilha * pPilha)
{
    LIS_tpCondRet condRetLista;
    
    if (pPilha == NULL)
    {
        return PIL_CondRetPilhaNaoExiste;
    }
    
    /* Destr�i Lista */
    LIS_DestruirLista(pPilha->pCabecaLista);
    /* Destr�i Cabe�a da Pilha */
    free(pPilha);
    pPilha = NULL;
    
    return PIL_CondRetOK;
    
} /* Fim fun��o: PIL Destruir pilha */

/***************************************************************************
 *
 *  Fun��o: PIL Inserir valor no topo da pilha
 *
 ****/

PIL_tpCondRet PIL_EmpilhaValor(PIL_tpPilha * pPilha, char ValorParm)
{
    LIS_tpCondRet condRetLista;

    if (pPilha == NULL)
    {
        return PIL_CondRetPilhaNaoExiste;
    }
    
    if ( testaCorrDiferenteOrigem((pPilha)->pCabecaLista) == 0 )
    {
        IrInicioLista((pPilha)->pCabecaLista);
    }
   
    condRetLista = LIS_InserirElementoAntes((pPilha)->pCabecaLista, ValorParm);
    
    if (condRetLista == LIS_CondRetFaltouMemoria)
    {
        return PIL_CondRetFaltouMemoria;
    }
    
    (pPilha)->numElementos++;
    
    return PIL_CondRetOK;
    
} /* Fim fun��o: PIL Inserir valor no topo da pilha */

/***************************************************************************
 *
 *  Fun��o: PIL Remover topo da pilha
 *
 ****/

PIL_tpCondRet PIL_DesempilhaValor(PIL_tpPilha *pPilha)
{
    LIS_tpCondRet condRetLista;
    
    if (pPilha == NULL)
    {
        return PIL_CondRetPilhaNaoExiste;
    }
    
    if (testaCorrDiferenteOrigem(pPilha->pCabecaLista) == 0)
    {
        IrInicioLista(pPilha->pCabecaLista);
    }
    
    condRetLista = LIS_ExcluirElemento(pPilha->pCabecaLista);
    
    if (condRetLista == LIS_CondRetListaVazia)
    {
        return PIL_CondRetPilhaVazia;
    }
    
    pPilha->numElementos--;
    
    return PIL_CondRetOK;
    
} /* Fim fun��o: PIL Remover topo da pilha */

/***************************************************************************
 *
 *  Fun��o: PIL Obter valor topo
 *
 ****/

PIL_tpCondRet PIL_ObterValorTopo(PIL_tpPilha *pPilha, char * ValorParm)
{
	char valor;
    if (pPilha == NULL)
    {
        return PIL_CondRetPilhaNaoExiste;
    }
    
    if (testaCorrDiferenteOrigem(pPilha->pCabecaLista) == 0)
    {
        IrInicioLista(pPilha->pCabecaLista);
    }

    *ValorParm = LIS_ObterValor(pPilha->pCabecaLista);
 
    if ((*ValorParm) == NULL)
    {
        return PIL_CondRetPilhaVazia;
    }

    
    return PIL_CondRetOK;
} /* Fim fun��o: PIL Obter valor topo */

/***************************************************************************
 *
 *  Fun��o: PIL Obter tamanho da pilha
 *
 ****/

PIL_tpCondRet PIL_ObterTamanho(PIL_tpPilha *pPilha, int * pTamanhoPilha)
{
    if (pPilha == NULL)
    {
        return PIL_CondRetPilhaNaoExiste;
    }
    
    *pTamanhoPilha = pPilha->numElementos;
    
    return PIL_CondRetOK;
    
} /* Fim fun��o: PIL Obter tamanho da pilha*/

/***********************************************************************
*
*  $FC Fun��o: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( char pValor )
   {
      return;

   } /* Fim fun��o: TLIS -Destruir valor */

/********** Fim do m�dulo de implementa��o: M�dulo pilha **********/