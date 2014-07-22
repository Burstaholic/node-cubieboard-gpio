#Introduce

Use node.js to control gpio on cubieboard

#Install

	npm install node-cubieboard-gpio

#Usage
  // Require library
  var GPIO = require('node-cubieboard-gpio');

  // initialize the gpio pin
  var pin = GPIO.PD0;
  var status = 0;
  GPIO.init();

  // config the gpio pin -> either input or output
  GPIO.setcfg(pin, GPIO.OUT);

  // toggle a pin on and off
  var toggle = function(){
    if(status){
      GPIO.output(pin, GPIO.LOW);
      status = 0;
    } else {
      GPIO.output(pin, GPIO.HIGH);
      status = 1;
    }
  }

  setInterval(toggle, 1000);

#Methdods

  /**
    initializes a pin to be used as a gpio
    args: none
  **/
  GPIO.init()

  /**
    reads a pins input
    args: Pin - pin instance that will become the input
  **/
  GPIO.input()

  /**
    writes a pin output
    args: Pin - pin instance that will become the input
          State - pin state. Either GPIO.LOW or GPIO.HIGH
  **/
  GPIO.output()
  
  /**
  sets the configuration of the pin as an input or an output
  args: Pin - pin instance that will become the input
        Direction - direction of the pin. Either GPIO.OUT or GPIO.IN
  **/
  GPIO.setcfg()
  
  /**
  gets the configuration parameters of the pin
  args: none
  **/
  GPIO.getcfg()



