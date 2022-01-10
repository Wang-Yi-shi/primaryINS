user_name=`echo $USER | sed 's/ /_/g'`
dir_name=./results_${user_name}
if [ ! -d $dir_name ]
then
    mkdir $dir_name
fi

dir_data=./data

imu_file=${dir_data}/Calibration_Data.txt

echo $imu_file

calibration --input $imu_file --help
