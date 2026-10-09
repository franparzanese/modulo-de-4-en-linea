#include <criterion/criterion.h>

#include "grill.h"

Test(grill, create, .description = "Crear una grilla") {
    /*
     * Grilla:
     * | - - |
     * | - - |
     * | 1 - |
     * | 1 2 |
     */
    unsigned char **cells = malloc(2 * sizeof(unsigned char *));
    cells[0] = malloc(4 * sizeof(unsigned char));
    cells[0][0] = 1;
    cells[0][1] = 1;
    cells[0][2] = 0;
    cells[0][3] = 0;
    cells[1] = malloc(4 * sizeof(unsigned char));
    cells[1][0] = 2;
    cells[1][1] = 0;
    cells[1][2] = 0;
    cells[1][3] = 0;
    Grill *grill = grill_create(cells, 2, 4, 2);
    cr_assert_not_null(grill);
    cr_assert_eq(grill->cells, cells);
    cr_assert_eq(grill->columns, 2);
    cr_assert_eq(grill->rows, 4);
    cr_assert_eq(grill->chips_per_player[0], 2);
    cr_assert_eq(grill->chips_per_player[1], 1);
    cr_assert_eq(grill->players, 2);
    grill_free(&grill);
}

Test(grill, create_empty, .description = "Crear una grilla vacía") {
    /*
     * Grilla:
     * | - - |
     * | - - |
     * | - - |
     * | - - |
     */
    unsigned char **cells = malloc(2 * sizeof(unsigned char *));
    cells[0] = malloc(4 * sizeof(unsigned char));
    cells[0][0] = 0;
    cells[0][1] = 0;
    cells[0][2] = 0;
    cells[0][3] = 0;
    cells[1] = malloc(4 * sizeof(unsigned char));
    cells[1][0] = 0;
    cells[1][1] = 0;
    cells[1][2] = 0;
    cells[1][3] = 0;
    Grill *grill = grill_create(cells, 2, 4, 2);
    cr_assert_not_null(grill);
    cr_assert_eq(grill->cells, cells);
    cr_assert_eq(grill->columns, 2);
    cr_assert_eq(grill->rows, 4);
    cr_assert_eq(grill->chips_per_player[0], 0);
    cr_assert_eq(grill->chips_per_player[1], 0);
    cr_assert_eq(grill->players, 2);
    grill_free(&grill);
}

Test(grill, create_floating_chips, .description = "No puede crearse una grilla con fichas en el aire") {
    /*
     * Grilla:
     * | - - |
     * | - - |
     * | 1 2 |
     * | 1 - |
     */
    unsigned char **cells = malloc(2 * sizeof(unsigned char *));
    cells[0] = malloc(4 * sizeof(unsigned char));
    cells[0][0] = 1;
    cells[0][1] = 1;
    cells[0][2] = 0;
    cells[0][3] = 0;
    cells[1] = malloc(4 * sizeof(unsigned char));
    cells[1][0] = 0;
    cells[1][1] = 2;
    cells[1][2] = 0;
    cells[1][3] = 0;
    cr_assert_null(grill_create(cells, 2, 4, 2));
    free(cells[0]);
    free(cells[1]);
    free(cells);
}

Test(grill, create_chips_of_non_existent_players, .description = "No puede crearse una grilla con fichas de jugadores inexistentes") {
    /*
     * Grilla:
     * | - - |
     * | - - |
     * | - 3 |
     * | 1 2 |
     */
    unsigned char **cells = malloc(2 * sizeof(unsigned char *));
    cells[0] = malloc(4 * sizeof(unsigned char));
    cells[0][0] = 1;
    cells[0][1] = 0;
    cells[0][2] = 0;
    cells[0][3] = 0;
    cells[1] = malloc(4 * sizeof(unsigned char));
    cells[1][0] = 2;
    cells[1][1] = 3;
    cells[1][2] = 0;
    cells[1][3] = 0;
    cr_assert_null(grill_create(cells, 2, 4, 2));
    free(cells[0]);
    free(cells[1]);
    free(cells);
}

Test(grill, create_no_columns, .description = "No puede crearse una grilla sin columnas") {
    cr_assert_null(grill_create(NULL, 0, 4, 2));
}

Test(grill, create_no_rows, .description = "No puede crearse una grilla sin filas") {
    unsigned char **cells = malloc(2 * sizeof(unsigned char *));
    cells[0] = NULL;
    cells[1] = NULL;
    cr_assert_null(grill_create(cells, 2, 0, 2));
    free(cells);
}

