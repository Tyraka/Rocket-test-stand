# Rocket test stand

## About
This is a project of rocket test stand to measure the trust and temperature of the engine and to save the data on SD-card.

## Engine thrust
We mesure thrust using load-cell. To amplify analog sygnal from load-cell we use amplifer - HX711

### Amplifer - HX711

#### Amplifer schema
This is a schema for all the wireing with arduino
![alt text](https://github.com/Tyraka/Rocket-test-stand/blob/master/Engine%20thrust/amplifier_schema.png "Logo Title Text 1")

#### HX711 library
You can download the necessary library here:
[download](https://halckemy.s3.amazonaws.com/uploads/attachments/392655/HX711-master.zip)

#### Arduino code
All the code necessary for measuring the force:
- calibration:
[the code is here](https://github.com/Tyraka/Rocket-test-stand/blob/master/Engine%20thrust/calibration.ino)
- measurment:
[the code is here](https://github.com/Tyraka/Rocket-test-stand/blob/master/Engine%20thrust/measurement.ino)

#### Datasheet
[link](https://circuits4you.com/wp-content/uploads/2016/11/hx711_datasheet_english.pdf)

### Load cell

#### Load cell wireing
| HX711 | Load cell |
|-------|----------:|
| E+    | white     |
| E-    | red       |
| S+    | black     |
| S-    | green     |

#### Basic load resistance checks
| Resistance check | Typical 350 Ω |
|------------------|--------------:|
| Ex+ to Ex-       | ~410Ω         |
| S+ to S-         | 350Ω          |
| Ex+ to S+        | ~315Ω         |
| Ex+ to S-        | ~315Ω         |
| Ex- to S+        | ~280Ω         |
| Ex- to S-        | ~280Ω         |

## Engine temperature
We measure temperature of the combustion chember and nozzle using termocapules. They use voltage diffrences to determine the temperature.

### Chip - MAX 6675

#### Specifications
|                        |                    |
|------------------------|-------------------:|
| Suply Voltage          | 3.3 to 5 VDC       |
| Operating Current      | ~50mA              |
| Measurement Range      | 0 - 1024^∘C        |
| Measurement Resolution | +/- 0.25^∘C        |
| Output                 | Uses SPI interface |
| Required sensor        | K Thermocouple     |

#### Thermocouples schema
This is the schema for all the wireing with arduino
![alt text]()

#### Pinns functions:
- **SO:** Serial output, arduino reads output from this
- **CS:** Chip select. Setting low, selects the Module and tells it to supply an output that is synchronize with a clock
- **VCC:** power suply(5V)
- **GND:** ground
- **-(minus):** K Thermocouple minus input
- **+(plus):** K Thermocouple plus input

#### MAX6675 library
You can download the necessary library here
[download](https://github.com/adafruit/MAX6675-library)

#### Arduino code
Basic code for reading temperature
[the necessary code is here](https://github.com/Tyraka/Rocket-test-stand/blob/master/Engine%20temperature/thermocouples_schema.png)

#### Datasheet
[link](http://henrysbench.capnfatz.com/wp-content/uploads/2015/05/MAX6675-Datasheet.pdf)
dfsdfdsf
