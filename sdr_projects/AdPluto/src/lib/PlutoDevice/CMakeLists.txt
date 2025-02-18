# src/libs/PlutoDevice/CMakeLists.txt

set(LD_NAME "PlutoDevice")

# тута указываем зависимости
set(LD_DEPENDENCIES) 

add_library(${LD_NAME} 
    STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/class/${LD_NAME}.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/helperController.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/helperBuffer.cpp
)

target_include_directories(${LD_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${LD_NAME} PUBLIC ${LD_DEPENDENCIES})