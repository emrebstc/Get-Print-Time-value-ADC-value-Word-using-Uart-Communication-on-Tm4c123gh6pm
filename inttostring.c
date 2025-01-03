#include "stdbool.h"
#include "stdint.h"

void uint32_to_string(uint32_t num, char *str) {
    int i = 0;
    int j;
    char temp;

    // E�er num s�f�rsa, string'e '0' ekle
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';  // null terminat�r
        return;
    }

    // Say�y� ters �evrilmi� olarak yaz
    while (num > 0) {
        str[i++] = (num % 10) + '0';  // num % 10 son basama�� al�r ve '0' ile ASCII'ye d�n��t�r�r
        num /= 10;
    }

    str[i] = '\0';  // null terminat�r ekle

    // String'i ters �evir
    for (j = 0; j < i / 2; j++) {
        temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}
