// Generated by gencpp from file mover/Direction.msg
// DO NOT EDIT!


#ifndef MOVER_MESSAGE_DIRECTION_H
#define MOVER_MESSAGE_DIRECTION_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace mover
{
template <class ContainerAllocator>
struct Direction_
{
  typedef Direction_<ContainerAllocator> Type;

  Direction_()
    : directions()
    , counter(0)  {
    }
  Direction_(const ContainerAllocator& _alloc)
    : directions(_alloc)
    , counter(0)  {
  (void)_alloc;
    }



   typedef std::vector<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , typename ContainerAllocator::template rebind<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::other >  _directions_type;
  _directions_type directions;

   typedef int32_t _counter_type;
  _counter_type counter;





  typedef boost::shared_ptr< ::mover::Direction_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::mover::Direction_<ContainerAllocator> const> ConstPtr;

}; // struct Direction_

typedef ::mover::Direction_<std::allocator<void> > Direction;

typedef boost::shared_ptr< ::mover::Direction > DirectionPtr;
typedef boost::shared_ptr< ::mover::Direction const> DirectionConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::mover::Direction_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::mover::Direction_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::mover::Direction_<ContainerAllocator1> & lhs, const ::mover::Direction_<ContainerAllocator2> & rhs)
{
  return lhs.directions == rhs.directions &&
    lhs.counter == rhs.counter;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::mover::Direction_<ContainerAllocator1> & lhs, const ::mover::Direction_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace mover

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::mover::Direction_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::mover::Direction_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mover::Direction_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::mover::Direction_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mover::Direction_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::mover::Direction_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::mover::Direction_<ContainerAllocator> >
{
  static const char* value()
  {
    return "64e541ae8bb2db4768685ff2c7898ac4";
  }

  static const char* value(const ::mover::Direction_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x64e541ae8bb2db47ULL;
  static const uint64_t static_value2 = 0x68685ff2c7898ac4ULL;
};

template<class ContainerAllocator>
struct DataType< ::mover::Direction_<ContainerAllocator> >
{
  static const char* value()
  {
    return "mover/Direction";
  }

  static const char* value(const ::mover::Direction_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::mover::Direction_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string[] directions\n"
"int32 counter\n"
;
  }

  static const char* value(const ::mover::Direction_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::mover::Direction_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.directions);
      stream.next(m.counter);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Direction_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::mover::Direction_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::mover::Direction_<ContainerAllocator>& v)
  {
    s << indent << "directions[]" << std::endl;
    for (size_t i = 0; i < v.directions.size(); ++i)
    {
      s << indent << "  directions[" << i << "]: ";
      Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.directions[i]);
    }
    s << indent << "counter: ";
    Printer<int32_t>::stream(s, indent + "  ", v.counter);
  }
};

} // namespace message_operations
} // namespace ros

#endif // MOVER_MESSAGE_DIRECTION_H
