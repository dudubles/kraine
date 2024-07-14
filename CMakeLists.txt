cmake_minimum_required(VERSION 3.28)
SET(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
SET(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project("Kraine")

# =================================== TESTING ===================================
add_executable(test 
  ${PROJECT_SOURCE_DIR}/src/main.c

  # Renderer
  ${PROJECT_SOURCE_DIR}/src/renderer/shader.c
  ${PROJECT_SOURCE_DIR}/src/renderer/texture.c
  ${PROJECT_SOURCE_DIR}/src/renderer/mesh.c
  ${PROJECT_SOURCE_DIR}/src/renderer/model.c
  ${PROJECT_SOURCE_DIR}/src/renderer/coords.c

  # Utils
  ${PROJECT_SOURCE_DIR}/src/utils/files.c

  # Core
  ${PROJECT_SOURCE_DIR}/src/core/game.c
  ${PROJECT_SOURCE_DIR}/src/core/gameobj.c
  ${PROJECT_SOURCE_DIR}/src/core/gamecam.c
  ${PROJECT_SOURCE_DIR}/src/core/scene.c
  ${PROJECT_SOURCE_DIR}/src/core/transform.c

  #Libs
  ${PROJECT_SOURCE_DIR}/src/glad.c

)
target_include_directories(test PUBLIC ${PROJECT_SOURCE_DIR}/include/)

target_link_libraries(test 
  ${PROJECT_SOURCE_DIR}/lib/libglfw3.a 
  ${PROJECT_SOURCE_DIR}/lib/libufbx.a
)

