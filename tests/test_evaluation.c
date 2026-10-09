#include <criterion/criterion.h>

#include "evaluation.h"

Test(evaluation, create, .description = "Crear una evaluación de victoria forzada") {
    unsigned char *sequence = malloc(3 * sizeof(unsigned char));
    sequence[0] = 4;
    sequence[1] = 1;
    sequence[2] = 5;
    Evaluation *evaluation = evaluation_create(2, sequence, 3);
    cr_assert_not_null(evaluation);
    cr_assert_eq(evaluation->value, 2);
    cr_assert_eq(evaluation->sequence, sequence);
    cr_assert_eq(evaluation->length, 3);
    evaluation_free(&evaluation);
}

Test(evaluation, create_bad_sequence, .description = "Una evaluación con valor 'n' tal que 'n != 0' debe tener '|2n|-1' ó '|2n|' cantidad de jugadas") {
    unsigned char *sequence = malloc(sizeof(unsigned char));
    sequence[0] = 4;
    // Dado el valor 2 debería tener 3 ó 4 jugadas pero tiene 1.
    Evaluation *evaluation = evaluation_create(2, sequence, 1);
    cr_assert_null(evaluation);
    free(sequence);
}

Test(evaluation, create_value_zero, .description = "Crear una evaluación de empate forzado") {
    unsigned char *sequence = malloc(2 * sizeof(unsigned char));
    sequence[0] = 5;
    sequence[1] = 5;
    Evaluation *evaluation = evaluation_create(0, sequence, 2);
    cr_assert_not_null(evaluation);
    cr_assert_eq(evaluation->value, 0);
    cr_assert_eq(evaluation->sequence, sequence);
    cr_assert_eq(evaluation->length, 2);
    evaluation_free(&evaluation);
}

Test(evaluation, create_value_zero_empty_sequence, .description = "Crear una evaluación de empate efectivizado") {
    Evaluation *evaluation = evaluation_create(0, NULL, 0);
    cr_assert_not_null(evaluation);
    cr_assert_eq(evaluation->value, 0);
    cr_assert_eq(evaluation->length, 0);
    evaluation_free(&evaluation);
}

Test(evaluation, test_free, .description = "Al liberar una evaluación debe setear el puntero a 'NULL'") {
    unsigned char *sequence = malloc(sizeof(unsigned char));
    sequence[0] = 4;
    Evaluation *evaluation = evaluation_create(0, sequence, 1);
    cr_assert_not_null(evaluation);
    evaluation_free(&evaluation);
    cr_assert_null(evaluation);
}

Test(evaluation, write_to_file, .description = "Escribir una evaluación en un fichero de texto", .disabled = true) {}

Test(evaluation, write_to_file_error, .description = "Manejo de errores al escribir una evaluación en un fichero de texto", .disabled = true) {}

Test(evaluation, write_to_file_null, .description = "Una evaluación nula no puede escribirse en un fichero de texto") {
    cr_assert_not(evaluation_write_to_file(NULL, "test.txt"));
}

Test(evaluation, is_better_positive_values, .description = "Una evaluación de victoria es mejor que otra si requiere menos jugadas") {
    unsigned char *sequence_a = malloc(sizeof(unsigned char));
    sequence_a[0] = 2;
    Evaluation *evaluation_a = evaluation_create(1, sequence_a, 1);
    unsigned char *sequence_b = malloc(3 * sizeof(unsigned char));
    sequence_b[0] = 1;
    sequence_b[1] = 1;
    sequence_b[2] = 2;
    Evaluation *evaluation_b = evaluation_create(2, sequence_b, 3);
    cr_assert(evaluation_is_better(evaluation_a, evaluation_b));
    cr_assert_not(evaluation_is_better(evaluation_b, evaluation_a));
    evaluation_free(&evaluation_a);
    evaluation_free(&evaluation_b);
}

