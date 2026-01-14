#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#else
#include <unistd.h>
#endif

#include "boite_noire.h"
#include "simulation.h"

int main() {
    printf("=== Bienvenue dans le projet Boite Noire ===\n");
    printf("Projet realise par : \n ADJAVON Maelle \n AKELANI Aziz\n CAKPO Fades\n DAOUDA Chakirath\n GOUNONGBE Sidney\n\n");

    BoiteNoire *b = creer();
    float vitesse = 0, temperature_moteur  = 25;

    while (1) {
        char c;
        printf("\nAction [A]ccelerer [F]reiner [Q]uitter : ");
        scanf(" %c", &c);

        if (c == 'A') vitesse+= 5;
        else if (c == 'F') vitesse= (vitesse>= 5) ? vitesse- 7 : 0;
        else if (c == 'Q') {
            dump_memory(b);
            break;
        }

        sleep(1);
        temperature_moteur  = temperature_moteur +( 0.5 * vitesse) -(0.1*(temperature_moteur - 20));

        printf("Vitesse : %.2f | Temp : %.2f\n", vitesse, temperature_moteur );
        enregistrer_cycle(b, vitesse, temperature_moteur );

        if (temperature_moteur  > 110) {
            printf("\nil y a crash\n");
            dump_memory(b);
            break;
        }
    }

    analyser();
    printf("\n=== FIN DU PROGRAMME ===\n");
    return 0;
}