Test(grill, create_no_players, .description = "No puede crearse una grilla sin jugadores") {
    /*
     * Grilla:
     * | - - |
     * | - - |
     * | - - |
     * | - - |
     */
    unsigned char **cells = malloc(2 * sizeof(unsigned char *));
    cells[0] = malloc(4 * sizeof(unsigned char));
    cells[0][0] = 0;
    cells[0][1] = 0;
    cells[0][2] = 0;
    cells[0][3] = 0;
    cells[1] = malloc(4 * sizeof(unsigned char));
    cells[1][0] = 0;
    cells[1][1] = 0;
    cells[1][2] = 0;
    cells[1][3] = 0;
    cr_assert_null(grill_create(cells, 2, 4, 0));
    free(cells[0]);
    free(cells[1]);
    free(cells);
}

Test(grill, test_free, .description = "Al liberar una grilla debe setear el puntero a 'NULL'") {
    unsigned char **cells = malloc(sizeof(unsigned char *));
    cells[0] = malloc(sizeof(unsigned char));
    cells[0][0] = 0;
    Grill *grill = grill_create(cells, 1, 1, 2);
    cr_assert_not_null(grill);
    grill_free(&grill);
    cr_assert_null(grill);
}

Test(grill, is_full_column_true, .description = "Verificar que una columna esté llena") {
    /*
     * Grilla:
     * | 2 - |
     * | 1 - |
     * | 1 2 |
     * | 1 2 |
     */
    unsigned char **cells = malloc(2 * sizeof(unsigned char *));
    cells[0] = malloc(4 * sizeof(unsigned char));
    cells[0][0] = 1;
    cells[0][1] = 1;
    cells[0][2] = 1;
    cells[0][3] = 2;
    cells[1] = malloc(4 * sizeof(unsigned char));
    cells[1][0] = 2;
    cells[1][1] = 2;
    cells[1][2] = 0;
    cells[1][3] = 0;
    Grill *grill = grill_create(cells, 2, 4, 2);
    cr_assert(grill_is_full_column(grill, 1));
    grill_free(&grill);
}

Test(grill, is_full_column_false, .description = "Verificar que una columna no esté llena") {
    /*
     * Grilla:
     * | 2 - |
     * | 1 - |
     * | 1 2 |
     * | 1 2 |
     */
    unsigned char **cells = malloc(2 * sizeof(unsigned char *));
    cells[0] = malloc(4 * sizeof(unsigned char));
    cells[0][0] = 1;
    cells[0][1] = 1;
    cells[0][2] = 1;
    cells[0][3] = 2;
    cells[1] = malloc(4 * sizeof(unsigned char));
    cells[1][0] = 2;
    cells[1][1] = 2;
    cells[1][2] = 0;
    cells[1][3] = 0;
    Grill *grill = grill_create(cells, 2, 4, 2);
    cr_assert_not(grill_is_full_column(grill, 2));
    grill_free(&grill);
}

Test(grill, is_full_column_non_existent, .description = "Una columna inexistente no está llena") {
    /*
     * Grilla:
     * | 2 - |
     * | 1 - |
     * | 1 2 |
     * | 1 2 |
     */
    unsigned char **cells = malloc(2 * sizeof(unsigned char *));
    cells[0] = malloc(4 * sizeof(unsigned char));
    cells[0][0] = 1;
    cells[0][1] = 1;
    cells[0][2] = 1;
    cells[0][3] = 2;
    cells[1] = malloc(4 * sizeof(unsigned char));
    cells[1][0] = 2;
    cells[1][1] = 2;
    cells[1][2] = 0;
    cells[1][3] = 0;
    Grill *grill = grill_create(cells, 2, 4, 2);
    cr_assert_not(grill_is_full_column(grill, 3));
    grill_free(&grill);
}

Test(grill, is_full_column_null, .description = "Una grilla nula no tiene columnas llenas") {
    cr_assert_not(grill_is_full_column(NULL, 1));
}

Test(grill, is_full_true, .description = "Verificar que una grilla esté llena") {
    /*
     * Grilla:
     * | 2 2 |
     * | 1 2 |
     * | 1 1 |
     * | 1 2 |
     */
    unsigned char **cells = malloc(2 * sizeof(unsigned char *));
    cells[0] = malloc(4 * sizeof(unsigned char));
    cells[0][0] = 1;
    cells[0][1] = 1;
    cells[0][2] = 1;
    cells[0][3] = 2;
    cells[1] = malloc(4 * sizeof(unsigned char));
    cells[1][0] = 2;
    cells[1][1] = 2;
    cells[1][2] = 1;
    cells[1][3] = 2;
    Grill *grill = grill_create(cells, 2, 4, 2);
    cr_assert(grill_is_full(grill));
    grill_free(&grill);
}

