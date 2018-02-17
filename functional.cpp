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

template<typename MapDescriptor>
void Map(std::vector<typename MapDescriptor::Type> &inout)
{
  for (auto &elem : inout)
  {
    MapDescriptor::TransformNoTypeConversion(elem);
  }
}

/////// End Defn //////////

/* Daisy chaining operations */
template<typename Operation>
std::vector<typename Operation::FinalType> Execute(std::vector<typename Operation::InitType> const &vector)
{
  std::vector<typename Operation::FinalType> return_value;
  Map<Operation>(vector, return_value);
  return return_value;
}

template<typename FirstOperation, typename SecondOperation, typename... RestOperation>
std::vector<typename FirstOperation::FinalType> Execute(std::vector<typename FirstOperation::InitType> const &vector)
{
  std::vector<typename FirstOperation::DestType> interim_value;
  Map<FirstOperation>(vector, interim_value);
  return Execute<SecondOperation, RestOperation...>(interim_value);
}

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
int addX(int i)
{
  return i + X;
}

template<int X>
void addXRef(int &i)
{
  i += X;
}

int addTwo(int current, int previous)
{
  return current + previous;
}

template<int X>
struct MapAddX
{
  typedef int InitType;
  typedef int DestType;
  static constexpr auto Transformation = &addX<X>;
};

template<int X>
struct MapSimpleAdd
{
  typedef int Type;
  static constexpr auto TransformNoTypeConversion = &addXRef<X>;
};

/* Add all the numbers in a vector, with X as the final value */
template<int Final>
struct FoldrAdd
{
  typedef int SourceType;
  typedef int ReturnType;
  static constexpr ReturnType FinalValue = Final;
  static constexpr auto FoldFunction = &addTwo;
};

/// End Examples ////


/* Special Structs for daisy-chaining */
struct AddOne
{
  typedef int InitType;
  typedef int DestType;
  typedef int FinalType;
  static constexpr auto Transformation = &addX<1>;
};

struct AddTwo
{
  typedef int InitType;
  typedef int DestType;
  typedef int FinalType;
  static constexpr auto Transformation = &addX<2>;
};

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
}
/// End example main ///