Test(evaluation, is_better_same_positive_value_and_sequence_length, .description = "Dos evaluaciones de victoria con igual valor y cantidad de jugadas se priorizan por la secuencia ascendente") {
    unsigned char *sequence_a = malloc(sizeof(unsigned char));
    sequence_a[0] = 2;
    Evaluation *evaluation_a = evaluation_create(1, sequence_a, 1);
    unsigned char *sequence_b = malloc(sizeof(unsigned char));
    sequence_b[0] = 10;
    Evaluation *evaluation_b = evaluation_create(1, sequence_b, 1);
    cr_assert(evaluation_is_better(evaluation_a, evaluation_b));
    cr_assert_not(evaluation_is_better(evaluation_b, evaluation_a));
    evaluation_free(&evaluation_a);
    evaluation_free(&evaluation_b);
}

Test(evaluation, is_better_same_positive_value_but_different_sequence_length, .description = "Dos evaluaciones de victoria con igual valor pero distinta cantidad de jugadas se priorizan por la secuencia ascendente") {
    unsigned char *sequence_a = malloc(2 * sizeof(unsigned char));
    sequence_a[0] = 2;
    sequence_a[1] = 10;
    Evaluation *evaluation_a = evaluation_create(1, sequence_a, 2);
    unsigned char *sequence_b = malloc(sizeof(unsigned char));
    sequence_b[0] = 10;
    Evaluation *evaluation_b = evaluation_create(1, sequence_b, 1);
    cr_assert(evaluation_is_better(evaluation_a, evaluation_b));
    cr_assert_not(evaluation_is_better(evaluation_b, evaluation_a));
    evaluation_free(&evaluation_a);
    evaluation_free(&evaluation_b);
}

Test(evaluation, is_better_same_positive_value_and_partial_sequence, .description = "Entre dos evaluaciones de victoria con igual valor y jugadas parciales es mejor la de menor cantidad de jugadas") {
    unsigned char *sequence_a = malloc(sizeof(unsigned char));
    sequence_a[0] = 2;
    Evaluation *evaluation_a = evaluation_create(1, sequence_a, 1);
    unsigned char *sequence_b = malloc(2 * sizeof(unsigned char));
    sequence_b[0] = 2;
    sequence_b[1] = 2;
    Evaluation *evaluation_b = evaluation_create(1, sequence_b, 2);
    cr_assert(evaluation_is_better(evaluation_a, evaluation_b));
    cr_assert_not(evaluation_is_better(evaluation_b, evaluation_a));
    evaluation_free(&evaluation_a);
    evaluation_free(&evaluation_b);
}

Test(evaluation, is_better_positive_value_vs_zero, .description = "Una evaluación de victoria es mejor que una de empate") {
    unsigned char *sequence_a = malloc(sizeof(unsigned char));
    sequence_a[0] = 1;
    Evaluation *evaluation_a = evaluation_create(1, sequence_a, 1);
    Evaluation *evaluation_b = evaluation_create(0, NULL, 0);
    cr_assert(evaluation_is_better(evaluation_a, evaluation_b));
    cr_assert_not(evaluation_is_better(evaluation_b, evaluation_a));
    evaluation_free(&evaluation_a);
    evaluation_free(&evaluation_b);
}

Test(evaluation, is_better_positive_vs_negative_values, .description = "Una evaluación de victoria es mejor que una de derrota") {
    unsigned char *sequence_a = malloc(sizeof(unsigned char));
    sequence_a[0] = 2;
    Evaluation *evaluation_a = evaluation_create(1, sequence_a, 1);
    unsigned char *sequence_b = malloc(sizeof(unsigned char));
    sequence_b[0] = 1;
    Evaluation *evaluation_b = evaluation_create(-1, sequence_b, 1);
    cr_assert(evaluation_is_better(evaluation_a, evaluation_b));
    cr_assert_not(evaluation_is_better(evaluation_b, evaluation_a));
    evaluation_free(&evaluation_a);
    evaluation_free(&evaluation_b);
}

