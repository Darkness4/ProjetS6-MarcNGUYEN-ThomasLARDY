#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "jouer_un_tour.h"

/**
 * @brief Renvoie true s'il y a encore au moins un zombie dans la population, false dans le cas contraire.
 * 
 * @param population Grille représentant la population.
 * @return char Booléen, si zombies toujours présents.
 */
char presenceZombie(struct Population *population)
{
	int i, j;
	long cote = population->cote;
	for (i = 0; i < cote; i++)
	{
		for (j = 0; j < cote; j++)
		{
			if (population->grille_de_personnes[i][j]->state == MALADE)
				return 1;
		}
	}
	return 0;
}


/**
 * @brief Faire passer la grille du temps t au temps t+1.
 * 
 * @param population Grille au temps t.	
 * @param beta Probabilité d'un individu infecté de mourir.
 * @param gamma Probabilité d'un individu infecté de guérir.
 * @param lambda Probabilité d'un individu sain d'être contaminé par un individu voisin infecté.
 * @return char Retourne si la population est maintenant vide.
 */
char jouerTour(struct Population *population, double beta, double gamma, double lambda)
{
	const long unsigned cote = population->cote;

	srand(time(NULL));
	// On va modifier une grille tampon pour ne pas modifier la grille originale en cours de traitement.
	struct Population *population_tampon = clonerPopulation(population);
	double nb_aleatoire;
	int voisin = 0; // compteur de voisins.

	// Aliases
	struct Personne ***grille = population->grille_de_personnes;
	struct Personne ***grille_tampon = population_tampon->grille_de_personnes;

	// Pour chaque case
	for (long unsigned i = 0; i < cote; i++)
	{
		for (long unsigned j = 0; j < cote; j++)
		{
			switch (grille[i][j]->state)
			{
			case MALADE:
				// S'il est MALADE, soit IMMUNISE, soit MORT, soit MALADE
				nb_aleatoire = (double)rand() / RAND_MAX;
				if (nb_aleatoire < beta)
					grille_tampon[i][j]->state = MORT;
				nb_aleatoire = (double)rand() / RAND_MAX;
				if (nb_aleatoire < gamma)
					grille_tampon[i][j]->state = IMMUNISE;
				break;

			case SAIN:
				// On utilise (condition) * (valeur), algorithmie booléene
				// NOTE : Les valeurs sont quand même récupérés, mais ne sont pas attribuable.
				// (a == a) = 1
				// (a != a) = 0
				voisin += (j > 0) * (grille[i][j - 1]->state == MALADE) +		 // j [1:n]
							(j < cote - 1) * (grille[i][j + 1]->state == MALADE) + // j [0:n-1]
							(i > 0) * (grille[i - 1][j]->state == MALADE) +		 // i [1:n]
							(i < cote - 1) * (grille[i + 1][j]->state == MALADE);  // i [0:n-1]
				//on applique la probabilité que l'individu tombe malade pour chaque voisin.
				while (voisin != 0 && grille_tampon[i][j]->state != MALADE)
				{
					nb_aleatoire = (double)rand() / RAND_MAX;
					if (nb_aleatoire < lambda)
						grille_tampon[i][j]->state = MALADE;
					voisin--;
				}
				break;
			default:
				break;
			}
		}
	}
	free(population);				// Supprime l'original
	population = population_tampon; // On met à jour la grille.
	// S'il n'y a plus de zombie le programme doit arrêter de jouer des tours.
	if (!presenceZombie(population))
		return 1; 
	else
		return 0;
}
