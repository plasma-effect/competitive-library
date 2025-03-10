load("define_library_rule.bzl", "cl_library")

filegroup(
    name = "cl_headers",
    srcs = glob(["include/*.hpp"]),
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
    name = "segtree",
    deps = [
        ":numeric",
        ":utility",
        "@custom_ac_library//:ac_library",
    ],
)

cl_library(
    name = "warshall_floyd",
    deps = [":utility"],
)

cl_library(
    name = "heuristic",
    deps = [
        ":utility",
        "@boost//:container",
    ],
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
