#
#	 Copyright (C) 2018 Qub³d Engine Group.
#	 All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without modification,
#  are permitted provided that the following conditions are met:
# 
#  1. Redistributions of source code must retain the above copyright notice, this
#  list of conditions and the following disclaimer.
#  
#  2. Redistributions in binary form must reproduce the above copyright notice,
#  this list of conditions and the following disclaimer in the documentation and/or
#  other materials provided with the distribution.
#  
#  3. Neither the name of the copyright holder nor the names of its contributors
#  may be used to endorse or promote products derived from this software without
#  specific prior written permission.
#  
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
#  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
#  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
#  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
#  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
#  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

# Use this version because it adds some options that we use.
cmake_minimum_required(VERSION 3.0)

project(qub3d-client)

# Set include, library, and source directories.

set(libdeps ${CMAKE_CURRENT_LIST_DIR}/../qub3d-libdeps)

set(source_dir ${PROJECT_SOURCE_DIR}/source/src)
set(headers_dir ${PROJECT_SOURCE_DIR}/source/include)

set(client_sources
  ${source_dir}/globalVars.cpp
  ${source_dir}/main.cpp
  ${source_dir}/client.cpp
  ${source_dir}/management/chunks.cpp
  ${source_dir}/input/inputHandler.cpp
  ${source_dir}/states/mainMenu.cpp
  ${source_dir}/states/options.cpp
  ${source_dir}/states/playing.cpp
  ${source_dir}/states/loading.cpp
  ${libdeps}/ImGUI/imgui.cpp
  ${libdeps}/ImGUI/imgui_draw.cpp
  ${libdeps}/ImGUI/imgui_demo.cpp
  ${libdeps}/ImGUI/examples/imgui_impl_sdl.cpp
  ${libdeps}/ImGUI/examples/imgui_impl_opengl2.cpp
)

set(clientHeaders
    ${headers_dir}/client.hpp
    ${headers_dir}/types.hpp
    ${headers_dir}/globalVars.hpp
    ${headers_dir}/states/mainMenu.hpp
    ${headers_dir}/states/options.hpp
    ${headers_dir}/states/playing.hpp
    ${headers_dir}/states/clientStateMap.hpp
    ${headers_dir}/management/chunks.hpp
    ${headers_dir}/input/command.hpp
    ${headers_dir}/input/inputHandler.hpp
    ${headers_dir}/gui/imguihelpers.hpp
)

if(APPLE)
  message(STATUS "Including SDL2 dependency frameworks for macOS")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework CoreAudio -framework AudioToolbox -framework CoreFoundation -framework CoreGraphics -framework CoreVideo -framework ForceFeedback -framework IOKit -framework Carbon -framework AppKit -framework OpenGL -liconv")
endif()# APPLE

set(include_dirs
        ${libdeps}/glew/include
        ${libdeps}/glm
        ${libdeps}/SDL2/include
        ${libdeps}/yaml-cpp/include
        ${libdeps}/ImGUI/
        ${PROJECT_SOURCE_DIR}/../qub3d-engine/source/include
        ${source_dir}/../include
)

set(library_dirs
    qub3d-engine
	glew_s
	yaml-cpp
    SDL2-static
    SDL2main
)

if (UNIX AND NOT APPLE)
  find_package(X11 REQUIRED)
	find_package(Threads REQUIRED)
	list(APPEND library_dirs
		${CMAKE_DL_LIBS}
        ${CMAKE_THREAD_LIBS_INIT}
        ${X11_LIBRARIES}
        ${X11_Xxf86vm_LIB}
        GL
	)
endif()

if(WIN32)
	list(APPEND library_dirs 
		${library_dirs}
		imm32.lib
		ole32.lib
		oleaut32.lib
		opengl32.lib
		version.lib
		winmm.lib
    )
endif()# WIN32

# Link the "SandBlox" binary.

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(qub3d-client ${client_sources} ${clientHeaders})
include_directories(${include_dirs})
target_link_libraries(qub3d-client ${library_dirs})

# Install it system-wide. (Invoked by `sudo make install`)
if (UNIX)
  install(
    TARGETS qub3d-client
    RUNTIME DESTINATION /usr/bin
  )
endif()
