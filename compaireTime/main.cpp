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


void bubbleSort(int a[], int N) {
    for (int i = 0; i < N-1; ++i) {
        int flag = 0;
        for (int j = 0; j < N-i-1; ++j) {
            if (a[j] > a[j+1]) {
                swapTwoElement(a[j], a[j+1]);
                flag = 1;
            }
        }
        if (flag == 0) {
            break;
        }
    }
}


void selectionSort(int a[], int N) {
    int indexOfMin;
    for (int i = 0; i < N-1; ++i) {
        indexOfMin = i;
        for (int j = i+1; j < N; ++j) {
            if (a[j] < a[indexOfMin]) {
                indexOfMin = j;
            }
        }
        swapTwoElement(a[i], a[indexOfMin]);
    }
}


void insertionSort(int a[], int N) {
    int v;
    for (int i = 1; i < N; ++i) {
        v = a[i];
        int j = i;
        while (v < a[j-1] && j > 0) {
            a[j] = a[j-1];
            --j;
        }
        a[j] = v;
    }
}


void merge(int a[], int left, int mid, int right);
void mergeSort(int a[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(a, left, mid);
        mergeSort(a, mid+1, right);
        merge(a, left, mid, right);
    }
}
void merge(int a[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid + 1 - left;
    int n2 = right - mid;
    int L[n1], R[n2];
    for (i = 0; i < n1; ++i) {
        L[i] = a[left + i];
    }
    for (j = 0; j < n2; ++j) {
        R[j] = a[mid + 1 + j];
    }
    i = j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            ++i;
        } else {
            a[k] = R[j];
            ++j;
        }
        ++k;
    }
    while (i < n1) {
        a[k] = L[i];
        ++i;
        ++k;
    }
    while (j < n2) {
        a[k] = R[j];
        ++j;
        ++k;
    }
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


void buildHeap(int a[], int N, int i);
void heapSort(int a[], int N) {
    for (int i = N/2 - 1; i > -1; --i) {
        buildHeap(a, N, i);
    }
    for (int i = N-1; i > -1; --i) {
        swapTwoElement(a[i], a[0]);
        buildHeap(a, i, 0);
    }
}
void buildHeap(int a[], int N, int i) {
    int leftChild = 2*i + 1;
    int rightChild = 2*i + 2;
    int largest = i;
    if (leftChild < N && a[leftChild] > a[largest]) {
        largest = leftChild;
    }
    if (rightChild < N && a[rightChild] > a[largest]) {
        largest = rightChild;
    }
    if (largest != i) {
        swapTwoElement(a[largest], a[i]);
        buildHeap(a, N, largest);
    }
}


int main() {
    int N;
    cout << "Nhap so luong so muon sinh ngau nhien: ";
    cin >> N;
    int *arr = new int[N];
    srand(time(0));
    FILE *file;
    file = fopen("data100k.txt", "a+");
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
    mergeSort(arr, 0, N-1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Thoi gian sap xep " << N << " so bang thuat toan sap xep Merge Sort la: " << duration.count() << " micro giay\n";

     file = fopen("data.txt", "r");
    for (int i = 0; i < N; ++i) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
    start = high_resolution_clock::now();
    quickSort(arr, 0, N-1);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Thoi gian sap xep " << N << " so bang thuat toan sap xep Quick Sort la: " << duration.count() << " micro giay\n";


    file = fopen("data.txt", "r");
    for (int i = 0; i < N; ++i) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
    start = high_resolution_clock::now();
    heapSort(arr, N);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Thoi gian sap xep " << N << " so bang thuat toan sap xep Heap Sort la: " << duration.count() << " micro giay\n\n";


    file = fopen("data.txt", "r");
    for (int i = 0; i < N; ++i) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
     start = high_resolution_clock::now();
    bubbleSort(arr, N);
     stop = high_resolution_clock::now();
     duration = duration_cast<microseconds>(stop - start);
    cout << "Thoi gian sap xep " << N << " so bang thuat toan sap xep Bubble Sort la: " << duration.count() << " micro giay\n";






    file = fopen("data.txt", "r");
    for (int i = 0; i < N; ++i) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
    start = high_resolution_clock::now();
    selectionSort(arr, N);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Thoi gian sap xep " << N << " so bang thuat toan sap xep Selection Sort la: " << duration.count() << " micro giay\n";


    file = fopen("data.txt", "r");
    for (int i = 0; i < N; ++i) {
        fscanf(file, "%d", &arr[i]);
    }
    fclose(file);
    start = high_resolution_clock::now();
    insertionSort(arr, N);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Thoi gian sap xep " << N << " so bang thuat toan sap xep Insertion Sort la: " << duration.count() << " micro giay\n";



    return 0;
}
