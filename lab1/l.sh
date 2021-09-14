#!/bin/bash
date | awk '{print $2,$3,$4}'
whoami
hostname

printf "Процессор: \n"
printf "\tМодель - "
lscpu | grep -e "Model name:" -e "Имя модели:" | awk '{print $3,$4,$5,$6,$7,$8}'

printf "\tАрхитектура - "
lscpu | awk 'FNR == 1 {print $NF}'

printf "\tТактовая частота - "
lscpu | grep -e "CPU МГц:" -e "CPU MHz:" | awk '{print $NF}'

printf "\tКоличество ядер - "
lscpu | grep -e "Core(s) per socket:" -e "Ядер на сокет:" | awk '{print $NF}'

printf "\tКоличество потоков на одно ядро - "
lscpu | grep -e "Потоков на ядро:" -e "Thread(s) per core:" | awk '{print $NF}'

printf "Оперативная память: \n"
free -m | awk 'FNR == 2 {print "\tВсего -",$2,"\n\tДоступно -",$4}'

printf "Жесткий диск: "
df --total --all --si | awk 'END{print "\tВсего -",$2,"\n\tДоступно -",$4,"\n\tСмонтировано в корневую директорию -",$5}'
free -m | awk 'FNR == 3 {print "\tSWAP всего -",$2,"\n\tSWAP доступно -",$4}'

printf "Сетевые интерфейсы: \n"

count=$(ip link |wc -l)
count=$((count/2))

printf "\tКолличество сетевых интерфейсов - %s\n" $count

echo  -e  "\t№\tИмя сетевого интерфейса\t\tMAC адрес\t\tIP адрес\t\tСкорость соединения"

for i in $(seq 1 "$count")
do
printf "\t%s\t" $i
printf "%-32s" $(ifconfig -s | awk -v i=$i 'FNR==i+1 {print $1}')
printf "%-24s" $(ip link | grep 'link' | awk -v i=$i 'FNR==i {print $2}')
printf "%-24s" $(ip address | grep -w 'inet' | awk -v i=$i 'FNR==i {print $2}')
printf "%-10s\n" $(sudo ethtool $(ifconfig -s | awk -v i=$i 'FNR==i+1 {print $1}') | grep Speed | awk '{print $2}')
#printf "%-10s\n" $(cat /sys/class/net/$(ip link | awk -v i=$i 'NR==i+1*(i-1) {print substr($2, 1, length($2)-1)}')/speed | awk '!/cat/')
done