/**
 * @file include/value/array_value.hpp
 * @brief Definition of JsonValueArray.
 *
 * ! Internal header file. Not to be used directly.
 */
#include "value.hpp"

namespace hades
{
    /**
     * @brief Specialization of `JsonValue` for json array data-type.
     * @implements `JsonValue`
     */
    class JsonValueArray : public JsonValue
    {
        std::vector<json> data;

        // @brief Overridden `JsonValue::type()` to provide Array type.
        JsonType type() { return JsonType::Array; }

    public:
        JsonValueArray() {}
        JsonValueArray(std::initializer_list<json> val) : data(val) {}

        // @brief Overridden `JsonValue::push_back(json&&)` to insert a rvalue to the array.
        void push_back(json &&val) override
        {
            data.push_back(val);
        }

        // @brief Overridden `JsonValue::push_back(json&)` to insert a value to the array.
        void push_back(json &val) override
        {
            data.push_back(val);
        }

        // @brief Overridden `JsonValue::str()` to convert json array to string
        std::string str(int indent = 0) override
        {
            std::ostringstream oss;
            oss << "[";
            if (data.size() != 0)
                oss << "\n";
            std::string indent_str(indent * 2, ' ');
            for (auto value : data)
            {
                oss << indent_str << "  " << value.str(indent + 1);
                if (value != data.back())
                {
                    oss << ",\n";
                }
            }
            if (data.size() != 0)
                oss << "\n"
                    << indent_str;
            oss << "]";
            return oss.str();
        }

        // @brief Overridden `JsonValue::describe()` to provide the overview of json array
        std::string describe(int indent) override
        {
            std::ostringstream oss;
            std::string indent_str(indent * 2, ' ');
            oss << "Array[ ";
            if (data.size() != 0)
                oss << data[0].describe(0);
            oss << " ]";
            return oss.str();
        }

        // @brief Overridden `JsonValue::operator[]` to provide the array-like access to json array
        json &operator[](const size_t &idx)
        {
            if (idx >= data.size() || idx < 0)
            {
                throw std::runtime_error("Not a valid index.");
            }
            return data[idx];
        }

        // @brief Overidden `JsonValue::size()` to return the size of the array type
        size_t size() override { return data.size(); }
    };
}