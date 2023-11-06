#include <iostream>

using namespace std;

int words(char* A) {  //Подсчет количества слов
    int pr = 1;  //изначально = 1 тк проверяем количество пробелов(на 2 слова 1 пробел)
    for (int i = 0; A[i] != '\0'; i++) {
        if (A[i] == ' ') pr++;
    }
    return pr;  //возвращаем количество пробелов
}

char** fun(char* A, int pr) {
    char** din = new char* [pr + 1]{};  //динамический массив
    for (int i = 0; i < pr; i++) {
        din[i] = new char[i + 3]{};
    }
    char* tmp = new char[15]{};  //массив для слова
    for (int i = 0, j = 0, k = 0; A[i] != '\0'; i++) {
        if (A[i] != ' ') {  //находим слова
            tmp[j] = A[i];
            j++;
            tmp[j] = '\0';
        }
        if ((A[i] == ' ') || (A[i + 1] == '\0')) { //если кончилось слово, то
            j = 0;
            for (int y = 0; tmp[y] != '\0'; y++) { //записываем его
                din[k][y] = tmp[y];
                din[k][y + 1] = '\0';
            }
            k++;
        }
    }
    delete[] tmp;  //освобождаем память
    return din;  //возвращаем дин массив указателей на слова
}

int main() {
    const int N = 25;  //длина массива
    char A[N] = "One two three four five";  //строка
    int pr = words(A);  //количество слов
    char** din;
    din = fun(A, pr);
    cout << "Before:" << endl;
    puts(A);
    cout << endl << "After:" << endl;
    for (int i = 0; i < pr; i++){  //вывод слов на экран
        puts(din[i]);
    }
}
