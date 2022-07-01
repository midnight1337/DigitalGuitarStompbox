# Digital guitar stompbox based on Atmega328P (Arduino)

This is my project made for graduating University of Science and Technology in 31-01-2022. The idea behind the project, was that I started being very curious how analog guitar stompboxes are made, I was reading a lot and I was so amazed how we can change audio signal by electronic components. Due to that my studies were focused on low level programming and processors architecture, I wanted to build my very first, fully digital guitar pedal.


![Final stompbox](/Pictures/Enclosure_top.jpeg)

## Schematic and how does it work.
The heart of the circuit is Atmega328P, I've considered choosing STM32, but I felt more confident with arduino, as I was playing with this a lot.

Basically the circuit works almost exactly like any basic analog stompbox, the difference is that signal is mostly modified by a processor, not by op-amps, transistors or diodes.

There is Input stage which purpose is to filter out signal and boost it to desired level, but not higher than 5V, because it's supply voltage value of microcontroller so more volts would possibly damage it.

Atmega is programmed to take sample of our filtered signal, represented by voltage level, then process it by our program, and finally outputs it by setting logic states on register, which are related to processed sample. ADC sampling rate was set to approx 38.5KHz, I was able to get that value by changing some ADC register bits and prescaler.

Output stage is created with 10bit R2R ladder, which is able to represent voltage as binary values on our register. Last step is to filter out signal nad proceed it to amplifier.

![Schematic](/Schematic/Schematic.png)


## Some photos and other stuff.

First working prototype on a bredboard

![prototype](/Pictures/Prototype.JPG)


All components assembled on PCB

![PCB](/Pictures/Pcb_assembly.jpeg)


Top and side of enclosure

![Top](/Pictures/Enclosure_top.jpeg)

![Side](/Pictures/Enclosure_side.jpeg)


## Testing effects on osciloscope

For testing purpose I used sine generator and Hameg HM408 osciloscope. I've connected first probe of osciloscope to the input of atmega328 (right after gain section and before ADC of microcontroller). Second probe was connected directly to the output of the stompbox. Upper signal on osciloscope screen is reference input view (clean amplified sine), lower signal on osciloscope screen is output view (signal after being processed). Frequency of generated sine wave was 440Hz, Amplitude was set to 300-400mV peak to peak. As you can see, upper signal of the osciloscope is measured at 4V because potentiometer at gain section was set to amplify signal about 10 times. There are two pictures for every effect, first one shows how processed signal looks like, second one shows measured time of processing one sample (right top corner)


### Clean effect

Just to remind you, the stompbox is fully digital so there is no true bypass for clean signal, it is taken by microcontroller and then just put at the output.

![Side](/Pictures/Clean.JPG)

![Side](/Pictures/Clean_sample.JPG)


### Fuzz effect

![Side](/Pictures/Fuzz.JPG)

![Side](/Pictures/Fuzz_sample.JPG)


### Distortion effect

![Side](/Pictures/Distortion.JPG)

![Side](/Pictures/Distortion_sample.JPG)


### Octave effect

![Side](/Pictures/Octave.JPG)

![Side](/Pictures/Octave_sample.JPG)


## Summary

I have to admit, that it was pretty interesting but hard project. It took me a lot of time to figure out how all of this stuff works, despite this at the end I'm very happy and proud of myself because I've managed to get it work for real.
