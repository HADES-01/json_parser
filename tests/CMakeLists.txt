project(tests)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/../include")

file(COPY "${PROJECT_SOURCE_DIR}/test.json" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME "json.Test" COMMAND "tests" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})