cmake_minimum_required(VERSION 2.6)
project(EngineDemo)

include_directories(
src
contrib
)

if(MSVC)
  include_directories(
    contrib/msvc-2017-windows-x86/glew/include
    contrib/msvc-2017-windows-x86/SDL2/include
    contrib/msvc-2017-windows-x86/openal-soft/include
    contrib/msvc-2017-windows-x86/ogg/include
    contrib/msvc-2017-windows-x86/vorbis/include
	contrib/msvc-2017-windows-x86/assimp/include
  )

  link_directories(
    ${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/SDL2/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/glew/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/openal-soft/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/ogg/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/vorbis/lib
	${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/assimp/lib
  )
else()
  include_directories(
    /usr/X11R6/include
    /usr/local/include
  )

  link_directories(
    /usr/X11R6/lib
    /usr/local/lib
  )
endif()

add_library(viridian
  src/viridian/engine.h
  src/viridian/stb_image.h
  src/viridian/stb_image.cpp
  src/viridian/Core.h
  src/viridian/Core.cpp
  src/viridian/Entity.h
  src/viridian/Entity.cpp
  src/viridian/Component.h
  src/viridian/Component.cpp
  src/viridian/Shader.h
  src/viridian/Shader.cpp
  src/viridian/Resource.h
  src/viridian/Resource.cpp
  src/viridian/ResourceManager.h
  src/viridian/ResourceManager.cpp
  src/viridian/Renderer.h
  src/viridian/Renderer.cpp

  src/viridian/Environment.h
  src/viridian/Environment.cpp
  src/viridian/Keyboard.h
  src/viridian/Keyboard.cpp
  src/viridian/Mouse.h
  src/viridian/Mouse.cpp
  
)
if(MSVC)
  target_link_libraries(viridian
    SDL2 glew32 opengl32 OpenAL32 ogg vorbis vorbisfile assimp-vc140-mt
  )
else()
  target_link_libraries(viridian
    SDL2 GLU GLEW GL openal ogg vorbis vorbisfile assimp-vc140-mt
  )
endif()

add_executable(game
  src/game/main.cpp
)

target_link_libraries(game 
  viridian
)

if(MSVC)
  add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/SDL2/bin/SDL2.dll"
      "$<TARGET_FILE_DIR:game>"
  )
  add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/assimp/bin/assimp-vc140-mt.dll"
      "$<TARGET_FILE_DIR:game>"
  )

  add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/glew/bin/glew32.dll"
      "$<TARGET_FILE_DIR:game>"
  )

  add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-2017-windows-x86/openal-soft/bin/OpenAL32.dll"
      "$<TARGET_FILE_DIR:game>"
  )
endif()