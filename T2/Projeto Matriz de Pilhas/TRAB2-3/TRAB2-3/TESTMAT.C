/***************************************************************************
 *  $MCI Módulo de implementação: TesteMatriz
 *
 *  Arquivo gerado:              TesteMat.C
 *  Letras identificadoras:      TSTMAT
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
#include	"Matriz.h"


static const char RESET_MATRIZ_CMD        [ ] = "=resetteste"     ;
static const char RESET_PILHAS_CMD        [ ] = "=resetpilhas"    ;
static const char CRIAR_MATRIZ_CMD        [ ] = "=criarmatriz"    ;
static const char DESTRUIR_MATRIZ_CMD     [ ] = "=destruirmatriz" ;
static const char INSERE_VALOR_CMD        [ ] = "=inserirvalor"   ;
static const char ADD_LINHA_CMD			  [ ] = "=addlinha"       ;
static const char ADD_COLUNA_CMD		  [ ] = "=addcoluna"	  ;
static const char REM_LINHA_CMD			  [ ] = "=remlinha"       ;
static const char REM_COLUNA_CMD		  [ ] = "=remcoluna"	  ;
static const char IR_PARA_CMD		      [ ] = "=irpara"	      ;
static const char OBTER_PILHA_CMD         [ ] = "=obterpilha"     ;
static const char IR_COORD_CMD            [ ] = "=irparacoord"    ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VALOR     100

LIS_tppLista vtListas[ DIM_VT_LISTA ] ;
PIL_tppPilha vtPilhas[ DIM_VT_LISTA ] ;
MAT_tppMatriz pMatriz ;

/*****  CÛdigo das funÁıes exportadas pelo mÛdulo  *****/

