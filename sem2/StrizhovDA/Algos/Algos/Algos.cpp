#include <iostream>
#include <map>

int main() {
    int n, p;
    std::map<int, int> m_IntToInt;
    std::cin >> n;
    std::cin >> p;
    m_IntToInt[p] = p;
    m_IntToInt[1e18] = p;
    for (int i = 2; i <= n; i++) {
        int q;
        std::cin >> q;
        auto w = m_IntToInt.lower_bound(q);
        std::cout << (*w).second << " ";
        m_IntToInt[q] = (*w).second = q;
    }
}
