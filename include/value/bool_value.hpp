/**
 * @file include/value/bool_value.hpp
 * @brief Definition of JsonValueBoolean.
 *
 * ! Internal header file. Not to be used directly.
 */

#include "value.hpp"

namespace hades
{
    /**
     * @brief Specialization of `JsonValue` for json boolean data-type.
     * @implements `JsonValue`
     */
    class JsonValueBoolean : public JsonValue
    {
        bool data;

        // @brief Overridden `JsonValue::tpye()` to provide Boolean type.
        JsonType type() { return JsonType::Boolean; }

    public:
        JsonValueBoolean(bool val) : data(val) {}

        // @brief Overridden `JsonValue::str()` to convert json boolean to string
        std::string str(int indent) override
        {
            std::ostringstream oss;
            oss << std::boolalpha << data;
            return oss.str();
        }

        // @brief Overridden `JsonValue::get_bool()` to return the reference to the boolean value.
        bool &get_bool() { return data; }
    };

     //@brief Template specialzation for bool data-type.
    template <>
    json::json(bool val)
    {
        data.reset(new JsonValueBoolean(val));
    }

}
