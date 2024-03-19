# Definindo uma lista
lista=("nodes" "edges" "removed_nodes")

# Loop sobre os elementos da lista
for item in "${lista[@]}"; do
    for ((i=1; i<=10; i++)); do
        mkdir temp_nodes_info
        mkdir mem_"$item"_"$i"
        ./run-mem-tests.sh $item
        mv ./improved_* ./temp_nodes_info
        mv ./original_* ./temp_nodes_info
        mv ./input_nodes_* ./temp_nodes_info
        mv ./output_nodes_* ./temp_nodes_info
        mv ./temp_nodes_info/* mem_"$item"_"$i"
        rm -rf ./temp_nodes_info
    done
done
