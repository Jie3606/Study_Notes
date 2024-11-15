#!/bin/bash

# $1= test case name
# $2= purpose

function func_ethernet_speed_duplex () {
    local purpose=$(unpack_by_space "${2}")
    local result=""
    local expect_result="Local time: 五 2024-11-15 09:25:18 CST\n\
            \tUniversal time: 五 2024-11-15 01:25:18 UTC\n\
            \tRTC time: 五 2024-11-15 01:25:18\n\
            \tTime zone: Asia/Taipei (CST, +0800)\n\
            \tSystem clock synchronized: yes\n\
            \tNTP service: active\n\
            \tRTC in local TZ: no"
    local criteria="Do the action happened correctly?\n\tSystem clock synchronized: no\n\tNTP service: active\n\tRTC in local TZ: no=pass\n\other output=fail"
    local host_machine_step=""
    local target_machine_step=""

    IFS= read -r -d '' host_machine_step <<EOF
host machine:
    no-operation
EOF
    IFS='' read -r -d '' target_machine_step <<EOF
target machine:
    1. enter the following command to check the current time config:
        # timedatectl
    2. enter the following command to disable ntp:
        # timedatectl set-ntp 0
    3. enter the following command to change time manually:
        # date -s "20240819 14:02:41"
    4. enter the following command to write the time to RTC:
        # hwclock -w
    5. enter the following command to confirm whether the local time is the same as the rtc time:
        # timedatectl
    6. power off the c8015 & completely remove power/Ethernet.
    7. connect the power and boot again.
    8. enter the following command again to check the current time
        # timedatectl
EOF

    echo -e "Test Case: ${1}" > $(tty)
    echo -e "Purpose: $purpose" > $(tty)
    echo -e "Step:" > $(tty)
    echo -e "$host_machine_step" > $(tty)
    echo -e "$target_machine_step" > $(tty)
    echo -e "Outcome:\n\t$expect_result" > $(tty)
    echo -e "Verification:\n\t$criteria" > $(tty)
    read -p "${yellow}0= pass, 1= fail, other=skip. input:${color_off}" result
    echo "" > $(tty)

if [ $result == $EXIT_GENE_ERROR ]; then
        record_script_result $FUNCNAME $TEST_RESULT_FAIL
        return $EXIT_GENE_ERROR
elif [ $result == $EXIT_SUCCESS ]; then
record_script_result $FUNCNAME $TEST_RESULT_PASS
    return $EXIT_SUCCESS
    else
        record_script_result $FUNCNAME "$TEST_RESULT_NOT_TESTED"
        return $EXIT_NOT_TESTED
    fi
}
