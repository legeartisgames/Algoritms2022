#include <cmath>
#include <iomanip>
#include <iostream>

void ReadAndProcessInput(double* noises, double* mult_noises,
                         size_t number_of_mandrakes) {
  mult_noises[0] = 1;
  for (size_t i = 0; i < number_of_mandrakes; ++i) {
    std::cin >> noises[i];
    mult_noises[i + 1] = mult_noises[i] + std::log(noises[i]);
  }
}

void ComputeAverageNoise(const double* mult_noises, size_t query_number) {
  size_t left;
  size_t right;
  double answer;
  double power;
  for (size_t i = 0; i < query_number; i++) {
    std::cin >> left >> right;
    answer = mult_noises[right + 1] - mult_noises[left];
    power = 1 / (double)(right - left + 1);
    answer = std::exp(answer * power);
    std::cout << std::setprecision(7) << answer << std::endl;
  }
}

int main() {
  size_t number_of_mandrakes;
  std::cin >> number_of_mandrakes;

  double* noises = new double[number_of_mandrakes];
  double* mult_noises = new double[number_of_mandrakes + 1];
  ReadAndProcessInput(noises, mult_noises, number_of_mandrakes);

  size_t query_number;
  std::cin >> query_number;
  ComputeAverageNoise(mult_noises, query_number);
  delete[] noises;
  delete[] mult_noises;
  return 0;
}
