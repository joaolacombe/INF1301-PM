/***************************************************************************
*  $MCI M�dulo de implementa��o: M�dulo de teste espec�fico
*
*  Arquivo gerado:              TESTARV.C
*  Letras identificadoras:      TARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: INF 1301 - Programa��o Modular
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*			gg - Gabriel Gomes
*			gs - Gustavo Severo
*			jg - Joao Garcia
*
*  $HA Hist�rico de evolu��o:
*     Vers�o	Autor		Data      Observa��es
*	   4.00   gg,gs,jg   28/mar/2016 Altera��o do conte�do do n� da �rvore de char
*									 para ponteiro de lista e adapta��o das fun��es 
*									 para a respectiva altera��o. Altera��o das 
*									 fun��es dado a possibilidade de recebimento
*									 de diferentes �rvores por par�metro.
*      3.00      avs     08/dez/2004 uniformiza��o dos exemplos
*      2.00      avs     07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*      1.00      avs     16/abr/2003 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Este m�dulo cont�m as fun��es espec�ficas para o teste do
*     m�dulo �rvore. Ilustra como redigir um interpretador de comandos
*     de teste espec�ficos utilizando o arcabou�o de teste para C.
*
*  $EIU Interface com o usu�rio pessoa
*     Comandos de teste espec�ficos para testar o m�dulo �rvore:
*
*     =criar  <int> <CondRetEsp>
*					- chama a fun��o ARV_CriarArvore(<arvore[<int>]> ) criando na determinada posicao do vetor de arvores
*     =insdir <int> <int> <CondRetEsp>- 
*                   - chama a fun��o ARV_InserirDireita(<arvore[<int>]> <lista[<int>]> )
*                     Obs. nota��o: acessa a posicao da lista no vetor de listas e
*                     passa essa lista para que seja inserida na arvore.
*
*     "=insesq" <int> <int> <CondRetEsp>
*                   - chama a fun��o ARV_InserirEsquerda( <arvore[<int>]> <lista[<int>]> )
*					- funciona como a insdir explicada acima
*     "=irpai"  <int>  <CondRetEsp>  - chama a fun��o ARV_IrPai( <arvore[<int>]> )
*								acessa o elemento pai do atual
*     "=iresq"  <int>  <CondRetEsp>  - chama a fun��o ARV_IrEsquerda( <arvore[<int>]> )
*								acessa o filho a esquerda do no atual
*     "=irdir"  <int>  <CondRetEsp>  - chama a fun��o ARV_IrDireita( <arvore[<int>]> )
*								acessa o filho a direita do no atual
*     "=obter" <int> <int> <CondRetEsp>
*                   - chama a fun��o ARV_ObterValorCorr( <arvore[<int>]> ) e compara
*                     o valor retornado com o valor <Lista[<int>]>
*     "=destroi" <int>   - chama a fun��o ARV_DestruirArvore( <arvore[<int>]> )
*
*     Comandos dispon�veis para lista:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de mem�ria
*     =criarlista                   inxLista
*     =destruirlista                inxLista
*     =esvaziarlista                inxLista
*     =inselemantes                 inxLista  char  CondRetEsp
*     =inselemapos                  inxLista  char  CondRetEsp
*     =obtervalorelem               inxLista  char  CondretPonteiro
*     =excluirelem                  inxLista  CondRetEsp
*     =irinicio                     inxLista
*     =irfinal                      inxLista
*     =avancarelem                  inxLista  numElem CondRetEsp

***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_ESPC.H"

#include    "generico.h"
#include    "lerparm.h"

#include    "arvore.h"
#include    "Lista.h"

/* Tabela dos nomes dos comandos de teste espec�ficos */

/*Relativos a arvore */
#define     CRIAR_ARV_CMD       "=criar"
#define     INS_DIR_CMD         "=insdir"
#define     INS_ESQ_CMD         "=insesq"
#define     IR_PAI_CMD          "=irpai"
#define     IR_ESQ_CMD          "=iresq"
#define     IR_DIR_CMD          "=irdir"
#define     OBTER_VAL_CMD       "=obter"
#define     DESTROI_CMD         "=destruir"

#define DIM_VT_ARVORE 10
ptArvore vtArvore[ DIM_VT_ARVORE ] ;

/*Relativos a lista*/
static const char RESET_LISTA_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_LISTA_CMD         [ ] = "=criarlista"     ;
static const char DESTRUIR_LISTA_CMD      [ ] = "=destruirlista"  ;
static const char ESVAZIAR_LISTA_CMD      [ ] = "=esvaziarlista"  ;
static const char INS_ELEM_ANTES_CMD      [ ] = "=inselemantes"   ;
static const char INS_ELEM_APOS_CMD       [ ] = "=inselemapos"    ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorelem" ;
static const char EXC_ELEM_CMD            [ ] = "=excluirelem"    ;
static const char IR_INICIO_CMD           [ ] = "=irinicio"       ;
static const char IR_FIM_CMD              [ ] = "=irfinal"        ;
static const char AVANCAR_ELEM_CMD        [ ] = "=avancarelem"    ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VALOR     100

