cmake_minimum_required(VERSION 3.21)

project(game CXX)

find_package(assimp CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)
find_package(Flatbuffers CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(Lua REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)

add_executable(game
    src/main.cpp
)

target_compile_features(game
PRIVATE
    cxx_std_20
)

target_include_directories(game
PRIVATE
    ${LUA_INCLUDE_DIR}
)

target_link_libraries(game
PRIVATE
    assimp::assimp
    box2d::box2d
    flatbuffers::flatbuffers
    GLEW::GLEW
    ${LUA_LIBRARIES}
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    unofficial::sqlite3::sqlite3
)
