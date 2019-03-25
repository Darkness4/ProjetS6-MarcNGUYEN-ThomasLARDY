/**
 * @file population.c
 * @author your name (you@domain.com)
 * @brief Manipuler une population.
 * @version 0.1
 * @date 2019-03-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include "population.h"

/**
 * @brief Créer une population dans une grille cote*cote.
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

/**
 * @brief .
 * 
 * @param population Population contenant la tailler et la grille.
 * @return struct Statistique Structure contenant le nombre de struct State.
 */
struct Statistique getStatistique(struct Population *population)
{
    struct Statistique statistique = {population->cote * population->cote, 0, 0, 0, 0};
    for (int i = 0; i < population->cote; i++)
    {
        for (int j = 0; j < population->cote; j++)
        {
            switch (population->grille_de_personnes[i][j]->state)
            {
            case IMMUNISE:
                statistique.nb_IMMUNISE++;
                break;
            case SAIN:
                statistique.nb_SAIN++;
                break;
            case MALADE:
                statistique.nb_IMMUNISE++;
                break;
            case MORT:
                statistique.nb_MORT++;
                break;
            }
        }
    }
    return statistique;
}
