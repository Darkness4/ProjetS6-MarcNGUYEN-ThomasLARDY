/** 
 * @dir src
 * @brief Dossier code source
 */

/**
 * @file main.c
 *
 * @brief Propagation d’une épidémie dans une population avec une structure de graphe
 *
 * Fichier principal.
 *
 * Fonctionnalités :
 * - Simulateur de propagation d’une épidémie dans une population
 * - Analyse des performances
 * - Extensions
 *
 * @author Marc NGUYEN
 * @author Thomas LARDY
 * @date 26 Mar 2019
 */

#include <stdio.h>

#include "population.h"

/**
 * @brief Execute la simulation d'une propagation, et sort des statistiques.
 * 
 * 
 * @param argc Nombres d'arguments
 * @param argv [1] cote: Population de taille cote*cote
 * @return int exit(0)
 */
int main(int argc, char const *argv[])
{
  unsigned long cote = 10;
  if (argc > 1)
    sscanf(argv[1], "%lu", &cote);

  struct Population *population = creerPopulation(cote);

  return 0;
}
