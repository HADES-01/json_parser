# JSON Parser

### Read JSON from a file

The `json` class provides an API for manipulating a JSON value. To create a `json` object by reading a JSON file:

```cpp
#include <fstream>
#include <json.h>
using json = hades::json;

std::ifstream f("example.json");
json data(f);
```

### Write JSON to a file

The `json` class provides an API for writing a JSON value. To write a `json` object to a JSON file:

```cpp
#include <fstream>
#include <json.h>
using json = hades::json;

json j(std::ifstream("in.json"));
j.to_file("out.json");
```

### Creating `json` objects from JSON literals

Assume you want to create hard-code this literal JSON value in a file, as a `json` object:

```json
{
  "pi": 3.141,
  "happy": true
}
```

There are various options:

```cpp
// Using (raw) string literals and json::parse
json ex1 = json::parse(R"(
  {
    "pi": 3.141,
    "happy": true
  }
)");

// Using user-defined (raw) string literals
using namespace nlohmann::literals;
json ex2 = R"(
  {
    "pi": 3.141,
    "happy": true
  }
)"_json;

// Using initializer lists
json ex3 = {
  {"happy", true},
  {"pi", 3.141},
};
```

### JSON as first-class data type

Here are some examples to give you an idea how to use the class.

Assume you want to create the JSON object

```json
{
  "pi": 3.141,
  "happy": true,
  "name": "Niels",
  "nothing": null,
  "answer": {
    "everything": 42
  },
  "list": [1, 0, 2],
  "object": {
    "currency": "USD",
    "value": 42.99
  }
}
```

With this library, you could write:

```cpp
// create an empty structure (null)
json j;

// add a number that is stored as double (note the implicit conversion of j to an object)
j["pi"] = 3.141;

// add a Boolean that is stored as bool
j["happy"] = true;

// add a string that is stored as std::string
j["name"] = "Niels";

// add another null object by passing nullptr
j["nothing"] = nullptr;

// add an object inside the object
j["answer"]["everything"] = 42;

// add an array that is stored as std::vector (using an initializer list)
j["list"] = { 1, 0, 2 };

// add another object (using an initializer list of pairs)
j["object"] = { {"currency", "USD"}, {"value", 42.99} };

// instead, you could also write (which looks very similar to the JSON above)
json j2 = {
  {"pi", 3.141},
  {"happy", true},
  {"name", "Niels"},
  {"nothing", nullptr},
  {"answer", {
    {"everything", 42}
  }},
  {"list", {1, 0, 2}},
  {"object", {
    {"currency", "USD"},
    {"value", 42.99}
  }}
};
```

### Serialization / Deserialization

#### To/from strings

You can create a JSON value (deserialization) by appending `_json` to a string literal:

```cpp
// create object from string literal
json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;

// or even nicer with a raw string literal
auto j2 = R"(
  {
    "happy": true,
    "pi": 3.141
  }
)"_json;
```

Note that without appending the `_json` suffix, the passed string literal is not parsed, but just used as JSON string
value. That is, `json j = "{ \"happy\": true, \"pi\": 3.141 }"` would just store the string
`"{ "happy": true, "pi": 3.141 }"` rather than parsing the actual object.

### Helper Member Functions 

You can know more about the raw value using the helper functions provided by the `json` object

```cpp
json j = {10.2, 23, 32};

j.size()                // 3 
j.push_back({2,3,4})    // [10.2, 23, 32, [2, 3, 4]]
j.describe()            // Array[ Number ]
j.str()                 // [10.2, 23, 32, [2, 3, 4]] 
```

### Implicit Conversions

You can retrieve raw values by using `get<>()` value on a `json` object :

```cpp
json j = {
    {"number", 32.4},
    {"arr", {
        true, false, true
    }},
    {"str": "str"}
};

j["number"].get<double>()   // 32.4
j["arr"][2].get<bool>()     // true
j["str"].get<std::string>() // str
```