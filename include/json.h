#include "value/bool_value.hpp"
#include "value/float_Value.hpp"
#include "value/string_value.hpp"
#include "value/array_value.hpp"
#include "value/object_value.hpp"

#include "parser.hpp"

namespace hades
{

    template <>
    json::json(std::ifstream ifs)
    {
        data = hades::Parser(ifs).parse().data;
    }
}

extern hades::json operator"" _json(const char *val, size_t)
{
    std::string temp(val);
    return hades::Parser(temp).parse();
}