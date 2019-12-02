#include <iostream>

using namespace std;

void swapElement(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

int partition(int arr[], int left, int right);
void kPartition(int arr[], int result[], int left, int right, int K) {
    if (left < right) {
        int pivot = partition(arr, left, right);
        if (pivot == K-1) {
            for (int i = left; i < K+left; ++i) {
                result[i] = arr[i];
            }
        } else if (pivot > K) {
            kPartition(arr, result, left, pivot-1, K);
        } else {
            for (int i = left; i <= pivot; ++i) {
                result[i] = arr[i];
            }
            kPartition(arr, result, pivot+1, right, K-pivot-1);
        }
    }
}
int partition(int arr[], int left, int right) {
    int i = left-1;
    for (int j = left; j < right; ++j) {
        if (arr[j] < arr[right]) {
            ++i;
            swapElement(arr[j], arr[i]);
        }
    }
    swapElement(arr[right], arr[i + 1]);
    return i + 1;
}

int main()
{
    int N, K;
    printf("Nhap so so nguyen muon sinh tu dong N = ");
    scanf("%d", &N);
    printf("Nhap so so nguyen nho nhat muon in ra K = ");
    scanf("%d", &K);
    int *arr = new int[N];
    srand(time(0));
    for (int i = 0; i < N; ++i) {
        arr[i] = rand();
    }
    FILE *file;
    file = fopen("Input.txt", "w");
    for (int i = 0; i < N; ++i) {
        fprintf(file, "%d  ", arr[i]);
    }
    fclose(file);
    int *result = new int[K];
    file = fopen("Output.txt", "w");
    kPartition(arr, result, 0, N-1, K);
    printf("%d so nho nhat la:\n", K);
    for (int i = 0; i < K; ++i) {
        printf("%d  ", result[i]);
        fprintf(file, "%d ", result[i]);
    }
    fclose(file);
    delete[] arr;
    delete[] result;
    return 0;
}
