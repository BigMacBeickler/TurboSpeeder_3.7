//#include "pch.h"
//#include "gtest/gtest.h"
//#include "../TurboSpeeder_3.7/datacontainer.h"
//#include "../TurboSpeeder_3.7/configcontainer.h"
//#include "../TurboSpeeder_3.7/FileHandler.h"
//
////TEST(TestCaseName, TestName) {
////  EXPECT_EQ(1, 1);
////  EXPECT_TRUE(true);
////}
//
//TEST(DataContainerTest, GetData_ValidFile_ReturnsTrue) {
//    ConfigContainer config;
//    DataContainer data(config);
//    FileHandler file("testdata.txt"); // Provide a valid test file
//    EXPECT_EQ(data.getData(file),1) ;
//}

#include "gtest/gtest.h"
#include "../TurboSpeeder_3.7/datacontainer.h"
#include "../TurboSpeeder_3.7/configcontainer.h"
#include "../TurboSpeeder_3.7/FileHandler.h"
#include <fstream>
#include <cstdio>

// Helper: create a test data file
void CreateTestDataFile(const std::string& filename) {
    std::ofstream ofs(filename);
    // 2 data points, each: time, x, y, z, 9 rotMatrix
    ofs << "0 0 0 0 1 0 0 0 1 0 0 0 1\n";
    ofs << "1 1 2 3 1 0 0 0 1 0 0 0 1\n";
    ofs.close();
}

// Helper: remove file after test
void RemoveFile(const std::string& filename) {
    std::remove(filename.c_str());
}

TEST(DataContainerTest, GetData_ValidFile) {
    std::string filename = "testdata.txt";
    CreateTestDataFile(filename);

    ConfigContainer config;
    DataContainer data(config);
    FileHandler file(filename);

    EXPECT_TRUE(data.getData(file));
    EXPECT_EQ(data.dataField.size(), 2);

    RemoveFile(filename);
}

TEST(DataContainerTest, AverageFilter_Basic) {
    std::string filename = "testdata.txt";
    CreateTestDataFile(filename);

    ConfigContainer config;
    DataContainer data(config);
    FileHandler file(filename);
    data.getData(file);

    // n = 2, should average first point with second
    EXPECT_TRUE(data.averageFilter(2));
    EXPECT_NEAR(data.dataField[0].x, 0.5, 1e-6);
    EXPECT_NEAR(data.dataField[0].y, 1.0, 1e-6);
    EXPECT_NEAR(data.dataField[0].z, 1.5, 1e-6);

    RemoveFile(filename);
}

TEST(DataContainerTest, ApproximateXYZ_ReducesPoints) {
    std::string filename = "testdata.txt";
    CreateTestDataFile(filename);

    ConfigContainer config;
    DataContainer data(config);
    FileHandler file(filename);
    data.getData(file);

    size_t before = data.dataField.size();
    data.approximateXYZ(0.1f); // Should keep both points for a straight line
    size_t after = data.dataField.size();
    EXPECT_LE(after, before);

    RemoveFile(filename);
}

TEST(DataContainerTest, RotationMatrixToEulerAngels_ComputesAngles) {
    std::string filename = "testdata.txt";
    CreateTestDataFile(filename);

    ConfigContainer config;
    DataContainer data(config);
    FileHandler file(filename);
    data.getData(file);

    data.rotationMatrixToEulerAngels();
    // For identity matrix, all angles should be 0
    EXPECT_NEAR(data.dataField[0].A, 0.0, 1e-6);
    EXPECT_NEAR(data.dataField[0].B, 0.0, 1e-6);
    EXPECT_NEAR(data.dataField[0].C, 0.0, 1e-6);

    RemoveFile(filename);
}

TEST(DataContainerTest, GIVEMETHESPEEEEEEEEED_ComputesSpeed) {
    std::string filename = "testdata.txt";
    CreateTestDataFile(filename);

    ConfigContainer config;
    DataContainer data(config);
    FileHandler file(filename);
    data.getData(file);

    data.GIVEMETHESPEEEEEEEEED();
    // Speed between (0,0,0) and (1,2,3) in cm, dt=1
    // distance = sqrt(1^2+2^2+3^2) = sqrt(14) ≈ 3.741657
    // speed = distance / dt * 0.01 = 0.03741657
    EXPECT_NEAR(data.dataField[1].speed, 0.03741657, 1e-6);

    RemoveFile(filename);
}

// Main for Google Test
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}