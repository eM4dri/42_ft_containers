#!/bin/bash
RED_COLOR='\033[0;31m'
GREEN_COLOR='\033[0;32m'
YELLOW_COLOR='\033[0;33m'
RESET_COLOR='\033[0m'
FILE=containers

echo -e "${YELLOW_COLOR}Compiling with std... Wait a sec.${RESET_COLOR}"
make std > /dev/null
if [ ! -f "${FILE}" ]
then
    echo -e "${RED}KO: Compilation error${RESET_COLOR}"
    make std
else
    echo -e "${GREEN_COLOR}${FILE} generated!${RESET_COLOR}"
    echo -e "mv containers containersSTD"
    mv containers containersSTD

    echo -e "${YELLOW_COLOR}Compiling with ft... Wait a sec.${RESET_COLOR}"
    make ft > /dev/null
    if [ ! -f "${FILE}" ]
    then
        echo -e "${RED}KO: Compilation error${RESET_COLOR}"
         make ft
    else
        echo -e "${GREEN_COLOR}${FILE} generated!${RESET_COLOR}"
        echo -e "mv containers containersFT"
        mv containers containersFT

        echo -e "\nCompare outputs & timing (you can be up to 20 times slower)."
        tests="vector stack map set utility"
        for test in $tests
        do
            echo -e "\n    ./containers $test"
            TIMEFORMAT='    -   ft took %3R seconds.'
            time ./containersFT $test > ft_out
            TIMEFORMAT='    -   std took %3R seconds.'
            time ./containersSTD $test > std_out
            DIFF=$(diff ft_out std_out)
            if [ "${DIFF}" != "" ]
            then
                echo -e "     DIFF: ${RED_COLOR}KO${RESET_COLOR}\tlog in file ft.$test.log"
                diff ft_out std_out > ft.$test.log
            else
                echo -e "      DIFF: ${GREEN_COLOR}OK${RESET_COLOR}"
            fi
        done
    fi
fi

rm -f containersSTD containersFT ft_out std_out

