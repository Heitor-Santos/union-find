import fs from 'fs';

function genereteGraph(numNodes, numEdges){
    const graph = [];
    for (let i = 0; i < numNodes; i++) {
        graph[i]=[];
    }
    
    // Embaralha as arestas para obter uma seleção aleatória
    while(numEdges){
        let i = Math.floor(Math.random() * (numNodes));
        let j = Math.floor(Math.random() * (numNodes));
        if(i!=j && !graph[i].includes(j) && !graph[j].includes(i)){
            graph[i].push(j);
            numEdges--;
        }
    }
    return graph
}

function visitedGraph(graph){
    const visited = []
    for(let i=0;i<graph.length;i++){
        visited[i] = false;
    }
    return visited;
}

// Obter os argumentos da linha de comando
var args = process.argv.slice(2);
//console.log(args)
const graph = genereteGraph(args[0], args[1]);
const visited = visitedGraph(graph);

function shuffle(lista) {
    for (let i = lista.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [lista[i], lista[j]] = [lista[j], lista[i]];
    }
    return lista;
}

function nodesToRemoveNow(a, b, c) {
    const menor = Math.min(a, b, c);
    return Math.floor(Math.random() * (menor + 1)); 
}

function nodesAleatoriosDoSet(conjunto, quantidade) {
    const elementos = Array.from(conjunto); // Converte o conjunto para um array
    const elementosAleatorios = [];

    // Garante que a quantidade solicitada não seja maior do que o tamanho do conjunto
    quantidade = Math.min(quantidade, elementos.length);

    // Embaralha o array de elementos
    for (let i = elementos.length - 1; i >= 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [elementos[i], elementos[j]] = [elementos[j], elementos[i]];
    }

    // Seleciona os primeiros 'quantidade' elementos do array embaralhado
    for (let i = 0; i < quantidade; i++) {
        elementosAleatorios.push(elementos[i]);
    }

    return elementosAleatorios;
}

let addedNodes = new Set();

function dfs(graph, i){
    for(let j=0;j<graph[i].length;j++){
        let currNode = graph[i][j];
        if(visited[currNode] && addedNodes.has(currNode)){
            fs.appendFileSync(fileInput, `union\n`);
            fs.appendFileSync(fileInput, `${i} ${currNode}\n`);
        }
        else if(!visited[currNode]){
            fs.appendFileSync(fileInput, `add\n`);
            fs.appendFileSync(fileInput, `${currNode}\n`);
            fs.appendFileSync(fileInput, `union\n`);
            fs.appendFileSync(fileInput, `${i} ${currNode}\n`);
            addedNodes.add(currNode);
            visited[currNode] = true;
            dfs(graph, currNode);
        }
    }
}

const lista = Array.from({ length: args[0] }, (_, index) => index);
const shuffleNodes = shuffle(lista);
let nodesToRemove = parseInt(args[2])

const fileInput = `${args[3]}_input`

for(let i of shuffleNodes){
    if(!visited[i]){
        fs.appendFileSync(fileInput, `add\n`);
        fs.appendFileSync(fileInput, `${i}\n`);
        visited[i]=true;
        addedNodes.add(i);
        dfs(graph, i);
    }
    if(nodesToRemove>0){
        let toDelete = nodesToRemoveNow(5, nodesToRemove, addedNodes.size)
        let nodesToDelete =nodesAleatoriosDoSet(addedNodes, toDelete);
        for(const el of nodesToDelete){
            addedNodes.delete(el);
            fs.appendFileSync(fileInput, "delete\n");
            fs.appendFileSync(fileInput, `${el}\n`);
        }   
        nodesToRemove-=toDelete;
    }
}

while(nodesToRemove){
    let toDelete = nodesToRemoveNow(1, nodesToRemove, addedNodes.size)
    if(toDelete == 0)break;
    let nodeToDelete = nodesAleatoriosDoSet(addedNodes, toDelete)[0];
    addedNodes.delete(nodeToDelete);
    fs.appendFileSync(fileInput, "delete\n");
    fs.appendFileSync(fileInput, `${nodeToDelete}\n`);
    nodesToRemove--;
}

if(nodesToRemove>0)console.log("falhou em deletar todos, sobram ",nodesToRemove)