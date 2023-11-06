#include <iostream>

using namespace std;

char* Str() {  //ввод строки
	char* str = (char*)malloc(sizeof(char));  //выделяем память.
	int len = 0;  //количество цифр в числе
	char ch;  //1 символ
	while (1) {
		ch = getchar();
		if (ch == ' ' || ch == '\n') {  //если цифра закончилась
			break;
		}
		if (ch == '-') {
			cout << "Ошибка";
			break;
		}
		len++;
		str = (char*)realloc(str, CHAR_BIT * len);  // расширяем память
		str[len] = ch - '0';
	}
	str[0] = len;  //в 0 элементе массива хранится длина
	return str;
}

bool length(char num1[], char num2[]) {  //какое число больше
	if (num1[0] > num2[0]) return 1;
	if (num1[0] < num2[0]) return 0;
	for (int i = 1; i <= num1[0]; i++) {  //числа с 1й цифрой
		if (num1[i] > num2[i]) return 1;
		if (num2[i] > num1[i])return 0;
	}
	return 1;
}

void razn(char num1[], char num2[], char res[]) {
	if (length(num1, num2)) {  //1 цифра > 2й
		int i = num1[0];  //длина результата
		res[0] = num1[0];  //запишем ее в 0 элемент массива
		for (int j = num2[0]; j != 0; i--, j--) {  //запишем
			if (num1[i] < num2[j]) {
				num1[i] += 10;
				num1[i - 1]--;  //уменьшаем следующий разряд
				res[i] = num1[i] + (~num2[j] + (1 << 8) + 1);  //записали вычисленную цифру
				continue;
			}
			res[i] = num1[i] + (~num2[j] + (1 << 8) + 1);//записали вычисленную цифру
		}
		for (; i != 0; i--) {  //запишем оствашиеся цифры
			res[i] = num1[i];
		}
		i++;
		for (int j = 1; res[j] == 0;) {  //убираем нули(003333 -> 3333)
			for (int k = j, s = k + 1; s <= res[0]; k++, s++)
			{
				res[k] = res[s];
			}
			res[0]--;
		}
	}
	else {  //2 > 1
		int i = num2[0];  //длина результата
		res[0] = num2[0];  //запишем ее в 0 элемент массива
		for (int j = num1[0]; j != 0; i--, j--) {
			if (num2[i] < num1[j]) {
				num2[i] += 10;
				num2[i - 1]--;  //уменьшаем следующий разряд
				res[i] = num2[i] + (~num1[j] + (1 << 8) + 1);  //записали вычисленную цифру
				continue;
			}
			res[i] = num2[i] + (~num1[j] + (1 << 8) + 1);  //записали вычисленную цифру
		}
		for (; i != 0; i--) {  //запишем оствашиеся цифры
			res[i] = num2[i];
		}
		i++;
		for (int j = 1; res[j] == 0;) {  //убираем нули(003333 -> 3333)
			for (int k = j, s = k + 1; s <= res[0]; k++, s++)
			{
				res[k] = res[s];
			}
			res[0]--;
		}
		res[1] = -res[1];
	}
}

int main() {
	setlocale(0, "rus");  //ря
	cout << "Введите два числа:" << endl;
	char* num1 = Str();
	char* num2 = Str();
	char* res = new char[CHAR_BIT * (length(num1, num2) ? num1[0] : num2[0])]{};
	razn(num1, num2, res);
	cout << endl << "Результат:     ";  //вывод результата
	for (int i = 1; i <= res[0]; i++) {
		cout << (int)res[i];
	}
	return 0;
}
