load(":library_test.bzl", "library_cc_test")

filegroup(
    name = "test_source",
    srcs = glob(["*.cpp"]),
)

cc_library(
    name = "test_async",
    hdrs = ["heuristic/test_async.hpp"],
    strip_include_prefix = "heuristic",
)

library_cc_test(name = "utility_test")

library_cc_test(name = "print_base_test")

library_cc_test(name = "debug_print_test")

library_cc_test(name = "normal_print_test")

library_cc_test(name = "numeric_test")

library_cc_test(name = "segtree_test")

library_cc_test(name = "warshall_floyd_test")

library_cc_test(
    name = "heuristic_random_test",
    srcs = ["heuristic/random.cpp"],
    deps = [":test_async"],
)

library_cc_test(
    name = "heuristic_time_control_test",
    srcs = ["heuristic/time_control.cpp"],
    deps = [":test_async"],
)

library_cc_test(
    name = "heuristic_static_container_test",
    srcs = ["heuristic/static_container.cpp"],
    deps = [
        ":test_async",
        "//:debug_print",
        "//:normal_print",
    ],
)

library_cc_test(
    name = "heuristic_grid_bfs_queue_test",
    srcs = ["heuristic/grid_bfs_queue.cpp"],
    deps = [":test_async"],
)
