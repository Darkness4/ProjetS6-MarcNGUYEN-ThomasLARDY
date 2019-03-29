/**
 * @file jouer_un_tour.c
 *
 * @brief Lancer un tour.
 *
 * Fichier principal.
 *
 * Fonctionnalités :
 * - Détecteur de zombie.
 * - jouerTour lancer un tour.
 *
 * Usage pour jouer un jeu complet:
 * @code
 * char est_fini = 0;
 * int tour_max = 500;
 * struct Population* population = creerPopulation(7);  // TODO add function
 * infecter. for(int i = 0; (i<tour_max)&&(!est_fini); i++) {
 *     jouerTour(population);
 *     est_fini = presenceZombie(population);
 * }
 * @endcode
 *
 * @author Marc NGUYEN
 * @author Thomas LARDY
 * @date 28 Mar 2019
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "jouer_un_tour.h"

/**
 * @brief Renvoie true s'il y a encore au moins un zombie dans la population,
 * false dans le cas contraire.
 *
 * Usage:
 * @code
 * struct Population* population = creerPopulation(7);
 * char boolean = presenceZombie(population);  // -> false;
 * @endcode
 *
 * @param population Grille représentant la population.
 * @return char Booléen, si zombies toujours présents.
 */
char presenceZombie(struct Population *population) {
  unsigned long cote = population->cote;
  for (unsigned long i = 0; i < cote; i++) {
    for (unsigned long j = 0; j < cote; j++) {
      if (population->grille_de_personnes[i][j]->state == MALADE) return 1;
    }
  }
  return 0;
}

/**
 * @brief Faire passer la population->grille_de_personnes du temps t au temps
 * t+1.
 *
 * Usage pour jouer un jeu complet:
 * @code
 * char est_fini = 0;
 * int tour_max = 500;
 * struct Population* population = creerPopulation(7);  // TODO add function
 * infecter. for(int i = 0; (i<tour_max)&&(!est_fini); i++) {
 *     jouerTour(population);
 *     est_fini = presenceZombie(population);
 * }
 * @endcode
 *
 * @param population Grille au temps t.
 * @param beta Probabilité d'un individu infecté de mourir.
 * @param gamma Probabilité d'un individu infecté de guérir.
 * @param lambda Probabilité d'un individu sain d'être contaminé par un individu
 * voisin infecté.
 */
void jouerTour(struct Population *population, double beta, double gamma,
               double lambda) {
  const long unsigned cote = population->cote;

  srand(time(NULL));
  // On va modifier une population->grille_de_personnes tampon pour ne pas
  // modifier la population->grille_de_personnes originale en cours de
  // traitement.
  struct Personne ***grille_tampon = clonerGrillePopulation(population);
  double nb_aleatoire;
  int voisin = 0;  // compteur de voisins.

  // Pour chaque case
  for (long unsigned i = 0; i < cote; i++) {
    for (long unsigned j = 0; j < cote; j++) {
      switch (population->grille_de_personnes[i][j]->state) {
        case SAIN:
          voisin = 0;

          if (j > 0)
            voisin +=
                (population->grille_de_personnes[i][j - 1]->state == MALADE);
          if (j < cote - 1)
            voisin +=
                (population->grille_de_personnes[i][j + 1]->state == MALADE);
          if (i > 0)
            voisin +=
                (population->grille_de_personnes[i - 1][j]->state == MALADE);
          if (i < cote - 1)
            voisin +=
                (population->grille_de_personnes[i + 1][j]->state == MALADE);
          // on applique la probabilité que l'individu tombe malade pour chaque
          // voisin.
          while (voisin > 0 && grille_tampon[i][j]->state != MALADE) {
            nb_aleatoire = (double)rand() / RAND_MAX;
            if (nb_aleatoire < lambda) grille_tampon[i][j]->state = MALADE;
            voisin--;
          }
          break;

        case MALADE:
          // S'il est MALADE, soit IMMUNISE, soit MORT, soit MALADE
          nb_aleatoire = (double)rand() / RAND_MAX;
          if (nb_aleatoire < beta) grille_tampon[i][j]->state = MORT;
          nb_aleatoire = (double)rand() / RAND_MAX;
          if (nb_aleatoire < gamma) grille_tampon[i][j]->state = IMMUNISE;
          break;

        default:
          break;
      }
    }
  }
  population->grille_de_personnes = grille_tampon;
  // NOTE TO MYSELF : Les pointers envoyés en argument sont LOCALES.
  // Les ptr->data sont addressé donc changeable.
}
