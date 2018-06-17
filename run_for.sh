# RUN GAP LAHC SCRIPT

# Array params
declare -a arr_inst=("gapa-1.txt" "gapa-2.txt" "gapa-3.txt")
declare -a arr_limit=(500000 750000 1000000)
declare -a arr_alpha=(10 30 50 70 90)
declare -a arr_list=(50 100 200 500 1000)
outDir="./output/output"
count=0

# Compile
make clean
make all

# Loop
for instances in ${arr_inst[@]}; do
for limit in ${arr_limit[@]}; do 
for alpha in ${arr_alpha[@]}; do 
for list in ${arr_list[@]}; 
do
echo "Run GAP LAHC $count"
output="$outDir-limit-$limit-list-$list-alpha-$alpha-in-$instances"
./bin/main $limit $list $alpha < ./instances/$instances > ./output/output
sleep 0.1
echo $output
cp $outDir $output
((count++))
done
done
done
done