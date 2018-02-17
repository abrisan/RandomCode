#ifndef AB_FUNCTIONAL_HELPERS
#define AB_FUNCTIONAL_HELPERS

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

template<int CompareTo>
bool compare(int i)
{
  return i == CompareTo;
}

template<int CompareTo>
struct EqualsFilter
{
  typedef int ElemType;
  static constexpr auto Predicate = &compare<CompareTo>;
};

/// Define a templated operator<< for outputting vector
template<typename Value>
inline std::ostream &operator<<(std::ostream &out, std::vector<Value> const &values)
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


#endif
