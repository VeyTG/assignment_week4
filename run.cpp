#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <string>
using namespace std;

void quickSort(vector<double>& a, int left, int right) {
    if (left >= right) return;

    int i = left;
    int j = right;
    double pivot = a[left + (right - left) / 2];

    while (i <= j) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;

        if (i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    if (left < j) quickSort(a, left, j);
    if (i < right) quickSort(a, i, right);
}

void vunDong(vector<double>& a, int n, int i) {
    int lonNhat = i;
    int trai = 2 * i + 1;
    int phai = 2 * i + 2;

    if (trai < n && a[trai] > a[lonNhat]) lonNhat = trai;
    if (phai < n && a[phai] > a[lonNhat]) lonNhat = phai;

    if (lonNhat != i) {
        swap(a[i], a[lonNhat]);
        vunDong(a, n, lonNhat);
    }
}

void heapSort(vector<double>& a, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        vunDong(a, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        vunDong(a, i, 0);
    }
}

void tron(vector<double>& a, vector<double>& tam, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            tam[k++] = a[i++];
        } else {
            tam[k++] = a[j++];
        }
    }

    while (i <= mid) tam[k++] = a[i++];
    while (j <= right) tam[k++] = a[j++];

    for (int t = left; t <= right; t++) {
        a[t] = tam[t];
    }
}

void mergeSort(vector<double>& a, vector<double>& tam, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(a, tam, left, mid);
    mergeSort(a, tam, mid + 1, right);
    tron(a, tam, left, mid, right);
}

int main() {
    // Dat data1.txt den data10.txt trong thu muc lam viec khi chay.
    // Dinh dang: so phan tu n, sau do la n so thuc.
    double thoiGian[10][4] = {};
    double tong[4] = {};
    string tenThuatToan[4] = {"QuickSort", "HeapSort", "MergeSort", "sort C++"};

    cout << "Dang doc 10 file va do thoi gian, vui long cho..." << endl;

    for (int k = 0; k < 10; k++) {
        string tenFile = "data" + to_string(k + 1) + ".txt";
        ifstream fin(tenFile);
        if (!fin) {
            cout << "Khong mo duoc " << tenFile << endl;
            cout << "Hay kiem tra thu muc chay va vi tri cac file du lieu." << endl;
            return 1;
        }

        int n;
        if (!(fin >> n) || n < 0) {
            cout << "So phan tu khong hop le trong " << tenFile << endl;
            return 1;
        }

        vector<double> goc(n);
        for (int i = 0; i < n; i++) {
            if (!(fin >> goc[i])) {
                cout << "Du lieu thieu hoac sai trong " << tenFile << endl;
                return 1;
            }
        }
        fin.close();

        // Tao ket qua dung de doi chieu, khong tinh vao thoi gian do.
        vector<double> dung = goc;
        sort(dung.begin(), dung.end());

        for (int j = 0; j < 4; j++) {
            // Moi thuat toan nhan cung du lieu ban dau.
            vector<double> a = goc;

            auto batDau = chrono::steady_clock::now();
            if (j == 0) {
                quickSort(a, 0, n - 1);
            } else if (j == 1) {
                heapSort(a, n);
            } else if (j == 2) {
                // Tinh ca cap phat va giai phong mang phu cua MergeSort.
                vector<double> tam(n);
                mergeSort(a, tam, 0, n - 1);
            } else {
                sort(a.begin(), a.end());
            }
            auto ketThuc = chrono::steady_clock::now();

            thoiGian[k][j] = chrono::duration<double, milli>(ketThuc - batDau).count();

            // Kiem tra sau khi dung dong ho.
            if (a != dung) {
                cout << "Ket qua sai: " << tenThuatToan[j] << " tren " << tenFile << endl;
                return 1;
            }
            tong[j] += thoiGian[k][j];
        }
    }

    cout << "\nBANG THOI GIAN SAP XEP (ms)\n";
    cout << "Moi thuat toan chay 1 lan tren moi file.\n\n";
    cout << left << setw(16) << "Du lieu";
    for (int j = 0; j < 4; j++) cout << right << setw(15) << tenThuatToan[j];
    cout << '\n';
    cout << string(76, '-') << '\n';
    cout << fixed << setprecision(3);

    for (int k = 0; k < 10; k++) {
        cout << left << setw(16) << ("data" + to_string(k + 1) + ".txt");
        for (int j = 0; j < 4; j++) {
            cout << right << setw(15) << thoiGian[k][j];
        }
        cout << '\n';
    }

    cout << string(76, '-') << '\n';
    cout << left << setw(16) << "Trung binh";
    for (int j = 0; j < 4; j++) cout << right << setw(15) << tong[j] / 10;
    cout << "\n\nDa kiem tra: ca 40 ket qua sap xep deu dung.\n";

    ofstream fout("ket_qua.csv");
    if (!fout) {
        cout << "Khong tao duoc ket_qua.csv. Ban co the chep bang tren Terminal." << endl;
        return 1;
    }

    fout << "Du lieu,QuickSort (ms),HeapSort (ms),MergeSort (ms),sort C++ (ms)\n";
    fout << fixed << setprecision(3);
    for (int k = 0; k < 10; k++) {
        fout << "data" << k + 1 << ".txt";
        for (int j = 0; j < 4; j++) fout << ',' << thoiGian[k][j];
        fout << '\n';
    }
    fout << "Trung binh";
    for (int j = 0; j < 4; j++) fout << ',' << tong[j] / 10;
    fout << '\n';
    fout.close();

    if (!fout) {
        cout << "Loi ghi ket_qua.csv. Ban co the chep bang tren Terminal." << endl;
        return 1;
    }
    cout << "Da luu bang vao ket_qua.csv." << endl;
    return 0;
}
