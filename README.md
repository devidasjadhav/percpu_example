# percpu_example
Linux kernel percpu kernel example

# Building code
make

# instering Module
insmod percpu_example.ko

# Testing code

beta:~ # taskset -c 1 echo "test1" > /sys/module/percpu_example/parameters/mybuf

beta:~ # taskset -c 1 cat /sys/module/percpu_example/parameters/mybuf

test1

beta:~ # taskset -c 2 echo "test2" > /sys/module/percpu_example/parameters/mybuf

beta:~ # taskset -c 1 cat /sys/module/percpu_example/parameters/mybuf

test1

beta:~ # taskset -c 2 cat /sys/module/percpu_example/parameters/mybuf

test2

# removin Module
rmmod percpu_example
