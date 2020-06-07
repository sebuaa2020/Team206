// Generated by gencpp from file waterplus_map_tools/GetWaypointByIndexRequest.msg
// DO NOT EDIT!


#ifndef WATERPLUS_MAP_TOOLS_MESSAGE_GETWAYPOINTBYINDEXREQUEST_H
#define WATERPLUS_MAP_TOOLS_MESSAGE_GETWAYPOINTBYINDEXREQUEST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace waterplus_map_tools
{
template <class ContainerAllocator>
struct GetWaypointByIndexRequest_
{
  typedef GetWaypointByIndexRequest_<ContainerAllocator> Type;

  GetWaypointByIndexRequest_()
    : index(0)  {
    }
  GetWaypointByIndexRequest_(const ContainerAllocator& _alloc)
    : index(0)  {
  (void)_alloc;
    }



   typedef int32_t _index_type;
  _index_type index;





  typedef boost::shared_ptr< ::waterplus_map_tools::GetWaypointByIndexRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::waterplus_map_tools::GetWaypointByIndexRequest_<ContainerAllocator> const> ConstPtr;

}; // struct GetWaypointByIndexRequest_

typedef ::waterplus_map_tools::GetWaypointByIndexRequest_<std::allocator<void> > GetWaypointByIndexRequest;

typedef boost::shared_ptr< ::waterplus_map_tools::GetWaypointByIndexRequest > GetWaypointByIndexRequestPtr;
typedef boost::shared_ptr< ::waterplus_map_tools::GetWaypointByIndexRequest const> GetWaypointByIndexRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::waterplus_map_tools::GetWaypointByIndexRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::waterplus_map_tools::GetWaypointByIndexRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace waterplus_map_tools

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'waterplus_map_tools': ['/home/leopord/demo_ws/src/waterplus_map_tools/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::waterplus_map_tools::GetWaypointByIndexRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::waterplus_map_tools::GetWaypointByIndexRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::waterplus_map_tools::GetWaypointByIndexRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::waterplus_map_tools::GetWaypointByIndexRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::waterplus_map_tools::GetWaypointByIndexRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::waterplus_map_tools::GetWaypointByIndexRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::waterplus_map_tools::GetWaypointByIndexRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "483eea06cdc3e559421ee31116d0f3b9";
  }

  static const char* value(const ::waterplus_map_tools::GetWaypointByIndexRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x483eea06cdc3e559ULL;
  static const uint64_t static_value2 = 0x421ee31116d0f3b9ULL;
};

template<class ContainerAllocator>
struct DataType< ::waterplus_map_tools::GetWaypointByIndexRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "waterplus_map_tools/GetWaypointByIndexRequest";
  }

  static const char* value(const ::waterplus_map_tools::GetWaypointByIndexRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::waterplus_map_tools::GetWaypointByIndexRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int32 index\n\
";
  }

  static const char* value(const ::waterplus_map_tools::GetWaypointByIndexRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::waterplus_map_tools::GetWaypointByIndexRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.index);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GetWaypointByIndexRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::waterplus_map_tools::GetWaypointByIndexRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::waterplus_map_tools::GetWaypointByIndexRequest_<ContainerAllocator>& v)
  {
    s << indent << "index: ";
    Printer<int32_t>::stream(s, indent + "  ", v.index);
  }
};

} // namespace message_operations
} // namespace ros

#endif // WATERPLUS_MAP_TOOLS_MESSAGE_GETWAYPOINTBYINDEXREQUEST_H
