#!/bin/bash
RED_COLOR='\033[0;31m'
GREEN_COLOR='\033[0;32m'
YELLOW_COLOR='\033[0;33m'
RESET_COLOR='\033[0m'
FILE=containers
LOG_FILE=logs
# remove previous outputs
rm -rf containers.std containers.ft ft_out std_out logs

mkdir logs

namespaces="std ft"
for ns in $namespaces
do
    echo -e "${YELLOW_COLOR}Compiling with $ns... Wait a sec.${RESET_COLOR}"
    make $ns > /dev/null
    if [ ! -f "${FILE}" ]
    then
        echo -e "${RED}KO: Compilation error${RESET_COLOR} log in file logs/ft.$FILE.$ns.log"
        make $ns > logs/ft.$FILE.$ns.log
    else
        echo -e "${GREEN_COLOR}${FILE} generated!${RESET_COLOR}"
        echo -e "mv $FILE $FILE.$ns"
        mv $FILE $FILE.$ns
    fi
done

if [ -f "${FILE}.ft" ]
then
    echo -e "\nCompare outputs & timing (you can be up to 20 times slower)."
    tests="vector stack map set utility"
    for test in $tests
    do
        echo -e "\n    ./containers $test"
        TIMEFORMAT='    -   ft took %3R seconds.'
        time ./containers.ft $test > ft_out
        TIMEFORMAT='    -   std took %3R seconds.'
        time ./containers.std $test > std_out
        DIFF=$(diff ft_out std_out)
        if [ "${DIFF}" != "" ]
        then
            echo -e "     DIFF: ${RED_COLOR}KO${RESET_COLOR}\tlog in file logs/ft.$test.log"
            diff ft_out std_out > logs/ft.$test.log
        else
            echo -e "      DIFF: ${GREEN_COLOR}OK${RESET_COLOR}"
        fi
    done
fi
LOGS_COUNT=$(ls -l ${LOG_FILE} | wc -l)
# if  no error remove outputs
if [ "${LOGS_COUNT}" > 1 ]
then
    rm -rf containers.std containers.ft ft_out std_out logs
fi

