add_module(
    NAME Resources
    TYPE STATIC
    SOURCES
        Elements.cpp
        Resource.cpp
    TESTS
        ResourceTests.cpp
        TrackedTests.cpp
)
