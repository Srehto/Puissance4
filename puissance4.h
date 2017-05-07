
#define LIGNES 6
#define COLONNES 7
enum etat_joueur {JOUEUR_NONE=0, J1=1, J2=2};
struct case_s
{
  enum etat_joueur etat_j;
};
typedef struct case_s cases;
enum etat_partie {EN_COURS=0, GAGNE_J1=1, GAGNE_J2=2, NULLE=-1};
struct partie_s
{
  int nbr_partie;
  enum etat_joueur e_tour;
  enum etat_partie e_partie;
  cases plateau[LIGNES][COLONNES];
};
typedef struct partie_s partie_t;


enum etat_joueur get_etat_case(partie_t *,int, int);
enum etat_partie get_etat_partie(partie_t *);
enum etat_joueur tour_du_joueur(partie_t*);
int get_etat_colonne(partie_t*, int);
void partie_jouer(partie_t *,int );
void case_set_etat(partie_t*);
void affichage(partie_t *);
int colonne_choisie(partie_t *);
int test_victoire(partie_t *,int ,int ,enum etat_joueur);

