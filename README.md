# Survive It

A 2D multiplayer battle royale game inspired by Surviv.io. Drop into a map with up to 50 players, loot weapons and supplies, and fight to be the last one standing.

## Gameplay

- Up to **50 players** per session
- Spawn on a large 2D top-down map
- **Loot** weapons, healing items and supplies scattered across the map
- The **zone** shrinks over time — stay inside or take damage
- Eliminate other players and survive to reach **Top 1**

## Tech Stack

| Component | Technology |
|-----------|------------|
| Language  | C++17      |
| Graphics  | SFML 3     |
| Networking | Boost.Asio (latest via vcpkg) |
| Protocol  | UDP        |
| Build     | vcpkg      |

## Architecture

```
client/
├── scenes/         — ConnectingScene, MenuScene, GameScene
├── network/        — NetworkManager (UDP, async via Boost.Asio)
├── fonts/          — Font assets
├── Game.h/cpp      — Main game loop, scene management
├── FSM.h/cpp       — Finite state machine (Connecting → Menu → InGame)
└── main.cpp
```

## Getting Started

### Prerequisites

- [vcpkg](https://github.com/microsoft/vcpkg)
- Visual Studio 2022 or newer
- C++17 compiler

### Install dependencies

```bash
vcpkg install sfml
vcpkg install boost-asio
vcpkg integrate install
```

### Build

Open `client.sln` in Visual Studio and build the solution.

### Run

Make sure the server is running, then launch `client.exe`.

## Controls

| Key | Action |
|-----|--------|
| W A S D | Move |
| Mouse | Aim |
| Left Click | Shoot |

## Server

The server is a separate project. See the server repository for setup instructions.
