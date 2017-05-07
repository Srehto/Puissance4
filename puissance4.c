/* declaration de fonctionnalites supplementaires */
#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "puissance4.h"
#include "puissance4_ig.h"
#include "puissance4_ig.c"

/* fonction principale */
int main()
{
  int i;

  /* Déclaration et initialisation du jeu */
  modele_jeu jeu;
  jeu=init_partie(&jeu);


  gtk_widget_show_all(jeu.fenetre);

  /* Fonctions de signals*/

 for(i=0;i<7;i++)
    gtk_signal_connect(GTK_OBJECT(jeu.bouton[i]),"clicked",G_CALLBACK(mettre_pion),(&jeu));

  gtk_signal_connect(GTK_OBJECT(jeu.fenetre),"destroy",G_CALLBACK(gtk_main_quit),NULL);
  gtk_signal_connect(GTK_OBJECT(jeu.quitter),"clicked",G_CALLBACK(gtk_main_quit),NULL);
  gtk_signal_connect(GTK_OBJECT(jeu.recommencer),"clicked",G_CALLBACK(recommencer),(&jeu));


  gtk_main();

	return EXIT_SUCCESS;
}

/* definition des fonctions utilisateur */

