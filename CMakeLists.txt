cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(engine VERSION 1.0)

find_package(fmt CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(engine warpengine.cpp ${SRC_FILES})
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(engine PRIVATE fmt::fmt JsonCpp::JsonCpp glm::glm glfw Vulkan::Vulkan)