LIS_tppLista   vtListas[ DIM_VT_LISTA ] ;

/***** Prot�tipos das fun��es encapuladas no m�dulo relativas a lista*****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxLista( int inxLista , int Modo ) ;


/*****  C�digo das fun��es exportadas pelo m�dulo*****/


/***********************************************************************
*
*  $FC Fun��o: TARV Efetuar opera��es de teste espec�ficas para �rvore
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     �rvore sendo testado.
*
*  $EP Par�metros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {
	  /* Declaracao de variaveis utilizadas pelo modulo arvore */
      ARV_tpCondRet CondRetObtido   = ARV_CondRetOK ;
      ARV_tpCondRet CondRetEsperada = ARV_CondRetFaltouMemoria ;
                                      /* inicializa para qualquer coisa */

      int ValorEsperado = -1 ;
      int ValorObtido = -1 ;
      char ValorDado     = '\0'  ;

	  int  ValorLido = -1 ; 

	  int  inxArvore = -1 ;
      int  NumLidos = -1 ;

      TST_tpCondRet Ret ;

	  /* declaracao de variaveis utilizadas pelo modulo lista */
	  int inxLista  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      LIS_tpCondRet CondRet ;

      char   CharDado;
      char * pDado ;

      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;

      CharDado = 0 ;

      /* Testar ARV Criar �rvore */

         if ( strcmp( ComandoTeste , CRIAR_ARV_CMD ) == 0 )
         {
            NumLidos = LER_LerParametros( "ii" ,
                               &inxArvore, &CondRetEsperada ) ;

            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_CriarArvore( &vtArvore[inxArvore] ) ;
            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao criar �rvore." );

         } /* fim ativa: Testar ARV Criar �rvore */

      /* Testar ARV Adicionar filho � direita */

         else if ( strcmp( ComandoTeste , INS_DIR_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "iii" ,
                              &inxArvore, &ValorLido , &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */
			
            CondRetObtido = ARV_InserirDireita( &vtArvore[inxArvore], &vtListas[ValorLido]) ;
			
            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado inserir �a direita." );

         } /* fim ativa: Testar ARV Adicionar filho � direita */

      /* Testar ARV Adicionar filho � esquerda */

         else if ( strcmp( ComandoTeste , INS_ESQ_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "iii" ,
                               &inxArvore, &ValorLido , &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */
			
            CondRetObtido = ARV_InserirEsquerda( &vtArvore[inxArvore], &vtListas[ValorLido] ) ;
            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir � esquerda." );

         } /* fim ativa: Testar ARV Adicionar filho � esquerda */

      /* Testar ARV Ir para n� pai */

         else if ( strcmp( ComandoTeste , IR_PAI_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                              &inxArvore, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrPai( &vtArvore[inxArvore] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para pai." );

         } /* fim ativa: Testar ARV Ir para n� pai */

      /* Testar ARV Ir para n� � esquerda */

         else if ( strcmp( ComandoTeste , IR_ESQ_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "ii" ,
                               &inxArvore, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_IrNoEsquerda(&vtArvore[inxArvore]) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para esquerda." );

         } /* fim ativa: Testar ARV Ir para n� � esquerda */

      /* Testar ARV Ir para n� � direita */

         else if ( strcmp( ComandoTeste , IR_DIR_CMD ) == 0 )
         {
			
            NumLidos = LER_LerParametros( "ii" ,
                              &inxArvore, &CondRetEsperada ) ;
            if ( NumLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */
	
            CondRetObtido = ARV_IrNoDireita( &vtArvore[inxArvore] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao ir para direita." );

         } /* fim ativa: Testar ARV Ir para n� � direita */

      /* Testar ARV Obter valor corrente */

         else if ( strcmp( ComandoTeste , OBTER_VAL_CMD ) == 0 )
         {

            NumLidos = LER_LerParametros( "iii" ,
                               &inxArvore, &ValorEsperado , &CondRetEsperada ) ;
            if ( NumLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = ARV_ObterValorCorr( &vtArvore[inxArvore], &ValorObtido ) ;

            Ret = TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                   "Retorno errado ao obter valor corrente." );

            if ( Ret != TST_CondRetOK )
            {
               return Ret ;
            } /* if */

            return TST_CompararInt( (int)&vtListas[ValorEsperado] , ValorObtido ,
                                     "Conte�do do n� est� errado." ) ;

         } /* fim ativa: Testar ARV Obter valor corrente */

      /* Testar ARV Destruir �rvore */

         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {
			NumLidos = LER_LerParametros( "i" ,
                               &inxArvore ) ;
			if ( NumLidos != 1 )
            {
               return TST_CondRetParm ;
            } /* if */

            ARV_DestruirArvore( &vtArvore[inxArvore] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar ARV Destruir �rvore */

		 /* Efetuar reset de teste de lista */


		 /*
		 *	Inicio das funcoes referentes a lista
		 *
		 *
		 */


         if ( strcmp( ComandoTeste , RESET_LISTA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_LISTA ; i++ )
            {
               vtListas[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar CriarLista */

         else if ( strcmp( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                       &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtListas[ inxLista ] =
                 LIS_CriarLista( DestruirValor ) ;

            return TST_CompararPonteiroNulo( 1 , vtListas[ inxLista ] ,
               "Erro em ponteiro de nova lista."  ) ;

         } /* fim ativa: Testar CriarLista */

      /* Testar Esvaziar lista lista */

         else if ( strcmp( ComandoTeste , ESVAZIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_EsvaziarLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Esvaziar lista lista */

      /* Testar Destruir lista */

         else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_DestruirLista( vtListas[ inxLista ] ) ;
            vtListas[ inxLista ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir lista */

      /* Testar inserir elemento antes */

         else if ( strcmp( ComandoTeste , INS_ELEM_ANTES_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ici" ,
                       &inxLista , &CharDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) malloc( strlen( &CharDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , &CharDado ) ;


            CondRet = LIS_InserirElementoAntes( vtListas[ inxLista ] , pDado ) ;

            if ( CondRet != LIS_CondRetOK )
            {
               free( pDado ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir antes."                   ) ;

         } /* fim ativa: Testar inserir elemento antes */

      /* Testar inserir elemento apos */

         else if ( strcmp( ComandoTeste , INS_ELEM_APOS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ici" ,
                       &inxLista , &CharDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) malloc( strlen( &CharDado ) + 1 ) ;
            if ( pDado == NULL )
            {
               return TST_CondRetMemoria ;
            } /* if */

            strcpy( pDado , &CharDado ) ;


            CondRet = LIS_InserirElementoApos( vtListas[ inxLista ] , pDado ) ;

            if ( CondRet != LIS_CondRetOK )
            {
               free( pDado ) ;
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir apos."                   ) ;

         } /* fim ativa: Testar inserir elemento apos */

      /* Testar excluir simbolo */

         else if ( strcmp( ComandoTeste , EXC_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                  &inxLista , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_ExcluirElemento( vtListas[ inxLista ] ) ,
                     "Condi��o de retorno errada ao excluir."   ) ;

         } /* fim ativa: Testar excluir simbolo */

      /* Testar obter valor do elemento corrente */

         else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ici" ,
                       &inxLista , &CharDado , &ValEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            pDado = ( char * ) LIS_ObterValor( vtListas[ inxLista ] ) ;

            if ( ValEsp == 0 )
            {
               return TST_CompararPonteiroNulo( 0 , pDado ,
                         "Valor n�o deveria existir." ) ;
            } /* if */

            if ( pDado == NULL )
            {
               return TST_CompararPonteiroNulo( 1 , pDado ,
                         "Dado tipo um deveria existir." ) ;
            } /* if */

            return TST_CompararString( &CharDado , pDado ,
                         "Valor do elemento errado." ) ;

         } /* fim ativa: Testar obter valor do elemento corrente */

      /* Testar ir para o elemento inicial */

         else if ( strcmp( ComandoTeste , IR_INICIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            IrInicioLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar ir para o elemento inicial */

      /* LIS  &Ir para o elemento final */

         else if ( strcmp( ComandoTeste , IR_FIM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            IrFinalLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: LIS  &Ir para o elemento final */

      /* LIS  &Avan�ar elemento */

         else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" , &inxLista , &numElem ,
                                &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_AvancarElementoCorrente( vtListas[ inxLista ] , numElem ) ,
                      "Condicao de retorno errada ao avancar" ) ;

         } /* fim ativa: LIS  &Avan�ar elemento */

      return TST_CondRetNaoConhec ;

   } /* Fim fun��o: TARV Efetuar opera��es de teste espec�ficas para �rvore */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TLIS - Destruir valor
*
***********************************************************************/

   void DestruirValor( char * pValor )
   {

      free( pValor ) ;

   } /* Fim fun��o: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Fun��o: TLIS -Validar indice de lista
*
***********************************************************************/

   int ValidarInxLista( int inxLista , int Modo )
   {

      if ( ( inxLista <  0 )
        || ( inxLista >= DIM_VT_LISTA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtListas[ inxLista ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtListas[ inxLista ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim fun��o: TLIS -Validar indice de lista */

/********** Fim do m�dulo de implementa��o: TLIS Teste lista de s�mbolos **********/



/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/

