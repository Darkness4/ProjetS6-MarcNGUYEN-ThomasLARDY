#if !defined(POPULATION_H)
#define POPULATION_H

enum State{SAIN, MALADE, MORT, IMMUNISE};

struct Personne
{
    enum State state;
};


#endif // POPULATION_H

