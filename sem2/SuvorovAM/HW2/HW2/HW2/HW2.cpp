#include <iostream>
#include "MathLibrary.h"

int main()
{
    int size;
    std::cout << "Enter size of the array: ";
    std::cin >> size;

    double* values = (double*)malloc(size * sizeof(double));

    if (values == NULL) {
        std::cout << "Memory allocation error";
        return 1;
    }

    for (int i = 0; i < size; i++) {
        std::cout << "Enter " << i+1 << " value: ";
        std::cin >> values[i];
    }

    int menu;
    double answer;

    std::cout << "\n\nChoose any action: " << std::endl;
    std::cout << "\t1. Calculate arifmetic average.\n";
    std::cout << "\t2. Calculate median.\n";
    std::cout << "\t3. Calculate standart deviation.\n";
    std::cout << "\t4. Calculate variance of numerical series.\n";
    std::cout << "\n\nYour choise: ";
    std::cin >> menu;
    switch (menu)
    {
    case 1:
        answer = calc_arifmetic_avg(values, size);
        std::cout << "\n------------\nAnswer = " << answer << "\n------------" << std::endl;
        break;
    case 2:
        answer = calc_median(values, size);
        std::cout << "\n------------\nAnswer = " << answer << "\n------------" << std::endl;
        break;
    case 3:
        answer = calс_deviation(values, size);
        std::cout << "\n------------\nAnswer = " << answer << "\n------------" << std::endl;
        break;
    case 4:
        answer = calc_variance_num_series(values, size);
        std::cout << "\n------------\nAnswer = " << answer << "\n------------" << std::endl;
        break;
    default:
        std::cout << "\nWrong input, try again." << std::endl;
        break;
    }    
    free(values);

    return 0;
}

