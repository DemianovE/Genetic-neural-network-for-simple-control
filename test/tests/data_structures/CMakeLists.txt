# add matrix test executable
add_executable(test_matrices
        test/tests/data_structures/test_matrices.c
        # headers for the toolbox
        include/toolbox/data_structures/matrix.h
        include/toolbox/neural/activation_fnc.h
        # executables of toolbox
        src/toolbox/neural/activation_fnc.c
        src/toolbox/data_structures/matrix.c)

target_compile_features(test_matrices PRIVATE c_std_99)
target_link_libraries(test_matrices m unity_testlib)

add_test(NAME test_matrices         COMMAND test_matrices)