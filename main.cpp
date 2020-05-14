#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <cassert>

using namespace std;

/*Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n.
 * Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k (0..n-1)
 * в отсортированном массиве.
 *
 * Реализуйте стратегию выбора опорного элемента “медиана трёх”.
 * Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
*/


template<typename T = int, typename Comparator = std::greater<T>>
int posOfMedianOfThree(int *arr, int first, int second, int third, Comparator cmp = Comparator()) {
    int a = arr[first];
    int b = arr[second];
    int c = arr[third];
    int x = max(a, b, cmp);
    int y = max(a, c, cmp);
    int mid;
    if (x == y) {
        mid = max(b, c, cmp);
    } else {
        mid = min(x, y, cmp);
    }
    if (arr[first] == mid)
        return first;
    if (arr[second] == mid)
        return second;
    if (arr[third] == mid)
        return third;
}

template<typename T = int, typename Comparator = std::greater<T>>
int partition(int *arr, int left, int right, Comparator cmp = Comparator()) {
    int pivotPos = posOfMedianOfThree(arr, left + rand() % (right - left + 1), left + rand() % (right - left + 1),
                                      left + rand() % (right - left + 1), cmp);
    swap(arr[pivotPos], arr[right]);
    pivotPos = right;
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (!cmp(arr[j], arr[pivotPos])) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[pivotPos]);

    return i + 1;
}

template<typename T = int, typename Comparator = std::greater<T>>
int find_order_statistics(T *arr, const int len, const int statistics, Comparator cmp = Comparator()) {
    int left = 0;
    int right = len - 1;
    int pivot_pos = partition(arr, left, right, cmp);
    while (pivot_pos != statistics) {
        if (statistics < pivot_pos) {
            right = pivot_pos - 1;
        } else {
            left = pivot_pos + 1;
        }
        pivot_pos = partition(arr, left, right, cmp);
    }
    return arr[pivot_pos];
}

void randomTest() {
    srand(time(0));
    for (int i = 0; i < 100000; ++i) {
        int n = 1 + rand() % 15, k = rand() % n;
        // cout<<"n = "<<n<<" k = "<<k<<endl<<"array: "<<endl;
        int *a = new int[n];
        int *b = new int[n];
        for (int i = 0; i < n; ++i) {
            a[i] = b[i] = rand() % 100;
            //cout<<a[i]<<" ";
        }
//        cout<<endl;

        int q = find_order_statistics(b, n, k, std::greater<int>());
        std::sort(a, a + n);
//        for(int j = 0; j<n; j++){
//            cout<<a[j]<<" ";
//        }
//        cout<<endl;
//        cout<<endl;
//        cout << "after sort = " <<a[k]<< " partition res "<< q<<endl;
        assert (a[k] == q);
        delete[] a;
        delete[] b;
    }
    cout << "all test OK";
}

int main() {
    //randomTest();
    int n, k;
    cin>>n>>k;
    int* arr = new int[n];
    for(int i=0; i<n; i++)
        cin>>arr[i];
    cout<<find_order_statistics(arr, n, k);
    delete [] arr;
    return 0;
}
