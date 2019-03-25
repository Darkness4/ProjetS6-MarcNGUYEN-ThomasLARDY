# Algorithmique et Programmation II : Graphes et calcul distribué

Par Marc NGUYEN.

- [Algorithmique et Programmation II : Graphes et calcul distribué](#algorithmique-et-programmation-ii--graphes-et-calcul-distribué)
  - [Enoncé](#enoncé)
  - [Build](#build)
  - [Usage](#usage)
    - [Linux](#linux)
    - [Output](#output)
  - [Paramétrage](#paramétrage)
  - [Proposition de réponse aux questions](#proposition-de-réponse-aux-questions)
    - [Partie I](#partie-i)
  - [Partie II](#partie-ii)
  - [Résultats des tests](#résultats-des-tests)
    - [graph_6_7_without_negative_cycle.txt](#graph_6_7_without_negative_cycletxt)
    - [graph_6_7.txt](#graph_6_7txt)
    - [graph_super_negative_2_loops_butterfly.txt](#graph_super_negative_2_loops_butterflytxt)

## Enoncé

Voir [./doc/2019_algo_prog_seance_4.pdf](./doc/2019_algo_prog_seance_4.pdf).

## Build

```bash
cd AlgoProg5
make -j4
```

## Usage

### Linux

Executer le fichier binaire dans le dossier bin.
Un fichier "graph_6_7_without_negative_cycle.txt" doit exiter afin de pouvoir lancer le programme sans spécifier d'arguments.

Par default :

```bash
nom_du_fichier_txt="graph_6_7_without_negative_cycle.txt"
source="1"
destination="2"
disable_negation=unset
```

Executez :

```bash
cd bin
./AlgoProg5 [nom_du_fichier_txt] [source] [destination] [disable_negation]
```

disable_negation est activé si un 4e argument existe.

Exemple :

```bash
cd bin
./AlgoProg5 graph_6_7_without_negative_cycle.txt 1 2 blabla
```

### Output

La sortie se fait sur STDOUT.

```bash
> AlgoProg5 graph_6_7_without_negative_cycle.txt 1 6 disabled
# graph_6_7_without_negative_cycle.txt
Phase 1
3 <- 1: 4		1 is now waiting.
2 <- 1: 3		1 is now waiting.
4 <- 3: 10		3 is now waiting.
4 <- 2: 5		2 is now waiting.
6 <- 4: 12		4 is now waiting.
5 <- 4: 11		4 is now waiting.
6 <- 4: 7		4 is now waiting.
5 <- 4: 6		4 is now waiting.
2 <- 5: 15		5 is now waiting.
2 <- 5: 10		5 is now waiting.
d[6][1] = 7
Path: 6 <- 4 <- 2 <- 1
```

## Paramétrage

Suivre [./doc/graph_n_m_specification_format.txt](./doc/graph_n_m_specification_format.txt)

## Proposition de réponse aux questions

### Partie I

```bash
> AlgoProg5 graph_6_7_without_negative_cycle.txt 1 6 disabled
# graph_6_7_without_negative_cycle.txt
Phase 1
3 <- 1: 4		1 is now waiting.
2 <- 1: 3		1 is now waiting.
4 <- 3: 10		3 is now waiting.
4 <- 2: 5		2 is now waiting.
6 <- 4: 12		4 is now waiting.
5 <- 4: 11		4 is now waiting.
6 <- 4: 7		4 is now waiting.
5 <- 4: 6		4 is now waiting.
2 <- 5: 15		5 is now waiting.
2 <- 5: 10		5 is now waiting.
d[6][1] = 7
Path: 6 <- 4 <- 2 <- 1
```

## Partie II

L'algorithme présente un problème.
L47 : Le send over? fait tourner à l'infini le programme.
Ayant fait des recherches, je suis tombé sur :

> Distributed Computation on Graphs: Shortest Path Algorithms
>
> K. M. Chandy and J. Misra
>
> University of Texas at Austin

Voici l'instruction originale (*p. 835*):

```txt
> Upon receiving an over ? message
>
> if d != -inf then send over? to all successors who have not been sent such a message.
```

Il manque une information importante dans l'énoncé.

Pour résoudre ce problème, j'ai rajoutté un tableau enregistrant tout les noeud ayant reçu over?.

```C
  char *has_over_q_received = (char *)malloc(G->nb_sommets * sizeof(char));
```

Et j'utilise cette fonction pour obtenir si un noeud particulier a reçu over? :

```C
char check_over(struct DataContext *DC, int destinataire)
{
  if (DC->has_over_q_received[destinataire])
    return 1;
  struct Message *message = DC->liste_messages->HEAD;
  while (message != NULL)
  {
    if (message->type == OVER_QUESTION && message->destinataire == destinataire)
      return 1;
    message = message->suivant;
  }
  return 0;
}
```

Ensuite, il y a une erreur avec les send over- L44 et L36, il manque un "d_t(s) = -inf".
Trois raisons me poussent à penser qu'il s'agit d'une erreur:

- Sans ce morceau de code, mon programme tourne en boucle.
- L'énoncé dit que over- sert à informer que tous les sommets atteignables à partir du sommet t sont à une distance -inf.
- Le document original dit :

```txt
Upon receiving a phase II message (over- or over?)

if d != -inf then
  begin d := -inf;
    send over- to all successors
  end.
```

Pour finir, comme dans le document, la phase 1 doit se terminer.
**J'ai créé une variable is_phase2 qui permettra de terminer la phase 1.**

## Résultats des tests

### graph_6_7_without_negative_cycle.txt

```bash
> AlgoProg5 graph_6_7_without_negative_cycle.txt 1 6 disabled
# graph_6_7_without_negative_cycle.txt
Phase 1
3 <- 1: 4		1 is now waiting.
2 <- 1: 3		1 is now waiting.
4 <- 3: 10		3 is now waiting.
4 <- 2: 5		2 is now waiting.
6 <- 4: 12		4 is now waiting.
5 <- 4: 11		4 is now waiting.
6 <- 4: 7		4 is now waiting.
5 <- 4: 6		4 is now waiting.
2 <- 5: 15		5 is now waiting.
2 <- 5: 10		5 is now waiting.
d[6][1] = 7
Path: 6 <- 4 <- 2 <- 1

> AlgoProg5 graph_6_7_without_negative_cycle.txt 1 5 disabled
# graph_6_7_without_negative_cycle.txt
Phase 1
3 <- 1: 4		1 is now waiting.
2 <- 1: 3		1 is now waiting.
4 <- 3: 10		3 is now waiting.
4 <- 2: 5		2 is now waiting.
6 <- 4: 12		4 is now waiting.
5 <- 4: 11		4 is now waiting.
6 <- 4: 7		4 is now waiting.
5 <- 4: 6		4 is now waiting.
2 <- 5: 15		5 is now waiting.
2 <- 5: 10		5 is now waiting.
d[5][1] = 6
Path: 5 <- 4 <- 2 <- 1

> AlgoProg5 graph_6_7_without_negative_cycle.txt 1 6
# graph_6_7_without_negative_cycle.txt
Phase 1
3 <- 1: 4		1 is now waiting.
2 <- 1: 3		1 is now waiting.
4 <- 3: 10		3 is now waiting.
4 <- 2: 5		2 is now waiting.
6 <- 4: 12		4 is now waiting.
5 <- 4: 11		4 is now waiting.
3 <- 4: ACK		3 is now waiting for 0 answers.
6 <- 4: 7		4 is now waiting.
5 <- 4: 6		4 is now waiting.
4 <- 6: ACK		4 is now waiting for 3 answers.
2 <- 5: 15		5 is now waiting.
1 <- 3: ACK		1 is now waiting for 1 answers.
4 <- 6: ACK		4 is now waiting for 2 answers.
4 <- 5: ACK		4 is now waiting for 1 answers.
2 <- 5: 10		5 is now waiting.
5 <- 2: ACK		5 is now waiting for 1 answers.
5 <- 2: ACK		5 is now waiting for 0 answers.
4 <- 5: ACK		4 is now waiting for 0 answers.
2 <- 4: ACK		2 is now waiting for 0 answers.
1 <- 2: ACK		1 is now waiting for 0 answers.
Phase 2 : No more ack message remaining for P1
3 <- 1: OVER?
2 <- 1: OVER?
4 <- 3: OVER?
6 <- 4: OVER?
5 <- 4: OVER?
2 <- 5: OVER?
d[6][1] = 7
Path: 6 <- 4 <- 2 <- 1

> AlgoProg5 graph_6_7_without_negative_cycle.txt 1 5
# graph_6_7_without_negative_cycle.txt
Phase 1
3 <- 1: 4		1 is now waiting.
2 <- 1: 3		1 is now waiting.
4 <- 3: 10		3 is now waiting.
4 <- 2: 5		2 is now waiting.
6 <- 4: 12		4 is now waiting.
5 <- 4: 11		4 is now waiting.
3 <- 4: ACK		3 is now waiting for 0 answers.
6 <- 4: 7		4 is now waiting.
5 <- 4: 6		4 is now waiting.
4 <- 6: ACK		4 is now waiting for 3 answers.
2 <- 5: 15		5 is now waiting.
1 <- 3: ACK		1 is now waiting for 1 answers.
4 <- 6: ACK		4 is now waiting for 2 answers.
4 <- 5: ACK		4 is now waiting for 1 answers.
2 <- 5: 10		5 is now waiting.
5 <- 2: ACK		5 is now waiting for 1 answers.
5 <- 2: ACK		5 is now waiting for 0 answers.
4 <- 5: ACK		4 is now waiting for 0 answers.
2 <- 4: ACK		2 is now waiting for 0 answers.
1 <- 2: ACK		1 is now waiting for 0 answers.
Phase 2 : No more ack message remaining for P1
3 <- 1: OVER?
2 <- 1: OVER?
4 <- 3: OVER?
6 <- 4: OVER?
5 <- 4: OVER?
2 <- 5: OVER?
d[5][1] = 6
Path: 5 <- 4 <- 2 <- 1

```

**Conclusion : Le programme est robuste face à un graphe orienté sans cycle négatif.**

### graph_6_7.txt

```sh
> AlgoProg5 graph_6_7.txt 1 2
# graph_6_7.txt
Phase 1
3 <- 1: 4		1 is now waiting.
2 <- 1: 3		1 is now waiting.
4 <- 3: 10		3 is now waiting.
4 <- 2: 5		2 is now waiting.
6 <- 4: 12		4 is now waiting.
5 <- 4: 11		4 is now waiting.
3 <- 4: ACK		3 is now waiting for 0 answers.
6 <- 4: 7		4 is now waiting.
5 <- 4: 6		4 is now waiting.
4 <- 6: ACK		4 is now waiting for 3 answers.
2 <- 5: 7		5 is now waiting.
1 <- 3: ACK		1 is now waiting for 1 answers.
4 <- 6: ACK		4 is now waiting for 2 answers.
4 <- 5: ACK		4 is now waiting for 1 answers.
2 <- 5: 2		5 is now waiting.
5 <- 2: ACK		5 is now waiting for 1 answers.
1 <- 2: ACK		1 is now waiting for 0 answers.
Phase 2 : No more ack message remaining for P1
3 <- 1: OVER?
2 <- 1: OVER?
4 <- 3: OVER?
4 <- 2: OVER-
6 <- 4: OVER-
5 <- 4: OVER-
2 <- 5: OVER-
d[2][1] = -9223372036854775808
Path: 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5
 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4
 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2
 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5
 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4
 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2
 <- 5 <- 4 <- 2

> AlgoProg5 graph_6_7.txt 1 3
# graph_6_7.txt
Phase 1
3 <- 1: 4		1 is now waiting.
2 <- 1: 3		1 is now waiting.
4 <- 3: 10		3 is now waiting.
4 <- 2: 5		2 is now waiting.
6 <- 4: 12		4 is now waiting.
5 <- 4: 11		4 is now waiting.
3 <- 4: ACK		3 is now waiting for 0 answers.
6 <- 4: 7		4 is now waiting.
5 <- 4: 6		4 is now waiting.
4 <- 6: ACK		4 is now waiting for 3 answers.
2 <- 5: 7		5 is now waiting.
1 <- 3: ACK		1 is now waiting for 1 answers.
4 <- 6: ACK		4 is now waiting for 2 answers.
4 <- 5: ACK		4 is now waiting for 1 answers.
2 <- 5: 2		5 is now waiting.
5 <- 2: ACK		5 is now waiting for 1 answers.
1 <- 2: ACK		1 is now waiting for 0 answers.
Phase 2 : No more ack message remaining for P1
3 <- 1: OVER?
2 <- 1: OVER?
4 <- 3: OVER?
4 <- 2: OVER-
6 <- 4: OVER-
5 <- 4: OVER-
2 <- 5: OVER-
d[3][1] = 4
Path: 3 <- 1

> AlgoProg5 graph_6_7.txt 1 4
# graph_6_7.txt
Phase 1
3 <- 1: 4		1 is now waiting.
2 <- 1: 3		1 is now waiting.
4 <- 3: 10		3 is now waiting.
4 <- 2: 5		2 is now waiting.
6 <- 4: 12		4 is now waiting.
5 <- 4: 11		4 is now waiting.
3 <- 4: ACK		3 is now waiting for 0 answers.
6 <- 4: 7		4 is now waiting.
5 <- 4: 6		4 is now waiting.
4 <- 6: ACK		4 is now waiting for 3 answers.
2 <- 5: 7		5 is now waiting.
1 <- 3: ACK		1 is now waiting for 1 answers.
4 <- 6: ACK		4 is now waiting for 2 answers.
4 <- 5: ACK		4 is now waiting for 1 answers.
2 <- 5: 2		5 is now waiting.
5 <- 2: ACK		5 is now waiting for 1 answers.
1 <- 2: ACK		1 is now waiting for 0 answers.
Phase 2 : No more ack message remaining for P1
3 <- 1: OVER?
2 <- 1: OVER?
4 <- 3: OVER?
4 <- 2: OVER-
6 <- 4: OVER-
5 <- 4: OVER-
2 <- 5: OVER-
d[4][1] = -9223372036854775808
Path: 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2
 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5
 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4
 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2
 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5
 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4
 <- 2 <- 5 <- 4

> AlgoProg5 graph_6_7.txt 1 5
# graph_6_7.txt
Phase 1
3 <- 1: 4		1 is now waiting.
2 <- 1: 3		1 is now waiting.
4 <- 3: 10		3 is now waiting.
4 <- 2: 5		2 is now waiting.
6 <- 4: 12		4 is now waiting.
5 <- 4: 11		4 is now waiting.
3 <- 4: ACK		3 is now waiting for 0 answers.
6 <- 4: 7		4 is now waiting.
5 <- 4: 6		4 is now waiting.
4 <- 6: ACK		4 is now waiting for 3 answers.
2 <- 5: 7		5 is now waiting.
1 <- 3: ACK		1 is now waiting for 1 answers.
4 <- 6: ACK		4 is now waiting for 2 answers.
4 <- 5: ACK		4 is now waiting for 1 answers.
2 <- 5: 2		5 is now waiting.
5 <- 2: ACK		5 is now waiting for 1 answers.
1 <- 2: ACK		1 is now waiting for 0 answers.
Phase 2 : No more ack message remaining for P1
3 <- 1: OVER?
2 <- 1: OVER?
4 <- 3: OVER?
4 <- 2: OVER-
6 <- 4: OVER-
5 <- 4: OVER-
2 <- 5: OVER-
d[5][1] = -9223372036854775808
Path: 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4
 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2
 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5
 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4
 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2
 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5
 <- 4 <- 2 <- 5

> AlgoProg5 graph_6_7.txt 1 6
# graph_6_7.txt
Phase 1
3 <- 1: 4		1 is now waiting.
2 <- 1: 3		1 is now waiting.
4 <- 3: 10		3 is now waiting.
4 <- 2: 5		2 is now waiting.
6 <- 4: 12		4 is now waiting.
5 <- 4: 11		4 is now waiting.
3 <- 4: ACK		3 is now waiting for 0 answers.
6 <- 4: 7		4 is now waiting.
5 <- 4: 6		4 is now waiting.
4 <- 6: ACK		4 is now waiting for 3 answers.
2 <- 5: 7		5 is now waiting.
1 <- 3: ACK		1 is now waiting for 1 answers.
4 <- 6: ACK		4 is now waiting for 2 answers.
4 <- 5: ACK		4 is now waiting for 1 answers.
2 <- 5: 2		5 is now waiting.
5 <- 2: ACK		5 is now waiting for 1 answers.
1 <- 2: ACK		1 is now waiting for 0 answers.
Phase 2 : No more ack message remaining for P1
3 <- 1: OVER?
2 <- 1: OVER?
4 <- 3: OVER?
4 <- 2: OVER-
6 <- 4: OVER-
5 <- 4: OVER-
2 <- 5: OVER-
d[6][1] = -9223372036854775808
Path: 6 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4
 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2
 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5
 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4
 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2
 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5 <- 4 <- 2 <- 5
 <- 4 <- 2 <- 5

```

**Conclusion : L'algorithme détecte les cycles négatifs mais ne peut pas les ignorer.**

### graph_super_negative_2_loops_butterfly.txt

![Graphe Butterfly](./doc/graph_super_negative_2_loops_butterfly.png)

```
> AlgoProg5 graph_super_negative_2_loops_butterfly.txt 1 3
# graph_super_negative_2_loops_butterfly.txt
Phase 1
2 <- 1: 1		1 is now waiting.
7 <- 2: 0		2 is now waiting.
4 <- 2: 0		2 is now waiting.
3 <- 2: 2		2 is now waiting.
9 <- 7: 1		7 is now waiting.
8 <- 7: -1		7 is now waiting.
6 <- 4: 1		4 is now waiting.
5 <- 4: -1		4 is now waiting.
2 <- 3: ACK		2 is now waiting for 2 answers.
11 <- 9: 2		9 is now waiting.
2 <- 8: -2		8 is now waiting.
10 <- 6: 2		6 is now waiting.
2 <- 5: -2		5 is now waiting.
9 <- 11: ACK		9 is now waiting for 0 answers.
1 <- 2: ACK		1 is now waiting for 0 answers.
Phase 2 : No more ack message remaining for P1
2 <- 1: OVER?
7 <- 2: OVER-
4 <- 2: OVER-
3 <- 2: OVER-
9 <- 7: OVER-
8 <- 7: OVER-
6 <- 4: OVER-
5 <- 4: OVER-
11 <- 9: OVER-
2 <- 8: OVER-
10 <- 6: OVER-
2 <- 5: OVER-
d[3][1] = -9223372036854775808
Path: 3 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2
 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8
 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7
 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2
 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8
 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7
 <- 2 <- 8 <- 7

> AlgoProg5 graph_super_negative_2_loops_butterfly.txt 4 2
# graph_super_negative_2_loops_butterfly.txt
Phase 1
6 <- 4: 1		4 is now waiting.
5 <- 4: -1		4 is now waiting.
10 <- 6: 2		6 is now waiting.
2 <- 5: -2		5 is now waiting.
6 <- 10: ACK		6 is now waiting for 0 answers.
7 <- 2: -3		2 is now waiting.
4 <- 2: -3		2 is now waiting.
Phase 2 : P1 is in a negative cycle
6 <- 4: OVER-
5 <- 4: OVER-
10 <- 6: OVER-
2 <- 5: OVER-
7 <- 2: OVER-
4 <- 2: OVER-
3 <- 2: OVER-
9 <- 7: OVER-
8 <- 7: OVER-
6 <- 4: OVER-
5 <- 4: OVER-
11 <- 9: OVER-
2 <- 8: OVER-
d[2][4] = -9223372036854775808
Path: 2 <- 5 <- 4

> AlgoProg5 graph_super_negative_2_loops_butterfly.txt 2 10
# graph_super_negative_2_loops_butterfly.txt
Phase 1
7 <- 2: -1		2 is now waiting.
4 <- 2: -1		2 is now waiting.
3 <- 2: 1		2 is now waiting.
9 <- 7: 0		7 is now waiting.
8 <- 7: -2		7 is now waiting.
6 <- 4: 0		4 is now waiting.
5 <- 4: -2		4 is now waiting.
2 <- 3: ACK		2 is now waiting for 2 answers.
11 <- 9: 1		9 is now waiting.
2 <- 8: -3		8 is now waiting.
Phase 2 : P1 is in a negative cycle
7 <- 2: OVER-
4 <- 2: OVER-
3 <- 2: OVER-
9 <- 7: OVER-
8 <- 7: OVER-
6 <- 4: OVER-
5 <- 4: OVER-
11 <- 9: OVER-
2 <- 8: OVER-
10 <- 6: OVER-
2 <- 5: OVER-
7 <- 2: OVER-
4 <- 2: OVER-
3 <- 2: OVER-
d[10][2] = -9223372036854775808
Path: 10

> AlgoProg5 graph_super_negative_2_loops_butterfly.txt 7 4
# graph_super_negative_2_loops_butterfly.txt
Phase 1
9 <- 7: 1		7 is now waiting.
8 <- 7: -1		7 is now waiting.
11 <- 9: 2		9 is now waiting.
2 <- 8: -2		8 is now waiting.
9 <- 11: ACK		9 is now waiting for 0 answers.
7 <- 2: -3		2 is now waiting.
Phase 2 : P1 is in a negative cycle
9 <- 7: OVER-
8 <- 7: OVER-
11 <- 9: OVER-
2 <- 8: OVER-
7 <- 2: OVER-
4 <- 2: OVER-
3 <- 2: OVER-
9 <- 7: OVER-
8 <- 7: OVER-
6 <- 4: OVER-
5 <- 4: OVER-
10 <- 6: OVER-
2 <- 5: OVER-
d[4][7] = -9223372036854775808
Path: 4

> AlgoProg5 graph_super_negative_2_loops_butterfly.txt 1 11
# graph_super_negative_2_loops_butterfly.txt
Phase 1
2 <- 1: 1		1 is now waiting.
7 <- 2: 0		2 is now waiting.
4 <- 2: 0		2 is now waiting.
3 <- 2: 2		2 is now waiting.
9 <- 7: 1		7 is now waiting.
8 <- 7: -1		7 is now waiting.
6 <- 4: 1		4 is now waiting.
5 <- 4: -1		4 is now waiting.
2 <- 3: ACK		2 is now waiting for 2 answers.
11 <- 9: 2		9 is now waiting.
2 <- 8: -2		8 is now waiting.
10 <- 6: 2		6 is now waiting.
2 <- 5: -2		5 is now waiting.
9 <- 11: ACK		9 is now waiting for 0 answers.
1 <- 2: ACK		1 is now waiting for 0 answers.
Phase 2 : No more ack message remaining for P1
2 <- 1: OVER?
7 <- 2: OVER-
4 <- 2: OVER-
3 <- 2: OVER-
9 <- 7: OVER-
8 <- 7: OVER-
6 <- 4: OVER-
5 <- 4: OVER-
11 <- 9: OVER-
2 <- 8: OVER-
10 <- 6: OVER-
2 <- 5: OVER-
d[11][1] = -9223372036854775808
Path: 11 <- 9 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8
 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7
 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2
 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8
 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7
 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2 <- 8 <- 7 <- 2
 <- 8 <- 7 <- 2

```
