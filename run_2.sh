# RUN GAP LAHC SCRIPT

# Compile
make clean
make all

echo "gapa-all"
limit=100000
alpha=50
list=100


# ----------------------------------------------------------------------- #

# instances="gapa-1.txt"
# output="rel-output-limit-$limit-list-$list-alpha-$alpha-in-$instances"
# ./bin/main $limit $list $alpha < ./instances/$instances > ./output/$output
# echo $output

# instances="gapa-2.txt"
# output="rel-output-limit-$limit-list-$list-alpha-$alpha-in-$instances"
# ./bin/main $limit $list $alpha < ./instances/$instances > ./output/$output
# echo $output

# instances="gapa-3.txt"
# output="rel-output-limit-$limit-list-$list-alpha-$alpha-in-$instances"
# ./bin/main $limit $list $alpha < ./instances/$instances > ./output/$output
# echo $output

# instances="gapa-4.txt"
# output="rel-output-limit-$limit-list-$list-alpha-$alpha-in-$instances"
# ./bin/main $limit $list $alpha < ./instances/$instances > ./output/$output
# echo $output

# instances="gapa-5.txt"
# output="rel-output-limit-$limit-list-$list-alpha-$alpha-in-$instances"
# ./bin/main $limit $list $alpha < ./instances/$instances > ./output/$output
# echo $output

# instances="gapa-6.txt"
# output="rel-output-limit-$limit-list-$list-alpha-$alpha-in-$instances"
# ./bin/main $limit $list $alpha < ./instances/$instances > ./output/$output
# echo $output

instances="gapd-1.txt"
output="rel-output-limit-$limit-list-$list-alpha-$alpha-in-$instances"
./bin/main $limit $list $alpha < ./instances/$instances > ./output/$output
echo $output

instances="gapd-2.txt"
output="rel-output-limit-$limit-list-$list-alpha-$alpha-in-$instances"
./bin/main $limit $list $alpha < ./instances/$instances > ./output/$output
echo $output

instances="gapd-6.txt"
output="rel-output-limit-$limit-list-$list-alpha-$alpha-in-$instances"
./bin/main $limit $list $alpha < ./instances/$instances > ./output/$output
echo $output