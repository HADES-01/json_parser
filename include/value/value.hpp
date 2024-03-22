/**
 * @file include/value/value.hpp
 * @brief Definition of json.
 *
 * ! Internal header file. Not to be used directly.
 */

#pragma once
#include "value_base.hpp"
#include <cstddef>

namespace hades
{
    /**
     * @brief Wrapper for `JsonValue*` to simplify its use.
     */
    class json
    {
        // `std::shared_ptr` to `JsonValue` to avoid memory leaks
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

        /**
         * @brief Initialize a value with null if nullptr is assigned.
         */
        json &operator=(JsonValue *val)
        {
            if (!val)
                val = new JsonValue();
            this->data.reset(val);
            return *this;
        }

        /**
         * @brief Returns the reference to the raw data.
         *
         * @throws `std::runtime_error` if the data-type is not valid.
         * @tparam T type of the raw value
         * @return T&
         */
        template <typename T>
        T &get() { throw std::runtime_error("Type not deduced."); }

        /**
         * @brief Provides js-object-like access to values of a json objects.
         *
         * @param key key in th object.
         * @return reference to the value if it exists otherwise create a new null value with `key` as key
         * @throws `std::runtime_error` if the value is not of `JsonType::Object`
         */
        json &operator[](std::string a)
        {
            return data.get()[0][a];
        }

        /**
         * @brief Provides array-like access to json arrays.
         *
         * @param idx index in the array
         * @return reference to the value if it exists and the `idx` is valid.
         * @throws `std::runtime_error` if the value is not of `JsonType::Array` or if `idx` is not a valid index.
         */
        json &operator[](size_t idx)
        {
            return data.get()[0][idx];
        }

        // @brief Compare the pointers to ascertain they are different
        bool operator!=(json &a) { return a.data != data; }

        /**
         * @brief Writes a json value to file.
         *
         * @param path filename
         * @returns `bool` whether `json` object written to file or not
         */
        bool to_file(std::string path) { return data->to_file(path); }

        /**
         * @brief recursively serializes the json value into a string to be written to a file or outputstream.
         *
         * @param indent indentation of the current level of heirarchy (only to prettify the output).
         * @return `std::string` serialized output.
         */
        std::string str(int indent = 0) { return data->str(indent); }

        /**
         * @brief Provides a overview of the json object with data types in order to avoid undefined behaviours.
         * Espescially helpful to avoid undefined behaviours when the origin of the json object is unknown.
         *
         * @param indent indentation of the current level of heirarchy (only to prettify the output)..
         * @return `std::string` overview
         */
        std::string describe(int indent = 0) { return data->describe(indent); }

        /**
         * @brief Easier output to the outputstream.
         */
        friend std::ostream &operator<<(std::ostream &os, json &j)
        {
            return os << j.data.get();
        }

        /**
         * @brief Inserts an element to the array data-type.
         *
         * @param json& value to be inserted.
         * @throws `std::runtime_error` if the type doesn't match array
         */
        void push_back(json &&val)
        {
            (*data).push_back(val);
        }

        /**
         * @brief Inserts an element to the array data-type.
         *
         * @param json&& rvalue to be inserted.
         * @throws `std::runtime_error` if the type doesn't match array
         */
        void push_back(json &val)
        {
            (*data).push_back(val);
        }

        /**
         * @brief Returns the size of the element. Returns `1` if the type is not iterable.
         *
         * @return size_t size of the container
         */
        virtual size_t size()
        {
            return (*data).size();
        }
    };

    /**
     * @brief Returns reference to the raw double data.
     *
     * @throws `std::runtime_error` if the data is not of `double` type.
     * @return `double&`
     */
    template <>
    double &json::get() { return (*data).get_double(); }

    /**
     * @brief Returns reference to the raw bool data.
     *
     * @throws `std::runtime_error` if the data is not of `bool` type.
     * @return `bool&`
     */
    template <>
    bool &json::get() { return (*data).get_bool(); }

    /**
     * @brief Returns reference to the raw string data.
     *
     * @throws `std::runtime_error` if the data is not of `std::string` type.
     * @return `std::string&`
     */
    template <>
    std::string &json::get() { return (*data).get_string(); }

    template <>
    json::json(JsonValue *ptr)
    {
        if (!ptr)
            ptr = new JsonValue();
        data.reset(ptr);
    }
}
