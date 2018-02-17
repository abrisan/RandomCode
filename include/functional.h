#ifndef AB_FUNCTIONAL_CONCEPTS
#define AB_FUNCTIONAL_CONCEPTS

#include <vector>

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


/*
  Define filtering
*/
template<typename FilterDescriptor>
std::vector<typename FilterDescriptor::ElemType> Filter(std::vector<typename FilterDescriptor::ElemType> const &vec)
{
  std::vector<typename FilterDescriptor::ElemType> return_value;

  for (auto &x : vec)
  {
    if (FilterDescriptor::Predicate(x))
    {
      return_value . push_back(x);
    }
  }

  return return_value;
}


#endif
