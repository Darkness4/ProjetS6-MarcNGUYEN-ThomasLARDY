#if !defined(POPULATION_H)
#define POPULATION_H

enum State
{
    SAIN,
    MALADE,
    MORT,
    IMMUNISE
};

struct Statistique
{
    unsigned long population_totale;
    unsigned long nb_IMMUNISE;
    unsigned long nb_SAIN;
    unsigned long nb_MORT;
    unsigned long nb_MALADE;
};

struct Personne
{
    enum State state;
};

struct Population
{
    struct Personne ***grille_de_personnes;
    unsigned long cote;
};

struct Population *creerPopulation(const unsigned long cote);
struct Population *clonerPopulation(struct Population *population_source);
struct Statistique getStatistique(struct Population *population);

#endif // POPULATION_H
