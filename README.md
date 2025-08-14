# 5207Comp — Angry Birds-Style Game

## Overview
This project is an Angry Birds–inspired 2D physics game built in C++ with SFML. Players use a slingshot to launch a sequence of birds at towers made of bricks and pigs. The aim is to knock down all pigs using limited birds.

The game demonstrates the use of **abstract data types**, **queues**, **doubly linked lists**, and a **Bounding Volume Hierarchy (BVH)** for collision detection.

---

## Features
- **Slingshot mechanics** — Click and drag to set angle and power; release to launch.
- **Queue-based bird management** — Birds are loaded into the slingshot in FIFO order.
- **Doubly linked list tower structure** — Efficient addition/removal of bricks and pigs.
- **Bounding Volume Hierarchy** — Optimised collision checks for smoother gameplay.
- **Scoring system** — Different scores for hitting bricks vs pigs.
- **Victory/Game Over conditions** — Win by destroying all pigs; lose when out of birds.
- **Basic sound effects** — Launch, idle, and collision sounds.
- **Smooth performance** — Designed for at least 30 FPS.

---

## Requirements
- Windows 10/11
- Visual Studio 2022 (with Desktop Development with C++)
- SFML 2.5+ installed and linked

---

## Getting Started

### Clone the Repository
```powershell
git clone https://github.com/ewanhmack/5207Comp.git
cd 5207Comp
```

### Open and Build
1. Open the `.sln` file in Visual Studio 2022.
2. Set the startup project to the main game project.
3. Select **Debug** or **Release** build configuration.
4. Build the solution (`Ctrl+Shift+B`).
5. Run (`F5` or `Ctrl+F5`).

---

## Controls
- **Mouse click + drag** — Aim slingshot and set power.
- **Mouse release** — Launch bird.

---

## Folder Structure
```
Assets/              # Textures, sprites, and sounds
src/                 # Game source code
include/             # Header files
```

---

## How It Works
- **Bird Queue** — Birds are enqueued at level start, dequeued when launched.
- **Tower List** — Bricks and pigs stored in a doubly linked list for fast removal.
- **BVH Collision** — Bricks and pigs grouped in bounding boxes to reduce collision checks.
- **Game Loop** — Handles events, updates game state, and renders each frame.

---
