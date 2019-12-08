# ---------------------------------------------------------------------------
# IMLAB
# ---------------------------------------------------------------------------

include(ExternalProject)
find_package(Git REQUIRED)

# Rapidjson has some problems with Clang>=5
# See https://bugs.freebsd.org/bugzilla/show_bug.cgi?id=220388
# Disable all warnings:
set(CMAKE_CXX_FLAGS_RAPIDJSON "${CMAKE_CXX_FLAGS} -w")

# Get rapidjson
ExternalProject_Add(
    rapidjson_src
    PREFIX "vendor/rapidjson"
    GIT_REPOSITORY "https://github.com/Tencent/rapidjson.git"
    GIT_TAG f54b0e47a08782a6131cc3d60f94d038fa6e0a51
    TIMEOUT 10
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/vendor/rapidjson
        -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS_RAPIDJSON}
    UPDATE_COMMAND ""
    BUILD_BYPRODUCTS <INSTALL_DIR>/lib/libgtest.a
)

# Prepare rapidjson
ExternalProject_Get_Property(rapidjson_src install_dir)
set(RAPIDJSON_INCLUDE_DIR ${install_dir}/include)
set(RAPIDJSON_LIBRARY_PATH ${install_dir}/lib/libgtest.a)
file(MAKE_DIRECTORY ${RAPIDJSON_INCLUDE_DIR})
add_library(rapidjson STATIC IMPORTED)
set_property(TARGET rapidjson PROPERTY IMPORTED_LOCATION ${RAPIDJSON_LIBRARY_PATH})
set_property(TARGET rapidjson APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${RAPIDJSON_INCLUDE_DIR})

# Dependencies
add_dependencies(rapidjson rapidjson_src)
