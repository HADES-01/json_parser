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

    class JsonValue
    {
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

    public:
        virtual std::string str(int indent) { return "null"; };
        virtual std::string describe(int indent = 0)
        {
            return to_string(type());
        }
        virtual JsonType type() { return JsonType::Null; };
        virtual json &operator[](const std::string &)
        {
            throw std::runtime_error("JsonValue of type " + to_string(type()) + " is not string-subscriptable.\n Avoid undefined behaviour by using type().");
            // return this;
        }
        virtual json &operator[](const size_t &)
        {
            throw std::runtime_error("JsonValue of type " + to_string(type()) + " is not array-subscriptable.\n Avoid undefined behaviour by using type().");
            // return nullptr;
        }
        friend std::ostream &operator<<(std::ostream &os, JsonValue *obj)
        {
            return os << obj->str(0);
        }
        void to_file(std::string path)
        {
            try
            {
                std::ofstream ofs(path);
                ofs << str(0);
                std::cout << "Written to file-" + path << "\n";
            }
            catch (std::exception &e)
            {
                std::cout << e.what();
            }
        }

        virtual std::string& get_string()
        {
            throw std::runtime_error("Not a string type.");
        }

        virtual double& get_double()
        {
            throw std::runtime_error("Not a double type.");
        }

        virtual bool& get_bool()
        {
            throw std::runtime_error("Not a bool type.");
        }

        virtual ~JsonValue() {}
    };
}
