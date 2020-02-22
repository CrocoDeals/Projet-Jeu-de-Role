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

void looterUnObjet(joueur* heroine, joueur* ennemiMort, item item) {
	ajouterObjet(heroine, item);
	enleverObjet(ennemiMort, item);
}

bool verifierMort(joueur* perso){
	if((*perso).pv <= 0){
		printf("\n%s subit trop de degats et s'effondre\n", (*perso).nom);
		return true;
	} else if((*perso).pv >= 0 && (*perso).nom == "XV-95"){
		color(10,0);
		printf("\n%s : %d PV\n", (*perso).nom, (*perso).pv);
		color(15,0);
		return false;
	} else if((*perso).pv >= 0 && (*perso).nom == "XV-96"){
		color(10,0);
		printf("\n%s : %d PV\n", (*perso).nom, (*perso).pv);
		color(15,0);
		return false;
	} else if((*perso).pv >= 0 && (*perso).nom == "Mule"){
		color(10,0);
		printf("\n%s : %d PV\n", (*perso).nom, (*perso).pv);
		color(15,0);
		return false;
	} else {
		return false;
	}
}

void infligerDegats(joueur* attaquant, joueur* defenseur, int degatSupp){
	int degatActuels = 0;
	degatActuels = (*attaquant).att/(*defenseur).def;
	degatActuels = degatActuels + degatSupp;
	(*defenseur).pv = (*defenseur).pv - degatActuels;
	color (12,0);
	printf("\n%s subit %d points de degats\n", (*defenseur).nom, degatActuels);
	color(15,0);
}

void attaqueGarde(joueur* heros, joueur* garde){
	srand(time(NULL));
	int choixMob = rand()%2+1;
	switch (choixMob) {
			case 1: //attaque
				printf("Le garde vous attaque et vous donne un coup de matraque");
					(*garde).def = 2;
					infligerDegats(&(*garde),&(*heros),0);
				break;
			case 2: //defense
				printf("Le garde prend un coup et place son bouclier devant lui\n");
					(*garde).def = (*garde).def + 2;
				break;
	}
}

void attaqueMule(joueur* heros, joueur* mule){
	srand(time(NULL));
	int choixMob = rand()%4+1;
	int nbCaisses = 3;
	switch (choixMob) {
			case 1: //attaque sautée
				printf("La Mule se jette sur vous et vous frappe de plein fouet.\n");
					infligerDegats(&(*mule),&(*heros),2);
				break;
			case 2: //attaque a distance
					if(nbCaisses > 0){
						printf("La Mule attrape une caisse et la lance sur vous !\n");
						infligerDegats(&(*mule),&(*heros),4);
						nbCaisses -= 1;
					} else {
						printf("La Mule cherche quelque chose a lancer mais ne trouve rien...\n");
					}
				break;
				case 3: //Boost et Heal
					if((*mule).incDrogue > 0){
						printf("La Mule se plante le pic a glace dans son corps !\n");
						printf("La Mule devient plus forte et ses blessures se ferme !\n");
						(*mule).incDrogue = (*mule).incDrogue - 20;
						(*mule).pv += 5;
						(*mule).att += 2;
					} else {
						printf("Les sachets present dans le corps de la Mule sont vide ! Elle se blesse dans l'action\n");
						(*mule).pv -= 5;
					}
					break;
					case 4: //Concentration et Essouflement
						if((*mule).incDrogue > 0){
							printf("La Mule reprend son souffle et prepare son prochain coup !\n");
							(*mule).att += 1;
						} else {
							printf("Ayant beaucoup de drogue dans son corps la Mule prend un moment pour respirer\n");
							(*mule).pv -= 2;
						}
						break;
					}
}

void boost(joueur* heros){
	(*heros).pv += 10;
	(*heros).att += 4;
	(*heros).def += 1;
	(*heros).force += 1;
	(*heros).agilite += 1;
	(*heros).intelligence += 1;
	(*heros).incDrogue -= 10;
}

