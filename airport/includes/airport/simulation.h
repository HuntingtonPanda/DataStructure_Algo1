#ifndef SIMULATION_H
#define SIMULATION_H

#include "../queue/MyQueue.h"
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>

using namespace std;

class bool_probability
{
public:
    // CONSTRUCTOR
    bool_probability(double p = 0.5);
    // CONSTANT function
    bool query( ) const;
private:
    double probability; // Probability of query( ) returning true
};

class averager
{
public:
    // CONSTRUCTOR
    averager( );
    // MODIFICATION function
    void next_number(double value);
    // CONSTANT functions
    std::size_t how_many_numbers( ) const { return count; }
    double average( ) const;
private:
    std::size_t count; // How many numbers have been given to the averager
    double sum;   // Sum of all the numbers given to the averager
};

class AirportSimulation {
public:
    AirportSimulation(unsigned int takeoff_time, double takeoff_probability,
                      unsigned int landing_time, double landing_probability,
                      unsigned int fuel_limit, unsigned int total_time);
    ~AirportSimulation();

    void runSimulation(bool debug = false);

private:
    unsigned int takeoff_time;
    double takeoff_probability;
    unsigned int landing_time;
    double landing_probability;
    unsigned int fuel_limit;
    unsigned int total_time;

    Queue<int> landing_source;
    Queue<int> takeoff_source;
    Queue<int> fuel_check;

    void initialize();
    void processArrivals(bool_probability landingProb);
    void processDepartures();
    void updateQueues();
    void printDebugInfo();
    void handleLanding(unsigned int current_time);
    void handleTakeoff(unsigned int current_time);
    void simulateOneSecond(unsigned int current_time);
    void printSimulationResults();
};

#endif /* SIMULATION_H */
