#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

void SwapElements(int* array, int ind1, int ind2) {
  int c = array[ind1];
  array[ind1] = array[ind2];
  array[ind2] = c;
}
int Partition(int* array, int start_ind, int end_ind, int pivot_ind) {
  int pivot_value = array[pivot_ind];
  int left = start_ind;
  int right = end_ind;
  while (true) {
    while (array[left] < pivot_value) {
      ++left;
    }
    while (array[right] > pivot_value) {
      --right;
    }
    if (left >= right) {
      return right;
    }
    if (array[left] != array[right]) {
      SwapElements(array, left, right);
    }
    ++left;
    --right;
  }
}
int Median(int* array, int s, int e, int m) {
  if (s + 1 == e) {
    if (array[e] > array[s]) {
      SwapElements(array, e, s);
    }
    return e;
  }
  if (array[s] > array[m]) {
    if (array[e] > array[s]) {
      SwapElements(array, m, s);
      return m;
    }
    if (array[m] >= array[e]) {
      SwapElements(array, s, e);
      return m;
    }
    SwapElements(array, s, e);
    SwapElements(array, s, m);
    return m;
  }
  if (array[e] >= array[m]) {
    return m;
  }
  if (array[e] >= array[s]) {
    SwapElements(array, e, m);
    return m;
  }
  SwapElements(array, m, e);
  SwapElements(array, s, m);
  return m;
}

void QuickSort(int* array, int start_ind, int end_ind) {
  if (start_ind < end_ind) {
    int s =
        start_ind + (end_ind - start_ind) / 20 *
                        abs((end_ind - start_ind + array[start_ind] / 10) % 10);
    int e = start_ind + 1 +
            (end_ind - 1 - start_ind) / 10 *
                abs((end_ind - start_ind + array[start_ind] / 10) % 10);
    int m = s + (e - s) / 2;
    int pivot_ind = Median(array, s, e, m);
    int new_pivot_ind = Partition(array, start_ind, end_ind, pivot_ind);
    QuickSort(array, start_ind, new_pivot_ind);
    QuickSort(array, new_pivot_ind + 1, end_ind);
  }
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int length_of_array;
  cin >> length_of_array;
  int* array = new int[length_of_array];
  for (int i = 0; i < length_of_array; ++i) {
    cin >> array[i];
  }
  QuickSort(array, 0, length_of_array - 1);
  for (int i = 0; i < length_of_array; ++i) {
    cout << array[i] << ' ';
  }
  delete[] array;
  return 0;
}
