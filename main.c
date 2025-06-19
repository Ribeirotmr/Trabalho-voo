#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "menu.h"


int main() {
    setlocale(LC_ALL, "Portuguese");
    menuPrincipal(); // Chama o menu principal

    return 0;
}
