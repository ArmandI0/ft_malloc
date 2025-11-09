#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// Remplacez par votre propre include si nécessaire
#include "include/malloc.h" 

#define NUM_THREADS 10        // Nombre de threads à créer
#define ALLOCATIONS_PER_THREAD 100 // Nombre d'allocations par thread
#define MAX_SIZE 1024         // Taille maximale d'une allocation (en octets)
#define MAX_MSG_LEN 128       // Longueur max du buffer pour les messages

// Mutex pour synchroniser l'accès à la sortie standard (stdout)
// C'est la seule variable globale (en dehors de la configuration de votre malloc)
// qui est partagée entre les threads pour l'I/O.
pthread_mutex_t g_write_mutex = PTHREAD_MUTEX_INITIALIZER;


// Fonction utilitaire qui utilise UN SEUL appel write(2)
// Elle utilise un mutex pour garantir que les écritures de différents threads ne se mélangent pas.
// Cette fonction ne fait que l'écriture et est l'unique point d'accès à l'I/O.
void safe_write(const char *msg) {
    size_t len = strlen(msg);
    
    // Verrouillage : un seul thread peut écrire à la fois.
    pthread_mutex_lock(&g_write_mutex);

    // Écrire directement sur le descripteur de fichier standard (1 = stdout)
    // On s'assure qu'un seul appel write est fait pour le message complet.
    write(1, msg, len);

    // Déverrouillage
    pthread_mutex_unlock(&g_write_mutex);
}

// Structure pour passer les arguments au thread
typedef struct {
    int thread_id;
} thread_data_t;

// Fonction exécutée par chaque thread
void *thread_func(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    int id = data->thread_id;
    char log_buffer[MAX_MSG_LEN];

    // Utilisation de snprintf dans un buffer local pour formater le message.
    // Cette opération est thread-safe car le buffer est local à la pile du thread.
    snprintf(log_buffer, MAX_MSG_LEN, "Thread %d: Démarrage des allocations...\n", id);
    safe_write(log_buffer);

    for (int i = 0; i < ALLOCATIONS_PER_THREAD; i++) {
        // Détermination d'une taille aléatoire entre 1 et MAX_SIZE
        size_t size = (rand() % MAX_SIZE) + 1; 

        // 1. ALLOCATION
        char *ptr = (char *)malloc(size);

        if (ptr == NULL) {
            snprintf(log_buffer, MAX_MSG_LEN, "Thread %d: Échec de l'allocation pour la taille %zu\n", id, size);
            safe_write(log_buffer);
            continue;
        }

        // 2. ÉCRITURE/UTILISATION DE LA MÉMOIRE
        for (size_t j = 0; j < size; j++) {
            // Utiliser une valeur basée sur l'ID du thread
            ptr[j] = (char)('A' + (id % 26)); 
        }

        // 3. VÉRIFICATION (simple, on vérifie seulement le premier octet)
        if (ptr[0] != (char)('A' + (id % 26))) {
            snprintf(log_buffer, MAX_MSG_LEN, "Thread %d: ERREUR de corruption de mémoire détectée sur l'allocation %d !\n", id, i);
            safe_write(log_buffer);
        }

        // Simuler un peu de travail ou une pause
        usleep(rand() % 100); 

        // 4. LIBÉRATION
        free(ptr);
    }

    snprintf(log_buffer, MAX_MSG_LEN, "Thread %d: Terminé après %d allocations/libérations.\n", id, ALLOCATIONS_PER_THREAD);
    safe_write(log_buffer);
    
    pthread_exit(NULL);
}

int main() {
    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL)); 

    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];
    int rc;
    long t;
    char log_buffer[MAX_MSG_LEN];

    snprintf(log_buffer, MAX_MSG_LEN, "Démarrage du test de thread-safety de Malloc avec %d threads...\n", NUM_THREADS);
    safe_write(log_buffer);

    // Création des threads
    for (t = 0; t < NUM_THREADS; t++) {
        thread_data[t].thread_id = (int)t;
        
        snprintf(log_buffer, MAX_MSG_LEN, "Création du thread %ld\n", t);
        safe_write(log_buffer);
        
        rc = pthread_create(&threads[t], NULL, thread_func, &thread_data[t]);
        
        if (rc) {
            snprintf(log_buffer, MAX_MSG_LEN, "ERREUR: code de retour de pthread_create() est %d (%s)\n", rc, strerror(rc));
            safe_write(log_buffer);
            return 1;
        }
    }

    // Attente de la fin de tous les threads
    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    safe_write("\nTest terminé. Si aucune erreur n'a été affichée ci-dessus (corruption, échec d'allocation) et le programme se termine correctement, votre malloc est probablement thread-safe.\n");
    safe_write("**REMARQUE : Exécutez avec Valgrind --tool=helgrind pour confirmer l'absence de race conditions dans votre MALLOC.**\n");
    
    // Libération du mutex (bonne pratique)
    pthread_mutex_destroy(&g_write_mutex);

    return 0;
}