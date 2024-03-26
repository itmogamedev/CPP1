#include <iostream>
#include <vector>

int main()
{
    std::vector<std::string> vec{"xaa", " ", "afd", "gdf", "agr", "", "grer", "hdf34", "gsde"};

    auto countStrInVec{
        [&vec](char startSymbol)
        {
            int counter = 0;

            for(std::string str : vec)
            {
                if (str.empty()) continue;

                if (str[0] == startSymbol) counter++;
            }

            return counter;
        }
    };

    std::cout << countStrInVec(' ');
}
