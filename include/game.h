#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "grill.h"

typedef struct GameRep {
    Grill *grill;
    unsigned char current_player;
} Game;

/**
 * Crea una partida a partir de un fichero de texto con la siguiente estructura:
 * @todo Documentar estructura.
 * @param file Ruta al fichero de texto.
 * @return Partida creada.
 */
Game *game_create_from_file(char *file);

/**
 * Libera la memoria reservada por una partida.
 * @param game Partida a liberar.
 */
void game_free(Game **game);

/**
 * Determina si una partida es válida. Esto implica que:
 * - Ambos jugadores han jugado la misma cantidad de fichas, o bien el primer
 *   jugador ha jugado una más (por iniciar el juego).
 * - No han ganado ambos jugadores a la vez.
 * @param game Partida a evaluar.
 * @return Si la partida es válida o no.
 */
bool game_is_valid(Game *game);

/**
 * Determina si una partida ha sido empate.
 * @param game Partida a evaluar.
 * @return Si la partida ha sido empate o no.
 */
bool game_is_draw(Game *game);

/**
 * Determina si un jugador ha ganado en una partida.
 * @param game Partida a evaluar.
 * @param player Jugador a evaluar.
 * @return Si el jugador ha ganado o no.
 */
bool game_has_won(Game *game, unsigned char player);

/**
 * Coloca una ficha de un jugador en una columna.
 * @param game Partida en juego.
 * @param column Columna en la cual se coloca la ficha.
 * @return Si se efectuó la jugada o no.
 */
bool game_put_chip(Game *game, unsigned char column);

#endif
