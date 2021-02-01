#define _POSIX_C_SOURCE 200809L

#include "testing.h"
#include "abb.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

void pruebas_abb_alumno(void);

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

int main(int argc, char *argv[]){   

    printf("~~~ PRUEBAS ALUMNO ~~~\n");
    pruebas_abb_alumno();

    return failure_count() > 0;
}
