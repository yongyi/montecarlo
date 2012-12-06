<link href="http://kevinburke.bitbucket.org/markdowncss/markdown.css" rel="stylesheet"></link>
Monte-Carlo
===========

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

        
        
*Dec.5 -- Started Version 2.0 of the Monte-Carlo pricer to better performs the tasks of the course so that it is easier to use and understand*


*What Happened: The Monte-Carlo class will be splitted into two separate classes: the Monte-Carlo General and Monte-Carlo Vanilla.
Monte-Carlo General will be responsible for pricing any kind of options given the payoff defition of the option regardless its 
path-dependency. The Monte-Carlo Vanilla is used only to price European put or call options, along with the option's simulated delta
and vega, with a choice of the variance reduction technique.*


*Reason for the change: even though the two Monte-Carlo classes are very similar, there are additions as well as subtractions in
the Monte-Carlo Vanilla compared to Monte-Carlo General. The Monte-Carlo Vanilla is also responsible for estimating deltas and vegas
of the European options while the Monte-Carlo General only serves as a pricer. In order to make sure the simulated values of the price,
delta, vega of a given vanilla option come from the same sequence of random numbers, the designed and structure of the simulation
functions in the two classes ought to be different. In addition, the interface and codes will be clearer, easier to understand and use if 
the Monte-Carlo is broken into two different classes in this case - a praticability issue*


Dec.5: Separated Monte-Carlo into Monte-Carlo general and Monte-Carlo vanilla such that the general
       can be used to price ANY options with any forms of payoffs; the vanilla will be used only to
       price vanilla European options (call or put) and the corresponding greeks.
       
       Redefined the random number gernerators' get_uniform() and get_normal functions. The get_uniform() function
       takes in an integer N as the number of uniformed needed to be generated and the get_normal() takes 
       in the integer N which is to be passed to get_uniform() to generated N uniforms, then converts the N
       uniforms into normals by the chosen method. The Monte-Carlo General class will get the normals from
       the generator and converts them into a n simulations * m steps per simulation grid for simulation.

Dec.6: Finshed the implementation of Monte-Carlo General and Monte-Carlo Vanilla.
