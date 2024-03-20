#pragma once
#include "fstream"
#include "iostream"
#include "json_util.hpp"
#include "sstream"
#include "vector"

namespace hades
{
    class Parser
    {
        std::stringstream buffer;
        hades::json parse_object()
        {
            char ele;
            buffer >> ele;
            std::unordered_map<std::string, hades::json> obj;
            bool haveKey = false;
            std::string currKey = "";
            while (buffer.peek() != '}' && ele != -1)
            {
                ele = char(buffer.peek());
                switch (ele)
                {
                case '{':
                {
                    auto parsed = parse_object();
                    obj[currKey] = parsed;
                    // obj->add_entry(currKey, parsed);
                    break;
                }
                case ',':
                {
                    haveKey = !haveKey;
                    buffer >> ele;
                    break;
                }
                case '\"':
                {
                    auto parsed = parse_string();
                    if (!haveKey)
                    {
                        currKey = parsed;
                        haveKey = true;
                    }
                    else
                    {
                        obj[currKey] = parsed;
                        // obj->add_entry(currKey, parsed);
                    }
                    break;
                }
                case '[':
                {
                    auto parsed = parse_array();
                    obj[currKey] = parsed;
                    // obj->add_entry(currKey, parsed);
                    break;
                }
                default:
                {
                    if (isdigit(ele))
                    {
                        auto parsed = parse_float();
                        obj[currKey] = parsed;
                        // obj->add_entry(currKey, parsed);
                    }
                    else if (ele == 't' || ele == 'f')
                    {
                        // boolean value
                        auto parsed = parse_boolean();
                        obj[currKey] = parsed;
                        // obj->add_entry(currKey, parsed);
                    }
                    else if (ele == 'n')
                    {
                        // null value
                        buffer.seekg((int)buffer.tellg() + 4);
                        obj[currKey] = {};
                        // obj->add_entry(currKey, {});
                    }
                    else
                    {
                        buffer >> ele;
                    }
                }
                }
            }
            buffer >> ele;
            return hades::json(obj);
        }
        hades::json parse_array()
        {
            std::vector<hades::json> arr;
            char ele;
            buffer >> ele;
            while (buffer.peek() != ']' && ele != -1)
            {
                ele = char(buffer.peek());
                switch (ele)
                {
                case '{':
                {
                    auto parsed = parse_object();
                    arr.push_back(parsed);
                    // arr->add_entry(parsed);
                    break;
                }
                case '[':
                {
                    auto parsed = parse_array();
                    arr.push_back(parsed);
                    // arr->add_entry(parsed);
                    break;
                }
                case '\"':
                {
                    auto parsed = parse_string();
                    arr.push_back(parsed);
                    // arr->add_entry(parsed);
                    break;
                }
                default:
                {
                    if (isdigit(ele))
                    {
                        auto parsed = parse_float();
                        arr.push_back(parsed);
                        // arr->add_entry(parsed);
                    }
                    else if (ele == 't' || ele == 'f')
                    {
                        // boolean value
                        auto parsed = parse_boolean();
                        arr.push_back(parsed);
                        // arr->add_entry(parsed);
                    }
                    else if (ele == 'n')
                    {
                        // null value
                        buffer.seekg((int)buffer.tellg() + 4);
                        arr.push_back({});
                        // arr->add_entry({});
                    }
                    else
                    {
                        buffer >> ele;
                    }
                }
                }
            }
            buffer >> ele;
            return hades::json(arr);
        }
        double parse_float()
        {
            char c;
            std::string data;
            buffer >> c;
            while ((isdigit(c) || c == '.') && !buffer.eof())
            {
                data += c;
                buffer >> c;
            }
            buffer.seekg((int)buffer.tellg() - 1);
            return std::stod(data);
        }
        bool parse_boolean()
        {
            char c;
            buffer >> c;
            if (c == 't')
            {
                buffer.seekg((int)buffer.tellg() + 3);
                return true;
            }
            buffer.seekg((int)buffer.tellg() + 4);
            return false;
        }
        std::string parse_string()
        {
            char c;
            std::string data;
            buffer >> c;
            buffer >> c;
            while (c != '\"')
            {
                data += c;
                buffer >> c;
            }
            return data;
        }

    public:
        Parser(std::ifstream& ifs)
        {
            if (!ifs.is_open())
            {
                throw std::runtime_error("File not Open !!!");
            }

            char c = '\n';
            while (ifs.peek() != -1)
            {
                ifs >> c;
                if (c == '\n')
                    continue;
                buffer << c;
            }

            ifs.close();
        }
        Parser(std::string json)
        {
            for (auto a : json)
            {
                if (a == '\n' || a == ' ')
                    continue;
                buffer << a;
            }
        }
        hades::json parse()
        {
            char ele;
            buffer >> ele;
            buffer.seekg((int)buffer.tellg() - 1);
            switch (ele)
            {
            case '{':
                return parse_object();
                break;
            case '[':
                return parse_array();
                break;
            case '\"':
                return parse_string();
                break;
            default:
                if (isdigit(ele))
                {
                    return parse_float();
                }
                else if (ele == 'n')
                {
                    return {};
                }
                else if (ele == 't' || ele == 'f')
                {
                    return parse_boolean();
                }
                break;
            }
            buffer.clear();
            return {};
        }
    };
}