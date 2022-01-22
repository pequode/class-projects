import matplotlib.pyplot as plt
import numpy as np
#Parameters
n = 10
p = 0.5
numtrials = 100
#Generate Binomial(n,p) random variables
X = np.random.binomial(n,p,numtrials)
#Plot
plt.stem(X)
plt.xlabel('Trial Number')
plt.ylabel('X')
plt.axis([1, numtrials, 0, n])
plt.show()