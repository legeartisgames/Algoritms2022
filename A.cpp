#include <iostream>

bool BinarySearch(const int* begin, const int* end, int target);

void ProcessQuieries(const int* increasing_array) {
  size_t number_queries;
  std::cin >> number_queries;

  size_t begin_ind;
  size_t end_ind;
  int target_el;

  for (size_t i = 0; i < number_queries; ++i) {
    std::cin >> begin_ind >> end_ind >> target_el;
    if (BinarySearch(&increasing_array[begin_ind], &increasing_array[end_ind],
                     target_el)) {
      std::cout << "YES" << std::endl;
    } else {
      std::cout << "NO" << std::endl;
    }
  }
}

int main() {
  size_t array_length;
  std::cin >> array_length;
  int* increasing_array = new int[array_length];

  for (size_t i = 0; i < array_length; i++) {
    std::cin >> increasing_array[i];
  }
  ProcessQuieries(increasing_array);
  delete[] increasing_array;

  return 0;
}

bool BinarySearch(const int* begin, const int* end, int target) {
  int start_ind = 0;
  int finish_ind = (end - begin);
  int medium;
  while (abs(finish_ind - start_ind) > 1) {
    medium = (start_ind + finish_ind) / 2;

    if (begin[medium] > target) {
      finish_ind = medium;
    } else {
      start_ind = medium;
    }
  }

  return (begin[start_ind] == target);
}
