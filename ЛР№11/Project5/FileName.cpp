#include <Windows.h>
#include <CommCtrl.h>
#include <string>
#include <fstream>

#pragma comment(lib, "Comctl32.lib")

// Глобальні змінні
HWND g_hWnd;
HWND g_hLabel;
HWND g_hTextBox;
HWND g_hButtonCalculate;
HWND g_hButtonImport;

// Функція обробки повідомлень головного вікна
LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        // Створення елементів управління
        g_hLabel = CreateWindowW(L"STATIC", L"Результат:", WS_VISIBLE | WS_CHILD,
            20, 20, 200, 20, hWnd, NULL, NULL, NULL);

        g_hTextBox = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,
            20, 50, 100, 20, hWnd, NULL, NULL, NULL);

        g_hButtonCalculate = CreateWindowW(L"BUTTON", L"Обчислити", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            20, 80, 100, 30, hWnd, (HMENU)1, NULL, NULL);

        g_hButtonImport = CreateWindowW(L"BUTTON", L"Імпортувати", WS_VISIBLE | WS_CHILD,
            20, 120, 100, 30, hWnd, (HMENU)2, NULL, NULL);

        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) // Натиснута кнопка "Обчислити"
        {
            // Отримання введеного числа з текстового поля
            wchar_t buffer[256];
            GetWindowTextW(g_hTextBox, buffer, 256);

            // Перетворення рядка в число
            int number = _wtoi(buffer);

            // Обчислення десятків та одиниць числа
            int tens = number / 10;
            int ones = number % 10;

            // Формування результуючого рядка
            std::wstring result = L"Десятки: " + std::to_wstring(tens) + L", Одиниці: " + std::to_wstring(ones);

            // Виведення результату у мітку
            SetWindowTextW(g_hLabel, result.c_str());
        }
        else if (LOWORD(wParam) == 2) // Натиснута кнопка "Імпортувати"
        {
            // Відкриття стандартного діалогу вибору файлу
            OPENFILENAME ofn;
            wchar_t szFile[260] = L"";
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hWnd;
            ofn.lpstrFilter = L"All Files (*.*)\0*.*\0";
            ofn.lpstrFile = szFile;
            ofn.nMaxFile = sizeof(szFile);
            ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
            ofn.lpstrDefExt = L"";

            if (GetOpenFileName(&ofn))
            {
                // Відкриття вибраного файлу
                std::wifstream file(ofn.lpstrFile);
                if (file.is_open())
                {
                    // Зчитування числа з файлу
                    int number;
                    file >> number;
                    file.close();

                    // Перетворення числа в рядок
                    std::wstring numberStr = std::to_wstring(number);

                    // Виведення числа у текстове поле
                    SetWindowTextW(g_hTextBox, numberStr.c_str());
                }
            }
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Функція створення та відображення головного вікна
HWND CreateMainWindow(HINSTANCE hInstance)
{
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    // Реєстрація класу вікна
    WNDCLASS wc = {};
    wc.lpfnWndProc = MainWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);

    // Створення головного вікна
    HWND hWnd = CreateWindowEx(0, CLASS_NAME, L"Класичний додаток Windows",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 250,
        NULL, NULL, hInstance, NULL);

    // Відображення головного вікна
    ShowWindow(hWnd, SW_SHOWDEFAULT);
    UpdateWindow(hWnd);

    return hWnd;
}

// Функція обробки повідомлень
int MessageLoop()
{
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

// Функція входу в програму
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    // Створення головного вікна
    g_hWnd = CreateMainWindow(hInstance);

    // Запуск головного циклу повідомлень
    return MessageLoop();
}
