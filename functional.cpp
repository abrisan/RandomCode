#include <vector>
#include <iostream>

/// Define a templated operator<< for outputting vector
template<typename Value>
std::ostream &operator<<(std::ostream &out, std::vector<Value> const &values)
{
  size_t i = 1;
  size_t length = values.size();
  out << "[";
  for (auto const &x:values)
  {
    out << x;
    if (length-i)
    {
      out << " , ";
    }
    ++i;
  }
  out << "]";
  return out;
}
/////////

/// Define templated Map function ///////
template<typename MapDescriptor>
void Map(std::vector<typename MapDescriptor::InitType> const &source,
	 std::vector<typename MapDescriptor::DestType> &dest)
{
  for (auto const &elem : source)
  {
    dest . push_back(
	 MapDescriptor::Transformation(elem)
    );
  }
}
/////// End Defn //////////

/// Define Right Hand Folding ////
template<typename FoldrDescriptor>
typename FoldrDescriptor::ReturnType FoldR(std::vector<typename FoldrDescriptor::SourceType> const &vec)
{
  typename FoldrDescriptor::ReturnType return_value = FoldrDescriptor::FinalValue;
  size_t i = vec.size() -1;
  for (;;)
  {
    if (!(i+1))
    {
      break;
    }
    return_value = FoldrDescriptor::FoldFunction(return_value, vec[i]);
    --i;
  }
  return return_value;
}


/// Define example structs (can support currying with primitive types) /////
/* Example : Add x to a number */
template<int X>
struct MapAddX
{
  typedef int InitType;
  typedef int DestType;
  static constexpr auto Transformation = [](int i){return i + X;};
};

/* Add all the numbers in a vector, with X as the final value */
template<int Final>
struct FoldrAdd
{
  typedef int SourceType;
  typedef int ReturnType;
  static constexpr ReturnType FinalValue = Final;
  static constexpr auto FoldFunction = [](int previous, int current){return previous + current;};
};

/// End Examples ////

/// Example main ///
int main()
{
  std::vector<int> test_vector = {1, 2, 3};
  std::vector<int> dest_vector;
  std::cout << test_vector << std::endl;
  Map<MapAddX<2>>(test_vector, dest_vector);

  std::cout << dest_vector << std::endl;

  int sum_value = FoldR<FoldrAdd<0>>(test_vector);
  std::cout << sum_value << std::endl;
}
/// End example main ///
