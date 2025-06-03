#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_virtualization() {
    char buffer[128];
    FILE *fp = popen("wmic computersystem get manufacturer", "r");
    
    if (fp == NULL) {
        printf("Error al ejecutar el comando.\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strstr(buffer, "VMware") || strstr(buffer, "VirtualBox") || strstr(buffer, "QEMU")) {
            printf("Máquina Virtual detectada. Cerrando programa...\n");
            exit(0);
        }
    }

    pclose(fp);
    printf("No se ha detectado ninguna Máquina Virtual.\n");
}

int main() {
    check_virtualization();
    return 0;
}
