#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
  int number_of_mandrakes;
  std::cin >> number_of_mandrakes;

  double* noises = new double[number_of_mandrakes];
  double* mult_noises = new double[number_of_mandrakes + 1];
  mult_noises[0] = 1;
  for (int i = 0; i < number_of_mandrakes; i++) {
    std::cin >> noises[i];
    mult_noises[i + 1] = mult_noises[i] + std::log(noises[i]);
  }
  int query_number;
  std::cin >> query_number;
  int left;
  int right;
  double answer;
  double power;
  for (int i = 0; i < query_number; i++) {
    std::cin >> left >> right;
    answer = mult_noises[right + 1] - mult_noises[left];
    power = 1 / (double)(right - left + 1);
    answer = std::exp(answer * power);
    std::cout << std::setprecision(7) << answer << std::endl;
  }
  delete[] noises;
  delete[] mult_noises;
  return 0;
}
