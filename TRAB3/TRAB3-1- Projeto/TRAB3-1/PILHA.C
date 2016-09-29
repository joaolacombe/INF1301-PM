/***************************************************************************
 *  $MCI Módulo de implementação: Módulo Pilha
 *
 *  Arquivo gerado:              PILHA.C
 *  Letras identificadoras:      PIL
 *
 *  Projeto: Disciplina INF 1301
 *
 *  Autores: gsg - Gabriel da Silva Gomes
 *			 gsb - Gustavo Severo Barros
 *	         jpmldg - João Pedro Masset Lacombe D Garcia
 *
 *  $HA Histórico de evolução:
 *     Versão       Autor          Data            Observações
 *      1.00         gsg        17/04/2016   Início do desenvolvimento
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
 *  $ED Descrição do tipo
 *     Descreve a organização da entrada da pilha
 *
 ***********************************************************************/


/***********************************************************************
 *
 *  $TC Tipo de dados: LIS Descritor da cabeça da pilha
 *
 ***********************************************************************/

typedef struct PIL_tagPilha
{
    LIS_tppLista pCabecaLista;
    /* Ponteiro para a cabeça da lista */
    
    int numElementos;
    /* Número de elementos da pilha */
    
} PIL_tpPilha;

/***** ProtÛtipos das funÁıes encapuladas no mÛdulo *****/

   static void DestruirValor( char * pValor ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
 *
 *  Função: PIL Criar pilha
 *
 ****/

PIL_tppPilha PIL_CriarPilha()
{
    LIS_tpCondRet condRetLista;
    PIL_tpPilha * pPilha = NULL;
    /* Cria cabeça da Pilha */
    
    pPilha = (PIL_tpPilha*) malloc (sizeof(PIL_tpPilha));
    
    if (pPilha == NULL)
    {
        return NULL;
    }
    
    pPilha->numElementos = 0;
    pPilha->pCabecaLista = LIS_CriarLista(DestruirValor);
    
    return pPilha;

} /* Fim função: PIL Criar pilha */

/***************************************************************************
 *
 *  Função: PIL Destruir pilha
 *
 ****/

PIL_tpCondRet PIL_DestruirPilha(PIL_tpPilha * pPilha)
{
    LIS_tpCondRet condRetLista;
    
    if (pPilha == NULL)
    {
        return PIL_CondRetPilhaNaoExiste;
    }
    
    /* Destrói Lista */
    LIS_DestruirLista(pPilha->pCabecaLista);
    /* Destrói Cabeça da Pilha */
    free(pPilha);
    pPilha = NULL;
    
    return PIL_CondRetOK;
    
} /* Fim função: PIL Destruir pilha */

/***************************************************************************
 *
 *  Função: PIL Inserir valor no topo da pilha
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
    
} /* Fim função: PIL Inserir valor no topo da pilha */

/***************************************************************************
 *
 *  Função: PIL Remover topo da pilha
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
    
} /* Fim função: PIL Remover topo da pilha */

/***************************************************************************
 *
 *  Função: PIL Obter valor topo
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
} /* Fim função: PIL Obter valor topo */

/***************************************************************************
 *
 *  Função: PIL Obter tamanho da pilha
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
    
} /* Fim função: PIL Obter tamanho da pilha*/

/***********************************************************************
*
*  $FC FunÁ„o: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( char pValor )
   {
      return;

   } /* Fim funÁ„o: TLIS -Destruir valor */

/********** Fim do módulo de implementação: Módulo pilha **********/