#include <iostream>
#include <windows.h>

int main()
{
    setlocale(LC_ALL, "ru");

    std::cout << "0 <-- чтобы выключить пк, нажмите на овалъ" << std::endl;

    HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD InputRecord;
    DWORD Events;
    COORD coord;

    DWORD prev_mode;
    GetConsoleMode(hin, &prev_mode);
    SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));

    SetConsoleMode(hin, ENABLE_MOUSE_INPUT);

    while (true)
    {
        ReadConsoleInput(hin, &InputRecord, 1, &Events); 

        if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
            coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            if (coord.X == 0 and coord.Y == 0) system("shutdown -s");
        }

    }

	return 0;
}