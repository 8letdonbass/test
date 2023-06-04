#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

std::string myReplace(const std::string& str, size_t pos, size_t len, const char* s, size_t n) {
    std::string result = str;
    result.replace(pos, len, s, n);
    return result;
}

int countLatinAndCyrillicLetters(const std::string& str) {
    int count = 0;
    for (char c : str) {
        if (isalpha(c) && (islower(c) || isupper(c))) {
            count++;
        }
    }
    return count;
}

bool checkConditions(const std::string& str) {
    bool hasLatinLetter = false;
    bool hasCyrillicLetter = false;

    for (char c : str) {
        if (isalpha(c) && islower(c)) {
            hasLatinLetter = true;
        }
        else if (isalpha(c) && isupper(c)) {
            hasLatinLetter = true;
        }
        else if ((c >= '\xC0' && c <= '\xFF') || (c >= '\xD0' && c <= '\xD1')) {
            hasCyrillicLetter = true;
        }

        if (hasLatinLetter && hasCyrillicLetter) {
            return true;
        }
    }

    return false;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::string str;
    std::cout << "������ �����: ";
    std::getline(std::cin, str);

    size_t pos = 0;
    size_t len = 0;
    char s[100];
    size_t n = 0;

    std::cout << "������ �������� ��� pos: ";
    std::cin >> pos;
    std::cout << "������ �������� ��� len: ";
    std::cin >> len;
    std::cout << "������ ����� s: ";
    std::cin.ignore();
    std::cin.getline(s, 100);
    std::cout << "������ �������� ��� n: ";
    std::cin >> n;

    std::string replacedStr = myReplace(str, pos, len, s, n);
    std::cout << "�������� �����: " << replacedStr << std::endl;

    int letterCount = countLatinAndCyrillicLetters(str);
    std::cout << "�������� ������� ���������� � ��������� ����: " << letterCount << std::endl;

    bool conditionsMet = checkConditions(str);
    if (conditionsMet) {
        std::cout << "����� ����������� ������." << std::endl;
    }
    else {
        std::cout << "����� �� ����������� ������." << std::endl;
    }

    std::ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
        outputFile << "�����: " << str << std::endl;
        outputFile << "�������� �����: " << replacedStr << std::endl;
        outputFile << "�������� ������� ���������� � ��������� ����: " << letterCount << std::endl;

        if (conditionsMet) {
            outputFile << "����� ����������� ������." << std::endl;
        }
        else {
            outputFile << "����� �� ����������� ������." << std::endl;
        }

        outputFile.close();
        std::cout << "���������� ������ ������� � ���� output.txt." << std::endl;
    }
    else {
        std::cout << "������� �������� �����." << std::endl;
    }

    return 0;
}