void ajouterObjet(joueur*, item);
void enleverObjet(joueur*, item);
void looterUnObjet(joueur*, joueur*, item);
bool verifierMort(joueur*);
void infligerDegats(joueur*,joueur*,int);
void attaqueGarde(joueur*, joueur*);
void attaqueMule(joueur*, joueur*);
void boost(joueur*);

int main(){
	color(15,0);
	int choixAction;
  int choixRecup;
	int choixAttaque;
	int choixMob;
	int choixPlan;
	int choixGarde;
	int choixChemin;
	int choixAutel;
	int choixFuite;
	char choixPassword[40];
	joueur garde={"XV-95",30,30,30,10,2,4,2,3,{{"Casque de Garde","Casque de la garde, offre une protection a la tete"},{"Baton","Matraque de garde"}},2,10,false};
	joueur garde2={"XV-96",40,40,30,6,2,4,2,3,{{"Casque de Garde","Casque de la garde, offre une protection a la tete"},{"Baton","Matraque de garde"}},2,10,false};
	joueur heros={"Loyd",50,50,60,5,2,3,3,3,{{"Vetement Dechire","Vetement en lambeaux n'offrant aucune defense"},{"Morceau de Metal","Petit morceau de metal coupant"}},2,10,false};
	joueur muleEnragee={"Mule N8745",150,150,40,10,1,3,3,3,{{"Vetement Dechire","Vetement en lambeaux n'offrant aucune defense"},{"Pic a Glace","Petit morceau de metal coupant"},{"Hosmozine","Sachet de drogue"}},3,10,false};
	lieu chapelle={1, "Chapelle en Ruine", "Chapelle servant de couverture a une operation de trafic de drogue de grande envergure"};
	lieu egout={2, "Egout Obscur", "Egout servant d'entrepot de stockage pour la drogue, sert aussi de lien entre chaque batiment"};
	lieu laboratoire={3, "Laboratoire", "Laboratoire servant d'usine a creation de Mule"};
	password motdepasse ={"hosmozine",3};

		reveil(egout);
		printf("\nVous etes nu et dans le noir, vous ramassez ce que vous trouvez dans la piece et vous vous en equipez\n");
		afficherInventaire(heros);
		/*
		// ACT 1
		do {
		printf("\nVous avancez vers la lumiere et vous vous retrouvez dans une grande piece.\nPlusieurs caisses de stockage se trouvent a droite.\nVous entendez des voix dans le couloir de gauche.\nQue faites-vous ? Se cacher et fouiller les caisses (1)  Ecouter la conversation (2)\n");
		//color(15,0);
			scanf("%d", &choixAction);
			// Premier choix du Joueur
			switch (choixAction) {
				// Se Cacher et Fouiller
				case 1:
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
								ajouterObjet(&heros, blouse);
								color(15,0);
								afficherInventaire(heros);
                heros.def=heros.def+1;
              break;
              //objet non récupéré
              case 2:
                printf("\n");
              break;
            }
            color (15,0);
            printf("\nVous avez fait trop de bruit ! Les gardes qui discutaient non loin vous ont repere !\n");
						printf("Oh toi ! Qu'est ce que tu fais la ?! T'as rien a faire ici retourne dans ta cellule pauvre mule !\n");
						color(3,0);
						printf("\nUn combat est declare entre %s et %s\n", heros.nom, garde.nom);
						color (15,0);
							//Debut combat
								do{
										printf("\nQue voulez vous faire ? Donner un coup de poing (1) Donner un coup de pied (2) Couper avec le bout de metal (3)\n");
										scanf("%d",&choixAttaque);
											switch(choixAttaque){
													case 1: //poing
														printf("\nVous placez une droite !");
															infligerDegats(&heros,&garde,1);
																if(verifierMort(&garde)==true){
																	choixAttaque = 0;
																	break;
																}
															attaqueGarde(&heros,&garde);
																if(verifierMort(&heros)==true){
																	choixAttaque = 0;
																	break;
																}
													  break;
													case 2: //pied
														printf("\nVous jetez votre jambe dans les airs en direction de la tete du garde\n");
														infligerDegats(&heros,&garde,2);
															if(verifierMort(&garde)==true){
																choixAttaque = 0;
																break;
															}
														attaqueGarde(&heros,&garde);
															if(verifierMort(&garde)==true){
																choixAttaque = 0;
																break;
															}
													  break;
													case 3: //metal
														printf("\nVous serrez le bout de metal entre vos doigts et infligez une coupure a %s\n",garde.nom);
														infligerDegats(&heros,&garde,3);
															if(verifierMort(&garde)==true){
																choixAttaque = 0;
																break;
															}
														attaqueGarde(&heros,&garde);
															if(verifierMort(&garde)==true){
																choixAttaque = 0;
																break;
															}
													  break;
												}
									}while(choixAttaque != 0);
									choixAction = -1;
								//Fin combat
								break;
					break;
				// Ecouter la conversation
				case 2:
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
						scanf("%d",&choixGarde);
							switch (choixGarde) {
								//Cas Assomer le garde
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
												ajouterObjet(&heros, barre);
												color(15,0);
												afficherInventaire(heros);
												heros.att=heros.att+1;
												choixGarde=0;
											break;
										//objet non récupéré
										case 2:
								       printf("\n");
								       choixGarde=0;
								      break;
										}
											printf("Vous avez desormais acces a l'ordinateur que le garde utilisait\n\n");
											printf("Il semblerait que l'ordinateur soit verouille par un mot de passe\n\n");
											printf("Entrez un mot de passe.\n");
												scanf("%39s", &choixPassword);
												if(strcmp(choixPassword, motdepasse.nom) == 0){
																			printf("mot de passe correct. acces autorise\n");
																			sleep(2);
																			printf("Vous ouvrez l'explorateur de fichier et commencez a chercher un plan du lieu\n\n");
																			sleep(5);
																			printf("Ca y est ! Vous avez trouve un plan de la zone qui vous indique ou est la sortie\n");
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
																								ajouterObjet(&heros, planEgout);
																								color(15,0);
																								afficherInventaire(heros);
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
																					choixAction=0;
																						break;
																					case 2:
																						printf("Vous memorisez le plan en le structant pendant quelques minutes\n");
																						sleep(3);
																						printf("Vous sortez de la salle et vous vous dirigez vers la sortie\n");
																						sleep(3);
																						printf("Une bifurcation se presente devant vous quel chemin voulez vous prendre? Droite (1)  Gauche (2)\n");
																						scanf("%d",&choixChemin);
																							if (choixChemin==1) {
																								printf("Vous decidez d'aller a droite\n");
																								sleep (5);
																								printf("Vous avez trouve la sortie ! \n");
																							} else if (choixChemin==2){
																								printf("Vous decidez d'aller a gauche\n");
																								sleep (5);
																								printf("Vous avez trouve la sortie ! \n");
																							}
																							choixAction=0;
																						break;
																				}
												}else {
													printf("mot de passe incorect. acces refuse\n");
												}
									break;
									//Cas Fouiller Discretement
								case 2:
										printf("Vous observez les alentours de la salle et regardez ce qu'il peut y avoir au sol ou sur les etageres \n");
										sleep (2);
										printf("Vous trouvez un morceau de papier avec ecrit dessus un mot qui vous parait familier... hosmozine...\n");
										sleep (2);
										printf("Vous avez fait trop de bruit ! Le garde vous a repere !\n");
											//debut combat
												do{
														printf("\nQue voulez vous faire ? Donner un coup de poing (1) Donner un coup de pied (2) Couper avec le bout de metal (3)\n");
														scanf("%d",&choixAttaque);
															switch(choixAttaque){
																	case 1: //poing
																		printf("\nVous placez une droite !");
																			infligerDegats(&heros,&garde2,1);
																				if(verifierMort(&garde2)==true){
																					choixAttaque = 0;
																					break;
																				}
																			attaqueGarde(&heros,&garde2);
																				if(verifierMort(&heros)==true){
																					choixAttaque = 0;
																					break;
																				}
																		break;
																	case 2: //pied
																		printf("\nVous jetez votre jambe dans les airs en direction de la tete du garde\n");
																		infligerDegats(&heros,&garde2,2);
																			if(verifierMort(&garde2)==true){
																				choixAttaque = 0;
																				break;
																			}
																		attaqueGarde(&heros,&garde2);
																			if(verifierMort(&garde2)==true){
																				choixAttaque = 0;
																				break;
																			}
																		break;
																	case 3: //metal
																		printf("\nVous serrez le bout de metal entre vos doigts et infligez une coupure a %s\n",garde2.nom);
																		infligerDegats(&heros,&garde2,3);
																			if(verifierMort(&garde2)==true){
																				choixAttaque = 0;
																				break;
																			}
																		attaqueGarde(&heros,&garde2);
																			if(verifierMort(&garde2)==true){
																				choixAttaque = 0;
																				break;
																			}
																		break;
																}
													}while(choixAttaque != 0);
													choixAction = -1;
													//fin combat
									break;
								}
								choixAction = 0;
					break;
				}
			break;
		}while(choixAction != 0);
		choixAction = -1;
		*/
		//ACT 2
		do {
		printf("\nVous arrivez dans un petite piece.\nDevant vous se trouve une petite echelle menant vers une trappe au plafond.\nVous entendez des bruits derriere la trappe.\nQue faites-vous ?\nSortir discretement par la trappe (1)  Attendre que le bruit s'en aille avant de passer par la trappe (2)\n");
		//color(15,0);
			scanf("%d", &choixAction);
			// Premier choix du Joueur
			switch (choixAction) {
				// Sortir Discretement
				case 1:
            printf("Vous escaladez l echelle  et  poussez la porte froide et lourde de la trappe metallique \n\n");
						sleep(4);
						printf("Vous sentez le vent froid siffler lorsqu il traverse l interstice \n");
						sleep(4);
						printf("vous entendez le bruit d helices qui tranchent l air dans le ciel \n\n");
						sleep(3);
						printf("vous regardez dans l ouverture et etes ebloui par la forte lumiere bleue d un projecteur d helicoptere\n");
						sleep(3);
						printf("vous refermez la trappe \n");
						sleep(1);
						printf("enfin l helicoptere semble etre parti\n");
						sleep (1);
						printf("vous rouvrez la trappe vous vous retrouvez dans la nef d une enorme eglise gothique desafectee\n");
						sleep(4);
						printf("Plusieurs gardes patrouillent dans la nef et pres du choeur\n\nVous vous glissez discretement derriere des grosses caisses de stockage \n");
						sleep(4);
						printf("*je me demande bien ce qu il peut y avoir dans toutes ces caisses*\n");
						sleep(4);
						printf("Vous reperez un laptop ouvert pose sur une des caisses\n\n ");
						sleep(3);
						printf("Il semble afficher un plan\nVous y jetez un oeil.\n\n");
						sleep(4);
						color(1,0);
						printf("Chargement...\n\n");
						sleep(4);
						printf("Vous vous situez dans la %s,\nune %s\n", chapelle.nom, chapelle.description);
						sleep(4);
						color(15,0);
						printf("\n\nVous entendez un bruit derriere vous : quelqu un vous a suivi \n la porte de la trappe s ouvre et un jeune homme habille comme vous, arme d un pic a glace vous fixe avec un regard vitreux\n\n");
						sleep(5);
						printf("Il se jete violemment sur un garde de la salle.\nSans grand succes \n\n");
						sleep(2);
						printf("le garde le maitrise et lui plaque le visage contre le sol \n");
						sleep(5);
						printf("Vous le voyez se debattre... une flaque de liquide noiratre se repand sur le sol\n\n");
						sleep(5);
						printf("Comme pris d une rage et d une rage extreme, il souleve le garde et le lance contre le mur. Le garde s ecrase de tout son poids sur le sol et tombe KO\n\n");
						sleep(4);
						printf("ses yeux changent de couleur...les scleres de ses yeux noircissent il se releve et se tourne vers vous.\n");
						sleep(5);
						printf("-Aah... Toi aussi... Toi aussi...Tu es comme moi tu vas mourir un jouuuuur tu vas mouriiiiir nous allons tous mourir aaaah\n\n");
						sleep (4);
						printf("Vous voyez un drole de tatouage derrierre son oreille...comme un numero\n" );

						//Debut Combat Boss Phase 1
						/*
							//Debut combat
								do{
										printf("\nQue voulez vous faire ?\nDonner un coup de poing (1) Attaquer avec votre arme (2) Planter votre pic a glace dans votre ventre (3)\n");
										scanf("%d",&choixAttaque);
											switch(choixAttaque){
													case 1: //Poing
														printf("\nVous placez une droite puissante !\n");
															infligerDegats(&heros,&muleEnragee,2);
																if(verifierMort(&muleEnragee)==true){
																	choixAttaque = 0;
																	break;
																}
															attaqueMule(&heros,&muleEnragee);
																if(verifierMort(&heros)==true){
																	choixAttaque = 0;
																	break;
																}
													  break;
													case 2: //Arme
														printf("\nVous prenez votre arme a deux mains et frappez la Mule\n");
														infligerDegats(&heros,&muleEnragee,4);
															if(verifierMort(&muleEnragee)==true){
																choixAttaque = 0;
																break;
															}
														attaqueMule(&heros,&muleEnragee);
															if(verifierMort(&heros)==true){
																choixAttaque = 0;
																break;
															}
													  break;
													case 3: //Pic à Glace
														printf("\nVous utilisez le pic a glace sur votre ventre pour percer la poche de drogue\n");
														boost(&heros);
														heros.isDrogued = true;
														attaqueMule(&heros,&muleEnragee);
															if(verifierMort(&muleEnragee)==true){
																choixAttaque = 0;
																break;
															}
													  break;
												}
									}while(choixAttaque != 0);
									choixAction = -1;
							//Fin combat
						*/
						printf("\nLa Mule s'effondre au sol et le silence revient dans la chapelle\n");
						printf("\nLa salle est vide, vous vous approchez de l'autel, sur ce dernier se touve un ordinateur.\n");
						printf("\nQue voulez vous faire ?\nEntrer le Mot de Passe (1) Ouvrir en Guest (2)\n");
						scanf("%d",&choixAutel);
						switch (choixAutel) {
							//Cas Password : Hosmozine
							case 1:
								printf("Vous entrez le mot de passe : Hosmozine\nLa session s'ouvre.\n\n");
								printf("L'ordi s'eteint et une alarme se declenche !\nUne dizaine de gardes entrent dans la piece.\n\n");
								printf("Vous prenez la fuite.");
								color (12,0);
								printf("Vous obtenez l'ordinateur portable []\n\n");
								item ordinateur = {"Ordinateur", "Ordinateur contenant les plans"};
								ajouterObjet(&heros, ordinateur);
								color(15,0);
							 	afficherInventaire(heros);
						 		printf("\n\nVous partez en courant, vous ouvrez la porte arriere de la chapelle et vous vous engouffrez dans une ruelle\n");
										printf("Vous avez desormais acces a l'ordinateur que le garde utilisait\n\n");
										printf("Il semblerait que l'ordinateur soit verouille par un mot de passe\n\n");
										printf("Entrez un mot de passe.\n");
											scanf("%39s", &choixPassword);
												if(strcmp(choixPassword, motdepasse.nom) == 0){
														printf("mot de passe correct. acces autorise\n");
															sleep(2);
															printf("Vous ouvrez l'explorateur de fichier et commencez a chercher un plan du lieu\n\n");
															sleep(5);
															printf("Ca y est ! Vous avez trouve un plan de la zone qui vous indique ou est la sortie\n");
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
																						ajouterObjet(&heros, planEgout);
																						color(15,0);
																						afficherInventaire(heros);
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
																					choixAction=0;
																					break;
																				case 2:
																					printf("Vous memorisez le plan en le structant pendant quelques minutes\n");
																					sleep(3);
																					printf("Vous sortez de la salle et vous vous dirigez vers la sortie\n");
																					sleep(3);
																					printf("Une bifurcation se presente devant vous quel chemin voulez vous prendre? Droite (1)  Gauche (2)\n");
																					scanf("%d",&choixChemin);
																						if (choixChemin==1) {
																							printf("Vous decidez d'aller a droite\n");
																							sleep (5);
																							printf("Vous avez trouve la sortie ! \n");
																						} else if (choixChemin==2){
																							printf("Vous decidez d'aller a gauche\n");
																							sleep (5);
																							printf("Vous avez trouve la sortie ! \n");
																						}
																						choixAction=0;
																					break;
																			}
											}else {
												printf("mot de passe incorect. acces refuse\n");
											}
								break;
								//Cas Fouiller Discretement
							case 2:
									printf("Vous observez les alentours de la salle et regardez ce qu'il peut y avoir au sol ou sur les etageres \n");
									sleep (2);
									printf("Vous trouvez un morceau de papier avec ecrit dessus un mot qui vous parait familier... hosmozine...\n");
									sleep (2);
									printf("Vous avez fait trop de bruit ! Le garde vous a repere !\n");
										//debut combat
											do{
													printf("\nQue voulez vous faire ? Donner un coup de poing (1) Donner un coup de pied (2) Couper avec le bout de metal (3)\n");
													scanf("%d",&choixAttaque);
														switch(choixAttaque){
																case 1: //poing
																	printf("\nVous placez une droite !");
																		infligerDegats(&heros,&garde2,1);
																			if(verifierMort(&garde2)==true){
																				choixAttaque = 0;
																				break;
																			}
																		attaqueGarde(&heros,&garde2);
																			if(verifierMort(&heros)==true){
																				choixAttaque = 0;
																				break;
																			}
																	break;
																case 2: //pied
																	printf("\nVous jetez votre jambe dans les airs en direction de la tete du garde\n");
																	infligerDegats(&heros,&garde2,2);
																		if(verifierMort(&garde2)==true){
																			choixAttaque = 0;
																			break;
																		}
																	attaqueGarde(&heros,&garde2);
																		if(verifierMort(&garde2)==true){
																			choixAttaque = 0;
																			break;
																		}
																	break;
																case 3: //metal
																	printf("\nVous serrez le bout de metal entre vos doigts et infligez une coupure a %s\n",garde2.nom);
																	infligerDegats(&heros,&garde2,3);
																		if(verifierMort(&garde2)==true){
																			choixAttaque = 0;
																			break;
																		}
																	attaqueGarde(&heros,&garde2);
																		if(verifierMort(&garde2)==true){
																			choixAttaque = 0;
																			break;
																		}
																	break;
															}
												}while(choixAttaque != 0);
												choixAction = -1;
												//fin combat
								break;
							}
							choixAction = 0;

						break;
				// Attendre et Sortir
				case 2:
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
						scanf("%d",&choixAutel);
							switch (choixAutel) {
								//Cas Assomer le garde
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
												ajouterObjet(&heros, barre);
												color(15,0);
												afficherInventaire(heros);
												heros.att=heros.att+1;
												choixGarde=0;
											break;
										//objet non récupéré
										case 2:
								       printf("\n");
								       choixGarde=0;
								      break;
										}
											printf("Vous avez desormais acces a l'ordinateur que le garde utilisait\n\n");
											printf("Il semblerait que l'ordinateur soit verouille par un mot de passe\n\n");
											printf("Entrez un mot de passe.\n");
												scanf("%39s", &choixPassword);
												if(strcmp(choixPassword, motdepasse.nom) == 0){
																			printf("mot de passe correct. acces autorise\n");
																			sleep(2);
																			printf("Vous ouvrez l'explorateur de fichier et commencez a chercher un plan du lieu\n\n");
																			sleep(5);
																			printf("Ca y est ! Vous avez trouve un plan de la zone qui vous indique ou est la sortie\n");
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
																								ajouterObjet(&heros, planEgout);
																								color(15,0);
																								afficherInventaire(heros);
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
																					choixAction=0;
																						break;
																					case 2:
																						printf("Vous memorisez le plan en le structant pendant quelques minutes\n");
																						sleep(3);
																						printf("Vous sortez de la salle et vous vous dirigez vers la sortie\n");
																						sleep(3);
																						printf("Une bifurcation se presente devant vous quel chemin voulez vous prendre? Droite (1)  Gauche (2)\n");
																						scanf("%d",&choixChemin);
																							if (choixChemin==1) {
																								printf("Vous decidez d'aller a droite\n");
																								sleep (5);
																								printf("Vous avez trouve la sortie ! \n");
																							} else if (choixChemin==2){
																								printf("Vous decidez d'aller a gauche\n");
																								sleep (5);
																								printf("Vous avez trouve la sortie ! \n");
																							}
																							choixAction=0;
																						break;
																				}
												}else {
													printf("mot de passe incorect. acces refuse\n");
												}
									break;
									//Cas Fouiller Discretement
								case 2:
										printf("Vous observez les alentours de la salle et regardez ce qu'il peut y avoir au sol ou sur les etageres \n");
										sleep (2);
										printf("Vous trouvez un morceau de papier avec ecrit dessus un mot qui vous parait familier... hosmozine...\n");
										sleep (2);
										printf("Vous avez fait trop de bruit ! Le garde vous a repere !\n");
											//debut combat
												do{
														printf("\nQue voulez vous faire ? Donner un coup de poing (1) Donner un coup de pied (2) Couper avec le bout de metal (3)\n");
														scanf("%d",&choixAttaque);
															switch(choixAttaque){
																	case 1: //poing
																		printf("\nVous placez une droite !");
																			infligerDegats(&heros,&garde2,1);
																				if(verifierMort(&garde2)==true){
																					choixAttaque = 0;
																					break;
																				}
																			attaqueGarde(&heros,&garde2);
																				if(verifierMort(&heros)==true){
																					choixAttaque = 0;
																					break;
																				}
																		break;
																	case 2: //pied
																		printf("\nVous jetez votre jambe dans les airs en direction de la tete du garde\n");
																		infligerDegats(&heros,&garde2,2);
																			if(verifierMort(&garde2)==true){
																				choixAttaque = 0;
																				break;
																			}
																		attaqueGarde(&heros,&garde2);
																			if(verifierMort(&garde2)==true){
																				choixAttaque = 0;
																				break;
																			}
																		break;
																	case 3: //metal
																		printf("\nVous serrez le bout de metal entre vos doigts et infligez une coupure a %s\n",garde2.nom);
																		infligerDegats(&heros,&garde2,3);
																			if(verifierMort(&garde2)==true){
																				choixAttaque = 0;
																				break;
																			}
																		attaqueGarde(&heros,&garde2);
																			if(verifierMort(&garde2)==true){
																				choixAttaque = 0;
																				break;
																			}
																		break;
																}
													}while(choixAttaque != 0);
													choixAction = -1;
													//fin combat
									break;
								}
								choixAction = 0;
					break;
				}
			break;
		}while(choixAction != 0);
		choixAction = -1;
  return 0;
}