Test(evaluation, is_better_zero_values_with_same_sequence_length, .description = "Dos evaluaciones de empate con igual cantidad de jugadas se priorizan por la secuencia ascendente") {
    unsigned char *sequence_a = malloc(2 * sizeof(unsigned char));
    sequence_a[0] = 2;
    sequence_a[1] = 10;
    Evaluation *evaluation_a = evaluation_create(0, sequence_a, 2);
    unsigned char *sequence_b = malloc(2 * sizeof(unsigned char));
    sequence_b[0] = 10;
    sequence_b[1] = 2;
    Evaluation *evaluation_b = evaluation_create(0, sequence_b, 2);
    cr_assert(evaluation_is_better(evaluation_a, evaluation_b));
    cr_assert_not(evaluation_is_better(evaluation_b, evaluation_a));
    evaluation_free(&evaluation_a);
    evaluation_free(&evaluation_b);
}

Test(evaluation, is_better_zero_values_with_different_sequence_length, .description = "Dos evaluaciones de empate con distinta cantidad de jugadas se priorizan por la secuencia ascendente") {
    unsigned char *sequence_a = malloc(2 * sizeof(unsigned char));
    sequence_a[0] = 2;
    sequence_a[1] = 10;
    Evaluation *evaluation_a = evaluation_create(0, sequence_a, 2);
    unsigned char *sequence_b = malloc(4 * sizeof(unsigned char));
    sequence_b[0] = 10;
    sequence_b[1] = 2;
    sequence_b[2] = 2;
    sequence_b[3] = 10;
    Evaluation *evaluation_b = evaluation_create(0, sequence_b, 4);
    cr_assert(evaluation_is_better(evaluation_a, evaluation_b));
    cr_assert_not(evaluation_is_better(evaluation_b, evaluation_a));
    evaluation_free(&evaluation_a);
    evaluation_free(&evaluation_b);
}

Test(evaluation, is_better_zero_values_with_same_partial_sequence, .description = "Entre dos evaluaciones de empate con las mismas jugadas parciales es mejor la de menor cantidad de jugadas") {
    unsigned char *sequence_a = malloc(2 * sizeof(unsigned char));
    sequence_a[0] = 2;
    sequence_a[1] = 10;
    Evaluation *evaluation_a = evaluation_create(0, sequence_a, 2);
    unsigned char *sequence_b = malloc(4 * sizeof(unsigned char));
    sequence_b[0] = 2;
    sequence_b[1] = 10;
    sequence_b[2] = 10;
    sequence_b[3] = 2;
    Evaluation *evaluation_b = evaluation_create(0, sequence_b, 4);
    cr_assert(evaluation_is_better(evaluation_a, evaluation_b));
    cr_assert_not(evaluation_is_better(evaluation_b, evaluation_a));
    evaluation_free(&evaluation_a);
    evaluation_free(&evaluation_b);
}

Test(evaluation, is_better_negative_values, .description = "Una evaluación de derrota es mejor que otra si la retrasa más jugadas") {
    unsigned char *sequence_a = malloc(3 * sizeof(unsigned char));
    sequence_a[0] = 2;
    sequence_a[1] = 2;
    sequence_a[2] = 1;
    Evaluation *evaluation_a = evaluation_create(-2, sequence_a, 3);
    unsigned char *sequence_b = malloc(sizeof(unsigned char));
    sequence_b[0] = 1;
    Evaluation *evaluation_b = evaluation_create(-1, sequence_b, 1);
    cr_assert(evaluation_is_better(evaluation_a, evaluation_b));
    cr_assert_not(evaluation_is_better(evaluation_b, evaluation_a));
    evaluation_free(&evaluation_a);
    evaluation_free(&evaluation_b);
}

