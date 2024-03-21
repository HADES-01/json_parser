/**
 * @file include/value/object_value.hpp
 * @brief Definition of JsonObject.
 *
 * ! Internal header file. Not to be used directly.
 */

#include "value.hpp"

namespace hades
{
    /**
     * @brief Specialization of `JsonValue` for json object data-type.
     * @implements `JsonValue`
     */
    class JsonObject : public JsonValue
    {
        std::unordered_map<std::string, json> data;

        // @brief Overridden `JsonValue::tpye()` to provide Object type.
        JsonType type() { return JsonType::Object; }

    public:
        JsonObject() {}
        JsonObject(std::unordered_map<std::string, json> val) : data(val) {}

        // @brief Overridden `JsonValue::str()` to convert json object to string
        std::string str(int indent) override
        {
            std::ostringstream oss;
            std::string indent_str(indent * 2, ' ');
            oss << "{";
            if (data.size() != 0)
                oss << "\n";
            for (auto p = data.begin(); p != data.end(); p++)
            {
                oss << indent_str << "  \"" << p->first << "\""
                    << " : " << p->second.str(indent + 1);
                auto l = p;
                if ((++l) != data.end())
                {
                    oss << ",\n";
                }
            }
            if (data.size() != 0)
                oss << "\n"
                    << indent_str;
            oss << "}";
            return oss.str();
        }

        // @brief Overridden `JsonValue::describe()` to provide overview of the json object
        std::string describe(int indent) override
        {
            std::ostringstream oss;
            std::string indent_str(indent * 2, ' ');
            oss << "Object{";
            if (data.size() != 0)
                oss << "\n";
            for (auto p = data.begin(); p != data.end(); p++)
            {
                oss << indent_str << "  \"" << p->first << "\""
                    << " : " << p->second.describe(indent + 1);
                auto l = p;
                if ((++l) != data.end())
                {
                    oss << ",\n";
                }
            }
            if (data.size() != 0)
                oss << "\n"
                    << indent_str;
            oss << "}";
            return oss.str();
        }

        // @brief Overridden `JsonValue::operator[]` to provide object-like access.
        json &operator[](const std::string &key) override
        {
            if (data.count(key) == 0)
            {
                data[key] = new JsonValue;
            }
            return data[key];
        }

        // @brief Overidden `JsonValue::size()` to return the size of the object type
        size_t size() override { return data.size(); }
    };
}