#add_subdirectory(test)
add_library(indexlib_jsonlib STATIC
        json_reader.cpp
        json_value.cpp
        json_writer.cpp
        jsonutil.cpp
        )

add_public_headers(HEADERS
        json_batchallocator.h
        autolink.h
        config.h
        features.h
        forwards.h
        json.h
        reader.h
        value.h
        writer.h
        jsonutil.h
        )