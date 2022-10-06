#include <iostream>
int SearchShift(const int* begin, const int* end);

int main() {
  int array_length;
  std::cin >> array_length;
  int* changed_array = new int[array_length];

  for (int i = 0; i < array_length; i++) {
    std::cin >> changed_array[i];
  }

  std::cout << SearchShift(&changed_array[0], &changed_array[array_length - 1]);
  delete[] changed_array;

  return 0;
}

int SearchShift(const int* begin, const int* end) {
  int start_ind = 0;
  int finish_ind = (end - begin);
  int medium;
  while (abs(finish_ind - start_ind) > 1) {
    medium = (start_ind + finish_ind) / 2;

    if (begin[medium] < begin[start_ind]) {
      finish_ind = medium;
    } else {
      start_ind = medium;
    }
  }
  int answer;
  if (begin[start_ind] > begin[finish_ind]) {
    answer = finish_ind;
  } else {
    answer = 0;
  }
  return answer;
}
