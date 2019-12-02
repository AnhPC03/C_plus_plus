#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

void swapTwoElement(int &x, int &y) {
    int tmp = x;
    x = y;
    y = tmp;
}


int partition(int a[], int low, int high);
void quickSort(int a[], int low, int high) {
    if (low < high) {
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}
int partition(int a[], int low, int high) {
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (a[j] < a[high]) {
            ++i;
            swapTwoElement(a[i], a[j]);
        }
    }
    swapTwoElement(a[i+1], a[high]);
    return i+1;
}

int main() {
    int N;
    cout << "Nhap so luong so muon sinh ngau nhien: ";
    cin >> N;
    int *arr = new int[N];
    srand(time(0));
    FILE *file;
    remove("data.txt");
    file = fopen("data.txt", "a+");
    if (file != NULL) {
        for (int i = 0; i < N; ++i) {
            arr[i] = rand();
            fprintf(file, "%d", arr[i]);
            fprintf(file, " ");
        }
        fclose(file);
    } else {
        cout << "Khong the mo file";
    }
    cout << "\n";
    auto start = high_resolution_clock::now();
    quickSort(arr, 0, N-1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Thoi gian sap xep " << N << " so bang thuat toan sap xep Quick Sort la: " << duration.count() << " micro giay\n";
    return 0;
}