/***********************************************************************
*
*  $FC FunÁ„o: TLIS &Testar matriz
*
*  $ED DescriÁ„o da funÁ„o
*     Pode criar uma matriz e manipula-la com as funcoes de entradas
*
*     Comandos disponÌveis:
*
*     =resetteste
*           - anula a matriz. Provoca vazamento de memÛria
*     =resetpilhas
*           - anula o vetor de pilhas. Provoca vazamento de memÛria
*     =criarmatriz                  int		  int	CondRetEsp
*     =destruirmatriz               CondRetEsp
*     =inserirvalor                 inxPilha  CondRetEsp
*     =addlinha						CondRetEsp
*     =addcoluna					CondRetEsp
*     =remlinha						CondRetEsp
*     =remcoluna					CondRetEsp
*     =irapara                      Coord  CondRetEsp
*     =obterpilha                   inxPilha	CondRetEsp
*     =iraparacoord                 X	   Y	CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxPilha  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      MAT_tpCondRet CondRet ;

      char   CharDado ;
      char * pDado ;

      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;

	  int linha = -1;

	  int coluna = -1;

	  MAT_tpCoord Coordenada ;

      CharDado = '0' ;

      /*
		 *	Inicio das funcoes referentes a matriz
		 *
		 *
		 */


         if ( strcmp( ComandoTeste , RESET_MATRIZ_CMD ) == 0 )
         {
            pMatriz = NULL ;
            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de matriz */


		 else if ( strcmp( ComandoTeste , RESET_PILHAS_CMD ) == 0 )
         {
            for(i=0; i < DIM_VT_LISTA; i++){
				vtPilhas[i] = PIL_CriarPilha();
			}
            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de pilhas */

      /* Testar CriarMatriz */

         else if ( strcmp( ComandoTeste , CRIAR_MATRIZ_CMD ) == 0 )
         {
			int linhas, colunas;
            numLidos = LER_LerParametros( "iii" , &linhas, &colunas, &CondRetEsp ) ;

            if ( ( numLidos != 3 ) )
            {
               return TST_CondRetParm ;
            } /* if */

			CondRet = MAT_CriarMatriz(&pMatriz, linhas, colunas);

            return TST_CompararInt( CondRetEsp , CondRet ,"Erro na criaao da nova matriz."  ) ;

         } /* fim ativa: Testar CriarMatriz */

      /* Testar Destruir Matriz */

         else if ( strcmp( ComandoTeste , DESTRUIR_MATRIZ_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &CondRetEsp ) ;

            if ( ( numLidos != 1 ) )
            {
			   return TST_CondRetParm ;
            }
            CondRet = MAT_DestruirMatriz( &pMatriz ) ;
            pMatriz = NULL ;

			if(CondRet == MAT_CondRetOK){
				return TST_CondRetOK ;
			}
			return TST_CompararInt( CondRetEsp , CondRet , "Condicao de retorno errada ao inserir antes.") ;


         } /* fim ativa: DestruirMatriz */

      /* Testar Insere Valor */

         else if ( strcmp( ComandoTeste , INSERE_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxPilha, &CondRetEsp ) ;

            if ( ( numLidos != 2 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = MAT_InserirValor(pMatriz, vtPilhas[inxPilha]);	

            return TST_CompararInt( CondRetEsp , CondRet , "Condicao de retorno errada ao inserir antes.") ; 

         } /* fim ativa: Insere Valor */

      /* Testar Adicionar linha */

         else if ( strcmp( ComandoTeste , ADD_LINHA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &CondRetEsp ) ;

            if ( ( numLidos != 1 ) )
            {
               return TST_CondRetParm ;
            }

			CondRet = MAT_AdicionarLinha(pMatriz);

            return TST_CompararInt( CondRetEsp , CondRet , "Condicao de retorno errada ao inserir antes.") ;

         } /* fim ativa: Testar adicionar linha */

	/* Testar Adicionar coluna */

         else if ( strcmp( ComandoTeste , ADD_COLUNA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &CondRetEsp ) ;

            if ( ( numLidos != 1 ) )
            {
               return TST_CondRetParm ;
            }

			CondRet = MAT_AdicionarColuna(pMatriz);

            return TST_CompararInt( CondRetEsp , CondRet , "Condicao de retorno errada ao inserir antes.") ;

         } /* fim ativa: Testar adicionar coluna */

      /* Testar remover linha */

         else if ( strcmp( ComandoTeste , REM_LINHA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &CondRetEsp ) ;

            if ( ( numLidos != 1 ) )
            {
               return TST_CondRetParm ;
            }

			CondRet = MAT_RemoverLinha(pMatriz);

            return TST_CompararInt( CondRetEsp , CondRet , "Condicao de retorno errada ao inserir antes.") ;

         } /* fim ativa: Testar remover linha */

	/* Testar remover coluna */

         else if ( strcmp( ComandoTeste , REM_COLUNA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &CondRetEsp ) ;

            if ( ( numLidos != 1 ) )
            {
               return TST_CondRetParm ;
            }

			CondRet = MAT_RemoverColuna(pMatriz);

            return TST_CompararInt( CondRetEsp , CondRet , "Condicao de retorno errada ao inserir antes.") ;

         } /* fim ativa: Testar remover coluna */

	/* Testar ir para */

         else if ( strcmp( ComandoTeste , IR_PARA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &Coordenada , &CondRetEsp ) ;

			if ( ( numLidos != 2 ) )
            {
               return TST_CondRetParm ;
            }

			CondRet = MAT_IrPara(pMatriz, Coordenada);
            
            return TST_CompararInt( CondRetEsp , CondRet , "CondiÁ„o de retorno errada ao excluir."   ) ;

         } /* fim ativa: Testar ir para */

      /* Testar obter pilha */

         else if ( strcmp( ComandoTeste , OBTER_PILHA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" , &inxPilha , &CondRetEsp ) ;
			
			if ( ( numLidos != 2 ) )
            {
               return TST_CondRetParm ;
            }

			CondRet = MAT_ObterValorCorr(pMatriz, vtPilhas[inxPilha]);
            
            return TST_CompararInt( CondRetEsp , CondRet , "CondiÁ„o de retorno errada ao excluir."   ) ;

         } /* fim ativa: Testar obter pilha */

	/* Testar ira para coord especifica */

         else if ( strcmp( ComandoTeste , IR_COORD_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" , &linha, &coluna , &CondRetEsp ) ;
			
			if ( ( numLidos != 3 ) )
            {
               return TST_CondRetParm ;
            }

			CondRet = MAT_IrParaCoordenada(pMatriz, linha, coluna);
            
            return TST_CompararInt( CondRetEsp , CondRet , "CondiÁ„o de retorno errada ao excluir."   ) ;

         } /* fim ativa: Testar ir para coord especifica */
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

   } /* Fim funÁ„o: TLIS -Validar indice de lista */

/********** Fim do mÛdulo de implementaÁ„o: TLIS Teste lista de sÌmbolos **********/

