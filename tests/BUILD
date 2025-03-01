load(":library_test.bzl", "library_cc_test")

library_cc_test(
    name = "utility_test",
    srcs = ["utility.cpp"],
)

library_cc_test(
    name = "print_base_test",
    srcs = ["print_base.cpp"],
)

library_cc_test(
    name = "debug_print_test",
    srcs = ["debug_print.cpp"],
)

library_cc_test(
    name = "normal_print_test",
    srcs = ["normal_print.cpp"],
)

library_cc_test(
    name = "numeric_test",
    srcs = ["numeric.cpp"],
)

library_cc_test(
    name = "segtree_test",
    srcs = ["segtree.cpp"],
)

library_cc_test(
    name = "warshall_floyd_test",
    srcs = ["warshall_floyd.cpp"],
)

test_suite(
    name = "tests",
    tests = [
        ":debug_print_test",
        ":normal_print_test",
        ":numeric_test",
        ":print_base_test",
        ":segtree_test",
        ":utility_test",
        ":warshall_floyd_test",
    ],
)
