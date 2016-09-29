/***************************************************************************
 *  $MCI Módulo de implementação: TestePILHA
 *
 *  Arquivo gerado:              TestePIL.C
 *  Letras identificadoras:      TSTPIL
 *
 *  Projeto: Disciplina INF 1301
 *
 *  Autores: gsg - Gabriel da Silva Gomes
 *			 gsb - Gustavo Severo Barros
 *	         jpmldg - João Pedro Masset Lacombe D Garcia
 *
 *  $HA Histórico de evolução:
 *     Versão       Autor          Data            Observações
 *      1.00         jpmldg        20/04/2016   Início do desenvolvimento
 *
 ***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Lista.h"
#include	"Pilha.h"


static const char RESET_PILHA_CMD         [ ] = "=resetteste"     ;
static const char CRIAR_PILHA_CMD         [ ] = "=criarpilha"     ;
static const char DESTRUIR_PILHA_CMD      [ ] = "=destruirpilha"  ;
static const char EMPILHA_VALOR_CMD       [ ] = "=empilvalor"     ;
static const char DESEMPILHA_VALOR_CMD    [ ] = "=desempilvalor"  ;
static const char OBTER_VALOR_TOPO_CMD    [ ] = "=obtervalortopo" ;
static const char OBTER_TAMANHO_CMD       [ ] = "=obtertamanho"   ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VALOR     100

PIL_tppPilha vtPilhas[DIM_VT_LISTA] ;

/*****  CÛdigo das funÁıes exportadas pelo mÛdulo  *****/

