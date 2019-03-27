cmake_minimum_required(VERSION 3.0) # setting this is required
project(TeaInsideBot_S6)            # this sets the project name

file(GLOB_RECURSE sources src/*.cpp)
file(GLOB_RECURSE include include/*.hpp)

add_executable(icetea_s6 ${sources} ${include})

SET(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
#set(CMAKE_CXX_FLAGS_MINSIZEREL "put your flags")
#set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "put your flags")
set(CMAKE_CXX_FLAGS_RELEASE "-DESTEH_DEBUG -O3 -s")

# This allows to include files relative to the root of the src directory with a <> pair
target_include_directories(icetea_s6 PUBLIC include)

target_link_libraries(icetea_s6 fcgi++ fcgi curl)
target_compile_options(icetea_s6 PUBLIC -std=c++1y -Wall -Wfloat-conversion)

# This copies all resource files in the build directory.
# We need this, because we want to work with paths relative to the executable.
# file(COPY ${data} DESTINATION resources)

###############################################################################
## dependencies ###############################################################
###############################################################################

# This defines the variables Boost_LIBRARIES that containts all library names
# that we need to link into the program.
# find_package(Boost 1.36.0 COMPONENTS filesystem system REQUIRED)

#target_link_libraries(example PUBLIC
#  ${Boost_LIBRARIES}
  # here you can add any library dependencies
#)

# find_package(nlohmann_json 3.2.0 REQUIRED)
# target_link_libraries(icetea_s6 PRIVATE nlohmann_json::nlohmann_json)


###############################################################################
## testing ####################################################################
###############################################################################

# This is for our testing framework,
# we don't add REQUIRED because it's just for testing.
# People who might want to build the project to use it should not be required
# to install testing dependencies.
find_package(GTest)

if(GTEST_FOUND)
  add_executable(unit_tests ${sources_test} ${sources})

  # This define is added to prevent collision with the main.
  # It might be better solved by not adding the source with the main to the
  # testing target.
  target_compile_definitions(unit_tests PUBLIC UNIT_TESTS)

  # This allows us to use the executable as a link library, and inherit all 
  # linker options and library dependencies from it, by simply adding it as dependency.
  set_target_properties(example PROPERTIES ENABLE_EXPORTS on)

  target_link_libraries(unit_tests PUBLIC
    ${GTEST_BOTH_LIBRARIES}
    example
  )

  target_include_directories(unit_tests PUBLIC
    ${GTEST_INCLUDE_DIRS} # doesn't do anything on linux
  )
  
endif()

###############################################################################
## packaging ##################################################################
###############################################################################

# All install commands get the same destination. this allows us to use paths
# relative to the executable.
install(TARGETS icetea_s6 DESTINATION icetea_s6)

# This is basically a repeat of the file copy instruction that copies the
# resources in the build directory, but here we tell cmake that we want it
# in the package.
# install(DIRECTORY resources DESTINATION example_destination)

# Now comes everything we need, to create a package
# there are a lot more variables you can set, and some
# you need to set for some package types, but we want to
# be minimal here.
set(CPACK_PACKAGE_NAME "TeaInsideBot")
set(CPACK_PACKAGE_VERSION "0.0.1")

# We don't want to split our program up into several incomplete pieces.
set(CPACK_MONOLITHIC_INSTALL 1)

# This must be last
include(CPack)
