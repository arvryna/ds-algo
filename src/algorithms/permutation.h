#ifndef PERMUTATION_SRC_PERMUTATION_H
#define PERMUTATION_SRC_PERMUTATION_H

template <size_t _size>

class permutation {

private:
  unsigned *_digits;

  void reverse(unsigned *array, int start_pos = 0) const{
    int len = _size;
    int limit = (start_pos == 0) ? (len-1)/2: ((len + start_pos) / 2);
    int end_pos = len-1;
    while (start_pos <= limit){
      std::swap(array[start_pos], array[end_pos]);
      start_pos++;
      end_pos--;
    }
  }

public:
  
  // ******** BLOCK 1 ************
  permutation (){
    _digits = new unsigned[_size];
    for(size_t i = 0; i < _size ; i++){
      _digits[i] = i;
    }
  }

  permutation (const unsigned* input){
    _digits = new unsigned[_size];
    for(size_t i = 0; i < _size; i++){
      _digits[i]= input[i];
    }
  }

  //copy constructor (create new data and copy other data)
  permutation (const permutation& other){
    _digits = new unsigned[_size];
    for(size_t i = 0; i < _size; i++){
      _digits[i]= other[i];
    }
  }

  // Assignment operator (overwrite data of souce with other)
  permutation& operator=(const permutation& other){
      for( size_t i=0; i< _size; i++){
        _digits[i] = other[i];
      }
    return *this;
  }

  ~permutation(){
    delete[] _digits;
  }

  // ******** BLOCK 2 ************

  // Applying permutation to given array 
  void operator()(unsigned* values) const{
    unsigned *_res = new unsigned[_size];

    for(int i=0; i< _size; i++){
      _res[_digits[i]] = values[i];
    }

    for(size_t i=0; i< _size; i++){
      values[i] = _res[i];
    }
  }

  // 1203 * 0123 = 1203   
  permutation inverse() const{
    unsigned *_res = new unsigned[_size];

    for(int i=0; i< _size; i++){
      _res[_digits[i]] = i;
    }

    for(size_t i=0; i<_size; i++){
      _digits[i] = _res[i];
    }

    return *this;
  }

  permutation operator* (const permutation& other) const {
    unsigned *_res = new unsigned[_size];
    for(size_t i = 0; i<_size; i++){
      _res[i] = _digits[other._digits[i]];
    }
    for(size_t i=0; i<_size; i++){
      _digits[i] = _res[i];
    }
    return *this;
  }

  permutation& operator*= (const permutation& other) {
    unsigned *_res = new unsigned[_size];
    for(size_t i = 0; i<_size; i++){
      _res[i] = _digits[other._digits[i]];
    }
    _digits = _res;
    return *this;
  }


  // ************* NEXT ******************
  //p++
  // Example 13542 -> 14235
  // In this example, i'm creating a new permutation instead of changing internal state


  permutation next() const{
    permutation<_size> p = *this;
    unsigned *array = p._digits; 
    int i = _size - 1;
    while (i > 0 && array[i - 1] >= array[i])
        i--;

    if (i <= 0){
      int s = 0;
      int e = _size-1;
      while(s<e){
        int temp = array[s];
        array[s] = array[e];
        array[e] = temp;
        s++;
        e--;
      }
      return p;
    }
    
    int j = _size - 1;
    while (array[j] <= array[i - 1])
        j--;
    
    // Swap the pivot with j
    int temp = array[i - 1];
    array[i - 1] = array[j];
    array[j] = temp;
    
    // Reverse the suffix
    j = _size - 1;
    while (i < j) {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        i++;
        j--;
    }
    
    return p;
  }

  //p++ - return cpy
  const permutation operator++ (int) {
    permutation cpy(*this); 
    ++(*this);
    return cpy;
  }

  // this should change internal state
  // ++p, return new val
  permutation& operator++ () {
    *this = next();
    return *this;
  }

  // ************* PREV ******************
  // Example -> 14235 -> 13542
  void print_arr(unsigned *arr) const{
    for(int i=0;i<_size; i++){
      std::cout << arr[i] << ",";
    }
    std::cout <<  std::endl;
  }

  permutation prev() const{
    permutation<_size> p = *this;
    unsigned *array = p._digits; 
    
    int i = _size - 1;
    while (i > 0 && array[i - 1] <= array[i])
        i--;
    
    // Are we at the first permutation already?
    if (i <= 0){
      int s = 0;
      int e = _size-1;
      while(s<e){
        int temp = array[s];
        array[s] = array[e];
        array[e] = temp;
        s++;
        e--;
      }
      return p;
    }
    
    // Let array[i - 1] be the pivot
    // Find rightmost element that is below the pivot
    int j = _size - 1;
    while (array[j] >= array[i - 1])
        j--;
    
    // Swap the pivot with j
    std::swap(array[i-1], array[j]);
    
    // Reverse the suffix
    j = _size - 1;
    while (i < j) {
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        i++;
        j--;
    }
    return p;
  }

  //p--
  const permutation operator-- (int) {
    permutation cpy(*this); 
    --(*this);
    return cpy;
  }

  // --p
  permutation& operator-- () {
    *this = prev();
    return *this;
  }

  void to_string() const{
    std::cout << "\n";
    for(int i=0; i<_size; i++){
      std::cout << _digits[i];
    }
    std::cout << "\n";
  }

  unsigned int size() const {
    return _size;
  }

  const unsigned& operator [](unsigned index) const;
};

template <size_t _size>
const unsigned& permutation<_size>::operator [](unsigned index) const {
    return _digits[index];
}

template <size_t _size>
bool operator< (const permutation<_size>& first, const permutation<_size>& second) {
  for(size_t i = 0; i <_size; i++){
    if(first[i] < second[i]){
      return true;
    }else if(first[i] > second[i]){
      return false;
    }
  }
  return false;
}

template <size_t _size>
bool operator> (const permutation<_size>& first, const permutation<_size>& second) {
  for(size_t i = 0; i <_size; i++){
    if(first[i] > second[i]){
      return true;
    }else if(first[i] < second[i]){
      return false;
    }
  }
  return false;
}

template <size_t _size>
bool operator>= (const permutation<_size>& first, const permutation<_size>& second) {
  return !(second > first); 
}

template <size_t _size>
bool operator<= (const permutation<_size> first, const permutation<_size>& second) { 
  return !(second < first); 
}

template <size_t _size>
bool operator== (const permutation<_size>& first, const permutation<_size>& second) {
  if (sizeof(first) != sizeof(second)) return false;
  for(size_t i = 0; i <_size; i++){
    if(first[i] != second[i]) return false;
  }
  return true;
}

template <size_t _size>
bool operator!= (const permutation<_size>& first, const permutation<_size>& second) {
  return !(first == second);
}

#endif /// PERMUTATION_SRC_PERMUTATION_H.
