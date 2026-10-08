#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    const int n = 1000000;
    uniform_real_distribution<double> phanPhoi(-1000000, 1000000);

    for (int k = 1; k <= 10; k++) {
        mt19937_64 rng(20261008 + k);
        vector<double> a(n);

        for (int i = 0; i < n; i++) {
            a[i] = phanPhoi(rng);
        }

        if (k == 1) {
            sort(a.begin(), a.end());
        } else if (k == 2) {
            sort(a.begin(), a.end());
            reverse(a.begin(), a.end());
        }

        string tenFile = "data" + to_string(k) + ".txt";
        ofstream fout(tenFile);
        if (!fout) {
            cout << "Khong tao duoc file " << tenFile << endl;
            return 1;
        }

        // Dong dau la so phan tu, cac dong sau la gia tri.
        fout << n << '\n';
        fout << setprecision(17);
        for (int i = 0; i < n; i++) {
            fout << a[i] << '\n';
        }
        fout.close();
        if (!fout) {
            cout << "Loi ghi file " << tenFile << endl;
            return 1;
        }
        cout << "Da tao " << tenFile << endl;
    }

    return 0;
}
