#! /bin/sh
### BEGIN INIT INFO
# Provides:          cobaya
# Required-Start:    mysql
# Required-Stop:     
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: cobaya service
# Description:       This file should be used to construct scripts to be
#                    placed in /etc/init.d.
### END INIT INFO

PATH=/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin
PATH=$PATH:/home/lijianguo/work/cobaya/bin

LD_LIBRARY_PATH=/home/lijianguo/work/cobaya/bin/lib

export PATH
export LD_LIBRARY_PATH

# Some things that run always

case "$1" in
  start)
	/home/lijianguo/work/cobaya/bin/watch &
	;;
esac
