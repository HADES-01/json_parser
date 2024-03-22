/**
 * @file include/value/value.hpp
 * Definition of JsonValue and JsonType
 *
 * ! Internal header file. Not to be used directly.
 */
#pragma once

#include "fstream"
#include "iostream"
#include "memory"
#include "sstream"
#include "string"
#include "unordered_map"
#include "vector"
#include <cassert>

namespace hades
{
    /**
     * @brief values of JsonType denotes the data-type of a json value.
     */
    enum JsonType
    {
        Boolean,
        Object,
        Array,
        String,
        Number,
        Null
    };

    class json;

    /**
     * @brief Defines the base structure and behaviour of a value in a json object.
     */
    class JsonValue
    {
        /**
         * @brief converts the type of a value into its corresponding string notation.
         *
         * @param type data-type of value
         * @return `std::string` corresponding string notation
         */
        std::string to_string(JsonType type)
        {
            std::string type_str;
            switch (type)
            {
            case Boolean:
            {
                type_str = "Boolean";
                break;
            }
            case Array:
            {
                type_str = "Array";
                break;
            }
            case Object:
            {
                type_str = "Object";
                break;
            }
            case Number:
            {
                type_str = "Number";
                break;
            }
            case String:
            {
                type_str = "String";
                break;
            }
            case Null:
            {
                type_str = "Null";
                break;
            }
            }
            return type_str;
        }

        /**
         * @brief Returns the data-type of the value.
         * @return JsonType data-type of the value
         */
        virtual JsonType type() { return JsonType::Null; };

    public:
        /**
         * @brief recursively serializes the json value into a string to be written to a file or outputstream.
         *
         * @param indent indentation of the current level of heirarchy (only to prettify the output).
         * @return `std::string` serialized output.
         */
        virtual std::string str(int indent = 0) { return "null"; };

        /**
         * @brief Provides a overview of the json object with data types in order to avoid undefined behaviours.
         * Espescially helpful to avoid undefined behaviours when the origin of the json object is unknown.
         *
         * @param indent indentation of the current level of heirarchy (only to prettify the output)..
         * @return `std::string` overview
         */
        virtual std::string describe(int indent = 0)
        {
            return to_string(type());
        }

        /**
         * @brief Provides js-object-like access to values of a json objects.
         *
         * @param key key in th object.
         * @return reference to the value if it exists otherwise create a new null value with `key` as key
         * @throws `std::runtime_error` if the value is not of `JsonType::Object`
         */
        virtual json &operator[](const std::string &key)
        {
            throw std::runtime_error("JsonValue of type " + to_string(type()) + " is not string-subscriptable.");
        }

        /**
         * @brief Provides array-like access to json arrays.
         *
         * @param idx index in the array
         * @return `json&` reference to the value if it exists and the `idx` is valid.
         * @throws 'std::runtime_error` if the value is not of `JsonType::Array` or if `idx` is not a valid index.
         */
        virtual json &operator[](const size_t &idx)
        {
            throw std::runtime_error("JsonValue of type " + to_string(type()) + " is not array-subscriptable.");
        }

        /**
         * @brief Easier output to the outputstream.
         */
        friend std::ostream &operator<<(std::ostream &os, JsonValue *obj)
        {
            return os << obj->str(0);
        }

        /**
         * @brief Writes a json value to file.
         *
         * @param path filename
         * @returns `bool` whether `json` object written to file or not
         */
        bool to_file(std::string path)
        {
            try
            {
                std::ofstream ofs(path);
                ofs << str(0);
            }
            catch (std::exception &e)
            {
                return false;
            }
            return true;
        }

        /**
         * @brief Get the refrence to the json string value
         *
         * @return `std::string&`
         * @throws `std::runtime_error` if the type doesn't match string
         */
        virtual std::string &get_string()
        {
            throw std::runtime_error("Not a string type.");
        }

        /**
         * @brief Get the reference to the json number value
         *
         * @return `double&`
         * @throws `std::runtime_error` if the type doesn't match double
         */
        virtual double &get_double()
        {
            throw std::runtime_error("Not a double type.");
        }

        /**
         * @brief Get the reference to the json boolean value
         *
         * @return `bool&`
         * @throws `std::runtime_error` if the type doesn't match bool
         */
        virtual bool &get_bool()
        {
            throw std::runtime_error("Not a bool type.");
        }

        /**
         * @brief Inserts an element to the array data-type.
         *
         * @param json& value to be inserted.
         * @throws `std::runtime_error` if the type doesn't match array
         */
        virtual void push_back(json &&val)
        {
            throw std::runtime_error("Not a array or string type.");
        }

        /**
         * @brief Inserts an element to the array data-type.
         *
         * @param json&& rvalue to be inserted.
         * @throws `std::runtime_error` if the type doesn't match array
         */
        virtual void push_back(json &val)
        {
            push_back(std::move(val));
        }

        /**
         * @brief Returns the size of the element. Returns `1` if the type is not iterable.
         * 
         * @return size_t size of the container 
         */
        virtual size_t size()
        {
            return 1;
        }

        virtual ~JsonValue() {}
    };
}
