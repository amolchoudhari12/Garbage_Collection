# Garbage Collection Demo (C++/CLI)

This project demonstrates the working of the **.NET Garbage Collector (GC)** using **C++/CLI**.  
It was created as a personal learning project to explore how memory is managed automatically in the .NET runtime and to understand object lifetimes, weak references, and the Dispose pattern.

---

## 🧠 Overview

The program walks through key concepts of the .NET GC:
- **Memory Allocation & Collection:** Creates large numbers of objects and measures memory usage before and after garbage collection.  
- **Generations:** Shows how the GC promotes surviving objects through **Gen 0**, **Gen 1**, and **Gen 2**.  
- **Weak References:** Demonstrates how objects referenced weakly can be reclaimed.  
- **Finalize & Dispose:** Illustrates the proper cleanup of managed and unmanaged resources.


## 🎯 Learning Goals

- Understand **how .NET reclaims memory** automatically.  
- Learn about **object generations** and collection efficiency.  
- Explore **weak references** and when to use them.  
- Practice **Dispose/Finalize** patterns for resource cleanup.  

---

## 👨‍💻 Author

Developed by **Amol**  
A practical experiment to understand **Garbage Collection** and **memory management** in .NET.
