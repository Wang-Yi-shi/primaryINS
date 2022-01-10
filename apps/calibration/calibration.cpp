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
#include <iomanip>

#include "IMUReader.hpp"

#define debug 1

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

    string helpInfo="Usage:\n"
                    " \n"
                    "required options:\n"
                    "    --input  <input_imu_file_path>   input imu file\n"
                    "optional options:\n"
                    "    --output <output_imu_file_name>  output imu file\n"
                    "    --help                           Prints this help\n"
                    " \n"
                    "Examples:\n"
                    "calibration --file ./test.txt --output ./result.txt \n"
                    " \n"
                    "Author:\n"
                    "   written by  wang yishi, 2022\n"
                    "   email: 1297366455@qq.com ";

    string inputImuFile;
    string outputImuFile;

    while((arg=getopt_long(argc,argv,shortOptStr,longopts,NULL))!=-1)
    {
        switch(arg)
        {
            ///Usage information
            case 'h':
                cout<<helpInfo<<endl;
                break;
            case 'i':
                cout<<"The file path is: "<<optarg<<endl;
                inputImuFile = optarg;
                break;
            case 'o':
                cout<<"The output file path is :"<<optarg<<endl;
                outputImuFile = optarg;
                break;
            default:
                cout<<"Invalid argument!"<<endl;
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

    IMUDataMap imuData;
    imuData = imuReader.readFile();

    cout<<"--------start process--------"<<endl;

    ///test whether the read function is succeed
    if(debug)
    {
        for(auto it = imuData.begin();it!=imuData.end();++it)
        {
            cout<< setiosflags(ios::fixed);
            cout<< setprecision(4)
                <<(*it).first<<" "
                << setprecision(6)
                <<(*it).second.gyro_x<<" "
                <<(*it).second.gyro_y<<" "<<(*it).second.gyro_z<<" "
                <<(*it).second.acc_x<<" "<<(*it).second.acc_y<<" "
                <<" "<<(*it).second.acc_z<<endl;
        }
    }

    fstream outFileStream(outputImuFile.c_str(),ios::out);
    
    for(auto it=imuData.begin();it!=imuData.end();++it)
    {
        outFileStream<< setiosflags(ios::fixed);
        outFileStream<< setprecision(4)
                     <<(*it).first<<" "
                     << setprecision(6)
                     <<(*it).second.gyro_x<<" "
                     <<(*it).second.gyro_y<<" "
                     <<(*it).second.gyro_z<<endl;
    }


    outFileStream.close();

    return 0;
}
