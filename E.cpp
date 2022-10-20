#include <algorithm>
#include <iostream>
#include <string>

struct ArrayStack {
  size_t ind_front = 0;
  size_t size = 0;
  size_t capacity = 1;

  int* array = new int[capacity];
  int min_value = 1'010'000'000;  // for stack_of_min_l
  ~ArrayStack() { delete[] array; }
};

void ExpandDataBase(ArrayStack& db) {
  int* expanded_array = new int[2 * db.capacity];
  size_t ind_front = db.ind_front;
  for (size_t i = ind_front; i < db.capacity; ++i) {
    expanded_array[i - ind_front] = db.array[i];
  }
  delete[] db.array;
  db.array = expanded_array;
  db.ind_front = 0;
  db.capacity *= 2;
}

void MakeWithMin(ArrayStack* stack_of_min_l, ArrayStack* stack_of_min_r);
bool EnqEl(int value, ArrayStack* my_stack, ArrayStack* stack_of_min_l,
           bool is_stack_of_min);

bool DeqEl(ArrayStack* my_stack, ArrayStack* stack_of_min_l,
           ArrayStack* stack_of_min_r, bool is_stack_of_min = false,
           bool do_printing = true) {
  if (my_stack->size == 0) {
    return false;
  }
  if (do_printing) {
    std::cout << my_stack->array[my_stack->ind_front] << std::endl;
  }
  --my_stack->size;
  if (!is_stack_of_min) {
    ++my_stack->ind_front;
  }
  if (!is_stack_of_min) {
    MakeWithMin(stack_of_min_l, stack_of_min_r);
  }
  return true;
}

void MakeWithMin(ArrayStack* stack_of_min_l, ArrayStack* stack_of_min_r) {
  if (stack_of_min_r->size == 0) {
    stack_of_min_l->min_value = 1'010'000'000;
    while (stack_of_min_l->size > 0) {
      int value =
          stack_of_min_l
              ->array[stack_of_min_l->ind_front + stack_of_min_l->size - 1];
      DeqEl(stack_of_min_l, stack_of_min_l, stack_of_min_l, true, false);
      if (stack_of_min_r->size > 0) {
        value =
            std::min(value, stack_of_min_r->array[stack_of_min_r->ind_front +
                                                  (stack_of_min_r->size - 1)]);
      }
      EnqEl(value, stack_of_min_r, stack_of_min_r, true);
    }
  }
  DeqEl(stack_of_min_r, stack_of_min_r, stack_of_min_r, true, false);
}

bool ClearStack(ArrayStack* my_stack, ArrayStack* stack_of_min_l,
                ArrayStack* stack_of_min_r) {
  my_stack->size = 0;
  my_stack->ind_front = 0;

  stack_of_min_l->size = 0;
  stack_of_min_l->ind_front = 0;

  stack_of_min_r->size = 0;
  stack_of_min_r->ind_front = 0;
  stack_of_min_l->min_value = 1'010'000'000;

  return true;
}
bool PrintFrontEl(ArrayStack* my_stack) {
  if (my_stack->size > 0) {
    std::cout << my_stack->array[my_stack->ind_front] << std::endl;
    return true;
  }
  return false;
}

bool PrintBackEl(ArrayStack* my_stack) {
  size_t stack_size = my_stack->size;
  if (stack_size > 0) {
    std::cout << my_stack->array[my_stack->ind_front - stack_size + 1]
              << std::endl;
    return true;
  }
  return false;
}

bool EnqEl(int value, ArrayStack* my_stack, ArrayStack* stack_of_min_l,
           bool is_stack_of_min = false) {
  if (my_stack->size + my_stack->ind_front == my_stack->capacity) {
    ExpandDataBase(*my_stack);
  }
  ++my_stack->size;
  my_stack->array[my_stack->ind_front + my_stack->size - 1] = value;

  if (!is_stack_of_min) {
    EnqEl(value, stack_of_min_l, stack_of_min_l, true);
    stack_of_min_l->min_value = std::min(value, stack_of_min_l->min_value);
  }
  return true;
}

bool PrintMin(ArrayStack* my_stack, ArrayStack* stack_of_min_l,
              ArrayStack* stack_of_min_r) {
  if (my_stack->size > 0) {
    int var_l = stack_of_min_l->min_value;
    int var_r = stack_of_min_l->min_value;
    if (stack_of_min_r->size > 0) {
      var_r = stack_of_min_r
                  ->array[stack_of_min_r->ind_front + stack_of_min_r->size - 1];
    }
    std::cout << std::min(var_l, var_r) << std::endl;
    return true;
  }
  return false;
}

void CheckResult(bool result, bool inform_positive = true) {
  if (result && inform_positive) {
    std::cout << "ok\n";
  }
  if (!result) {
    std::cout << "error\n";
  }
}
void ProcessInput(size_t number_of_commands, ArrayStack* my_stack,
                  ArrayStack* stack_of_min_l, ArrayStack* stack_of_min_r) {
  int push_el_value;
  std::string input_string;

  for (size_t i = 0; i < number_of_commands; ++i) {
    std::cin >> input_string;
    if (input_string == "enqueue") {
      std::cin >> push_el_value;
      CheckResult(EnqEl(push_el_value, my_stack, stack_of_min_l));
    }
    if (input_string == "dequeue") {
      CheckResult(DeqEl(my_stack, stack_of_min_l, stack_of_min_r), false);
    }
    if (input_string == "size") {
      std::cout << my_stack->size << std::endl;
    }
    if (input_string == "back") {
      CheckResult(PrintBackEl(my_stack));
    }
    if (input_string == "front") {
      CheckResult(PrintFrontEl(my_stack), false);
    }
    if (input_string == "clear") {
      CheckResult(ClearStack(my_stack, stack_of_min_l, stack_of_min_r));
    }
    if (input_string == "min") {
      CheckResult(PrintMin(my_stack, stack_of_min_l, stack_of_min_r), false);
    }
  }
}

int main() {
  size_t number_of_commands;
  std::cin >> number_of_commands;
  ArrayStack my_stack;
  ArrayStack stack_of_min_l;
  ArrayStack stack_of_min_r;
  ProcessInput(number_of_commands, &my_stack, &stack_of_min_l, &stack_of_min_r);
  return 0;
}
