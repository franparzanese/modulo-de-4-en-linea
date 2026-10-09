#include <stdlib.h>

#include "grill.h"

Grill *grill_create(unsigned char **cells, unsigned char columns, unsigned char rows, unsigned char players) {
    // if (!columns || !rows || !players) return NULL;
    unsigned short *chips_per_player = malloc(players * sizeof(unsigned short));
    if (!chips_per_player) return NULL;
    Grill *grill = malloc(sizeof(Grill));
    if (!grill) {
        free(chips_per_player);
        return NULL;
    }
    grill->cells = cells;
    grill->columns = columns;
    grill->rows = rows;
    for (char i = 0; i < players; i++) {
        chips_per_player[i] = 0;
    }
    grill->chips_per_player = chips_per_player;
    grill->players = players;
    return grill;
}

void grill_free(Grill **grill) {}

bool grill_is_full_column(Grill *grill, unsigned char column) {
    return false;
}

bool grill_is_full(Grill *grill) {
    return false;
}

bool grill_put_chip(Grill *grill, unsigned char player, unsigned char column) {
    return false;
}
