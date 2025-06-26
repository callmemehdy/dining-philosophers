# 🧠 Philosophers

A classic **multithreading synchronization problem** recreated in C as part of the [42/1337 curriculum](https://1337.ma). The "Dining Philosophers" problem challenges you to handle concurrency, mutexes, and timing issues — ensuring no philosopher dies, no deadlocks occur, and everyone eats in peace 🧘‍♂️🍝.

---

## 📦 Project Overview

The goal is to simulate a group of philosophers who alternately think, eat, and sleep. Each philosopher needs two forks (mutexes) to eat, and forks are shared with their neighbors — which leads to concurrency issues that must be resolved using threads and synchronization primitives.

---

## ⚙️ Requirements

- 🧠 C language (C99 or later)
- 🧵 `pthread` library
- 🐧 Linux/macOS environment
- ✅ `make`

---

## 🚀 Getting Started

### 1. Clone the repository:

```bash
git clone https://github.com/callmemehdy/dining-philosophers.git
cd dining-philosophers
```

### 2 testing

```bash
./philo [philo number] [time to die] [time to eat] [time to sleep] [optional: meals number]
```

### - Example:
```bash
./philo 5 800 200 200 10
```
