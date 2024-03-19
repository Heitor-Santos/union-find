# Definindo uma lista
lista=("nodes" "edges" "removed_nodes")

if [ -d "mem_results" ]; then
    rm -r "mem_results"
fi
mkdir mem_results

# Loop sobre os elementos da lista
for item in "${lista[@]}"; do
    for ((i=1; i<=10; i++)); do
        mkdir temp_nodes_info
        mkdir mem_results/mem_"$item"_"$i"
        ./run-mem-tests.sh $item
        mv ./improved_* ./temp_nodes_info
        mv ./original_* ./temp_nodes_info
        mv ./input_nodes_* ./temp_nodes_info
        mv ./temp_nodes_info/* mem_results/mem_"$item"_"$i"
        rm -rf ./temp_nodes_info
    done
done
