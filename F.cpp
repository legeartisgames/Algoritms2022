#include <iostream>
#include <vector>

using std::vector;

void LSDSortByByte(vector<uint64_t>& shifted, vector<int>& shifted256,
                   vector<size_t>& order_of_numbers, vector<size_t>& new_order,
                   int order_of_byte) {
  const size_t kPOW8OF2 = 256;
  size_t a_size = order_of_numbers.size();
  vector<int> cnt(kPOW8OF2, 0);
  for (size_t i = 0; i < a_size; ++i) {
    if (order_of_byte > 0) {
      shifted[i] = shifted[i] >> 8;
    }
    shifted256[i] = shifted[i] & 0xFF;
    ++cnt[shifted256[i]];
  }
  vector<int> pref(kPOW8OF2, 0);
  for (size_t i = 1; i < kPOW8OF2; ++i) {
    pref[i] = pref[i - 1] + cnt[i - 1];
  }
  for (size_t i = 0; i < a_size; ++i) {
    new_order[pref[shifted256[order_of_numbers[i]]]++] = order_of_numbers[i];
  }
  order_of_numbers.swap(new_order);
}

void FulfillLSD(const uint64_t* array, vector<size_t>& order_of_numbers,
                size_t length_of_ar) {
  order_of_numbers.reserve(length_of_ar);
  vector<uint64_t> shifted;
  shifted.reserve(length_of_ar);
  vector<int> shifted256(length_of_ar, 0);

  for (size_t i = 0; i < length_of_ar; ++i) {
    shifted.push_back(array[i]);
    order_of_numbers.push_back(i);
  }

  vector<size_t> new_order(length_of_ar, 0);
  for (int i = 0; i < 7; ++i) {
    LSDSortByByte(shifted, shifted256, order_of_numbers, new_order, i);
  }
}

void ReadInput(uint64_t* array, size_t length_of_ar) {
  for (size_t i = 0; i < length_of_ar; ++i) {
    std::cin >> array[i];
  }
}
void PrintSorted(uint64_t* array, vector<size_t>& order_of_numbers,
                 size_t length_of_ar) {
  for (size_t i = 0; i < length_of_ar; ++i) {
    std::cout << array[order_of_numbers[i]] << '\n';
  }
}

int main() {
  size_t length_of_ar;
  std::cin >> length_of_ar;

  uint64_t* array = new uint64_t[length_of_ar];
  ReadInput(array, length_of_ar);

  vector<size_t> order_of_numbers;
  FulfillLSD(array, order_of_numbers, length_of_ar);
  PrintSorted(array, order_of_numbers, length_of_ar);
  delete[] array;
  return 0;
}
