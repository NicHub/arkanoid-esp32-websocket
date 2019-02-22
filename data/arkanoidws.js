"use strict";

var connection;
openWebSocket();

function openWebSocket() {
  try {
    var ip = location.hostname;
    connection = new WebSocket( 'ws://' + ip + '/ws', [ 'arduino' ] );
  } catch( exception ) {
    console.error( exception );
  }
}

setInterval( getConnectionState, 1000 );
function getConnectionState() {
  var state = connection.readyState;
  if( state === 1 ) // OPEN
    return;
  else if( state === 0 ) // CONNECTING
    console.log( "# LA CONNEXION EST EN COURS D’OUVERTURE" );
  else if( state === 2 ) // CLOSING
    console.log( "# LA CONNEXION EST EN COURS DE FERMETURE" );
  else if( state === 3 ) // CLOSED
    console.log( "# LA CONNEXION EST FERMÉE" );
  else
    console.log( "# LA CONNEXION EST DANS UN ÉTAT INCONNU" );
}

connection.onopen = function() {
  console.log( 'Connexion établie' );
  connection.send( 'PAGE WEB - Connexion etablie : ' + new Date() );
};

connection.onerror = function( error ) {
  console.log( 'Erreur WebSocket ', error );
};

connection.onclose = function( error ) {
  console.log( 'Fermeture WebSocket ', error );
};

connection.onmessage = function( e ) {
  console.log( 'COUCOU L’ESP8266 dit : ', e.data );
  console.log( 'length : ', e.data.length );
  var ESP8266rep = JSON.parse( e.data );

  for( var elem in ESP8266rep ) {
    console.log( 'elem = ' + elem  );
         if( elem === 'cpt'      ) receivedCPT( ESP8266rep );
  }
};

function receivedCPT( ESP8266rep ) {
  // let ev = {clientX: ESP8266rep.cpt.cpt1 };
  let ev = {clientX: ESP8266rep.cpt.cpt1 * 2 };
  player.extDispatch(ev);
}

