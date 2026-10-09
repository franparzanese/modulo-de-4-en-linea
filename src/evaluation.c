#include <stdlib.h>
#include <string.h>

#include "evaluation.h"

Evaluation *evaluation_create(short value, unsigned char *sequence, unsigned short length) {
    // Valida la longitud de la secuencia.
    if (value != 0) {
        unsigned int value_x2 = abs(2 * value);
        if (length != value_x2 - 1 && length != value_x2) return NULL;
    }
    Evaluation *evaluation = malloc(sizeof(Evaluation));
    if (!evaluation) return NULL;
    evaluation->value = value;
    evaluation->sequence = sequence;
    evaluation->length = length;
    return evaluation;
}

void evaluation_free(Evaluation **evaluation) {
    free((*evaluation)->sequence);
    free(*evaluation);
    *evaluation = NULL;
}

/**
 * @todo No implementado aún.
 */
bool evaluation_write_to_file(Evaluation *evaluation, char *file) {
    return false;
}

/**
 * Determina si una evaluación es mejor que otra aplicando los criterios de desempate.
 * @param evaluation Evaluación a determinar si es mejor.
 * @param other Evaluación a comparar.
 * @return Si la evaluación es mejor o no.
 */
static bool evaluation_is_better_tie_breaker(Evaluation *evaluation, Evaluation *other) {
    if (evaluation->value != other->value) {
        return evaluation->value < other->value;
    }
    if (evaluation->length < other->length) {
        return memcmp(evaluation->sequence, other->sequence, evaluation->length) <= 0;
    }
    return memcmp(evaluation->sequence, other->sequence, other->length) < 0;
}

bool evaluation_is_better(Evaluation *evaluation, Evaluation *other) {
    if (!evaluation) return false;
    if (!other) return true;
    if (evaluation->value > 0) {
        if (other->value <= 0) return true;
        return evaluation_is_better_tie_breaker(evaluation, other);
    }
    if (evaluation->value < 0) {
        if (other->value >= 0) return false;
        return evaluation_is_better_tie_breaker(evaluation, other);
    }
    if (other->value > 0) return false;
    if (other->value < 0) return true;
    return evaluation_is_better_tie_breaker(evaluation, other);
}