Test(evaluation, is_better_same_negative_value_and_sequence_length, .description = "Dos evaluaciones de derrota con igual valor y cantidad de jugadas se priorizan por la secuencia ascendente") {
    unsigned char *sequence_a = malloc(sizeof(unsigned char));
    sequence_a[0] = 2;
    Evaluation *evaluation_a = evaluation_create(-1, sequence_a, 1);
    unsigned char *sequence_b = malloc(sizeof(unsigned char));
    sequence_b[0] = 10;
    Evaluation *evaluation_b = evaluation_create(-1, sequence_b, 1);
    cr_assert(evaluation_is_better(evaluation_a, evaluation_b));
    cr_assert_not(evaluation_is_better(evaluation_b, evaluation_a));
    evaluation_free(&evaluation_a);
    evaluation_free(&evaluation_b);
}

Test(evaluation, is_better_same_negative_value_but_different_sequence_length, .description = "Dos evaluaciones de derrota con igual valor pero distinta cantidad de jugadas se priorizan por la secuencia ascendente") {
    unsigned char *sequence_a = malloc(2 * sizeof(unsigned char));
    sequence_a[0] = 2;
    sequence_a[1] = 10;
    Evaluation *evaluation_a = evaluation_create(-1, sequence_a, 2);
    unsigned char *sequence_b = malloc(sizeof(unsigned char));
    sequence_b[0] = 10;
    Evaluation *evaluation_b = evaluation_create(-1, sequence_b, 1);
    cr_assert(evaluation_is_better(evaluation_a, evaluation_b));
    cr_assert_not(evaluation_is_better(evaluation_b, evaluation_a));
    evaluation_free(&evaluation_a);
    evaluation_free(&evaluation_b);
}

Test(evaluation, is_better_same_negative_value_and_partial_sequence, .description = "Entre dos evaluaciones de derrota con igual valor y jugadas parciales es mejor la de menor cantidad de jugadas") {
    unsigned char *sequence_a = malloc(sizeof(unsigned char));
    sequence_a[0] = 2;
    Evaluation *evaluation_a = evaluation_create(-1, sequence_a, 1);
    unsigned char *sequence_b = malloc(2 * sizeof(unsigned char));
    sequence_b[0] = 2;
    sequence_b[1] = 2;
    Evaluation *evaluation_b = evaluation_create(-1, sequence_b, 2);
    cr_assert(evaluation_is_better(evaluation_a, evaluation_b));
    cr_assert_not(evaluation_is_better(evaluation_b, evaluation_a));
    evaluation_free(&evaluation_a);
    evaluation_free(&evaluation_b);
}

Test(evaluation, is_better_negative_value_vs_zero, .description = "Una evaluación de empate es mejor que una de derrota") {
    Evaluation *evaluation_a = evaluation_create(0, NULL, 0);
    unsigned char *sequence_b = malloc(sizeof(unsigned char));
    sequence_b[0] = 1;
    Evaluation *evaluation_b = evaluation_create(-1, sequence_b, 1);
    cr_assert(evaluation_is_better(evaluation_a, evaluation_b));
    cr_assert_not(evaluation_is_better(evaluation_b, evaluation_a));
    evaluation_free(&evaluation_a);
    evaluation_free(&evaluation_b);
}

Test(evaluation, is_better_equal_evaluations, .description = "Entre dos evaluaciones equivalentes no hay ninguna mejor que la otra") {
    Evaluation *evaluation_a = evaluation_create(0, NULL, 0);
    Evaluation *evaluation_b = evaluation_create(0, NULL, 0);
    cr_assert_not(evaluation_is_better(evaluation_a, evaluation_b));
    cr_assert_not(evaluation_is_better(evaluation_b, evaluation_a));
    evaluation_free(&evaluation_a);
    evaluation_free(&evaluation_b);
}

Test(evaluation, is_better_null, .description = "Una evaluación no nula es mejor que una nula") {
    Evaluation *evaluation = evaluation_create(0, NULL, 0);
    cr_assert(evaluation_is_better(evaluation, NULL));
    cr_assert_not(evaluation_is_better(NULL, evaluation));
    evaluation_free(&evaluation);
}

Test(evaluation, is_better_equal_nulls, .description = "Dos evaluaciones nulas son equivalentes") {
    cr_assert_not(evaluation_is_better(NULL, NULL));
}
