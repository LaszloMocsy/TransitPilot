#include <stdio.h>
#include <stdbool.h>

int main(void) {
    bool _loop = true;

    while (_loop) {
        printf("Choose one of the following actions:\n"
               "[ 1 ]  List all lines and stops\n"
               "[ 2 ]  Modify starting stop\n"
               "[ 3 ]  Modify ending stop\n"
               "[ 4 ]  Plan a route\n"
               "[ 0 ]  Exit program\n");
        int action;
        do {
            printf("> ");
            scanf("%d", &action);
            switch (action) {
                case 1:
                    printf("\n--> List all lines and stops\n\n");
                    break;
                case 2:
                    printf("\n--> Modify starting stop\n\n");
                    break;
                case 3:
                    printf("\n--> Modify ending stop\n\n");
                    break;
                case 4:
                    printf("\n--> Plan a route\n\n");
                    break;
                case 0:
                    _loop = false;
                    break;
                default:
                    // Invalid action submitted
                    break;
            };
        } while (action != 0 && !(action >= 1 && action <= 4));
    };

    return 0;
}