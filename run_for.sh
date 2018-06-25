# RUN GAP LAHC SCRIPT

# Array params
declare -a arr_inst=("gapa-1.txt" "gapa-2.txt" "gapa-3.txt" "gapa-4.txt" "gapa-5.txt" "gapa-6.txt" "gapd-1.txt" "gapd-2.txt" "gapd-6.txt")
declare -a arr_limit=(500000 1000)
declare -a arr_alpha=(50 10)
declare -a arr_list=(300 50)
outDir="./output/output"
count=0

# Compile
# make clean
# make all

# Loop
for limit in ${arr_limit[@]}; do 
for instances in ${arr_inst[@]}; do
for alpha in ${arr_alpha[@]}; do 
for list in ${arr_list[@]}; 
do
# make clean
# make all
echo "Run GAP LAHC $count"
output="$outDir-Rel-limit-$limit-list-$list-alpha-$alpha-in-$instances"
./bin/main $limit $list $alpha < ./instances/$instances > ./output/output
echo $output
cp $outDir $output
((count++))
sleep 0.1
done
done
done
done