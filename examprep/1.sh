array=(1,2,3,4)

echo ${array[0]}

for i in ${array[@]}; do
echo -n $i " "
done
