#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stddef.h>


void WAIT(size_t secs) {
	sleep(secs);
}

void PRINT_PROGRESS(size_t count, size_t max) {
	const char prefix[] = "En cours de préparation: [";
	const char suffix[] = "]";
	const size_t prefix_length = sizeof(prefix) - 1;
	const size_t suffix_length = sizeof(suffix) - 1;
	char *buffer = calloc(max + prefix_length + suffix_length + 1, 1); // +1 for \0
	size_t i = 0;

	strcpy(buffer, prefix);
	for (; i < max; ++i)
	{
		buffer[prefix_length + i] = i < count ? '#' : ' ';
	}

	strcpy(&buffer[prefix_length + i], suffix);
	printf("\b%c[2K\r%s\n", 27, buffer);
	fflush(stdout);
	free(buffer);
}

void LAUNCH_PROGRESS_BAR() {
	size_t num_secs = 1, max_secs = 10;
	printf("%s\n", "");
	PRINT_PROGRESS(0, max_secs);
	for (; num_secs <= max_secs; ++num_secs)
	{
		WAIT(1);
		PRINT_PROGRESS(num_secs, max_secs);
	}
}

void AFFICHAGE_BOISSONS() {
	printf("╔══════════════════╦════╦═════╗\n");
	printf("║Boisson           ║Prix║Choix║\n");
	printf("╠══════════════════╬════╬═════╣\n");
	printf("║Café court        ║0.70║  9  ║\n");
	printf("║Café long         ║0.80║  8  ║\n");
	printf("║Café au lait      ║0.60║  7  ║\n");
	printf("║Chocolat          ║0.50║  6  ║\n");
	printf("║Lait              ║0.50║  5  ║\n");
	printf("║Thé au citron     ║0.60║  4  ║\n");
	printf("║Thé à la menthe   ║0.90║  3  ║\n");
	printf("║Thé au gingembre  ║1.20║  2  ║\n");
	printf("║Thé au miel       ║1.40║  1  ║\n");
	printf("║Zlatan tea        ║8.75║  0  ║\n");
	printf("╚══════════════════╩════╩═════╝\n");
}

void ACHAT_BOISSON(double MONNAIE_DISPO[], double PRIX_BOISSONS[], int Choix, double Somme) {
	int demande = 0;
	while (Choix != 10) {
		sleep(2);
		int i = 0;
		int j = 0;
		double renduMonnaie;
		double listNbPiece[10];
		if (demande >= 1) {
			system("clear");
			AFFICHAGE_BOISSONS();
		}
		printf("Quel est votre choix (tapez '10' pour quitter) ?\n");
	    scanf("%d", &Choix);
		if (Choix >= 0 && Choix < 10) {
			printf("Donner votre montant : ");
	        scanf("%lf", &Somme);
	        renduMonnaie = Somme - PRIX_BOISSONS[Choix];
			if (Somme < PRIX_BOISSONS[Choix]) {
				printf("ATTENTION le montant donné est inférieur au prix indiqué !\n");
				exit(-1);
			}
	        printf("La monnaie à rendre est de : %.2lf\n", renduMonnaie);
			while (i < 10) {
				while (renduMonnaie > MONNAIE_DISPO[i] || fabs(renduMonnaie - MONNAIE_DISPO[i]) < 0.001) {
					renduMonnaie = renduMonnaie - MONNAIE_DISPO[i];
					j++;
				}
				if (j > 0) {
					printf("%d x %.2lf\n", j, MONNAIE_DISPO[i]);
				}
				j = 0;
				i++;
			}
			LAUNCH_PROGRESS_BAR();
			demande++;
		    printf("Votre boisson est prête !!!\n");
		} else {
			if (Choix == 10) {
				printf("A BIENTOT POUR DE NOUVEAUX ACHAT CLIENT FIDELE !!!\n");
	            exit(-1);
			} else {
				printf("VEUILLEZ FAIRE UN CHOIX COMPRIS ENTRE 0 ET 9 !!!\n");
			}
		}
	}
}

