aux_source_directory(src STM32F4_LIB_SRC)
add_library(stm32f4xx_lib ${STM32F4_LIB_SRC})

target_compile_definitions(stm32f4xx_lib PUBLIC -DUSE_STDPERIPH_DRIVER -D${MCU_FAMILY})

#target_link_libraries(stm32f4xx_hal PUBLIC cmsis)
target_include_directories(stm32f4xx_lib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
  PRIVATE src)
