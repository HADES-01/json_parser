#include "../json_util.hpp"

namespace hades
{
    class JsonValueFloat : public JsonValue
    {
        double data;

    public:
        JsonValueFloat(double val) : data(val) {}
        std::string str(int indent = 0) override
        {
            auto temp = std::to_string(data);
            temp = temp.substr(0, temp.find_last_not_of('0') + 1);
            if (temp.back() == '.')
                temp.pop_back();
            return temp;
        }
        JsonType type() { return JsonType::Number; }
    };

    template <>
    json::json(int val)
    {
        data.reset(new JsonValueFloat(val));
    }

    template <>
    json::json(double val)
    {
        data.reset(new JsonValueFloat(val));
    }

}