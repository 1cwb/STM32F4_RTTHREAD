aux_source_directory(. SYSTEM_LIB_SRC)

include_directories(${CMAKE_SOURCE_DIR}/USER)
message(status "${CMAKE_SOURCE_DIR}/rt-thread/include")

add_library(syslib ${SYSTEM_LIB_SRC})
target_link_libraries(syslib PUBLIC stm32f4xx_lib)
#target_compile_definitions(stm32f4xx_lib PUBLIC -DUSE_STDPERIPH_DRIVER -D${MCU_TYPE})

#target_link_libraries(stm32f4xx_hal PUBLIC cmsis)
target_include_directories(syslib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/SYSTEM>
  PRIVATE SYSTEM)
