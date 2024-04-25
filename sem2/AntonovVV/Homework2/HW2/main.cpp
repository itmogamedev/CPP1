#include <iostream>
#include "C:\Users\Asus\CLionProjects\Lib\library.cpp"
int main() {

    int n;
    std :: cout << "Enter the number of the elements.\n";
    std :: cin >> n;
    int arr[n];
    std :: cout << "Enter your elements.\n";
    for (int i = 0; i < n; i ++)
    {
        std :: cin >> arr[i];
    }
    std :: cout << "Select your command: 1.Average, 2.Median, 3.Mean square, 4.Dispersion.\n";
    int ans;
    std :: cin >> ans;
    if (ans == 1) std :: cout << Average(n, arr);
    if (ans == 2) std :: cout << Median(n, arr);
    if (ans == 3) std :: cout << Mean_square(n, arr);
    if (ans == 4) std :: cout << Dispersion(n, arr);

    return 0;
}
