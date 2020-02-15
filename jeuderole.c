#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

void punchHero (joueur* joueur, joueur* ennemi){
  printf("Vous décrochez une droite à votre adversaire ! \n");
  if ((*joueur).pv>5) {
    (*ennemi).pv = (*ennemi).pv-5;
  } else{
    printf("Vous vous sentez faible, votre tête vacille\n");
  }
  }

void drug1 (joueur* joueur){
  printf("Vous utilisez le pic à glace pour percer le sachet d'hosmozine...\n
  Vous sentez la drogue faire effet dans votre corps\n");
  bool isDrogued=true;
  (*joueur).incDrogue = (*joueur).incDrogue -15;
  (*joueur).pv = (*joueur).pv+5;
  (*joueur).att = (*joueur).att + 3;
  (*joueur).def = (*joueur).def + 3;
  (*joueur).force = (*joueur).force+1;
  (*joueur).agilite = (*joueur).agilite+1;
  (*joueur).intelligence = (*joueur).intelligence+1;
}

void drug2 (joueur* joueur){
  printf("Vous utilisez le pic à glace pour percer le sachet d'hosmozine...\n
  Vous sentez la drogue faire effet dans votre corps\n");
  bool isDrogued=true;
  (*joueur).incDrogue = (*joueur).incDrogue -20;
  (*joueur).pv = (*joueur).pv+10;
  (*joueur).att = (*joueur).att + 5;
  (*joueur).def = (*joueur).def + 5;
  (*joueur).force = (*joueur).force+2;
  (*joueur).agilite = (*joueur).agilite+2;
  (*joueur).intelligence = (*joueur).intelligence+2;
}

void drug3 (joueur* joueur){
  printf("Vous utilisez le pic à glace pour percer le sachet d'hosmozine...\n
  Vous sentez la drogue faire effet dans votre corps\n");
  bool isDrogued=true;
  (*joueur).incDrogue = (*joueur).incDrogue -30;
  (*joueur).pv = (*joueur).pvMax;
  (*joueur).att = (*joueur).att +8;
  (*joueur).def = (*joueur).def +8;
  (*joueur).force = (*joueur).force+5;
  (*joueur).agilite = (*joueur).agilite+5;
  (*joueur).intelligence = (*joueur).intelligence+5;
}

void sober (joueur* joueur){
  printf("Les effets de la drogue s'estompent...\n");
  bool isDrogued=false;
    while (isDrogued==false) {
      (*joueur).incDrogue= (*joueur).incDrogue+5;

    };
  (*joueur).att = (*joueur).att -10;
  (*joueur).def = (*joueur).def -10;
  (*joueur).force = (*joueur).force -5;
  (*joueur).agilite = (*joueur).agilite-5;
  (*joueur).intelligence = (*joueur).intelligence-5;
}


}

int main(){

  return 0;
}
