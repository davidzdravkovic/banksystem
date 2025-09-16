cmake_minimum_required(VERSION 3.20)
project(BankSystem VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# PostgreSQL (MSYS2 MinGW)
set(PostgreSQL_ROOT "C:/msys64/mingw64")
list(APPEND CMAKE_PREFIX_PATH "${PostgreSQL_ROOT}")
find_package(PostgreSQL REQUIRED)

# Drogon
set(Drogon_ROOT "C:/drogon_install")
list(APPEND CMAKE_PREFIX_PATH "${Drogon_ROOT}")
find_package(Drogon REQUIRED)

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    C:/drogon_install/include
    ${PostgreSQL_ROOT}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Drogon::Drogon
    pqxx
    pq
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
)
