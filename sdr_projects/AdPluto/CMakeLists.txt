cmake_minimum_required(VERSION 3.30)
project(PlutoSDR LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE Debug)

option(INSTALL_DEPS "Установить зависимости" ON)
option(UNIT_TESTS_ENABLED "Build unit tests" OFF)
option(PLUTO_TIMESTAMP "Build pluto with timestamp" ON)

set(PLUTO_INI_CONFIG_PATH "./.conf_ini/pluto_ini_conf.txt")
configure_file(${PLUTO_INI_CONFIG_PATH} ${CMAKE_BINARY_DIR}/${PLUTO_INI_CONFIG_PATH} COPYONLY)

# RF frontend driver
find_package(SoapySDR REQUIRED)

add_subdirectory(src/libs/pluto_api)

set(SHARED_DEPENDENCIES
    pluto_api
)

add_executable(pluto_main
    ${SHARED_SOURCE_FILES}
    src/app/main.cpp
)
add_custom_target(run_pluto
    COMMAND pluto_main ${PLUTO_INI_CONFIG_PATH}
    DEPENDS pluto_main
    COMMENT "Запуск pluto_main с конфигами"
)
target_include_directories(pluto_main PRIVATE
    ${CMAKE_SOURCE_DIR}/src/app/main.cpp
    ${SoapySDR_LIBRARIES}
)
target_link_libraries(pluto_main PRIVATE
    ${SHARED_DEPENDENCIES}
)

if(UNIT_TESTS_ENABLED)
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
endif()
