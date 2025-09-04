# Gravity Gun


---

## 🔧 Hardware Setup

- **Arduino UNO / Nano (or compatible)**
- **Momentary buttons**:
  - Left Button → `D2`
  - Right Button → `D3`
- **LEDs**:
  - Blue LED → `D5` (blinks 5 times at startup)  
  - Group 1 LEDs → `D4`, `D6`, `D7` (round-robin blinking)  
  - Group 2 LED → `D9` (PWM fading effect)
- **Sound Module**: JQ6500 MP3 Player
  - TX → `D10`
  - RX → `D11`

⚠️ **Note**: It’s highly recommended to use resistors (~220Ω) with LEDs to protect both the Arduino and the LEDs.

---

## 🎵 Behavior

- **Startup**:
  - Blue LED on pin `D5` blinks **5 times**.

- **Left Button (D2)**:
  - Plays **Sound 1** (track 1 on JQ6500).  
  - Group1 LEDs (`D4`, `D6`, `D7`) blink in a **round pattern**.

- **Right Button (D3)**:
  - Plays **Sound 2** (track 2 on JQ6500).  
  - Group2 LED (`D9`) fades brightness **up and down continuously**.

---

## 📂 File Overview

- `arduino_led_sound.ino` → Main Arduino sketch  
- `README.md` → Documentation  

---

## ▶️ How to Use

1. Connect the circuit according to the pin mapping above.  
2. Copy your audio files to the JQ6500 module:  
   - Track 1 → `001.mp3`  
   - Track 2 → `002.mp3`  
3. Upload the sketch to your Arduino board.  
4. Press **Left button** for Sound1 + Group1 LEDs, **Right button** for Sound2 + PWM LED.  

---

## 🛠️ Future Improvements

- Add debounce to button inputs.  
- Enable **loop playback** automatically for each track.  
- Support more LED patterns or sound tracks.  

---

## 📸 Demo

*(Add GIFs or photos of your hardware setup and LED effects here)*

---

## 📜 License

MIT License © 2025 Maksym Tsybulskyi
