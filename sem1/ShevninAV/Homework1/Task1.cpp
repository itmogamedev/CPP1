#include <iostream>

using namespace std;

int main()
{
    char vCharOverflow = CHAR_MAX;
    
    cout << vCharOverflow << endl;
    cout << (char) (vCharOverflow + 1) << endl;

    vCharOverflow = CHAR_MIN;
    
    cout << vCharOverflow << endl;
    cout << (char) (vCharOverflow - 1) << endl;

    double vDoubleOverflow = DBL_MAX;
    
    cout << vDoubleOverflow << endl;
    cout <<  vDoubleOverflow + 1 << endl;

    vDoubleOverflow = DBL_MIN;
    
    cout << vDoubleOverflow << endl;
    cout <<  vDoubleOverflow - 1 << endl;
}
