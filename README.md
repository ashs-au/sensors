# sensors

Sketches to drive Etherten Arduino clones used as part of the mapping for a performance project where capturing the performer's movement and their interaction with props was captured using sensors and communicated to a server process (over a closed ethernet LAN) that assembled pre-written text fragments into a fiction narrative by reacting to parameters: heat, cold, light, dark, silence, noise - and the presence of the performer in defined regions of the stage space (using proximity detectors). 

'proximity.ino' monitors and reports light, sound and motion in front of a single IR detector.
'temp.no' monitors and reports from 2 temperature probes. In the show, one monitored the melting of a bucket of ice and the other, the cooling of a mug of tea.

Notes/critique
* neither sketch involves any osrt of control about the frequency of message of any sort of saved state in the sensor box itself (which might reduce the quantity of messaging) - beyond the typical Arduino delay() function. 
* there's no attempt to aggregate messages to report sensor states aggregated into a compound OSC message, which would also mean less packets flying.

[This is what the final devices looked like](https://github.com/ashs-au/sensors/wiki)

More details about the project: http://squidsilo.net/rima/
