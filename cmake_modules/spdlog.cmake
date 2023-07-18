# Import spdlog library

include(FetchContent)

# Fetch spdlog library from github
FetchContent_Declare(
    spdlog
    URL https://github.com/gabime/spdlog/archive/refs/tags/v1.10.0.zip
    URL_HASH MD5=031565384b28f29e44c6e7fb247ad48a
    )
FetchContent_MakeAvailable(spdlog)
