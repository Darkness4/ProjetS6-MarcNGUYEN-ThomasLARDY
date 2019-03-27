/**
 * @file population_test.c
 * @author Marc NGUYEN
 * @author Thomas LARDY
 * @brief Lancer des tests unitaires sur les fonctions de manipulation de Population.
 * @date 27 Mar 2019
 * 
 */

#include <assert.h>
#include <stdio.h>

#include "../src/population.h"

/**
 * @brief Main pour tourner les tests unitaires.
 * 
 * @return int Exit 0.
 */
int main(void)
{
    printf("population_test:\n");
    printf("  creerPopulation:\n");
    struct Population *population = creerPopulation(7);
    assert(population->cote == 7);
    printf("    Population cote: \x1B[32mOK\x1B[0m\n");

    for (unsigned long i = 0; i < population->cote; i++)
    {
        for (unsigned long j = 0; j < population->cote; j++)
        {
            assert(population->grille_de_personnes[i][j]->state == SAIN);
        }
    }
    printf("    Population grille_de_personnes: \x1B[32mOK\x1B[0m\n");

    printf("  clonerPopulation:\n");
    struct Population *population_clone = clonerPopulation(population);
    assert(population_clone != population);
    printf("    Malloc Population Clone != Malloc Population Source: \x1B[32mOK\x1B[0m\n");
    assert(population_clone->cote == population->cote);
    printf("    Cote meme: \x1B[32mOK\x1B[0m\n");
    for (unsigned long i = 0; i < population_clone->cote; i++)
    {
        for (unsigned long j = 0; j < population_clone->cote; j++)
        {
            assert(population_clone->grille_de_personnes[i][j] != population->grille_de_personnes[i][j]);
        }
    }
    printf("    Malloc Personne Clone != Malloc Personne Source: \x1B[32mOK\x1B[0m\n");
    for (unsigned long i = 0; i < population_clone->cote; i++)
    {
        for (unsigned long j = 0; j < population_clone->cote; j++)
        {
            assert(population_clone->grille_de_personnes[i][j]->state == population->grille_de_personnes[i][j]->state);
        }
    }
    printf("    State Personne Clone == State Personne Source: \x1B[32mOK\x1B[0m\n");

    printf("  getStatistiques:\n");
    struct Statistique stats = getStatistique(population);
    assert(stats.nb_IMMUNISE == 0);
    printf("    nb_IMMUNISE: \x1B[32mOK\x1B[0m\n");
    assert(stats.nb_MORT == 0);
    printf("    nb_MORT: \x1B[32mOK\x1B[0m\n");
    assert(stats.nb_MALADE == 0);
    printf("    nb_MALADE: \x1B[32mOK\x1B[0m\n");
    assert(stats.nb_SAIN == 49);
    printf("    nb_SAIN: \x1B[32mOK\x1B[0m\n");
    return 0;
}
