// FILE: washing.cxx
// CLASSES implemented: bool_source, averager, washer
//
// INVARIANT for the bool_source ADT:
//   1. The member variable probability is the appoximate probability that
//      query( ) returns true.
//
// INVARIANT for the averager ADT:
//   1. The member variable count indicates how many numbers the averager has
//      been given.
//   2. The member variable sum is the sum of all the numbers that the
//      averager has been given.
//
// INVARIANT for the washer class:
//   1. The member variable seconds_for_wash is the number of seconds required
//      for one wash.
//   2. The member varible wash_time_left is 0 if the washer is not busy;
//      otherwise it is the number of seconds until the washer is free.

#include <cassert>    // Provides assert
#include <cstdlib>    // Provides rand, RAND_MAX, size_t
#include "washing.h"  // Provides bool_source, averager, washer definitions
using namespace std;

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

    carwash::carwash(unsigned int s)
    {
        seconds_for_wash = s;
        wash_time_left = 0;
    }


    void carwash::one_second( )
    {
        if (is_busy( ))
            --wash_time_left;
    }


    void carwash::start_washing( )
    // Library facilities used: cassert
    {
        assert(!is_busy( ));
        wash_time_left = seconds_for_wash;
    }
