--unionDFA :: DFA s1 a1 -> DFA s2 a2-> DFA () (s1,s2)
unionDFA z1 (qs1, sigma, delta1, q1, inF1)  z2 (qs2, sigma2, delta2, q2, inF2) = (qs, sigma, delta, q0, True)
   where  
      qs = [(r1,r2) | r1 <- qs1, r2 <- qs2]
      delta (r1,r2) a = (delta1 r1 a, delta2 r2 a)
      q0 = (q1, q2)
      inF (r1,r2) = (inF1 r1) || (inF2 r2)