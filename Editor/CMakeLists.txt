file(GLOB src "src/*.cpp")
add_executable(Editor ${src})
target_link_libraries(Editor PRIVATE REN)