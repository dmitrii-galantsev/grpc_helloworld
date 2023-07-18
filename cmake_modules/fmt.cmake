# Import FMT library

include(FetchContent)

# Fetch FMT library from github
FetchContent_Declare(
    fmt
    URL https://github.com/fmtlib/fmt/releases/download/8.1.1/fmt-8.1.1.zip
    URL_HASH MD5=16dcd48ecc166f10162450bb28aabc87
    )
FetchContent_MakeAvailable(fmt)
