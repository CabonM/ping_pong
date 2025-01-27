/************* Tests unitaires - ligne de commande **************/
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>

#include "erreur.h"
#include "nombre.h"

/** Montage de la fixation - appelé avant chaque cas de test. **/
int init_suite(void) { return 0; }

/* Démontage de la fixation - appelé après chaque cas de test. */
int clean_suite(void) { return 0; }

/******* Cas de test - lancement du client - cas nominal *******/
/* Le binaire retourne 0 en cas de succès - exit(0)            */
void test_ligne_commande_OK(void) {
  /* La fonction system() exécute une commande depuis le shell */
  CU_ASSERT(system("./multiplication 123 -5.1") == 0);
}

/****** Cas de test - lancement du client - cas d'erreur *******/
/* Le binaire retourne une valeur autre que 0 en cas d'échec   */
void test_ligne_commande_erreur(void) {
  /* Mauvais nombre d'argument                                 */
  /* La fonction system() exécute une commande depuis le shell */
  CU_ASSERT(system("./multiplication") != 0);
  CU_ASSERT(system("./multiplication 1") != 0);
  CU_ASSERT(system("./multiplication 1 2 3") != 0);

  /* Les arguments ne sont pas des nombres                     */
  CU_ASSERT(system("./multiplication abc 123") != 0);
  CU_ASSERT(system("./multiplication 123 abc") != 0);
  CU_ASSERT(system("./multiplication abc abc") != 0);
}

/******************* Lancement des tests ***********************/
int main ( void )
{
   CU_pSuite pSuite = NULL;
   unsigned int status = 0;

   /* initialisation des test CUnit */
   if ( CUE_SUCCESS != CU_initialize_registry() )
      return CU_get_error();

   /* ajout de la suite de test */
   pSuite = CU_add_suite( "Test ligne de commande", init_suite, clean_suite );
   if ( NULL == pSuite ) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* ajout des cas de test dans la suite de test */
   if ((NULL == CU_add_test(pSuite, "Cas de test - cas nominal", test_ligne_commande_OK)) ||
       (NULL == CU_add_test(pSuite, "Cas de test - ligne de commande sans argument", test_ligne_commande_erreur)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* lancement de tous les tests avec l'interface de base */
   CU_basic_set_mode(CU_BRM_NORMAL);
   if ( CUE_SUCCESS != CU_basic_run_tests() )
      return CU_get_error();
   
   status = CU_get_number_of_tests_failed();
   CU_basic_show_failures(CU_get_failure_list());
  
   /* cloture des tests */
   CU_cleanup_registry();

   printf("\n");
   return status;
}
