#include <iostream>

using namespace std;

int* f_min(int* M, int u) {  //нахождение минимального элемента на участке от u до конца
    int min = u;  //пусть начало участка - минимальный элемент
    for (int i = u; i < 8; i++)
        if (M[i] < M[min]) min = i;  // определяем минимальный элемент
    int* p = &M[min];  //указатель на минимальный элемент массива
    return p;
}

void sort(int* in) {
    int n = 8;  // длина массива
    for (int i = 0; i < n - 1; i++) {
        int* p = f_min(in, i);
        int c = *p; *p = in[i]; in[i] = c;  //"правило трех стаканов"
    }
}

int main() {
    int M[8] = { 1,6,-2,7,3,5,-6,9 };  // начальные данные
    cout << "Before:" << endl;
    for (int i = 0; i < 8; i++)  //вывод
        cout << M[i] << " ";
    cout << endl << "After:" << endl;
    sort(M);  //сортировка
    for (int i = 0; i < 8; i++)  //вывод результата
        cout << M[i] << " ";
}
