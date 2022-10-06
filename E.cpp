#include <algorithm>
#include <iostream>
#include <string>

struct ArrayStack {
  int ind_front = 200010;
  int size = 0;
  int* array = new int[200'100];
  int min_value = 1'010'000'000;  // for stack_of_min_l
};
void MakeWithMin(ArrayStack* stack_of_min_l, ArrayStack* stack_of_min_r);
void PushEl(int value, ArrayStack* my_stack, ArrayStack* stack_of_min_l,
            bool is_stack_of_min, bool do_printing);

void PopEl(ArrayStack* my_stack, ArrayStack* stack_of_min_l,
           ArrayStack* stack_of_min_r, bool is_stack_of_min = false,
           bool do_printing = true) {
  int stack_size = (*(my_stack)).size;
  if (stack_size > 0) {
    if (do_printing) {
      std::cout << (*(my_stack)).array[(*(my_stack)).ind_front] << std::endl;
    }
    (*(my_stack)).size--;
    if (!is_stack_of_min) {
      (*(my_stack)).ind_front--;
    }
  } else {
    if (do_printing) {
      std::cout << "error\n";
    }
  }
  if (!is_stack_of_min) {
    MakeWithMin(stack_of_min_l, stack_of_min_r);
  }
}

void MakeWithMin(ArrayStack* stack_of_min_l, ArrayStack* stack_of_min_r) {
  if ((*(stack_of_min_r)).size == 0) {
    stack_of_min_l->min_value = 1'010'000'000;
    while ((*(stack_of_min_l)).size > 0) {
      int value =
          stack_of_min_l
              ->array[stack_of_min_l->ind_front - stack_of_min_l->size + 1];
      PopEl(stack_of_min_l, stack_of_min_l, stack_of_min_l, true, false);
      if (stack_of_min_r->size > 0) {
        value =
            std::min(value, stack_of_min_r->array[stack_of_min_r->ind_front -
                                                  (stack_of_min_r->size - 1)]);
      }
      PushEl(value, stack_of_min_r, stack_of_min_r, true, false);
    }
  }
  PopEl(stack_of_min_r, stack_of_min_r, stack_of_min_r, true, false);
}

void ClearStack(ArrayStack* my_stack, ArrayStack* stack_of_min_l,
                ArrayStack* stack_of_min_r) {
  (*(my_stack)).size = 0;
  (*(my_stack)).ind_front = 200'000;

  (*(stack_of_min_l)).size = 0;
  (*(stack_of_min_l)).ind_front = 200'000;

  (*(stack_of_min_r)).size = 0;
  (*(stack_of_min_r)).ind_front = 200'000;
  stack_of_min_l->min_value = 1'010'000'000;

  std::cout << "ok\n";
}
void PrintFrontEl(ArrayStack* my_stack) {
  int stack_size = (*(my_stack)).size;
  if (stack_size > 0) {
    std::cout << (*(my_stack)).array[(*(my_stack)).ind_front] << std::endl;
  } else {
    std::cout << "error\n";
  }
}

void PrintBackEl(ArrayStack* my_stack) {
  int stack_size = (*(my_stack)).size;
  if (stack_size > 0) {
    std::cout << (*(my_stack)).array[(*(my_stack)).ind_front - stack_size + 1]
              << std::endl;
  } else {
    std::cout << "error\n";
  }
}

void PushEl(int value, ArrayStack* my_stack, ArrayStack* stack_of_min_l,
            bool is_stack_of_min = false, bool do_printing = true) {
  (*(my_stack)).size++;
  (*(my_stack)).array[(*(my_stack)).ind_front - (*(my_stack)).size + 1] = value;

  if (do_printing) {
    std::cout << "ok\n";
  }
  if (!is_stack_of_min) {
    PushEl(value, stack_of_min_l, stack_of_min_l, true, false);
    stack_of_min_l->min_value = std::min(value, stack_of_min_l->min_value);
  }
}

void PrintMin(ArrayStack* my_stack, ArrayStack* stack_of_min_l,
              ArrayStack* stack_of_min_r) {
  if ((*(my_stack)).size > 0) {
    int var_l = stack_of_min_l->min_value;
    int var_r = stack_of_min_l->min_value;
    if (stack_of_min_r->size > 0) {
      var_r = stack_of_min_r
                  ->array[stack_of_min_r->ind_front - stack_of_min_r->size + 1];
    }
    std::cout << std::min(var_l, var_r) << std::endl;
  } else {
    std::cout << "error\n";
  }
}

void ProcessInput(int number_of_commands, ArrayStack* my_stack,
                  ArrayStack* stack_of_min_l, ArrayStack* stack_of_min_r) {
  int push_el_value;
  std::string input_string;

  for (int i = 0; i < number_of_commands; i++) {
    std::cin >> input_string;
    if (input_string == "enqueue") {
      std::cin >> push_el_value;
      PushEl(push_el_value, my_stack, stack_of_min_l);
    }
    if (input_string == "dequeue") {
      PopEl(my_stack, stack_of_min_l, stack_of_min_r);
    }
    if (input_string == "size") {
      std::cout << (*(my_stack)).size << std::endl;
    }
    if (input_string == "back") {
      PrintBackEl(my_stack);
    }
    if (input_string == "front") {
      PrintFrontEl(my_stack);
    }
    if (input_string == "clear") {
      ClearStack(my_stack, stack_of_min_l, stack_of_min_r);
    }
    if (input_string == "min") {
      PrintMin(my_stack, stack_of_min_l, stack_of_min_r);
    }
  }
}
int main() {
  int number_of_commands;
  std::cin >> number_of_commands;
  ArrayStack my_stack;
  ArrayStack stack_of_min_l;
  ArrayStack stack_of_min_r;
  ProcessInput(number_of_commands, &my_stack, &stack_of_min_l, &stack_of_min_r);

  delete[] my_stack.array;
  delete[] stack_of_min_l.array;
  delete[] stack_of_min_r.array;
  return 0;
}
