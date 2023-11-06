#include <iostream>

using namespace std;

struct list {  //Структура списка
    list* next;
    int value;
};

void ShowList(list* res) {  //вывод результата
    cout << endl << "Пересечение списков: ";
    for (list* tempL = res; ; tempL = tempL->next) {
        cout << tempL->value << " ";
        if (tempL->next == res) break;  //прошли весь список -> выходим
    }
    cout << endl;
}

void following(list*& ls, int value) {  // заполнение следующего элемента списка
    list* temp = new list;
    temp->next = ls;
    temp->value = value;
    if (ls->next == ls) {
        ls->next = temp;
    }
    else {
        list* tempL = ls;
        while (tempL->next != ls)
            tempL = tempL->next;
        tempL->next = temp;
    }
}

list* per(list* ls1, list* ls2) {  //определение пересечений
    int k = 0;  // ключ
    list* out = new list;  //итоговый список
    out->next = out;
    for (list* tempL2 = ls2; ; tempL2 = tempL2->next) {  //сравниваем списки
        for (list* tempL1 = ls1; ; tempL1 = tempL1->next) {
            if (tempL1->value == tempL2->value) {  //если есть пересечение, то сохраняем
                if (k == 0) {
                    out->value = tempL2->value;
                    k = 1;
                    break;
                }
                following(out, tempL2->value);
                break;
            }
            if (tempL1->next == ls1) break;  //прошли 1 список
        }
        if (tempL2->next == ls2) break;  //прошли 2 список
    }
    return out;
}

list* Сreate() {  //заполнение списка
    list* out = new list;
    out->next = out;
    int count;
    cout << "Размерность списка - ";
    cin >> count;
    cout << "Заполните список - ";
    cin >> out->value;
    for (int i = 1, val; i < count; i++) {
        cin >> val;
        following(out, val);
    }
    return out;
}

int main() {
    setlocale(0, "rus");  //ря
    list* List1 = new list;    //1 список
    cout << "Список 1:" << endl;
    List1 = Сreate();
    list* List2 = new list;  //2 список
    cout << endl << "Список 2:" << endl;
    List2 = Сreate();
    list* perList = new list;  //список пересечений
    perList = per(List1, List2);
    ShowList(perList);  //вывод результата
}
