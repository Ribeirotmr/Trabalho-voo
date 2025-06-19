#include <stdio.h>
#include <stdlib.h>
#include "frequentes.h"

void limparBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}
