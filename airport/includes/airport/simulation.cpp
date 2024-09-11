#include "simulation.h"

bool_probability::bool_probability(double p)
// Library facilities used: cassert
{
    assert(p >= 0);
    assert(p <= 1);
    probability = p;
}

bool bool_probability::query( ) const
// Library facilities used: cstdlib
{
    return (rand( ) < probability * RAND_MAX);
}

averager::averager( )
{
    count = 0;
    sum = 0;
}

void averager::next_number(double value)
{
    ++count;
    sum += value;
}

double averager::average( ) const
// Library facilities used: cassert
{
    assert(how_many_numbers( ) > 0);
    return sum/count;
}

AirportSimulation::AirportSimulation(unsigned int takeoff_time, double takeoff_probability,
                    unsigned int landing_time, double landing_probability,
                    unsigned int fuel_limit, unsigned int total_time)
        : takeoff_time(takeoff_time), takeoff_probability(takeoff_probability),
            landing_time(landing_time), landing_probability(landing_probability),
            fuel_limit(fuel_limit), total_time(total_time) {
    
}
AirportSimulation::~AirportSimulation(){
    // delete &takeoff_time;
    // delete &takeoff_probability;
    // delete &landing_time;
    // delete &landing_probability;
    // delete &fuel_limit;
    // delete &total_time;
}

void AirportSimulation::runSimulation(bool debug){
    unsigned int current_time = 0;
    unsigned int runway = 0;

    unsigned int crashed = 0;

    bool_probability takeoffProb(takeoff_probability);
    averager takeoffAvg;

    bool_probability landingProb(landing_probability);
    averager landingAvg;

    for (current_time = 1; current_time <= total_time; ++current_time){
        
        while(!landing_source.empty()){
            if(current_time - landing_source.front() > fuel_limit){
                crashed++;
                landing_source.pop();
            }else{
                break;
            }
        }
        if(landingProb.query()){
            landing_source.push(current_time);
        }

        if(takeoffProb.query()){
            takeoff_source.push(current_time);
        }

        if(runway == 0){
            if(!landing_source.empty()){
                landingAvg.next_number(current_time - landing_source.pop());
                runway = landing_time;
            }else if (!takeoff_source.empty()){
                takeoffAvg.next_number(current_time - takeoff_source.pop());
                runway = takeoff_time;
            }
        } else {
            --runway;
        }
    }

    cout << "============================================";
    cout << endl;
    
    cout << "time to take off      : " << takeoff_time;
    cout << endl;
    
    cout << "time to land:         : " << landing_time;
    cout << endl;
    
    cout << "probability of landing: " << landing_probability;
    cout << endl;

    cout << "probability of takeoff: " << takeoff_probability;
    cout << endl;

    cout << "fuel: time to crash   : " << fuel_limit;
    cout << endl;

    cout << "total simulation time : " << total_time;
    cout << "\n \n \n";

    cout << ". . . . . . . . . . . . . . . . . . . . . . . ";
    cout << endl;

    cout << landingAvg.how_many_numbers() << " landed";
    cout << endl;

    cout << takeoffAvg.how_many_numbers() << " took off";
    cout << endl;

    cout << crashed <<" planes crashed. ";
    cout << endl;

    cout << "Average waiting time to land: " << landingAvg.average();
    cout << endl;

    cout << "Average waiting time to take off: " << takeoffAvg.average();
    cout << endl;
}

void AirportSimulation::initialize(){

}
void AirportSimulation::processArrivals(bool_probability landingProb){

}
void AirportSimulation::processDepartures(){

}
void AirportSimulation::updateQueues(){

}
void AirportSimulation::printDebugInfo(){

}
void AirportSimulation::handleLanding(unsigned int current_time){

}
void AirportSimulation::handleTakeoff(unsigned int current_time){

}
void AirportSimulation::simulateOneSecond(unsigned int current_time){

}
void AirportSimulation::printSimulationResults(){

}
