# Definindo uma lista
lista=("nodes" "edges" "removed_nodes")

if [ -d "time_results" ]; then
    rm -r "time_results"
fi
mkdir time_results

# Loop sobre os elementos da lista
for item in "${lista[@]}"; do
    for ((i=1; i<=10; i++)); do
        mkdir temp_nodes_info
        mkdir time_results/time_"$item"_"$i"
        ./run-time-tests.sh $item
        mv ./improved_* ./temp_nodes_info
        mv ./original_* ./temp_nodes_info
        mv ./input_nodes_* ./temp_nodes_info
        mv ./temp_nodes_info/* time_results/time_"$item"_"$i"
        rm -rf ./temp_nodes_info
    done
done