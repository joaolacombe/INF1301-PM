/***************************************************************************
 *  $MCI M�dulo de implementa��o: M�dulo matriz
 *
 *  Arquivo gerado:              MATRIZ.C
 *  Letras identificadoras:      MAT
 *
 *  Projeto: Disciplina INF 1301
 *
 *  Autores: gsg - Gabriel da Silva Gomes
 *			 gsb - Gustavo Severo Barros
 *	      jpmldg - Jo�o Pedro Masset Lacombe D Garcia
 *
 *  $HA Hist�rico de evolu��o:
 *     Vers�o       Autor          Data            Observa��es
 *      1.00         gsg        17/04/2016   In�cio do desenvolvimento
 *
 ***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>

#include "PILHA.H"

#define MATRIZ_OWN
#include "MATRIZ.H"
#undef MATRIZ_OWN

/***********************************************************************
 *
 *  $TC Tipo de dados: MAT Descritor do n� da matriz
 *
 *
 *  $ED Descri��o do tipo
 *     Descreve a organiza��o da entrada da matriz
 *
 ***********************************************************************/

typedef struct tgNoMatriz
{
    struct tgNoMatriz * pEntradaNorte;
    /* Ponteiro para entrada norte
     *
     */
    
    struct tgNoMatriz * pEntradaNordeste;
    /* Ponteiro para entrada nordeste
     *
     */
    
    struct tgNoMatriz * pEntradaLeste;
    /* Ponteiro para entrada leste
     *
     */
    
    struct tgNoMatriz * pEntradaSudeste;
    /* Ponteiro para entrada sudeste
     *
     */
    
    struct tgNoMatriz * pEntradaSul;
    /* Ponteiro para entrada sul
     *
     */
    
    struct tgNoMatriz * pEntradaSudoeste;
    /* Ponteiro para entrada sudoeste
     *
     */
    
    struct tgNoMatriz * pEntradaOeste;
    /* Ponteiro para entrada oeste
     *
     */
    
    struct tgNoMatriz * pEntradaNoroeste;
    /* Ponteiro para entrada noroeste
     *
     */
    
    int linhaMatriz;
    /* Linha do n� na matriz
     *
     */
    
    int colunaMatriz;
    /* Coluna do n� na matriz
     *
     */
    
    PIL_tppPilha pCabecaPilha;
    /* Ponteiro para a cabe�a da pilha */
    
} tpNoMatriz;

/***********************************************************************
 *
 *  $TC Tipo de dados: PIL Descritor da cabe�a da matriz1
 *
 ***********************************************************************/

typedef struct MAT_tagMatriz
{
    tpNoMatriz* pElemOrigem;
    /* Ponteiro para a origem da matriz */
    
    tpNoMatriz* pElemCorr;
    /* Ponteiro para o elemento corrente da matriz */
    
    int numLinhas;
    /* N�mero de linhas da matriz */
    
    int numColunas;
    /* N�mero de colunas da matriz */
    
} MAT_tpMatriz;

/*****  Dados encapsulados no m�dulo  *****/


/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static tpNoMatriz * CriarNo(void);

static void ExcluirNoMatriz(tpNoMatriz *pNoMatriz);

static void AvancaPrimeiraLinha(MAT_tpMatriz *pMatriz);

static void AvancaUltimaLinha(MAT_tpMatriz *pMatriz);

static void AvancaPrimeiraColuna(MAT_tpMatriz *pMatriz);

static void AvancaUltimaColuna(MAT_tpMatriz *pMatriz);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
 *
 *  Fun��o: MAT Criar matriz
 *
 ****/

