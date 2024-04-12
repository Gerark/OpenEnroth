#include <filesystem>
#include <string>
#include <vector>
#include <utility>

#include "Testing/Unit/UnitTest.h"

#include "Library/Lod/LodReader.h"
#include "Library/Lod/LodWriter.h"

#include "Utility/Streams/BlobOutputStream.h"

UNIT_TEST(LodWriter, TestWrite) {
    LodInfo info;
    info.version = LOD_VERSION_MM7;
    info.description = "Some LOD";
    info.rootName = "data";

    std::string file1 = "123";
    std::string file2 = "a";
    std::string file3 = "";
    std::string file4 = std::string(1'000'000, '0');

    Blob lod;
    BlobOutputStream stream(&lod);

    LodWriter writer(&stream, "some.lod", info);
    writer.write("1", Blob::view(file1));
    writer.write("2", Blob::view(file2));
    writer.write("3", Blob::view(file3));
    writer.write("4", Blob::view(file4));
    writer.close();
    stream.close();

    LodReader reader(std::move(lod), "some.lod");
    EXPECT_EQ(reader.ls(), (std::vector<std::string>{"1", "2", "3", "4"}));
    EXPECT_EQ(reader.info().rootName, info.rootName);
    EXPECT_EQ(reader.info().description, info.description);
    EXPECT_EQ(reader.info().version, info.version);
    EXPECT_TRUE(reader.exists("1"));
    EXPECT_TRUE(reader.exists("2"));
    EXPECT_TRUE(reader.exists("3"));
    EXPECT_TRUE(reader.exists("4"));
    EXPECT_EQ(reader.read("1").string_view(), file1);
    EXPECT_EQ(reader.read("2").string_view(), file2);
    EXPECT_EQ(reader.read("3").string_view(), file3);
    EXPECT_EQ(reader.read("4").string_view(), file4);
}

UNIT_TEST(LodWriter, Overwrite) {
    std::string fileName = "tmp.lod";

    auto cleanup = [&] {
        std::error_code ec;
        std::filesystem::remove(fileName, ec);
    };
    cleanup(); // Just in case.

    std::string file1 = "123";
    std::string file2 = "a";
    std::string file2_2 = "b";

    LodInfo info;
    info.version = LOD_VERSION_MM6;
    info.description = "Test LOD";
    info.rootName = "Hello";

    LodWriter writer0(fileName, info);
    writer0.write("1", Blob::view(file1));
    writer0.write("2", Blob::view(file2));
    writer0.close();

    LodReader reader(fileName);

    // Writing into the same LOD while also reading from it is OK...
    LodWriter writer1(fileName, reader.info());
    for (const std::string &name : reader.ls())
        writer1.write(name, reader.read(name));
    writer1.write("2", Blob::view(file2_2));

    // ...as long as you close them in the right order.
    reader.close();
    writer1.close();

    reader.open(fileName);
    EXPECT_EQ(reader.info().version, info.version);
    EXPECT_EQ(reader.info().description, info.description);
    EXPECT_EQ(reader.info().rootName, info.rootName);
    EXPECT_TRUE(reader.exists("1"));
    EXPECT_TRUE(reader.exists("2"));
    EXPECT_EQ(reader.read("1").string_view(), file1);
    EXPECT_EQ(reader.read("2").string_view(), file2_2);

    cleanup();
}
