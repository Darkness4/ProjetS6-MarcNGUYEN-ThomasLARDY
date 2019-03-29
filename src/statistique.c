/**
 * @file statistique.c
 *
 * @brief Gère le stockage de donnée et la récupération de métrique.
 *
 * Usage:
 * @code
 * struct Population *population = creerPopulation(7);  // population.h
 * struct Data *data = creerData(void);
 * struct Statistique stats = getStatistique(population);
 * data->population_totale = getTaillePopulation(population);
 *
 * appendData(data, stats);
 *
 * // Traitement ...
 *
 * appendData(data, stats);
 *
 * struct Data *data_derive = deriver(data);
 *
 * exporter(data, "data.txt")
 * exporter(data_derive, "data_derive.txt")
 * @endcode
 *
 * @author Marc NGUYEN
 * @author Thomas LARDY
 * @date 27 Mar 2019
 */

#include <stdio.h>
#include <stdlib.h>

#include "statistique.h"

/**
 * @brief Créer une base de données.
 *
 * @return struct Data* Base de données.
 */
struct Data *creerData(void) {
  struct Data *data = (struct Data *)malloc(sizeof(struct Data));
  struct Statistique **liste_statistiques = (struct Statistique **)malloc(0);
  data->liste_statistiques = liste_statistiques;
  data->tours = 0;
  return data;
}

/**
 * @brief Ajoute une donnée à la base.
 *
 * Usage:
 * @code
 * struct Population *population = creerPopulation(7);
 * struct Statistique stats = getStatistique(population);
 * struct Data *data = creerData();
 * appendData(data, stats);
 * @endcode
 *
 * @param data Base de données.
 * @param stats Donnée à ajouter.
 */
void appendData(struct Data *data, struct Statistique stats) {
  // Nouvelle allocation de mémoire
  struct Statistique **nouvelle_liste_statistiques =
      (struct Statistique **)malloc(sizeof(struct Statistique *) * data->tours +
                                    1);
  for (unsigned long i = 0; i < data->tours; i++)
    nouvelle_liste_statistiques[i] = data->liste_statistiques[i];

  data->liste_statistiques = nouvelle_liste_statistiques;
  data->liste_statistiques[data->tours] =
      (struct Statistique *)malloc(sizeof(struct Statistique));
  data->liste_statistiques[data->tours]->nb_IMMUNISE = stats.nb_IMMUNISE;
  data->liste_statistiques[data->tours]->nb_SAIN = stats.nb_SAIN;
  data->liste_statistiques[data->tours]->nb_MORT = stats.nb_MORT;
  data->liste_statistiques[data->tours]->nb_MALADE = stats.nb_MALADE;
  data->tours++;
}

/**
 * @brief Exporte les données brutes dans un fichier fichier_data.
 *
 * Le tableau est de la forme [tour, population totale, nb_IMMUNISE, nb_SAIN,
 * nb_MORT, nb_MALADE]
 *
 * @param data Base de données.
 * @param fichier_data Nom du fichier à écrire.
 */
void exporter(struct Data *data, const char *fichier_data) {
  FILE *file = fopen(fichier_data, "w");
  if (!file) {
    printf("Erreur: Le fichier n'a pas pu être ouvert.\n");
    exit(1);
  }

  fprintf(file, "%lu\n", data->population_totale);
  fprintf(file, "%lu\n", data->tours);
  for (unsigned long i = 0; i < data->tours; i++) {
    fprintf(file, "%lu %li %li %li %li\n", i,
            data->liste_statistiques[i]->nb_IMMUNISE,
            data->liste_statistiques[i]->nb_SAIN,
            data->liste_statistiques[i]->nb_MORT,
            data->liste_statistiques[i]->nb_MALADE);
  }

  fclose(file);
}

/**
 * @brief Dérive tel que x(t+1)-x(t)
 *
 * @param data Structure Data source
 * @return struct Data* Structure Data avec liste_statistiques dérivée.
 */
struct Data *deriver(struct Data *data) {
  struct Data *data_derive = creerData();
  struct Statistique stats;

  for (unsigned long i = 0; i < data->tours - 1; i++) {
    stats.nb_IMMUNISE = data->liste_statistiques[i + 1]->nb_IMMUNISE -
                        data->liste_statistiques[i]->nb_IMMUNISE;
    stats.nb_SAIN = data->liste_statistiques[i + 1]->nb_SAIN -
                    data->liste_statistiques[i]->nb_SAIN;
    stats.nb_MORT = data->liste_statistiques[i + 1]->nb_MORT -
                    data->liste_statistiques[i]->nb_MORT;
    stats.nb_MALADE = data->liste_statistiques[i + 1]->nb_MALADE -
                      data->liste_statistiques[i]->nb_MALADE;
    appendData(data_derive, stats);
  }
  data_derive->tours = data->tours - 1;
  data_derive->population_totale = data->population_totale;
  return data_derive;
}

