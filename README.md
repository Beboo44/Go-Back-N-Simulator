# Go-Back-N ARQ Protocol Simulator

A C++ simulation of the **Go-Back-N (GBN) Automatic Repeat reQuest** protocol used in reliable data transmission.  
This project demonstrates how frames are sent, acknowledged, lost, or retransmitted using a sliding-window mechanism.

---

## 📌 Features

- Full implementation of **Go-Back-N ARQ**
- User-defined:
  - Window size
  - Number of frames
- Simulates:
  - Frame sending
  - ACK / NAK
  - Frame loss
  - Sequence number corruption (20% probability)
- Displays detailed sender/receiver logs
- Random packet generation (lowercase a–z)
- Sliding window with modulo arithmetic

---

## 🧠 How the Protocol Works

### Sender
- Sends frames up to the window limit.
- Waits for ACKs.
- If one frame fails, **all frames from that point are resent**.

### Receiver
- Accepts only the frame with the correct expected sequence number.
- Sends:
  - ACK if correct
  - NAK if wrong or out-of-order

### Error Simulation

A 20% chance of sequence number corruption:

```cpp
if((rand()%100)<20){
    return rand()%MAX_SEQ;
}

🔧_compilation_and_execution:
  compile: "g++ -std=c++17 -O2 -o gbn main.cpp"
  run: "./gbn"
  example_input:
    - "Please, Enter the window size --> 4"
    - "Please, Enter number of data frames --> 10"
  example_output: |
    Sending Window:
    ===========================================
    Sender   : Frame 0 is sent  Data_Sent: qwerty...
    Sender   : Frame 1 is sent  Data_Sent: kjhgfd...
    Sender   : Frame 2 is sent  Data_Sent: asdfgh...
    !!!!! error has happened !!!!
    Receiver: Frame 2 is lost. Send it again
    ===========================================

📁_project_structure:
  - file: "main.cpp"
    description: "Go-Back-N implementation"
  - file: "README.md"
    description: "Documentation"

🧩_concepts_covered:
  - "Sliding Window Protocols"
  - "Reliable Data Transfer"
  - "Sequence Number Wrapping (modulo arithmetic)"
  - "ACK/NAK handling"
  - "Sender/Receiver synchronization"
  - "Error simulation"

🚀_future_improvements:
  - "Selective Repeat ARQ version"
  - "Timer + timeout support"
  - "GUI visualization"
  - "Bit-level error simulation"
  - "File logging"
