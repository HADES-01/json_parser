#include "../json_util.hpp"

namespace hades
{
    class JsonValueString : public JsonValue
    {
        std::string data;

    public:
        JsonValueString(std::string val) : data(val) {}
        std::string str(int indent = 0) override
        {
            return "\"" + data + "\"";
        }
        JsonType type() { return JsonType::String; }
    };

    template <>
    json::json(char const *val)
    {
        data.reset(new JsonValueString(val));
    }

    template <>
    json::json(std::string val)
    {
        data.reset(new JsonValueString(val));
    }
    
}