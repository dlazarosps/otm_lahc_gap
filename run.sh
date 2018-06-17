# RUN GAP LAHC SCRIPT
echo "gapa-1"
instances="gapa-1.txt"

limit=500000
alpha=90
# output="$outDir-limit-$limit-list-$list-alpha-$alpha-in-$instances"

output="output-limit-500000-list-300-alpha-10-in-$instances"
./bin/main 500000 300 10 < ./instances/$instances > ./output/$output
echo $output

output="output-limit-500000-list-300-alpha-30-in-$instances"
./bin/main 500000 300 30 < ./instances/$instances > ./output/$output
echo $output

output="output-limit-500000-list-1000-alpha-70-in-$instances"
./bin/main 500000 1000 70 < ./instances/$instances > ./output/$output
echo $output

list=50
output="output-limit-$limit-list-$list-alpha-$alpha-in-$instances"
./bin/main $limit $list $alpha < ./instances/$instances > ./output/$output
echo $output

list=100
output="output-limit-$limit-list-$list-alpha-$alpha-in-$instances"
./bin/main $limit $list $alpha < ./instances/$instances > ./output/$output
echo $output

list=200
output="output-limit-$limit-list-$list-alpha-$alpha-in-$instances"
./bin/main $limit $list $alpha < ./instances/$instances > ./output/$output
echo $output

list=300
output="output-limit-$limit-list-$list-alpha-$alpha-in-$instances"
./bin/main $limit $list $alpha < ./instances/$instances > ./output/$output
echo $output

list=500
output="output-limit-$limit-list-$list-alpha-$alpha-in-$instances"
./bin/main $limit $list $alpha < ./instances/$instances > ./output/$output
echo $output

list=1000
output="output-limit-$limit-list-$list-alpha-$alpha-in-$instances"
./bin/main $limit $list $alpha < ./instances/$instances > ./output/$output
echo $output

