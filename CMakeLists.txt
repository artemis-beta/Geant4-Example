
    #setup the project
    cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED True)

    project(basicProject)

    find_package(Geant4 REQUIRED ui_all vis_all)
    find_package(Geant4 REQUIRED)
    include(${Geant4_USE_FILE})


    #----------------------------------------------------------------------------
    # Add the executable, and link it to the Geant4 libraries
    
    file(GLOB sources ${CMAKE_SOURCE_DIR}/src/*.cxx)

    add_executable(MaterialTesting ${CMAKE_SOURCE_DIR}/MaterialTesting.cxx ${sources} ${headers})
    target_include_directories(MaterialTesting PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_include_directories(MaterialTesting PUBLIC ${CMAKE_SOURCE_DIR}/third_party/tomlplusplus/include)
    target_include_directories(MaterialTesting PUBLIC ${CMAKE_SOURCE_DIR}/third_party/taywee_args/)
    target_link_libraries(MaterialTesting ${Geant4_LIBRARIES})

    add_custom_target(basicProject DEPENDS MaterialTesting)

    #----------------------------------------------------------------------------
    # Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
    #
    install(TARGETS MaterialTesting DESTINATION bin)