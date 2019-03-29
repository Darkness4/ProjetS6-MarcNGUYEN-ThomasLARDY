/**
 * @dir src
 * @brief Dossier code source
 */

/**
 * @file main.c
 *
 * @brief Propagation d’une épidémie dans une population avec une structure de
 * graphe
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
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "jouer_un_tour.h"
#include "population.h"
#include "statistique.h"

/**
 * @brief Execute la simulation d'une propagation, et sort des statistiques.
 *
 *
 * @param argc Nombres d'arguments
 * @param argv [1] cote: Population de taille cote*cote
 * @return int exit(0)
 */
int main(int argc, char const* argv[]) {
  // Default
  srand(time(NULL));
  unsigned long cote = 10;
  unsigned long hauteur = 100;
  unsigned long limite = 80;
  double beta = 0.5;    // MALADE -> MORT
  double gamma = 0.1;   // MALADE -> IMMUNISE
  double lambda = 1.0;  // SAIN -> MALADE
  char* file_graph = "graphique.txt";
  char* file_data = "data.txt";
  unsigned long tour_max = 500;

  // Constructeur
  for (int i = 0; i < argc; i++) {
    if (!strcmp(argv[i], "-c") || !strcmp(argv[i], "--cote"))
      sscanf(argv[i + 1], "%lu", &cote);
    if (!strcmp(argv[i], "-b") || !strcmp(argv[i], "--beta") ||
        !strcmp(argv[i], "--mort"))
      sscanf(argv[i + 1], "%lf", &beta);
    if (!strcmp(argv[i], "-g") || !strcmp(argv[i], "--gamma") ||
        !strcmp(argv[i], "--immunise"))
      sscanf(argv[i + 1], "%lf", &gamma);
    if (!strcmp(argv[i], "-la") || !strcmp(argv[i], "--lambda") ||
        !strcmp(argv[i], "--malade"))
      sscanf(argv[i + 1], "%lf", &lambda);
    if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--hauteur"))
      sscanf(argv[i + 1], "%lu", &hauteur);
    if (!strcmp(argv[i], "-li") || !strcmp(argv[i], "--limite"))
      sscanf(argv[i + 1], "%lu", &limite);
    if (!strcmp(argv[i], "-fg") || !strcmp(argv[i], "--graph") ||
        !strcmp(argv[i], "-og"))
      file_graph = argv[i + 1];
    if (!strcmp(argv[i], "-fd") || !strcmp(argv[i], "--data") ||
        !strcmp(argv[i], "-o") || !strcmp(argv[i], "-od"))
      file_data = argv[i + 1];
    if (!strcmp(argv[i], "-t") || !strcmp(argv[i], "--tours") ||
        !strcmp(argv[i], "--tour"))
      sscanf(argv[i + 1], "%lu", &tour_max);
  }

  // Init
  struct Statistique stats;
  struct Data* data = creerData();
  struct Population* population = creerPopulation(cote);
  data->population_totale = getTaillePopulation(population);
  stats = getStatistique(population);
  appendData(data, stats);

  // Traitement
  population->grille_de_personnes[0][0]->state = MALADE;
  afficherGrillePopulation(population);
  for (unsigned long i = 0; i < tour_max && zombiePresent(population); i++) {
    jouerTour(population, beta, gamma, lambda);
    stats = getStatistique(population);
    afficherGrillePopulation(population);
    appendData(data, stats);
  }

  // Output
  char** graph = graphique(data, file_graph, hauteur, limite);
  exporter(data, file_data);
  for (unsigned long i = 0; i < hauteur; i++) {
    for (unsigned long j = 0; j < limite; j++) printf("%c", graph[i][j]);
    printf("\n");
  }

  return 0;
}
