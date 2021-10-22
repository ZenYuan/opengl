cmake_minimum_required(VERSION 3.5)

project(openglTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#core
file(GLOB_RECURSE src_opengl_core
./src/*.cpp
)

#test
file(GLOB_RECURSE src_test_core
./test/*.cpp
./test/*.h
)

#head
file(GLOB_RECURSE head_opengl
./include/*.h
)

#res
file(GLOB_RECURSE res_opengl
./res/shaders/*.shader
./res/image/*.jpg
./res/image/*.png
)

#----------------------------------thirdParty------------------------------
#imgui
file(GLOB_RECURSE thirdSrc_imgui
./thirdParty/imgui/src/*.cpp
./thirdParty/imgui/include/*.h
)

#stb_imgae
file(GLOB_RECURSE thirdSrc_stb_imgae
./thirdParty/stb_imgae/*.cpp
./thirdParty/stb_imgae/*.h
)

add_definitions()

include_directories(
./include
./test
./thirdParty/imgui/include
./thirdParty/stb_imgae
./thirdParty/Lib/include
)

link_directories(./thirdParty/Lib/lib)
list(APPEND opengllib glfw3 glew32 glew32s assimp-vc142-mtd opengl32)

add_executable(openglTest ${src_opengl_core} ${src_test_core} ${head_opengl} ${thirdSrc_imgui} ${thirdSrc_stb_imgae})
target_link_libraries(openglTest PRIVATE ${opengllib})


source_group("src\\opengl\\core" FILES ${src_opengl_core})
source_group("src\\opengl\\include" FILES ${head_opengl})
source_group("test" FILES ${src_test_core})
source_group("res" FILES ${res_opengl})

#thirdParty
source_group("thirdParty\\stb_imgae" FILES ${thirdSrc_stb_imgae})
source_group("thirdParty\\imgui" FILES ${thirdSrc_imgui})
