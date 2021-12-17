cmake_minimum_required(VERSION 3.0.0)
project(USER C CXX ASM)

# adjust project folder name if necessary
set(STM32_PROJ_FOLDER USER)

message(STATUS "Building project: ${PROJECT_NAME}")
set(STM32_CMAKE_DIR "${CMAKE_SOURCE_DIR}")

# set the build type
if(NOT CMAKE_BUILD_TYPE) 
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE MATCHES Debug)
  message(STATUS "Build type: Debug")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
  message(STATUS "Build type: Release")
endif()

## Setup cross-compile toolchain 
set(CROSS_COMPILE_PREFIX arm-none-eabi-)
include(${STM32_CMAKE_DIR}/cmake/gcc-arm-none-eabi.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/target-def.cmake)

## auto-set variables from user input
set(MCU_FLAGS "${CPU} -mthumb ${FPU} ${FLOAT_ABI}")
set(LINK_FLAGS "${MCU_FLAGS} -Wl,--gc-sections")
set(EXTRA_LINK_FLAGS "-Wl,-Map=${PROJECT_NAME}.map,--cref,--no-warn-mismatch -specs=nano.specs -specs=nosys.specs")
include(${STM32_CMAKE_DIR}/cmake/stm32-gcc-flags.cmake)

# print summary of configurations
message(STATUS "MCU_FAMILY: ${MCU_FAMILY}")
message(STATUS "MCU_TYPE: ${MCU_TYPE}")
message(STATUS "MCU_NAME: ${MCU_NAME}")
message(STATUS "Specified C compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Linker script: ${LINKER_SCRIPT}")
message(STATUS "Use LL library: ${USE_LL_LIB}")
message(STATUS "Use HAL library: ${USE_HAL_LIB}")
message(STATUS "Use Segger SystemView library: ${USE_SYSTEM_VIEW}")

## version information
set(VERSION_MAJOR 0 CACHE STRING "Project major version number.")
set(VERSION_MINOR 1 CACHE STRING "Project minor version number.")
set(VERSION_PATCH 0 CACHE STRING "Project patch version number.")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/CORE)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/FWLIB/inc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/SYSTEM)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/HARDWARE)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER})

if(USE_SYSTEM_VIEW)
add_definitions("-DENABLE_SYSTEMVIEW")
endif()

## add project components
set(ELF_TARGET ${PROJECT_NAME}.elf)
#set(PROJ_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libraries)

# project-specific modules
# add_subdirectory(driver)

# common libraries
add_subdirectory(${STM32_CMAKE_DIR}/FWLIB ${CMAKE_BINARY_DIR}/libraries/FWLIB)
add_subdirectory(${STM32_CMAKE_DIR}/SYSTEM ${CMAKE_BINARY_DIR}/libraries/SYSTEM)
add_subdirectory(${STM32_CMAKE_DIR}/HARDWARE ${CMAKE_BINARY_DIR}/libraries/HARDWARE)

# STM32 USER generated source files
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/USER USER_SRC_FILE)
file(GLOB ASM_FILE ${CMAKE_CURRENT_SOURCE_DIR}/USER/*.s)

set(CUBEMX_SRC
    ${ASM_FILE}
    ${USER_SRC_FILE}
)

add_executable(${ELF_TARGET} ${CUBEMX_SRC})
target_compile_definitions(${ELF_TARGET} PUBLIC -D${MCU_FAMILY})
target_link_libraries(${ELF_TARGET} PUBLIC stm32f4xx_lib syslib hwlib -lc -lm -lnosys)
target_link_libraries(${ELF_TARGET} PRIVATE -T${LINKER_SCRIPT} ${EXTRA_LINK_FLAGS})
target_include_directories(${ELF_TARGET} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR})

## add post-build targets
include(${STM32_CMAKE_DIR}/cmake/stm32-gcc-postbuild.cmake)
