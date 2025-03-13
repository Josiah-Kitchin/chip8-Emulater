

#include "memory.hpp"
#include <gtest/gtest.h>

TEST(Memory, read_write)
{
    // Test valid reads and write to memory
    Memory memory;
    memory.write(1000, 5);
    uint8_t value = memory.read(1000);
    ASSERT_EQ(value, 5);
}

TEST(Memory, out_of_range_write)
{
    Memory memory;
    ASSERT_THROW(memory.write(4096, 5), std::out_of_range);
}

TEST(Memory, out_of_range_read)
{
    Memory memory;
    ASSERT_THROW(memory.read(4096), std::out_of_range);
}
