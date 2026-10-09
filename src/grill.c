#include <stdlib.h>

#include "grill.h"

Grill *grill_create(unsigned char **cells, unsigned char columns, unsigned char rows, unsigned char players) {
    if (!columns || !rows || !players) return NULL;
    unsigned short *chips_per_player = malloc(players * sizeof(unsigned short));
    if (!chips_per_player) return NULL;
    for (unsigned char i = 0; i < players; i++) {
        chips_per_player[i] = 0;
    }
    // Valida la grilla e inicializa el contador de fichas por jugador.
    for (unsigned char i = 0; i < columns; i++) {
        bool has_more_chips = true;
        for (unsigned char j = 0; j < rows; j++) {
            if (cells[i][j] > players) {
                free(chips_per_player);
                return NULL;
            }
            if (cells[i][j]) {
                if (!has_more_chips) {
                    // Ficha "en el aire".
                    free(chips_per_player);
                    return NULL;
                }
                chips_per_player[cells[i][j] - 1] += 1;
            } else {
                has_more_chips = false;
            }
        }
    }
    Grill *grill = malloc(sizeof(Grill));
    if (!grill) {
        free(chips_per_player);
        return NULL;
    }
    grill->cells = cells;
    grill->columns = columns;
    grill->rows = rows;
    grill->chips_per_player = chips_per_player;
    grill->players = players;
    return grill;
}

void grill_free(Grill **grill) {
    free((*grill)->cells);
    free((*grill)->chips_per_player);
    free(*grill);
    *grill = NULL;
}

bool grill_is_full_column(Grill *grill, unsigned char column) {
    if (!grill || !column || column > grill->columns) return false;
    return grill->cells[column - 1][grill->rows - 1] > 0;
}

bool grill_is_full(Grill *grill) {
    if (!grill) return false;
    for (unsigned char i = 1; i <= grill->columns; i++) {
        if (!grill_is_full_column(grill, i)) return false;
    }
    return true;
}

bool grill_put_chip(Grill *grill, unsigned char player, unsigned char column) {
    if (!grill || !player || player > grill->players || !column || column > grill->columns) {
        return false;
    }
    for (unsigned char i = 0; i < grill->rows; i++) {
        if (!grill->cells[column - 1][i]) {
            grill->cells[column - 1][i] = player;
            grill->chips_per_player[player - 1] += 1;
            return true;
        }
    }
    return false;
}
