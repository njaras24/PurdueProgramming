#!/usr/bin/env/python

### hw2_starter.py

import sys
from BitVector import *

#################diffusion.py##################
#################Call format###################
########## diffusion.py BitVector BitVector##########


################################   Initial setup  ################################

# Expansion permutation (See Section 3.3.1):
expansion_permutation = [31, 0, 1, 2, 3, 4, 3, 4, 5, 6, 7, 8, 7, 8, 
9, 10, 11, 12, 11, 12, 13, 14, 15, 16, 15, 16, 17, 18, 19, 20, 19, 
20, 21, 22, 23, 24, 23, 24, 25, 26, 27, 28, 27, 28, 29, 30, 31, 0]

# P-Box permutation (the last step of the Feistel function in Figure 4):
p_box_permutation = [15,6,19,20,28,11,27,16,0,14,22,25,4,17,30,9,
1,7,23,13,31,26,2,8,18,12,29,5,21,10,3,24]

# Initial permutation of the key (See Section 3.3.6):
key_permutation_1 = [56,48,40,32,24,16,8,0,57,49,41,33,25,17,9,1,58,
50,42,34,26,18,10,2,59,51,43,35,62,54,46,38,30,22,14,6,61,53,45,37,
29,21,13,5,60,52,44,36,28,20,12,4,27,19,11,3]

# Contraction permutation of the key (See Section 3.3.7):
key_permutation_2 = [13,16,10,23,0,4,2,27,14,5,20,9,22,18,11,3,25,
7,15,6,26,19,12,1,40,51,30,36,46,54,29,39,50,44,32,47,43,48,38,55,
33,52,45,41,49,35,28,31]

# Each integer here is the how much left-circular shift is applied
# to each half of the 56-bit key in each round (See Section 3.3.5):
shifts_key_halves = [1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1] 



#################################### main #######################################
def diffusion_or_confusion(RE,LE,encrypt_or_decrypt,rkey,s_box):
    bitvec = BitVector(size=64)
    for i in range(16):
        ## write code to carry out 16 rounds of processing
        TMP = RE
    
        ## Expansion_permutation
        RE = RE.permute(expansion_permutation)
        # Get the order of key right
        if encrypt_or_decrypt == "encrypt":
            RE = RE ^ rkey[i]
        elif encrypt_or_decrypt == "decrypt":
            RE = RE ^ rkey[15 - i]
        ## Do the S_boxes subsititution
        k=0
        output = BitVector(size = 0)
        for ct in range(8):
            row = RE[k]*pow(2,1) + RE[k+5]*pow(2,0)
            col = RE[k+1]*pow(2,3) + RE[k+2]*pow(2,2)+ RE[k+3]*pow(2,1) + RE[k+4]*pow(2,0)                           
            sbox_val = s_box[ct][row][col]
            
            sbox_bv = BitVector(intVal = int(sbox_val), size = 4)
            output += sbox_bv
            k += 6
        ## Permutation with P-Box
        output = output.permute(p_box_permutation)

        ## XOR with original LE
        RE = LE ^ output
        LE = TMP
    ## Add RE and LE up
    bitvec = RE + LE

    return bitvec

if __name__ == "__main__":
    main()
