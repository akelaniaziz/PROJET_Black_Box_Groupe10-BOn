#include "simulation.h"

void dump_memory(BoiteNoire *b) {
    FILE *f = fopen("crash.bin", "wb");
    if (!f) return;

    Frame *c = b->head;
    while (c) {
        fwrite(c, sizeof(Frame), 1, f);
        c = c->next;
    }

    fclose(f);
    printf("Données sauvegardées en binaire dans crash.bin\n");
}

void lire_memory(BoiteNoire *b) {
    FILE *f = fopen("crash.bin", "rb");
    if (!f) return;

    Frame temp;
    while (fread(&temp, sizeof(Frame), 1, f) == 1) {
        enregistrer_cycle(b, temp.vitesse, temp.temperature_moteur);
    }

    fclose(f);
    printf("Données lues depuis crash.bin\n");
}

void analyser() {
    FILE *f = fopen("crash.bin", "rb");
    if (!f) {
        printf("Aucune donnée à analyser.\n");
        return;
    }

    long timestamp;
    float vitesse, temperature_moteur;
    float sv = 0, Tmax = 0;
    int n = 0;

    printf("\n=== DONNEES ENREGISTREES ===\n");

    Frame temp;
    while (fread(&temp, sizeof(Frame), 1, f) == 1) {
        timestamp = temp.timestamp;
        vitesse = temp.vitesse;
        temperature_moteur = temp.temperature_moteur;

        printf("timestamp=%ld | vitesse=%.2f | temperature_moteur =%.2f\n",
               timestamp, vitesse, temperature_moteur);

        sv += vitesse;
        if (temperature_moteur > Tmax) Tmax = temperature_moteur;
        n++;
    }

    fclose(f);

    if (n == 0) {
        printf("Aucune frame enregistrée.\n");
        return;
    }

    printf("\n=== ANALYSE ===\n");
    printf("Vitesse moyenne : %.2f km/h\n", sv / n);
    printf("Temperature max : %.2f °C\n", Tmax);
}
