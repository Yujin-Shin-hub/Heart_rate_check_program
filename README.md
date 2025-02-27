![image](https://github.com/user-attachments/assets/fa9847e0-2ee8-424b-8255-514cbb71ea0a)
![image](https://github.com/user-attachments/assets/a78f378e-2a57-46a3-9deb-0263ebaa5296)
![image](https://github.com/user-attachments/assets/97987976-c492-4b3a-a87e-01c0d77178cd)
![image](https://github.com/user-attachments/assets/dd2ce169-337e-4155-9b02-910824de7990)
![image](https://github.com/user-attachments/assets/7d3d4177-8a87-4410-bbf1-b99a279100ba)


# Button Input and Heart Rate Measurement System

## Overview

This project implements a system that detects button presses, stabilizes the input signal, and measures heart rate based on the number of button presses within **10 seconds**. The results are displayed in four categories: **Perfect, Normal, Below Average, and Bad**.

---

## 1. Button Input Stabilization

- The switch was initially unstable, causing **irregular** intervals between **0 and 1** outputs.  
- Even though the switch was connected according to the circuit diagram, it did not work correctly.  
- To fix this, the **digital pin and ground pin connections** were swapped, which resulted in a **more stable signal**.  
- Additionally, setting a **100ms delay** helped maintain a **consistent signal interval**.

---

## 2. Pull-up Resistor and Signal Behavior

- When the **switch is open**, the pull-up resistor is connected, and current flows into the **input pin instead of GND**, resulting in a **HIGH (1)** signal.  
- When the **switch is closed**, **Vcc and GND are directly connected**, and all current flows to GND because it is the lowest potential point, resulting in a **LOW (0)** signal.

---

## 3. Heart Rate Measurement Logic

- The system **counts button presses** for **10 seconds** and categorizes the heart rate as follows:  
  - **8 or more presses** → **Perfect**  
  - **Between 5 and 7 presses** → **Normal**  
  - **Between 2 and 4 presses** → **Below Average**  
  - **Less than 2 presses** → **Bad**  
- The result is displayed on the screen.

---

## 4. Button Press Detection Method

- The system counts a press **only when the button is released**, ensuring that only valid presses are measured.  
- Two variables, `new_button` and `old_button`, are used:  
  1. The **new digital input signal** is stored in `new_button`.  
  2. The **previous signal** is stored in `old_button`.  
  3. If `new_button` and `old_button` are different, a button press is recorded.  
  4. After each check, `old_button` is updated with the value of `new_button`.  

This method ensures that **multiple counts are not registered** from a single press, preventing errors in heart rate measurement.
