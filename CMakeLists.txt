#
# CMakeLists.txt
#
#  Created on: 17 may. 2026
#      Author: Ludo
#

# Minimum CMake version.
cmake_minimum_required(VERSION 3.23)

# Project creation.
project(sigfox-device-motherboard)
add_executable(${PROJECT_NAME})

# Use object build mode in all sub-directories.
set(BUILD_MODE "OBJECT")

# Macro to convert options to variables.
macro(add_compilation_flag FLAG_NAME FLAG_DESCRIPTION FLAG_DEFAULT_VALUE)
    option(FLAG_NAME FLAG_DESCRIPTION FLAG_DEFAULT_VALUE)
    set(${FLAG_NAME} ${FLAG_DEFAULT_VALUE} CACHE STRING ${FLAG_DESCRIPTION})
    list(APPEND COMPILATION_FLAGS_LIST ${FLAG_NAME})
endmacro()

# Hardware compilation flags.
set(SDM_HW_VERSION "NONE" CACHE STRING "Hardware version")

# Software compilation flags.
add_compilation_flag(SDM_MODE_CLI "Enable command line mode." OFF)

# Hardware specific settings.
# SDM HW1.0.
if(SDM_HW_VERSION STREQUAL "HW1_0")   
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-m0plus -O1")
    set(SDM_MCU "stm32l0xx")
    set(PROJECT_LINKER_SCRIPT "stm32l051x8xx.ld")
# Unknown version.
else()
    message(FATAL_ERROR "Invalid hardware version.")
endif()
set(PROJECT_LINKER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/drivers/device/${SDM_MCU}-device/linker")

# Add hardware compilation flags.
add_compile_definitions(
    __SDM_FLAGS_H__
    ${SDM_HW_VERSION}
)

# Add software compilation flags.
foreach(FLAG ${COMPILATION_FLAGS_LIST})
    # Macros only defined.
    if(${FLAG} STREQUAL ON)
        add_compile_definitions(${FLAG})
    endif()
    # Macros with value.
    if((NOT ${FLAG} STREQUAL OFF) AND (NOT ${FLAG} STREQUAL ON))
        set(${FLAG} "(${${FLAG}})")
        add_compile_definitions(${FLAG}=${${FLAG}}) 
    endif()
endforeach()

# Add project sources files.
target_sources(${PROJECT_NAME}
    PRIVATE
        drivers/peripherals/src/mcu_mapping.c
        drivers/components/src/aht2x_hw.c
        drivers/components/src/lis2dh12_hw.c
        drivers/components/src/ltr329_hw.c
        drivers/components/src/s2lp_hw.c
        drivers/components/src/sensors_hw.c
        drivers/utils/src/terminal_hw.c
        middleware/analog/src/analog.c
        middleware/cli/src/cli.c
        middleware/power/src/power.c
        middleware/sigfox/sigfox-ep-lib/src/core/TI_aes_128_encr_only.c
        middleware/sigfox/src/mcu_api.c
        middleware/sigfox/src/rf_api.c
        application/src/main.c
)

# Project include folders.
include_directories(${PROJECT_NAME}
    PRIVATE
        drivers/device/inc
        drivers/registers/inc
        drivers/registers/${SDM_MCU}-registers/inc
        drivers/peripherals/inc
        drivers/peripherals/${SDM_MCU}-drivers/inc
        drivers/utils/inc
        drivers/utils/embedded-utils/inc
        drivers/components/inc
        drivers/components/aht2x-driver/inc
        drivers/components/lis2dh12-driver/inc
        drivers/components/ltr329-driver/inc
        drivers/components/s2lp-driver/inc
        middleware/analog/inc
        middleware/cli/inc
        middleware/power/inc
        middleware/sigfox/inc
        middleware/sigfox/sigfox-ep-lib/inc
        middleware/sigfox/sigfox-ep-addon-rfp/inc
        application/inc
)

# Add submodules sources files.
add_subdirectory(drivers/device/${SDM_MCU}-device EXCLUDE_FROM_ALL)
add_subdirectory(drivers/peripherals/${SDM_MCU}-drivers EXCLUDE_FROM_ALL)
add_subdirectory(drivers/utils/embedded-utils EXCLUDE_FROM_ALL)
add_subdirectory(drivers/components/aht2x-driver EXCLUDE_FROM_ALL)
add_subdirectory(drivers/components/lis2dh12-driver EXCLUDE_FROM_ALL)
add_subdirectory(drivers/components/ltr329-driver EXCLUDE_FROM_ALL)
add_subdirectory(drivers/components/s2lp-driver EXCLUDE_FROM_ALL)
add_subdirectory(middleware/sigfox/sigfox-ep-lib EXCLUDE_FROM_ALL)
add_subdirectory(middleware/sigfox/sigfox-ep-addon-rfp EXCLUDE_FROM_ALL)

# Link libraries.
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${SDM_MCU}-device
        ${SDM_MCU}-drivers
        embedded-utils
        aht2x-driver
        lis2dh12-driver
        ltr329-driver
        s2lp-driver
        sigfox_ep_lib_obj
        sigfox_ep_addon_rfp_obj
        c_nano
        nosys
        gcc
)

# Linker and artifact.
include(script/cmake-arm-none-eabi/linker.cmake)
include(script/cmake-arm-none-eabi/artifact.cmake)
