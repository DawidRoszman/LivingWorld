cmake_minimum_required(VERSION 3.14)
project(LivingWorld)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/external/cereal/include)

add_executable(main Animal.cpp LivingWorld.cpp Organism.cpp Plant.cpp Position.cpp World.cpp Sheep.cpp Grass.cpp Wolf.cpp Dandelion.cpp Toadstool.cpp)
enable_testing()


add_executable(tests tests.cpp Position.cpp Organism.cpp Plant.cpp Animal.cpp Wolf.cpp Sheep.cpp Toadstool.cpp Dandelion.cpp)
target_link_libraries(tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
