#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
void LSDSort(vector<uint64_t>& shifted, vector<int>& shifted256,
             vector<int>& order_of_numbers, vector<int>& new_order,
             int order_of_byte) {
  int a_size = (int)order_of_numbers.size();
  vector<int> cnt(256, 0);
  for (int i = 0; i < a_size; ++i) {
    if (order_of_byte > 0) {
      shifted[i] = shifted[i] >> 8;
    }
    shifted256[i] = shifted[i] & 0xFF;
    ++cnt[shifted256[i]];
  }
  vector<int> pref(256, 0);
  for (int i = 1; i < 256; ++i) {
    pref[i] = pref[i - 1] + cnt[i - 1];
  }
  for (int i = 0; i < a_size; ++i) {
    new_order[pref[shifted256[order_of_numbers[i]]]++] = order_of_numbers[i];
  }
}

int main() {
  int length_of_ar;
  cin >> length_of_ar;
  uint64_t* array = new uint64_t[length_of_ar];
  vector<int> order_of_numbers;
  order_of_numbers.reserve(length_of_ar);
  vector<uint64_t> shifted;
  shifted.reserve(length_of_ar);
  vector<int> shifted256(length_of_ar, 0);
  for (int i = 0; i < length_of_ar; ++i) {
    cin >> array[i];
    shifted.push_back(array[i]);
    order_of_numbers.push_back(i);
  }
  vector<int> new_order(length_of_ar, 0);
  for (int i = 0; i < 7; ++i) {
    if (i % 2 == 0) {
      LSDSort(shifted, shifted256, order_of_numbers, new_order, i);
    } else {
      LSDSort(shifted, shifted256, new_order, order_of_numbers, i);
    }
  }
  for (int i = 0; i < length_of_ar; ++i) {
    cout << array[new_order[i]] << '\n';
  }
  delete[] array;
  return 0;
}
