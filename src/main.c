#include "../include/malloc.h"
#include <string.h> // Pour ft_memcpy, ft_memcmp, ft_strncmp (qui sont dans libft)


int main() {
	char *toto = malloc(100);

	for (int i = 0; i < 100; i++) {
		toto[i] = i;
	}
	show_alloc_mem_ex();
}


// /**
//  * @brief Affiche un en-tête de section pour la clarté des logs.
//  */
// void	print_header(const char *test_name)
// {
// 	ft_printf("\n======================================================\n");
// 	ft_printf("  TEST: %s\n", test_name);
// 	ft_printf("======================================================\n");
// }

// /**
//  * @brief Remplit une zone mémoire avec un motif et le vérifie.
//  */
// void	fill_and_check(void *ptr, size_t size, char c)
// {
// 	if (!ptr)
// 		return;
	
// 	// Remplit la mémoire
// 	size_t i = 0;
// 	while (i < size)
// 	{
// 		((char *)ptr)[i] = c;
// 		i++;
// 	}
	
// 	// Vérifie la mémoire
// 	i = 0;
// 	while (i < size)
// 	{
// 		if (((char *)ptr)[i] != c)
// 		{
// 			ft_printf("  [ERREUR] Corruption mémoire détectée à %p (index %zu)\n", ptr, i);
// 			return;
// 		}
// 		i++;
// 	}
// 	ft_printf("  [OK] Remplissage et vérification de %zu bytes à %p avec '%c'\n", size, ptr, c);
// }

// int	main(void)
// {
// 	// p8 et p9 ont été retirés
// 	void	*p1, *p2, *p3, *p4, *p5, *p6, *p7;

// 	ft_printf("Démarrage du programme de test Malloc...\n");
// 	ft_printf("TINY_MAX: %d, SMALL_MAX: %d\n", TINY, SMALL);
// 	ft_printf("NB_TINY_BLOCS: %d, NB_SMALL_BLOCS: %d\n", NB_TINY_BLOCS, NB_SMALL_BLOCS);

// 	// --- Test 1: Allocations Simples ---
// 	print_header("Allocations Simples (TINY, SMALL, LARGE)");
// 	p1 = malloc(TINY);       // 128 bytes
// 	p2 = malloc(SMALL);      // 1024 bytes
// 	// Corrigé: Utilisation de SMALL + 1 pour tester "LARGE"
// 	p3 = malloc(SMALL + 1);  
	
// 	ft_printf("  TINY  (%d) alloué à : %p\n", TINY, p1);
// 	ft_printf("  SMALL (%d) alloué à : %p\n", SMALL, p2);
// 	ft_printf("  LARGE (%d) alloué à : %p\n", SMALL + 1, p3);

// 	fill_and_check(p1, TINY, 'T');
// 	fill_and_check(p2, SMALL, 'S');
// 	// Corrigé: Utilisation de SMALL + 1
// 	fill_and_check(p3, SMALL + 1, 'L');
	
// 	show_alloc_mem();

// 	// --- Test 2: Free Simple et Réutilisation ---
// 	print_header("Free Simple et Réutilisation (TINY)");
// 	ft_printf("  Libération de p1 (TINY) : %p\n", p1);
// 	free(p1);
// 	show_alloc_mem();

// 	ft_printf("  Allocation de p4 (TINY) de 50 bytes\n");
// 	p4 = malloc(50);
// 	ft_printf("  p4 alloué à : %p\n", p4);
// 	if (p4 == p1)
// 		ft_printf("  [SUCCÈS] Le bloc p1 a été réutilisé pour p4.\n");
// 	else
// 		ft_printf("  [ERREUR] Le bloc p1 n'a PAS été réutilisé pour p4.\n");
	
// 	fill_and_check(p4, 50, 'A');
// 	show_alloc_mem();

// 	// --- Test 3: Fragmentation et Réutilisation multiple ---
// 	print_header("Fragmentation et Réutilisation (TINY & SMALL)");
// 	ft_printf("  Libération de p2 (SMALL), p3 (LARGE), p4 (TINY)\n");
// 	free(p2);
// 	free(p3);
// 	free(p4);
// 	show_alloc_mem(); // Tout devrait être vide

// 	ft_printf("  Allocation de 3xTINY et 2xSMALL entrelacés\n");
// 	p1 = malloc(10); // TINY
// 	p2 = malloc(200); // SMALL
// 	p3 = malloc(20); // TINY
// 	p4 = malloc(300); // SMALL
// 	p5 = malloc(30); // TINY
	
// 	ft_printf("  p1(T): %p, p2(S): %p, p3(T): %p, p4(S): %p, p5(T): %p\n", p1, p2, p3, p4, p5);
// 	show_alloc_mem();
	
// 	ft_printf("  Libération de p1, p3, p5 (TINY) et p4 (SMALL)\n");
// 	free(p1);
// 	free(p3);
// 	free(p5);
// 	free(p4);
// 	show_alloc_mem(); // p2 (SMALL) doit rester

// 	ft_printf("  Allocation de p6(TINY) et p7(SMALL)\n");
// 	p6 = malloc(10);  // Devrait réutiliser p5 (ou p3 ou p1)
// 	p7 = malloc(250); // Devrait réutiliser p4
// 	ft_printf("  p6(T): %p, p7(S): %p\n", p6, p7);
// 	if (p7 == p4)
// 		ft_printf("  [SUCCÈS] Le bloc SMALL p4 a été réutilisé pour p7.\n");
// 	else
// 		ft_printf("  [ERREUR] Le bloc SMALL p4 n'a PAS été réutilisé pour p7.\n");
	
// 	show_alloc_mem();
	
