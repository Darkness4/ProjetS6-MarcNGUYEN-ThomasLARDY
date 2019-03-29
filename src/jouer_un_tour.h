#if !defined(JOUER_UN_TOUR_H)
#define JOUER_UN_TOUR_H

#include "population.h"

char zombiePresent(struct Population *population);
void jouerTour(struct Population *population, double beta, double gamma,
               double lambda);

#endif  // JOUER_UN_TOUR_H
