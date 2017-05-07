
modele_jeu init_partie(modele_jeu * jeu)
{
  gtk_init(NULL,NULL);
  int i,j;
  /*Initialisation du modele*/
  for(i=0;i<=LIGNES;i++)
    {
      for(j=0;j<=COLONNES;j++)
	jeu->modele.plateau[i][j].etat_j=JOUEUR_NONE;
    }
  jeu->modele.e_partie=EN_COURS;
  jeu->modele.e_tour=J1;

  /*Initialisation des fenetre*/

  jeu->fenetre=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(jeu->fenetre),"Puissance 4");
  gtk_window_set_default_size(GTK_WINDOW(jeu->fenetre),450,350);
  gtk_window_set_resizable(GTK_WINDOW(jeu->fenetre),FALSE);
  jeu->table=gtk_table_new(LIGNES+1,COLONNES+2,TRUE);

  jeu->bouton[0]=gtk_button_new_with_label("1");
  jeu->bouton[1]=gtk_button_new_with_label("2");
  jeu->bouton[2]=gtk_button_new_with_label("3");
  jeu->bouton[3]=gtk_button_new_with_label("4");
  jeu->bouton[4]=gtk_button_new_with_label("5");
  jeu->bouton[5]=gtk_button_new_with_label("6");
  jeu->bouton[6]=gtk_button_new_with_label("7");

  for(i=0;i<7;i++)
    gtk_table_attach_defaults(GTK_TABLE(jeu->table),jeu->bouton[i],i,i+1,LIGNES,LIGNES+1);


  /* Popup an cas de victoire */
  jeu->popup=gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(jeu->popup),"Recommencer ?");
  gtk_window_set_default_size(GTK_WINDOW(jeu->popup),1000,750);
  gtk_window_set_resizable(GTK_WINDOW(jeu->popup),FALSE);
  jeu->recommencer=gtk_button_new_with_label("RECOMMENCER ?");
  jeu->quitter=gtk_button_new_with_label("QUITTER ?");
	  
  jeu->hbox=gtk_hbox_new(3,10);
  gtk_box_pack_start(GTK_BOX(jeu->hbox),jeu->recommencer,0,0,10);
  gtk_box_pack_end(GTK_BOX(jeu->hbox),jeu->quitter,0,0,10);
  gtk_container_add(GTK_CONTAINER(jeu->popup),GTK_WIDGET(jeu->hbox));


  gtk_window_set_position(GTK_WINDOW(jeu->fenetre),GTK_WIN_POS_CENTER_ALWAYS);
  gtk_window_set_position(GTK_WINDOW(jeu->popup),GTK_WIN_POS_CENTER_ALWAYS);
  gtk_window_set_modal(GTK_WINDOW(jeu->popup),TRUE);


  jeu->tour_joueur=gtk_label_new("COMMENCEZ !");
  jeu->score=gtk_label_new("ROUGE 0 - 0 JAUNE ");
  gtk_table_attach_defaults(GTK_TABLE(jeu->table),jeu->tour_joueur,7,10,0,3);
  gtk_table_attach_defaults(GTK_TABLE(jeu->table),jeu->score,7,10,3,6);
  gtk_container_add(GTK_CONTAINER(jeu->fenetre),GTK_WIDGET(jeu->table));

 for(i=0;i<LIGNES;i++)
    {
      for(j=0;j<COLONNES;j++)
	{
	  jeu->cases[i][j]=gtk_image_new_from_file("./pasdepion.gif");
	  gtk_table_attach_defaults(GTK_TABLE(jeu->table),jeu->cases[i][j],j,j+1,i,i+1);
	}
    }
 

  return *jeu;
}


enum etat_joueur tour_du_joueur(partie_t * partie)
{
  return partie->e_tour;
}
enum etat_joueur get_etat_case(partie_t * partie, int ligne, int colonne)
{
  return partie->plateau[ligne][colonne].etat_j;
}

enum etat_partie get_etat_partie(partie_t * partie)
{
  return partie->e_partie;
}

int get_etat_colonne(partie_t* partie, int colonne) /* retourne ligne libre de la colonne, si la colonne pleine ou n'existe pas, renvoie -1*/
{
  if(colonne<0 || colonne>COLONNES)
    return -1;
  int i;
  for(i=0;i<LIGNES;i++)
    {
      if(get_etat_case(partie,i,colonne)==JOUEUR_NONE)
	{
	  return i;
	}
    }
  return -1;
}

void partie_jouer(partie_t * partie, int colonne)
{
  partie->plateau[get_etat_colonne(partie,colonne)][colonne].etat_j=tour_du_joueur(partie);
}
void affichage(partie_t * partie)
{
  int i,j;
  for(j=LIGNES-1;j>=0;j--)
    {
      for(i=0;i<COLONNES;i++)
	{
	  if(get_etat_case(partie,j,i)==J1)
	    printf(" O ");
	  else if(get_etat_case(partie,j,i)==J2)
	    printf(" X ");
	  else if(get_etat_case(partie,j,i)==JOUEUR_NONE)
	    printf("   ");
	}
      printf("\n");
    }
  printf(" 1  2  3  4  5  6  7\n");
  
}

