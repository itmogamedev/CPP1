#include "GameInfo.h"
#include "Help.h"
#include <windows.h>
#include <ShellAPI.h>
#pragma comment(lib,"shell32")

using namespace std;

    
void GameInfo()
{ 
    LPCWSTR open = L"open";
    LPCWSTR url = L"https://youtu.be/dQw4w9WgXcQ?si=3SPKElEZHfXQXglg";
    ShellExecute(NULL, open, url, 0, 0, SW_SHOWNORMAL);
    isMenuActive = 1;
}