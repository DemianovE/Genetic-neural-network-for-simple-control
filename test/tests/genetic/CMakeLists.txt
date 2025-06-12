# add matrix test executable
add_executable(test_genetic_operations
        test/tests/genetic/test_genetic_operations.c
        # headers for the toolbox
        include/toolbox/genetic/genetic_operations.h
        include/toolbox/genetic/population.h
        include/toolbox/general/sort.h
        include/toolbox/general/general_math.h
        # executables of toolbox
        src/toolbox/genetic/genetic_operations.c
        src/toolbox/genetic/population.c
        src/toolbox/general/sort.c
        src/toolbox/general/general_math.c)

add_executable(test_population
        test/tests/genetic/test_population.c
        # headers for the toolbox
        include/toolbox/genetic/population.h
        include/toolbox/general/sort.h
        include/toolbox/general/general_math.h
        # executables of toolbox
        src/toolbox/genetic/population.c
        src/toolbox/general/sort.c
        src/toolbox/general/general_math.c)

target_compile_features(test_genetic_operations PRIVATE c_std_99)
target_link_libraries(test_genetic_operations m unity_testlib)

target_compile_features(test_population PRIVATE c_std_99)
target_link_libraries(test_population m unity_testlib)

add_test(NAME test_genetic_operations COMMAND test_genetic_operations)
add_test(NAME test_population COMMAND test_population)