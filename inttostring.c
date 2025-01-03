#include "stdbool.h"
#include "stdint.h"

void uint32_to_string(uint32_t num, char *str) {
    int i = 0;
    int j;
    char temp;

    // Eðer num sýfýrsa, string'e '0' ekle
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';  // null terminatör
        return;
    }

    // Sayýyý ters çevrilmiþ olarak yaz
    while (num > 0) {
        str[i++] = (num % 10) + '0';  // num % 10 son basamaðý alýr ve '0' ile ASCII'ye dönüþtürür
        num /= 10;
    }

    str[i] = '\0';  // null terminatör ekle

    // String'i ters çevir
    for (j = 0; j < i / 2; j++) {
        temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}
