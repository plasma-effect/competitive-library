load(":library_test.bzl", "library_cc_test")

cc_library(
    name = "test_utils",
    hdrs = glob(["test_utils/*.hpp"]),
    strip_include_prefix = "test_utils",
)

library_cc_test(
    name = "graph_topological_sort_test",
    srcs = ["graph/topological_sort.cpp"],
    deps = ["@custom_ac_library//:ac_library"],
)
