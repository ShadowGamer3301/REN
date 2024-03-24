file(GLOB src "src/*.cpp")
add_library(REN ${src})
target_link_libraries(REN PRIVATE "glfw3.lib" "dxgi.lib" "d3d11.lib" "d3dcompiler.lib" "xinput.lib")