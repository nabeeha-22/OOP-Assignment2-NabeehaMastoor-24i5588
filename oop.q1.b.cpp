#include <iostream>
using namespace std;

void PrintPattern(int n, int i = 1) {
    if (i > n) return;
    for (int j = 1; j <= i; j++) {
        if (j == i) cout << n - i + 1;
        else cout << 1 << " ";
    }
    cout << endl;
    PrintPattern(n, i + 1);
}

int main() {
    int n;
    cout << "Enter any number = ";
    cin >> n;
    PrintPattern(n);
    return 0;
}