MAT_tpCondRet MAT_CriarMatriz(MAT_tpMatriz **pMatriz, int NumeroLinhas, int NumeroColunas)
{
    int linhaAtual = 0;
    
    if(NumeroLinhas <= 0 || NumeroColunas <= 0)
    {
        return MAT_CondRetErroEstrutura;
    }
    
    *pMatriz = (MAT_tpMatriz*) malloc(sizeof(MAT_tpMatriz));
    
    if(pMatriz == NULL)
    {
        return MAT_CondRetFaltouMemoria;
    }
    
    (*pMatriz)->pElemCorr = NULL;
    (*pMatriz)->numLinhas = 0;
    (*pMatriz)->numColunas = NumeroColunas;
    
    for(linhaAtual = 1; linhaAtual <= NumeroLinhas; linhaAtual++)
    {
        if(MAT_AdicionarLinha(*pMatriz) == MAT_CondRetFaltouMemoria)
        {
            return MAT_CondRetFaltouMemoria;
        }
    }
    
    AvancaPrimeiraLinha(*pMatriz);
    AvancaPrimeiraColuna(*pMatriz);
    
    (*pMatriz)->pElemOrigem = (*pMatriz)->pElemCorr;
   
    return MAT_CondRetOK;
    
} /* Fim fun��o: MAT Criar matriz */

/***************************************************************************
 *
 *  Fun��o: MAT Destruir matriz
 *
 ****/

MAT_tpCondRet MAT_DestruirMatriz(MAT_tpMatriz ** pMatriz)
{
    if(*pMatriz == NULL)
    {
        return MAT_CondRetMatrizNaoExiste;
    }
    
    while((*pMatriz)->numColunas > 0)
    {
        MAT_RemoverColuna((*pMatriz));
    }
    
    free((*pMatriz));
    pMatriz = NULL;
    
    return MAT_CondRetOK ;
} /* Fim fun��o: MAT Destruir matriz */

/***************************************************************************
 *
 *  Fun��o: MAT Inserir valor no n� corrente
 *
 ****/

MAT_tpCondRet MAT_InserirValor(MAT_tpMatriz *pMatriz, PIL_tppPilha pPilha)
{
    if(pMatriz == NULL)
    {
        return MAT_CondRetMatrizNaoExiste;
    }
    
    if(pMatriz->pElemCorr == NULL)
    {
        return MAT_CondRetMatrizVazia;
    }
    
    pMatriz->pElemCorr->pCabecaPilha = pPilha;
    
    return MAT_CondRetOK;
    
} /* Fim fun��o: MAT Inserir valor no n� corrente */

/***************************************************************************
 *
 *  Fun��o: MAT Adicionar Linha
 *
 ****/

MAT_tpCondRet MAT_AdicionarLinha(MAT_tppMatriz pMatriz)
{
    int colunaAtual;
    tpNoMatriz *pElemInicioLinha, *pElemAnterior, *pNoCriado;
    
    if(pMatriz == NULL)
    {
        return MAT_CondRetMatrizNaoExiste;
    }
    
    /* Move o pElemCorr at� a primeira coluna da �ltima linha*/
    AvancaPrimeiraColuna(pMatriz);
    AvancaUltimaLinha(pMatriz);
    
    pElemInicioLinha = CriarNo();
    
    if(pElemInicioLinha == NULL)
    {
        return MAT_CondRetFaltouMemoria;
    }
    
    pElemInicioLinha->linhaMatriz = pMatriz->numLinhas + 1;
    pElemInicioLinha->colunaMatriz = 1;
    
    if(pMatriz->pElemCorr != NULL)
    {
        pElemInicioLinha->pEntradaNorte = pMatriz->pElemCorr;
        pMatriz->pElemCorr->pEntradaSul = pElemInicioLinha;
    }
    
    else
    {
        pMatriz->pElemCorr = pElemInicioLinha;
    }
    
    if(pElemInicioLinha->pEntradaNorte != NULL && pElemInicioLinha->pEntradaNorte->pEntradaLeste != NULL)
    {
        pElemInicioLinha->pEntradaNorte->pEntradaLeste->pEntradaSudoeste = pElemInicioLinha;
        pElemInicioLinha->pEntradaNordeste = pElemInicioLinha->pEntradaNorte->pEntradaLeste;
    }
    
    pElemAnterior = pElemInicioLinha;
    
    for(colunaAtual = 2; colunaAtual <= pMatriz->numColunas; colunaAtual++)
    {
        pNoCriado = CriarNo();
        
        if(pNoCriado == NULL)
        {
            return MAT_CondRetFaltouMemoria;
        }
        
        pNoCriado->linhaMatriz = pMatriz->numLinhas + 1;
        pNoCriado->colunaMatriz = colunaAtual;
        
        /* O oeste do n� criado � o n� anterior na linha */
        pNoCriado->pEntradaOeste = pElemAnterior;
        
        /* Se o norte do n� anterior � nulo, n�o h� coordenadas acima do n� criado */
        if(pElemAnterior->pEntradaNorte != NULL)
        {
            /* Atualiza as coordenadas do n� criado e dos n�s adjacentes a ele */
            pElemAnterior->pEntradaNorte->pEntradaLeste->pEntradaSul = pNoCriado;
            pNoCriado->pEntradaNorte = pElemAnterior->pEntradaNorte->pEntradaLeste;
            
            pElemAnterior->pEntradaNorte->pEntradaSudeste = pNoCriado;
            pNoCriado->pEntradaNoroeste = pElemAnterior->pEntradaNorte;
            
            /* Verifica se o n� a nordeste do n� criado existe */
            if(pElemAnterior->pEntradaNorte->pEntradaLeste->pEntradaLeste != NULL)
            {
                /* Atualiza a coordenada do n� criado e do n� a nordeste */
                pElemAnterior->pEntradaNorte->pEntradaLeste->pEntradaLeste->pEntradaSudoeste = pNoCriado;
                pNoCriado->pEntradaNordeste = pElemAnterior->pEntradaNorte->pEntradaLeste->pEntradaLeste;
            }
        }
        
        pElemAnterior->pEntradaLeste = pNoCriado;
        pElemAnterior = pElemAnterior->pEntradaLeste;
    }
    
    pMatriz->numLinhas++;
    
    return MAT_CondRetOK;
    
} /* Fim fun��o: MAT Adicionar Linha */

