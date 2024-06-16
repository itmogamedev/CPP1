#include "HeaderDll1.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

int main()
{
    std::cout << "Enter number of elements\n";
    double vecCount;
    std::cin >> vecCount;
    std::vector<double> vec(vecCount);
    std::cout << "Enter the elements via Enter\n";
    for (size_t i = 0; i < vecCount; i++)
    {
        double a;
        std::cin >> a;
        vec[i]=a;
    }
    
    std::cout << "What do you whant to do?:\n\
        1) Arithmetic mean\n\
        2) Mediana\n\
        3) Square mean\n\
        4) Dispercion\n\
        If you want to finish input 0\n";

    bool k=1;
    while (k)
    {
        int l;
        std::cin >> l;
        switch (l)
        {
        case 1:
            std::cout << "Arithmetic mean is " << srArifmet(vec) << std::endl;
            break;
        case 2:
            std::cout << "Mediana is " << Mediana(vec) << std::endl;
            break;
        case 3:
            std::cout << "Square mean is " << srKvadr(vec) << std::endl;
            break;
        case 4:
            std::cout << "Dispercion is " << Disp(vec) << std::endl;
            break;
        case 0:
            return 0;
        default:
            std::cout << "Wrong Input" << std::endl;
            break;
        }
    }




    
    
    
    
    
    


}