Test(grill, is_full_false, .description = "Verificar que una grilla no esté llena") {
    /*
     * Grilla:
     * | 2 - |
     * | 1 1 |
     * | 1 2 |
     * | 1 2 |
     */
    unsigned char **cells = malloc(2 * sizeof(unsigned char *));
    cells[0] = malloc(4 * sizeof(unsigned char));
    cells[0][0] = 1;
    cells[0][1] = 1;
    cells[0][2] = 1;
    cells[0][3] = 2;
    cells[1] = malloc(4 * sizeof(unsigned char));
    cells[1][0] = 2;
    cells[1][1] = 2;
    cells[1][2] = 1;
    cells[1][3] = 0;
    Grill *grill = grill_create(cells, 2, 4, 2);
    cr_assert_not(grill_is_full(grill));
    grill_free(&grill);
}

Test(grill, is_full_null, .description = "Una grilla nula no está llena") {
    cr_assert_not(grill_is_full(NULL));
}

Test(grill, put_chip, .description = "Colocar una ficha") {
    /*
     * Grilla:
     * | - - |
     * | 1 - |
     * | 1 2 |
     * | 1 2 |
     */
    unsigned char **cells = malloc(2 * sizeof(unsigned char *));
    cells[0] = malloc(4 * sizeof(unsigned char));
    cells[0][0] = 1;
    cells[0][1] = 1;
    cells[0][2] = 1;
    cells[0][3] = 0;
    cells[1] = malloc(4 * sizeof(unsigned char));
    cells[1][0] = 2;
    cells[1][1] = 2;
    cells[1][2] = 0;
    cells[1][3] = 0;
    Grill *grill = grill_create(cells, 2, 4, 2);
    cr_assert(grill_put_chip(grill, 2, 1));
    cr_assert_eq(grill->cells[0][3], 2);
    cr_assert_eq(grill->chips_per_player[1], 3);
    grill_free(&grill);
}

Test(grill, put_chip_full_column, .description = "No puede colocarse una ficha en una columna llena") {
    /*
     * Grilla:
     * | 2 - |
     * | 1 - |
     * | 1 2 |
     * | 1 2 |
     */
    unsigned char **cells = malloc(2 * sizeof(unsigned char *));
    cells[0] = malloc(4 * sizeof(unsigned char));
    cells[0][0] = 1;
    cells[0][1] = 1;
    cells[0][2] = 1;
    cells[0][3] = 2;
    cells[1] = malloc(4 * sizeof(unsigned char));
    cells[1][0] = 2;
    cells[1][1] = 2;
    cells[1][2] = 0;
    cells[1][3] = 0;
    Grill *grill = grill_create(cells, 2, 4, 2);
    cr_assert_not(grill_put_chip(grill, 1, 1));
    cr_assert_eq(grill->chips_per_player[0], 3);
    grill_free(&grill);
}

Test(grill, put_chip_non_existent_player, .description = "Un jugador inexistente no puede colocar fichas") {
    /*
     * Grilla:
     * | - - |
     * | 1 - |
     * | 1 2 |
     * | 1 2 |
     */
    unsigned char **cells = malloc(2 * sizeof(unsigned char *));
    cells[0] = malloc(4 * sizeof(unsigned char));
    cells[0][0] = 1;
    cells[0][1] = 1;
    cells[0][2] = 1;
    cells[0][3] = 0;
    cells[1] = malloc(4 * sizeof(unsigned char));
    cells[1][0] = 2;
    cells[1][1] = 2;
    cells[1][2] = 0;
    cells[1][3] = 0;
    Grill *grill = grill_create(cells, 2, 4, 2);
    cr_assert_not(grill_put_chip(grill, 3, 1));
    cr_assert_eq(grill->cells[0][3], 0);
    grill_free(&grill);
}

Test(grill, put_chip_non_existent_column, .description = "En una columna inexistente no pueden colocarse fichas") {
    /*
     * Grilla:
     * | - - |
     * | 1 - |
     * | 1 2 |
     * | 1 2 |
     */
    unsigned char **cells = malloc(2 * sizeof(unsigned char *));
    cells[0] = malloc(4 * sizeof(unsigned char));
    cells[0][0] = 1;
    cells[0][1] = 1;
    cells[0][2] = 1;
    cells[0][3] = 0;
    cells[1] = malloc(4 * sizeof(unsigned char));
    cells[1][0] = 2;
    cells[1][1] = 2;
    cells[1][2] = 0;
    cells[1][3] = 0;
    Grill *grill = grill_create(cells, 2, 4, 2);
    cr_assert_not(grill_put_chip(grill, 2, 3));
    cr_assert_eq(grill->chips_per_player[1], 2);
    grill_free(&grill);
}

Test(grill, put_chip_null, .description = "En una grilla nula no pueden colocarse fichas") {
    cr_assert_not(grill_put_chip(NULL, 2, 1));
}
