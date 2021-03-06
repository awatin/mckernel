#!/bin/sh

USELTP=0
USEOSTEST=1

. ../../common.sh

sudo /bin/sh ${OSTESTDIR}/util/insmod_test_drv.sh
${MCEXEC} ./CT_001
sudo /bin/sh ${OSTESTDIR}/util/rmmod_test_drv.sh


tid=001
echo "*** RT_$tid start *******************************"
sudo ${MCEXEC} ${TESTMCK} -s procfs -n 0 2>&1 | tee ./RT_${tid}.txt
if grep -v "RESULT: TP failed" ./RT_${tid}.txt > /dev/null 2>&1 ; then
	echo "*** RT_$tid: PASSED"
else
	echo "*** RT_$tid: FAILED"
fi
echo ""

tid=002
echo "*** RT_$tid start *******************************"
sudo ${MCEXEC} ${TESTMCK} -s procfs -n 1 2>&1 | tee ./RT_${tid}.txt
if grep -v "RESULT: TP failed" ./RT_${tid}.txt > /dev/null 2>&1 ; then
	echo "*** RT_$tid: PASSED"
else
	echo "*** RT_$tid: FAILED"
fi
echo ""

tid=003
echo "*** RT_$tid start *******************************"
sudo ${MCEXEC} ${TESTMCK} -s procfs -n 3 2>&1 | tee ./RT_${tid}.txt
if grep -v "RESULT: TP failed" ./RT_${tid}.txt > /dev/null 2>&1 ; then
	echo "*** RT_$tid: PASSED"
else
	echo "*** RT_$tid: FAILED"
fi
echo ""

tid=004
echo "*** RT_$tid start *******************************"
sudo ${MCEXEC} ${TESTMCK} -s procfs -n 6 2>&1 | tee ./RT_${tid}.txt
if grep -v "RESULT: TP failed" ./RT_${tid}.txt > /dev/null 2>&1 ; then
	echo "*** RT_$tid: PASSED"
else
	echo "*** RT_$tid: FAILED"
fi
echo ""

