# RUN GAP LAHC SCRIPT

# Array params
declare -a arr_inst=("gapa-1.txt" "gapa-2.txt" "gapa-3.txt")
declare -a arr_limit=(2500 10000 50000 100000 500000)
declare -a arr_list=(10 20 40 30 50)
declare -a arr_alpha=(10 30 50 70 90)
outDir="./output/output"
count=0

# Compile
make clean
make all

# Loop
for limit in ${arr_limit[@]}; do 
for list in ${arr_list[@]}; do 
for alpha in ${arr_alpha[@]}; do 
for instances in ${arr_inst[@]}
do
echo "Run GAP LAHC $count"
output="$outDir-limit-$limit-list-$list-alpha-$alpha-in-$instances"
./bin/main $limit $list $alpha < ./instances/$instances > ./output/output
echo $output
cp $outDir $output
((count++))
done
done
done
done