/***************************************************************************
 *
 *  Fun��o: MAT Adicionar Coluna
 *
 ****/
MAT_tpCondRet MAT_AdicionarColuna(MAT_tpMatriz * pMatriz)
{
    int linhaAtual;
    tpNoMatriz * pElemInicioColuna, * pElemAnterior, * pNoCriado;
    
    if(pMatriz == NULL)
    {
        return MAT_CondRetMatrizNaoExiste;
    }
    
    /* Move o pElemCorr at� a primeira linha da �ltima coluna */
    AvancaPrimeiraLinha(pMatriz);
    AvancaUltimaColuna(pMatriz);
    
    pElemInicioColuna = CriarNo();
    
    if(pElemInicioColuna == NULL)
    {
        return MAT_CondRetFaltouMemoria;
    }
    
    pElemInicioColuna->linhaMatriz = 1;
    pElemInicioColuna->colunaMatriz = pMatriz->numColunas + 1;
    
    if(pMatriz->pElemCorr != NULL)
    {
        pElemInicioColuna->pEntradaOeste = pMatriz->pElemCorr;
        pMatriz->pElemCorr->pEntradaLeste = pElemInicioColuna;
    }
    
    else
    {
        pMatriz->pElemCorr = pElemInicioColuna;
    }
    
    if(pElemInicioColuna->pEntradaOeste != NULL && pElemInicioColuna->pEntradaOeste->pEntradaSul != NULL)
    {
        pElemInicioColuna->pEntradaOeste->pEntradaSul->pEntradaNordeste = pElemInicioColuna;
        pElemInicioColuna->pEntradaSudoeste = pElemInicioColuna->pEntradaOeste->pEntradaSul;
    }
    
    pElemAnterior = pElemInicioColuna;
    
    for(linhaAtual = 2; linhaAtual <= pMatriz->numLinhas; linhaAtual++)
    {
        pNoCriado = CriarNo();
        
        if(pNoCriado == NULL)
        {
            return MAT_CondRetFaltouMemoria;
        }
        
        pNoCriado->colunaMatriz = pMatriz->numColunas + 1;
        pNoCriado->linhaMatriz = linhaAtual;
        
        /* O norte do n� criado � o n� anterior na coluna */
        pNoCriado->pEntradaNorte = pElemAnterior;
        
        /* Se o oeste do n� anterior � nulo, n�o h� coordenadas ao lado do n� criado */
        if(pElemAnterior->pEntradaOeste != NULL)
        {
            /* Atualiza as coordenadas do n� criado e dos n�s adjacentes a ele */
            pElemAnterior->pEntradaOeste->pEntradaSul->pEntradaLeste = pNoCriado;
            pNoCriado->pEntradaOeste = pElemAnterior->pEntradaOeste->pEntradaSul;
            
            pElemAnterior->pEntradaOeste->pEntradaSudeste = pNoCriado;
            pNoCriado->pEntradaNoroeste = pElemAnterior->pEntradaOeste;
            
            /* Verifica se o n� a sudoeste do n� criado existe */
            if(pElemAnterior->pEntradaOeste->pEntradaSul->pEntradaSul != NULL)
            {
                /* Atualiza a coordenada do n� criado e do n� a sudoeste */
                pElemAnterior->pEntradaOeste->pEntradaSul->pEntradaSul->pEntradaNordeste = pNoCriado;
                pNoCriado->pEntradaSudoeste = pElemAnterior->pEntradaOeste->pEntradaSul->pEntradaSul;
            }
        }
        
        pElemAnterior->pEntradaSul = pNoCriado;
        pElemAnterior = pElemAnterior->pEntradaSul;
    }
    
    pMatriz->numColunas++;
    
    return MAT_CondRetOK;
} /* Fim fun��o: MAT Adicionar Coluna */

