/**
 * @file include/value/float_value.hpp
 * @brief Definition of JsonFloatValue
 *
 * ! Internal header file. Not to be used directly.
 */
#include "value.hpp"

namespace hades
{
    /**
     * @brief Specialization of JsonValue for json number data-type.
     * @implements `JsonValue`
     */
    class JsonValueFloat : public JsonValue
    {
        double data;

        // @brief Overridden `JsonValue::type()` to provide Number type.
        JsonType type() { return JsonType::Number; }

    public:
        JsonValueFloat(double val) : data(val) {}

        // @brief Overridden `JsonValue::str()` to convert json number to string
        std::string str(int indent = 0) override
        {
            auto temp = std::to_string(data);
            temp = temp.substr(0, temp.find_last_not_of('0') + 1);
            if (temp.back() == '.')
                temp.pop_back();
            return temp;
        }

        // @brief Overridden `JsonValue::get_double()` to return the reference to the double value.
        double &get_double() override
        {
            return data;
        }
    };

    //@brief Template specialzation for double data-type.
    template <>
    json::json(int val)
    {
        data.reset(new JsonValueFloat(val));
    }

    //@brief Template specialzation for double data-type.
    template <>
    json::json(double val)
    {
        data.reset(new JsonValueFloat(val));
    }

}