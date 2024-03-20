#include "../json_util.hpp"

namespace hades
{
    class JsonValueBoolean : public JsonValue
    {
        bool data;

    public:
        JsonValueBoolean(bool val) : data(val) {}
        std::string str(int indent) override
        {
            std::ostringstream oss;
            oss << std::boolalpha << data;
            return oss.str();
        }
        JsonType type() { return JsonType::Boolean; }

        bool &get_bool() { return data; }
    };

    template <>
    json::json(bool val)
    {
        data.reset(new JsonValueBoolean(val));
    }

}
