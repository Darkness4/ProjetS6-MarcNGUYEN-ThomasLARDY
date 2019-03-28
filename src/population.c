/**
 * @file population.c
 *
 * @brief Manipulateur de population.
 *
 * Fonctionnalités :
 * - Créer
 * - Cloner
 *
 * @author Marc NGUYEN
 * @author Thomas LARDY
 * @date 26 Mar 2019
 */

#include <stdio.h>
#include <stdlib.h>

#include "population.h"

/**
 * @brief Créer une population dans une grille cote*cote.
 * 
 * Usage:
 * @code
 * // Init
 * struct Population *population = creerPopulation(3);
 *
 * // Traitement
 * //...
 *
 * // Fin
 * free(population)
 * @endcode
 * 
 * @param cote Longueur de la
 * @return struct Personne** 
 */
struct Population *creerPopulation(const unsigned long cote)
{
    struct Population *population = (struct Population *)malloc(sizeof(struct Personne));
    struct Personne ***grille_de_personnes = (struct Personne ***)malloc(sizeof(struct Personne **) * cote);
    for (unsigned long i = 0; i < cote; i++)
    {
        grille_de_personnes[i] = (struct Personne **)malloc(sizeof(struct Personne *) * cote);
        for (unsigned long j = 0; j < cote; j++)
        {
            grille_de_personnes[i][j] = (struct Personne *)malloc(sizeof(struct Personne) * cote);

            grille_de_personnes[i][j]->state = SAIN;
        }
    }
    population->grille_de_personnes = grille_de_personnes;
    population->cote = cote;
    return population;
}

/**
 * @brief Clone une population.
 * 
 * Usage:
 * @code
 * // Init
 * struct Population *population1 = creerPopulation(3);
 * struct Population *population2 = clonerPopulation(population1);
 * 
 * // Traitement
 * // ...
 * 
 * // Fin
 * free(population1)
 * free(population2)
 * @endcode
 * 
 * @param population_source Population source.
 * @return struct Population* Population destination.
 */
struct Population *clonerPopulation(struct Population *population_source)
{
    struct Population *population = (struct Population *)malloc(sizeof(struct Personne));
    struct Personne ***grille_de_personnes = (struct Personne ***)malloc(sizeof(struct Personne **) * population_source->cote);
    for (unsigned long i = 0; i < population_source->cote; i++)
    {
        grille_de_personnes[i] = (struct Personne **)malloc(sizeof(struct Personne *) * population_source->cote);
        for (unsigned long j = 0; j < population_source->cote; j++)
        {
            grille_de_personnes[i][j] = (struct Personne *)malloc(sizeof(struct Personne) * population_source->cote);

            grille_de_personnes[i][j]->state = population_source->grille_de_personnes[i][j]->state;
        }
    }
    population->grille_de_personnes = grille_de_personnes;
    population->cote = population_source->cote;
    return population;
}
