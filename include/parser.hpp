#pragma once
#include "fstream"
#include "value/value.hpp"
#include "sstream"
#include "vector"

namespace hades
{
    /**
     * @brief Parses json objects from string
     */
    class Parser
    {
        std::stringstream buffer;

        /**
         * @brief Parses a json object if the first character is {
         */
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
                    }
                    break;
                }
                case '[':
                {
                    auto parsed = parse_array();
                    obj[currKey] = parsed;
                    break;
                }
                default:
                {
                    if (isdigit(ele))
                    {
                        auto parsed = parse_float();
                        obj[currKey] = parsed;
                    }
                    else if (ele == 't' || ele == 'f')
                    {
                        // boolean value
                        auto parsed = parse_boolean();
                        obj[currKey] = parsed;
                    }
                    else if (ele == 'n')
                    {
                        // null value
                        buffer.seekg((int)buffer.tellg() + 4);
                        obj[currKey] = {};
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

        /// @brief Parses a json array if the first character is [
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
                    break;
                }
                case '[':
                {
                    auto parsed = parse_array();
                    arr.push_back(parsed);
                    break;
                }
                case '\"':
                {
                    auto parsed = parse_string();
                    arr.push_back(parsed);
                    break;
                }
                default:
                {
                    if (isdigit(ele))
                    {
                        auto parsed = parse_float();
                        arr.push_back(parsed);
                    }
                    else if (ele == 't' || ele == 'f')
                    {
                        // boolean value
                        auto parsed = parse_boolean();
                        arr.push_back(parsed);
                    }
                    else if (ele == 'n')
                    {
                        // null value
                        buffer.seekg((int)buffer.tellg() + 4);
                        arr.push_back({});
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

        /// @brief Parses a json number if a first character is a digit
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

        /// @brief Parses a json boolean if the first character is a t or f
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

        /// @brief Parses a json string if the first character is "
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
        /**
         * @brief Construct a new Parser object from `std::ifstream`
         * 
         * @throws `std::runtime_error` if the file was not opened.
         */
        Parser(std::ifstream &ifs)
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

        /**
         * @brief Construct a new Parser object from `std::string`
         */
        Parser(std::string json)
        {
            for (auto a : json)
            {
                if (a == '\n' || a == ' ')
                    continue;
                buffer << a;
            }
        }

        /// @brief Starts parsing and delegates to appropriate function based on the first character.
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