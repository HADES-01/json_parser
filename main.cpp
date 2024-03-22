#include "include/json.h"
#include "iostream"

int main()
{
    hades::json k = {{"hello", hades::json({ 1, {{"temp", true}}, true, "temp"})}};
    std::cout << k << std::endl;
    hades::json j({
        {"obj", {
            10.2, 10.3,
        }},
        {"obj1", {
            {"temp", true},
            {"temp2", {10,30}},
        }}
    });
    std::cout << j << std::endl;

    hades::json l = (R"({
        "hello" : [10,23,4.5]
    })"_json);
    std::cout << l << std::endl;

    hades::json a = hades::json(std::ifstream("temp.json"));
    a["obj"]["obj"]["hello"] = "hello";
    // a.get<char>();
    std::string& lp = a["obj"]["obj"]["hello"].get<std::string>();
    lp[4] = 'e';
    std::cout << a["obj"]["obj"]["hello"];
    a["arr"][1] = {10, 34, 21};
    a["arr"][1].push_back({{"hades", "json"}});
    std::cout << a << std::endl;
    // a.to_file("temp2.json");
    // std::cout << std::boolalpha << "a[\"obj\"][\"obj\"][\"hello\"] => " << a["obj"]["obj"]["hello"] << std::endl;
    return 0;
}