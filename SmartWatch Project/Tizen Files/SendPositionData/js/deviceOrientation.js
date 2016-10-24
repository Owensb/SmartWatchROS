

function deviceOrientation(){
 window.addEventListener("deviceorientation", function(event) {
    
	// console.log(event.alpha, event.beta , event.gamma)  
	 
         // alpha is the compass direction the device is facing in degrees
         var alpha = event.alpha

         // beta is the front-to-back tilt in degrees, where front is positive
         var beta = event.beta;
	 
	 	// gamma is the left-to-right tilt in degrees, where right is positive (might not be right)
	 	 var gamma = event.gamma;

         // call our orientation event handler
//	 	 var current_dt = tizen.time.getCurrentDateTime();
//	 	 console.log("current date/time is " + current_dt.toLocaleString());
//	 	 
	 	 
         document.getElementById('textboxA').innerHTML= "Alpha:" + alpha;
         document.getElementById('textboxB').innerHTML= "Beta:" + beta;
         document.getElementById('textboxC').innerHTML= "Gamma:" + gamma;
         
         //Package Alpha/Beta/Gamma
         var message= JSON.stringify({
        		alpha: alpha , beta: beta, gamma: gamma
        		})
        console.log(message);
         document.getElementById('text_field').value= message;
      }, true);
 }
