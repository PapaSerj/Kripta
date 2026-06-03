#include <windows.h>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void generateKeyFile(const string& filename, size_t size, unsigned int seed = 12345) {
    const unsigned int a = 1664525;
    const unsigned int c = 1013904223;
    const unsigned int m = 1u << 31;

    unsigned int x = seed;

    ofstream fout(filename, ios::binary);
    if (!fout) {
        cerr << "Не удалось создать файл ключа.\n";
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        x = (a * x + c) % m;
        char byte = static_cast<char>(x & 0xFF); // Младший байт
        fout.put(byte);
    }

    fout.close();
    cout << "Файл ключа создан: " << filename << endl;
}

void vernamCipherFile(const string& inputFile, const string& keyFile, const string& outputFile) {
    ifstream finText(inputFile, ios::binary);
    ifstream finKey(keyFile, ios::binary);
    ofstream fout(outputFile, ios::binary);

    if (!finText || !finKey || !fout) {
        cerr << "Ошибка при открытии файлов.\n";
        return;
    }

    char chText, chKey;
    while (finText.get(chText) && finKey.get(chKey)) {
        fout.put(chText ^ chKey);  // Побитовый XOR
    }

    finText.close();
    finKey.close();
    fout.close();
}

void rc4(const string& inputFile, const string& keyStr, const string& outputFile) {
    vector<unsigned char> S(256);
    vector<unsigned char> K(256);

    // Инициализация S и K
    for (int i = 0; i < 256; ++i) {
        S[i] = i;
        K[i] = keyStr[i % keyStr.length()];
    }

    // Перестановка S (алгоритм KSA)
    int j = 0;
    for (int i = 0; i < 256; ++i) {
        j = (j + S[i] + K[i]) % 256;
        swap(S[i], S[j]);
    }

    ifstream fin(inputFile, ios::binary);
    ofstream fout(outputFile, ios::binary);
    if (!fin || !fout) {
        cerr << "Ошибка открытия файлов RC4.\n";
        return;
    }

    int i = 0;
    j = 0;
    char data;
    while (fin.get(data)) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        int t = (S[i] + S[j]) % 256;
        int k = S[t];
        fout.put(data ^ k);
    }

    fin.close();
    fout.close();
}

int main() {

    SetConsoleOutputCP(1251);  // Устанавливаем русскую кодировку

    // Исходные имена файлов
    string plainFile = "plain.txt";            // Входной открытый файл
    string keyFile = "key.bin";                // Ключ, сгенерированный ЛКГ

    string encryptedFile = "cipher.bin";       // Зашифрованный файл (Вернам)
    string decryptedFile = "decrypted.txt";    // Расшифрованный файл (Вернам)

    string rc4Encrypted = "rc4_cipher.bin";    // RC4-зашифрованный файл
    string rc4Decrypted = "rc4_decrypted.txt"; // RC4-расшифрованный

    generateKeyFile(keyFile, 1024);

    vernamCipherFile(plainFile, keyFile, encryptedFile);
    cout << "Шифрование Вернама завершено: " << encryptedFile << endl;
    vernamCipherFile(encryptedFile, keyFile, decryptedFile); 
    cout << "Расшифровка Вернама завершено: " << decryptedFile << endl;

    string rc4Key = "supersekret"; // Ключ RC4 (любой текст)
    rc4(plainFile, rc4Key, rc4Encrypted);
    cout << "RC4 шифрование завершено: " << rc4Encrypted << endl;
    rc4(rc4Encrypted, rc4Key, rc4Decrypted);
    cout << "RC4 расшифрование завершено: " << rc4Decrypted << endl;

    return 0;
}