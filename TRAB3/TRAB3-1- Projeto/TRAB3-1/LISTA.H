#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD MÛdulo de definiÁ„o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Nome da base de software:    ArcabouÁo para a automaÁ„o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 AutomatizaÁ„o dos testes de mÛdulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA HistÛrico de evoluÁ„o:
*     Vers„o  Autor    Data     ObservaÁıes
*     4       avs   01/fev/2006 criar linguagem script simbÛlica
*     3       avs   08/dez/2004 uniformizaÁ„o dos exemplos
*     2       avs   07/jul/2003 unificaÁ„o de todos os mÛdulos em um sÛ projeto
*     1       avs   16/abr/2003 inÌcio desenvolvimento
*
*  $ED DescriÁ„o do mÛdulo
*     Implementa listas genÈricas duplamente encadeadas.
*     Podem existir n listas em operaÁ„o simultaneamente.
*     As listas possuem uma cabeÁa encapsulando o seu estado.
*
*     Cada lista È homogÍnea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contÈm.
*
*     Os ponteiros para os dados s„o copiados para elementos da lista.
*        N„o È copiado o valor apontado por estes ponteiros.
*
*     O controle da destruiÁ„o do valor de um elemento a ser excluÌdo
*        È realizado por uma funÁ„o fornecida pelo usu·rio.
*
*     Cada lista referencia uma funÁ„o que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A funÁ„o de liberaÁ„o dos valores contidos nos elementos deve
*        assegurar a liberaÁ„o de todos os espaÁos referÍnciados pelo
*        valor contido em um elemento.
*        Esta funÁ„o È chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso n„o seja necess·rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a funÁ„o de liberaÁ„o poder· ser NULL .
*        Caso o elemento da lista seja a ˙nica ‚ncora do valor referenciado,
*        esta funÁ„o deve promover a destruiÁ„o (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** DeclaraÁıes exportadas pelo mÛdulo *****/

/* Tipo referÍncia para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS CondiÁıes de retorno
*
*
*  $ED DescriÁ„o do tipo
*     CondiÁıes de retorno das funÁıes da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista n„o contÈm elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* N„o encontrou o valor procurado */

         LIS_CondRetFaltouMemoria
               /* Faltou memÛria ao tentar criar um elemento de lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC FunÁ„o: LIS  &Criar lista
*
*  $ED DescriÁ„o da funÁ„o
*     Cria uma lista genÈrica duplamente encadeada.
*     Os possÌveis tipos s„o desconhecidos a priori.
*     A tipagem È implicita.
*     N„o existe identificador de tipo associado ‡ lista.
*
*  $EP Par‚metros
*     ExcluirValor  - ponteiro para a funÁ„o que processa a
*                     exclus„o do valor referenciado pelo elemento
*                     a ser excluÌdo.
*                     Ver descriÁ„o do mÛdulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro ser· utilizado pelas funÁıes que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memÛria ou dados errados,
*     a funÁ„o retornar· NULL.
*     N„o ser· dada mais informaÁ„o quanto ao problema ocorrido.
*   
*   Assertivas de Entrada:
*     - Deve existir um ponteiro para a função que processa a exclusão do 
*       valor referenciado pelo elemento a ser excluído.
*
*   Assertivas de Saída:
*     - Se existe memória disponível, a lista é criada e seu ponteiro 
*       aponta para NULL.
*
***********************************************************************/

   LIS_tppLista LIS_CriarLista(
             void   ( * ExcluirValor ) ( char pDado ) ) ;


/***********************************************************************
*
*  $FC FunÁ„o: LIS  &Destruir lista
*
*  $ED DescriÁ„o da funÁ„o
*     DestrÛi a lista fornecida.
*     O par‚metro ponteiro para a lista n„o È modificado.
*     Se ocorrer algum erro durante a destruiÁ„o, a lista resultar·
*     estruturalmente incorreta.
*     OBS. n„o existe previs„o para possÌveis falhas de execuÁ„o.
*
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
*   Assertivas de Entrada:
*     - Deve existir um ponteiro para a lista a ser destruida.
*
*   Assertivas de Saída:
*     - Se a lista existe, ela é esvaziada, destruida e seu ponteiro 
*       aponta para NULL.
*
***********************************************************************/

   void LIS_DestruirLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC FunÁ„o: LIS  &Esvaziar lista
*
*  $ED DescriÁ„o da funÁ„o
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Par‚metros
*     pLista - ponteiro para a lista a ser esvaziada
*
*   Assertivas de Entrada:
*     - Deve existir um ponteiro para a lista a ser destruida.
*
*   Assertivas de Saída:
*     - Se a lista existe, ela é esvaziada.
*
***********************************************************************/

   void LIS_EsvaziarLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC FunÁ„o: LIS  &Inserir elemento antes
*
*  $ED DescriÁ„o da funÁ„o
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par‚metros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
*
*   Assertivas de Entrada:
*     - Deve existir um ponteiro para a lista a ser utilizada.
*     - Deve existir um valor a ser inserido na lista.
*
*   Assertivas de Saída:
*     - Se a lista existe e existe memória disponível, o valor é inserido
*       antes do valor corrente.
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           char  pValor        ) ;