/**
 * @brief Obtenir des métriques intéressantes sur la population.
 *
 * Usage:
 * @code
 * struct Statistique stats = getStatistique(population);
 * printf("%lu\n", stats.nb_IMMUNISE);
 * printf("%lu\n", stats.nb_SAIN);
 * printf("%lu\n", stats.nb_MALADE);
 * printf("%lu\n", stats.nb_MORT);
 * @endcode
 *
 * @param population Population contenant la tailler et la grille.
 * @return struct Statistique Structure contenant le nombre de struct State.
 */
struct Statistique getStatistique(struct Population *population) {
  struct Statistique statistique = {0, 0, 0, 0};
  for (long unsigned i = 0; i < population->cote; i++) {
    for (long unsigned j = 0; j < population->cote; j++) {
      switch (population->grille_de_personnes[i][j]->state) {
        case IMMUNISE:
          statistique.nb_IMMUNISE++;
          break;
        case SAIN:
          statistique.nb_SAIN++;
          break;
        case MALADE:
          statistique.nb_MALADE++;
          break;
        case MORT:
          statistique.nb_MORT++;
          break;
      }
    }
  }
  return statistique;
}

/**
 * @brief Récupérer la taille totale de la Population de la Population
 *
 * @param population Structure Population.
 * @return unsigned long Taille totale de la population.
 */
unsigned long getTaillePopulation(struct Population *population) {
  return population->cote * population->cote;
}

/**
 * @brief Exporte un graph style ASCII dans un fichier fichier_data.
 *
 * IMMUNISE = '*'
 * SAIN = '+'
 * MALADE = 'o'
 * MORT = ' '
 *
 * @param data Base de données.
 * @param fichier_data Nom du fichier à écrire.
 * @param hauteur Hauteur du graphique
 * @param limite Limite en tour du graphique (permet de compresser le graphique)
 * @return char** Graphique[ligne][charactère]
 */
char **graphique(struct Data *data, const char *fichier_data,
                 unsigned long hauteur, unsigned long limite) {
  FILE *file;

  char **graphique = (char **)malloc(sizeof(char *) * hauteur);
  for (unsigned long i = 0; i < hauteur; i++) {
    graphique[i] = (char *)malloc(sizeof(char) * limite);
    for (unsigned long j = 0; j < limite; j++) {
      graphique[i][j] = ' ';
    }
  }
  unsigned long pop_tot = data->population_totale;
  unsigned long ratio_tour = data->tours / limite;
  if (ratio_tour == 0) ratio_tour = 1;
  struct Statistique **stats = data->liste_statistiques;

  for (unsigned long tour = 0; tour < data->tours - ratio_tour + 1;
       tour += ratio_tour) {
    unsigned long ratio_nb_IMMUNISE_norm = 0;
    unsigned long ratio_nb_MORT_norm = 0;
    unsigned long ratio_nb_SAIN_norm = 0;
    unsigned long ratio_nb_MALADE_norm = 0;
    for (unsigned long i = 0; i < ratio_tour; i++) {
      ratio_nb_IMMUNISE_norm += stats[tour + i]->nb_IMMUNISE;
      ratio_nb_MORT_norm += stats[tour + i]->nb_MORT;
      ratio_nb_SAIN_norm += stats[tour + i]->nb_SAIN;
      ratio_nb_MALADE_norm += stats[tour + i]->nb_MALADE;
    }

    // Ratio normalizé (quand positif, conversion float vers int = floor)
    ratio_nb_IMMUNISE_norm =
        ratio_nb_IMMUNISE_norm * hauteur / ratio_tour / pop_tot;
    ratio_nb_MORT_norm = ratio_nb_MORT_norm * hauteur / ratio_tour / pop_tot;
    ratio_nb_SAIN_norm = ratio_nb_SAIN_norm * hauteur / ratio_tour / pop_tot;
    ratio_nb_MALADE_norm =
        ratio_nb_MALADE_norm * hauteur / ratio_tour / pop_tot;

    // Print
    unsigned long curseur = 0;
    for (unsigned long i = 0; i < ratio_nb_IMMUNISE_norm; i++) {
      graphique[curseur][tour / ratio_tour] = '*';
      curseur++;
    }
    for (unsigned long i = 0; i < ratio_nb_SAIN_norm; i++) {
      graphique[curseur][tour / ratio_tour] = '+';
      curseur++;
    }
    for (unsigned long i = 0; i < ratio_nb_MALADE_norm; i++) {
      graphique[curseur][tour / ratio_tour] = 'o';
      curseur++;
    }
    for (unsigned long i = 0; i < ratio_nb_MORT_norm; i++) curseur++;
    // if (curseur >= hauteur)
    // printf(
    //     "Attention, le curseur aurait du provoquer une erreur de "
    //     "segmentation !\n"
    //     "Le graph n'est pas precis !\n");
  }

  // Ecrire sur le fichier
  file = fopen(fichier_data, "w");
  if (!file) {
    printf("Erreur: Le fichier n'a pas pu être ouvert.\n");
    exit(1);
  }
  for (unsigned long i = 0; i < hauteur; i++) {
    for (unsigned long j = 0; j < limite; j++) {
      fprintf(file, "%c", graphique[i][j]);
    }
    fprintf(file, "\n");
  }

  fclose(file);

  return graphique;
}
