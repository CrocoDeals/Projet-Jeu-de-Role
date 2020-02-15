#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define MAX_CAPACITE 10

struct Item{
	char* nom;
	char* description;
	};
typedef struct Item item;

struct Joueur{
	char* nom;
	int pv;
	int pvMax;
	int incDrogue;
	int att;
	int def;
	int force;
	int agilite;
	int intelligence;
	item inventaire[MAX_CAPACITE];
	int tailleInventaire;
	bool isDrogued;
	};
typedef struct Joueur joueur;

struct Lieu{
	int id;
	char* nom;
	char* description;
	};
typedef struct Lieu lieu;

void color(int t,int f){
  HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(H,f*16+t);
}



void reveil(lieu lieuReveil){
	//color(1,15);
	printf("\nVous vous reveillez dans le lieu : %s\n", lieuReveil.nom);
}

void afficherInventaire(joueur joueur) {
	printf("Inventaire de %s \n", joueur.nom);
	for (int i=0; i<joueur.tailleInventaire; i++) {
		printf(" %d. %s >> %s\n", i+1, joueur.inventaire[i].nom, joueur.inventaire[i].description);
	}
}

int main(){
	int choixAction;
	joueur noelie={"Noelie",50,50,60,5,2,3,3,3,{{"Vetement Dechire","Vetement en lambeaux n'offrant aucune defense"},{"Morceau de Metal","Petit morceau de metal coupant"}},2,false};
	lieu chapelle={1, "Chapelle en Ruine", "Chapelle servant de couverture a une operation de trafic de drogue de grande envergure"};
	lieu egout={2, "Egout Obscur", "Egout servant d'entrepot de stockage pour la drogue, sert aussi de lien entre chaque batiment"};
	lieu laboratoire={3, "Laboratoire", "Laboratoire servant d'usine a creation de Mule"};

		reveil(egout);
	printf("\nVous etes nu et dans le noir, vous ramassez ce que vous trouvez dans la piece et vous vous en equipez\n");
		afficherInventaire(noelie);

		do {
		printf("\nVous avancez vers la lumiere et vous vous retrouvez dans une grande piece.\nPlusieurs caisses de stockage se trouve a droite.\nVous entendez des voix dans le couloir de gauche.\nQue faites-vous ? (1) Se cacher et fouiller les caisses  (2) Ecouter la conversation\n");
		//color(15,0);
			scanf("%d", choixAction);
			// Premier choix du Joueur
			switch (choixAction) {
				// Se Cacher et Fouiller
				case 1:
            do{printf("Vous vous accroupissez derrière deux grosses caisses en bois et faites un trou dans le flan de la boite pour extirper son contenu.\n Vous trouvez une combinaison de laborantin.\n");
            int choixRecup;
            printf("Voulez vous ramasser cet objet ? \n (1) Oui (2) Non\n");
            scanf("%d", &choixRecup);
            switch (choixRecup) {
              //objet dans inventaire
              case 1:
              color (0,5);
              printf("Vous obtenez combinaison de laborantin [defense + 1]\n");
              noelie.def=noelie.def+1;
              break;
              //objet non récupéré
              case 2:
              printf("  \n");
              break;}
            printf("Vous avez fait trop de bruit ! Les gardes qui discutaient non loin vous ont repéré !\n");}
            while(choixAction != 0);
            choixAction = -1;
					break;
				// Ecouter la conversation
				case 2:
				do{
				} while (choixAction != 0);
				choixAction = -1;
				default:;
			}
		} while (choixAction != 0);
  return 0;
}