/***************************************************************************
 *
 *  Fun��o: MAT Remover Linha
 *
 ****/

MAT_tpCondRet MAT_RemoverLinha(MAT_tpMatriz *pMatriz)
{
    if (pMatriz == NULL)
    {
        return MAT_CondRetMatrizNaoExiste;
    }
    
    if (pMatriz->pElemCorr == NULL)
    {
        return MAT_CondRetMatrizVazia;
    }
    
    /* Move o pElemCorr at� a �ltima coluna da �ltima linha */
    AvancaUltimaColuna(pMatriz);
    AvancaUltimaLinha(pMatriz);
    
    /* Sobreescrevendo a matriz */
    
    while (pMatriz->pElemCorr->pEntradaOeste != NULL)
    {
        if (pMatriz->pElemCorr->pEntradaNorte != NULL)
        {
            pMatriz->pElemCorr->pEntradaNorte->pEntradaSul      = NULL;
            pMatriz->pElemCorr->pEntradaNorte->pEntradaSudoeste = NULL;
            pMatriz->pElemCorr->pEntradaNorte->pEntradaSudeste  = NULL;
        }
        
        pMatriz->pElemCorr = pMatriz->pElemCorr->pEntradaOeste;
        ExcluirNoMatriz(pMatriz->pElemCorr->pEntradaLeste);
    }
    
    if (pMatriz->pElemCorr->pEntradaNorte != NULL)
    {
        pMatriz->pElemCorr->pEntradaNorte->pEntradaSudoeste = NULL;
        pMatriz->pElemCorr->pEntradaNorte->pEntradaSudeste  = NULL;
        pMatriz->pElemCorr = pMatriz->pElemCorr->pEntradaNorte;
        ExcluirNoMatriz(pMatriz->pElemCorr->pEntradaSul);
        pMatriz->pElemCorr->pEntradaSul = NULL;
    }
    
    else
    {
        ExcluirNoMatriz(pMatriz->pElemCorr);
        pMatriz->pElemCorr = NULL;
    }
    
    pMatriz->numLinhas--;
    
    if(pMatriz->numLinhas == 0)
    {
        pMatriz->numColunas = 0;
    }
    
    /* Levando n� corrente para a origem da matriz */

    AvancaPrimeiraColuna(pMatriz);
    AvancaPrimeiraLinha(pMatriz);
    
    pMatriz->pElemOrigem = pMatriz->pElemCorr;
    
    return MAT_CondRetOK;
    
} /* Fim fun��o: MAT Remover Linha */

/***************************************************************************
 *
 *  Fun��o: MAT Remover Coluna
 *
 ****/

