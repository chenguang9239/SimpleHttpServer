#!/bin/bash

filename=`ls *.h *.cpp | sed '/Socket\|Thread\|Handle\|Parser/d' | awk '{printf $0 " " }'` 

echo
echo $filename
echo

sed -i '1i\\' $filename
sed -i '1i\*/' $filename
sed -i '1i\ * E-mail: wangzhiyiiiii@163.com' $filename
sed -i '1i\ * Author: chenguang9239' $filename
sed -i '1i\/*' $filename

