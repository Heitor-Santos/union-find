import fs from 'fs'
import {parse} from 'json2csv'

function realTimeToMilliseconds(realTime) {
    // Expressão regular para extrair minutos e segundos
    const regex = /(\d+)m(\d+),(\d+)s/;

    // Executa a expressão regular na string de tempo real
    const match = regex.exec(realTime);

    // Verifica se houve correspondência
    if (match) {
        // Extrai minutos, segundos e milissegundos da correspondência
        const minutes = parseInt(match[1]);
        const seconds = parseInt(match[2]);
        const milliseconds = parseInt(match[3]);

        // Converte para milissegundos
        const totalMilliseconds = (minutes * 60 * 1000) + (seconds * 1000) + milliseconds;
        return totalMilliseconds;
    } else {
        // Retorna -1 se não houver correspondência
        return -1;
    }
}

function extractTime(fileName){
    const regex = /real (\d+m\d+,\d+s)/;
    let file = fs.readFileSync(fileName).toString();
    let realTime = regex.exec(file)[1];
    let realMiliTime = realTimeToMilliseconds(realTime);
    return realMiliTime
}

function getTimeMetrics(){
    const options=["nodes", "edges", "removed_nodes"];
    for(let option of options){
        let opts = {fields: [option, 'original', 'improved']}
        let allResults = []
        for(let i=1;i<=10;i++){
            let origsTime = []
            let impsTime = [] 
            for(let folder=1;folder<=10;folder++){
                let origFile = `./time_${option}_${folder}/original_${i*1000}_nodes_time`
                let origTime = extractTime(origFile);
                let impFile = `./time_${option}_${folder}/improved_${i*1000}_nodes_time`
                let impTime = extractTime(impFile);
                origsTime.push(origTime);
                impsTime.push(impTime);
                //console.log(origTime, impTime);
            }
            let avgOrigTime = origsTime.reduce((prev,curr)=>prev+curr,0)/10;
            let avgImpTime = impsTime.reduce((prev,curr)=>prev+curr,0)/10;
            console.log(avgOrigTime, avgImpTime)
            let res=  {removed_nodes: i*500, original: avgOrigTime, improved: avgImpTime}
            let value = i*1000;
            if(option=="removed_nodes")value = i*500;
            res[option]=value; 
            allResults.push(res);
        }
        
        fs.writeFileSync(`${option}_time_sheet.csv`,parse(allResults, opts))
    }
}

function extractMemory(file){
    let fileText = fs.readFileSync(file).toString();
    return parseInt(fileText.split("\n")[1]);
}


function getMemoryMetrics(){
    let opts = {fields: ['removed_nodes', 'original', 'improved']}
    let allResults = []
    for(let i=1;i<=10;i++){
        let origsMem = []
        let impsMem = [] 
        for(let folder=1;folder<=10;folder++){
            let origFile = `./mem_rem_nodes${folder}/original_${i*1000}_nodes_memory`
            let origMem = extractMemory(origFile);
            let impFile = `./mem_rem_nodes${folder}/improved_${i*1000}_nodes_memory`
            let impMem = extractMemory(impFile);
            origsMem.push(origMem);
            impsMem.push(impMem);
            //console.log(origTime, impTime);
        }
        let avgOrigMem = origsMem.reduce((prev,curr)=>prev+curr,0)/10;
        let avgImpMem = impsMem.reduce((prev,curr)=>prev+curr,0)/10;
        //console.log(avgOrigMem, avgImpMem)
        let res=  {removed_nodes: i*500, original: avgOrigMem, improved: avgImpMem}
        allResults.push(res);
    }
    
    fs.writeFileSync(`removed_nodes_memory_sheet.csv`,parse(allResults, opts))
}

getTimeMetrics();