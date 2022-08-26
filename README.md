# bayes-net

This project is a programming assignment from the Artificial Intelligence course taught at Trinity College in Hartford Connecticut.

The purpose of the assignment is to implement a bayesian network using two different sampling algorithms: prior sampling, and a choice of
either rejection sampling and likelihood weighting; I chose rejection sampling. 

## Project Description
On Patriots’ Day (a holiday observed by several states in the US, including Massachusetts, on
the third Monday in April), the Tortoise and the Hare have their annual footrace in a small
town in eastern Massachusetts. On the morning of the race, either the short or the long
course is chosen at random. Another major factor is the weather, which can be cold and wet,
very hot, or very nice. The short course favors the Hare. The Hare does not like cold and wet
weather, frequently leaving the course and taking shelter. The Tortoise does not like the heat,
although on the long course there are some muddy puddles that it can use to cool off.

Implement this network with the probabilities indicated below. You will need to implement
two algorithms for sampling:
- PRIOR-SAMPLE, which is run without any evidence to generate a sample for the general
case. Run many times, it should give a probability distribution for the Hare’s winning.
- Your choice of REJECTION SAMPLING or LIKELIHOOD WEIGHTING, which are run in the presence
of evidence.

Using these two algorithms, generate answers to the following three queries:
1. In general, how likely is the Hare to win?
2. Given that is it coldWet, how likely is the Hare to win?
3. Given that the Tortoise won on the short course, what is the probability distribution for
the Weather?
Rather than interpreting queries at the keyboard, these may be hard-coded with a menu
selection to run one of them.

### Need to compile with -lm at the end of the gcc command so that the round() function can be correctly linked.
