#include <algorithm>
#include <vector>
#include <cmath>

void bubbleSort(float list[], int listLength)
{
    while (listLength--)
    {
        bool swapped = false;

        for (int i = 0; i < listLength; i++)
        {
            if (list[i] > list[i + 1])
            {
                std::swap(list[i], list[i + 1]);
                swapped = true;
            }
        }

        if (swapped == false)
            break;
    }
}
float srarf(int len, float arr[]) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += arr[i];
    }
    return sum / len;
}


float median(int len, float arr[]) {
    bubbleSort(arr, len);
    if (len % 2 == 0) {
        return (arr[len / 2] + arr[len / 2 - 1]) / 2;
    }
    else {
        return arr[len / 2];
    }
}

float srkvadr(int len, float arr[]) {
    float sum = 0;
    for (int i = 0; i < len; i++) {
        sum += (arr[i] * arr[i]);
    }
    return sqrt(sum / len);
}

float dispers(int len, float arr[]) {
    int x = srarf(len, arr);
    float sum = 0;
    for (int i = 0; i < len; i++) {
        sum += (arr[i] - x) * (arr[i] - x);
    }
    return sqrt(sum / len - 1);
}