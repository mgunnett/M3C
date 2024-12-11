# M3C
By PW & MG

In order for the lighting system to function, two programs are needed for both the indoor and outdoor system. Below is a list of 
the Pins and their corresponding sensor. 

## Pin Modes

### Indoor System
#### Digital
11- Red RGB

10- Green RGB

9- Blue RGB

7- IR Reciever

4- PIR Reciever (motion)

2- Button

### Outdoor System
#### Digital
13- LED Power

8- PIR Reciever (motion)

4- IR Reciever

2- Light Sensor Digital

#### Analog
A0- Light Sensor Analog

## Remote Codes
| Button |  Code |
| :------: |  :-----: |
| 0 |  22 |
| 1 |  12 |
| 2 |  24 |
| 3 |  9 |
| 4 |  8 |
| 5 | 28 |
| 6 |  90 |
| 7 |  66 |
| 8 |  82 |
| 9 |  74 |

## Important Information

- Our particular Arduino remote communicates using the NEC protocol. It can also detect signals from other remotes.
- The remote operates using multiple presets coded into buttons 0-9
- The outdoor and indoor system will be ran from two different Arduinos
  

