/**
 *  Function:
 *
 *  calibration the IMU
 *
 *  Copyright(c)
 *
 *  Wang-Yi-shi, 2022.1.9, Wuhan University
 */

#include <iostream>
#include <unistd.h>
#include <getopt.h>

#include "IMUReader.hpp"

#define debug 0

using namespace std;
using namespace primaryINS;

int main(int argc, char *argv[])
{
    char arg;
    char shortOptStr[]="hi:o:";

    struct option longopts[]={
            {"help",no_argument, NULL,'h'},
            {"input",required_argument,NULL,'i'},
            {"output",required_argument,NULL,'o'},
            {0,0,0,0},
    };

    string inputImuFile;
    string outputImuFile;

    while((arg=getopt_long(argc,argv,shortOptStr,longopts,NULL))!=-1)
    {
        switch(arg)
        {
            ///Usage information
            case 'h':
                printf("Usage:\n");
                printf(" \n");
                printf("    required options:\n");
                printf("    --input <input_imu_file_path>  input imu file\n");
                printf("    optional options:\n");
                printf("    --output <output_imu_file_name>  output imu file\n");
                printf("    --help                             Prints this help\n");
                printf(" \n");
                printf("Examples:\n");
                printf("    calibration --input ./data/imu.txt\n");
                printf(" \n");
                printf("Author:\n");
                printf("    written by Wang-Yi-shi, 2022\n");
                break;
            case 'i':
                printf("The file path is: %s\n",optarg);
                inputImuFile = optarg;
                break;
            case 'o':
                printf("The output file path is :%s\n",optarg);
                outputImuFile = optarg;
                break;
            default:
                printf("Invalid argument!\n");
                return -1;
        }
    }

    if(inputImuFile.size()!=0&&outputImuFile.size()==0)
    {
        outputImuFile=inputImuFile+".out";
        cout<<"the default path of output file is: "<<outputImuFile<<endl;
    }

    ///now, start read imu data
    IMUReader imuReader(inputImuFile);
    imuReader.readFile();

    IMUDataMap imuData;
    imuData = imuReader.imuData;

    cout<<"-------------------"<<endl;

    ///test whether the read function is succeed
    if(debug)
    {
        for(auto it = imuData.begin();it!=imuData.end();++it)
        {
            cout<<(*it).first<<" "<<(*it).second.gyro_x<<" "
                <<(*it).second.gyro_y<<" "<<(*it).second.gyro_z<<" "
                <<(*it).second.acc_x<<" "<<(*it).second.acc_y<<" "
                <<" "<<(*it).second.acc_z<<endl;
        }
    }

    fstream outFileStream(outputImuFile.c_str(),ios::out);

    double result;

    for(auto it=imuData.begin();it!=imuData.end();++it)
    {
        result = (*it).second.gyro_x+(*it).second.gyro_y+(*it).second.gyro_z;
        outFileStream<<(*it).first<<" "<<result<<endl;
    }


    outFileStream.close();

    return 0;
}
