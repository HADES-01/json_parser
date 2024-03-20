#pragma once
#include "value/value.hpp"

namespace hades
{
    class json
    {
        std::shared_ptr<JsonValue> data;

    public:
        json();

        template <typename T>
        json(T val)
        {
            throw std::runtime_error("Type not supported.");
        }

        template <typename T>
        json(std::initializer_list<T> val);

        json(std::unordered_map<std::string, json> val);

        json(std::vector<json>);

        json(std::initializer_list<std::pair<std::string, json>>);

        json &operator=(JsonValue *val)
        {
            if (!val)
                val = new JsonValue();
            this->data.reset(val);
            return *this;
        }

        template <typename T>
        T& get() { throw std::runtime_error("Type not deduced."); }

        json &
        operator[](std::string a)
        {
            return data.get()[0][a];
        }

        json &operator[](size_t idx)
        {
            return data.get()[0][idx];
        }

        bool operator!=(json &a) { return a.data != data; }

        void to_file(std::string path) { data->to_file(path); }

        std::string str(int indent = 0) { return data->str(indent); }
        std::string describe(int indent = 0) { return data->describe(indent); }

        friend std::ostream &operator<<(std::ostream &os, json &j)
        {
            return os << j.data.get();
        }
    };

    template <>
    double& json::get()
    {
        return (*data).get_double();
    }

    template <>
    bool& json::get()
    {
        return (*data).get_bool();
    }
    template <>
    std::string& json::get() { return (*data).get_string(); }
}
