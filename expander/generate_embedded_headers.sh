cd $(dirname $0)/..
echo '#include "expander.hpp"'
echo '#include "get_embedded.hpp"'
echo 'namespace {'
echo 'source_expander::embedded_data_t get_data_impl() {'
echo '  using namespace source_expander;'
echo '  embedded_data_t ret;'
for file in $(find ./include/ -type f -name '*.hpp'); do
    name=$(echo ${file} | sed 's|^.*include/||')
    echo '  {'
    echo "    const char* name = \"${name}\";"
    printf '    const char* source = R"embed('
    cat ${file}
    echo ')embed";'
    echo "    ret.base[name].str(source);"
    echo "    ret.headers.emplace(name, iref(ret.base[name]));"
    echo '  }'
done
echo '  return ret;'
echo '}'
echo '}'
echo 'namespace source_expander{'
echo '  embedded_data_t get_data() {'
echo '    return get_data_impl();'
echo '}'
echo '}'
