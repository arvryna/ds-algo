// Listed various binary search approaches

long int find_square_root(long int val) {
  long int root = val;
  while (true) {
    root = root / 2;
    if (root * root == val) {
      return root;
    } else if (root * root < val) {
      while (true) {
        root++;
        if (root * root == val) {
          return root;
        } else if (root * root > val) {
          return root - 1;
        }
      }
    }
  }
  return root;
}

int find_index_of_largest_element(int n, const std::vector<int> list) {
  if (list[n-2] < list[n-1]) return n-1;
  int pivot, left = 0;
  int right = n - 1;
  while (true) {
    int pivot = (left + right) / 2;
    if (list[pivot - 1] < list[pivot] && list[pivot] > list[pivot+1]) {
      break;
    } else if (list[pivot - 1] < list[pivot]) {
      left = pivot;
    } else if (list[pivot] > list[pivot+1]) {
      right = pivot;
    }
  }
  return pivot;
}

int find_singleton(int n, int list[]) {
  if (list[0] != list[1])     return list[0];
  if (list[n-2] != list[n-1]) return list[n-1];
  int pivot, left = 0;
  int right = n - 1;
  while (true) {
    pivot = (left + right) / 2;
    if (pivot % 2 == 0) {
      if (list[pivot - 1] == list[pivot]) {  // DOL
        right = pivot;  // EOL
      } else {  // DOR
        left = pivot;  // EOR
      }
    } else {
      if (list[pivot - 1] == list[pivot]) {  // DOL
        left = pivot;  // EOR
      } else {  // DOR
        right = pivot;  // EOL
      }
    }
    if (list[pivot - 1] != list[pivot] && list[pivot] != list[pivot+1]) {
      break;
    }
  }
  return list[pivot];
}

int find_index(int e, int n, const int list[]) {
  // Border cases for part 1
  if (e == list[0]) return 0;
  if (e == list[n-1]) return n-1;
  
  // Border cases for part 2
  if (e < list[0]) return 0;
  if (e > list[n-1]) return n;

  int pivot, left = 0;
  int right = n - 1;
  while (true) {
    pivot = (left + right) / 2;
    if (right == left+1) {
      pivot = left+1;
      break;
    }
    if (e == list[pivot]) {
      break;
    } else if (e > list[pivot]) {  // EOR
      left = pivot;
    } else {
      right = pivot;
    }
  }
  return pivot;
}