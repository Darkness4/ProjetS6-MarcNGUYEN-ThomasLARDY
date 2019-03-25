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
 * @brief Créer une population dans une grille length*length.
 * 
 * @param length Longueur de la
 * @return struct Personne** 
 */
struct Population* creerPopulation(const long length) {
    struct Population* population = (struct Population*)malloc(sizeof(struct Personne));
    struct Personne** grille_de_personnes = (struct Personne**)malloc(sizeof(struct Personne*)*length);
    for (int i = 0; i < length; i++) {
        grille_de_personnes[i] = (struct Personne*)malloc(sizeof(struct Personne)*length);

        grille_de_personnes[i]->state = SAIN;
    }
    population->grille_de_personnes = grille_de_personnes;
    population->length = length;
    return population;
}


/**
 * @brief Clone une population.
 * 
 * @param population_source Population source.
 * @return struct Population* Population destination.
 */
struct Population* clonerPopulation(struct Population* population_source) {
    struct Population* population = (struct Population*)malloc(sizeof(struct Personne));
    struct Personne** grille_de_personnes = (struct Personne**)malloc(sizeof(struct Personne*)*population_source->length);
    for (int i = 0; i < population_source->length; i++) {
        grille_de_personnes[i] = (struct Personne*)malloc(sizeof(struct Personne)*population_source->length);

        grille_de_personnes[i]->state = population_source->grille_de_personnes[i]->state;
    }
    population->grille_de_personnes = grille_de_personnes;
    population->length = population_source->length;
    return population;
}