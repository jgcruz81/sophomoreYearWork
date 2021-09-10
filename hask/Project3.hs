module Project3 where
import Control.Monad
import Control.Exception
import Data.List
import System.Timeout
--import qualified Project3 as P

 
data RE a
    = Symbol a
    | Empty
    | RE a :+: RE a
    | RE a :|: RE a
    | Repeat (RE a)
    | Plus (RE a)
    deriving (Show, Read, Eq, Ord)

data ABC = A | B | C deriving (Show, Read, Eq, Ord)



okay = Symbol B :|: Symbol C
match :: (Eq a) => RE a -> [a] -> Bool
match r = any (null . snd) . matchPre r

matchPre :: (Eq a) => RE a -> [a] -> [(Bool,[a])]
matchPre (Symbol a) (x:xs) | x == a = [(True, xs)]
matchPre (Symbol a) _ = []
matchPre Empty xs = [(False, xs)]
matchPre (r :|: s) xs = matchPre r xs ++ matchPre s xs
matchPre (r :+: s) xs = do
     (r_consumed, ys) <- matchPre r xs
     (s_consumed, zs) <- matchPre s ys
     return (r_consumed || s_consumed, zs)
matchPre (Repeat r) xs = (False, xs) : do
     (r_consumed, ys) <- matchPre r xs
     guard r_consumed
     (_, zs) <- matchPre (Repeat r) ys
     return (True, zs)
matchPre (Plus r) xs = do
     (r_consumed, ys) <- matchPre r xs
     (s_consumed, zs) <- matchPre (Repeat r) ys
     return (r_consumed || s_consumed, zs)

atMost2As :: RE ABC
atMost2As = Empty :|: (Repeat(Repeat(Symbol C) :+: Repeat( Symbol B)) :+: 
   Symbol A :+: Repeat(Repeat(Symbol C) :+: Repeat(Symbol B))) :|: (Repeat(Repeat
   (Symbol C) :+: Repeat( Symbol B))) :|: (Repeat(Repeat(Symbol C) :+: Repeat
   (Symbol B)) :+: Symbol A :+: Repeat(Repeat(Symbol C) :+: Repeat(Symbol B)) 
   :+: Symbol A :+: Repeat(Repeat(Symbol C) :+: Repeat(Symbol B)))
   
anyOf :: [a] -> RE a
anyOf [] = Empty
anyOf [r] = Symbol r
anyOf (r:s) = Symbol r :|: anyOf s


repeats :: Int -> Int -> RE a -> RE a
repeats x y a
   | x < y = (peat x a) :|: repeats (x+1) y a
   | x == y = peat y a 

peat :: Int-> RE a-> RE a
peat 1 a = a
peat 2 a = a :+: a
peat 3 a = a :+: a :+: a
peat x a
   | x > 1 = a :+: peat(x-1) a



matchEmpty :: RE a -> Bool
matchEmpty Empty = True
matchEmpty (Repeat(a)) = True
matchEmpty (Plus(a)) = False
matchEmpty (Symbol a) = False
matchEmpty (a:+:b) = both (matchEmpty a) (matchEmpty b)
matchEmpty (a:|:b) = both2 (matchEmpty a) (matchEmpty b)


both :: Bool -> Bool -> Bool
both True True = True
both _ _ = False

both2 :: Bool -> Bool -> Bool
both2 False False = False
both2 _ _ = True




minLength :: RE a -> Integer
minLength a = seeless a 1

maxLength :: RE a -> Maybe Integer
maxLength a -- = Just (toInteger( round (toRational(seemore a 1))))
   |seemore a 1 == 1/0 = Nothing  
   |otherwise = Just (toInteger( round (toRational(seemore a 1))))


seemore :: (Fractional a, Real a) => RE b -> a -> a
seemore (a:+:b) x = seemore (a) (x) + seemore b x
seemore (a:|:b) x = max (seemore a y) (seemore b z)
   where y = x
         z = x
seemore (Symbol a) x = x
seemore Empty x = 0
seemore (Repeat(a)) x = 1/0
seemore (Plus(a)) x = 1/0

-----------------------

seeless :: RE a -> Integer -> Integer
seeless (a:+:b) x = (seeless a x) + seeless b x
seeless (a:|:b) x = min (seeless a y) (seeless b z)
   where y = x
         z = x
seeless (Symbol a) x = x
seeless Empty x = 0
seeless (Repeat(a)) x = 0
seeless (Plus(a)) x = 1





yello :: RE a -> [a]
yello Empty = []
yello (a:|:b) = yello a ++ yello b
yello (Symbol a) = [a]































