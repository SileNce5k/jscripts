#include <stdio.h>

int main() {
    // Generate LF line endings
    FILE* file_lf = fopen("file_lf.txt", "w");
    if (file_lf == NULL) {
        printf("Error creating file with LF line endings.\n");
        return 1;
    }

    for (int i = 1; i <= 10; i++) {
        fprintf(file_lf, "Line %d\n", i);
    }

    fclose(file_lf);


    // Generate CRLF line endings
    FILE* file_crlf = fopen("file_crlf.txt", "w");
    if (file_crlf == NULL) {
        printf("Error creating file with CRLF line endings.\n");
        return 1;
    }

    for (int i = 1; i <= 10; i++) {
        fprintf(file_crlf, "Line %d\r\n", i);
    }

    fclose(file_crlf);


    // Generate mixed line endings
    FILE* file_mixed = fopen("file_mixed.txt", "w");
    if (file_mixed == NULL) {
        printf("Error creating file with mixed line endings.\n");
        return 1;
    }

    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            fprintf(file_mixed, "Line %d\r\n", i);
        } else {
            fprintf(file_mixed, "Line %d\n", i);
        }
    }

    fclose(file_mixed);

    printf("Files generated successfully.\n");

    return 0;
}
