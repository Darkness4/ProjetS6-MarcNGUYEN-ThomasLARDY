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
struct Population* creerPopulation(const long cote) {
    struct Population* population = (struct Population*)malloc(sizeof(struct Personne));
    struct Personne*** grille_de_personnes = (struct Personne***)malloc(sizeof(struct Personne**)*cote);
    for (int i = 0; i < cote; i++) {
        grille_de_personnes[i] = (struct Personne**)malloc(sizeof(struct Personne*)*cote);
        for (int j = 0; j < cote; j++) {
            grille_de_personnes[i][j] = (struct Personne*)malloc(sizeof(struct Personne)*cote);

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
struct Population* clonerPopulation(struct Population* population_source) {
    struct Population* population = (struct Population*)malloc(sizeof(struct Personne));
    struct Personne*** grille_de_personnes = (struct Personne***)malloc(sizeof(struct Personne**)*population_source->cote);
    for (int i = 0; i < population_source->cote; i++) {
        grille_de_personnes[i] = (struct Personne**)malloc(sizeof(struct Personne*)*population_source->cote);
        for (int j = 0; j < population_source->cote; j++) {
            grille_de_personnes[i][j] = (struct Personne*)malloc(sizeof(struct Personne)*population_source->cote);

            grille_de_personnes[i][j]->state = population_source->grille_de_personnes[i][j]->state;
    }
    }
    population->grille_de_personnes = grille_de_personnes;
    population->cote = population_source->cote;
    return population;
}