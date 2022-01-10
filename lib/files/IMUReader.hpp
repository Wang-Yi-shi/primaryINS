#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<sstream>
#include <iomanip>

using namespace std;

namespace primaryINS
{

    struct IMUData
    {
        double gyro_x;
        double gyro_y;
        double gyro_z;
        double acc_x;
        double acc_y;
        double acc_z;
    };

    typedef map<double,IMUData> IMUDataMap;

    class IMUReader
    {
    public:
        // Default constructor
        IMUReader() {};
        // Common constructor
        IMUReader(string _filePath);

        void setFilePath(string _filePath);
        void getFilePath(string _filePath);

        IMUDataMap readFile();



    private:
        string filePath;
    };
}


