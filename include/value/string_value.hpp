/**
 * @file include/value/string_value.hpp
 * @brief Definition of JsonValueString.
 *
 * ! Internal header file. Not to be used directly.
 */
#include "value.hpp"

namespace hades
{
    /**
     * @brief Specialization of `JsonValue` for json string data-type.
     * @implements `JsonValue`
     */
    class JsonValueString : public JsonValue
    {
        std::string data; // @brief Overridden `JsonValue::type()` to provide Object type.
        JsonType type() { return JsonType::String; }

    public:
        JsonValueString(std::string val) : data(val) {}

        // @brief Overridden `JsonValue::str()` to convert json object to string
        std::string str(int indent = 0) override
        {
            return "\"" + data + "\"";
        }

        // @brief Overridden `JsonValue::get_string()` to return the reference to the string value.
        std::string &get_string() override
        {
            return data;
        }

        // @brief Overidden `JsonValue::size()` to return the size of the string type
        size_t size() override { return data.size(); }
    };

    //@brief Template specialzation for string data-type.
    template <>
    json::json(char const *val)
    {
        data.reset(new JsonValueString(val));
    }

    //@brief Template specialzation for string data-type.
    template <>
    json::json(std::string val)
    {
        data.reset(new JsonValueString(val));
    }
}