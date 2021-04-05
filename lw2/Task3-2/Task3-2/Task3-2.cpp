#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "DictionaryExtensions.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (argc < 2) {
        cout << "Enter dictionary file name as second argument" << endl;
        return 1;
    }
    string dictionaryPath = argv[1];
    fstream dictionary(dictionaryPath, ios::in | ios::out);

    string buffer;
    vector<Translation> changes(0);

    string unknownWord;
    bool isAddWordMode = false;
    bool isExitMode = false;
    while (getline(cin, buffer))
    {
        if (isAddWordMode) 
        {
            isAddWordMode = false;
            if (buffer.empty())
            {
                cout << "Слово \"" << unknownWord << "\" проигнорировано" << endl;
                continue;
            }
            Translation translation;
            translation.english = unknownWord;
            translation.russians = Split(buffer, " *, *");
            cout << "Слово \"" << unknownWord << "\"";
            cout << " сохранено в словаре как \"" << buffer <<"\"." << endl;
            changes.push_back(translation);
            continue;
        }
        if (isExitMode)
        {
            if (ToLowerCase(buffer) == "y") {
                SaveChanges(dictionaryPath, changes);
                cout << "Изменения сохранены. До свидания." << endl;
                break;
            }
        }
        if (buffer == "...") 
        {
            if (changes.size() == 0) {
                break;
            }
            cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << endl;
            isExitMode = true;
            continue;
        }
        Translation translation = FindTranslation(dictionaryPath, buffer);
        if (translation.english != "")
        {
            for (auto i = translation.russians.begin(); i != translation.russians.end(); i++)
            {
                string russian = *i;
                cout << russian;
                if (i != translation.russians.end() - 1) {
                    cout << ", ";
                }
            }
            cout << endl;
        }
        else 
        {
            unknownWord = buffer;
            cout << "Неизвестное слово \"" << buffer << "\". ";
            cout << "Введите перевод или пустую строку для отказа." << endl;
            isAddWordMode = true;
        }
    }
    return 0;
}
