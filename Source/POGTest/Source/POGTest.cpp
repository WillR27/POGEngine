#include <gtest/gtest.h>

#include "POGTest/POGMaths/VectorsTests.h"

namespace my {
    namespace project {
        namespace {

            class Foo
            {
            public:
                int Bar(const std::string asd, const std::string asdas)
                {
                    return 0;
                }
            };

            // The fixture for testing class Foo.
            class FooTest : public ::testing::Test {
            protected:
                // You can remove any or all of the following functions if their bodies would
                // be empty.

                FooTest() {
                    // You can do set-up work for each test here.
                }

                ~FooTest() override {
                    // You can do clean-up work that doesn't throw exceptions here.
                }

                // If the constructor and destructor are not enough for setting up
                // and cleaning up each test, you can define the following methods:

                void SetUp() override {
                    // Code here will be called immediately after the constructor (right
                    // before each test).
                }

                void TearDown() override {
                    // Code here will be called immediately after each test (right
                    // before the destructor).
                }

                // Class members declared here can be used by all tests in the test suite
                // for Foo.
            };

            // Tests that the Foo::Bar() method does Abc.
            TEST_F(FooTest, MethodBarDoesAbc) {
                const std::string input_filepath = "this/package/testdata/myinputfile.dat";
                const std::string output_filepath = "this/package/testdata/myoutputfile.dat";
                Foo f;
                EXPECT_EQ(f.Bar(input_filepath, output_filepath), 0);
            }

            // Tests that Foo does Xyz.
            TEST_F(FooTest, DoesXyz) {
                // Exercises the Xyz feature of Foo.
            }

        }  // namespace
    }  // namespace project
}  // namespace my

int main(int argc, char** argv) 
{
    ::testing::InitGoogleTest(&argc, argv);

    int ret = RUN_ALL_TESTS();

    std::cin.get();

    return ret;
}