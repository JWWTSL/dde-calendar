#!/bin/bash
workspace=$1

cd $workspace

dpkg-buildpackage -b -d -uc -us

project_path=$(cd `dirname $0`; pwd)
#获取工程名
project_name="${project_path##*/}"
echo "project name is: $project_name"

#获取打包生成文件夹路径
pathname=$(find . -name obj*)

echo $pathname

cd $pathname/tests

mkdir -p coverage

#针对当前目录进行覆盖率操作
extract_info="*/calendar-basicstruct/* */calendar-client/* */calendar-service/* */schedule-plugin/*"  

lcov -d ./coverage -c -o ./coverage/coverage.info

lcov --directory ../ --capture --output-file ./coverage/coverage.info

lcov --extract ./coverage/coverage.info $extract_info --output-file  ./coverage/coverage.info

lcov --list-full-path -e ./coverage/coverage.info –o ./coverage/coverage-stripped.info

mkdir ../report
genhtml -o ../report ./coverage/coverage.info

lcov -d $build_dir –z

exit 0