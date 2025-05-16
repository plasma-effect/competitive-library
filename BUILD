load("define_library_rule.bzl", "cl_library")

filegroup(
    name = "cl_headers",
    srcs = glob(["include/**/*.hpp"]),
    visibility = ["//visibility:public"],
)

cl_library(
    name = "utility",
)

cl_library(
    name = "print_base",
    deps = [
        ":utility",
        "@custom_ac_library//:ac_library",
    ],
)

cl_library(
    name = "debug_print",
    deps = [":print_base"],
)

cl_library(
    name = "normal_print",
    deps = [":print_base"],
)

cl_library(
    name = "numeric",
    deps = [":utility"],
)

cl_library(
    name = "math",
    deps = [":utility"],
)

cl_library(
    name = "segtree",
    deps = [
        ":numeric",
        ":utility",
        "@custom_ac_library//:ac_library",
    ],
)

cl_library(
    name = "rolling_hash",
    deps = [
        ":utility",
        "@boost//:multiprecision",
    ],
)

cl_library(
    name = "graph_warshall_floyd",
    hdrs = ["graph/warshall_floyd.hpp"],
    deps = [":utility"],
)

cl_library(
    name = "graph_topological_sort",
    hdrs = ["graph/topological_sort.hpp"],
    deps = [":utility"],
)

cl_library(
    name = "heuristic_random",
    hdrs = ["heuristic/random.hpp"],
)

cl_library(
    name = "heuristic_time_control",
    hdrs = ["heuristic/time_control.hpp"],
    deps = [":heuristic_random"],
)

cl_library(
    name = "heuristic_static_container",
    hdrs = ["heuristic/static_container.hpp"],
    deps = [
        ":print_base",
        "@boost//:container",
    ],
)

cl_library(
    name = "heuristic_grid_bfs_queue",
    hdrs = ["heuristic/grid_bfs_queue.hpp"],
    deps = [":heuristic_static_container"],
)

cc_library(
    name = "competitive_library",
    hdrs = [":cl_headers"],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = [
        "@boost//:container",
        "@custom_ac_library//:ac_library",
    ],
)
