#include "../json_util.hpp"

namespace hades
{
    class JsonValueArray : public JsonValue
    {
        std::vector<json> data;

    public:
        JsonValueArray() {}
        JsonValueArray(std::initializer_list<json> val) : data(val) {}
        void add_entry(json val)
        {
            data.push_back(val);
        }

        std::string str(int indent) override
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
        json &operator[](const size_t &idx)
        {
            if (idx >= data.size() || idx < 0)
            {
                throw std::runtime_error("Not a valid index.");
            }
            return data[idx];
        }
        JsonType type() { return JsonType::Array; }
    };

    json::json(std::vector<json> val)
    {
        auto l = new JsonValueArray();
        for (auto a : val)
        {
            l->add_entry(a);
        }
        // data.reset(l);
        data.reset(l);
    }

    template <>
    json::json(std::initializer_list<std::string> val)
    {
        auto l = new JsonValueArray();
        for (auto a : val)
        {
            l->add_entry(json(a));
        }
        data.reset(l);
    }

    template <>
    json::json(std::initializer_list<char const *> val)
    {
        auto l = new JsonValueArray();
        for (auto a : val)
        {
            l->add_entry(json(a));
        }
        data.reset(l);
    }

    template <>
    json::json(std::initializer_list<bool> val)
    {
        auto l = new JsonValueArray();
        for (auto a : val)
        {
            l->add_entry(json(a));
        }
        data.reset(l);
    }

    template <>
    json::json(std::initializer_list<int> val)
    {
        auto l = new JsonValueArray();
        for (auto a : val)
        {
            l->add_entry(json(a));
        }
        data.reset(l);
    }

    template <>
    json::json(std::initializer_list<double> val)
    {
        auto l = new JsonValueArray();
        for (auto a : val)
        {
            l->add_entry(json(a));
        }
        data.reset(l);
    }
}