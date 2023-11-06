#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct date { //структура даты
    int day, month, year; //объявление переменных для дня, месяца и года
    void showDate() {  //функция показа даты
        cout << day << " " << month << " " << year << endl;
    }
    long int difDates(date date_) {
        return abs(day - date_.day) + 30 * abs(month - date_.month) + 365 * abs(year - date_.year);
    }
};


struct Bill { //структура счёта
    string surname; //объявление переменной для фамилии типа стринг
    int nBill; // целочисленная переменная для номера счёта
    int money; // целочисленная переменная для количества денег
    date lastChange; //переменная даты для даты последнего изменения
    void showBill() { //функция вывода
        cout << surname << " " << nBill << " " << money << " ";
        lastChange.showDate(); //вызов функции showDate
    }
};

struct Bills { // структура счетов
    Bill* A = new Bill[20]; //массив структуры с типом данных, именем структуры
    int n = 0; //целочисленная переменная для счёта количества строк
    void addBill(Bill bill) { //функция добавления счёта
        A[n++] = bill; //на строчку n+1 добавить счёт
    }
    void showTable() { //функция просмотра таблицы
        for (int i = 0; i < n; i++) { //вывод таблицы
            A[i].showBill(); //имя_переменной_структуры.имя_элемента
        }
    }
    void downloadFromFile(string& filename) { //функция загрузки таблицы из файла
        ifstream file(filename);
        if (!file) { //если файл не был найден, то выводится фраза ниже
            cout << "файл не найден" << endl;
        }
        else {
            string surname; //объявление переменной для фамилии
            int nBill, money, day, month, year; //целочисленные переменные для номера счёта, суммы денег, дня месяца года

            while (!file.eof()) { //пока файл не достигнет конца записывать в него таблицу
                file >> surname >> nBill >> money >> day >> month >> year; //считывание
                addBill({ surname, nBill, money, {day, month, year} });
            }
            file.close(); //закрытие файла
        }
    }
    void saveToFile(string& filename) { //сохранение таблицы в текстовом файле
        ofstream file(filename); //создаем объект для записи в файл
        string surname; //объявление переменной для фамилии
        int nBill, money, day, month, year; //целочисленная переменная для номера счёта, суммы денег, дня месяца года

        for (int i = 0; i < n; i++) {
            surname = A[i].surname; // запись фамилии в строку фамилии
            nBill = A[i].nBill; // запись номера счёта в строку НС
            money = A[i].money; // запись суммы денег в строку СД
            day = A[i].lastChange.day; // запись дня в строку последнего изменения даты
            month = A[i].lastChange.month; // запись месяца в строку последнего изменения даты

            year = A[i].lastChange.year; // запись года в строку последнего изменения даты

            file << surname << " " << nBill << " " << money << " " << day << " " << month << " " << year;
            if (i != n - 1)
                file << endl;
        }
        file.close(); //закрытие файла
    }

    void editBill(int n, Bill bill) { //функция изменения счёта
        A[n - 1] = bill;
    }

    void deleteBill(int number) { //функция удаления строчки (счёта)
        for (int i = number - 1; i < n; i++)
            A[i] = A[i + 1];
        n--;
    }

    void sortByNBill() { //функция сортировки по номеру счёта
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++)
                if (A[i].nBill > A[j].nBill) { //сравнивается значение номера счета и меняется местами в зависимости от результата
                    Bill temp;
                    temp = A[i];
                    A[i] = A[j];
                    A[j] = temp;
                }
    }
    void sortByMoney() { // функция сортировки по количеству денег
        for (int i = 0; i < n - 1; i++)
            for (int j = i + 1; j < n; j++)
                if (A[i].money > A[j].money) { //алгоритм как и в предыдущей функции
                    Bill temp;
                    temp = A[i];
                    A[i] = A[j];
                    A[j] = temp;
                }
    }

    Bill searchDate(date date_) { //функция поиска даты
        int minDif = INT_MAX;
        Bill currentBill;
        for (int i = 0; i < n; i++) {
            if (A[i].lastChange.difDates(date_) < minDif) {
                minDif = A[i].lastChange.difDates(date_);
                currentBill = A[i];
            }
        }
        return currentBill;
    }

    Bill searchNBill(int nBill) { //функция поиска номера счёта
        int minDif = INT_MAX;
        Bill currentBill;
        for (int i = 0; i < n; i++) {
            if (abs(A[i].nBill - nBill) < minDif) {
                minDif = abs(A[i].nBill - nBill);
                currentBill = A[i];
            }
        }
        return currentBill;
    }
    Bill searchMoney(int money) { //поиск по сумме денег на счете
        int minDif = INT_MAX;
        Bill currentBill;
        for (int i = 0; i < n; i++) {
            if (abs(A[i].money - money) < minDif) {
                minDif = abs(A[i].money - money);
                currentBill = A[i];
            }
        }
        return currentBill;
    }
    int sumOfMoney() { //функция суммирования количества денег
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += A[i].money;
        }
        return sum;
    }
};