/***********************************************************************
*
*  $FC FunÁ„o: TLIS &Testar pilha
*
*  $ED DescriÁ„o da funÁ„o
*     Podem ser criadas atÈ 10 pilhas, identificadas pelos Ìndices 0 a 10
*
*     Comandos disponÌveis:
*
*     =resetteste
*           - anula o vetor de pilhas. Provoca vazamento de memÛria
*     =criarpilha                   inxPilha
*     =destruirpilha                inxPilha  CondRetEsp
*     =empilvalor                   inxPilha  char  CondRetEsp
*     =desempilvalor                inxPilha  CondRetEsp
*     =obtervalortopo               inxPilha  char  CondRetEsp
*     =obtertamanho                 inxPilha  int   CondretEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxPilha  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      PIL_tpCondRet CondRet ;

      char   CharDado ;
      char   pDado[1] ;

      int ValEsp = -1 ;

	  int tamPilha = -1;
	  int tamPilhaEsp = -1;

      int i ;

      int numElem = -1 ;

      CharDado = '0' ;

		/*
		*	Inicio das funcoes referentes a pilha
		*
		*
		*/


         if ( strcmp( ComandoTeste , RESET_PILHA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_LISTA ; i++ )
            {
               vtPilhas[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar CriarPilha */

         else if ( strcmp( ComandoTeste , CRIAR_PILHA_CMD ) == 0 )
		 {
            numLidos = LER_LerParametros( "i" , &inxPilha ) ;

            if ( ( numLidos != 1 ) || ( ! ValidarInxPilha( inxPilha , VAZIO )))
			{
               return TST_CondRetParm ;
            }

			vtPilhas[ inxPilha ] = PIL_CriarPilha() ;
            return TST_CompararPonteiroNulo( 1 , vtPilhas[ inxPilha ] , "Erro em ponteiro de nova lista."  ) ;

         } /* fim ativa: Testar CriarPilha */

      /* Testar Destuir Pilha */

         else if ( strcmp( ComandoTeste , DESTRUIR_PILHA_CMD ) == 0 )
         { 
			numLidos = LER_LerParametros( "ii" , &inxPilha, &CondRetEsp ) ;

            if ( ( numLidos != 2 ) )
            {
			   return TST_CondRetParm ;
            }
            CondRet = PIL_DestruirPilha( vtPilhas[ inxPilha ] ) ;
            vtPilhas[ inxPilha ] = NULL ;

			if(CondRet == 0){
				return TST_CondRetOK ;
			}
			return TST_CompararInt( CondRetEsp , CondRet , "Condicao de retorno errada ao inserir antes.") ;

         } /* fim ativa: Testar Destruir Pilha */

      /* Testar Empilhar Valor */

         else if ( strcmp( ComandoTeste , EMPILHA_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ici" , &inxPilha , &CharDado , &CondRetEsp ) ; //Le VALOR
            if ( ( numLidos != 3 ) ) // se nao leu direito
            {
               return TST_CondRetParm ;
            }
			CondRet = PIL_EmpilhaValor(vtPilhas[ inxPilha ], CharDado);	// CHAMA A FUNCAO insere elemento

            return TST_CompararInt( CondRetEsp , CondRet , "Condicao de retorno errada ao inserir antes.") ; //verifica retorno

         } /* fim ativa: Empilhar Valor */

      /* Testar Desempilhar Valor */

         else if ( strcmp( ComandoTeste , DESEMPILHA_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxPilha , &CondRetEsp ) ; //Le VALOR

            if ( ( numLidos != 2 ) ) // se nao leu direito
            {
               return TST_CondRetParm ;
            }

            CondRet = PIL_DesempilhaValor( vtPilhas[ inxPilha ] ) ;	// CHAMA A FUNCAO remove elemento

            return TST_CompararInt( CondRetEsp , CondRet , "Condicao de retorno errada ao inserir antes.") ;//verifica retorno

         } /* fim ativa: Testar Desempilhar Valor */

      /* Testar obter valor topo */

         else if ( strcmp( ComandoTeste , OBTER_VALOR_TOPO_CMD ) == 0 )
         {
			char dado;
			numLidos = LER_LerParametros( "ici" , &inxPilha , &CharDado , &CondRetEsp ) ;
            if ( ( numLidos != 3 ) )
            {
               return TST_CondRetParm ;
            } 

			if ( pDado == NULL )
            {
               return TST_CompararPonteiroNulo( 1 , pDado , "Dado tipo um deveria existir." ) ;
            } 

            CondRet = PIL_ObterValorTopo(vtPilhas[inxPilha], pDado) ;

			dado = *pDado;

			if(CondRet == 0){
				return TST_CompararChar( CharDado, dado, "Valor do elemento errado.") ;
			}

			return TST_CompararInt( CondRetEsp, CondRet, "Condicao de retorno errada ao inserir antes.") ;
			
         } 
		 /* fim ativa: Testar Obter valor topo */

      /* Testar Obter Tamanho */

         else if ( strcmp( ComandoTeste , OBTER_TAMANHO_CMD ) == 0 )
         {
			char * DadoRetornado;
            numLidos = LER_LerParametros( "iii" , &inxPilha , &tamPilhaEsp , &CondRetEsp ) ;

            if ( ( numLidos != 3 ) )
            {
               return TST_CondRetParm ;
            } 

			CondRet = PIL_ObterTamanho(vtPilhas[inxPilha], &tamPilha) ;

			if(CondRet == 0){
				return TST_CompararInt( tamPilhaEsp, tamPilha, "Valor do elemento errado.") ;
			}

			return TST_CompararInt( CondRetEsp, CondRet, "Condicao de retorno errada ao inserir antes.") ;

         } /* fim ativa: Testar Obter Tamanho */
}


/*****  CÛdigo das funÁıes encapsuladas no mÛdulo  *****/


/***********************************************************************
*
*  $FC FunÁ„o: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( char * pValor )
   {

      free( pValor ) ;

   } /* Fim funÁ„o: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC FunÁ„o: TLIS -Validar indice de lista
*
***********************************************************************/

   int ValidarInxPilha( int inxPilha , int Modo )
   {

      if ( ( inxPilha <  0 ) || ( inxPilha >= DIM_VT_LISTA )) { //Caso Nao esteja em um intervalo valido
         return FALSE ;
      }
         
      if ( Modo == VAZIO ) {				// Caso modo vazio
         if ( vtPilhas[ inxPilha ] != NULL ) { // Se for diferente de NULL
            return FALSE ;
         } 
      } else {								//Caso modo NAO_VAZIO
         if ( vtPilhas[ inxPilha ] == NULL ){  //Se for Igual a NULL
            return FALSE ;
         } 
      }
      return TRUE ;

   } /* Fim funÁ„o: TLIS -Validar indice de lista */

/********** Fim do mÛdulo de implementaÁ„o: TLIS Teste lista de sÌmbolos **********/

