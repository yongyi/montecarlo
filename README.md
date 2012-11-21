<link href="http://kevinburke.bitbucket.org/markdowncss/markdown.css" rel="stylesheet"></link>
Monte-Carlo
===========

*need to debug*

A simple implementation of the Monte-Carlo simulation for pricing options.

*Contents:*

1.payoff: the interface and classes responsible for calculating the payoffs of 
          different kind of options.

2.statgatherer: statistics gatherer responsible for keeping track of the max, min, and mean
                of the numbers.

3.random: the interface for random number generators

4.randombsmoro: the random number generator that uses Beasley-Sringer-Moro inverse transform
                method to generate standard normal from uniforms in (0,1).

5.randomboxmuller: the random number generator that uses Magsarlia-Bray version of Box-Muller
                   method to generate standard normal from uniforms in (0,1).

6.randomacceptreject: the random number generator that uses Acceptance-Rejection method to
                       generate standard normals from uniforms in (0,1).

7.antithetic: the random number generator that takes an underlying generator (item 4, 5, or 6)
               and applies the antithetic variance reduction technique to generate standard
               normals.

8.wrapper: template wrapper to handle pointers and memory management.

9.monte-carlo: contains the functions to run Monte-Carlo simulation

:

*Timeline:*

Nov.10: Finished basic implementation of the option payoff and statistics gatherer class.

Nov.12: Added a template wrapper class to handle pointers.
        Finished basic implementation of random number generator class 
        Added a random number generator using linear congruential method.

Nov.14: Deleted randomlcg file. Moved the linear congruential generator implementation into
        the random base class since it is the default/only uniform number generator that will
        be used.
        Changed the random base class so that it utilizes differnt methods to generate standard
        normals and has a default uniform number generator.
        Added two derived random number generators that uses Beasley-Sringer-Moro and Magsarlia-Bray
        version of Box-Muller methods.

Nov.15: Added generator using the Acceptance-Rejection method.
        Added a generator using antithetic variance reduction technique for Monte-Carlo.
        Added the file that runs a monte-carlo simulation functions.

Nov.16: Fixed the bugs to generate standard normal random numbers in the generators.

Nov.18: Modified the condition checks in Box-Muller and Acceptance-Rejection generators.
        Corrected minor issues and Acceptance-Rejection generator.
        Separated Monte-Carlo functions into hpp and cpp files.
        Wrote a demonstration of the use of Monte-Carlo function.

Nov.20: Corrected minor issue in the Monte-Carlo simulation function - forgot to discount the option
        payoffs to exp(-rt).
        Changed the definition of the random number generators (get rid of the step attribute),changed
        the declaration of the get_uniform() and get_normal() functions to make them more flextible to
        fit the use of Monte-Carlo simulation (takes in arguments to know how many random numbers needed
        to be generated and how many simulations needed to perform in the whole simulation, returns a 
        2-dimensional deque of doubles). 
        
        
        Work to be done: need to redefine the get_normal() functions.
