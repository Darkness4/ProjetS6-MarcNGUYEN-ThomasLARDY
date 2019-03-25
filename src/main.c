#include <stdio.h>

#include "population.h"

/**
 * @brief Execute une recherche de chemin le plus court suivant Chandy-Misra.
 * 
 * 
 * @param argc
 * @param argv
 * @return int exit(0)
 */
int main(int argc, char const *argv[])
{
  long length = 10;
  if (argc > 1) sscanf(argv[1], "%li", &length);

  struct Population* population = creerPopulation(length);

  return 0;
}
