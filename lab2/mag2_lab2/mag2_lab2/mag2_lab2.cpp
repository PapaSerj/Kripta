#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <map>
using namespace std;

void calculateEntropy(const string& text) {
    map<unsigned char, int> frequency;
    int total = text.length();

    for (unsigned char ch : text) {
        frequency[ch]++;
    }

    double entropy = 0.0;
    for (auto& pair : frequency) {
        double p = static_cast<double>(pair.second) / total;
        entropy -= p * log2(p);
    }

    int uniqueCount = 0;
    for (const auto& pair : frequency) {
        if (pair.second == 1) {
            uniqueCount++;
        }
    }

    cout << "Количество уникальных символов: " << uniqueCount << endl;
    cout << "Энтропия файла: " << entropy << " бит/символ" << endl;
}




void main()
{
    SetConsoleOutputCP(1251);  // Устанавливаем русскую кодировку

    cout << "Меню" << endl;
    cout << "0) Анализ" << endl;
    cout << "Генерация файла:" << endl;
    cout << "1) Из одного символа" << endl;
    cout << "2) Случайный набор 0 и 1" << endl;
    cout << "3) Символы ASCII от 0 до 255" << endl;
    cout << "4) Символы латинского алфавита" << endl;

    while (1) {
        cout << "\nВыбирите действие" << endl;
        int act, count;
        string nameF, symbol;
        cin >> act;
        switch (act) {
        case 0: {
            cout << "Введите имя анализируемого файла:";
            cin >> nameF;
            ifstream MyReadFile(nameF);
            string line;
            getline(MyReadFile, line);
            calculateEntropy(line);
            break;
        }
        case 1: {
            cout << "Задайте имя файла:";
            cin >> nameF;
            cout << "Введите размер содержимого (кол-во символов):";
            cin >> count;
            cout << "Введите символ:";
            cin >> symbol;
            ofstream outFile(nameF, ios::binary);
            for (int i = 0; i < count; ++i) {
                outFile << symbol[0];
            }
            outFile.close();
            cout << "Файл " << nameF << " создан\n";
            break;
        }
        case 2: {
            cout << "Задайте имя файла:";
            cin >> nameF;
            cout << "Введите размер содержимого (кол-во символов):";
            cin >> count;
            ofstream outFile(nameF, ios::binary);
            for (int i = 0; i < count; ++i) {
                int start = 0, end = 1;
                int x = rand() % (end - start + 1) + start;
                outFile << static_cast<char>('0' + x);
            }
            outFile.close();
            cout << "Файл " << nameF << " создан\n";
            break;
        } 
        case 3: {
            cout << "Задайте имя файла:";
            cin >> nameF;
            cout << "Введите размер содержимого (кол-во символов):";
            cin >> count;
            ofstream outFile(nameF, ios::binary);
            for (int i = 0; i < count; ++i) {
                int start = 0, end = 255;
                int x = rand() % (end - start + 1) + start;
                unsigned char x_char = static_cast<unsigned char>(x);
                outFile << x_char;
            }
            outFile.close();
            cout << "Файл " << nameF << " создан\n";
            break;
        }
        case 4: {
            cout << "Задайте имя файла:";
            cin >> nameF;
            cout << "Введите размер содержимого (кол-во символов):";
            cin >> count;
            ofstream outFile(nameF, ios::binary);
            for (int i = 0; i < count; ++i) {
                int start = 97, end = 122;
                int x = rand() % (end - start + 1) + start;
                unsigned char x_char = static_cast<unsigned char>(x);
                outFile << x_char;
            }
            outFile.close();
            cout << "Файл " << nameF << " создан\n";
            break;
        }
        default:
            cout << "Введите допустимый номер действия." << endl;
        }

    }
}
