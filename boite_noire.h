#ifndef BOITE_NOIRE_H
#define BOITE_NOIRE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Frame {
    long timestamp;
    float vitesse;
    float temperature_moteur ;
    struct Frame *next;
} Frame;

typedef struct {
    Frame *head, *tail;
    int n;
} BoiteNoire;

BoiteNoire* creer();
void enregistrer_cycle(BoiteNoire *b, float vitesse, float temperature_moteur );

#endif
