# 🐧 C++ Embedded Linux System Monitor

A high-performance, lightweight system monitoring tool built to explore the depths of the Linux Kernel and the foundations of Embedded Systems Engineering.

## 🎯 The Mission
The goal of this project isn't just to display numbers on a screen—it's to master the **Host-Target workflow** essential in Embedded Linux development. By shunning high-level libraries and "copy-paste" logic, I am learning how software truly communicates with hardware through the Linux Kernel.

### 🏗️ Why this Stack?
* **WSL2 (Windows Subsystem for Linux):** Chosen to simulate a cross-platform development environment. It provides a real Linux kernel while maintaining the productivity of a Windows host.
* **VS Code:** Leveraged as the "Command Center," using remote extensions to bridge the gap between Windows and the Linux environment—mimicking how engineers develop for ARM-based boards.
* **C++ & /proc:** Utilizing C++ for its memory efficiency and speed, targeting the `/proc` virtual filesystem to understand how the kernel exposes live system data as text files.
---

## ⚙️ Architecture

The project follows a modular **Object-Oriented** design with separated concerns, 
making the codebase portable and scalable — ready to be extended or ported to an 
ARM-based embedded target.

| Class | Responsibility | Data Source |
|---|---|---|
| `Processor` | Real-time CPU utilization via delta algorithm | `/proc/stat` |
| `Memory` | RAM and Swap usage with unit scaling | `/proc/meminfo` |
| `SysUptime` | Human-readable uptime clock | `/proc/uptime` |
| `GenInfo` | Hostname and Kernel version extraction | `/proc/sys/kernel/` |
| `SystemManager` | Coordinator — owns all modules, drives refresh loop | — |

### The CPU Delta Algorithm
The Linux Kernel does not provide a CPU percentage directly. It exposes cumulative 
**Jiffies** (ticks) since boot. To calculate real-time usage:

1. Take snapshot of `/proc/stat` → record active and total ticks
2. Wait exactly 1 second
3. Take second snapshot
4. Apply delta formula:

```
CPU Usage % = (ΔActive Ticks / ΔTotal Ticks) × 100
```

This ensures the monitor shows **current load**, not a lifetime average.

### Memory Scaling
The kernel reports all memory values in Kilobytes. The `Memory` class implements a 
conversion pipeline (`KB → MB → GB`) using `long long` integers to prevent overflow 
on high-RAM systems. Guard clauses handle the divide-by-zero edge case when Swap is 
disabled.

---

## ✨ Current Capabilities

- **Real-Time CPU Usage** — per-core utilization via snapshot-delta algorithm
- **Memory & Swap Monitoring** — used/total with GB scaling
- **System Uptime** — precision clock in `Days:Hours:Minutes:Seconds`
- **Load Average** — 1m, 5m, 15m system load from `/proc/loadavg`
- **Kernel & Hostname** — live identity via `/proc/sys/kernel/`
- **Non-Flickering Dashboard** — ANSI escape codes for stable terminal UI

---

## 🏗️ Project Structure

```
sysMonitor/
├── include/          # Class declarations (.hpp)
│   ├── Processor.hpp
│   ├── Memory.hpp
│   ├── SysUptime.hpp
│   ├── GenInfo.hpp
│   └── SystemManager.hpp
├── src/              # Class definitions (.cpp)
│   ├── Processor.cpp
│   ├── Memory.cpp
│   ├── SysUptime.cpp
│   ├── GenInfo.cpp
│   ├── SystemManager.cpp
│   └── main.cpp
├── build/            # Compiler output (gitignored)
├── Makefile
├── CMakeLists.txt
└── README.md
```

**Why separate `include/` and `src/`?**  
Headers (`.hpp`) are declarations — they tell the compiler *what* exists. Source 
files (`.cpp`) are definitions — they contain *how* it works. This separation enables 
incremental compilation: changing one module only recompiles that module, not the 
entire project. It also makes the codebase portable and mirrors industry-standard 
embedded project structures.

---

## 🏗️ Build Automation & Scaling

### Prerequisites
- GCC with C++17 support (`g++ --version`)
- Make or CMake
- Linux environment (Native, WSL2, or VM)


To mirror professional embedded workflows, I have implemented two layers of build automation:

### 1. GNU Make
Used for local, fast builds. The `Makefile` manages dependencies and ensures that only modified files are recompiled, saving time during the rapid development cycle.

### 2. CMake (Cross-Platform Meta-Build)
Since the goal is **Embedded Linux**, CMake is used to make the project platform-agnostic. 
* **Abstraction:** It generates the necessary build files (Makefiles or Ninja) based on the environment.
* **Future-Proofing:** This allows for easy **Cross-Compilation**, enabling the code to be built on a Windows/WSL2 host and deployed to an ARM-based embedded target.

### 🚦 How to Build
### Using Make
```bash
git clone https://github.com/Yogita07-L/sysMonitor.git
cd sysMonitor
make
./monitor
```

### Using CMake
```bash
mkdir build && cd build
cmake ..
make
./monitor
```

---

## 🔧 Development Environment

| Tool | Role |
|---|---|
| WSL2 (Ubuntu) | Linux kernel access on Windows host |
| VS Code + Remote Extension | Cross-environment development, mirrors ARM host-target workflow |
| GNU Make | Fast local builds with dependency tracking |
| CMake | Platform-agnostic meta-build for cross-compilation readiness |
| C++17 | `std::filesystem`, modern STL, performance |

---

## 📚 Key Technical Concepts Demonstrated

- **VFS Parsing** — direct `/proc` filesystem interaction without system call wrappers
- **Delta Algorithm** — snapshot-based real-time metric calculation
- **OOP Encapsulation** — kernel-reading logic isolated from display logic; portable by design
- **Error Resilience** — guards for missing PIDs, disabled Swap, and divide-by-zero
- **Incremental Compilation** — modular structure minimizes rebuild time
- **Cross-Platform Build** — CMake enables future ARM cross-compilation

---

## 🗺️ Roadmap

- [ ] Per-process CPU and memory tracking via `/proc/[PID]/stat`
- [ ] SocketCAN integration for embedded network monitoring
- [ ] Cross-compilation support for ARM targets (Raspberry Pi / STM32MP1)
- [ ] Unit tests with Google Test

---