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

6.wrapper: template wrapper to handle pointers and memory management.

:

*Timeline:*

Nov.10: Finished basic implementation of the option payoff and statistics gatherer class.

Nov.12: Added a template wrapper class to handle pointers.
        Finished basic implementation of random number generator class 
        Added a random number generator using linear congruential method.

Nov.14:     Deleted randomlcg file. Moved the linear congruential generator implementation into
        the random base class since it is the default/only uniform number generator that will
        be used.
            Changed the random base class so that it utilizes differnt methods to generate standard
        normals and has a default uniform number generator.
            Added two derived random number generators that uses Beasley-Sringer-Moro and Magsarlia-Bray
        version of Box-Muller methods.