int test_victoire(partie_t * partie,int ligne, int colonne, enum etat_joueur joueur)
{
  int i,j,cpt_v=0,cpt_h=0;
  /*Test vertical*/
  for(i=0;i<COLONNES;i++)
    {
      cpt_v=0;
      for(j=0;j<LIGNES;j++)
	{
	  if(get_etat_case(partie,j,i)==joueur)
	    cpt_v++;
	  else
	    cpt_v=0;
	  if(cpt_v==4)
	    break;
	}
      if(cpt_v==4)
	break;
    }
  /*Test horizontal*/
  for(i=0;i<LIGNES;i++)
    {
      cpt_h=0;
      for(j=0;j<COLONNES;j++)
	{
	  /* Test horizontal */
	  if(get_etat_case(partie,i,j)==joueur)
	    cpt_h++;
	  else
	    cpt_h=0;
	  if(cpt_h==4)
	    break;
	  /* Tests Diagonaux */
	  if ((get_etat_case(partie,i,j)==joueur &&  get_etat_case(partie,i+1,j+1)==joueur && get_etat_case(partie,i+2,j+2)==joueur && get_etat_case(partie,i+3,j+3)==joueur) || (get_etat_case(partie,i,j)==joueur &&  get_etat_case(partie,i+1,j-1)==joueur && get_etat_case(partie,i+2,j-2)==joueur && get_etat_case(partie,i+3,j-3)==joueur) || (get_etat_case(partie,i,j)==joueur &&  get_etat_case(partie,i-1,j-1)==joueur && get_etat_case(partie,i-2,j-2)==joueur && get_etat_case(partie,i-3,j-3)==joueur) || (get_etat_case(partie,i,j)==joueur &&  get_etat_case(partie,i-1,j+1)==joueur && get_etat_case(partie,i-2,j+2)==joueur && get_etat_case(partie,i-3,j+3)==joueur))
	    {
	      if(joueur==J1)
		{
		  partie->e_partie=GAGNE_J1;
		  printf("JOUEUR 1 GAGNE ! \n");
		  return 1;
		}
	      else if(joueur==J2)
		{
		  partie->e_partie=GAGNE_J2;
		  printf("JOUEUR 2 GAGNE ! \n");
		  return 1;
		}
	    }
	}
      if(cpt_h==4)
	break;
    }
  /* Resultat*/
  if(cpt_v==4 || cpt_h==4)
    {
      if(joueur==J1)
	{
	  partie->e_partie=GAGNE_J1;
	  printf("JOUEUR 1 GAGNE ! \n");
	  return 1;
	}
      else if(joueur==J2)
	{
	  partie->e_partie=GAGNE_J2;
	  printf("JOUEUR 2 GAGNE ! \n");
	  return 1;
	}
    }
}

void recommencer(GtkWidget *reco, gpointer pjeu)
{
  modele_jeu *jeu=pjeu;

  int i,j;
  gtk_widget_hide(jeu->popup); 
  for(i=0;i<LIGNES;i++)
    {
      for(j=0;j<COLONNES;j++)
	{
	  jeu->modele.plateau[i][j].etat_j=JOUEUR_NONE;
	}
    }
  affichage_gtk(*jeu);
}

int colonne_choisie(partie_t * partie)
{
  int colonne;
  printf("choisissez une colonne: ");
  scanf("%d",&colonne);
  while(get_etat_colonne(partie,colonne-1)==-1)
    {
      printf("Colonne %d pleine ou innexistante, choisissez en une autre :",colonne);
      scanf("%d",&colonne);
    }
  return colonne;
}



void mettre_pion(GtkWidget *button, gpointer pjeu)
{
  modele_jeu *jeu=pjeu;
  int i=0;
  while(button!=jeu->bouton[i])
    {
      i++;
      if(i>8) break;
    }
  if(get_etat_colonne(&jeu->modele,i)!=-1)
     {
      partie_jouer(&jeu->modele,i);
      if(test_victoire(&jeu->modele,get_etat_colonne(&jeu->modele,i),i,jeu->modele.e_tour))
	{
	  gtk_widget_show_all(jeu->popup);
	}
      if(jeu->modele.e_tour==J1)
	{
	  jeu->modele.e_tour=J2;
	  gtk_label_set_label(GTK_LABEL(jeu->tour_joueur),"AU TOUR DU JOUEUR JAUNE !");
	}
      else
	{
	  jeu->modele.e_tour=J1;
	  gtk_label_set_label(GTK_LABEL(jeu->tour_joueur),"AU TOUR DU JOUEUR ROUGE !");
	  }
     }
  affichage_gtk(*jeu);

}
void affichage_gtk(modele_jeu jeu)
{
  int i,j;
  for(i=0;i<LIGNES;i++)
    {
      for(j=0;j<COLONNES;j++)
	{
	   if(get_etat_case(&jeu.modele,LIGNES-i-1,j)==JOUEUR_NONE)
	    {
	      gtk_image_set_from_file(GTK_IMAGE(jeu.cases[i][j]),"./pasdepion.gif");
	    }
	  else if(get_etat_case(&jeu.modele,LIGNES-i-1,j)==J1)
	    {
	      gtk_image_set_from_file(GTK_IMAGE(jeu.cases[i][j]),"./pion_rouge.gif");
	    }
	  else if(get_etat_case(&jeu.modele,LIGNES-i-1,j)==J2)
	    {
	      gtk_image_set_from_file(GTK_IMAGE(jeu.cases[i][j]),"./pion_jaune.gif");
	      }
	}
    }
}