MAT_tpCondRet MAT_RemoverColuna(MAT_tpMatriz *pMatriz)
{
    if(pMatriz == NULL)
    {
        return MAT_CondRetMatrizNaoExiste;
    }
    
    if(pMatriz->pElemCorr == NULL)
    {
        return MAT_CondRetMatrizVazia;
    }
    
    /* Move o pElemCorr at� a �ltima coluna da �ltima linha */
    AvancaUltimaColuna(pMatriz);
    AvancaUltimaLinha(pMatriz);
    
    /* Sobreescrevendo a matriz */
    
    while(pMatriz->pElemCorr->pEntradaNorte != NULL)
    {
        if(pMatriz->pElemCorr->pEntradaOeste != NULL)
        {
            pMatriz->pElemCorr->pEntradaOeste->pEntradaLeste    = NULL;
            pMatriz->pElemCorr->pEntradaOeste->pEntradaNordeste = NULL;
            pMatriz->pElemCorr->pEntradaOeste->pEntradaSudeste  = NULL;
        }
        
        pMatriz->pElemCorr=pMatriz->pElemCorr->pEntradaNorte;
        ExcluirNoMatriz(pMatriz->pElemCorr->pEntradaSul);
    }
    
    if(pMatriz->pElemCorr->pEntradaOeste != NULL)
    {
        pMatriz->pElemCorr->pEntradaOeste->pEntradaNordeste = NULL;
        pMatriz->pElemCorr->pEntradaOeste->pEntradaSudeste  = NULL;
        pMatriz->pElemCorr = pMatriz->pElemCorr->pEntradaOeste;
        ExcluirNoMatriz(pMatriz->pElemCorr->pEntradaLeste);
        pMatriz->pElemCorr->pEntradaLeste = NULL;
    }
    
    else
    {
        ExcluirNoMatriz(pMatriz->pElemCorr);
        pMatriz->pElemCorr = NULL;
    }
    
    pMatriz->numColunas--;
    
    if(pMatriz->numColunas == 0)
    {
        pMatriz->numLinhas = 0;
    }
    
    /* Levando n� corrente para a origem da matriz */
    
    AvancaPrimeiraColuna(pMatriz);
    AvancaPrimeiraLinha(pMatriz);
    
    pMatriz->pElemOrigem = pMatriz->pElemCorr;
    
    return MAT_CondRetOK;
    
} /* Fim fun��o: MAT Remover Coluna */

/***************************************************************************
 *
 *  Fun��o: MAT Ir para coordenada espec�fica
 *
 ****/

MAT_tpCondRet MAT_IrParaCoordenada(MAT_tpMatriz * pMatriz, int linha, int coluna)
{
	int i, j;
    
    if (pMatriz == NULL)
    {
        return MAT_CondRetMatrizNaoExiste;
    }
    
    if (pMatriz->pElemCorr == NULL)
    {
        return MAT_CondRetMatrizVazia;
    }
    
    if ((linha < 0 || linha >= pMatriz->numLinhas) || (coluna < 0 || coluna >= pMatriz->numColunas))
    {
        return MAT_CondRetCoordenadaInexistente;
    }
    
    AvancaPrimeiraLinha(pMatriz);
    AvancaPrimeiraColuna(pMatriz);
    
    for (i = 0; i < linha; i++)
    {
        MAT_IrPara(pMatriz, MAT_CoordSul);
    }
    
    for (j = 0; j < coluna; j++)
    {
        MAT_IrPara(pMatriz, MAT_CoordLeste);
    }
    
    return MAT_CondRetOK;
    
} /* Fim fun��o: MAT Ir para coordenada espec�fica */

/***************************************************************************
 *
 *  Fun��o: MAT Ir para coordenada
 *
 ****/

