#ifndef BIGINT_SRC_BIGINT_H
#define BIGINT_SRC_BIGINT_H

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

class bigint;
bool operator< (const bigint& first, const bigint& second);

class bigint{

private:
  bool _sign;
  std::vector<uint8_t> _digits;
  friend bool operator< (const bigint&, const bigint&);

public:
  // If it is positive number _sign is +ve and vice versa
  bigint (): _digits(1, 0), _sign(1) {}

  bigint (int num){
    _sign = (num > 0);
    num = std::abs(num);
    while(num != 0 || _digits.empty()){
      _digits.push_back(num % 10);
      num /= 10;
    }
  }

  bigint (const bigint& other) = default;
  ~bigint () = default;
  bigint& operator= (const bigint& other) = default;

  // ********* HELPER FUNCTIONS **************
  bool is_sign_same(const bigint& first, const bigint& second){
    return (first._sign == second._sign);
  }

  bigint& bigint_abs(bigint& val){
    if (val._sign) val._sign = false;
    return val;
  }

  //This class simply adds two vectors
  std::vector<uint8_t> add_vectors(const std::vector<uint8_t> x, const std::vector<uint8_t> y){
    std::vector<uint8_t> first(x);
    std::vector<uint8_t> second(y);
    
    // Check if other has more digits,
    // increase the size of our vector to fit
    if (first.size() < second.size()) {
        first.resize(second.size(), 0);
    }

    bool should_carry = false;

    for (int i = 0; i < first.size(); ++i) {
        // other can have less digits than we have.
        // So if i is bigger than the amount of digits other has,
        // we consider them as zeroes.
        int other_digit = (i < second.size() ? second[i] : 0);

        // Add digits together and also add carry
        // from the previous iteration
        first[i] += other_digit + should_carry;

        // Check if current digit was overflown
        if (first[i] >= 10) {
            // Leave only the least significant digit
            first[i] %= 10;
            // Carry the overflow over to the next digit
            should_carry = true;
        } else {
            should_carry = false;
        }
    }
    // If at the last iteration we have carried,
    // we should carry to a new digit (ex. 5+5 == 10)
    if (should_carry) {
        first.push_back(1);
    }
    return first;
  }

  std::vector<uint8_t> sub_vectors(const std::vector<uint8_t> x, const std::vector<uint8_t> y){
    std::vector<uint8_t> first(x);
    std::vector<uint8_t> second(y);
    std::vector<uint8_t> diff(first.size());

    bool carry = false;

    for (size_t i = 0; i < first.size(); i ++) {
        bool need_to_carry = first[i] < (i < second.size() ? second[i] : uint8_t(0)) + uint8_t(carry);
        diff[i] = need_to_carry ? uint8_t(10) : uint8_t(0);
        diff[i] += first[i];
        diff[i] -= (i < second.size() ? second[i] : uint8_t(0));
        diff[i] -= uint8_t(carry);
        carry = need_to_carry;
    }
    first = diff;

    while (first[first.size() - 1] == 0 && first.size() > 0){
      first.pop_back();
    }
    
    return first;
  }

  // ********* ARITHMETIC OPERATORS ***********

  bigint& operator+= (const bigint& second) {
    if(is_sign_same(*this, second)){
      // addition
      _digits = add_vectors(_digits, second._digits);
    }else{
      //Taking necessary copies for convinience
      bigint left_num(*this); bigint right_num(second);

      //computing sign of the result
      if(left_num._digits.size() > right_num._digits.size()){
        _sign = left_num._sign;
      }else if(left_num._digits.size() < right_num._digits.size()){
        _sign = right_num._sign;
      }else{
        for (int i = left_num._digits.size() - 1; i >= 0; i --)
          if (left_num._digits[i] != right_num._digits[i]){
            _sign = (left_num._digits[i] > right_num._digits[i]) ? left_num._sign : right_num._sign;
            break;
          }
      }

      //proceeding subtraction
      left_num._sign = true; right_num._sign = true;
      if (left_num < right_num) std::swap(right_num, left_num);
      std::vector<uint8_t> left = left_num._digits; 
      std::vector<uint8_t> right = right_num._digits;
      _digits = sub_vectors(left, right);
    }
    return *this;
  }
  
  bigint& operator-= (const bigint& second) {
    //Taking necessary copies for convinience
    bigint left_num(*this); bigint right_num(second);
    right_num._sign = !right_num._sign;

    if(is_sign_same(left_num, right_num)){
      _digits = add_vectors(left_num._digits, right_num._digits);
    }else{
      //computing sign of the result
      if(left_num._digits.size() > right_num._digits.size()){
        _sign = left_num._sign;
      }else if(left_num._digits.size() < right_num._digits.size()){
        _sign = right_num._sign;
      }else{ // if both of their size is equal check last digit
        for (int i = left_num._digits.size() - 1; i >= 0; i --)
          if (left_num._digits[i] != right_num._digits[i]){
            _sign = (left_num._digits[i] > right_num._digits[i]) ? left_num._sign : right_num._sign;
            break;
          }
      }

      //proceeding subtraction
      left_num._sign = true; right_num._sign = true;
      if (left_num < right_num) std::swap(right_num, left_num);
      std::vector<uint8_t> left = left_num._digits; 
      std::vector<uint8_t> right = right_num._digits;
      _digits = sub_vectors(left, right);
    }
    return *this;
  }

  void print_vec(std::vector<uint8_t> &res){
    printf("\n[Printarr: ");
    for(int z=0; z<res.size(); z++){
      std::cout << (int)res[z];
    }
    printf("]\n");
  }

