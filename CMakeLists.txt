cmake_minimum_required(VERSION 3.28)
SET(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
SET(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project("Kraine")

# =================================== TESTING ===================================
add_executable(test 
  ${PROJECT_SOURCE_DIR}/src/main.c
  ${PROJECT_SOURCE_DIR}/src/glad.c
  ${PROJECT_SOURCE_DIR}/src/renderer/shader.c
  ${PROJECT_SOURCE_DIR}/src/renderer/texture.c
  ${PROJECT_SOURCE_DIR}/src/renderer/mesh.c
  ${PROJECT_SOURCE_DIR}/src/renderer/model.c
  ${PROJECT_SOURCE_DIR}/src/renderer/camera.c
)
target_link_libraries(test ${PROJECT_SOURCE_DIR}/lib/libglfw3.a)
target_link_libraries(test ${PROJECT_SOURCE_DIR}/lib/cglm.lib)
target_link_libraries(test ${PROJECT_SOURCE_DIR}/lib/libassimp.dll.a)
target_include_directories(test PUBLIC ${PROJECT_SOURCE_DIR}/include/)
