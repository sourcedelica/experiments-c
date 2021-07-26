#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "catch_tests.h"

struct CatchListener : Catch::TestEventListenerBase {
    using Catch::TestEventListenerBase::TestEventListenerBase; // inherit constructor

    virtual void testCaseStarting(Catch::TestCaseInfo const& testInfo) override {
        CatchTests::currentTestCaseName = testInfo.name;
    }

    virtual void testCaseEnded(Catch::TestCaseStats const& testCaseStats) override {
        CatchTests::currentTestCaseName.clear();
    }

    virtual void sectionStarting(Catch::SectionInfo const& sectionInfo) override {
        CatchTests::currentSectionName = sectionInfo.name;
    }

    virtual void sectionEnded(Catch::SectionStats const& sectionStats) override {
        CatchTests::currentSectionName.clear();
    }
};

CATCH_REGISTER_LISTENER(CatchListener)
