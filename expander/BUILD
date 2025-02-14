COPTS = [
    "-std=c++20",
    "-Wall",
    "-Wextra",
    "-Wshadow",
    "-Wconversion",
    "-Werror",
]

cc_library(
    name = "lib_expander",
    srcs = ["lib_expander.cpp"],
    hdrs = ["expander.hpp"],
    copts = COPTS,
    includes = ["."],
)

cc_test(
    name = "test_expander",
    srcs = ["test_expander.cpp"],
    copts = COPTS + [
        "-fsanitize=undefined,address",
        "-fno-sanitize-recover=all",
    ],
    linkopts = [
        "-fsanitize=undefined,address",
    ],
    deps = [
        ":lib_expander",
        "@googletest//:gtest",
        "@googletest//:gtest_main",
    ],
)

genrule(
    name = "embedded_headers_source",
    srcs = ["//:cl_headers"],
    outs = ["embedded_headers.cpp"],
    cmd = """
        echo '#include "expander.hpp"' > $@
        echo '#include "get_embedded.hpp"' >> $@
        echo 'namespace {' >> $@
        echo 'source_expander::embedded_data_t get_data_impl() {' >> $@
        echo '  using namespace source_expander;' >> $@
        echo '  embedded_data_t ret;' >> $@
        for file in $(locations //:cl_headers); do
            name=$$(basename $${file})
            echo '  {' >> $@
            echo "    const char* name = \\\"$${name}\\\";" >> $@
            printf '    const char* source = R"embed(' >> $@
            cat $${file} >> $@
            echo ')embed";' >> $@
            echo "    ret.base[name].str(source);" >> $@
            echo "    ret.headers.emplace(name, iref(ret.base[name]));" >> $@
            echo '  }' >> $@
        done
        echo '  return ret;' >> $@
        echo '}' >> $@
        echo '}' >> $@
        echo 'namespace source_expander{' >> $@
        echo '  embedded_data_t get_data() {' >> $@
        echo '    return get_data_impl();' >> $@
        echo '}' >> $@
        echo '}' >> $@
    """,
)

cc_library(
    name = "lib_embedded_headers",
    srcs = [":embedded_headers_source"],
    hdrs = ["get_embedded.hpp"],
    copts = COPTS,
    includes = ["."],
    deps = [":lib_expander"],
)

cc_binary(
    name = "expander",
    srcs = ["expander.cpp"],
    copts = COPTS,
    deps = [
        ":lib_embedded_headers",
        ":lib_expander",
    ],
)