/***********************************************************************
*
*  $FC FunÁ„o: LIS  &Inserir elemento apÛs
*
*  $ED DescriÁ„o da funÁ„o
*     Insere novo elemento ap·s o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par‚metros
*     Par‚metros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*           
*
*  $FV Valor retornado
*     Valor retornado
*        LIS_CondRetOK
*        LIS_CondRetFaltouMemoria
*
*   Assertivas de Entrada:
*     - Deve existir um ponteiro para a lista a ser utilizada.
*     - Deve existir um valor a ser inserido na lista.
*
*   Assertivas de Saída:
*     - Se a lista existe e existe memória disponível, o valor é 
*       inserido após o valor corrente.
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          char * pValor        )
       ;


/***********************************************************************
*
*  $FC FunÁ„o: LIS  &Excluir elemento
*
*  $ED DescriÁ„o da funÁ„o
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente ser· o novo corrente.
*     Se n„o existir e existir o elemento ‡ direita, este se tornar· corrente.
*     Se este tambÈm n„o existir a lista tornou-se vazia.
*
*  $EP Par‚metros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
*   Assertivas de Entrada:
*     - Deve existir um ponteiro para a lista a ser utilizada.
*
*   Assertivas de Saída:
*     - Se a lista existe e ela não é vazia, o elemento corrente da lista 
*       é excluido.
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC FunÁ„o: LIS  &Obter referÍncia para o valor contido no elemento
*
*  $ED DescriÁ„o da funÁ„o
*     Obtem a referÍncia para o valor contido no elemento corrente da lista
*
*  $EP Par‚metros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     n„o NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
*   Assertivas de Entrada:
*     - Deve existir um ponteiro para a lista a ser utilizada.
*
*   Assertivas de Saída:
*     - Se a lista existe, se não for vazia, a referência para o elemento 
*       corrente da lista é retornado.
*
***********************************************************************/

   char LIS_ObterValor( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC FunÁ„o: LIS  &Ir para o elemento inicial
*
*  $ED DescriÁ„o da funÁ„o
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista est· vazia.
*
*  $EP Par‚metros
*     pLista - ponteiro para a lista a manipular
*
*   Assertivas de Entrada:
*     - Deve existir um ponteiro para a lista a ser utilizada.
*
*   Assertivas de Saída:
*     - Se a lista existe, se não for vazia, torna corrente o primeiro 
*       elemento da lista.
*
***********************************************************************/

   void IrInicioLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC FunÁ„o: LIS  &Ir para o elemento final
*
*  $ED DescriÁ„o da funÁ„o
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista est· vazia.
*
*  $EP Par‚metros
*     pLista - ponteiro para a lista a manipular
*
*   Assertivas de Entrada:
*     - Deve existir um ponteiro para a lista a ser utilizada.
*
*   Assertivas de Saída:
*     - Se a lista existe, se não for vazia, torna corrente o último
*       elemento da lista.
*
***********************************************************************/

   void IrFinalLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC FunÁ„o: LIS  &AvanÁar elemento
*
*  $ED DescriÁ„o da funÁ„o
*     AvanÁa o elemento corrente numElem elementos na lista
*     Se numElem for positivo avanÁa em direÁ„o ao final
*     Se numElem for negativo avanÁa em direÁ„o ao inÌcio
*     numElem pode ser maior do que o n˙mro de elementos existentes na
*               direÁ„o desejada
*     Se numElem for zero somente verifica se a lista est· vazia
*
*  $EP Par‚metros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o n˙mero de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista est· vazia
*
*   Assertivas de Entrada:
*     - Deve existir um ponteiro para a lista a ser utilizada.
*     - Deve existir um valor representando o número de elementos que o
*       elemento corrente deve avançar.
*
*   Assertivas de Saída:
*     - Se a lista existe, se não for vazia e o valor for encontrado, a 
*       referência do valor é retornada.
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC FunÁ„o: LIS  &Procurar elemento contendo valor
*
*  $ED DescriÁ„o da funÁ„o
*     Procura o elemento que referencia o valor dado.
*     A funÁ„o compara ponteiro e n„o conte˙do apontado.
*
*  $EP Par‚metros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente È o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que contÈm o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o ponteiro n„o foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
*   Assertivas de Entrada:
*     - Deve existir um ponteiro para a lista a ser utilizada.
*     - Deve existir um ponteiro para o valor a ser procurado.
*
*   Assertivas de Saída:
*     - Se a lista existe, se não for vazia, a referência do valor 
*       procurado é o elemento corrente;
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    char * pValor        ) ;


   int testaCorrDiferenteOrigem(LIS_tppLista pLista);

#undef LISTA_EXT

/********** Fim do mÛdulo de definiÁ„o: LIS  Lista duplamente encadeada **********/

#else
#endif
