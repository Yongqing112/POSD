#include "../src/hello.h"

TEST(HelloTest, SayHello) {
  ASSERT_EQ("hello, world", sayHello("world"));
}
