# Two-Wheeled Self-Balancing Robot
Clone the whole project included:

* Shematic and PCB design using Altium
* Frame designed with Solidworks and corel file for cutitng mica
* Source code for STM32F103C8T6 (BluePill board)
* Computer software for remote control

```
git clone --recursive https://github.com/tuanngo0898/2WheelsRobot.git 
```

# Mavlink protocol
## Prerequisite 
```
    pip install future
```
## Gencode
Mavlink messages are defined in Software/mavlink/protocol.xml To generate C code for communication:

* Go to Software/mavlink/mavlink.
* Open cmd in this folder and run mavgenerate.py
```
    python mavgenerate.py
```
Out 1: Firmware\BlancingRobot\Src\UserCode\Com\Mav
