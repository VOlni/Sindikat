# Sindikat
Here is all the code we prepared for the TADHack 2023

## CUP (Flight Management Center)
### *digitalocean/*  
*CUP* is hosted on the DigitalOcean host, that was created for free. Nothing interesting, just terraform script to run the Debian host.  
### *frontend/*  
We used *nginx* as a proxy server that will redirect requests to our UDP client.  
### *backend/*  
The most interesting part here.  
- *client/TadHack*  
There is a UDP client code written in Java. Script *client/run-all-the-things.sh* runs all the binaries for the demo purposes.  
- *client/udp-client*  
There is UDP socket prototype that has been started to be implemented but we didn't finish it because of the lack of time.  
- *dist/*  
This folder contains *drachtio* binary to run SIP service.  
- *factory01/*  
Contains self-made class factory that acts like a microservice to choose the processing method is needed at the moment.  


## Client side
*voice-test/*  
is a simple Python client that should send voice message to the backend.
We were restricted to use any devices except laptops, so the client wasn't developed well, there is just proof that the program can send a voice message from the web interface (Google API was defined as ad-hoc).  
*Stacuity*.  
Endpoint was created and connection was set up.