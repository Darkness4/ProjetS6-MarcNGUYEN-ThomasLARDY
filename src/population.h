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
 * @brief Structure contenant les chiffres intéressants.
 */
struct Statistique
{
    /**
     * @brief Population totale, égale à cote*cote.
     */
    unsigned long population_totale;
    /**
     * @brief Nombre de Personne IMMUNISE.
     */
    unsigned long nb_IMMUNISE;
    /**
     * @brief Nombre de Personne SAIN.
     */
    unsigned long nb_SAIN;
    /**
     * @brief Nombre de Personne MORT.
     */
    unsigned long nb_MORT;
    /**
     * @brief Nombre de Personne MALADE.
     */
    unsigned long nb_MALADE;
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
struct Statistique getStatistique(struct Population *population);

#endif // POPULATION_H
