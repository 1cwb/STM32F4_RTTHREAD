aux_source_directory(. SYSTEM_LIB_SRC)

add_library(syslib ${SYSTEM_LIB_SRC})
target_link_libraries(syslib PUBLIC stm32f4xx_lib)
#target_compile_definitions(stm32f4xx_lib PUBLIC -DUSE_STDPERIPH_DRIVER -D${MCU_TYPE})

#target_link_libraries(stm32f4xx_hal PUBLIC cmsis)
#target_include_directories(stm32f4xx_lib PUBLIC
#  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
#  PRIVATE src)
