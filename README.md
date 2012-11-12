<link href="http://kevinburke.bitbucket.org/markdowncss/markdown.css" rel="stylesheet"></link>
Monte-Carlo
===========

A simple implementation of the Monte-Carlo simulation for pricing options.

Contents:

1.payoff: the interface and classes responsible for calculating the payoffs of 
          different kind of options.

2.statgatherer: statistics gatherer responsible for keeping track of the max, min, and mean
                of the numbers.

3.random: the interface for random number generators

4.randomlcg: the random number generators using linear congruential method to generate
             underlying uniformly distributed random numbers.

5.wrapper: template wrapper to handle pointers and memory management.



Timeline:

Nov.10: Finished basic implementation of the option payoff and statistics gatherer class.

Nov.12: Added a template wrapper class to handle pointers.
        Finished basic implementation of random number generator class 
        Added a random number generator using linear congruential method.
