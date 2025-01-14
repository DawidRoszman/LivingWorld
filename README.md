# Organism Simulation

This project is a simulation that models the behavior and lifecycle of organisms using advanced object-oriented programming techniques. The system was designed to follow SOLID principles and provides a clean, extensible structure for further enhancements. Below is an overview of the implemented features:

## Features
1. Organism History Tracking
Each Organism maintains a history of its ancestors, represented as a list containing the birth and death turns of its predecessors.
The implementation includes constructors (including copy constructors) and destructors to ensure proper object management.
Mechanisms for updating ancestor history are integrated, allowing dynamic changes during simulation.
Assignment operators were implemented with care to avoid resource leaks or unintended side effects.
2. Enhanced Class Design
The class hierarchy was refined with an appropriate inheritance model to reflect real-world organism relationships.
Polymorphic methods were implemented across relevant classes, enabling dynamic behavior for different organism types.
3. Abstract Base Classes
The Organism, Animal, and Plant classes were refactored into abstract base classes.
These classes define common interfaces and cannot be instantiated directly.
Concrete subclasses implement the required methods, ensuring a clear separation between abstraction and implementation.
4. Improved Serialization
The naive serialization mechanism was redesigned to align with SOLID principles.
Serialization and deserialization responsibilities are now handled individually by each object, promoting modularity and encapsulation.
The updated mechanism was tested thoroughly to ensure reliability and correctness.
