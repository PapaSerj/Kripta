#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

void main()
{
    SetConsoleOutputCP(1251);  // Устанавливаем русскую кодировку

    cout << "Меню:" << endl;
    cout << "1)Зашифровать текст" << endl;
    cout << "2)Расшифровать текст" << endl;
    cout << "3)Атака по открытому тексту" << endl;
    cout << "4)Атака по шифрованному тексту" << endl;
    cout << "5)Интеграция со словарем" << endl;

    while (1) {
        cout << '\n' << "Выбирите действие" << endl;
        int act, shift;
        int max_shift = 0;
        int shift_counts[26] = { 0 };
        bool found;
        string str, str_new, str_tmp;
        string dictionary[] = { "banana", "apple", "pear", "champignon", "lemon", "kiwi" };
        cin >> act;
        switch (act) {
        case 1:
            cout << "Введите текст для шифрования: " ;
            cin >> str;
            cout << "Введите ключ от 0 до 25: " ;
            cin >> shift;
            str_new = str;
            for (char& ch : str_new) {
                if (isalpha(ch)) {
                    char base = islower(ch) ? 'a' : 'A';
                    ch = static_cast<char>((ch - base + shift) % 26 + base);
                }
            }
            cout << "Закодированная строка:" << str_new << endl;
            break;
        case 2:
            cout << "Введите текст для расшифрования: ";
            cin >> str;
            cout << "Введите ключ от 0 до 25: ";
            cin >> shift;
            str_new = str;
            for (char& ch : str_new) {
                if (isalpha(ch)) {
                    char base = islower(ch) ? 'a' : 'A';
                    ch = static_cast<char>(((ch - base - shift + 26) % 26) + base);
                }
            }
            cout << "Закодированная строка:" << str_new << endl;
            break;
        case 3:
            cout << "Введите открытый текст: ";
            cin >> str;
            cout << "Введите зашифрованный текст: ";
            cin >> str_new;

            for (size_t i = 0; i < str.length() && i < str_new.length(); ++i) {
                if (isalpha(str[i]) && isalpha(str_new[i])) {
                    char p = tolower(str[i]);
                    char c = tolower(str_new[i]);
                    int local_shift = (c - p + 26) % 26;
                    shift_counts[local_shift]++;
                }
            }

            max_shift = 0;
            for (int i = 1; i < 26; ++i) {
                if (shift_counts[i] > shift_counts[max_shift]) {
                    max_shift = i;
                }
            }
            cout << "Наиболее вероятный ключ: " << max_shift << endl;
            break;
        case 4:
            cout << "Введите зашифрованный текст: ";
            cin >> str_new;
            for (int i = 1; i < 26; ++i) {
                str_tmp = str_new;
                for (char& ch : str_tmp) {
                    if (isalpha(ch)) {
                        char base = islower(ch) ? 'a' : 'A';
                        ch = static_cast<char>((ch - base + i) % 26 + base);
                    }
                }
                cout << "Вариант №"<< i << ": " << str_tmp << endl;
            }
            break;
        case 5:
            cout << "Введите зашифрованный текст: ";
            cin >> str_new;

            found = false; // флаг удачи
            for (int i = 1; i < 26; ++i) {
                str_tmp = str_new;

                for (char& ch : str_tmp) {
                    if (isalpha(ch)) {
                        char base = islower(ch) ? 'a' : 'A';
                        ch = (ch - base + i) % 26 + base;
                    }
                }

                string lower = str_tmp;
                for (char& c : lower) c = tolower(c);

                for (string word : dictionary) {
                    if (lower.find(word) != string::npos) {
                        cout << "В словаре найдено данное слово!" << endl;
                        cout << "Текст: " << str_tmp << endl;
                        cout << "Ключ: " << i << endl;
                        found = true;
                        break;
                    }
                }

                if (found) break; // останавливаем перебор, если найдено
            }

            if (!found) {
                cout << "Соответствующего слова в словаре не найдено" << endl;
            }
            break;
        default:
            cout << "Введите допустимый номер действия." << endl;
        }

    }
}
