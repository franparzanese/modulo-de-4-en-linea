#ifndef EVALUATION_H
#define EVALUATION_H

#include <stdbool.h>

typedef struct EvaluationRep {
    short value;
    unsigned char *sequence;
    unsigned short length;
} Evaluation;

/**
 * Crea una evaluación.
 * @param value Valor de la evaluación.
 * @param sequence Secuencia de columnas jugadas.
 * @param length Cantidad de jugadas en la secuencia.
 * @return Evaluación creada.
 */
Evaluation *evaluation_create(short value, unsigned char *sequence, unsigned short length);

/**
 * Libera la memoria reservada por una evaluación.
 * @param evaluation Evaluación a liberar.
 */
void evaluation_free(Evaluation **evaluation);

/**
 * Escribe una evaluación en un fichero de texto.
 * @param evaluation Evaluación a escribir.
 * @param file Ruta al fichero de texto.
 * @return Si se escribió el fichero o no.
 */
bool evaluation_write_to_file(Evaluation *evaluation, char *file);

/**
 * Determina si una evaluación es mejor que otra.
 * @param evaluation Evaluación a determinar si es mejor.
 * @param other Evaluación a comparar.
 * @return Si la evaluación es mejor o no.
 */
bool evaluation_is_better(Evaluation *evaluation, Evaluation *other);

#endif
