cmake_minimum_required(VERSION 3.20)
project(PlutoSDR LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE Debug)

option(INSTALL_DEPS "Установить зависимости" ON)
option(UNIT_TESTS_ENABLED "Build unit tests" ON)
option(PLUTO_TIMESTAMP "Build pluto with timestamp" ON)

set(PLUTO_INI_CONFIG_PATH "./.conf_ini/pluto_ini_conf.txt")
configure_file(${PLUTO_INI_CONFIG_PATH} ${CMAKE_BINARY_DIR}/${PLUTO_INI_CONFIG_PATH} COPYONLY)

link_directories(${CMAKE_SOURCE_DIR}/lib/static)

include_directories(include)

# Подключаем тесты
enable_testing()

# RF frontend driver
find_package(SoapySDR REQUIRED)

#add_subdirectory(src/lib/PlutoDevice)
add_subdirectory(src/lib/RingBuffer)

set(SHARED_DEPENDENCIES
    #PlutoDevice
    RingBuffer
)

if(UNIT_TESTS_ENABLED)
    add_test(NAME RingBufferTest COMMAND RingBufferTest)
endif()

# add_executable(pluto_main
#     ${SHARED_SOURCE_FILES}
#     src/app/main.cpp
# )
# add_custom_target(run_pluto
#     COMMAND pluto_main ${PLUTO_INI_CONFIG_PATH}
#     DEPENDS pluto_main
#     COMMENT "Запуск pluto_main с конфигами"
# )
# target_include_directories(pluto_main PRIVATE
#     ${CMAKE_SOURCE_DIR}/src/app/main.cpp
#     ${SoapySDR_LIBRARIES}
# )
# target_link_libraries(pluto_main PRIVATE
#     ${SHARED_DEPENDENCIES}
# )

# if(UNIT_TESTS_ENABLED)
#   add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
# endif()
