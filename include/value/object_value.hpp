#include "../json_util.hpp"

namespace hades
{
    class JsonObject : public JsonValue
    {
        std::unordered_map<std::string, json> data;

    public:
        JsonObject() {}
        JsonObject(std::unordered_map<std::string, json> val) : data(val) {}
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
        void add_entry(std::string key, json value)
        {
            data[key] = value;
        }
        json &operator[](const std::string &key) override
        {
            if (data.count(key) == 0)
            {
                data[key] = new JsonValue;
            }
            return data[key];
        }
        JsonType type() { return JsonType::Object; }
    };

    json::json()
    {
        data.reset(new JsonObject());
    }

    json::json(std::unordered_map<std::string, json> val)
    {
        auto l = new JsonObject();
        for (auto a : val)
        {
            l->add_entry(a.first, a.second);
        }
        data.reset(l);
    }

    json::json(std::initializer_list<std::pair<std::string, json>> val)
    {
        auto l = new JsonObject();
        for (auto a : val)
        {
            l->add_entry(a.first, a.second);
        }
        data.reset(l);
    }
}