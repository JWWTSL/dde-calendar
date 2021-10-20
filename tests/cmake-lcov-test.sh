utdir=build-ut
rm -r $utdir
rm -r ../$utdir
mkdir ../$utdir
cd ../$utdir

cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j16

./tests/dde-calendar-client-test/dde-calendar-test --gtest_output=xml:./report/report_calendar_client.xml
./tests/dde-calendar-service-test/dde-calendar-service-test --gtest_output=xml:./report/report_calendar_service.xml
./tests/dde-online-accounts-test/dde-online-accounts-plugin-test/dde-online-accounts-plugin-test  --gtest_output=xml:./report/doa-plugin.xml
./tests/dde-online-accounts-test/dde-online-accounts-daemon-test/dde-online-accounts-daemon-test  --gtest_output=xml:./report/doa-daemon.xml

workdir=$(cd ../$(dirname $0)/$utdir; pwd)

mkdir -p report
lcov -d $workdir -c -o ./report/coverage.info

lcov --extract ./report/coverage.info '*/calendar-basicstruct/*' '*/calendar-client/*' '*/calendar-service/*' '*/schedule-plugin/*' '*/doa-plugin/*' '*/doa-daemon/*' -o ./report/coverage.info
lcov --remove ./report/coverage.info '*/tests/*' -o  ./report/coverage.info

genhtml -o ./report ./report/coverage.info

exit 0