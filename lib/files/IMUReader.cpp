#include "IMUReader.hpp"

#define debug 0

namespace primaryINS
{
    IMUReader::IMUReader(string _filePath)
    {
        this->filePath = _filePath;
    }

    void IMUReader::setFilePath(string _filePath)
    {
        this->filePath = _filePath;
    }

    void IMUReader::getFilePath(string _filePath)
    {
        if(this->filePath.size()!=0)
        {
            cout<<"The file path is: "<<this->filePath<<endl;
        }
        else
        {
            cout<<"getFilePath failed, the file path is NULL"<<endl;
        }
    }

    IMUDataMap IMUReader::readFile()
    {
        IMUDataMap imuData;
        if(this->filePath.size()==0)
        {
            cout<<"Sorry, you should set filePath first!"<<endl;
            exit(0);
        }
        else
        {
            fstream inFileStrm(filePath.c_str(),ios::in);
            while(inFileStrm.peek()!=EOF)
            {
                string str="";
                getline(inFileStrm,str);

                double timeStamp;
                IMUData data;

                stringstream  ss(str);
                ss>>timeStamp>>data.gyro_x>>data.gyro_y>>data.gyro_z
                  >>data.acc_x>>data.acc_y>>data.acc_z;

                imuData.insert(pair<double, IMUData> (timeStamp,data));
            }

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
            inFileStrm.close();
            return imuData;
        }
    }
}
