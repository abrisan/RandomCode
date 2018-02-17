#include <vector>
#include <iostream>

#include "include/helpers.h"
#include "include/functional.h"

/// Example main ///
int main()
{
  std::vector<int> test_vector = {1, 2, 3};
  std::vector<int> dest_vector;
  std::cout << "Initial Vector Is :\n";
  std::cout << test_vector << std::endl << std::endl;
  
  std::cout << "Daisy Chaining AddOne and AddTwo gives :\n";
  std::vector<int> daisy_chain = Execute<AddOne, AddTwo>(test_vector);
  
  std::cout << daisy_chain << std::endl << std::endl;
  
  
  Map<MapAddX<2>>(test_vector, dest_vector);
  
  std::cout << "Mapping Addition of 2 gives :\n";
  std::cout << dest_vector << std::endl << std::endl;
  
  std::cout << "Folding using sum and 0 base value gives :\n";
  int sum_value = FoldR<FoldrAdd<0>>(test_vector);
 
  std::cout << sum_value << std::endl << std::endl;


  std::cout << "Filtering on equality to 2 gives: \n";
  std::vector<int> filter_result = Filter<EqualsFilter<2>>(test_vector);
  std::cout << filter_result << std::endl;
  
}
/// End example main ///
