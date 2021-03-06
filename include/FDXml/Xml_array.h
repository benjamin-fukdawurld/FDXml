#ifndef XML_ARRAY_H
#define XML_ARRAY_H

#include <FDXml/Xml_array_fwd.h>

#include <FDXml/XmlAttribute.h>
#include <FDXml/XmlValue.h>
#include <FDXml/XmlSerializer.h>

#include <sstream>

namespace FDXml
{
    template<size_t S>
    template<typename T>
    XmlValue internal::array_helper<S>::serialize(T &&arr, Serializer &serializer)
    {
        XmlValue result("array", serializer);
        result.setAttribute("size", std::to_string(S));
        for(size_t i = 0; i < S; ++i)
        {
            result->append_node(FDXml::serialize(arr[i], serializer).get());
        }
        return result;
    }

    template<size_t S>
    template<typename T>
    XmlValue internal::array_helper<S>::serialize(const T &arr, Serializer &serializer)
    {
        XmlValue result("array", serializer);
        result.setAttribute("size", std::to_string(S));
        for(size_t i = 0; i < S; ++i)
        {
            result->append_node(FDXml::serialize(arr[i], serializer).get());
        }
        return result;
    }

    template<size_t S>
    template<typename T>
    bool internal::array_helper<S>::unserialize(const XmlValue &val, T &arr, Serializer &serializer, std::string *err)
    {
        if(!val.isArray())
        {
            if(err)
                *err = "Value is not an array";
            return false;
        }

        if(val.size() != S)
        {
            if(err)
            {
                std::ostringstream oss;
                oss << "Value array size is " << val.size() << " while " << S << " elements was expected";
                *err = oss.str();
            }
            return false;
        }

        size_t i = 0;
        for(auto it = val.begin(), end = val.end(); it != end; ++it, ++i)
        {
            if(!FDXml::unserialize(*it, arr[i], serializer, err))
                return false;
        }

        return true;
    }

    template<typename T>
    XmlValue internal::array_helper<0>::serialize(T &&arr, size_t len, Serializer &serializer)
    {
        XmlValue result("array", serializer);
        result.setAttribute("size", std::to_string(len));
        for(size_t i = 0; i < len; ++i)
        {
            result->append_node(FDXml::serialize(arr[i], serializer).get());
        }
        return result;
    }

    template<typename T>
    XmlValue internal::array_helper<0>::serialize(const T &arr, size_t len, Serializer &serializer)
    {
        XmlValue result("array", serializer);
        result.setAttribute("size", std::to_string(len));
        for(size_t i = 0; i < len; ++i)
        {
            result->append_node(FDXml::serialize(arr[i], serializer).get());
        }
        return result;
    }

    template<typename T>
    bool internal::array_helper<0>::unserialize(const XmlValue &val, T &arr, size_t len, Serializer &serializer, std::string *err)
    {
        if(!val.isArray())
        {
            if(err)
                *err = "Value is not an array";
            return false;
        }

        if(val.size() != len)
        {
            if(err)
            {
                std::ostringstream oss;
                oss << "Value array size is " << val.size() << " while " << len << " elements was expected";
                *err = oss.str();
            }
            return false;
        }

        size_t i = 0;
        for(auto it = val.begin(), end = val.end(); it != end; ++it, ++i)
        {
            if(!FDXml::unserialize(*it, arr[i], serializer, err))
                return false;
        }

        return true;
    }


    template<typename T>
    bool internal::array_helper<0>::unserialize(const XmlValue &val, T &arr, Serializer &serializer, std::string *err)
    {
        if(!val.isArray())
        {
            if(err)
                *err = "Value is not an array";
            return false;
        }

        size_t i = 0;
        for(auto it = val.begin(), end = val.end(); it != end; ++it, ++i)
        {
            typename T::value_type tmp;
            if(!FDXml::unserialize(*it, tmp, serializer, err))
                return false;

            arr.push_back(std::move(tmp));;
        }

        return true;
    }

    template<typename T>
    XmlValue serialize(const T arr[], size_t len, Serializer &serializer)
    {
        return internal::array_helper<0>::serialize(arr, len, serializer);
    }

    template<typename T>
    bool unserialize(const XmlValue &val, T arr[], size_t len, Serializer &serializer, std::string *err)
    {
        return internal::array_helper<0>::unserialize(val, arr, len, serializer, err);
    }

    template<typename T, size_t N>
    XmlValue serialize(const T arr[], Serializer &serializer)
    {
        return internal::array_helper<N>::serialize(arr, serializer);
    }

    template<typename T, size_t N>
    XmlValue serialize(std::array<T, N> &&arr, Serializer &serializer)
    {
        return internal::array_helper<N>::serialize(arr, serializer);
    }

    template<typename T, size_t N>
    bool unserialize(const XmlValue &val, T arr[], Serializer &serializer, std::string *err)
    {
        return internal::array_helper<N>::unserialize(val, arr, serializer, err);
    }

    template<typename T, size_t N>
    XmlValue serialize(const std::array<T, N> &arr, Serializer &serializer)
    {
        return internal::array_helper<N>::serialize(arr, serializer);
    }

    template<typename T, size_t N>
    bool unserialize(const XmlValue &val, std::array<T, N> &arr, Serializer &serializer, std::string *err)
    {
        return internal::array_helper<N>::unserialize(val, arr, serializer, err);
    }

    template<template<typename, typename> typename Container, typename T, typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::vector<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::deque<T, Allocator>>::value,
    XmlValue > serialize(Container<T, Allocator> &&arr, Serializer &serializer)
    {
        return internal::array_helper<0>::serialize(arr, arr.size(), serializer);
    }

    template<template<typename, typename> typename Container, typename T, typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::vector<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::deque<T, Allocator>>::value,
    XmlValue > serialize(const Container<T, Allocator> &arr, Serializer &serializer)
    {
        return internal::array_helper<0>::serialize(arr, arr.size(), serializer);
    }

    template<template<typename, typename> typename Container, typename T, typename Allocator>
    std::enable_if_t<std::is_same<Container<T, Allocator>, std::vector<T, Allocator>>::value
                         || std::is_same<Container<T, Allocator>, std::deque<T, Allocator>>::value,
    bool> unserialize(const XmlValue &val, Container<T, Allocator> &arr, Serializer &serializer, std::string *err)
    {
        return internal::array_helper<0>::unserialize(val, arr, serializer, err);
    }
}

#endif // XML_ARRAY_H
