#ifndef SOLVER_H
#define SOLVER_H

#include "evaluation.h"
#include "game.h"

/**
 * Evalúa una partida.
 * @param game Partida a evaluar.
 * @return Evaluación de la partida.
 */
Evaluation *solver_evaluate(Game *game);

#endif