MAT_tpCondRet MAT_IrPara(MAT_tpMatriz * pMatriz, MAT_tpCoord Coordenada)
{
    if(pMatriz == NULL)
    {
        return MAT_CondRetMatrizNaoExiste;
    }
    
    if(pMatriz->pElemCorr == NULL)
    {
        return MAT_CondRetMatrizVazia;
    }
    
    switch(Coordenada)
    {
        case MAT_CoordNorte:
            
            if(pMatriz->pElemCorr->pEntradaNorte == NULL)
            {
                return MAT_CondRetCoordenadaInexistente;
            }
            
            pMatriz->pElemCorr = pMatriz->pElemCorr->pEntradaNorte;
            break;
            
        case MAT_CoordNordeste:
            
            if(pMatriz->pElemCorr->pEntradaNordeste == NULL)
            {
                return MAT_CondRetCoordenadaInexistente;
            }
            
            pMatriz->pElemCorr = pMatriz->pElemCorr->pEntradaNordeste;
            break;
            
        case MAT_CoordLeste:
            
            if(pMatriz->pElemCorr->pEntradaLeste == NULL)
            {
                return MAT_CondRetCoordenadaInexistente;
            }
            
            pMatriz->pElemCorr = pMatriz->pElemCorr->pEntradaLeste;
            break;
            
        case MAT_CoordSudeste:
            
            if(pMatriz->pElemCorr->pEntradaSudeste == NULL)
            {
                return MAT_CondRetCoordenadaInexistente;
            }
            
            pMatriz->pElemCorr = pMatriz->pElemCorr->pEntradaSudeste;
            break;
            
        case MAT_CoordSul:
            
            if(pMatriz->pElemCorr->pEntradaSul == NULL)
            {
                return MAT_CondRetCoordenadaInexistente;
            }
            
            pMatriz->pElemCorr = pMatriz->pElemCorr->pEntradaSul;
            break;
            
        case MAT_CoordSudoeste:
            
            if(pMatriz->pElemCorr->pEntradaSudoeste == NULL)
            {
                return MAT_CondRetCoordenadaInexistente;
            }
            
            pMatriz->pElemCorr = pMatriz->pElemCorr->pEntradaSudoeste;
            break;
            
        case MAT_CoordOeste:
            
            if(pMatriz->pElemCorr->pEntradaOeste == NULL)
            {
                return MAT_CondRetCoordenadaInexistente;
            }
            
            pMatriz->pElemCorr = pMatriz->pElemCorr->pEntradaOeste;
            break;
            
        case MAT_CoordNoroeste:
            
            if(pMatriz->pElemCorr->pEntradaNoroeste == NULL)
            {
                return MAT_CondRetCoordenadaInexistente;
            }
            
            pMatriz->pElemCorr = pMatriz->pElemCorr->pEntradaNoroeste;
            break;
            
        default:
            return MAT_CondRetCoordenadaInexistente;
    }
    
    return MAT_CondRetOK;
} /* Fim fun��o: MAT Ir para coordenada */

/***************************************************************************
 *
 *  Fun��o: MAT Obter valor corrente
 *
 ****/

MAT_tpCondRet MAT_ObterValorCorr(MAT_tpMatriz *pMatriz, PIL_tppPilha* pPilha)
{
    if(pMatriz == NULL)
    {
        return MAT_CondRetMatrizNaoExiste;
    }
    
    if(pMatriz->pElemCorr == NULL)
    {
        return MAT_CondRetMatrizVazia;
    }
    
    *pPilha = pMatriz->pElemCorr->pCabecaPilha;
    
    return MAT_CondRetOK;
} /* Fim fun��o: MAT Obter valor corrente */

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
 *
 *  $FC Fun��o: Criar n� da matriz
 *
 *  $ED Descri��o da fun��o
 *     Cria um n� vazio.
 *
 *  $FV Valor retornado
 *     Ponteiro para o n� criado.
 *     Ser� NULL caso a mem�ria tenha se esgotado.
 *     Os ponteiros dos n�s vizinhos e o valor do n� criado estar�o nulos.
 *
 ***********************************************************************/

tpNoMatriz * CriarNo(void)
{
    tpNoMatriz * pNo;
    
    pNo = (tpNoMatriz *) malloc(sizeof(tpNoMatriz));
    
    if(pNo == NULL)
    {
        return NULL;
    }
    
    pNo->pEntradaNorte    = NULL;
    pNo->pEntradaNordeste = NULL;
    pNo->pEntradaLeste    = NULL;
    pNo->pEntradaSudeste  = NULL;
    pNo->pEntradaSul      = NULL;
    pNo->pEntradaSudoeste = NULL;
    pNo->pEntradaOeste    = NULL;
    pNo->pEntradaNoroeste = NULL;
    pNo->pCabecaPilha     = NULL;
    
    return pNo;
} /* Fim fun��o: Criar n� da matriz */

