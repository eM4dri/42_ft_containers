#!/bin/sh
RED_COLOR='\033[0;31m'
GREEN_COLOR='\033[0;32m'
YELLOW_COLOR='\033[0;33m'
RESET_COLOR='\033[0m'
FILE=containers

echo "${YELLOW_COLOR}Compiling with std... Wait a sec.${RESET_COLOR}"
make std > /dev/null
if [ ! -f "${FILE}" ]
then
    echo "${RED}KO: Compilation error${RESET_COLOR}"
    make std
else
    echo "${GREEN_COLOR}${FILE} generated!${RESET_COLOR}"
    echo "mv containers containersSTD"
    mv containers containersSTD

    echo "${YELLOW_COLOR}Compiling with ft... Wait a sec.${RESET_COLOR}"
    make ft > /dev/null
    if [ ! -f "${FILE}" ]
    then
        echo "${RED}KO: Compilation error${RESET_COLOR}"
         make ft
    else
        echo "${GREEN_COLOR}${FILE} generated!${RESET_COLOR}"
        echo "mv containers containersFT"
        mv containers containersFT
        
        echo "\nCompare outputs & timing (you can be up to 20 times slower)."
        tests="vector stack map set utility"
        for test in $tests
        do
            echo "\n    ./containers $test" 
            TIMEFORMAT='    -   ft took %3R seconds.'
            time ./containersFT $test > ft_out
            TIMEFORMAT='    -   std took %3R seconds.'
            time ./containersSTD $test > std_out
            DIFF=$(diff ft_out std_out)
            if [ "${DIFF}" != "" ]
            then
                echo "     DIFF: ${RED}KO${RESET_COLOR}"
                diff ft_out std_out
            else
                echo "      DIFF: ${GREEN_COLOR}OK${RESET_COLOR}"
            fi
        done
    fi
fi

