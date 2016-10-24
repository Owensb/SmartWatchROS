
window.onload = function () {
    // TODO:: Do your initialization job

	
	
    // add eventListener for tizenhwkey. Closes/goes back to app screen when you swipe down
    document.addEventListener('tizenhwkey', function(e) {
        if(e.keyName == "back")
            tizen.application.getCurrentApplication().exit();
    });

   
  
    deviceOrientation(); //starts data collection
  connect_id(); //connects to server
    
    
};
