#!/bin/bash

echo -e "\n\n"

echo "Дата: `date +%F`;"
echo "Имя учетной записи: `whoami`;"
echo "Доменное имя ПК: `hostname`;"

echo "Процессор:"
echo -n -e "\tМодель -"
lscpu|grep "Имя модели" | awk '{$1 = $2 = ""; print $0 ";"}'
echo -n -e "\tАрхитектура - "
lscpu|grep "Архитектура" | awk '{print $2 ";"}'
echo -n -e "\tТактовая частота - "
lscpu|grep "CPU МГц" | awk '{print $3 ";"}'
echo -n -e "\tКоличество ядер - "
lscpu|grep "Ядер на сокет" | awk '{print $4 ";"}'
echo -n -e "\tКоличество потоков на одно ядро - "
lscpu|grep "Потоков на ядро" | awk '{print $4 ";"}'

echo "Оперативная память:"
echo -n -e "\tВсего - "
free --kilo | grep "Память" | awk '{print $2 " KiB;"}'
echo -n -e "\tДоступно - "
free|grep "Память" | awk '{print $7 " KiB;"}'

echo "Жесткий диск:"
echo -n -e "\tВсего - "
# lsblk|grep "sda" | sed -n '1p' | awk '{print $4}'
a=`df -h | grep "/dev/sda7" | awk '{print $2}' | cut -c -3`" GiB;"
echo $a
# a=`df -h | grep "/dev/sda6" | awk '{print $4 " "}'`+" "`df -h | grep "/dev/sda7" | awk '{print $4 ";"}'`
echo -n -e "\tДоступно - "
a=`df -h | grep "/dev/sda7" | awk '{print $4}' | cut -c -3`" GiB;"
echo $a
echo -n -e "\tСмонтировано в корневую директорию / - "
a=`df -h | grep "/dev/sda6" | awk '{print $2 " GiB;"}' | cut -c -2`" GiB;"
echo $a
echo -n -e "\tSWAP всего - "
# lsblk|grep "sda" | sed -n '6p' | awk '{print $4}'
a=`free --kilo | grep "Подкачка" | awk '{print $2}'`
echo $a "KiB;"
echo -n -e "\tSWAP доступно - "
a=`free --kilo | grep "Подкачка" | awk '{print $4}'`
echo $a "KiB;"

echo "Сетевые интерфейсы:"
echo -n -e "\tКоличество сетевых интерфейсов - "
count=0
for iface in $(ifconfig | cut -d ' ' -f1| tr '\n' ' ')
do 
  let count++
done
echo $count

counter=0
echo -e "\t№\tИмя сетевого интерфейса\t\tMAC адрес\t\t\tIP адрес\t\t\tСкорость соединения"
for iface in $(ifconfig | cut -d ' ' -f1| tr '\n' ' ')
do 
  iface=`echo $iface | sed 's/.$//'`
  let counter++
  addr=$(ip -o -4 addr list $iface | awk '{print $4}' | cut -d/ -f1)
  if [ -z $addr ]
  then
  	addr="-------------"
  fi
  link=$(ip link list $iface | grep "link" | awk '{print $2}')
  speed=$(sudo ethtool $iface | grep "Speed" | awk '{print $2}')
  printf "\t$counter\t$iface\t\t\t\t$link\t\t$addr\t\t\t$speed\n"
done

echo -e "\n\n"