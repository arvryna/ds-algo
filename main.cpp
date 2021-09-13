#include <algorithm>
#include <vector>
#include <iostream>

bool containsDuplicate(std::vector<int>& nums) {
  std::sort(nums.begin(), nums.end());
  for(size_t i=0; i<nums.size(); i++){
    if(i != nums.size()-1 && nums[i] == nums[i+1]){
      return true;
    }
  }
  return false;
}

int main() {
    std::vector<int> vect{50, 30, 11, 20, 51};
    std::cout << containsDuplicate(vect);
    return 0;
}