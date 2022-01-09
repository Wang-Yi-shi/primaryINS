#!/bin/bash
#
#  自动安装脚本
#  为了避免软件重复编译且保持编译版本的统一，
#  我们将获取当前软件名字，并创建与名字对应的build路径，
#  在对应的路径下进行编译。
#
#########################

# 获取当前文件的绝对路径
dir=$(dirname $(readlink -f "$0"))
echo $dir

#截取软件的名字
source_name=${dir##*/}
echo ${source_name}

#创建软件对应的build目录，防止用户中存在一个build目录
mkdir ../build_${source_name}
cd ../build_${source_name}

#制定安装路径
cmake -DCMAKE_INSTALL_PREFIX=~/bin ../${source_name}/
make -j6
make install
