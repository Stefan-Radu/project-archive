#!/bin/sh

# cron job
# each dat at 5AM update ip ranges
echo "0 5 * * * cd ${PWD} && ./scripts/update_ranges.sh >> /var/log/cron.log 2>&1
  " > scheduler.txt
crontab scheduler.txt

# wouldn't use docker set env variables without this
printenv | grep -v "no_proxy" >> /etc/environment

rm scheduler.txt

cron -f &

# also update ranges on container creation
./scripts/update_ranges.sh

# run everything else
exec "$@"
