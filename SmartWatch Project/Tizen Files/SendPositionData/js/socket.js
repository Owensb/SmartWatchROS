

//prerequisists

//Initialize function

var websocket;
var output;



output = document.getElementById("output");
	function writeToScreen(message) {
		var pre = document.createElement("p");
		pre.style.wordWrap = "break-word";
		pre.innerHTML = message;
		output.appendChild(pre);
}


		
function onMessage(evt) {
	console.log(evt.data);
	writeToScreen('<span style="color: blue;">RESPONSE: ' + evt.data+'</span>');
}

function onClose(evt) {
	writeToScreen("DISCONNECTED");
}

function onError(evt) {
	writeToScreen('<span style="color: red;">ERROR:</span> ' + evt.data);
}

function connect_id(){

 if ("WebSocket" in window)//test for browser support
	{
		websocket = new WebSocket('ws://192.168.1.138:8001');
		
		websocket.onopen = function(evt) { //connecting to server
			alert("connected");
			writeToScreen("Connected");
		};
	
		websocket.onerror = function(evt) { //error in connection
			alert("error in connection");
			onError(evt)
		};
	
		websocket.onclose = function(evt) { //closing connection
			alert("closed");
			onClose(evt)
		};
	
		alert("browser supports websocket");

	}
	else
	{
		// The browser doesn't support WebSocket
		alert("WebSocket NOT supported by your Browser!");
	} 
}



window.setInterval(function(){
	
//function send_id(){
	var msg=document.getElementById('text_field');
		console.log(msg.value);
		console.log(websocket.readyState);
	var message=msg.value;
	
	//	console.log(message);
	if(websocket.readyState == 1)
	{
		websocket.send(message);
		//writeToScreen("SENT: " + message);
		//alert("message",message );
		websocket.onmessage = function(evt) { //receiving message from server
		onMessage(evt)
	};
	}



	else
		console.log("no connection");
}, 5); // frequency in milliseconds (thousandths of a second) 1 millisecond = 1 khz


function disconnect_id(){
	if(websocket.readyState == 1){
		websocket.close();
	}
	else
		alert("not connected yet");
	}