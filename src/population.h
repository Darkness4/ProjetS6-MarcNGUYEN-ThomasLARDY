#if !defined(POPULATION_H)
#define POPULATION_H

/**
 * @brief Etats pouvant être une Personne.
 */
enum State { SAIN, MALADE, MORT, IMMUNISE, INCUBE };

/**
 * @brief Structure Personne, contenant les propriétés de celle-ci.
 */
struct Personne {
  /**
   * @brief Etat de la Personne et temps d'incubation.
   */
  enum State state;
  int temps_incube;
};

/**
 * @brief Structure Population.
 */
struct Population {
  /**
   * @brief Tableau cote*cote contenant une struct Personne*.
   */
  struct Personne ***grille_de_personnes;
  /**
   * @brief Longueur d'un côté de la grille.
   */
  unsigned long cote;
};

struct Population *creerPopulation(const unsigned long cote);
struct Personne ***clonerGrillePopulation(struct Population *population_source);
void afficherGrillePopulation(struct Population *population);

#endif  // POPULATION_H
