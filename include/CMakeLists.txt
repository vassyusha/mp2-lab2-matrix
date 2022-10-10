set(target ${MP2_LIBRARY})

file(GLOB hdrs "*.h*")

add_custom_target(${target} STATIC ${hdrs})
