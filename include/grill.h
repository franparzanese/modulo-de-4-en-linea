#ifndef GRILL_H
#define GRILL_H

#include <stdbool.h>

typedef struct GrillRep {
    unsigned char **cells;
    unsigned char columns;
    unsigned char rows;
    unsigned short *chips_per_player;
    unsigned char players;
} Grill;

/**
 * Crea una grilla.
 * @param cells Celdas de la grilla.
 * @param columns Columnas de la grilla.
 * @param rows Filas de la grilla.
 * @param players Cantidad de jugadores.
 * @return Grilla creada.
 */
Grill *grill_create(unsigned char **cells, unsigned char columns, unsigned char rows, unsigned char players);

/**
 * Libera la memoria reservada por una grilla.
 * @param grill Grilla a liberar.
 */
void grill_free(Grill **grill);

/**
 * Determina si una columna está llena en una grilla.
 * @param grill Grilla a evaluar.
 * @param column Columna a evaluar (donde la primera es la 1).
 * @return Si la columna está llena o no.
 */
bool grill_is_full_column(Grill *grill, unsigned char column);

/**
 * Determina si una grilla está llena.
 * @param grill Grilla a evaluar.
 * @return Si la grilla está llena o no.
 */
bool grill_is_full(Grill *grill);

/**
 * Coloca una ficha de un jugador en una columna de una grilla.
 * @param grill Grilla de juego.
 * @param player Jugador que coloca la ficha (donde el primero es el 1).
 * @param column Columna en la cual se coloca la ficha (donde la primera es la 1).
 * @return Si se efectuó la jugada o no.
 */
bool grill_put_chip(Grill *grill, unsigned char player, unsigned char column);

#endif