  //******************* Multiplication *************************
  bigint& operator*= (const bigint& other) {
    bool computed_sign = (_sign == other._sign); 

    //Taking necessary copies for convinience
    bigint left_num(*this); bigint right_num(other);
    left_num._sign = true; right_num._sign = true;
    if (right_num < left_num) std::swap(right_num, left_num);

    std::vector<uint8_t> left = left_num._digits; 
    std::vector<uint8_t> right = right_num._digits;
    std::vector<uint8_t> res(0);
    std::vector<uint8_t> inter(0);

    for(int i=0; i<left.size(); i++){
      int carry = 0;
      for(int k=i; k>0; k--) inter.push_back(0);
      for(int j=0; j<right.size(); j++){
        //adding buffer zeros
        int val = (left[i] * right[j]) + carry; 
        // if one of the value is 0 then we there is no future carry for that iteration
        if (left[i] || right[i]) carry = 0; 
        if (val >= 10) {
          carry = val/10;
          inter.push_back(val%10);
          //if we are in last element then append carry also into the inter
          if (carry >0 && (j == right.size() - 1)) inter.push_back(carry);
        } else {
          inter.push_back(val);
        }
      }
      res = add_vectors(res, inter);
      inter.clear();
    }

    //Finalizing the state
    _digits = res;
    _sign = computed_sign; 
    return *this;
  }

  // *********** UNARY OPERATORS **********

  bigint operator+ () const {
    return *this;
  }

  //Negation opearator
  bigint operator- () const {
    bigint cpy(*this);
    cpy._sign = !cpy._sign;
    return cpy;
  }

  bigint& operator++ () {
    return operator+=(bigint(1));
  }

  bigint& operator-- () {
    return operator-=(bigint(1));
  }

  const bigint operator++ (int) {
      bigint cpy(*this);
      operator++();
      return cpy;
  }

  const bigint operator-- (int) {
      bigint cpy(*this);
      operator--();
      return cpy;
  }

  std::string to_string() const {
    std::string str = _sign ? "" : "-";
    for (ssize_t i = _digits.size() - 1; i >= 0; i --){
      str.push_back('0' + _digits[i]);
    }
    return str;
  }

  explicit operator bool () const {
      return _digits.size() > 1 || _digits[0] != 0;
  }

  void print_state() const{
     printf("\nstate: [%d]", _sign);
    for(int i=0; i<_digits.size(); i++){
     printf("%d",_digits[i]);
    }
    printf("\n");
  }


private:
  // Friend functions
  friend std::istream& operator >> (std::istream &is, bigint& num);
  friend std::ostream& operator << (std::ostream &os, const bigint& num);
};

bigint operator+ (const bigint& first, const bigint& second) { return bigint(first) += second; }
bigint operator- (const bigint& first, const bigint& second) { return bigint(first) -= second; }
bigint operator* (const bigint& first, const bigint& second) { return bigint(first) *= second; }

// *********** COMPARISON OPERATORS **********

bool operator< (const bigint& first, const bigint& second) {
  bool res = false;
  //if one of them is +ve or -ve, val of a is enough to decide comparison
  //and its ans is , take sign of first digit and negate it
  // eg 10<-10 false, -10<10 = true
  if(first._sign != second._sign) return !first._sign;

  //both signs are +ve
  if(first._sign && second._sign){
    if (first._digits.size() == second._digits.size()){
      // compariong number with same size
      for (int i = first._digits.size() - 1; i >= 0; i --)
        if (first._digits[i] != second._digits[i])
            return first._digits[i] < second._digits[i];

    }else{
      // comparing number with different size
      res = (first._digits.size() < second._digits.size());
    }
  }else{
    // if both sign are -ve
    if (first._digits.size() == second._digits.size()){
      // compariong number with same size
      for (int i = first._digits.size() - 1; i >= 0; i --)
        if (first._digits[i] != second._digits[i])
            return first._digits[i] > second._digits[i];
    }else{
      // comparing number with different size
      res = (first._digits.size() > second._digits.size());
    }
  }

  return res;
}

bool operator<= (const bigint& first, const bigint& second) {
    return !(second < first);
}
 
bool operator> (const bigint& first, const bigint& second) {
    return second < first;
}
 
bool operator>= (const bigint& first, const bigint& second) {
    return !(first < second);
}
 
bool operator== (const bigint& first, const bigint& second) {
  return !(first < second) && !(second < first);
}

bool operator!= (const bigint& first, const bigint& second) {
    return (first < second) || (second < first);
}

std::istream& operator>> (std::istream& is, bigint& num) {
    std::string str;
    is >> str;

    // if -ve num then update local store and trim head
    if(str[0] == '-'){
      num._sign = false;
      str.erase(str.begin());
    }
    
    //Take input as string and load digit array
    num._digits.clear();
    bool inputted_non_zero_digit = false;
    for (size_t i = 0; i < str.size(); i ++) {
        if (str[i] >= '1' && str[i] <= '9') {
            num._digits.push_back(str[i] - '0');
            inputted_non_zero_digit = true;
        } else if (str[i] == '0') {
            if (inputted_non_zero_digit){
                num._digits.push_back(0);
            }
        }else{
            break;
        }
    }
 
    /// reverse:
    for (size_t i = 0; i < num._digits.size() / 2; i ++) {
        const uint8_t tmp = num._digits[i];
        num._digits[i] = num._digits[num._digits.size() - 1 - i];
        num._digits[num._digits.size() - 1 - i] = tmp;
    }
 
    /// The case when user inputted only zeros:
    if (num._digits.size() == 0)
        num._digits.push_back(0);
 
    return is;
}

std::ostream& operator << (std::ostream &os, const bigint& num) {
  os << num.to_string();
  return os;
}


#endif /// BIGINT_SRC_BIGINT_H.