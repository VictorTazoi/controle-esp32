/* Documento JS implementado na página index.html */
// - Realiza a ação dos Switches;
// - Adiciona, altera e exclui Switches;


/*
========== LEIA A DOCUMENTAÇÃO! ==========
*/

const esp32_server = 'http://192.168.0.120/';

/* AÇÃO DOS SWITCHES */
function switchPressionado(numSwitch, actionSwitch){
    console.log(`${numSwitch}${actionSwitch}`);
    window.location.href = `${esp32_server}${numSwitch}${actionSwitch}`
}

/* DEFINE O NOME DOS SWITCHES */
const switches = `
    <a class="containerSwitch">
        Dispositivo 1
        <div class="switches">
            <button class="btn btn-success botaoSwitch" type="button" onclick="switchPressionado(1, 'ON')">ON</button>
            <button class="btn btn-danger botaoSwitch" type="button" onclick="switchPressionado(1, 'OFF')">OFF</button>
        </div>
    </a>
`

document.getElementById('integracaoSwitches').innerHTML = switches; //Implementa o bloco HTML dos switches dentro do controle
