### Poincare's prediction

> *after the unrolling of innumerable centuries, everything would return to its original state.*

  *"Imagine that we initially have a bucket A, filled with 100 balls, each labelled uniquely with numbers from 1 to 100, and another B, containing nothing. Also imagine a bucket of chips uniquely numbered 1 to 100. Randomly pick a chip and read its number, N. Take the ball numbered N from bucket A and place it in bucket B. Replace the  chip and repeat the process. Each time the chip N is picked, move the ball labelled N from whatever bucket it is in to the other bucket. (...) Can you guess what will happen in the long run? It may seem counterintuitive, even amazing, but with absolute certainty, all the balls will eventually return to  container A, though it will take an enormously long time for that to happen. **Poincare's general theorem on dynamical systems predicts this**."* - Joseph Mazur - The Maths and Myths of coincidences

This script puts to the test this prediction.  
Each 5 billion steps it prints the number of times the number of balls in bucket A was:  
* between 71 and 80
* between 81 and 90
* between 91 and 100

If the number of balls in bucket A reaches 100 it will print *"Back to the beginning"* and will stop. 

<u>edit:</u>  
After 8 hours the number of balls in bucket A reached between:  
* 71 and 80 balls 5615300 times
* 81 and 90 balls 34 times
* 91 and 100 balls 0 times

27 years later, there would have been a high chance that the number of balls in the A bucket would have exceeded 90 at least once. Quite a long time...
