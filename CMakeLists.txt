cmake_minimum_required(VERSION 3.20)
project(PortfolioConsole LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(app
    Theatre/main.cpp
    Theatre/Performance.cpp
    Theatre/Ticket.cpp
    Theatre/Utils.cpp
)
if(MSVC)
    add_compile_options(/utf-8 /W4)
    target_compile_options(app PRIVATE /utf-8 /W4)
else()
    add_compile_options(-Wall -Wextra)
    target_compile_options(app PRIVATE -Wall -Wextra)
endif()
enable_testing()
find_package(Python3 REQUIRED COMPONENTS Interpreter)
add_test(NAME console_regressions COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/tests/console_test.py $<TARGET_FILE:app>)
set_tests_properties(console_regressions PROPERTIES TIMEOUT 20)
