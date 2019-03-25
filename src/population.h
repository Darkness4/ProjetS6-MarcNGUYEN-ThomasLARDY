#if !defined(POPULATION_H)
#define POPULATION_H

enum State{SAIN, MALADE, MORT, IMMUNISE};

struct Personne
{
    enum State state;
};

struct Population
{
    struct Personne** grille_de_personnes;
    long length;
};

struct Population* creer_population(const long length);

#endif // POPULATION_H

