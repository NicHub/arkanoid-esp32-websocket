"use strict";

var connection;
openWebSocket();

function openWebSocket() {
    try {
        var ip = location.hostname;
        connection = new WebSocket("ws://" + ip + "/ws", ["arduino"]);
    } catch (exception) {
        console.error(exception);
    }
}

setInterval(getConnectionState, 1000);
function getConnectionState() {
    var state = connection.readyState;
    if (state === 1)
        // OPEN
        return;
    else if (state === 0)
        console.log("# CONNECTING");
    else if (state === 2)
        console.log("# CLOSING");
    else if (state === 3)
        console.log("# CLOSED");
    else
        console.log("# UNKNOWN STATE");
}

connection.onopen = function () {
    console.log("CONNECTED");
    connection.send("BROWSER CONNECTED : " + new Date());
};

connection.onerror = function (error) {
    console.log("WEBSOCKET ERROR ", error);
};

connection.onclose = function (error) {
    console.log("WEBSOCKET CLOSED ", error);
};

connection.onmessage = function (e) {
    console.log("RECEIVED FROM ESP : ", e.data);
    console.log("length : ", e.data.length);
    var ESPrep = JSON.parse(e.data);

    for (var elem in ESPrep) {
        console.log("elem = " + elem);
        if (elem === "cpt") receivedCPT(ESPrep);
    }
};

function receivedCPT(ESPrep) {
    let ev = { clientX: ESPrep.cpt.cpt1 * 2 };
    player.extDispatch(ev);
}
