set(LD_NAME "RingBuffer")

add_library(${LD_NAME} STATIC src/${LD_NAME}.cpp)

target_include_directories(${LD_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(UNIT_TESTS_ENABLED)
    enable_testing()
    add_executable(RingBufferTest tests/testBufferPerfomance.cpp)
    target_link_libraries(RingBufferTest PRIVATE ${LD_NAME} benchmark pthread)
    add_test(NAME RingBufferTest COMMAND RingBufferTest)
endif()
