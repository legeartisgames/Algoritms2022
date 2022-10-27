#include <iostream>
#include <vector>

void SwapElements(int* array, int ind1, int ind2) {
  int temp = array[ind1];
  array[ind1] = array[ind2];
  array[ind2] = temp;
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
int Median(int* array, size_t left, size_t right, size_t med) {
  if (left + 1 == right) {
    if (array[right] > array[left]) {
      SwapElements(array, right, left);
    }
    return right;
  }
  if (array[left] > array[med]) {
    if (array[right] > array[left]) {
      SwapElements(array, med, left);
      return med;
    }
    if (array[med] >= array[right]) {
      SwapElements(array, left, right);
      return med;
    }
    SwapElements(array, left, right);
    SwapElements(array, left, med);
    return med;
  }
  if (array[right] >= array[med]) {
    return med;
  }
  if (array[right] >= array[left]) {
    SwapElements(array, right, med);
    return med;
  }
  SwapElements(array, med, right);
  SwapElements(array, left, med);
  return med;
}

void QuickSort(int* array, int start_ind, int end_ind) {
  if (start_ind < end_ind) {
    const int kDivide = 10;  // suitable to randoming pivot
    int left =
        start_ind +
        (end_ind - start_ind) / (2 * kDivide) *
            abs((end_ind - start_ind + array[start_ind] / kDivide) % kDivide);
    int right =
        start_ind + 1 +
        (end_ind - 1 - start_ind) / kDivide *
            abs((end_ind - start_ind + array[start_ind] / kDivide) % kDivide);
    int median = left + (right - left) / 2;
    int pivot_ind = Median(array, left, median, right);
    int new_pivot_ind = Partition(array, start_ind, end_ind, pivot_ind);
    QuickSort(array, start_ind, new_pivot_ind);
    QuickSort(array, new_pivot_ind + 1, end_ind);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  size_t length_of_array;
  std::cin >> length_of_array;
  int* array = new int[length_of_array];
  for (size_t i = 0; i < length_of_array; ++i) {
    std::cin >> array[i];
  }

  QuickSort(array, 0, length_of_array - 1);
  for (size_t i = 0; i < length_of_array; ++i) {
    std::cout << array[i] << ' ';
  }
  delete[] array;

  return 0;
}
