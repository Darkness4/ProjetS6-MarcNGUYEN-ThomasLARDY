#if !defined(POPULATION_H)
#define POPULATION_H

/**
 * @brief Etats pouvant être une Personne.
 */
enum State
{
    SAIN,
    MALADE,
    MORT,
    IMMUNISE
};

/**
 * @brief Structure Personne, contenant les propriétés de celle-ci.
 */
struct Personne
{
    /**
     * @brief Etat de la Personne.
     */
    enum State state;
};

/**
 * @brief Structure Population.
 */
struct Population
{
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
struct Population *clonerPopulation(struct Population *population_source);

#endif // POPULATION_H
