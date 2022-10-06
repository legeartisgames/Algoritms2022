#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

int BinarySearch(vector<int>& vec, int target) {
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

int main() {
  int amount_of_numbers;
  cin >> amount_of_numbers;
  int first_k;
  cin >> first_k;
  unsigned long long int previous_el;
  cin >> previous_el;
  vector<int> first_numbers;
  int coef;
  cin >> coef;
  int addition;
  cin >> addition;
  unsigned long long int cur_number;
  for (int i = 0; i < amount_of_numbers; ++i) {
    cur_number = (coef * previous_el + addition) % (1073741824);
    if (i < first_k ||
        (!first_numbers.empty() && (int)cur_number < first_numbers.back())) {
      first_numbers.insert(
          first_numbers.begin() + BinarySearch(first_numbers, cur_number),
          (int)cur_number);
    }
    if ((int)first_numbers.size() > first_k) {
      first_numbers.resize(first_k);
    }
    previous_el = cur_number;
  }
  for (int i = 0; i < first_k; ++i) {
    cout << first_numbers[i] << ' ';
  }
  return 0;
}
