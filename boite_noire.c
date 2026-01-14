#include "boite_noire.h"

BoiteNoire* creer() {
    BoiteNoire *b = malloc(sizeof(BoiteNoire));
    b->head = b->tail = NULL;
    b->n = 0;
    return b;
}

void enregistrer_cycle(BoiteNoire *b, float vitesse, float temperature_moteur ) {
    Frame *f = malloc(sizeof(Frame));
    f->timestamp = time(NULL);
    f->vitesse= vitesse;
    f->temperature_moteur  = temperature_moteur ;
    f->next = NULL;

    if (b->n == 10) {
        printf("Rotation : Frame ancienne ecrasee.\n");
        Frame *tmp = b->head;
        b->head = tmp->next;
        free(tmp);
        b->n--;
    }

    if (!b->tail) b->head = b->tail = f;
    else { b->tail->next = f; b->tail = f; }

    b->n++;

    printf("Enregistrement Frame [%ld]... (Memoire : %d/10)\n", f->timestamp, b->n);
}
