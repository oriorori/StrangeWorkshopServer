find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

add_library(core STATIC
    server.cpp
    session.cpp)

target_include_directories(core PUBLIC 
    ${Boost_INCLUDE_DIRS} 
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(core PUBLIC 
    ${Boost_LIBRARIES} 
    Threads::Threads
)