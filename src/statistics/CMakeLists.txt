add_module(
    NAME Statistics
    TYPE STATIC
    SOURCES
        Tracker.cpp
    TESTS
        HistoryTests.cpp
        TrackerTests.cpp
    DEPENDENCIES
        Common
)
