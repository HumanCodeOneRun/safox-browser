macro(safox_add_test name)
    add_executable(${name}_test ${name}_test.cpp)
    target_link_libraries(${name}_test PRIVATE safox_lib)

    add_test(NAME ${name}_test COMMAND ${name}_test)
    
    set_property(TARGET ${name}_test PROPERTY FOLDER "tests")
endmacro()

include_sub_directories_recursively(${CMAKE_CURRENT_SOURCE_DIR}/../)

#safox_add_test(user)
#safox_add_test(bookmark)
#safox_add_test(bookmarkgroup)
#safox_add_test(download)
#safox_add_test(homepage)
#safox_add_test(service)
#safox_add_test(history)
#safox_add_test(adblock)
safox_add_test(icon)