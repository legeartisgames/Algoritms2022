#include <iostream>
#include <vector>

int BinarySearch(std::vector<int>& vec, int target) {
  int begin = 0;
  int end = vec.size() - 1;
  if (end < 0) {
    return 0;
  }
  int start_ind = 0;
  int finish_ind = (end - begin);
  int medium;
  while (finish_ind - start_ind > 1) {
    medium = (start_ind + finish_ind) / 2;

    if (vec[medium] > target) {
      finish_ind = medium;
    } else {
      start_ind = medium;
    }
  }
  int answer = start_ind + 1;
  if (target < vec[start_ind]) {
    answer--;
  }
  if (target > vec[finish_ind]) {
    answer = finish_ind + 1;
  }
  return answer;
}

struct SequenceStruct {
  SequenceStruct(int q_of_numbers, int coefficient_x, int parameter_y,
                 int seq_0, int range_k)
      : amount_of_numbers(q_of_numbers),
        coef(coefficient_x),
        addition(parameter_y),
        previous_el(seq_0),
        first_k(range_k) {}
  const unsigned long long kPOW30OF2 = 1073741824;
  int amount_of_numbers = 0;
  int coef = 0;
  int addition = 0;
  int previous_el = 0;
  int first_k = 0;

  std::vector<int> first_numbers;

  void ComputeFirstK() {
    unsigned long long int cur_number;
    for (int i = 0; i < amount_of_numbers; ++i) {
      cur_number = (coef * previous_el + addition) % kPOW30OF2;
      if (i < first_k ||
          (!first_numbers.empty() &&
           static_cast<int>(cur_number) < first_numbers.back())) {
        first_numbers.insert(
            first_numbers.begin() + BinarySearch(first_numbers, cur_number),
            static_cast<int>(cur_number));
      }
      if (static_cast<int>(first_numbers.size()) > first_k) {
        first_numbers.resize(first_k);
      }
      previous_el = cur_number;
    }
  }
  void PrintAnswer() {
    for (int i = 0; i < first_k; ++i) {
      std::cout << first_numbers[i] << ' ';
    }
  }
};

int main() {
  int amount_of_numbers;
  std::cin >> amount_of_numbers;

  int first_k;
  std::cin >> first_k;

  unsigned long long int previous_el;
  std::cin >> previous_el;
  int coef;
  std::cin >> coef;
  int addition;
  std::cin >> addition;

  SequenceStruct my_seq(amount_of_numbers, coef, addition, previous_el,
                        first_k);
  my_seq.ComputeFirstK();
  my_seq.PrintAnswer();
  return 0;
}
