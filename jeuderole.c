#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <unistd.h>

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
	int inventaireMax;
	bool isDrogued;
	};
typedef struct Joueur joueur;

struct Lieu{
	int id;
	char* nom;
	char* description;
	};
typedef struct Lieu lieu;

struct Password{
  char* nom;
  int nbEssais;
};

typedef struct Password password;

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

void ajouterObjet(joueur* joueur, item item) {
	if ((*joueur).tailleInventaire < (*joueur).inventaireMax) {
		(*joueur).inventaire[(*joueur).tailleInventaire] = item;
		(*joueur).tailleInventaire++;
	}
}

void enleverObjet(joueur* joueur, item item) {
	bool removed = false;
		for (int i=0; i<(*joueur).tailleInventaire; i++) {
			if (removed) {
				(*joueur).inventaire[i-1] = (*joueur).inventaire[i];
			} else if ( strcmp((*joueur).inventaire[i].nom, item.nom) == 0 ) {
				removed = true;
			}
		}
		if (removed) {
			(*joueur).tailleInventaire--;
		}
}

int main(){
  color(15,0);
	int choixAction;
  int choixRecup;
	joueur noelie={"Noelie",50,50,60,5,2,3,3,3,{{"Vetement Dechire","Vetement en lambeaux n'offrant aucune defense"},{"Morceau de Metal","Petit morceau de metal coupant"}},2,10,false};
	lieu chapelle={1, "Chapelle en Ruine", "Chapelle servant de couverture a une operation de trafic de drogue de grande envergure"};
	lieu egout={2, "Egout Obscur", "Egout servant d'entrepot de stockage pour la drogue, sert aussi de lien entre chaque batiment"};
	lieu laboratoire={3, "Laboratoire", "Laboratoire servant d'usine a creation de Mule"};
	password motdepasse ={"hosmozine",3};

		reveil(egout);
		printf("\nVous etes nu et dans le noir, vous ramassez ce que vous trouvez dans la piece et vous vous en equipez\n");
		afficherInventaire(noelie);

		do {
		printf("\nVous avancez vers la lumiere et vous vous retrouvez dans une grande piece.\nPlusieurs caisses de stockage se trouvent a droite.\nVous entendez des voix dans le couloir de gauche.\nQue faites-vous ? Se cacher et fouiller les caisses (1)  Ecouter la conversation (2)\n");
		//color(15,0);
			scanf("%d", &choixAction);
			// Premier choix du Joueur
			switch (choixAction) {
				// Se Cacher et Fouiller
				case 1:
            do{
              printf("Vous vous accroupissez derriere une grosse caisse en bois et faites un trou avec votre morceau de metal pour extirper son contenu.\n Vous trouvez une combinaison de laborantin.\n");
            int choixRecup;
            printf("Voulez vous ramasser cet objet ? \n (1) Oui (2) Non\n");
            scanf("%d", &choixRecup);
            switch (choixRecup) {
              //objet dans inventaire
              case 1:
                color (12,0);
                printf("Vous obtenez combinaison de laborantin [defense + 1]\n\n");
								item blouse = {"Combinaison de Laborantin", "Simple Combinaison de Laborantin offrant peu de defense"};
								ajouterObjet(&noelie, blouse);
								color(15,0);
								afficherInventaire(noelie);
                noelie.def=noelie.def+1;
                choixAction=0;
              break;
              //objet non récupéré
              case 2:
                printf("\n");
                choixAction=0;
              break;
            }
            color (15,0);
            printf("\nVous avez fait trop de bruit ! Les gardes qui discutaient non loin vous ont repere !\n");
          }
            while(choixAction != 0);
            choixAction = -1;
					break;
				// Ecouter la conversation
				case 2:
					do{
	          printf("-T'as entendu ca ? Apparament ils vont augmenter le taux de CTH dans l'hosmozine !\nLes mules vont avoir du mal survivre pouahaha\n\n");
	          //sleep (4);
	          printf("-Je trouve pas ca tres drole, ils pourraient etre plus professionels avec les mules,\nc'est pas comme s'ils disposaient des plus grands chirurgiens du monde\n\n");
	          //sleep(4);
	          printf("-Rhoo ca va qu'est ce qu'on s'en fiche de savoir si ces gens meurent ou pas,\ndans tous les cas leurs vies etaient foutues autant qu'ils servent a quelque chose !\n\n");
	          //sleep(4);
	          printf("-Tu me saoules, je vais aller me griller une cigarrette pour plus t'entendre dire des conneries\n\n");
	          //sleep(4);
						printf("-Ca marche moi je retourne en salle info inspecter les cameras de surveillance\n");
	          //sleep(4);
						printf("Tu feras gaffe, la sortie B6 est en maintenance, il n'y a que la sortie E4 qui est accessible depuis ici :\n continue tout droit et tu tournes a la deuxieme a gauche\n\n");
	          //sleep(2);

	          printf("Vous decidez de suivre le garde jusqu'a la sortie mais la porte se referme devant vous,\n vous ne parvenez pas a vous echaper\n\n");
	          printf("Vous retournez sur vos pas et trouvez la salle informatique dont parlait l'autre garde\n Celui ci se trouve assis devant les ecrans de surveillance avec un casque audio sur la tete\n\n");

	          printf("Que voulez vous faire ? Assomer le garde (1) Fouiller discretement la salle (2)\n");
						int choixGarde;
						scanf("%d",&choixGarde);
						switch (choixGarde) {
							case 1:
							printf("Vous ramassez une barre en fer sur le sol et assenez un violent coup sur la tete du garde\n\n celui ci vascille et tombe sur le sol\n\n");
							printf("Voulez vous garder la barre en fer ? \n (1) Oui (2) Non\n");
							scanf("%d", &choixRecup);
											switch (choixRecup) {
												//objet dans inventaire
												case 1:
													color (12,0);
													printf("Vous obtenez barre en fer [attaque + 1]\n\n");
													item barre = {"Barre en fer", "Long tuyau de metal qui peut servir d'arme redoutable"};
													ajouterObjet(&noelie, barre);
													color(15,0);
													afficherInventaire(noelie);
													noelie.att=noelie.att+1;
													choixAction=0;
													break;
												case 2: //objet non récupéré
						                printf("\n");
						                choixAction=0;
						              break;
												}
								printf("Vous avez desormais acces a l'ordinateur que le garde utilisait\n\n");
								printf("Il semblerait que l'ordinateur soit verouille par un mot de passe\n\n");
								printf("Entrez un mot de passe.\n");
								char choixPassword[40];
								int i = 0;
								while(i==0){
								scanf("%39s", &choixPassword);
								if(strcmp(choixPassword, motdepasse.nom) == 0){
								printf("mot de passe correct. acces autorise\n");
								sleep(2);
								printf("Vous ouvrez l'explorateur de fichier et commencez a chercher un plan du lieu\n\n");
								sleep(5);
								printf("Ca y est ! Vous avez trouve un plan de la zone qui vous indique ou est la sortie\n");

								int choixPlan;
								printf("Voulez vous imprimer le plan ? Oui (1)  Non (2)\n");
								scanf("%d",&choixPlan);
								switch (choixPlan) {
									case 1:
									printf("L'imprimante commence son travail...\n");
									sleep (3);
									printf("Voulez vous recuperer le plan ? \n (1) Oui (2) Non\n");
									scanf("%d", &choixRecup);
									switch (choixRecup) {
										//objet dans inventaire
										case 1:
											color (12,0);
											printf("Vous obtenez plan des egouts []\n\n");
											item planEgout = {"Plan des Egouts", "Un plan complexe qui vous indique la direction a suivre"};
											ajouterObjet(&noelie, planEgout);
											color(15,0);
											afficherInventaire(noelie);
											choixAction=0;
										break;
										//objet non récupéré
										case 2:
											printf("\n");
											choixAction=0;
										break;
									}
									printf("Vous vous dirigez maintenant vers la sortie\n");
									sleep (5);
									printf("Vous avez trouve la sortie\n");
									break;
									case 2:
									printf("Vous memorisez le plan en le structant pendant quelques minutes\n");
									sleep(3);
									printf("Vous sortez de la salle et vous vous dirigez vers la sortie\n");
									sleep(3);
									printf("Une bifurcation se presente devant vous quel chemin voulez vous prendre? Droite (1)  Gauche (2)\n");
									int choixChemin;
									scanf("%d",&choixChemin);
									if (choixChemin==1) {
										printf("Vous decidez d'aller a droite\n");
										sleep (5);
										printf("Vous avez trouve la sortie ! \n");
									}
									if (choixChemin==2){
										printf("Vous decidez d'aller a gauche\n");
										sleep (5);
										printf("Vous avez trouve la sortie ! \n");
									}

									break;
								}
								}else {
								printf("mot de passe incorect. acces refuse\n");
								}
							}
								break;
								case 2:
									printf("Vous observez les alentours de la salle et regardez ce qu'il peut y avoir au sol ou sur les etageres \n");
									sleep (2);
									printf("Vous trouvez un morceau de papier avec ecrit dessus un mot qui vous parait familier... hosmozine...\n");
									sleep (2);
									printf("Vous avez fait trop de bruit ! Le garde vous a repere !\n");
									break;
						}

          choixAction=0;
          }
				 while (choixAction != 0);
				choixAction = -1;
				default:;
			}
			break;
		} while (choixAction != 0);
  return 0;
}
