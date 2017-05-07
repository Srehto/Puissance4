
struct int_jeu_s
{
  partie_t modele;
  GtkWidget* bouton[7];
  GtkWidget* recommencer,*quitter;
  GtkWidget* fenetre, *popup;
  GtkWidget* table, *hbox;
  GtkWidget* cases[LIGNES][COLONNES];
  GtkWidget* tour_joueur, *score;
  GtkWidget* pas_de_pion, *pion_rouge, *pion_jaune;
};
typedef struct int_jeu_s modele_jeu;
modele_jeu init_partie(modele_jeu *);
void mettre_pion(GtkWidget *,gpointer data);
void recommencer(GtkWidget *,gpointer data);
void affichage_gtk(modele_jeu);

