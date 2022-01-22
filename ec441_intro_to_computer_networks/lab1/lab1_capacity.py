__author__ = "George Kent Scheller"
__email__ = "georgeks@bu.edu"
__lab__ = "lab1"

"""
Lab 1 : Switching Capacity
"""



# Correct output
"""
Given link rate 1000000 and user rate 100000, users active 10.0%
blocking probability is 0.000424

Given link rate 1000000 and user rate 100000, users active 10.0%
blocking probability limit of 0.00043, the capacity is
10 for circuit switching and 35 for packet switching.
"""

# the following function is included so that you can calculate
# n-choose-k  or C(n,k)

#from scipy.special import comb
import math
def C (n,k):#wrote because it was too complicated to add scipy to the python path variable in spyder
    if (n>k):
        return (math.factorial(n)/(math.factorial(k) * math.factorial(n-k)))
    else :
        return -1 
def binomial(n,k,p):# see above, although idk if scipy has a binomial function?it very much does
    if (n>k and p<=1):
        return C(n,k)*math.pow(p,k)*math.pow((1-p),(n-k))
    else:
        return -1
def prob_block(Rlink, Ruser, active, N):
    
  """return the probability of blocking on a shared 
  packet switched link, given these parameters:
  Rlink - data rate of the shared link
  Ruser - data rate of each user when active
  active - fraction of time each user is active
  N - number of packet switching users
  
  brainstorm section{
    need 10 tails to block 
  p of 1 blocking 0.1 
  p of 2 blocking 0.1 
  N choose 
  10 Union p 0.1
  N users 
  p = probability of blocking/ total situations
  research different rvs geo binom pison etc...
  binomial formula = (n -c -k)*p^n*(1-p)^(n-k)
  binomial sum to the block limit and substract from 1
}
  first code test{
  numUsers = C(N,blockinglim)
  
  pk = math.pow(active,blockinglim) 
  n_k = N-blockinglim
  invP = 1-active
  p1_n = math.pow(invP,n_k)
  a = numUsers*pk
  p = a*p1_n
  print(p)
  }
  """
  blockinglim = math.floor(float(Rlink)/Ruser)+1#calculates the most you can have then adds one
  sump = 0# sums probs
  # i think the way to do the intagral out to infinity of greater than is to take the fininte inegral
  # of the other side and subtract it from one... well its what Im doing
  if N>=blockinglim:
      for i in range(blockinglim):
          sump = sump + binomial(N,i,active)
      return 1-sump
  else:
      return -1

def capacity(Rlink, Ruser, active, block_limit):
  """return the number of users that can be supported on a
  shared link using circuit switching and using packet switching,
  given these parameters:
  
  Rlink - data rate of the shared link
  Ruser - data rate of each user when active
  active - fraction of time each user is active
  block_limit - maximum probability of blocking that is acceptable
    for the packet switching case.

  The return value should be a two-tuple containing the number of 
  users supported by circuit switching followed by the number of
  users supported by packet switching.
  """
  blockinglimC = math.floor(float(Rlink)/Ruser)# i wrote this in the last one
  num = -2# done to differentiate this error from the helper functions

  for i in range(Ruser):# done to stop infinate looping but could be a while loop 
          # basically were counting up until we reacha probiblity over the limit max 
          # this works because probibility is low if there are fewer N's
          # idk if this takes care of the edge case were N = blockinglimC is above the block limit
          if((prob_block(Rlink, Ruser, active, 1+i) >block_limit) and not i == 0):
              #this step adds 1 to the current index so you dont have to loop as many times
              num = i
              break
  return (blockinglimC, num)


def main():
    # This section is only here so you can run your python code 
    # directly from the command line by typing
    #   $ python3 lab2_yourname.py
    # There is nothing to do here.  
    R=1000000
    r=100000
    active = 0.1
    N=35
    pb = prob_block(R, r, active, N)

    print(f"Given link rate {R} and user rate {r}, with {N} users active {active:.1%}")
    print(f"of the time, the blocking probability is {pb:.6f}")

    limit = 0.00043
    (C,P) = capacity(R, r, active, limit)
    
    print(f"\nGiven link rate {R} and user rate {r}, users active {active:.1%}")
    print(f"blocking probability limit of {limit}, the capacity is")
    print(f"{C} for circuit switching and {P} for packet switching.")


if __name__ == '__main__':
  main()

