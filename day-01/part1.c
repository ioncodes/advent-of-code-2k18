#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE* fp = fopen("input.txt", "r");

    ssize_t read;
    char* line = NULL;
    size_t len = 0;
    int frequency = 0;

    while((read = getline(&line, &len, fp)) != -1) {
        frequency += atoi(line);
    }

    fclose(fp);
    free(line);

    printf("%i", frequency);
    
    return 0;
}
