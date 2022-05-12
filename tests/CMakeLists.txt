macro(folktell_add_test name)
    add_executable(${name}_test ${name}_test.cpp)
    target_link_libraries(${name}_test PRIVATE FolkTell_lib)

    add_test(NAME ${name}_test COMMAND ${name}_test)
    
    set_property(TARGET ${name}_test PROPERTY FOLDER "tests")
endmacro()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/bookmark)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/dao)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/user)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/taskscheduler)
#folktell_add_test(bookmark)
#folktell_add_test(bookmarkgroup)
folktell_add_test(user)