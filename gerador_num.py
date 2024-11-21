import numpy as np

from sklearn.utils import shuffle

with open('nums.txt', 'w') as f:
    nums = np.arange(0,100_001,1) 
    print(nums)
    nums = shuffle(nums)
    for n in nums:
        f.write(f'{n}\n')


