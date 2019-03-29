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
struct Population *creerPopulation(const unsigned long cote) {
  struct Population *population =
      (struct Population *)malloc(sizeof(struct Personne));
  struct Personne ***grille_de_personnes =
      (struct Personne ***)malloc(sizeof(struct Personne **) * cote);
  for (unsigned long i = 0; i < cote; i++) {
    grille_de_personnes[i] =
        (struct Personne **)malloc(sizeof(struct Personne *) * cote);
    for (unsigned long j = 0; j < cote; j++) {
      grille_de_personnes[i][j] =
          (struct Personne *)malloc(sizeof(struct Personne) * cote);

      grille_de_personnes[i][j]->state = SAIN;
    }
  }
  population->grille_de_personnes = grille_de_personnes;
  population->cote = cote;
  return population;
}

/**
 * @brief Clone une grille d'une population.
 *
 * Usage:
 * @code
 * // Init
 * struct Population *population = creerPopulation(3);
 * struct Personne *** grille_de_personnes = clonerGrillePopulation(population);
 *
 * // Traitement
 * // ...
 *
 * // Fin
 * free(population)
 * free(grille_de_personnes)
 * @endcode
 *
 * @param population_source Population source.
 * @return struct Population* Grille de population destination.
 */
struct Personne ***clonerGrillePopulation(
    struct Population *population_source) {
  struct Personne ***grille_de_personnes = (struct Personne ***)malloc(
      sizeof(struct Personne **) * population_source->cote);
  for (unsigned long i = 0; i < population_source->cote; i++) {
    grille_de_personnes[i] = (struct Personne **)malloc(
        sizeof(struct Personne *) * population_source->cote);
    for (unsigned long j = 0; j < population_source->cote; j++) {
      grille_de_personnes[i][j] = (struct Personne *)malloc(
          sizeof(struct Personne) * population_source->cote);

      grille_de_personnes[i][j]->state =
          population_source->grille_de_personnes[i][j]->state;
    }
  }
  return grille_de_personnes;
}

/**
 * @brief Affiche la grille de population
 *
 * @param population_source Population source.
 */
void afficherGrillePopulation(struct Population *population) {
  for (unsigned long i = 0; i < population->cote; i++) printf("-");
  printf("\n");
  for (unsigned long i = 0; i < population->cote; i++) {
    for (unsigned long j = 0; j < population->cote; j++) {
      switch (population->grille_de_personnes[i][j]->state) {
        case IMMUNISE:
          printf("*");
          break;

        case MALADE:
          printf("o");
          break;

        case SAIN:
          printf("+");
          break;

        case MORT:
          printf(" ");
          break;

        default:
          break;
      }
    }
    printf("\n");
  }
  for (unsigned long i = 0; i < population->cote; i++) printf("-");
  printf("\n");
  printf("\n");
}