/***********************************************************************
 *
 *  $FC Fun��o: Excluir n� da matriz
 *
 *  $ED Descri��o da fun��o
 *     Exclui o n� corrente da matriz.
 *
 *  $EP Par�metros
 *     pNoMatriz - ponteiro para a n� da matriz a ser exclu�do
 *
 ***********************************************************************/
void ExcluirNoMatriz(tpNoMatriz *pNoMatriz)
{
    PIL_tpCondRet retornoPilha;
    
    if(pNoMatriz->pCabecaPilha != NULL)
    {
        retornoPilha = PIL_DestruirPilha(&(pNoMatriz->pCabecaPilha));
    }
    
    free(pNoMatriz);
} /* Fim fun��o: Excluir n� da matriz */

/***********************************************************************
 *
 *  $FC Fun��o: Avan�a para a primeira linha da matriz
 *
 *  $ED Descri��o da fun��o
 *     Move o n� corrente da matriz para a primeira linha.
 *
 *  $EP Par�metros
 *     pMatriz - ponteiro para a matriz a ser utilizada
 *
 ***********************************************************************/

void AvancaPrimeiraLinha(MAT_tpMatriz *pMatriz)
{
    if(pMatriz->pElemCorr == NULL)
    {
        return;
    }
    
    while(pMatriz->pElemCorr->pEntradaNorte != NULL)
    {
        pMatriz->pElemCorr = pMatriz->pElemCorr->pEntradaNorte;
    }
} /* Fim fun��o: Avan�ar para a primeira linha */

/***********************************************************************
 *
 *  $FC Fun��o: Avan�a para a primeira coluna da matriz
 *
 *  $ED Descri��o da fun��o
 *     Move o n� corrente da matriz para a coluna linha.
 *
 *  $EP Par�metros
 *     pMatriz - ponteiro para a matriz a ser utilizada
 *
 ***********************************************************************/

void AvancaPrimeiraColuna(MAT_tpMatriz *pMatriz)
{
    if(pMatriz->pElemCorr == NULL)
    {
        return;
    }
    
    while(pMatriz->pElemCorr->pEntradaOeste != NULL)
    {
        pMatriz->pElemCorr = pMatriz->pElemCorr->pEntradaOeste;
    }
} /* Fim fun��o: Avan�ar para a primeira coluna */

/***********************************************************************
 *
 *  $FC Fun��o: Avan�a para a �ltima linha da matriz
 *
 *  $ED Descri��o da fun��o
 *     Move o n� corrente da matriz para a �ltima linha.
 *
 *  $EP Par�metros
 *     pMatriz - ponteiro para a matriz a ser utilizada
 *
 ***********************************************************************/

void AvancaUltimaLinha(MAT_tpMatriz *pMatriz)
{
    if(pMatriz->pElemCorr == NULL)
    {
        return;
    }
    
    while(pMatriz->pElemCorr->pEntradaSul != NULL)
    { 
        pMatriz->pElemCorr = pMatriz->pElemCorr->pEntradaSul;
    }
} /* Fim fun��o: Avan�ar para a �ltima linha */

/***********************************************************************
 *
 *  $FC Fun��o: Avan�a para a �ltima coluna da matriz
 *
 *  $ED Descri��o da fun��o
 *     Move o n� corrente da matriz para a �ltima coluna.
 *
 *  $EP Par�metros
 *     pMatriz - ponteiro para a matriz a ser utilizada
 *
 ***********************************************************************/

void AvancaUltimaColuna(MAT_tpMatriz *pMatriz)
{
    if(pMatriz->pElemCorr == NULL)
    {
        return;
    }
    
    while(pMatriz->pElemCorr->pEntradaLeste != NULL)
    {
        pMatriz->pElemCorr = pMatriz->pElemCorr->pEntradaLeste;
    }
} /* Fim fun��o: Avan�ar para a �ltima coluna */

/********** Fim do m�dulo de implementa��o: M�dulo matriz **********/