void ACHAT_BOISSON_2(double MONNAIE_DISPO[], int NB_PIECES_DISPO[], double PRIX_BOISSONS[], int Choix, double Somme) {
	int demande = 0;
	while (Choix != 10) {
		sleep(2);
		int i = 0;
		int j = 0;
		double renduMonnaie;
		int nbRendedMoney[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		if (demande >= 1) {
			system("clear");
			AFFICHAGE_BOISSONS();
		}
		printf("Quel est votre choix (tapez '10' pour quitter) ?\n");
	    scanf("%d", &Choix);
		if (Choix >= 0 && Choix < 10) {
			printf("Donner votre montant : ");
	        scanf("%lf", &Somme);
	        renduMonnaie = Somme - PRIX_BOISSONS[Choix];
			if (Somme < PRIX_BOISSONS[Choix]) {
				printf("ATTENTION le montant donné est inférieur au prix indiqué !\n");
				exit(-1);
			}
	        printf("La monnaie à rendre est de : %.2lf\n", renduMonnaie);
			while (i < 10) {
				while (renduMonnaie > MONNAIE_DISPO[i] || fabs(renduMonnaie - MONNAIE_DISPO[i]) < 0.001) {
					if (NB_PIECES_DISPO[i] > 0) {
					    renduMonnaie = renduMonnaie - MONNAIE_DISPO[i];
					    NB_PIECES_DISPO[i] = NB_PIECES_DISPO[i] - 1;
					    j++;
					} else {
						if (MONNAIE_DISPO[i] > 2.0) {
							printf("ATTENTION : OPERATION INTERROMPUE\n");
						    printf("Le distributeur ne dispose pas assez de billets pour vous rendre la monnaie\n");
						    printf("ATTENTION le distributeur ne délivre plus de billets de %.2lf euros\n", MONNAIE_DISPO[i]);
						} else {
							printf("ATTENTION : OPERATION INTERROMPUE\n");
							printf("Le distributeur ne dispose pas assez de pièces pour vous rendre la monnaie\n");
						    printf("ATTENTION le distributeur ne délivre plus de pièces de %.2lf euros\n", MONNAIE_DISPO[i]);
						}
						renduMonnaie = renduMonnaie - MONNAIE_DISPO[i];
					    j++;
					}
				}
				if (j > 0) {
					if (NB_PIECES_DISPO[i] > 0) {
					    printf("%d x %.2lf\n", j, MONNAIE_DISPO[i]);
					}
				}
				j = 0;
				i++;
			}
			LAUNCH_PROGRESS_BAR();
			demande++;
		    printf("Votre boisson est prête !!!\n");
		} else {
			if (Choix == 10) {
				printf("A BIENTOT POUR DE NOUVEAUX ACHAT CLIENT FIDELE !!!\n");
	            exit(-1);
			} else {
				printf("VEUILLEZ FAIRE UN CHOIX COMPRIS ENTRE 0 ET 9 !!!\n");
			}
		}
	}
}

void ACHAT_BOISSON_3(double MONNAIE_DISPO[], int NB_PIECES_DISPO[], double PRIX_BOISSONS[], int Choix, double Somme) {
	int demande = 0;
	while (Choix != 10) {
		sleep(2);
		int i = 0;
		int j = 0;
		double renduMonnaie;
		double monnaiePrefere;
		int nbRendedMoney[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		if (demande >= 1) {
			system("clear");
			AFFICHAGE_BOISSONS();
		}
		printf("Quel est votre choix (tapez '10' pour quitter) ?\n");
	    scanf("%d", &Choix);
		if (Choix >= 0 && Choix < 10) {
			printf("Quelle est votre pièce ou billet préféré dans la monnaie ? : ");
			scanf("%lf", &monnaiePrefere);
			printf("Donner votre montant : ");
	        scanf("%lf", &Somme);
	        renduMonnaie = Somme - PRIX_BOISSONS[Choix];
			if (Somme < PRIX_BOISSONS[Choix]) {
				printf("ATTENTION le montant donné est inférieur au prix indiqué !\n");
				exit(-1);
			}
	        printf("La monnaie à rendre est de : %.2lf\n", renduMonnaie);
			while (i < 10) {
				while (renduMonnaie > MONNAIE_DISPO[i] || fabs(renduMonnaie - MONNAIE_DISPO[i]) < 0.001) {
					if (NB_PIECES_DISPO[i] > 0) {
					    renduMonnaie = renduMonnaie - MONNAIE_DISPO[i];
					    NB_PIECES_DISPO[i] = NB_PIECES_DISPO[i] - 1;
					    j++;
					} else {
					    if (MONNAIE_DISPO[i] > 2.0) {
							printf("ATTENTION : OPERATION INTERROMPUE\n");
						    printf("Le distributeur ne dispose pas assez de billets pour vous rendre la monnaie\n");
						    printf("ATTENTION le distributeur ne délivre plus de billets de %.2lf euros\n", MONNAIE_DISPO[i]);
						} else {
							printf("ATTENTION : OPERATION INTERROMPUE\n");
							printf("Le distributeur ne dispose pas assez de pièces pour vous rendre la monnaie\n");
						    printf("ATTENTION le distributeur ne délivre plus de pièces de %.2lf euros\n", MONNAIE_DISPO[i]);
						}
                        renduMonnaie = renduMonnaie - MONNAIE_DISPO[i];
					    j++;						
					}
				}
				if (j > 0) {
					if (NB_PIECES_DISPO[i] > 0) {
					    printf("%d x %.2lf\n", j, MONNAIE_DISPO[i]);
					}
				}
				j = 0;
				i++;
			}
			LAUNCH_PROGRESS_BAR();
			demande++;
		    printf("Votre boisson est prête !!!\n");
		} else {
			if (Choix == 10) {
				printf("A BIENTOT POUR DE NOUVEAUX ACHAT CLIENT FIDELE !!!\n");
	            exit(-1);
			} else {
				printf("VEUILLEZ FAIRE UN CHOIX COMPRIS ENTRE 0 ET 9 !!!\n");
			}
		}
	}
}

void REMP_NOMS_BOISSONS(char BOISSONS[][20], int Choix) {
	printf("Votre '%s' est prête !!!\n", BOISSONS[Choix]);
}

void ACHAT_BOISSON_4(double MONNAIE_DISPO[], int NB_PIECES_DISPO[], double PRIX_BOISSONS[], char BOISSONS[][20], int Choix, double Somme) {
	int demande = 0;
	while (Choix != 10) {
		sleep(2);
		int i = 0;
		int j = 0;
		double renduMonnaie;
		double monnaiePrefere;
		int nbRendedMoney[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		if (demande >= 1) {
			system("clear");
			AFFICHAGE_BOISSONS();
		}
		printf("Quel est votre choix (tapez '10' pour quitter) ?\n");
	    scanf("%d", &Choix);
		if (Choix >= 0 && Choix < 10) {
			printf("Quelle est votre pièce ou billet préféré dans la monnaie ? : ");
			scanf("%lf", &monnaiePrefere);
			printf("Donner votre montant : ");
	        scanf("%lf", &Somme);
	        renduMonnaie = Somme - PRIX_BOISSONS[Choix];
			if (Somme < PRIX_BOISSONS[Choix]) {
				printf("ATTENTION le montant donné est inférieur au prix indiqué !\n");
				exit(-1);
			}
	        printf("La monnaie à rendre est de : %.2lf\n", renduMonnaie);
			while (i < 10) {
				while (renduMonnaie > MONNAIE_DISPO[i] || fabs(renduMonnaie - MONNAIE_DISPO[i]) < 0.001) {
					if (NB_PIECES_DISPO[i] > 0) {
					    renduMonnaie = renduMonnaie - MONNAIE_DISPO[i];
					    NB_PIECES_DISPO[i] = NB_PIECES_DISPO[i] - 1;
					    j++;
					} else {
					    if (MONNAIE_DISPO[i] > 2.0) {
							printf("ATTENTION : OPERATION INTERROMPUE\n");
						    printf("Le distributeur ne dispose pas assez de billets pour vous rendre la monnaie\n");
						    printf("ATTENTION le distributeur ne délivre plus de billets de %.2lf euros\n", MONNAIE_DISPO[i]);
						} else {
							printf("ATTENTION : OPERATION INTERROMPUE\n");
							printf("Le distributeur ne dispose pas assez de pièces pour vous rendre la monnaie\n");
						    printf("ATTENTION le distributeur ne délivre plus de pièces de %.2lf euros\n", MONNAIE_DISPO[i]);
						}
                        renduMonnaie = renduMonnaie - MONNAIE_DISPO[i];
					    j++;						
					}
				}
				if (j > 0) {
					if (NB_PIECES_DISPO[i] > 0) {
					    printf("%d x %.2lf\n", j, MONNAIE_DISPO[i]);
					}
				}
				j = 0;
				i++;
			}
			LAUNCH_PROGRESS_BAR();
			demande++;
			REMP_NOMS_BOISSONS(BOISSONS, Choix);
		} else {
			if (Choix == 10) {
				printf("A BIENTOT POUR DE NOUVEAUX ACHAT CLIENT FIDELE !!!\n");
	            exit(-1);
			} else {
				printf("VEUILLEZ FAIRE UN CHOIX COMPRIS ENTRE 0 ET 9 !!!\n");
			}
		}
	}
}


int main(int argc, char** argv) {
    int partieTP;
    double MONNAIE_DISPO[10] = {10.0, 5.0, 2.0, 1.0, .50, .20, .10, .05, .02, .01};
    double PRIX_BOISSONS[10] = {8.75, 1.40, 1.20, .90, .60, .50, .50, .60, .80, .70};
	char BOISSONS[10][20] = {{"Zlatan tea"}, {"Thé au miel"}, {"Thé au gingembre"}, {"Thé à la menthe"}, {"Thé au citron"}, {"Lait"}, {"Chocolat"}, {"Café au lait"}, {"Café long"}, {"Café court"}};
    int NB_PIECES_DISPO[10];
    for (int i = 0; i < 10; i++) {
        NB_PIECES_DISPO[i] = rand() % 10;
    }
    int Choix;
    int Somme;
	system("clear");
	printf("╔═══════════════════════════════════════════╗\n");
	printf("║                Distributeur               ║\n");
	printf("╠═══════════════════════════════════════════╬════╗\n");
	printf("║PARTIE A                                -->║  1 ║\n");
	printf("║PARTIE B                                -->║  2 ║\n");
	printf("║PARTIE C                                -->║  3 ║\n");
	printf("║PARTIE D                                -->║  4 ║\n");
	printf("╚═══════════════════════════════════════════╩════╝\n");
	printf("Choisissez une partie en renseignant le n° : ");
    scanf("%d", &partieTP);
    system("clear");
    switch (partieTP) {
        case 1:
			AFFICHAGE_BOISSONS();
			ACHAT_BOISSON(MONNAIE_DISPO, PRIX_BOISSONS, Choix, Somme);
        break;
		
        case 2:
			AFFICHAGE_BOISSONS();
			ACHAT_BOISSON_2(MONNAIE_DISPO, NB_PIECES_DISPO, PRIX_BOISSONS, Choix, Somme);
        break;
		
		case 3:
			AFFICHAGE_BOISSONS();
			ACHAT_BOISSON_3(MONNAIE_DISPO, NB_PIECES_DISPO, PRIX_BOISSONS, Choix, Somme);
        break;
		    
        case 4:
			AFFICHAGE_BOISSONS();
			ACHAT_BOISSON_4(MONNAIE_DISPO, NB_PIECES_DISPO, PRIX_BOISSONS, BOISSONS, Choix, Somme);
        break;
    }
    return 0;
}