// 	ft_printf("  Nettoyage Test 3\n");
// 	free(p2);
// 	free(p6);
// 	free(p7);
// 	show_alloc_mem(); // Devrait être vide

// 	// --- Test 4: Saturation de la page TINY ---
// 	print_header("Saturation de la page TINY (Allocation de nouvelle page)");
// 	void *tiny_addrs[NB_TINY_BLOCS + 5];
// 	ft_printf("  Allocation de %d blocs TINY pour forcer une nouvelle page...\n", NB_TINY_BLOCS + 5);
	
// 	int i;
// 	for (i = 0; i < NB_TINY_BLOCS + 5; i++)
// 	{
// 		tiny_addrs[i] = malloc(TINY / 2);
// 		if (tiny_addrs[i] == NULL)
// 		{
// 			ft_printf("  [ERREUR] Malloc a échoué à l'itération %d\n", i);
// 			break;
// 		}
// 	}
// 	ft_printf("  %d blocs alloués.\n", i);
	
// 	ft_printf("  --- Début de show_alloc_mem (devrait montrer >1 région TINY) ---\n");
// 	show_alloc_mem();
// 	ft_printf("  --- Fin de show_alloc_mem ---\n");

// 	ft_printf("  Libération des %d blocs TINY...\n", i);
// 	for (int j = 0; j < i; j++)
// 	{
// 		free(tiny_addrs[j]);
// 	}
// 	show_alloc_mem(); // Devrait être vide

// 	// --- Test 5: Cas Particuliers ---
// 	print_header("Cas Particuliers (NULL et 0)");
	
// 	ft_printf("  Appel de free(NULL)...\n");
// 	free(NULL);
// 	ft_printf("  [SUCCÈS] free(NULL) n'a pas crashé.\n");

// 	ft_printf("  Appel de malloc(0)...\n");
// 	p1 = malloc(0);
// 	ft_printf("  malloc(0) a retourné : %p\n", p1);
// 	if (p1 != NULL)
// 	{
// 		ft_printf("  INFO: malloc(0) a retourné un pointeur non-NULL. C'est un comportement valide.\n");
// 		ft_printf("  Tentative de free(p1)...\n");
// 		free(p1);
// 		ft_printf("  [SUCCÈS] free(p1) a réussi.\n");
// 	}
// 	else
// 	{
// 		ft_printf("  INFO: malloc(0) a retourné NULL. C'est aussi un comportement valide.\n");
// 	}
// 	show_alloc_mem();

// 	// --- Test 6: Realloc ---
// 	print_header("Test de Realloc");
	
// 	ft_printf("  Allocation de p1 (TINY) de 80 bytes\n");
// 	p1 = malloc(80);
// 	if (!p1)
// 	{
// 		ft_printf("  [ERREUR] Malloc initial a échoué.\n");
// 		return 1;
// 	}
// 	ft_memcpy(p1, "Test de realloc", 16);
// 	ft_printf("  p1 (%p) contient : '%s'\n", p1, (char *)p1);
// 	show_alloc_mem();

// 	ft_printf("  Appel de realloc(p1, 200) (TINY -> SMALL)...\n");
// 	p2 = realloc(p1, 200);
// 	ft_printf("  realloc a retourné : %p\n", p2);

// 	if (p2 == NULL)
// 	{
// 		ft_printf("  [INFO] realloc a retourné NULL.\n");
// 		ft_printf("  NOTE: Ton realloc est appelé, mais les fonctions tiny/small/large_malloc\n");
// 		ft_printf("  n'ont pas de 'case REALLOC:' dans leur switch. C'est pourquoi rien ne se passe.\n");
// 		ft_printf("  p1 (%p) devrait toujours être alloué et intact.\n", p1);
		
// 		if (ft_strncmp(p1, "Test de realloc", 16) == 0)
// 			ft_printf("  [SUCCÈS] p1 est intact.\n");
// 		else
// 			ft_printf("  [ERREUR] p1 a été corrompu !\n");
		
// 		show_alloc_mem(); // p1 doit être là
// 		free(p1); // Nettoyage
// 	}
// 	else
// 	{
// 		ft_printf("  [INFO] realloc a retourné un nouveau pointeur : %p\n", p2);
// 		ft_printf("  Vérification de la copie des données (ATTENTION: bug probable dans realloc_op)...\n");
		
// 		if (ft_memcmp(p2, "Test de realloc", 16) == 0)
// 		{
// 			ft_printf("  [SUCCÈS] Les données ont été copiées !\n");
// 		}
// 		else
// 		{
// 			ft_printf("  [ERREUR/BUG] Les données n'ont PAS été copiées de p1 à p2 !\n");
// 			ft_printf("  Contenu de p2 : 'garbage'\n");
// 		}
		
// 		// realloc_op semble aussi oublier de free l'ancien pointeur p1
// 		ft_printf("  Vérification si l'ancien pointeur p1 a été libéré (ATTENTION: bug probable)...\n");
// 		show_alloc_mem(); // p1 ET p2 pourraient être alloués ici
// 		free(p2);
// 	}


// 	// --- Test Final ---
// 	print_header("Test Final (Nettoyage et vérification)");
// 	ft_printf("  Allocation de 3 blocs (T, S, L)...\n");
// 	p1 = malloc(10);
// 	p2 = malloc(200);
// 	p3 = malloc(2000);
// 	show_alloc_mem();
// 	ft_printf("  Libération des 3 blocs...\n");
// 	free(p1);
// 	free(p2);
// 	free(p3);
// 	ft_printf("  Affichage final (tout doit être vide) :\n");
// 	show_alloc_mem();
	
// 	ft_printf("\nFin du programme de test Malloc.\n");
// 	return (0);
// }