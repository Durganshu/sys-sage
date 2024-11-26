set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake" ${CMAKE_MODULE_PATH})

#defines.hpp header with #cmakedefine 
configure_file(${PROJECT_SOURCE_DIR}/src/defines.hpp.in ${PROJECT_SOURCE_DIR}/src/defines.hpp)

include_directories(external_interfaces)
set(EXT_INTF "external_interfaces")

set(SOURCES
    Component.cpp
    DataPath.cpp
    xml_dump.cpp
    ${EXT_INTF}/intel_pqos.cpp
    ${EXT_INTF}/proc_cpuinfo.cpp
    ${EXT_INTF}/nvidia_mig.cpp
    parsers/hwloc.cpp
    parsers/caps-numa-benchmark.cpp
    parsers/mt4g.cpp
    parsers/cccbench.cpp
    parsers/qdmi-parser.cpp
    )

set(HEADERS
    sys-sage.hpp
    defines.hpp
    Component.hpp
    DataPath.hpp
    xml_dump.hpp
    parsers/hwloc.hpp
    parsers/caps-numa-benchmark.hpp
    parsers/mt4g.hpp
    parsers/cccbench.cpp
    parsers/qdmi-parser.hpp
    )

add_library(sys-sage SHARED ${SOURCES} ${HEADERS})

# For Quantum Systems
# Find QDMI package
find_package(backends REQUIRED)

# Find QInfo package
find_package(qinfo REQUIRED)

# Find nlohmann_json package
find_package(nlohmann_json REQUIRED)

target_link_libraries(sys-sage PUBLIC
  backend_ibm
  qdmi
  qinfo
  nlohmann_json::nlohmann_json
  )


target_include_directories(sys-sage 
    PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  
            $<INSTALL_INTERFACE:inc>
            $<INSTALL_INTERFACE:lib>
)

install(
    TARGETS sys-sage
    EXPORT sys-sage-targets 
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib/cmake/lib
    ARCHIVE DESTINATION lib/cmake/lib
)
#for spack
install(
    EXPORT sys-sage-targets 
    FILE sys-sage-targets.cmake
    DESTINATION lib/cmake/sys-sage
    NAMESPACE sys-sage::
)
install(DIRECTORY "."
    DESTINATION lib/cmake/inc
    FILES_MATCHING PATTERN "*.hpp")

install(
    TARGETS sys-sage
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install(DIRECTORY "."
    DESTINATION inc
    FILES_MATCHING PATTERN "*.hpp")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})