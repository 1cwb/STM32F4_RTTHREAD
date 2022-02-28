aux_source_directory(src RTTHREAD_SRC)
aux_source_directory(components/device RTTHREAD_COMP)
aux_source_directory(components/finsh RTTHREAD_FINSH)
aux_source_directory(libcpu/arm/cortex-m4 RTTHREAD_M4)
file(GLOB RT_ASM_FILE libcpu/arm/cortex-m4/*.S)
message(status "${RTTHREAD_SRC} ${RTTHREAD_COMP} ${RTTHREAD_FINSH} ${RTTHREAD_M4} ${RT_ASM_FILE}")
add_library(rtthread_nano ${RTTHREAD_SRC} ${RTTHREAD_COMP} ${RTTHREAD_FINSH} ${RTTHREAD_M4} ${RT_ASM_FILE})

target_compile_definitions(rtthread_nano PUBLIC -DUSE_STDPERIPH_DRIVER -D${MCU_FAMILY})

#target_link_libraries(stm32f4xx_hal PUBLIC cmsis)
target_include_directories(rtthread_nano PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/components/finsh>
  PRIVATE src)
