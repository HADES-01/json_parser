#include "value/bool_value.hpp"
#include "value/float_Value.hpp"
#include "value/string_value.hpp"
#include "value/array_value.hpp"
#include "value/object_value.hpp"

#include "parser.hpp"

namespace hades
{
    /**
     * @brief Construct a new `json` object by parsing a json file.
     * 
     * @internal Template Specialization with `std::ifstream`
     * @param ifs `std::ifstream` json file object 
     */
    template <>
    json::json(std::ifstream ifs)
    {
        data = (hades::Parser(ifs).parse().data);
    }

    /// @brief Constructs a new empty `json` object.
    json::json()
    {
        data.reset(new JsonObject());
    }

    /// @brief Constructs a new `json` array from a `std::vector` of json values.
    json::json(std::vector<json> val)
    {
        auto l = new JsonValueArray();
        for (auto a : val)
        {
            l->push_back(a);
        }
        data.reset(l);
    }

    /**
     * @brief Constructs a new `json` array from a uniform intialization list of `std::string` values.
     * @internal Template Specialization for uniform initialization list of `std::string`.
    */
    template <>
    json::json(std::initializer_list<std::string> val)
    {
        auto l = new JsonValueArray();
        for (auto a : val)
        {
            l->push_back(json(a));
        }
        data.reset(l);
    }

    /**
     * @brief Constructs a new `json` array from a uniform intialization list of string literal values.
     * @internal Template Specialization for uniform initialization list of `const char *`.
    */
    template <>
    json::json(std::initializer_list<char const *> val)
    {
        auto l = new JsonValueArray();
        for (auto a : val)
        {
            l->push_back(json(a));
        }
        data.reset(l);
    }

    /**
     * @brief Constructs a new `json` array from a uniform intialization list of bool values.
     * @internal Template Specialization for uniform initialization list of `bool`.
    */
    template <>
    json::json(std::initializer_list<bool> val)
    {
        auto l = new JsonValueArray();
        for (auto a : val)
        {
            l->push_back(json(a));
        }
        data.reset(l);
    }

    /**
     * @brief Constructs a new `json` array from a uniform intialization list of int values.
     * @internal Template Specialization for uniform initialization list of `int`.
    */
    template <>
    json::json(std::initializer_list<int> val)
    {
        auto l = new JsonValueArray();
        for (auto a : val)
        {
            l->push_back(json(a));
        }
        data.reset(l);
    }

    /**
     * @brief Constructs a new `json` array from a uniform intialization list of double values.
     * @internal Template Specialization for uniform initialization list of `double`.
    */
    template <>
    json::json(std::initializer_list<double> val)
    {
        auto l = new JsonValueArray();
        for (auto a : val)
        {
            l->push_back(json(a));
        }
        data.reset(l);
    }

    /**
     * @brief Constructs a new `json` object from a `std::unordered_map<std::string, json>`.
    */
    json::json(std::unordered_map<std::string, json> val)
    {
        auto l = new JsonObject();
        for (auto &a : val)
        {
            l[0][a.first] = a.second;
        }
        data.reset(l);
    }

    /**
     * @brief Constructs a new `json` object from a uniform intialization list `std::pair<std::string, json>`.
    */
    json::json(std::initializer_list<std::pair<std::string, json>> val)
    {
        auto l = new JsonObject();
        for (auto a : val)
        {
            l[0][a.first] = a.second;
        }
        data.reset(l);
    }
}

/**
 * @brief Custom String literal `_json` to create `json` object from a string literal.
 */
extern hades::json operator"" _json(const char *val, size_t)
{
    std::string temp(val);
    return hades::Parser(temp).parse();
}