int main() { //основная функция
    system("chcp 65001");
    Bills Table;
    Table.addBill({ "Abramson", 217, 245550,{18,04,2017} }); //добавление строчки с информацией в таблицу
    Table.addBill({ "Adamson", 103, 249134,{13,01,2011} });
    Table.addBill({ "Adderiy", 345, 179348,{15,07,2010} });
    Table.addBill({ "Addington", 550, 176034,{11,07,2000} });
    Table.addBill({ "Adrian", 747, 176971,{19,01,2010} });
    Table.addBill({ "Allford", 598, 220530,{17,02,2011} });
    int n;
    string filename = "lr_2.txt"; //расположение текстового файла
    bool state = true;
    while (state) {
        system("cls"); //очистка экрана
        cout << "1 - Добавить строку" << endl;
        cout << "2 - Посмотреть таблицу" << endl;
        cout << "3 - Убрать строку" << endl;
        cout << "4 - Редактировать" << endl;
        cout << "5 - Отсортировать строку" << endl;
        cout << "6 - Поиск строки" << endl;
        cout << "7 - Суммировать" << endl;
        cout << "8 - Сохранить" << endl;
        cout << "9 - Из файла" << endl;
        cin >> n;
        switch (n)
        {
            case 1: { //Добавление строчки
                string surname;
                int nBill, money;
                int day, month, year;
                cout << "Введите фамилию - ";
                cin >> surname;
                cout << "Введите номер счета - ";
                cin >> nBill;
                cout << "Введите сумму - ";
                cin >> money;
                cout << "Введите дату - ";
                cin >> day >> month >> year;

                Table.addBill({ surname, nBill, money, {day, month, year} });
                break;
            }
            case 2: { //Вывод таблицы
                Table.showTable();
                system("pause");
                break;
            }
            case 3: { // Удаление строчки
                int number;
                cout << "Ввести номер в списке - ";
                cin >> number;
                Table.deleteBill(number);
                system("pause");
                break;
            }
            case 4: { // Изменение
                int n;
                cout << "введите номер в списке - ";
                cin >> n;
                string surname;
                int nBill, money;
                int day, month, year;
                cout << "Введите фамилию - ";
                cin >> surname;
                cout << "Введите номер счета - ";
                cin >> nBill;
                cout << "Введите сумму - ";
                cin >> money;
                cout << "Введите дату - ";
                cin >> day >> month >> year;
                Bill bill = { surname, nBill,money,{day,month,year} };
                Table.editBill(n, bill);
                system("pause");
                break;
            }
            case 5: { //Сортировка по заданному полю (от меньшего значения к большему)
                int nField;
                cout << "1 по номеру" << endl;
                cout << "2 по сумме на счету" << endl;
                cin >> nField;
                switch (nField)
                {
                    case 1: { //Сортировка по номеру счёта
                        Table.sortByNBill();
                        break;
                    }
                    case 2: { //Сортировка по количеству денег
                        Table.sortByMoney();
                        break;
                    }

                    default:
                        cout << "Ошибка";
                        break;
                }
                system("pause");
                break;
            }

            case 6: { //Поиск по заданному полю
                int nField;
                cout << "1 по номеру счета" << endl;
                cout << "2 по количеству денег" << endl;
                cout << "3 по дате" << endl;
                cin >> nField;
                switch (nField)
                {
                    case 1: { //поиск по номеру счёта
                        int nBill;
                        cin >> nBill;
                        Table.searchNBill(nBill).showBill();
                        break;
                    }
                    case 2: { //поиск по количеству денег
                        int money;
                        cin >> money;
                        Table.searchMoney(money).showBill();
                        break;
                    }
                    case 3: { // поиск по дате
                        int day, month, year;
                        cout << "Введите день - ";
                        cin >> day;
                        cout << "Введите месяц - ";
                        cin >> month;
                        cout << "Введите год - ";
                        cin >> year;
                        Table.searchDate({ day, month,year }).showBill();
                        break;
                    }
                    default:
                        cout << "Не найден";
                        break;
                }
                system("pause");
                break;
            }
            case 7: { //Сумма всех средств, которые есть на счетах
                cout << "Сумма - " << Table.sumOfMoney() << endl;
                system("pause");
                break;
            }
            case 8: {
                Table.saveToFile(filename);
                system("pause");
                break;
            }
            case 9: {
                Table.downloadFromFile(filename);
                system("pause");
                break;
            }
            default:
                state = false;
                system("pause");
                break;
        }
    }
}
