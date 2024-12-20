list(APPEND FIRESIDE_HEADERS Fireside.hpp Program.hpp Shader.hpp 
  VertexArrayObject.hpp UniformBufferObject.hpp Vertex.hpp DrawList.hpp)

list(APPEND FIRESIDE_SOURCE Fireside.cpp Program.cpp Shader.cpp
  VertexArrayObject.cpp UniformBufferObject.cpp DrawList.cpp)

include(FetchContent)

# Build glm
# https://github.com/g-truc/glm
FetchContent_Declare(
  glm
  GIT_REPOSITORY	https://github.com/g-truc/glm.git
  GIT_TAG 	bf71a834948186f4097caa076cd2663c69a10e1e #refs/tags/1.0.1
)

FetchContent_MakeAvailable(glm)
list(APPEND FIRESIDE_LIBS glm::glm)

# Download Libraries
if (BUILD_DEPENDENCIES)
  # Build GLEW if needed
  if(USE_GLEW)
    FetchContent_Declare(
      GLEW
      GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
      GIT_TAG 9f4f3e6
    )

    FetchContent_MakeAvailable(GLEW)
    list(APPEND FIRESIDE_LIBS libglew_static)
  endif()

  # Build glfw
  FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 7b6aead
  )

  set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

  FetchContent_MakeAvailable(glfw)
  list(APPEND FIRESIDE_LIBS glfw)
else()
  list(APPEND FIRESIDE_LIBS GL glfw)
endif()

if (LIBRARY_BUILD_TYPE=="STATIC")
  add_library(${PROJECT_NAME} STATIC ${FIRESIDE_HEADERS} ${FIRESIDE_SOURCE})
else()
  add_library(${PROJECT_NAME} SHARED ${FIRESIDE_HEADERS} ${FIRESIDE_SOURCE})
endif()
target_link_libraries(${PROJECT_NAME} ${FIRESIDE_LIBS})

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})